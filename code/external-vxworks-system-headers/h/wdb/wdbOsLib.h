/* wdbOsLib.h - WDB vxWorks specific header */

/*
 * Copyright (c) 2003-2011 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
02a,20dec11,rlp  CQID: Fix WIND00323889 - Updated vxdbgCpuAllSuspend()
                 prototype.
01z,25oct10,rlp  Defined the IS_WDB_ENABLED macro.
01y,29apr10,pad  Moved extern C statement after include statements.
01x,01mar10,rlp  Cleaned up warnings.
01w,23feb10,rlp  Added wdbDynPrintfBpHandler prototype.
01v,10feb10,rlp  Added vxdbgLibP header file.
01u,05feb10,rlp  Renamed loCtx field of WDB_MEM_CTX_T to ctx for backward
                 compatibility.
01t,29sep09,rlp  Added the WDB_CORE_MEM_CTX_GET macro for LP64 adaptation.
01t,21sep09,s_s  changed INT_CPU_LOCK() and INT_CPU_UNLOCK() to 
                 INT_CPU_MICRO_LOCK() and INT_CPU_MICRO_UNLOCK()
		 (WIND00181479)
01s,10sep08,dbt  Added WDB_KERNEL_IS_INITIALIZED() macro.
01r,27aug08,jpb  Renamed VSB header file
01q,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01p,22apr08,dbt  Added WDB dynamic printf init routine.
01o,25jul07,rlp  Added CPU all suspend timeout (CQ:WIND00099255).
01n,11jul07,rlp  Added SMP support.
01m,06jul07,p_b  Added 64bits support
01l,09nov06,rlp  Added sigLib header file to remove warnings.
01k,30oct06,rlp  Modified to use VxDBG library (REQ00007655).
01j,20dec05,dbt  Added VxWorks specific APIs from wdbLib.h.
01i,05dec05,dbt  Removed inclusion of RPC header files.
		 Cleanup.
01h,28nov05,dbt  Moved WDB_CTX_XXX definitions to wdbOsLib.h.
01g,14nov05,dbt  Added WDB_IU_REGS definition.
01f,23mar04,elg  Macros to get information in context are now OS specific.
01e,12sep03,tbu  Added inclusion of netinet/in_systm.h
01d,29aug03,elg  Redefine GOPHER_STRTOL to do strtoul() (fix SPR #90223).
		 Include vxWorks.h first (fix SPR #90034).
01c,14jul03,pch  Conditional compilation cleanup
01b,06may03,elg  Fix compilation error when Altivec is supported.
01a,03jan03,elg  Written.
*/

#ifndef	__INCwdbOsLibh
#define	__INCwdbOsLibh

/*
DESCRIPTION

The vxWorks specific header contains definitions that cannot be used by other
OSes.
*/

/* includes */

#include <vxWorks.h>	/* this file must be included first */
#include <vsbConfig.h>

#include <types/vxANSI.h>
#include <netBufLib.h>
#include <net/mbuf.h>

#include <ctype.h>
#include <limits.h>
#include <sioLib.h>
#include <stdlib.h>
#include <string.h>
#include <regs.h>
#include <dspLib.h>
#include <taskHookLib.h>
#include <taskLib.h>
#include <intLib.h>
#include <fppLib.h>
#include <sigLib.h>
#include <sysDbgLib.h>
#include <private/intMicroLibP.h>
#include <private/vxdbgLibP.h>
#ifdef	_WRS_CONFIG_SMP
#include <private/vxdbgCpuLibP.h>
#endif	/* _WRS_CONFIG_SMP */

#ifdef	__cplusplus
extern "C" {
#endif

/* data types */

typedef REG_SET	WDB_IU_REGS;	/* WDB register set */
struct wdb_brkpt;		/* WDB breakpoint structure */

/* OS definitions */

#define	IS_WDB_ENABLED()	(wdbIsAlwaysEnabled ? TRUE : sysDebugModeGet())

#define	WDB_KERNEL_ID		-1L	/* kernel ID in WDB agent */

/* access to registers */

#define	WDB_PC(ptr)		(ptr)->reg_pc
#define	WDB_FP(ptr)		(ptr)->reg_fp
#define	WDB_SP(ptr)		(ptr)->reg_sp

/* debug info */

/* on vxWorks, PC does not need to be changed */

#define	_WRS_ADJUST_PC_AFTER_SW_BP(pRegs)

/* macros to get and set ID from context structure */

#ifdef	_WRS_CONFIG_SMP
#define	WDB_CTX_SYS_INFO_SET(pArgs)					\
	{								\
	(pArgs) [0] = 0;						\
	(pArgs) [1] = (TGT_LONG_T) _WRS_CPU_INDEX_GET();		\
	}
#else	/* _WRS_CONFIG_SMP */
#define	WDB_CTX_SYS_INFO_SET(pArgs)					\
	{								\
	(pArgs) [0] = 0;						\
	(pArgs) [1] = 0;						\
	}
#endif	/* _WRS_CONFIG_SMP */

#define	WDB_CTX_TASK_INFO_SET(pArgs, tid, pid)				\
	{								\
	(pArgs) [0] = (TGT_LONG_T) (tid);				\
	(pArgs) [1] = (TGT_LONG_T) (pid);				\
	}

#define	WDB_CTX_RTP_INFO_SET(pArgs, pid)				\
	{								\
	(pArgs) [0] = (TGT_LONG_T) (pid);				\
	(pArgs) [1] = 0;						\
	}

/* macro to get context from WDB_CORE structure */

#ifdef	_WRS_CONFIG_LP64
#define	WDB_CORE_MEM_CTX_GET(memCtx) \
	    ((((ULONG) memCtx.hiCtx) << 32) + \
	     (0x00000000ffffffff & (ULONG) memCtx.ctx))
#else	/* _WRS_CONFIG_LP64 */
#define	WDB_CORE_MEM_CTX_GET(memCtx)	memCtx.ctx
#endif	/* _WRS_CONFIG_LP64 */

/* macros used to save/load external agent context */

#ifndef WDB_CTX_LOAD
#define WDB_CTX_LOAD(pRegs) _sigCtxLoad(pRegs)
#endif  /* WDB_CTX_LOAD */

#ifndef WDB_CTX_SAVE
#define WDB_CTX_SAVE(pRegs) _sigCtxSave(pRegs)
#endif  /* WDB_CTX_SAVE */

#ifndef	WDB_CTX_SETUP
#define	WDB_CTX_SETUP(pRegs, pStack, taskEntry, pArgs)			\
	_sigCtxSetup ((pRegs), (pStack), (taskEntry), (pArgs))
#endif	/* WDB_CTX_SETUP */

#ifndef WDB_CTX_RTN_VALUE_SET
#define WDB_CTX_RTN_VALUE_SET(pRegs,retVal) \
	_sigCtxRtnValSet ((pRegs),(retVal))
#endif	/* WDB_CTX_RTN_VALUE_SET */
	
/*
 * These macros are used to stop/continue all CPUs of the system except the
 * current one. Moreover, they lock/unlock interrupts on the local CPU.
 */

#ifdef	_WRS_CONFIG_SMP
#define	WDB_CPU_ALL_STOP_TIMEOUT	100	/* CPU all suspend timeout */
						/* in msecs. */

#define	WDB_CPU_ALL_STOP(level)				\
	level = INT_CPU_MICRO_LOCK ();			\
	vxdbgCpuAllSuspend (WDB_CPU_ALL_STOP_TIMEOUT, NULL, TRUE)
#define	WDB_CPU_ALL_CONTINUE(level)			\
	vxdbgCpuAllResume ();				\
	INT_CPU_MICRO_UNLOCK (level)
#else	/* _WRS_CONFIG_SMP */
#define	WDB_CPU_ALL_STOP(level)				\
	level = INT_CPU_MICRO_LOCK ()
#define	WDB_CPU_ALL_CONTINUE(level)			\
	INT_CPU_MICRO_UNLOCK (level)
#endif	/* _WRS_CONFIG_SMP */

/* This macro is used to know if the kernel is multitasking or not */

#define	WDB_KERNEL_IS_INITIALIZED()			\
	((taskIdSelf() == (TASK_ID) 0) ? FALSE : TRUE)

/* globals */
	
extern void	wdbMbufInit		(struct mbuf *, UINT32,
					 CL_BLK *, UINT32);	
extern void	wdbSioTest		(SIO_CHAN *, int, char);
extern void	wdbMdlSymSyncLibInit	(void);
extern void     wdbSysBpLibInit		(struct wdb_brkpt * pBps, UINT32 bpCnt);
extern void     wdbTaskBpLibInit	(void);
extern STATUS	wdbTaskModeInit		(UINT32 spawnStackSize,
					 UINT32 taskPriority,
					 UINT32 taskOptions,
					 UINT32 stackSize,
					 UINT32 maxRestarts,
					 UINT32 restartTime);
extern void	wdbRtpLibInit		(int priority);
extern void	wdbRtpBpLibInit		(void);
extern void	wdbTaskHookInit		(void);
extern void	wdbBpSyncLibInit	(void);
extern void	wdbDynPrintfLibInit	(UINT32 maxMsgs, size_t maxMsgLength);
extern void	wdbDynPrintfBpHandler	(long arg, REG_SET * pRegisters);
	
#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* __INCwdbOsLibh */
