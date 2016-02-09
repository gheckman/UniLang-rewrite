/* taskLib.h - VxWorks tasking library interface header */

/*
 * Copyright (c) 1988-2001, 2003-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08x,12dec14,h_k  removed deferredCpuSet field from WIND_SMP_INFO in LP64.
                 (US48911)
08w,04dec14,h_k  removed deferredCpuSet field from WIND_SMP_INFO and replaced
                 its usage with resreved2 field for ILP32 SMP to prevent from
                 TCB size change to keep DKM binary compatibility temporarily.
                 (VXW6-83890)
08v,25sep14,h_k  added deferredCpuSet field to WIND_SMP_INFO. (VXW6-83383)
08u,03may13,pcs  Add support for SMP-optimized memory allocator.
08t,01apr13,cww  made task create/delete hook table size configurable
                 (WIND00395617)
08s,03feb12,jpb  CQ Req WIND00139205: Added two members to the TCB struct for 
                 the RTP Wait mechanism.
08q,14jun11,jpb  Added waitPendQ to WIND_TCB, taskWait() declaration.
                 (Req: WIND00070880).
08t,25jun12,ggm  corrected comment for ARM (WIND00353423).
08s,10apr12,cww  adjust padding for extended PPC EXC_INFO
08r,28nov11,h_k  corrected comment for PPC (WIND00314509).
08q,08may11,jxu  Added pCwdInfo in WIND_TCB and task create option 
                 VX_PRIVATE_CWD to support kernel per-task CWD 
                 feature (WIND00131452).
08p,31jan11,jpb  Defect WIND00253474. Fixed type of readyQExt.
08o,14jan11,cww  Updated spare fields datatype (WIND00241209)
08n,04jan11,elp  added simulator specific structure (CQ:WIND00247541).
08m,03dec10,zl   updated header file synopsis
08l,13oct10,jpb  Updated comments for offset in WIND_TCB
08k,20aug10,gls  added WIND_STOP client ID support (WIND00210700)
08j,27aug10,cww  fixed misaligned cpuTimeInfo field
08i,13aug10,cww  updated envTblSize
08h,01jul10,jpb  Introduced new type for eventCode in WIND_TCB struct.
08g,07jul10,pcs  Update data types of struct entries taskTicks and
                 taskIncTicks from UINT to _Vx_ticks_t
08f,07jun10,jpb  Added _WRS_CONFIG_RTP conditional.
08e,25may10,gls  worked around taskLibCommon.h inclusion
08d,21may10,gls  taskCpuUnlock optimization for SMP
08c,15apr10,jpb  Added logLib.h to reduce breakage of files that use
                 _func_logMsg.
08b,30mar10,pad  Moved declaration of extern C block for C++ after the
                 inclusion of header files.
08d,24mar10,cww  Added include cpuset.h
08c,23mar10,gls  modified size of OBJ_CORE
08b,05feb10,rlp  Used a pointer to access debug information.
08a,24aug09,gls  moved tickNode before qNode in TCB (WIND00112476)
08d,29may09,cww  Use fixed size atomic operators
08c,13apr09,jb   Remove pad from 64-bit build
08b,26mar09,zl   fixed VX_TASK_INSTANTIATE() for 64-bit. Doc fixes.
08a,03feb09,pcs  Updated to add support for the LP64 data model.
08b,12feb09,zl   removed qLib.h
08a,20jan09,jb   Adding 64-bit support
07z,27aug08,jpb  Renamed VSB header file
07y,25jun08,jpb  Added include path for kernel configurations
                 options set in vsb.
07x,16jun08,zl   replaced WRS_ASM() with VX_CODE_BARRIER()
07w,03jun08,to   moved back taskIdCurrent from taskLibP.h for UP
07v,12may08,jpb  Modifications for source build.    Renamed 
                 WV_INSTRUMENTATION to _WRS_CONFIG_SV_INSTRUMENTATION,
		 _WRS_VX_SMP to _WRS_CONFIG_SMP.
07u,04apr08,mfj  Changing TASK_ID_VERIFY to call objVerify instead of the
                 macro
07t,04apr08,mfj  making IS_KERNEL_TASK dependant on _WRS_CONFIG_RTP
07s,13mar08,to   cache the taskIdCurrent value in TASK_SAFE() for SMP
07r,12mar08,zl   replaced pReadyQ with readyQExt in WIND_SMP_INFO.
07q,10mar08,to   make sure taskIdCurrent stays global variable for UP
07p,13feb08,gls  modified safeCnt usage for SMP
07o,19jun07,gls  adjusted offsets for MSGQ_TCB size change (Defect #00096894)
07n,11jun07,lei  embedded WIND_SMP_INFO into WIND_TCB; moved refMsgQId from
                 WIND_SMP_INFO to MSGQ_TCB.
07m,07jun07,jmg  Moved taskCpuAffinityGet()/Set() to taskLibCommon.h
07l,28may07,lei  added taskSchedInfoGet() API;
                 modified TASK_QNODE_TO_PSCHEDINFO to call taskSchedInfoGet()
07k,04may07,dlk  Add TASK_CPU_LOCK_TASK() for taskCpuLock() SMP optimization.
07j,25apr07,kk   rename TASK_LOCK/UNLOCK() to TASK_CPU_LOCK/UNLOCK() and moved
                 taskIdCurrent variable to taskLibP.h
07i,23apr07,jmg  Removed taskPriRangeCheck
07h,27feb07,jmg  Changed VX_TASK_PRIORITY_MAX to 255
07g,08jan07,jmg  Added taskRotate()  (Req.WIND00071010) Added
                 VX_TASK_PRIORITY_MAX and VX_TASK_PRIORITY_MIN
07g,18dec06,jmg  added pIpcomInfo to WIND_TCB
07f,18nov06,gls  added fields for SMP task state change
07e,15nov06,dbt  Added field for __thread variables support.
07d,14nov06,scm  adjust definitions for IA32 embedding CTX_SET structure into
                 WIND_TCB
07c,10nov06,lei  changed the prototype of taskCpuAffinityGet().
07b,07nov06,rlp  Removed WDB_INFO type and replaced wdbInfo structure with
                 vxdbgInfo (REQ00007655).
07a,01nov06,jln  added refMsgQId
06z,30jun06,jmg  Added definition of taskPriNormalGet () Defect # WIND00045158
07j,08aug06,pch  remove obsolete VX_MAX_SMP_CPU; renumber history from 20jun93
07i,07aug06,pes  Remove non-SMP-safe reference to taskIdCurrent in definition
		 of IS_KERNEL_TASK.
07h,20jul06,lei  Added an extra field pSmpInfo to the WIND_TCB;
		 removed "CPU_FAMILY==I960"; updated comment for offset.
07g,19jul06,scm  increase VX_MAX_SMP_CPU to 4 for IA-32...
07f,13jul06,zl   removed __taskIdCurrent().
07e,10may06,pes  Increase VX_MAX_SMP_CPU to 4 for MIPS.
07d,27dec05,yvp  Fixed typo in VX_TASK_INITIALIZE macro argument list.
		 Fixed GNU compiler warning in VX_TASK_INSTANTIATE (SPR 114784)
07c,25may05,md   added SMP support
07b,12nov05,jln  added guardSize and collapsed PRI_INHERIT_DATE to TCB
07a,09sep05,jln  added _WRS_ABSOLUTE_EXTERN(_vx_qNodeToPschedInfo)
06z,30aug05,yvp  Reworked VX_TASK macros to undo struct workaround.
06y,31aug05,jln  added TASK_QNODE_TO_PSCHEDINFO macro
06x,25aug05,kk   fix VX_TASK_INSTANTIATE macro
06w,11aug05,mmi  Change pad from int --> UINT32
06v,09aug05,mmi  Add pCpuPwrMgmtPState
06u,15aug05,yvp  Added include of sys/taskDefs.h.
06t,10aug05,yvp  Added macros VX_TASK and VX_TASK_INITIALIZE.
06s,04aug05,yvp  Added prototype for create/delete library init.
06r,02aug05,yvp  Converted while(0) to while ((0)) - suppress diab warnings.
06q,01apr05,kk   added kernelBaseLibP.h for IS_KERNEL_TASK, added some docs.
06p,04mar05,kk   added cpuTimeInfo1, cpuTimeInfo2, pSchedInfo to TCB
		 fixed apigen errors (SPR# 106451)
06o,25feb05,pcs  Modified prototype of fn. taskLibInit to accept distint stack
		 overflow and underflow sizes for both user and kernel tasks.
06n,01feb05,kk   added IS_KERNEL_TASK() (SPR# 104271)
06m,26oct04,fr   added taskOpenInit() routine (SPR 101491)
06l,04oct04,aeg  removed #ifndef _ASMLANGUAGE around #include msgQLibP.h
06k,03oct04,kk   surround include of msgQLibP.h by #ifndef _ASMLANGUAGE
06j,24sep04,dcc  added accessObjId and taskVarSemId to WIND_TCB.
06i,01oct04,pcm  increased the number of task create/delete hooks from 16 to 20
06h,22sep04,pcm  changed WIND_TCB field name msgPassing to msgQInfo
06g,22sep04,md   moved taskSafe()/taskUnsafe() to taskLibCommon.h
06f,02sep04,aeg  removed NULL pointer check from TASK_ID_VERIFY();
		 changed taskInit2() to taskInitExcStk().
06e,20jul04,tcr  fix TASK_LOCK/TASK_SAFE macros for WV_INSTRUMENTATION
06d,11jun04,aeg  changed definition of VX_DEALLOC_TCB (SPR #98106).
06c,15may04,hya  added VX_DEALLOC_TCB.
06b,05may04,cjj  removed I960 preprocessor directives
06a,30mar04,jb   Renaming I80X86 pad entry to reflect new use
05z,29mar04,dcc  brought back VX_TASK_OBJ_OWNER option bit.
05y,17feb04,dcc  adjusted offsets in WIND_TCB and added currentCtx member.
05x,22jan04,aeg  moved coprocessor related task option bit to taskLibCommon.h
05w,09dec03,dlk  Restored reserved2 field for I80X86 cpu family only.
05v,02apr03,dtr  Reserving TCB slot for compiler.
05u,03sep02,dtr  Adding VX_SPE_TASK option.
05t,07nov03,tcr  allow WV instrumentation to OBJ_VERIFY
05s,26aug03,tcr  update WindView instrumentation
05r,31oct03,dcc  added some members to the WIND_TCB: pEdrInfo, pCompilerData,
		 pDbgInfo, pShellInfo and pUTcb. Reserved 8bytes for WRAMP use.
		 Removed windxLock member. Adjusted offsets as a result of
		 OBJ_CORE expansion.
05q,30oct03,pcm  implemented changes from code review
05p,20oct03,pcm  added new TCB field <pExcStackStart>; replaced various
		 priority inheritance TCB fields with <pPriInheritData>
05o,09sep03,kk   change taskLibInit prototype, added excCnt to TCB,
		 made VX_USER_MODE = 0, added VX_DEALLOC_EXC_STACK option bit,
		 added taskInit2(), renamed pKStackXXX to pExcStackXXX.
05n,05sep03,dcc  moved common definitions with user side to taskLibCommon.h
05m,19aug03,dbt  Added PAL coprocessor support for VxSim.
05l,24jul03,kam  updated offset comments for all simulators
05k,10apr03,pes  PAL Coprocessor Abstraction
05j,21jul03,kk   changed tcbPad[0,1] to pKStackBase and pKStackPtr
05i,08jul03,kk   added VX_USER_MODE option bit for user mode task
05h,15jul03,kam  rebased to Base6 integration branch
05g,23jun03,ymz  added 8-byte alignment padding for MIPS.
05f,20jun03,to   deleted dummyNode, move rtpId, resurrect reserved2.
05e,13may03,to   added rtpId to TCB, added task option VX_TASK_OBJ_OWNER,
		 deleted K&R style prototypes.
05d,14apr03,to   replaced activeNode with dummyNode in TCB for now
05c,14apr03,to   made task name a copy in TASK_DESC instead of a pointer.
05b,20mar03,ymz  moved OBJ_CORE as the first element of WIND_TCB
05a,16jan02,to   added fpStatus to TCB for ARM.
04z,17apr03,dbt  Added SIMLINUX support.
04y,27mar03,jmp  removed unused fields from SIMNT TCB, removed SUNOS and HPPA
		 simulators references.
04x,14mar03,jmp  removed windowsThreadId and windowsThread from SIMNT TCB.
04w,19nov01,aeg  added td_events to TASK_DESC.
04v,09nov01,jhw  Revert WDB_INFO to reside inside WIND_TCB.
04u,06nov01,gls  cleaned up compilation warnings
04t,06nov01,dee  fixed offsets in coldfire specific portion
		 for EXC_INFO and REG_SET per sh-coldfire.tcl
04s,30oct01,jhw  Removed wdbInfo and wdbExitHook from WIND_TCB.
	    gsl  Reused wdbExitHook for pPthread.
04r,22oct01,dee  Merged from T2.1.0 ColdFire
04q,04oct01,yvp  Fixed SPR69306: added member pCoprocCtx to PPC section for
		 Altivec support.
04p,27sep01,aeg  changed comment on WIND_TCB reservedX fields.
04o,24sep01,s_l  Fixed a syntax error on line "UINT32 regSetPad[2]" missing ';'
04n,18sep01,aeg  deleted selectSem, pad1, & pSelWakeupNode from WIND_TCB,
		 and added pSelContext, events, pWdbTaskInfo, & wdbExitHook;
		 added code barriers to TASK_LOCK and TASK_SAFE macros.
04m,01mar00,frf  Added SH4 support for T2.
04l,10sep98,kab  expanded WDB_INFO struct to match TOR2.x., moved pDspContext
		 to end of TCB, replaced spare4.
04k,22jul98,mem  added pDspContext to TCB, removed spare4. Added VX_DSP_TASK.
04j,23apr97,hk   added SH support.
04i,14mar01,pcs  Added VX_ALTIVEC_TASK.
04h,12mar99,dbs  added COM task-local storage to TCB
04g,29may98,cym  added windowsContextValid flag for SIMNT.
04f,24apr98,kkk  moved wdbInfo after ARM stuff in TCB. (bug created by merge)
04e,19aug97,cym  added SIMNT support.
04d,28nov96,cdp  added ARM support.
04c,06nov97,dbt  modified WIND_TCB for new debugger scheme. Removed Am29K
		 family support.
04b,22jul96,jmb  merged ease patch for HP Sim
04a,26may94,yao  added PPC support.
03z,26may95,ms   added wdbExitHook field to the TCB
03y,16may95,rrr  added WDB_INFO structure to TCB.
03x,12jul95,ism  added simsolaris support
03w,19mar95,dvs  removed #ifdef TRON - tron no longer supported.
03v,15mar94,smb  modified TASK_SAFE macro
03u,24jan94,smb  added instrumentation macros
03t,10dec93,smb  instrumented TASK_LOCK macro
03s,02dec93,pme  added Am29K family support
03r,12nov93,hdn  added support for I80X86
03q,15oct93,cd   removed junk values from MIPS TCB.
03p,16sep93,jmm  added S_taskLib_ILLEGAL_PRIORITY and taskPriRangeCheck
03o,11aug93,gae  vxsim hppa.
03n,20jun93,rrr  vxsim.
03m,11feb93,jcf  added __PROTOTYPE_5_0 for compatibility.
03l,08feb93,smb  added a null check to taskIdVerify.
03k,13nov92,dnw  changed declaration of pSmObjTcb to struct sm_obj_tcb *
		 removed include of smObjTcbP.h (SPR #1768)
		 moved typedef of DBG_INFO here from dbgLib.h
		 removed include of dbgLib.h (SPR #1768)
03j,22sep92,rrr  added support for c++
03i,21sep92,smb  removed exit prototype and added include of stdlib.h
03h,02aug92,jcf  changed reserved3 field to pExcRegSet for exception handling.
03g,29jul92,smb  made modification for the stdio library.
03f,28jul92,jcf  added windxLock/reserved[12]; moved dbgInfo/pSmTcbObj;
		 removed funcRestart.
03e,12jul92,yao  replace pDbgState pointer with data structure DBG_INFO
		 in WIND_TCB.  added dbgPCWSave to i960.
03d,19jul92,pme  added shared memory objects support.
03c,10jul92,jwt  moved padding out of REG_SET in into WIND_TCB for SPARC.
03b,06jul92,ajm  removed taskSummary from forward declarations
03a,04jul92,jcf  cleaned up.
02y,16jun92,yao  made pDbgState available for all architectures.
02x,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
02w,19mar92,yao  added ANSI prototype for taskStackAllot().
02v,12mar92,yao  removed ifdef CPU.  added taskRegsShow().
02u,10jan92,jwt  added CPU_FAMILY==SPARC architecture dependent prototypes.
02t,11nov91,rrr  Added funcRestart to tcb for signals.
02s,28oct91,wmd  Added changes for i960KB from Intel.
02r,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
02q,20sep91,hdn  deleted foroff from WIND_TCB for TRON.
		 added pDbgState to WIND_TCB for TRON.
02p,20aug91,ajm  made architecture independent.
02o,10jun91,del  added pragma for gnu960 alignment.
02n,23may91,wmd  added defines and macros for SPARC architecture.
02m,29apr91,hdn  added defines and macros for TRON architecture.
02l,08apr91,jdi  added NOMANUAL to prevent mangen.
02k,24mar91,del  added pDbgState for use with new dbgLib. And I960 defines.
02j,16oct90,shl  made #else ANSI style.
02i,05oct90,dnw  deleted private functions.
		 made taskSpawn, taskInit, taskCreate take var args.
02h,05oct90,shl  added ANSI function prototypes.
		 made #endif ANSI style.
		 added copyright notice.
02g,01oct90,jcf  added additional spares to WIND_TCB.
02f,03aug90,jcf  moved arch dependent portion of WIND_TCB to end of struct
02e,13jul90,rdc  added support for environment variables and additional
		 select functionality.
02d,30jun90,jcf  added assembly language defines.
02c,26jun90,jcf  removed obsolete generic status codes
		 changed inheritance protocol.
		 changed safetyQSem to a safetyQHead.
		 reworked priority management.
		 changed topOfStack to endOfStack.
02b,17may90,rdc  changed select semaphores in tcb to be binary semaphores.
02a,17apr90,jcf  added error codes.
		 changed to wind 2.0.
01l,16mar90,rdc  added select semaphore to tcbx.
01k,25may89,gae  added VX_FORTRAN option.
01j,21apr89,jcf  added KERNEL_{UNINIT,VRTX,PSOS,WIND}.
01i,07nov88,rdc  added VX_ADA_DEBUG to task options.
01h,22jun88,dnw  name tweaks.
01g,30may88,dnw  changed to v4 names.
01f,28may88,dnw  deleted obsolete status values.
		 added EXC_INFO to tcbx.
01e,18may88,jcf  added psos semaphore head to tcbx.
		  extended maximum number of hooks to 10.
01d,13may88,rdc  added signal info to tcbx.
01c,28apr88,ecs  added IMPORTs of idle & taskName.
01b,13apr88,gae  added function declarations; option bit VX_STDIO;
		 taskStd[] to TCB extension.
01a,25jan88,jcf  written by extracting from vxLib.h v02l.
*/

#ifndef __INCtaskLibh
#define __INCtaskLibh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>
#include <classLib.h>
#include <regs.h>
#include <excLib.h>
#include <private/qLibP.h>
#include <private/eventP.h>
#include <private/semLibP.h>
#include <private/objLibP.h>
#include <private/eventLibP.h>
#include <private/msgQLibP.h>
#include <private/kernelBaseLibP.h>	/* kernelId for IS_KERNEL_TASK */
#include <stdlib.h>
#include <taskLibCommon.h>
#include <sys/taskDefs.h>
#include <vxAtomicLib.h>
#include <cpuset.h>

/* 
 * logLib.h is included here to reduce the breakage of users who used to include
 * _func_logMsg via funcBindP.h
 */

#include <logLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* miscellaneous */

#define TASK_PRIORITY_SELF	-1	/* passing normal Priority */

#define MAX_TASK_ARGS		10	/* max args passed to a task */

#define VX_MAX_TASK_SWITCH_RTNS	16	/* max task switch callout routines */
#define VX_MAX_TASK_SWAP_RTNS	16	/* max task swap callout routines */

/* The MAX priority (lowest priority) that a public task can have */

#define VX_TASK_PRIORITY_MAX    255

/* The MIN priority (highest priority) that a public task can have */

#define VX_TASK_PRIORITY_MIN	0


/* kernel only task option bits (see taskLibCommon.h for common option bits) */

#define VX_UNBREAKABLE		0x0002	/* breakpoints ignored */

#define VX_STDIO		0x0010	/* OBSOLETE: need not be set for stdio*/
#define VX_ADA_DEBUG		0x0020	/* 1 = VADS debugger support */
#define VX_FORTRAN		0x0040	/* 1 = NKR FORTRAN support */

#define VX_PRIVATE_CWD          0x0200  /* 1 = private CWD */

/* VX_PRIVATE_ENV		0x0080	   defined in taskLibCommon.h */
/* VX_NO_STACK_FILL		0x0100     defined in taskLibCommon.h */
/* VX_TASK_NOACTIVATE		0x2000	   defined in taskLibCommon.h */
/* VX_NO_STACK_PROTECT		0x4000	   defined in taskLibCommon.h */

/* the following are now defined in sys/taskDefs.h */

/* #define VX_USER_MODE		0x0000	   INTERNAL: tasks in user mode */
/* #define VX_SUPERVISOR_MODE	0x0001	   INTERNAL: tasks in sup mode */
/* #define VX_DEALLOC_STACK	0x0004	   INTERNAL: deallocate stack */
/* #define VX_TASK_OBJ_OWNER	0x0800	   INTERNAL: task owns objs directly */
/* #define VX_DEALLOC_EXC_STACK	0x1000	   INTERNAL: deallocate the exc stack */
/* #define VX_DEALLOC_TCB	0x8000	   INTERNAL: deallocate the task TCB */

/* kernel SMP flags */

#define VX_SMP_INTLOCKED	0x0001	/* tasks holds global interrupt lock */

/* typedefs */

#ifndef	_ASMLANGUAGE

typedef struct
    {
    cpuset_t    affinity;       /* 0x00/0x00: CPU affinity (if any) */
    int         cpuIndex;       /* 0x04/0x04: CPU index running on (if any) */
    long	readyQExt;      /* 0x08/0x08: readyQ impl. specific extension */
    Q_HEAD      stateSaveQHead; /* 0x0c/0x10: stop queue head */
    UINT	stateRequest;	/* 0x1c/0x30: requested state change */
#ifdef	_WRS_CONFIG_LP64
    UINT	padding;	/* ----/0x34: padding  			*/
#endif	/* _WRS_CONFIG_LP64 */
    } WIND_SMP_INFO;		/* 0x20/0x38: total size */
    
/*
 * ############################# WARNING ###############################
 *
 * The WIND_TCB structure below will be moved into the private/taskLibP.h
 * header in the next major release of VxWorks. In future releases, direct
 * access to fields in the WIND_TCB structure will not be supported. Please
 * migrate to using the available published APIs in the task libraries
 * to access fields in the TCB.
 */

/*
 * INTERNAL: When adding fields to WIND_TCB, be sure to update the
 * offsets comments.  Also, the objCore and tickNode members must remain the 
 * first and second of the structure.  This is because consistency is necessary 
 * between the TCB and watchdog structures.
 */

typedef struct windTcb		/* WIND_TCB - task control block */
    {
    OBJ_CORE		objCore;	/* 0x00/0x00: object management */

    Q_NODE		tickNode;	/* 0x44/0x80: multiway q node: tick q */
    Q_NODE		qNode;		/* 0x54/0xa0: multiway q node: */
					/* 	      rdy/pend q */
    char *		pExcStackBase;	/* 0x64/0xc0: ptr to exc stack base */
    char *		pExcStackEnd;	/* 0x68/0xc8: ptr to exc stack end */
    char *		pExcStackStart; /* 0x6c/0xd0: ptr to start of exc */
					/* 	      stack */
    int			excCnt;		/* 0x70/0xd8: exception next cnt */

    UINT		status;		/* 0x74/0xdc: status of task */
    UINT		priority;	/* 0x78/0xe0: task's current priority */
    int			priNormal;      /* 0x7c/0xe4: normal running priority */
    UINT		lockCnt;	/* 0x80/0xe8: preemption lock count */

    /* SH arch. requires for the previous members to be within a 0x7f offset */

    UINT		priMutexCnt;    /* 0x84/0xec: # of inv safe sems a */
					/*	      task has 		   */
    UINT		priInheritCnt;  /* 0x88/0xf0: # of times task prio */
					/* 	      bumped 		   */
    int			priDrop;        /* 0x8c/0xf4: priority to drop task */
					/*	      to 		    */
    SEMAPHORE *		pPriMutex;      /* 0x90/0xf8: pointer to mutex task */
					/* 	      pends on 		    */

    RTP_ID		currentCtx;	/* 0x94/0x100: task's current context */
    RTP_ID		rtpId;		/* 0x98/0x108: real time process ID */

    void *		pUTcb;		/* 0x9c/0x110: ptr to user level TCB */
    int			options;	/* 0xa0/0x118: task option bits */
    UINT		tslice;		/* 0xa4/0x11c: current count of time */
					/*	       slice		     */
    Q_HEAD *		pPendQ;		/* 0xa8/0x120: q head pended on (if */
					/*	       any)		    */

    UINT16		swapInMask;	/* 0xac/0x128: task's switch in hooks */
    UINT16		swapOutMask;	/* 0xae/0x12a: task's switch out */
					/*	       hooks		 */

    UINT		safeCnt;	/* 0xb0/0x12c: safe-from-delete count */
    Q_HEAD		safetyQHead;	/* 0xb4/0x130: safe-from-delete q */
					/* 	       head 		  */

    FUNCPTR		entry;		/* 0xc4/0x150: entry point of task */

    char *		pStackBase;	/* 0xc8/0x158: points to bottom of */
					/* 	       stack 		   */
    char *		pStackEnd;	/* 0xcc/0x160: points to end of stack */
    void *		pEdrInfo;	/* 0xd0/0x168: ptr to ED&R info */

    int			errorStatus;	/* 0xd4/0x170: most recent task error */
#ifdef _WRS_CONFIG_LP64
    UINT		pad3;		/* ----/0x174: explicit pad for align */
#endif
    _Vx_exit_code_t	exitCode;	/* 0xd8/0x178: error passed to exit() */

    struct sigtcb *	pSignalInfo;	/* 0xdc/0x180: ptr to signal info for */
					/* 	       task 		      */
    struct selContext *	pSelectContext;	/* 0xe0/0x188: ptr to select info for */
					/*	       task 		      */

    _Vx_ticks_t		taskTicks;	/* 0xe4/0x190: total number of ticks */
    _Vx_ticks_t		taskIncTicks;	/* 0xe8/0x194: number of ticks in */
					/*	       slice 		  */

    struct taskVar *	pTaskVar;	/* 0xec/0x198: ptr to task variable */
					/*	       list 		    */
    struct rpcModList *	pRPCModList;	/* 0xf0/0x1a0: ptr to rpc module */
					/*	       statics 		 */
#if defined (_WRS_PAL_COPROC_LIB)
    struct coprocTblEntry * pCoprocTbl;	/* 0xf4/0x1a8: fpoint coprocessor */
					/*	       context 		  */
#else /* _WRS_PAL_COPROC_LIB */
    struct fpContext *	pFpContext;	/* 0xf4/0x1a8: fpoint coprocessor */
					/*	       context 		  */
#endif /* _WRS_PAL_COPROC_LIB */

    struct __sFILE *	taskStdFp[3];	/* 0xf8/0x1b0: stdin,stdout,stderr */
					/*	       fps 		   */
    int			taskStd[3];	/* 0x104/0x1c8: stdin,stdout,stderr */
					/*		fds 		    */
    EVENTS		events;		/* 0x110/0x1d4: event info for the */
					/*		task 		   */
    int			nEnvVarEntries; /* 0x11c/0x1e0: num env vars used */
#ifdef _WRS_CONFIG_LP64
    UINT		pad4;		/* -----/0x1e4: explicit padding */
#endif

    size_t		envTblSize;	/* 0x120/0x1e8: number of slots in */
					/*		table 		   */
    char **		ppEnviron;	/* 0x124/0x1f0: environment var table */
    struct sm_obj_tcb *	pSmObjTcb;	/* 0x128/0x1f8: shared mem object TCB */
    void *		pComLocal;	/* 0x12c/0x200: COM task-local  */
					/*		storage ptr 	*/
    REG_SET *		pExcRegSet;	/* 0x130/0x208: exception regSet ptr */
					/*		or NULL		     */

    void *		pWdbInfo;	/* 0x134/0x210: ptr to WDB info */
					/*		-future use     */
    void *		pDbgInfo;       /* 0x138/0x218: ptr to DBG info */
					/*		-future use     */

    void *		pPthread;	/* 0x13c/0x220: ptr to pthread data  */
					/*		structs 	     */
    void *		pCompilerData;	/* 0x140/0x228: ptr to thread and EH */
					/*		data 		     */
    void *		pShellInfo;	/* 0x144/0x230: ptr to kernel shell  */
					/*		info 		     */
    MSGQ_TCB		msgQInfo;	/* 0x148/0x238: used for message     */
					/*		queues 		     */
    OBJ_ID		accessObjId;    /* 0x158/0x258: objId task is        */
					/*		accessing            */
    SEM_ID		taskVarSemId;	/* 0x15c/0x260: task variable mutex  */
    size_t		execGuardSize;  /* 0x160/0x268: execution stack guard */
					/*		size 		      */

    /* cpuTimeInfo should be aligned on an 8-byte boundary */

#ifndef _WRS_CONFIG_LP64
    UINT                pad3;		/* 0x164/ ----: pad format/offset to */
                                        /*              UINT                 */
#endif

    UINT64              cpuTimeInfo[2]; /* 0x168/0x270: sched extension - CPU */
					/*		time 		      */

    void *              pPwrMgmtPState; /* 0x178/0x280: cpu pwr mgmt Task */
					/*		P-State 	  */

    /* extensions provided for plug-in schedulers */

    void *              pSchedInfo;     /* 0x17c/0x288: ptr to scheduler info */

    void *              pExecClkInfo;   /* 0x180/0x290: ptr to CPU-clock info */
    WIND_SMP_INFO       windSmpInfo;    /* 0x184/0x298: SMP info structure */

    long		reserved1;	/* 0x1a4/0x2d0: possible WRS 	*/
					/*		extension    	*/
    long		reserved2;	/* 0x1a8/0x2d8: possible WRS 	*/
					/*		extension    	*/
    long		spare1;		/* 0x1ac/0x2e0: possible user 	*/
					/*		extension 	*/
    long		spare2;		/* 0x1b0/0x2e8: possible user 	*/
					/*		extension 	*/
    long		spare3;		/* 0x1b4/0x2f0: possible user 	*/
					/*		extension 	*/
    long		spare4;		/* 0x1b8/0x2f8: possible user 	*/
					/*		extension 	*/

    /* ARCHITECTURE DEPENDENT */

#if (CPU_FAMILY==MC680X0)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET must be aligned on a 4 byte boundary */

    REG_SET		regs;		/* 0x1d0: register set */
    UINT16		foroff;		/* 0x218: format/offset from frame */
    UINT16		pad2;		/* 0x21a: pad format/offset to UINT */
#endif	/* CPU_FAMILY==MC680X0 */

#if (CPU_FAMILY==COLDFIRE)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET should be aligned on a 4-byte boundary */

    REG_SET		regs;		/* 0x1d0: register set */
#endif	/* CPU_FAMILY==COLDFIRE */

#if (CPU_FAMILY==MIPS)

    /* make excInfo on 8-byte boundary */

    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET should be on a 8-byte boundary */

    int			pad;		/* 0x1dc: pad format/offset to UINT */
    REG_SET		regs;		/* 0x1e0: register set */
#endif	/* CPU_FAMILY==MIPS */

#if (CPU_FAMILY == PPC)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */
    UINT		pCoprocCtx;	/* 0x1e4: pointer to Coprocessor Ctx */

    /* REG_SET must be aligned on a 4-byte boundary */

    int                 pad;            /* 0x1e8: padding
					 * No need this padding.
					 * However, we leave this
					 * padding for DKM binary compatibility.
					 */

    REG_SET		regs;		/* 0x1ec: register set */
#endif /* (CPU_FAMILY == PPC) */

#if (CPU_FAMILY == SPARC)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET must be aligned on an 8-byte boundary */

    REG_SET		regs;		/* 0x1d0: register set */
#endif	/* CPU_FAMILY == SPARC */

#if (CPU_FAMILY==SIMSPARCSOLARIS)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET must be aligned on an 8-byte boundary */

    int                 pad;            /* 0x1dc: padding for 8 bytes align */
    REG_SET		regs;		/* 0x1e0: register set */

#endif /* CPU_FAMILY==SIMSPARCSOLARIS*/

#if (CPU_FAMILY==SIMNT)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET must be aligned on a 4 byte boundary */

    REG_SET             regs;           /* 0x1d0: register set */
#ifdef _WRS_CONFIG_LP64
    SIM_REG_SET		extraRegs;	
#endif /* _WRS_CONFIG_LP64 */
#endif /* CPU_FAMILY==SIMNT */

#if (CPU_FAMILY==SIMLINUX)
    EXC_INFO            excInfo;        /* 0x1bc: exception info */

    /* REG_SET must be aligned on a 4 byte boundary */

    REG_SET             regs;           /* 0x1d0: register set */
#ifdef _WRS_CONFIG_LP64
    SIM_REG_SET		extraRegs;	
#endif /* _WRS_CONFIG_LP64 */
#endif /* CPU_FAMILY==SIMLINUX */

#if (CPU_FAMILY==I80X86)
    EXC_INFO            excInfo;        /* 0x1bc/0x300: exception info */
#ifdef _WRS_CONFIG_LP64
    UINT		padding;	/* -----/0x3ac: padding 	*/
#endif /* _WRS_CONFIG_LP64 */
    CTX_SET             ctxSet;         /* 0x214/0x3b0: ptr to extra context */

    /* REG_SET must be aligned on an 8-byte boundary for PENTIUM */

#ifndef _WRS_CONFIG_LP64
    int                 pad;            /* 0x224: padding for 8 bytes align */
#endif /* _WRS_CONFIG_LP64 */

    REG_SET             regs;           /* 0x228/0x3d0: register set */
#endif /* CPU_FAMILY==I80X86 */

#if (CPU_FAMILY==SH)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    /* REG_SET must be aligned on a 4 byte boundary */

    REG_SET		regs;		/* 0x1d0: register set */
#endif	/* CPU_FAMILY==SH */

#if (CPU_FAMILY==ARM)
    EXC_INFO		excInfo;	/* 0x1bc: exception info */

    UINT32		fpStatus;	/* 0x1cc: fp status word */

    /* REG_SET must be aligned on a 4-byte boundary */

    int                 pad[2];         /* 0x1d0: padding
					 * To be precise, only 4-byte alignment
					 * is required. However, we leave this
					 * padding for the offsets of other
					 * members to be compatible with VxWorks
					 * 6.9 in case kernel awareness host
					 * tools use hard coded offsets to
					 * access the TCB info.
					 */

    REG_SET		regs;		/* 0x1d8: register set */
#endif /* CPU_FAMILY==ARM */

#if !defined (_WRS_PAL_COPROC_LIB)
    struct dspContext *	pDspContext;	/* dsp coprocessor context */
#else /* _WRS_PAL_COPROC_LIB */
    void *		pUnused;
#endif /* _WRS_PAL_COPROC_LIB */
    void *		pIpcomInfo;     /* ipcom info */
    struct tls_desc *	pTlsDesc;	/* TLS descriptor */
    void *		pVxdbgInfo;	/* target debug info */
    UINT                stopClients;  	/* taskStop clients */
    UINT                sigStopCnt;  	/* signal stop count */
    Q_HEAD  		waitPendQ;      /* pend queue for taskWait */
    void *              pCwdInfo;       /* CWD info */

    RTP_ID		rtpWaitId;	/* These two members are used for  */
    void *              pMemCache;      /* ptr to memory cache bin */
    int			rtpExitStatus;  /* the rtpWait feature.  They hold */
                                        /* the RTP ID and exit status of   */
                                        /* RTP it is pending on.	   */
    } WIND_TCB;

/* variable declarations */

extern CLASS_ID	taskClassId;		/* task class id */

#ifdef  _WRS_CONFIG_SMP
#define taskIdCurrent	((WIND_TCB *) taskIdSelf())
#else
extern WIND_TCB * taskIdCurrent;	/* always current executing task */
#endif  /* _WRS_CONFIG_SMP */

/* defines */

#ifdef _WRS_CONFIG_SMP

#ifndef TASK_SAFE_INC_VALUE
#define TASK_SAFE_INC_VALUE 2
#endif /* !TASK_SAFE_INC_VALUE */

#ifndef TASK_LOCK_INC_VALUE
#define TASK_LOCK_INC_VALUE 2
#endif

#endif /* !_WRS_CONFIG_SMP */

/* TASK_LOCK()/UNLOCK() is now replaced by TASK_CPU_LOCK()/UNLOCK(() */

#define TASK_LOCK()	TASK_CPU_LOCK()
#define TASK_UNLOCK()	TASK_CPU_UNLOCK()

/*******************************************************************************
*
* TASK_ID_VERIFY - check the validity of a task
*
* This macro verifies the existence of the specified object by comparing the
* task's classId with the expected class id.  If the task does not check
* out, errno is set with the appropriate invalid id status.
*
* Since we added the ability to remove the OBJ_VERIFY macro definition, we need
* to call objVerify() directly here - taskIdVerify is a published API and we do
* not wish to change it's behavior.
*
* RETURNS: OK or ERROR if invalid task id
*
* \NOMANUAL
*/

#define TASK_ID_VERIFY(tid)						      \
    (									      \
    (objVerify (&((WIND_TCB *)(tid))->objCore, taskClassId))		      \
    )

/*******************************************************************************
*
* TASK_CPU_LOCK - lock CPU preemption for calling task
*
* This macro performs the taskCpuLock (2) routine.
* windview - this macro has been instrumented for windview.
*
* \NOMANUAL
*/

#define TASK_CPU_LOCK() taskCpuLockTask_inline(taskIdCurrent)

/*
 * Note that TASK_CPU_LOCK_TASK() must be used only for the current
 * task, and only when it's task ID is already known.
 */

#define TASK_CPU_LOCK_TASK(tCurrent) taskCpuLockTask_inline(tCurrent)

_WRS_INLINE void taskCpuLockTask_inline
    (
    WIND_TCB * tCurrent
    )
    {
#ifndef _WRS_CONFIG_SMP
    VX_CODE_BARRIER();
    tCurrent->lockCnt++;
    VX_CODE_BARRIER();
#else
    vxAtomic32Add_inline((atomic32_t *) &tCurrent->lockCnt, 
			 TASK_LOCK_INC_VALUE);
#endif

#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
    if (ACTION_IS_SET)
	{
	EVT_CTX_0_BH (EVENT_TASKLOCK);
	}
#endif
    }

/*******************************************************************************
*
* TASK_CPU_UNLOCK - unlock CPU preemption for calling task
*
* This macro performs the taskCpuUnlock (2) routine.
*
* \NOMANUAL
*/

#define TASK_CPU_UNLOCK()						\
    (									\
    taskCpuUnlock ()							\
    )

/*******************************************************************************
*
* TASK_SAFE - guard self from deletion
*
* This macro performs the taskSafe (2) routine.
* windview - this macro has been instrumented for windview.
*
* \NOMANUAL
*/

#define TASK_SAFE() taskSafeTask_inline(taskIdCurrent)

/*
 * Note that taskSafeTask_inline() must be used only for the current
 * task, and only when it's task ID is already known.
 */

_WRS_INLINE void taskSafeTask_inline 
    (
    WIND_TCB * tCurrent
    )
    {
#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
    EVT_OBJ_2 (tCurrent, taskClassId, EVENT_TASKSAFE,
	       tCurrent, tCurrent->safeCnt);
#endif

#ifndef _WRS_CONFIG_SMP
    VX_CODE_BARRIER();
    tCurrent->safeCnt++;
    VX_CODE_BARRIER();
#else /* !_WRS_CONFIG_SMP */
    vxAtomic32Add ((atomic32_t *) &tCurrent->safeCnt, TASK_SAFE_INC_VALUE);
#endif /* !_WRS_CONFIG_SMP */
    }

/*******************************************************************************
*
* TASK_UNSAFE - unguard self from deletion
*
* This macro performs the taskUnsafe (2) routine.
*
* \NOMANUAL
*/

#define TASK_UNSAFE()							\
    (									\
    taskUnsafe ()							\
    )

/*******************************************************************************
*
* IS_KERNEL_TASK - determine a task is a kernel task
*
* This macro returns 1 if the specified task is a kernel task. Otherwise
* 0 or if tid == 0, return the ID of the current task.
*
* If a system is built without RTP support, (for a faster and smaller kernel)
* the macro is simply replaced with "1". Without RTP support, all tasks will be
* kernel tasks.
*
* In the  case where this makes one branch of an "if-else" statement dead (e.g. 
* "if (IS_KERNEL_TASK(tid)) {..." ) the compiler will remove everything except
* the live statement from the resulting assembly code.
*
* \NOMANUAL
*/

#ifdef _WRS_CONFIG_RTP
#define IS_KERNEL_TASK( tid )						\
    (									\
    (((tid) == 0 ? (WIND_TCB *)taskIdCurrent:(WIND_TCB *)(tid))->rtpId == kernelId) \
    )
#else
#define IS_KERNEL_TASK( tid )		TRUE
#endif /* _WRS_CONFIG_RTP */

/******************************************************************************
*
* TASK_QNODE_TO_PSCHEDINFO - get the pSchedInfo from a task qNode
*
* This macro returns the address of "pSchedInfo" of WIND_TCB to which a "qNode"
* belongs. This macro is intended to be used by user specified schedulers, when
* the component INCLUDE_CUSTOM_SCHEDULER is configured.
*
* \NOMANUAL
*/

#define TASK_QNODE_TO_PSCHEDINFO(node)  \
    (                                   \
    taskSchedInfoGet(node)              \
    )

/*******************************************************************************
*
* VX_TASK - declare storage for a task
*
* This macro declares storage for a task with name <name> with a stack size
* <stackSz> bytes. This macro only generates data declarations for the task.
* This macro is useful for declaring tasks statically (i.e. at compile
* time, without using any dynamic memory allocation at runtime). To fully
* initialize the task, macro VX_TASK_INITIALIZE must be called. To initialize
* and activate the task, macro VX_TASK_INSTANTIATE must be called.
*
* SEE ALSO: VX_TASK_INITIALIZE, VX_TASK_INSTANTIATE
*
* \NOMANUAL
*/

#define VX_TASK(name,stackSz)                                                 \
    WIND_TCB name##Tcb;                                                       \
    _WRS_DATA_ALIGN_BYTES(_STACK_ALIGN_SIZE)                                  \
	char name##Stk [STACK_ROUND_UP((stackSz))];                           \
    _WRS_DATA_ALIGN_BYTES(_STACK_ALIGN_SIZE)                                  \
	 char name##ExcStk [STACK_ROUND_UP((KERNEL_TASK_EXC_STACK_SIZE))];


/*******************************************************************************
*
* VX_TASK_INITIALIZE - initialize a task declared with the VX_TASK macro
*
* This macro initializes a task declared previously with the VX_TASK macro.
* with name <name> having a stack size of <stackSz> bytes. This macro only
* initializes the task and leaves it suspended. It returns a task ID for
* the initialized task on successful initialization, or NULL on failure.
* To activate (i.e. schedule) the task, function taskActivate must be called
* with the task id returned by this macro. Only then is the task functional.
* The arguments to this macro and their types are the same as those passed to
* function taskSpawn(). Please refer to the documentation for taskSpawn() for
* more details on the arguments.
*
* RETURNS: task ID on success or NULL on error.
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <taskLib.h>
*
*      VX_TASK(myTask,4096);
*      TASK_ID myTaskId;
*
*      STATUS initializeFunction (void)
*          {
*          myTaskId = VX_TASK_INITIALIZE(myTask, 100, 0, 4096, pEntry, \
*                                        0,1,2,3,4,5,6,7,8,9);
*
*         if (myTaskId != NULL)
*             {
*             taskActivate (myTaskId);
*             return (OK);
*             }
*         else
*             return (ERROR);
*          }
* \ce
*
* SEE ALSO: VX_TASK, VX_TASK_INSTANTIATE, taskSpawn()
* \NOMANUAL
*/

#define VX_TASK_INITIALIZE(name,prio,options,stackSz,entryPt,arg1,arg2,arg3,  \
			   arg4,arg5,arg6,arg7,arg8,arg9,arg10)               \
    ((taskInitExcStk (&name##Tcb, #name, (prio), (options),                   \
		      &name##Stk[STACK_ROUND_UP((stackSz))],                  \
		      STACK_ROUND_UP((stackSz)),                              \
		      &name##ExcStk                                           \
		      [STACK_ROUND_UP((KERNEL_TASK_EXC_STACK_SIZE))],         \
		      STACK_ROUND_UP((KERNEL_TASK_EXC_STACK_SIZE)),           \
		      ((FUNCPTR) (entryPt)), (arg1), (arg2), (arg3), (arg4),  \
		      (arg5), (arg6), (arg7), (arg8), (arg9), (arg10)) == OK) \
     ? ((TASK_ID) &name##Tcb)                                                 \
     : ((TASK_ID) NULL))


/*******************************************************************************
*
* VX_TASK_INSTANTIATE - initialize and activate a task declared using VX_TASK
*
* This macro initializes and activates a task declared previously with the
* VX_TASK macro. The task is fully functional after the call to this macro
* if it succeeds. This macro returns a task ID for the instantiated task on
* or NULL on failure. The arguments to this macro and their types are the same
* as those passed to function taskSpawn(). Please refer to the documentation
* for taskSpawn() for more details on the arguments.
*
* RETURNS: task ID on success or ERROR.
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <taskLib.h>
*
*      VX_TASK(myTask,4096);
*      TASK_ID myTaskId;
*
*      STATUS initializeFunction (void)
*          {
*          myTaskId = VX_TASK_INSTANTIATE(myTask, 100, 0, 4096, pEntry, \
*                                         0,1,2,3,4,5,6,7,8,9);
*
*         if (myTaskId != TASK_ID_ERROR)
*             return (OK);                /@ instantiation succeeded @/
*         else
*             return (ERROR);
*          }
* \ce
*
* SEE ALSO: VX_TASK, VX_TASK_INITIALIZE, taskSpawn()
* \NOMANUAL
*/

#define VX_TASK_INSTANTIATE(name,prio,options,stackSz,entryPt,arg1,arg2,arg3, \
			   arg4,arg5,arg6,arg7,arg8,arg9,arg10)               \
    (((VX_TASK_INITIALIZE(name,prio,options,stackSz,entryPt,arg1,arg2,arg3,   \
		   arg4,arg5,arg6,arg7,arg8,arg9,arg10) == (TASK_ID) NULL) || \
      (taskActivate ((TASK_ID)&name##Tcb) != OK))                             \
    ? (TASK_ID_ERROR)                                                         \
    : ((TASK_ID) &name##Tcb))

/* function declarations */

extern STATUS	taskLibInit	(size_t usrDefExcStackSize,
				 size_t usrDefExcStackOverflowSize,
				 size_t kernelDefExcStackOverflowSize,
				 size_t usrDefExecStackOverflowSize,
				 size_t usrDefExecStackUnderflowSize,
				 size_t kernelDefExecStackOverflowSize,
				 size_t kernelDefExecStackUnderflowSize);
extern void	taskCreateLibInit (void);
extern void	taskOpenInit	(void);
extern STATUS	taskInit	(WIND_TCB * pTcb, char * name, int priority,
				 int options, char * pStackBase, 
                                 size_t stackSize, FUNCPTR entryPt, 
                                 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2, 
                                 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
                                 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6, 
                                 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8, 
                                 _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);
extern STATUS	taskInitExcStk	(WIND_TCB * pTcb, char * name, int priority,
				 int options, char * pStackBase, size_t stackSize,
				 char * pExcStackBase, size_t excStackSize,
				 FUNCPTR entryPt, 
                                 _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2, 
                                 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4, 
                                 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6, 
                                 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8, 
                                 _Vx_usr_arg_t arg9, _Vx_usr_arg_t arg10);
extern STATUS	taskOptionsSet	(TASK_ID tid, int mask, int newOptions);
extern WIND_TCB * taskTcb	(TASK_ID tid);
extern int	taskIdListGet	(TASK_ID idList [ ], int maxTasks);
extern STATUS	taskPriNormalGet (TASK_ID tid,int * priNormal);
extern STATUS	taskStatusString (TASK_ID tid, char * pString);
extern STATUS	taskOptionsString (TASK_ID tid, char * pString);
extern STATUS	taskRegsGet	(TASK_ID tid, REG_SET * pRegs);
extern STATUS	taskRegsSet	(TASK_ID tid, REG_SET * pRegs);
extern void	taskRegsShow	(TASK_ID tid);
extern void *	taskStackAllot	(TASK_ID tid, size_t nBytes);
extern void	taskShowInit	(void);
extern STATUS	taskShow	(TASK_ID tid, int level);
extern STATUS	taskLock	(void);
extern STATUS	taskUnlock	(void);
extern STATUS   taskRotate      (int priority);
extern STATUS	taskCpuLock     (void);
extern STATUS   taskCpuUnlock   (void);
extern void	taskExit	(_Vx_exit_code_t code);
extern void *   taskSchedInfoGet (Q_NODE * pNode);
extern STATUS   taskWait        (TASK_ID tid, _Vx_ticks_t timeout);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCtaskLibh */
