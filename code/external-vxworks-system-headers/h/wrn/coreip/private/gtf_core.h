/* gtf_core.h - general timer facility - core */

/*
 * Copyright (c) 2001-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01r,10nov10,dlk  Move extern "C" after last header file include. WIND00240828.
01q,16apr07,dcc  added _WRS_FASTDATA to the definition of netGtfSeconds.
01p,20feb07,kch  Merged from base6_iter12_smp-dev - Use spinlocks instead of
                 intLock.
01o,27dec06,kch  Removed references to the obsolete coreip virtual stack.
01n,10jul05,dlk  Optimizations. Use L_NODE lists rather than DLL_LIST lists
                 to avoid needing to reference the list head when removing
                 a timer from the expire list. Replace timerMutex with
                 intLock/intUnlock.
01m,31jan05,sar  Fix defects found in GTF code inspection of 10/26/2004 
                 as described in SPRs 106685 - 105688
01l,17jan05,vvv  osdep.h cleanup
01k,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01j,02jul04,vvv  changed vsnum from VSNUM to VSID
01i,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/2)
01h,25nov03,wap  Merge changes from Snowflake
01g,20nov03,niq  Remove copyright_wrs.h file inclusion
01f,04nov03,rlm  Ran batch header path update for header re-org.
01e,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01d,27oct03,rlm  update include statements post header re-org.
01c,07aug03,nee  Merging to Base6 from ACCORDION_BASE6_MERGE_BASELINE label on
                 Accordion codeline
01b,03feb02,ham  changed for tornado build.
01a,06jun01,deg  written.
*/

#ifndef __INCgtf_coreh
#define __INCgtf_coreh

#include <netVersion.h>
#include <wdLib.h>
#include <semLib.h>
#include <sllLib.h>
#include <dllLib.h>
#include <spinLockLib.h>
#include <private/gtf_util.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * For virtual stack, the source files that include this header must
 * include vsNetCore.h to find splSemId and splTid
 */

IMPORT SEM_ID splSemId; /* spl mutex semaphore id */
IMPORT INT32 splTid; /* task which currently owns splSemId */

/* defines */

/* The LOCAL_ALLOC bit indicates if the GTF has allocated the memory for
 * the timer.  It is set if GTF did so.
 * The ACTIVE bit indicates if the user has serviced this timer.  It is cleared
 * by GTF when initializing a timer structure and then set when a timer is
 * activated (started or reset).  It is cleared if the timer is stopped
 * (cancel or delete).  It is left for the user to clear when the timer
 * expires.
 * The PENDING bit indicates if the timer is queued in the GTF timer wheels.
 * It is cleared by GTF when initializing a timer structure and then set when
 * a timer is activated (started or reset).  It is cleared when the timer is
 * removed from the timer wheels (cancel, delete or expire).
 */

#define TIMER_LOCAL_ALLOC 0x0001 /* true if GTF allocates timer memory */
#define TIMER_ACTIVE 0x0002      /* true if timer has not been served */
#define TIMER_PENDING 0x0004     /* true if timer is waiting for timeout */

#define TICKS         tickGet()

#define TICK_LT(x,y)  ((long)((x) - (y)) < 0)
#define TICK_GT(x,y)  ((long)((x) - (y)) > 0)
#define TICK_LEQ(x,y) ((long)((x) - (y)) <= 0)
#define TICK_GEQ(x,y) ((long)((x) - (y)) >= 0)

#define time_second   netGtfSeconds


/* typedefs */

struct gtfTimerManager;
struct gtfTimer;

typedef int (*GTF_TIMER_HANDLER)(void*); 
typedef void (*GTF_TICK_FUNC) (struct gtfTimerManager *, void *);

/*
 * This structure is used both for the head and for nodes within
 * a circular list.  We want to be able to remove a node without
 * referencing the list head, and to add quickly to the tail end
 * of a list, and fetch the first node quickly. When used as a
 * list head, pNext indicates the first entry of the list and
 * pPrev indicates the last entry.
 */
typedef struct L_NODE
    {
    struct L_NODE * pPrev;
    struct L_NODE * pNext;
    } L_NODE;

#define L_EMPTY(h) ((h) == (h)->pNext)

#define L_INIT(h)				\
    do  {					\
	(h)->pPrev = (h);			\
	(h)->pNext = (h);			\
	} while ((0))

/*
 * Be careful. After L_REMOVE/L_GET, a node is left with dangling
 * references to the list it was in.
 */
#define L_REMOVE(n)				\
    do  {					\
	L_NODE * _pPrev_ = (n)->pPrev;		\
	L_NODE * _pNext_ = (n)->pNext;		\
	_pPrev_->pNext = _pNext_;		\
	_pNext_->pPrev = _pPrev_;		\
	} while ((0))

#define L_GET(h, n)				\
    do  {					\
	L_NODE * _pNext_;			\
	(n) = (void *)((h)->pNext);		\
	_pNext_ = ((L_NODE *)(n))->pNext;	\
	(h)->pNext = _pNext_;			\
	_pNext_->pPrev = (h);			\
	} while ((0))

#define L_SPLICE(_prev, _next, n)		\
    do  {					\
	(n)->pPrev = (_prev);			\
	(n)->pNext = (_next);			\
	(_prev)->pNext = (n);			\
	(_next)->pPrev = (n);			\
	} while ((0))

#define L_ADD(h, n)				\
    do  {					\
	L_NODE * _pPrev_ = (h)->pPrev;		\
	L_SPLICE (_pPrev_, (h), (n));		\
	} while ((0))

typedef struct gtfTimerUnitManager
{
  L_NODE *timerWheel;            /* array of timer slots */  
  unsigned int fuzzyMask;         /* lsb bits (error range) */
  unsigned int shiftBits;         /* # bits of fuzzy mask */
  unsigned long nbrFiredTimer;    /* # fired timer */
  unsigned int nbrOutstandTimer;  /* # outstanding timer */
} GTF_TIMER_UNIT_MANAGER;

typedef struct gtfTimerManager
{
  GTF_TIMER_UNIT_MANAGER *timerUnitManager; /* array of timer units */
  unsigned int nbrTimerUnit;      /* # of timer units */ 
  unsigned int nbrTimerSlot;      /* # of timer slots */
  unsigned int timerUnitMask;     /* mask to realize wrap-around array  */
  unsigned int binPowGranScale;   /* binary power of gran. scaling factor */
  unsigned long currTicks;        /* current GTF tick number  */
  unsigned int relSysClkTicks;    /* # system ticks per clock delay  */
  unsigned int maxTimerTicks;     /* max timer tick value */
  SL_LIST  timerQueue;            /* timer free queue */
  unsigned int maxAllocTimer;     /* # of timer in free queue */
  unsigned int currAllocTimer;    /* # of allocated timer in free queue */
  WDOG_ID clock;                  /* clock */
  SEM_ID mngrMutex;               /* manager lock */
  SEM_ID count;                   /* counting semaphore */
  GTF_TICK_FUNC tickFunc;         /* external tick function */
  void * tickArg;                 /* second arg to external tick function */
  SL_LIST timerBlocks;            /* blocks of memory for allocated timers */
  L_NODE * timerListMemory;      /* Memory allocated for the heads of the */
                                  /* timer lists, for use when deleting the */
                                  /* manager */
  spinlockIsr_t lock;	          /* manager lock */
} GTF_TIMER_MANAGER;

typedef struct gtfTimer
 {
   union 
   {
     L_NODE expNode;              /* node of expire list */
     SL_NODE freeNode;            /* node of free queue */
   } timerLinking; 
   unsigned int timerTicks;       /* timer ticks */
   unsigned int timerUnit;        /* timer unit */
   unsigned int timerFlags;       /* timer flags */
   GTF_TIMER_HANDLER handler;     /* timer handler */
   void* arg;                     /* argument to timer handler */
} GTF_TIMER;

extern unsigned long _WRS_FASTDATA netGtfSeconds;

extern GTF_TIMER_MANAGER *
    gtfTimerManagerCreate(unsigned int  nbrTimerUnit,
			  unsigned int  binPowTimerSlot,
			  unsigned int  binPowGranScale,
			  unsigned int  sizeTimerFreeQueue,
			  unsigned int  hertz,
			  GTF_TICK_FUNC tickFunc,
			  void * tickArg
			  );

extern int gtfTimerManagerRun(GTF_TIMER_MANAGER *tm);

extern int gtfBookkeeping(GTF_TIMER_MANAGER *tm);

extern int gtfTimerManagerDelete(GTF_TIMER_MANAGER *tm);

extern GTF_TIMER *gtfTimerCreate(GTF_TIMER_MANAGER *tm);

extern int gtfTimerInit(GTF_TIMER_MANAGER* tm,
			GTF_TIMER *t,
			unsigned int toTicks,
			GTF_TIMER_HANDLER th,
			void* arg
			);

extern int gtfTimerDelete(GTF_TIMER_MANAGER *tm,
			  GTF_TIMER *t);

extern int gtfTimerStart(GTF_TIMER_MANAGER *tm,
			 GTF_TIMER *t
			 );

extern int gtfTimerReset(GTF_TIMER_MANAGER* tm,
			GTF_TIMER *t,
			unsigned int toTicks,
			GTF_TIMER_HANDLER th,
			void* arg
			);

extern int gtfTimerCancel(GTF_TIMER_MANAGER *tm,
			  GTF_TIMER *t
			  );

extern int gtfShow(GTF_TIMER_MANAGER *tm);

extern int gtfGetNbrFiredTimer(GTF_TIMER_MANAGER *tm,
			       unsigned int timerUnit
			       );

extern int gtfGetNbrOutstandTimer(GTF_TIMER_MANAGER *tm,
				  unsigned int timerUnit
				  );

#ifdef __cplusplus
}
#endif

#endif /* __INCgtf_coreh */ 

