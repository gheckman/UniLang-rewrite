/* timerLibP.h - private POSIX 1003.4 Clocks & Timers header */

/*
 * Copyright (c) 1991-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
04a,22dec10,cww  added timerEventNode field in timer structure
03z,13jul10,pcs  Update the data type of tickBase from UINT32 to _Vx_ticks64_t
03y,09jun10,jpb  Fixed merge issue with TV_CONVERT_TO_TICK.
03x,03jun10,pad  Adapted TV_CONVERT_TO_TICK_NO_PARTIAL to LP64.
03w,17may10,jpb  Fixed TV_CONVERT_TO_TICK to fix build warnings for LP64.
03v,29apr10,pad  Moved extern C statement after include statements.
03u,06apr10,jpb  Added clockLibInit prototype.
03r,10nov09,gls  modified TV_CONVERT_TO_TICK() to compensate for partial tick
                 added TV_CONVERT_TO_TICK_NO_PARTIAL() (WIND00186253)
03t,26aug09,jpb  Updated for LP64 support.
03s,22jun07,lei  changed WDOG_ID to a union in struct __timer
03r,07feb07,jmg  Changed comment from vxTicks to vxAbsTicks
03q,31oct06,jmg  Added verbose mode to timer_show as part of Defect
                 #WIND00039293
03p,18sep06,jmg  Added { and } to some of the macros as part of Defect
                 #WIND00059292
03o,17feb06,jln  added TV_ROUNDUP macro
03n,26oct04,fr   added timerOpenInit() routine (SPR 101491)
03m,28sep04,fr   removed vTimerCreate prototype (SPR 101349)
03l,23aug04,lei  added timer_destroy() prototype.
03k,31mar04,dcc  added vTimerCreate() prototype. Added timerClassId declaration.
03j,02dec03,ans  code inspection changes
03i,22oct03,ans  added extern declaration for timerLibInit.
03h,30sep03,ans  User-level timer support.
03g,12nov01,gls  Account for system clock rate (SPR #70255)
03f,27jun96,dbt  modified TV_CONVERT_TO_TICK to round up the value to
		 return (SPR #5647).
		 Updated copyright.
03e,29nov93,dvs  updated for POSIX draft 14
03d,23sep92,kdl  changed name to timerLibP.h
03c,22sep92,rrr  added support for c++
03b,31jul92,gae  added sigevent.h, time.h and timers.h includes.
03a,22jul92,gae  Draft 12 revision; removed object stuff; moved
		 some prototype definitions to timers.h.
02a,04jul92,jcf  cleaned up.
01d,26may92,rrr  the tree shuffle
01c,30apr92,rrr  some preparation for posix signals.
01a,16oct91,gae  written.
*/

/*
DESCRIPTION
This file provides header information for the
POSIX 1003.4 Clocks & Timers interface per Draft 12.
*/

#ifndef __INCtimerLibPh
#define __INCtimerLibPh

#include <vxWorks.h>
#include <sllLib.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <sigevent.h>
#include <private/sigLibP.h>
#include <private/objLibP.h>
#include <private/pxCpuTimeLibP.h>
#include <wdLib.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __timer
    {
    OBJ_CORE            objCore;        /* object core */

    union                               
        {                               
        WDOG_ID         wdog;   
        void *          pxCpuTimer;     /* POSIX cpu timer */
        } expireId;                     /* expiry mechanism */

    int			active;		/* wdog is set */
    TASK_ID		taskId;		/* "owner" of timer */
    clockid_t		clock_id;	/* always CLOCK_REALTIME */
    SIGEVENT_ID         sigevId;        /* sigevent ID for async notification */
    struct sigevent	sevent;		/* user's signal event */
    struct itimerspec	exp;		/* time to go off plus interval */
    TIMER_CONNECT_FUNC	routine;	/* user's routine */
    _Vx_usr_arg_t	arg;		/* argument to user's routine */
    struct timespec     timeStamp;	/* timestamp when timer is armed */
    SL_NODE             timerEventNode; /* list node for queueing sigevents */
    int                 queuedCnt;      /* number of times timer is queued */
    } TIMER;

typedef struct clock
    {
    _Vx_ticks64_t   tickBase;		/* vxAbsTicks when time set */
    struct timespec timeBase;		/* time set */
    } CLOCK;

extern struct clock _clockRealtime;
extern CLASS_ID		timerClassId;		/* timer class id */

/* macros for "time value" manipulation */

#define BILLION         1000000000	/* 1000 million nanoseconds / second */

#define TV_EQ(a,b)	\
        ((a).tv_sec == (b).tv_sec && (a).tv_nsec == (b).tv_nsec)
#define TV_GT(a,b)	\
        ((a).tv_sec  > (b).tv_sec ||	\
        ((a).tv_sec == (b).tv_sec && (a).tv_nsec > (b).tv_nsec))
#define TV_LT(a,b)	\
        ((a).tv_sec  < (b).tv_sec ||	\
        ((a).tv_sec == (b).tv_sec && (a).tv_nsec < (b).tv_nsec))
#define TV_ISZERO(a)	\
        ((a).tv_sec == 0 && (a).tv_nsec == 0)
#define TV_SET(a,b)	\
        {(a).tv_sec = (b).tv_sec; (a).tv_nsec = (b).tv_nsec;}
#define TV_ADD(a,b)	\
        {(a).tv_sec += (b).tv_sec; (a).tv_nsec += (b).tv_nsec; TV_NORMALIZE(a);}
#define TV_SUB(a,b)	\
        {(a).tv_sec -= (b).tv_sec; (a).tv_nsec -= (b).tv_nsec; TV_NORMALIZE(a);}
#define	TV_NORMALIZE(a)	\
	if ((a).tv_nsec >= BILLION)	\
	    { (a).tv_sec++; (a).tv_nsec -= BILLION; }	\
	else if ((a).tv_nsec < 0)	\
	    { (a).tv_sec--; (a).tv_nsec += BILLION; }
#define TV_VALID(a)	\
        ((a).tv_nsec >= 0 && (a).tv_nsec < BILLION)
#define TV_ZERO(a)	\
        {(a).tv_sec = 0; (a).tv_nsec = 0;}

/* Round up the whole time value based on resolution */

#define TV_ROUNDUP(a) 						\
    do  {    							\
        ULONG offset;       					\
        UINT32 hz = (UINT32) sysClkRateGet(); 			\
        register UINT32 res = (BILLION / hz); 			\
								\
        offset = ((UINT64)((a).tv_sec) * (BILLION % res) + 	\
                  (UINT64)((a).tv_nsec)) % res; 		\
        if (offset != 0) 					\
            {            					\
            (a).tv_nsec += (res - offset); 			\
            TV_NORMALIZE (a)                			\
            }							\
        } while (0)

#define TV_CONVERT_TO_SEC(a,b)  				\
    do { 							\
       register UINT32 hz = sysClkRateGet(); 			\
       (a).tv_sec  = (time_t)((b) / hz);   			\
       (a).tv_nsec = (long)(((b) % hz) * (BILLION / hz)); 	\
       } while (0)

#define TV_CONVERT_TO_TICK(a,b) 				\
    do  { 							\
        register ULONG hz = (ULONG) sysClkRateGet(); 		\
        register ULONG res = (BILLION / hz); 			\
        (a) = (UINT64) ((b).tv_sec) * hz + 			\
	      (UINT64) ((b).tv_nsec) / res + 			\
              (((UINT64)((b).tv_nsec) % res) ? 2 : 1); 		\
        } while (0)

#define TV_CONVERT_TO_TICK_NO_PARTIAL(a,b) 			\
    do  { 							\
        register ULONG hz = sysClkRateGet(); 			\
        register ULONG res = (BILLION / hz); 			\
        (a) = (UINT64) ((b).tv_sec) * hz + 			\
 	      (UINT64) ((b).tv_nsec) / res + 			\
              (((UINT64)((b).tv_nsec) % res) ? 1 : 0); 		\
        } while (0)
       
/* function pointers */

extern PX_CPUTIMER *    (*_func_pxCpuTimerCreate) (void);
extern STATUS           (*_func_pxCpuTimerStart)  (timer_t timerid,
                                                   int execCount);
extern STATUS           (*_func_pxCpuTimerCancel) (PX_CPUTIMER * pxCpuTimerId,
                                                   TASK_ID tid);
extern STATUS           (*_func_pxCpuTimerDelete) (PX_CPUTIMER * pxCpuTimerId,
                                                   TASK_ID tid);

#ifdef _WRS_CONFIG_SMP
extern void (*_func_pxCpuTimerCancelVerify) (PX_CPUTIMER * pxCpuTimerId,
                                             TASK_ID tid);
#endif /* _WRS_CONFIG_SMP */

/* non-standard function declarations */

extern STATUS   clockLibInit    (void);
extern STATUS   timerScLibInit  (void);
extern STATUS   clockScLibInit  (void);
extern void 	timerShowInit   (void);
extern STATUS   timerLibInit    (void);
extern void	timerOpenInit   (void);
extern int      timer_destroy   (timer_t timerid, BOOL dealloc);
extern int      clock_setres    (clockid_t clock_id, struct timespec * res);

#ifdef __cplusplus
}
#endif

#endif /* __INCtimerLibPh */
