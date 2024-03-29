/* taskLibP.h - private task library interface header */

/*
 * Copyright (c) 1992-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05e,18apr13,pad  Updated taskDestroy()'s and taskStateChange()'s prototypes
                 (part of fix for WIND00402989).
05d,19oct12,cww  updated type of task create and delete hooks
05c,24jul12,pcs  Update  the logic of task lock count decrement to plug a hole
                 where a taskCpuLock being pre-empted by an interrupt was
                 causing the scheduler to misbehave. WIND00358456.
05b,27jan11,wzc  Record task unlock event before TASK_LOCK_DEC.(WIND00263621)
05a,08jan11,gls  made taskUnsafeInternal() available in UP (WIND00139322)
04z,10aug10,gls  added WIND_STOP client ID support (WIND00210700)
04y,21jun10,gls  added RTP force suspend (WIND00216710)
04x,12aug10,cww  Use dynamically generated offsets in offset macros
04w,27jul10,jpb  Updated offsets.
04v,16jun10,pcs  Change the data type of timeout from an int to _Vx_ticks_t
04x,03jun10,elp  updated 64 bits simulators for OBJ_CORE size.
04w,18jun10,scm  WIND00213159 adjust offset for pDbgInfo...
04v,15jun10,vhe  Improve lock level tracking for SV (WIND00209730)
04u,02jun10,gls  fixed TASK_LOCK_DEC() for UP (WIND00215275)
04t,24may10,gls  made taskCpuUnlockTask_inline() SMP only
04s,21may10,gls  taskCpuUnlock optimization for SMP
04s,27may10,pad  Moved closing brace of 'extern C' statement for appropriate
                 pairing.
04r,27apr10,cww  64-bit SMP update
04q,20apr10,kk   add VX_TASK_PRIO_SYSTEM_MAX/MIN macros
04q,08apr10,jpb  Added func binding prototypes.
04p,30mar10,pad  Moved declaration of extern C block for C++ after the
                 inclusion of header files.
04p,08mar10,elp  added simulator 64bits support.
04p,12feb10,gls  modified size of OBJ_CORE
04o,08jan10,jpb  Added taskCreateWithGuard declaration.
04n,24aug09,gls  moved tickNode before qNode in TCB (WIND00112476)
04m,28jul09,jpb  Removed unneeded addition of TASK_SAFE_INC_VALUE from
                 TASK_SAFE_INC macro.
04l,17apr09,gls  made taskCpuUnlockInternal() SMP only
04k,01apr09,gls  modifed safeCnt usage for UP
04p,29apr09,zl   updated taskRegsShowOutput() arguments
04o,25mar09,jb   Adjust x86_64 offsets to reflect removal of pad
04n,24mar09,jb   Fix incorrect offsets
04m,24mar09,jb   Restoring WIND_TCB_CTXSET
04l,11mar09,zl   Changed to fully qualified user routine for taskEach()
                 and taskBpHookSet(), fully qualified task hook routines.
                 Removed taskListCount().
04k,27feb09,zl   changed regset offset for x86_64
04j,03feb09,pcs  Updated to add support for the LP64 data model.
04k,21jan09,jb   Adding 64-bit support
04j,27oct08,jpb  Added declaration of taskListCount.
04i,04sep08,jpb  Renamed VSB header file
04h,31aug08,nld  Added TASK_DELAY_INFO structure
04g,15aug08,jpb  Added declaration of taskEach.
04f,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
04e,10jun08,to   use vxAtomic[Get|Set]_inline()
                 define _WRS_TASK_ID_CURRENT_GET()
04d,03jun08,to   moved back taskIdCurrent to taskLib.h for UP
                 rename taskCtxIdSelf() to MY_CTX_ID()
04c,13mar08,to   added taskCtxIdSelf() inline function
04b,10mar08,to   make sure taskIdCurrent stays global variable for UP
04a,13feb08,gls  modified safeCnt usage for SMP
03z,21aug07,lei  Added taskUnsafeInternal().
03y,13aug07,dlk  Added taskCpuUnlockInternal().
03x,30may07,tcr  prevent recursion with rtSpinlock and instrumented taskLock
03w,27jun07,cjj  fixed WIND_TCB_REGS definition for Coldfire.
03v,19jun07,gls  adjusted offsets for MSGQ_TCB size change  (Defect #00096894)
03u,18jun07,lei  updated WIND_TCB_REGS.
03t,16apr07,kk   renamed taskDbgUnlock(), moved taskIdCurrent variable here.
03s,05mar07,lei  added taskCpuIndexGet API for SMP
03r,10jan07,jmg  Added globalNoStackFill variable (Req. WIND00083667)
03q,18nov06,gls  added WIND_STATE_CHANGE
                 added taskStateChange()
03p,09nov06,scm  adjust definitions for IA32 embedding CTX_SET structure into
                 WIND_TXB...
03o,19jul06,lei  updated WIND_TCB_REGS; removed "CPU_FAMILY==I960"
03n,17jul06,zl   removed taskIdTable[] declaration.
03m,12nov05,jln  Collapse the PRI_INHERIT_DATA to WIND_TCB
03l,28nov05,rec  WIND_TCB_USP has wrong offset
03k,26oct05,j_b  update WIND_TCB_REGS for COLDFIRE
03j,01jul05,rec  review comments
03i,28apr05,rec  base6 update - add format word
03h,30jul05,pad  Removed _exit() prototype (SPR 110038).
03g,15aug05,yvp  Moved KERNEL_TASK_EXC_STACK_SIZE to sys/taskdefs.h
03f,09aug05,mmi  Update WIND_TCB_REGS offset
03e,15jul05,yvp  Added KERNEL_TASK_EXC_STACK_SIZE.
03d,07jun05,yvp  Updated copyright. #include now with angle-brackets.
03c,23mar05,yvp  Added extern declarations for task(Ker/Usr)ExcStackSize.
03b,18mar05,yvp  Added prototype for taskPriInheritDataInit.
03a,14mar05,yvp  Added task(Under/Over)flowSize
03a,25may05,md   added SMP support
02z,09mar05,kk   updated the offsets due to addition in WIND_TCB
02y,25sep04,dcc  updated TCB offsets.
02x,28sep04,fr   removed vTaskOpen prototype (SPR 101349)
02w,13sep04,md   added taskStopForce()
02v,16sep04,dbt  Added taskDbgUnlock() prototype (SPR #101075).
02u,30apr04,dcc  added WIND_TCB_UTCB offset.
02t,30apr04,yvp  Added WIND_TCB_P_K_STK_END.
02s,20apr04,hya  added taskReset prototype.
02r,22mar04,dcc  added vTaskOpen() prototype.
02q,23feb04,dcc  adjusted WIND_TCB offsets.
02p,18feb04,aeg  deprecated taskCreat().
02o,27nov03,aeg  added vTaskOpen() function prototype.
02n,19nov03,kk   added taskInitialize
02m,31oct03,dcc  adjusted WIND_TCB offsets as a result of OBJ_CORE expansion.
02l,30pcm03,pcm  implemented changes from code review
02k,20oct03,pcm  cleaned up WIND_TCB_xxx macros
02j,17sep03,kk   renamed WIND_TCB_P_K_STK_PTR to WIND_TCB_P_EXC_STK_BASE
02i,10sep03,dcc  moved taskCreate() prototype to taskLibCommon.h
02h,04aug03,elg  Add support for new task status: define WIND_STOP.
02g,24jul03,kam  updated WIND_TCB_REGS for SIMLINUX and SIMNT
02f,23jul03,kam  updated WIND_TCB_REGS for SIMSPARCSOLARIS
02e,07may03,pes  PAL conditional compilation cleanup, phase 2. Moved
                 ARM-specific #defines to arch/arm/regsArm.h.
02d,22jul03,pad  Moved _exit declaration here to solve coupling issues.
02c,18jul03,kk   change WIND_TCB_P_K_STK_PTR macro to point pKStackBase &
                 pKStackPtr
02b,10jul03,kk   added WIND_TCB_P_K_STK_PTR & WIND_TCB_RTP_ID macro
02a,17apr03,dbt  Added WIND_TCB_REGS definition for Linux & Windows VxSim.
01z,25mar03,dbt  Added WIND_TCB_REGS definition for Solaris VxSim.
01y,10jul03,ymz  fixed WIND_TCB_ERRNO comment.
01x,01jul03,ymz  updated MIPS register offset for 8-byte alignment.
01w,01jul03,rec  code review comments.
01v,02jun03,rec  Power Management - added ARM WIND_TCB_R5 WIND_TCB_SP.
01u,28mar03,ymz  does not assume qNode is the first element in WIND_TCB,
                 added WIND_TCB_QNODE.
01t,16jan02,to   added WIND_TCB_FPSTATUS for ARM.
01s,09nov01,dee  added coldfire portions from T2.1.0
01r,04oct01,yvp  fixed SPR69306: changed WIND_TCB_REGS to 0x130 for PPC.
01q,19sep01,aeg  updated WIND_TCB* macros to match taskLib.h v04j changes;
                 deleted Am29K family support.
01p,04sep01,hdn  moved I80X86 macros to regsI86.h.
01o,28feb00,frf  added SH support for T2.
01n,23jul98,mem  added pTaskLastDspTcb.
01m,23apr97,hk   added SH support.
01l,28nov96,cdp  added ARM support.
                 added WIND_TCB_PSTACKBASE.
01k,19mar95,dvs  removed tron references.
01j,26may94,yao  added PPC support.
01i,28jul94,dvs  added extern of pTaskLastFpTcb. (SPR #3033).
01h,12nov93,hdn  added support for I80X86.
01g,02dec93,pme  added Am29K family support.
01f,03aug93,jwt  abstracted common WIND_TCB_XXX definitions; copyright.
01e,22sep92,rrr  added support for c++.
01d,23aug92,jcf  added extern of taskBpHook.
01c,28jul92,jcf  changed offsets to match WIND_TCB.
01b,07jul92,ajm  removed external defines of taskSwapMaskClear/taskSwapMaskSet
01a,04jul92,jcf  written by extracting from taskLib.h v02x.
*/

#ifndef __INCtaskLibPh
#define __INCtaskLibPh

/* task status values */

#define WIND_READY         0x00    /* ready to run */
#define WIND_SUSPEND       0x01    /* explicitly suspended */
#define WIND_PEND          0x02    /* pending on semaphore */
#define WIND_DELAY         0x04    /* task delay (or timeout) */
#define WIND_DEAD          0x08    /* dead task */
#define WIND_STOP          0x10    /* stopped by the debugger */
#define WIND_STATE_CHANGE  0x20    /* currently changing state */

/* WIND_STOP client IDs */

#define WIND_STOP_CLIENT_NONE           0x0
#define WIND_STOP_CLIENT_DEBUGGER       0x1
#define WIND_STOP_CLIENT_SIGNAL         0x2

/* 
 * System max/min priority levels supported by VxWorks. 
 * These macros complements the following macros in taskLib.h:
 *
 * VX_TASK_PRIORITY_MAX 255
 * VX_TASK_PRIORITY_MIN 0
 */

#define VX_TASK_PRIO_SYSTEM_MAX   287  /* 256 to 287 reserved for VxWorks */
#define VX_TASK_PRIO_SYSTEM_MIN   0

/* idle task priority, should be the lowest priority for VxWorks */

#define VX_IDLE_TASK_PRIORITY   VX_TASK_PRIO_SYSTEM_MAX 

/* Option bits for taskDestroy() and taskStateChange()'s options parameter */

#define FORCED_OP                0x1     /* Force operation even if the task is
                                            protected - this option takes
                                            precedence! */
#define ABORT_STOPPED_DEL_SAFE   0x2     /* Abort operation if task is stopped
                                            while delete safe */

#ifndef _ASMLANGUAGE
#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/vxPortableP.h>
#include <private/windLibP.h>
#include <taskLib.h>
#include <classLib.h>
#include <objLib.h>
#include <stdarg.h>
#include <stdio.h>
#include <hookLib.h>
#include <private/hookTblLibP.h>

#ifdef _WRS_CONFIG_SMP
#include <vxAtomicLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct delayInfo
    {
    BOOL isDelayed;           /* TRUE if the task is in delayed state */
    _Vx_ticks_t delayTick;    /* delay tick for the task */
    } TASK_DELAY_INFO;

typedef void (*TASK_CREATE_HOOK) (WIND_TCB * pTcb);
typedef void (*TASK_DELETE_HOOK) (WIND_TCB * pTcb);
typedef void (*TASK_SWITCH_HOOK) (WIND_TCB * pOldTcb, WIND_TCB * pNewTcb);
typedef void (*TASK_SWAP_HOOK) (WIND_TCB * pOldTcb, WIND_TCB * pNewTcb);

/* variable declarations */

extern REG_INDEX taskRegName [];
extern void (*taskBpHook) (WIND_TCB * pTcb);

extern HOOK_TBL taskCreateHooks;
extern HOOK_TBL taskDeleteHooks;

extern TASK_SWITCH_HOOK  taskSwitchTable [];
extern TASK_SWAP_HOOK    taskSwapTable [];

extern STATUS (*_func_taskCreateHookAdd) (TASK_CREATE_HOOK createHook);
extern STATUS (*_func_taskDeleteHookAdd) (TASK_DELETE_HOOK deleteHook);

extern int      taskSwapReference [];
extern WIND_TCB * pTaskLastFpTcb;
extern WIND_TCB * pTaskLastDspTcb;
extern size_t  taskOverflowSize;   /* overflow protection size */
extern size_t  taskUnderflowSize;  /* underflow protection size */
extern size_t  taskUsrExcStackSize;    /* default exception stack size */
extern size_t  taskKerExcStackSize;    /* kernel task exc stack size */
extern BOOL globalNoStackFill;	/* VX_GLOBAL_NO_STACK_FILL build parameter */

/*
 * Global sem that protects adding/removing from task class list when 
 * class list configuration is removed
 */

#ifndef _WRS_CONFIG_OBJECT_CLASS_LIST
extern SEMAPHORE taskClassListSem;
#endif

/*
 * The following are lockCnt manipulation macros for both UP and SMP systems.
 *
 * For UP systems the semantics of lockCnt are not changed.  It is a simple
 * count modified under kernel or interrupt lock.
 *
 * For SMP systems the lowest bit of lockCnt will now be used to denote a
 * reschedule may be required.  The lockCnt field must only be accessed with 
 * atomic operators.
 */

#ifndef _WRS_CONFIG_SMP

#define TASK_LOCK_SCHED 0

#define TASK_LOCK_INC(pTcb) (pTcb->lockCnt++)
#define TASK_LOCK_DEC(pTcb) (--pTcb->lockCnt)
#define TASK_LOCK_GET(pTcb) (pTcb->lockCnt)

#else /* _WRS_CONFIG_SMP */

#ifndef TASK_LOCK_INC_VALUE
#define TASK_LOCK_INC_VALUE 2
#endif

#define TASK_LOCK_SCHED 1

#define TASK_LOCK_INC(pTcb) (vxAtomic32Add_inline((atomic32_t *)             \
                             &pTcb->lockCnt, TASK_LOCK_INC_VALUE))

#define TASK_LOCK_DEC(pTcb) (vxAtomic32Sub_inline((atomic32_t *)             \
                             &pTcb->lockCnt, TASK_LOCK_INC_VALUE) -          \
                             TASK_LOCK_INC_VALUE)

#define TASK_LOCK_GET(pTcb) (vxAtomic32Get_inline((atomic32_t *)             \
                             &pTcb->lockCnt) >> 1)

#define TASK_CPU_LOCK_SCHED_SET(pTcb) (vxAtomic32Or_inline((atomic32_t *)    \
                                       &pTcb->lockCnt, TASK_LOCK_SCHED))

#define TASK_CPU_LOCK_SCHED_CLEAR(pTcb) (vxAtomic32And_inline((atomic32_t *) \
                                         &pTcb->lockCnt, ~TASK_LOCK_SCHED))

#define TASK_CPU_LOCK_SCHED_CHECK(pTcb) (vxAtomic32Get_inline((atomic32_t *) \
                                         &pTcb->lockCnt) == TASK_LOCK_SCHED)

#endif /* _WRS_CONFIG_SMP */

/*
 * The following are safeCnt manipulation macros for both UP and SMP systems.
 *
 * For UP systems the semantics of safeCnt are not changed.  It is a simple
 * count modified under kernel or interrupt lock.
 *
 * For SMP systems the lowest bit of safeCnt will now be used to denote a
 * task has pended on the safety queue.  The safeCnt field must only be
 * accessed with atomic operators.
 */

#ifndef _WRS_CONFIG_SMP

#define TASK_SAFE_PEND 0

#define TASK_SAFE_INC(pTcb) (pTcb->safeCnt++)

_WRS_INLINE int TASK_SAFE_DEC (WIND_TCB * pTcb)
    {
    /*
     * TASK_SAFE_DEC (pTcb) is equal to TASK_SAFE_PEND when the safe count
     * of <pTcb> reaches zero and a task has pended on the safety queue.  This
     * is used to determine if it is necessary to enter the kernel and
     * flush the safety queue after decrementing safeCnt.
     *
     * For UP it is sufficient to check the safetyQHead without any protection
     * as there are no conditions under which a task could add itself to 
     * that queue after <safeCnt> reaches 0.
     *
     * If <safeCnt> is 0, any subsequent attempts to delete (or change the
     * state of) the task will succeed unless <lockCnt> is greater than 0.
     * If <lockCnt> is greater than 0 no other task can run while this code
     * is executing.
     * 
     * NOTE:  This interface is not ideal, but is the result of previous
     * efforts to avoid changing UP safeCnt code in any way.  It may be
     * a good idea to modify TASK_SAFE_DEC() simply return a boolean value
     * rather than an int to be compared to TASK_SAFE_PEND.
     */

    if (((--pTcb->safeCnt) == 0) &&
	(Q_FIRST (&pTcb->safetyQHead) != NULL))
	{    
	return (TASK_SAFE_PEND);
	}
    
    /* return a value other than TASK_SAFE_PEND */

    return (-1);
    }

#define TASK_SAFE_GET(pTcb) (pTcb->safeCnt)
#define TASK_SAFE_SET(pTcb, value) (pTcb->safeCnt = value)

#define TASK_IS_SAFE(pTcb) (pTcb->safeCnt > TASK_SAFE_PEND)

_WRS_INLINE BOOL TASK_SAFE_UNPEND_NEEDED (WIND_TCB * pTcb)
    {
    if ((pTcb->safeCnt == 0) && (Q_FIRST (&pTcb->safetyQHead) != NULL))
	{
	return (TRUE);
	}

    return (FALSE);
    }

#define TASK_SAFE_PEND_SET(pTcb)
#define TASK_SAFE_PEND_CLEAR(pTcb)

#define	_WRS_TASK_ID_CURRENT_GET(pTcb)	pTcb = taskIdCurrent

#else	/* _WRS_CONFIG_SMP */

#ifndef TASK_SAFE_INC_VALUE
#define TASK_SAFE_INC_VALUE 2
#endif

#define TASK_SAFE_INC(pTcb) (vxAtomic32Add((atomic32_t *) &pTcb->safeCnt,    \
                             TASK_SAFE_INC_VALUE))

#define TASK_SAFE_DEC(pTcb) (vxAtomic32Sub((atomic32_t *) &pTcb->safeCnt,    \
                             TASK_SAFE_INC_VALUE) - TASK_SAFE_INC_VALUE)

#define TASK_SAFE_GET(pTcb)						     \
	(vxAtomic32Get_inline ((atomic32_t *) &pTcb->safeCnt) >> 1)

#define TASK_SAFE_SET(pTcb, value)					     \
	(vxAtomic32Set_inline ((atomic32_t *) &pTcb->safeCnt, value))

#define TASK_SAFE_PEND 1

#define TASK_IS_SAFE(pTcb)						     \
	(vxAtomic32Get_inline ((atomic32_t *) &pTcb->safeCnt) >		     \
		(atomic32Val_t) TASK_SAFE_PEND)

#define TASK_SAFE_UNPEND_NEEDED(pTcb)					     \
        (vxAtomic32Get_inline ((atomic32_t *) &pTcb->safeCnt) == TASK_SAFE_PEND)

/*
 * Modification of the PEND bit must only occur after entering the kernel.
 * Thus, the following macros should only be called while in the kernel.
 */

#define TASK_SAFE_PEND_SET(pTcb)					     \
	(vxAtomic32Or ((atomic32_t *) &pTcb->safeCnt, TASK_SAFE_PEND))
#define TASK_SAFE_PEND_CLEAR(pTcb)					     \
	(vxAtomic32And ((atomic32_t *) &pTcb->safeCnt, ~TASK_SAFE_PEND))

#ifdef	_WRS_PORTABLE_taskIdSelf
#define	_WRS_TASK_ID_CURRENT_GET(pTcb)					     \
		_WRS_KERNEL_LOCKED_GLOBAL_GET (taskIdCurrent, pTcb)
#else	/* _WRS_PORTABLE_taskIdSelf */
#define	_WRS_TASK_ID_CURRENT_GET(pTcb)	pTcb = (WIND_TCB *) taskIdSelf()
#endif	/* _WRS_PORTABLE_taskIdSelf */

#endif	/* _WRS_CONFIG_SMP */

/* function declarations */

extern STATUS	taskInitialize		(WIND_TCB * pTcb, char * name,
					 int priority, int options,
					 char * pStackBase, size_t stackSize,
					 char * pExcStackBase,
					 size_t excStackSize, FUNCPTR entry, 
                               		 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                               		 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                               		 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
                               		 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
                               		 _Vx_usr_arg_t arg9,
					 _Vx_usr_arg_t arg10); 
extern TASK_ID	taskCreateWithGuard	(char * name, int priority, int options,
                                    	 size_t stackSize, size_t  guardSize, 
                                    	 FUNCPTR entryPt, _Vx_usr_arg_t arg1, 
                                    	 _Vx_usr_arg_t arg2, _Vx_usr_arg_t arg3,
                                    	 _Vx_usr_arg_t arg4, _Vx_usr_arg_t arg5,
                                    	 _Vx_usr_arg_t arg6, _Vx_usr_arg_t arg7,
                                    	 _Vx_usr_arg_t arg8, _Vx_usr_arg_t arg9,
                                    	 _Vx_usr_arg_t arg10);
extern TASK_ID	taskCreat		(char *name, int priority, int options, 
                               		 size_t stackSize, FUNCPTR entryPt, 
                               		 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                              		 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                              		 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
                              		 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
                              		 _Vx_usr_arg_t arg9,
					 _Vx_usr_arg_t arg10)
_WRS_DEPRECATED ("please use taskCreate instead");

extern STATUS   taskTerminate		(TASK_ID tid);
extern STATUS   taskDestroy		(TASK_ID tid, BOOL dealloc, 
                                         _Vx_ticks_t timeout,
                 			 UINT32 options);
extern STATUS   taskUndelay		(TASK_ID tid);
extern void 	taskBpHookSet		(void (*bpHook) (WIND_TCB * pTcb));
extern void	taskIdListSort		(TASK_ID idList[], int nTasks);
extern STATUS   taskStop		(TASK_ID tid);
extern STATUS   taskStopForce		(TASK_ID tid);
extern STATUS   taskCont		(TASK_ID tid);
extern BOOL     taskIsStopped		(TASK_ID tid);
extern STATUS   taskStateChange		(TASK_ID tid, int state, 
                                         _Vx_ticks_t timeout, 
                 			 UINT32 options);
extern STATUS   _taskSuspend            (TASK_ID tid, BOOL rtpForce);
extern STATUS   taskReset		(TASK_ID tid);
extern STATUS   taskCpuUnlockNoResched	(void);
extern STATUS   taskPriInheritDataInit	(TASK_ID tid);
extern TASK_ID  taskEach		(BOOL (*routine)(TASK_ID tid,
							 void * pArg), 
			  		 void * pArg, BOOL objPublic);
extern void	taskRegsShowOutput	(REG_SET * pRegs,
				    	 OPRINTF_OUTPUT_FUNCPTR prtFunc,
				    	 _Vx_usr_arg_t pArg);

extern void   taskUnsafeInternal	(WIND_TCB * pTcbCurrent);

#ifdef	_WRS_CONFIG_SMP
extern STATUS taskClientStopForce       (TASK_ID tid, UINT clientId, 
					 UINT * pClientCnt);
extern STATUS taskClientCont            (TASK_ID tid, UINT clientId, 
					 UINT * pClientCnt);
extern STATUS taskCpuIndexGet	        (TASK_ID tid, int * pCpuIndex);
extern void   taskCpuUnlockInternal	(WIND_TCB * pTcb);

/*******************************************************************************
*
* taskCpuUnlockTask_inline - unlock a specified task
*
* This internal routine will decrement the specified task's lockCnt, calling
* the taskCpuLockInternal() routine to check for a scheduling event if
* necessary.
*
* If the <checkError> argument is TRUE and the task's lockCnt is not greater
* than zero then no decrement will occur.  
*
* This routine exists only for SMP.
*
* RETURNS: OK or ERROR if error checking specified and lockCnt is not greater
*          than zero.
*
* NOMANUAL
*/

_WRS_INLINE STATUS taskCpuUnlockTask_inline
    (
    WIND_TCB * pTcb,
    BOOL       checkError
    )
    {

    if ((checkError == FALSE) || (TASK_LOCK_GET (pTcb) > 0))
        {
        atomic32_t lockCnt;

#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
        /* system viewer - context switch level event logging */
        if (TASK_LOCK_GET (pTcb) == 1) 
            EVT_CTX_0 (EVENT_TASKUNLOCK_ZERO);
        else     
            EVT_CTX_0 (EVENT_TASKUNLOCK_NONZERO);
#endif /* _WRS_CONFIG_SV_INSTRUMENTATION */

        /*
         * Read the task lock count and call taskCpuUnlockInternal() if 
         * 1. TASK_LOCK_SCHED is set(scheduling is requested at the last
         *    taskCpuLock) and it is the last taskCpuUnlock being executed.
         *    Note: In this case the decrement of the task lock count is done
         *          in taskCpuUnlockInternal() with the kernel lock taken. 
         *          This is required to close the window between the time the 
         *          lock count is decremented and the scheduler is called where
         *          an interrupt can come and messup the scheduler.
         *          (WIND00358456)
         * 2. The last taskCpuUnlock being executed and the an unpending of
         *    a task on the safety queue is requested.
         *
         */

retry:
        lockCnt = vxAtomic32Get_inline((atomic32_t *)&pTcb->lockCnt);
        if ((lockCnt == (TASK_LOCK_SCHED +  TASK_LOCK_INC_VALUE)) ||
            ((lockCnt == TASK_LOCK_INC_VALUE) && 
             TASK_SAFE_UNPEND_NEEDED (pTcb)))
            {
            taskCpuUnlockInternal (pTcb);
            }
        else
            {
            if ((vxAtomic32Cas((atomic32_t *)&pTcb->lockCnt, lockCnt, 
                             (lockCnt - TASK_LOCK_INC_VALUE))) == FALSE)
                {
                /* 
                 * The contents of lockCnt changed between the time it was read
                 * and the completion of vxAtomic32Cas.
                 * This happens if we get interrupted between the read and 
                 * update of the lock count and the TASK_LOCK_SCHED gets set.
                 * At this point the lock count has not been decremented. We
                 * need to go and retry the unlock.
                 */ 

                goto retry;
                }
            }
        return (OK);
        }
    else
        {
        return (ERROR);
        }
    }
#endif /* _WRS_CONFIG_SMP */

/* function pointers prototypes */

extern void      (*_func_exit)(int code);

/*
 * MY_CTX_ID() is now defined as an inline function to avoid calling
 * taskIdSelf() twice for SMP configuration.  It had to be moved here
 * from kernelBaseLibP.h to make sure all the declarations required
 * are done prior to the inline function definition below.
 */

_WRS_INLINE RTP_ID MY_CTX_ID (void)
    {
    WIND_TCB * tCurrent = taskIdCurrent;

    /* check for 0 is still needed for the rootTask in taskLib */

    return (tCurrent == NULL ? kernelId : tCurrent->rtpId);
    }

#ifdef __cplusplus
}
#endif

#else   /* _ASMLANGUAGE */

/*
 * architecture-independent WIND_TCB defines - these must be in an ASM section
 * due to a circular dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#include <private/offsetMacrosP.h>

#ifndef _WRS_CONFIG_LP64

#define WIND_TCB_QNODE           WIND_TCB_qNode_OFFSET
#define WIND_TCB_P_K_STK_BASE    WIND_TCB_pExcStackBase_OFFSET
#define WIND_TCB_P_K_STK_END     WIND_TCB_pExcStackEnd_OFFSET
#define WIND_TCB_PEXC_STK_START  WIND_TCB_pExcStackStart_OFFSET
#define WIND_TCB_EXC_CNT         WIND_TCB_excCnt_OFFSET
#define WIND_TCB_STATUS          WIND_TCB_status_OFFSET
#define WIND_TCB_PRIORITY        WIND_TCB_priority_OFFSET
#define WIND_TCB_PRI_NORMAL      WIND_TCB_priNormal_OFFSET
#define WIND_TCB_LOCK_CNT        WIND_TCB_lockCnt_OFFSET
#define WIND_TCB_PRI_MUTEX_CNT   WIND_TCB_priMutexCnt_OFFSET
#define WIND_TCB_PRI_INHERIT_CNT WIND_TCB_priInheritCnt_OFFSET
#define WIND_TCB_PRI_DROP        WIND_TCB_priDrop_OFFSET
#define WIND_TCB_PRI_PMUTEX      WIND_TCB_pPriMutex_OFFSET
#define WIND_TCB_RTP_ID          WIND_TCB_rtpId_OFFSET
#define WIND_TCB_UTCB            WIND_TCB_pUTcb_OFFSET
#define WIND_TCB_OPTIONS         WIND_TCB_options_OFFSET
#define WIND_TCB_SWAP_IN         WIND_TCB_swapInMask_OFFSET
#define WIND_TCB_SWAP_OUT        WIND_TCB_swapOutMask_OFFSET
#define WIND_TCB_SAFE_CNT        WIND_TCB_safeCnt_OFFSET
#define WIND_TCB_SAFETY_Q_HEAD   WIND_TCB_safetyQHead_OFFSET
#define WIND_TCB_ENTRY           WIND_TCB_entry_OFFSET
#define WIND_TCB_PSTACKBASE      WIND_TCB_pStackBase_OFFSET
#define WIND_TCB_PSTACKEND       WIND_TCB_pStackEnd_OFFSET
#define WIND_TCB_ERRNO           WIND_TCB_errorStatus_OFFSET
#define WIND_TCB_PFPCONTEXT      WIND_TCB_pCoprocTbl_OFFSET
#define WIND_TCB_PDBGINFO  	 WIND_TCB_pDbgInfo_OFFSET

#endif /* _WRS_CONFIG_LP64 */

#define	WIND_TCB_REGS		 WIND_TCB_regs_OFFSET

/* architecture-dependent WIND_TCB defines */

#if (CPU_FAMILY == MC680X0)
#define	WIND_TCB_DREGS	        WIND_TCB_REGS
#define	WIND_TCB_DREGS4		WIND_TCB_REGS + 0x00
#define	WIND_TCB_DREGS8		WIND_TCB_REGS + 0x04
#define	WIND_TCB_AREGS		WIND_TCB_REGS + 0x08
#define	WIND_TCB_AREGS4		WIND_TCB_REGS + 0x20
#define	WIND_TCB_AREGS8		WIND_TCB_REGS + 0x24
#define	WIND_TCB_SSP		WIND_TCB_REGS + 0x28
#define	WIND_TCB_FRAME1		WIND_TCB_REGS + 0x42
#define	WIND_TCB_SR		WIND_TCB_REGS + 0x42
#define	WIND_TCB_PC		WIND_TCB_REGS + 0x44
#define	WIND_TCB_FRAME2		WIND_TCB_REGS + 0x46
#define	WIND_TCB_FOROFF		WIND_TCB_REGS + 0x48
#endif	/* CPU_FAMILY==MC680X0 */

#if (CPU_FAMILY == MIPS)
#include <arch/mips/taskMipsLib.h>
#endif	/* MIPS */

#if (CPU_FAMILY == ARM)
#define WIND_TCB_FPSTATUS       WIND_TCB_fpStatus_OFFSET
#endif  /* CPU_FAMILY==ARM */

#if (CPU_FAMILY == COLDFIRE)
#define WIND_TCB_DREGS          (WIND_TCB_REGS+OFF_REG_D0)
#define WIND_TCB_DREGS4         (WIND_TCB_REGS+OFF_REG_D1)
#define WIND_TCB_DREGS8         (WIND_TCB_REGS+OFF_REG_D2)
#define WIND_TCB_AREGS          (WIND_TCB_REGS+OFF_REG_A0)
#define WIND_TCB_AREGS4         (WIND_TCB_REGS+OFF_REG_A1)
#define WIND_TCB_AREGS8         (WIND_TCB_REGS+OFF_REG_A2)
#define WIND_TCB_SSP            (WIND_TCB_REGS+OFF_REG_SP)
#define WIND_TCB_USP            (WIND_TCB_REGS+OFF_REG_USP)
#define WIND_TCB_FORMAT         (WIND_TCB_REGS+OFF_REG_FORMAT)
#define WIND_TCB_SR             (WIND_TCB_REGS+OFF_REG_SR)
#define WIND_TCB_ESF            (WIND_TCB_FORMAT)
#define WIND_TCB_PC             (WIND_TCB_REGS+OFF_REG_PC)
#endif  /* CPU_FAMILY==COLDFIRE */

#include <regs.h>

#endif	/* _ASMLANGUAGE */

#endif /* __INCtaskLibPh */
