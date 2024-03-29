/* windLibP.h - VxWorks kernel header file */

/*
 * Copyright (c) 1992, 2002-2003, 2005-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03d,18apr12,jpb  Defect# WIND00309765.  Removed duplicate definition for 
                 windTaskStateChange.
03c,29mar12,zl   added windStopClear() to support taskReset() (WIND00117574)
03b,27oct10,gls  added windStateRequestService() (WIND00204208)
03a,01jun10,gls  added WIND_STOP client ID support (WIND00210700)
02z,13aug10,cww  Use dynamically generated offsets in offset macros
02y,16jun10,pcs  Change the data type of timeout from an int to _Vx_ticks_t
02x,26apr10,cww  LP64 SMP update
02w,30mar10,pad  Moved declaration of extern C block for C++ after the
                 inclusion of header files.
02v,21oct09,cww  Moved _func_windTickAnnounceHook to windLibP.h
02t,21sep09,s_s  changed INT_CPU_LOCK() and INT_CPU_UNLOCK() to 
                 KERNEL_INT_CPU_LOCK() and KERNEL_INT_CPU_UNLOCK()
		 (WIND00181479)
02u,01jun09,zl   updated windRotate() arguments
02t,11feb09,zl   removed qLib.h inclusion
02s,07jul08,gls  added kernel lock free fast path for SMP semaphores
02r,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02q,11mar08,to   include taskLibP.h to use taskIdCurrent for UP
02p,22feb08,zl   removed unused SMP scheduler prototypes
02o,05oct07,gls  added _WRS_ASM_EXTERN_KERNEL_GLOBALS (defect #00106175)
02n,11sep07,pch  CQ101748: add EDR_SYSTEM_FATAL_INJECT temporarily
02m,08aug07,zl   added windSchedulerRestore().
02l,18jul07,lei  added windPendQCheckGet() for SMP.
02k,06may07,dlk  Add my_tkt for kernel ticket lock implementation.
02j,30apr07,lei  renamed cpu_reschedNeeded to cpu_reschedMode;
                 added _WRS_KERNEL_CPU_GLOBAL_OR/[NORMAL RR]_RESCHEDULE;
                 changed windSchedulerAdd/windCpcNeedReschedule API.
02i,26apr07,mmi  move tickLib definitions to tickLibP.h
02h,18apr07,jmg  Moved _IS_INT_CONTEXT() and VX_INT_RESTRICT() to intLibP.h
02g,12apr07,jmg  Changed intCpuLock()/Unlock to INT_CPU_LOCK/UNLOCK
02f,13mar07,lei  added windCpcNeedReschedule API and cpu_reschedNeeded;
                 removed unused  windCpcReschedule()
02e,29jan07,lei  added/renamed windScheduler[AddToAll RemoveFromAll Add Remove];
                 removed _WRS_ARCH_HAS_IDLE_TASK.
02d,07feb07,jmg  Removed vxTicks
02c,22jan07,jmg  Added Function windRotate() (Req WIND00071010).
02b,11jan07,aeg  removed windSpawn().
02a,12dec06,kk   clean up global arrays, now replaced by per-CPU globals,
                 removed references to reschedule stack
01z,05dec06,jln  embedded WORK_Q_IX structure
01y,15nov06,mmi	 removed old spinlock, update vxKernelVars
01x,01nov06,gls  renamed windCpcSuspend() to windCpcStateChange()
                 added windHold() and windRelease()
01w,31oct06,lei  surrounded IS_KERNEL_IDLE with "#ifdef _WRS_ARCH_HAS_IDLE_TASK"
01v,17oct06,lei  added cpu_idleTaskId; removed coreEnabledTbl/cpu_kernelIsIdle;
                 updated WIND_VAR offset.
01u,27sep06,pcs  Remove macros IS_KERNEL_STATE and IS_KERNEL_STATE_ME since
		 they are the same as KERNEL_ENTERED and KERNEL_ENTERED_ME
01t,27sep06,lei  Added coreEnabledTbl
01s,15sep06,lei  Added _WRS_ARCH_HAS_NEW_KERNEL_LOCK.
01r,04sep06,mmi  introduce winVars as struct-in-struct for alignment
01q,01sep06,gls  cleaned up support for vxKernelVars[]
01p,01jul06,jln  added Macros for windPriNormalSet and windPrioritySet()
01o,18aug06,lei  Added windCpcSuspend().
01n,17Aug06,mmi  #if VX_KERNEL_VARS => #ifdef
		 fixed _WRS_KERNEL_CPU_GLOBAL_GET()
01m,11Aug06,mmi  add SMP workQ, spinLockCnt, VX_KERNEL_VARS
01l,08aug06,pch  Ensure arch definitions of _WRS_WIND_VARS_ALIGN and
		 _WRS_CPU_INDEX_GET are included ahead of the fallback
		 definitions here.
01k,21jul06,lei  SMP clean up; added windSchedulerAdd/Remove/Resort API
01j,11jul06,zl   added per-CPU WIND_VARS structure and the C access macros.
01i,02feb06,lei  moved the declaration of kernelState
01h,14apr05,kk   removed prototypes for tick64[SG]et, moved to tickLib.h
01g,02jun05,md   added SMP support
01f,04aug03,elg  Add support for new task status: define
		 windStop()/windCont().
01e,28may03,rec  Power management, add windTickAnnounceN and windTickWaitGet
01d,22may02,jgn  move vxTicks & vxAbsTicks here - SPR #70255
01c,22sep92,rrr  added support for c++
01b,19jul92,pme	 added windReadyQPut() and windReadyQRemove().
		 windPendQPut(), windDelete(), windPendQRemove() return STATUS.
01a,04jul92,jcf	 extracted from wind.h.
*/

#ifndef __INCwindLibPh
#define __INCwindLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>
#include <private/qLibP.h>
#include <private/taskLibP.h>
#include <taskLib.h>
#include <semLib.h>
#include <sysLib.h>

#ifndef	_ASMLANGUAGE
#include <private/wdLibP.h>
#include <private/workQLibP.h>
#include <private/kernelLibP.h>

#ifdef	_WRS_CONFIG_SMP
#include <private/vxSmpP.h>
#include <spinLockLib.h>
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_WRS_CONFIG_SMP
    /*
     *  ***** WARNING *****
     *
     * This private header file is included by the public header file(s):
     *   - h/inline/semLibInline.h 
     *
     * Ensure that no usage of a VSB source configuration macro is made 
     * by any structure or macro in this file that is also used(directly or 
     * indirectly) by the above list of public header files.
     */

/* definitions */

/* macros */

# define _WRS_KERNEL_CPU_GLOBAL_OR(cpuid, glob, var)			     \
            vxKernelVars[cpuid].vars.cpu_##glob |= var

# define _WRS_KERNEL_CPU_GLOBAL_SET(cpuid, glob, var)			     \
	    vxKernelVars[cpuid].vars.cpu_##glob = var

# define _WRS_KERNEL_CPU_GLOBAL_GET(cpuid, glob)			     \
	    vxKernelVars[cpuid].vars.cpu_##glob

# define _WRS_KERNEL_GLOBAL_ACCESS(glob)				     \
	vxKernelVars[_WRS_CPU_INDEX_GET()].vars.cpu_##glob

# define _WRS_KERNEL_LOCKED_GLOBAL_SET(glob, var)			     \
	do								     \
	    {								     \
	    int key = KERNEL_INT_CPU_LOCK ();   /* prevent task migration */ \
	    vxKernelVars[_WRS_CPU_INDEX_GET()].vars.cpu_##glob = var;	     \
	    KERNEL_INT_CPU_UNLOCK (key);				     \
	    } while ((0))

# define _WRS_KERNEL_LOCKED_GLOBAL_GET(glob, var)			     \
	do								     \
	    {								     \
	    int key = KERNEL_INT_CPU_LOCK ();   /* prevent task migration */ \
	    var = vxKernelVars[_WRS_CPU_INDEX_GET()].vars.cpu_##glob;	     \
	    KERNEL_INT_CPU_UNLOCK (key);				     \
	    } while ((0))

#define IS_KERNEL_IDLE()  kernelIsCpuIdle(_WRS_CPU_INDEX_GET())

/* type definitions */

/*
 * _WRS_WIND_VARS_ALIGN is architecture specific; it should be defined
 * for the common CPU build variants (e.g. PPC32, MIPS32, XSCALE, etc),
 * representing the maximum cache line size of the variants of the respective
 * arch. We default here to a globally acceptable value, but should be
 * overridden in <arch/xx/archXxx.h>
 *
 * Another consideration for _WRS_WIND_VARS_ALIGN is that, from
 * compiler and assembler optimization point of view, the alignment
 * should force the size of WIND_WARS structure to be a power of 2 value.
 * Since the size of data fields in WIND_WARS is at least 0x4c bytes, the
 * smallest _WRS_WIND_VARS_ALIGN that satisfies that requirement is 128.
 */

#ifndef _WRS_WIND_VARS_ALIGN
# define _WRS_WIND_VARS_ALIGN	128
#endif

typedef struct _windVars
    {
    WIND_TCB *	  cpu_taskIdCurrent;   /* 0x00/0x00: current task ID	     */
    ISR_ID	  cpu_isrIdCurrent;    /* 0x04/0x08: current ISR ID	     */
    int		  cpu_errno;	       /* 0x08/0x10:			     */
				       /*	 errno location (for ISRs)   */
    int		  cpu_intCnt;	       /* 0x0c/0x14: interrupt nesting count */
    char *	  cpu_vxIntStackBase;  /* 0x10/0x18: interrupt stack base    */
    char *	  cpu_vxIntStackEnd;   /* 0x14/0x20: interrupt stack end     */
    WORK_Q_IX     cpu_workQIx;         /* 0x18/0x28: read,		     */
				       /* 0x1c/0x2c: bitmask,		     */
                                       /* 0x20/0x30: write		     */
    volatile BOOL cpu_workQIsEmpty;    /* 0x24/0x34: each workQ status       */
    atomic32_t    cpu_spinLockIsrCnt;  /* 0x28/0x38: counting help spinlocks */
    atomic32_t    cpu_spinLockTaskCnt; /* 0x2c/0x3c: counting help spinlocks */
    WIND_TCB *    cpu_idleTaskId;      /* 0x30/0x40: idle task ID	     */
    BOOL	  cpu_kernelIsIdle;    /* 0x34/0x48: kernel idle state	     */
    int           cpu_reschedMode;     /* 0x38/0x4c: call "reschedule()" or  */
				       /*	     not		     */
    atomicVal_t   cpu_my_tkt;	       /* 0x3c/0x50: ticket for kernel lock  */
    int		  cpu_windPwrOffState; /* 0x40/0x58: power management state  */
#ifdef _WRS_CONFIG_LP64
    int		  pad;		       /* ----/0x5c: 64-bit alignment pad    */
#endif
    char *	  cpu_reserved1;       /* 0x44/0x60: Reserved field one      */
    char *	  cpu_reserved2;       /* 0x48/0x68: Reserved field two      */
#ifdef _WRS_WIND_VARS_ARCH
    /*
     * _WRS_WIND_VARS_ARCH macro-definition can be used for specifying
     * architecture an specific fields for WIND_VARS.
     */
    _WRS_WIND_VARS_ARCH;	       /* 0x4c/0x70: architecture specific   */
#endif /* _WRS_WIND_VARS_ARCH */
    } _WIND_VARS _WRS_DATA_ALIGN_BYTES (_WRS_WIND_VARS_ALIGN);

/*
 * Wrapper structure to force the structure alignment when used in
 * an array.
 */

typedef struct windVars
    {
    _WIND_VARS vars;
    } WIND_VARS;

#ifndef _WRS_VX_KERNEL_VARS_SECTION_ATTR
#define _WRS_VX_KERNEL_VARS_SECTION_ATTR
#endif


/* reschedule mode bit mask */

#define WIND_NO_RESCHEDULE            0x0
#define WIND_NORMAL_RESCHEDULE        0x1
#define WIND_RR_RESCHEDULE            0x2

/* variable declaration */

extern WIND_VARS _WRS_VX_KERNEL_VARS_SECTION_ATTR vxKernelVars[];

#else	/* _WRS_CONFIG_SMP */

/* cpuid arg is ignored */

#define _WRS_KERNEL_CPU_GLOBAL_GET(ignored, glob)       (glob)
#define _WRS_KERNEL_CPU_GLOBAL_SET(ignored, glob, var)	(glob = var)
#define _WRS_KERNEL_GLOBAL_ACCESS(glob)	        	(glob)
#define _WRS_KERNEL_LOCKED_GLOBAL_SET(glob, var)	glob = var
#define _WRS_KERNEL_LOCKED_GLOBAL_GET(glob, var)	var = glob

#define IS_KERNEL_IDLE()	(kernelIsIdle)

/* variable declaration */

extern BOOL	kernelIsIdle;		/* boolean reflecting idle state */

#endif	/* _WRS_CONFIG_SMP */

extern void (*_func_windTickAnnounceHook)(TASK_ID);

/*
 * The following four MACROs are used to lower task's normal priority.
 * They are used in windPrioNormalSet() and windPrioritySet(), and they
 * are also used to support user side POSIX thread with SCHED_SPOARDIC policy.
 */

#define WIND_CHECK_LOWER_PRIORITY(pTcb, priority) \
	((pTcb->priInheritCnt == 0) && (pTcb->priority < priority))

#define WIND_GET_LOWER_PRIORITY(pTcb, priority) \
     do						\
        {					\
        if (pTcb->priNormal != pTcb->priDrop)	\
            priority = pTcb->priDrop;		\
	} while ((0))

/*
 * The following macros modify either the priDrop or priNormal fields of
 * the TCB.  For SMP systems these must be atomic operations to allow
 * a task to view its own values outside of the kernel.
 */

#ifndef _WRS_CONFIG_SMP

#define WIND_SET_RUNNING_PRIORITY(pTcb, priority)	\
     do 						\
        {						\
	pTcb->priority = priority; 			\
	} while ((0))

#define WIND_SET_NORMAL_PRIORITY(pTcb, priNormal) 			\
     do									\
	{								\
	if ((priNormal < pTcb->priDrop) ||				\
            (pTcb->priMutexCnt == pTcb->priInheritCnt))			\
            {                  /* Raise or lower <priDrop> */		\
            pTcb->priDrop = priNormal;					\
            }								\
    	pTcb->priNormal = priNormal; /* Update normal priority */ 	\
	} while ((0))
#else /* _WRS_CONFIG_SMP */
#define WIND_SET_RUNNING_PRIORITY(pTcb, priority)		\
     do 							\
       {							\
       vxAtomic32Set_inline ((atomic32_t *) &pTcb->priority,	\
			     (atomic32Val_t) priority);		\
       } while ((0))

#define WIND_SET_NORMAL_PRIORITY(pTcb, priNormal) 			\
     do									\
	{								\
	if ((priNormal < pTcb->priDrop) ||				\
            (pTcb->priMutexCnt == pTcb->priInheritCnt))			\
            {  /* Raise or lower <priDrop> */				\
	    vxAtomic32Set_inline ((atomic32_t *) &pTcb->priDrop,	\
                                  (atomic32Val_t) priNormal);		\
            }								\
	/* Update normal priority */					\
	vxAtomic32Set_inline ((atomic32_t *) &pTcb->priNormal,		\
			      (atomic32Val_t) priNormal); 		\
	} while ((0))
#endif /* _WRS_CONFIG_SMP */

/*
 * This really ought to be in edrLib.h, but the temporary implementation
 * (which overloads INTERRUPT instead of creating a new class of handler
 * within ED&R) needs _WRS_KERNEL_GLOBAL_ACCESS() to get at intCnt.
 *
 * EDR_SYSTEM_FATAL_INJECT is for errors which by default require a
 * reboot, but arise when the system might not be in interrupt context.
 * In this implementation, interrupts must already be locked on the
 * local CPU; this restriction might be removed in the future.
 */

#define	EDR_SYSTEM_FATAL_INJECT(intInfo, regs, excinfo, pc, reason)	 \
    do									 \
	{								 \
	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)++;				 \
	EDR_INTERRUPT_FATAL_INJECT (intInfo, regs, excinfo, pc, reason); \
	_WRS_KERNEL_GLOBAL_ACCESS (intCnt)--;				 \
	} while ((0))

/* function declarations */

extern STATUS	windDelete		(WIND_TCB * pTcb);
extern void	windSuspend		(WIND_TCB * pTcb);
extern void	windResume		(WIND_TCB * pTcb);
extern void	windStop		(WIND_TCB * pTcb);
extern void	windCont		(WIND_TCB * pTcb);
extern void	windStopClear		(WIND_TCB * pTcb);
extern void	windHold		(WIND_TCB * pTcb);
extern void	windRelease		(WIND_TCB * pTcb);
extern void	windPriNormalSet	(WIND_TCB * pTcb, UINT priNormal);
extern void	windPrioritySet		(WIND_TCB * pTcb, UINT priority);
extern void	windSemDelete		(SEM_ID semId);
extern void	windTickAnnounce	(void);
extern void     windTickAnnounceN	(_Vx_ticks_t nTicks);
extern _Vx_ticks_t windTickWaitGet	(void);
extern STATUS	windDelay		(_Vx_ticks_t timeout);
extern STATUS	windUndelay		(WIND_TCB * pTcb);
extern STATUS	windWdStart		(WDOG * wdId, _Vx_ticks_t timeout);
extern void	windWdCancel		(WDOG * wdId);
extern void	windPendQGet		(Q_HEAD * pQHead);
extern void	windReadyQPut		(WIND_TCB * pTcb);
extern void	windReadyQRemove	(Q_HEAD * pQHead, _Vx_ticks_t timeout);
extern void	windPendQFlush		(Q_HEAD * pQHead);
extern STATUS	windPendQPut		(Q_HEAD * pQHead, _Vx_ticks_t timeout);
extern STATUS	windPendQRemove		(WIND_TCB * pTcb);
extern STATUS	windRotate		(void * pArg, int priority);
extern void	windPendQTerminate	(Q_HEAD * pQHead);
extern STATUS	windExit		(void);
extern void	windIntStackSet		(char * pBotStack);
extern void *   windNullReturn		(void);

extern void	vxTaskEntry		(void);

/*
 * These cannot be declared with a void argument list as the routines vary by
 * architecture
 */

extern void	intEnt			();
extern void	intExit			();

#ifdef _WRS_CONFIG_SMP
extern void    windClientStop           (WIND_TCB * pTcb, UINT clientId, 
					 UINT * pClientCnt);
extern void    windClientCont           (WIND_TCB * pTcb, UINT clientId, 
					 UINT * pClientCnt);
extern void    windTaskStateChange      (WIND_TCB * pTcb, int state);
extern STATUS  windCpcTaskStateChange	(void * pParam, size_t size);
extern void    windRescheduleNotify	(void);
extern void    windPendQCheckGet	(Q_HEAD * pQHead);

/******************************************************************************
*
* windStateRequestService - service a requested state change
*
* Service a task state change request.
*
* RETURNS: void
*
* ERRNO:  N/A
*
* \NOMANUAL
*/

_WRS_INLINE void windStateRequestService
    (
    FAST WIND_TCB * pTcb
    )
    {
    if (pTcb->windSmpInfo.stateRequest & WIND_SUSPEND)
	{
	windSuspend (pTcb);
	pTcb->windSmpInfo.stateRequest &= ~WIND_SUSPEND;
	}

    if (pTcb->windSmpInfo.stateRequest & WIND_STOP)
	{
	/*
	 * NOTE:
	 *
	 * If stoppage was requested while the caller was locked then
	 * the client ID and count (if specified) was updated by the 
	 * CPC handler.  Because of this the WIND_STOP_CLIENT_NONE is
	 * specified here. 
	 */

	windClientStop (pTcb, WIND_STOP_CLIENT_NONE, NULL);

	pTcb->windSmpInfo.stateRequest &= ~WIND_STOP;
	}
    }
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#else /* _ASMLANGUAGE */

/* macros for use in assembly files  */

#ifndef _WRS_ASM_EXTERN_KERNEL_GLOBALS

#ifdef	_WRS_CONFIG_SMP
#define _WRS_ASM_EXTERN_KERNEL_GLOBALS		  \
        .extern vxKernelVars
#else
#define _WRS_ASM_EXTERN_KERNEL_GLOBALS		  \
	.extern taskIdCurrent			; \
	.extern kernelIsIdle			; \
	.extern intCnt				; \
	.extern vxIntStackBase			; \
	.extern vxIntStackEnd
#endif	/* _WRS_CONFIG_SMP */

#endif /* _WRS_ASM_EXTERN_KERNEL_GLOBALS */

/*
 * assembly offsets - these must be in an ASM section due to a circular
 * dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#ifdef	_WRS_CONFIG_SMP

#include <private/offsetMacrosP.h>

#define _WRS_WIND_VARS_OFFSET_taskIdCurrent				\
					_WIND_VARS_cpu_taskIdCurrent_OFFSET
#define _WRS_WIND_VARS_OFFSET_isrIdCurrent				\
					_WIND_VARS_cpu_isrIdCurrent_OFFSET
#define _WRS_WIND_VARS_OFFSET_errno					\
					_WIND_VARS_cpu_errno_OFFSET
#define _WRS_WIND_VARS_OFFSET_intCnt					\
					_WIND_VARS_cpu_intCnt_OFFSET
#define _WRS_WIND_VARS_OFFSET_vxIntStackBase				\
					_WIND_VARS_cpu_vxIntStackBase_OFFSET
#define _WRS_WIND_VARS_OFFSET_vxIntStackEnd				\
					_WIND_VARS_cpu_vxIntStackEnd_OFFSET
#define _WRS_WIND_VARS_OFFSET_workQIx					\
					_WIND_VARS_cpu_workQIx_OFFSET

#define _WRS_WIND_VARS_OFFSET_workQIsEmpty				\
					 _WIND_VARS_cpu_workQIsEmpty_OFFSET
#define _WRS_WIND_VARS_OFFSET_idleTaskId				\
					_WIND_VARS_cpu_idleTaskId_OFFSET
#define _WRS_WIND_VARS_OFFSET_reschedMode				\
					_WIND_VARS_cpu_reschedMode_OFFSET
#define _WRS_WIND_VARS_OFFSET_my_tkt	       				\
					_WIND_VARS_cpu_my_tkt_OFFSET
#define _WRS_WIND_VARS_OFFSET_archVars					\
					_WIND_VARS_cpu_archVars_OFFSET


#endif /* _WRS_CONFIG_SMP */

#endif /* _ASMLANGUAGE */

#endif /* __INCwindLibPh */
