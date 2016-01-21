/* wdbLibP.h - private header file for remote debug agent */

/*
 * Copyright (c) 1994-1995,1998,2001-2000,2003-2007,2009-2012,
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
02s,07feb12,rlp  CQ:WIND00331131. Added wdbIsReady variable.
02r,08apr11,rlp  Added wdbIoctl prototype.
02q,04mar11,jmp  Fixed foundation/wdbagent-ptrace build.
02p,31jan11,rlp  System mode support for LP64.
02o,25oct10,rlp  Added a variable to indicate if WDB is enabled (WIND00227819).
02n,29jul10,pad  Moved extern C statement after include statements.
02m,07may10,jmp  Added wdbRtMemInit().
02m,06may10,jmp  Added wdbSharedBuffer & wdbSharedBufferSize,
		 and removed obsolete wdbRegsBuffer & wdbRegsBufferSize.
02l,27apr10,jmp  Added _func_wdb[Task|Extern]CoprocRegs[Set|Get],
		 and wdb[Task|Extern]CoprocRegLibInit.
02k,26feb10,rlp  Added more private prototypes.
02j,10dec09,rlp  Modified _func_wdbTaskBpByIdRemove function pointer.
02i,20oct09,rlp  Added the WDB_CTX_ARGS_FILL macro to fill context structure,
                 Added WDB_ALL_CTXS for commands that apply to all contexts.
02h,26jul07,rlp  Added _func_wdbTaskBpByIdRemove function pointer to remove a
                 dependency between the agents (CQ:WIND00099423).
02g,26jun07,tbu  Added 64 bit support
          + p_b  completed support
02f,02feb07,tbu  Added DISCONNECT_ON_CONNECT
02e,30oct06,rlp  Modified to use VxDBG library (REQ00007655).
02d,08dec05,dbt  Added wdbCommMtuGet() prototype.
02c,06dec05,dbt  Added WDB_NTOHx and WDB_HTONx macros
02b,28nov05,dbt  Removed wdbExternCmdRun().
		 Added macros to isolate code of external and task mode agents
02a,07nov05,dbt  Updated wdbConnectHookAdd() prototype.
		 Removed wdbDisconnectHookAdd().
		 Removed wdbExternRegsSet() & wdbExternRegsGet() prototypes.
		 Removed wdbMemRtLibInit() prototype.
01z,01aug05,bpn  Add new register buffer.
01y,28may04,elg  Add new function pointers.
01x,08apr04,elg  Define wdbMemChunk.
		 Remove obsolete type WDB_REG_SET_TYPE.
01w,13jan04,elg  Add prototype of wdbCnctModePost().
01v,26sep03,tbu  Moved definition of wdbMbufInit & wdbSioTest  to wdbOsLib.h
01u,15sep03,elg  Add definition of wdbSioTest().
01t,27aug03,elg  Add declarations of context event routines.
01s,15jul03,pch  Conditional compilation cleanup
01r,26jun03,elg  Add definition of wdbSuspendSystem() as extern routine.
01q,27feb03,elg  Merge file with BSD.
01p,04feb03,elg  Add WDB merged protocol.
01o,20jul00,dbt  Added wdbExternCmdRun() prototype.
01n,03feb00,elg  Fix component dependencies problems.
01m,31jan00,dbt  Added wdbPdUpdateNotify() prototype.
01l,21jan00,dbt  Added WDB_USR_SVC_STRUCT structure.
01k,25oct99,elg  Rename PD creation and deletion hooks.
01j,15oct99,dbt  added wdbConnectHookAdd() and wdbDisconnectHookAdd()
                 prototypes.
01i,19aug99,elg  Add hooks for protection domains.
01h,29jun99,elg  Add WDB_CORE support.
01g,25apr02,jhw  Added C++ support (SPR 76304).
01f,14sep01,jhw  Added wdbExternRegsGet() and wdbExternRegsSet() function
                 prototypes.
		 Removed __STDC__ precompiler conditional.
01e,11jun98,dbt  removed wdbTgtHasFpp() prototype.
01d,03jun95,ms	 added prototype for wdbTargetIsConnected()
01c,05apr95,ms   new data types.
01b,06feb95,ms	 removes wdbRpcLib specific things.
01a,20sep94,ms   written.
*/

#ifndef __INCwdbLibPh
#define __INCwdbLibPh

/* includes */

#include <wdb/wdb.h>
#include <wdb/wdbRtIfLib.h>
#include <wdb/wdbCommIfLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define DISCONNECT_ON_CONNECT		1

#define WDB_STATE_EXTERN_RUNNING        1

#define	WDB_IS_NOW_EXTERNAL()		(wdbMode & WDB_MODE_SYSTEM)

#ifndef	IS_WDB_ENABLED
#define	IS_WDB_ENABLED()		(wdbIsAlwaysEnabled)
#endif	/* IS_WDB_ENABLED */

#ifndef IS_WDB_READY 
#define IS_WDB_READY()			(wdbIsReady)
#endif  /* IS_WDB_READY */

#define	wdbSuspendSystemHere(callBack,callBackArg)			\
    if (_func_wdbSuspendSystem != NULL)					\
	_func_wdbSuspendSystem (NULL, (callBack), (callBackArg))

#define	wdbSuspendSystem(pRegSet,callBack,callBackArg)			\
    if (_func_wdbSuspendSystem != NULL)					\
	_func_wdbSuspendSystem ((pRegSet), (callBack), (callBackArg))

#define	wdbResumeSystem()						\
    if (_func_wdbResumeSystem != NULL)					\
	_func_wdbResumeSystem ()

/* Byte swapping macros */

/*
 * The endianness of the networks packets is always BIG, so is the target is 
 * BIG no swap is needed 
 */

#if	_BYTE_ORDER == _BIG_ENDIAN
#define	WDB_NTOH64(x)	(x)
#define	WDB_HTON64(x)	(x)
#define	WDB_NTOH32(x)	(x)
#define	WDB_HTON32(x)	(x)
#define	WDB_NTOH16(x)	(x)
#define	WDB_HTON16(x)	(x)
#else   /* BYTE_ORDER == BIG_ENDIAN */ 

#define WDB_NTOH64(x)	SWAB_64(x)
#define WDB_HTON64(x)	SWAB_64(x)
#define WDB_NTOH32(x)	SWAB_32(x)
#define WDB_HTON32(x)	SWAB_32(x)
#define WDB_NTOH16(x)	SWAB_16(x)
#define WDB_HTON16(x)	SWAB_16(x)

/* Swap of eight bytes : ABCDEFGH becomes HGFEDCBA */

#define SWAB_64(x)	((((x) & 0x00000000000000ffLL) << 56) | \
			 (((x) & 0x000000000000ff00LL) << 40) | \
			 (((x) & 0x0000000000ff0000LL) << 24) | \
			 (((x) & 0x00000000ff000000LL) << 8)  | \
			 (((x) & 0x000000ff00000000LL) >> 8)  | \
			 (((x) & 0x0000ff0000000000LL) >> 24) | \
			 (((x) & 0x00ff000000000000LL) >> 40) | \
			 (((x) & 0xff00000000000000LL) >> 56))	

/* Swap of four bytes : ABCD becomes DCBA */

#define SWAB_32(x)	(((UINT32)((x) & 0x000000ff) << 24) | \
			 ((UINT32)((x) & 0x0000ff00) << 8)  | \
			 ((UINT32)((x) & 0x00ff0000) >> 8)  | \
			 ((UINT32)((x) & 0xff000000) >> 24))

/* Swap of two bytes : AB becomes BA */

#ifdef SWAB_16
#undef SWAB_16
#endif

#define SWAB_16(x)	((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))

#endif	/* BYTE_ORDER == BIG_ENDIAN */

#define WDB_ACTION_STOP_MASK	(WDB_ACTION_STOP | WDB_ACTION_ALL_STOP | \
					WDB_ACTION_SYS_STOP)

/* Convert a WDB action type to a VXDBG_BP_ACTION type */

#define WDB_ACTION_TYPE_CONV(t)	(t)

/* Convert a VxDBG errno value to a WDB error value */

#define	WDB_RETURN_VALUE_GET(rtn)				\
		((rtn == OK) ? WDB_OK : ((errno & ~M_vxdbgLib) + 0x500))

#define WDB_ALL_CTXS		-1L     /* Command applies to all contexts */

/* Fill a context structure */

#define	WDB_CTX_ARGS_FILL(pArgs, pCtx)					\
	{								\
	int	ix;							\
									\
	for (ix = 0; ix < (int) (pCtx)->numArgs; ix++)			\
	    (pArgs) [ix] = (pCtx)->args [ix];				\
	for (ix = (pCtx)->numArgs; ix < WDB_CTX_MAX_ARGS; ix++)		\
	    (pArgs) [ix] = 0;						\
	}

/* data types */

typedef enum wdb_cont_type
    {
    WDB_STEP             = 0x0001,
    WDB_STEP_OVER        = 0x0002,
    WDB_STEP_RANGE       = 0x0004
    } WDB_CONT_TYPE;

typedef struct wdb_usr_svc		/* user service structure */
    {
    FUNCPTR	func;			/* service entry point */
    UINT32 	svcId;			/* service ID */
    } WDB_USR_SVC;

/* agent variables */

extern UINT32  		wdbCommMtu;
extern UINT32		wdbAvailOptions;
extern UINT32		wdbMode;
extern BOOL		wdbOneShot;
extern BOOL		wdbIsAlwaysEnabled;
extern UINT32		wdbAvailModes;
extern BOOL		wdbIsInitialized;
extern BOOL		wdbIsReady;
extern char *		wdbSharedBuffer;
extern UINT32		wdbSharedBufferSize;

#ifndef _WRS_ARCH_NO_SYSTEM_MODE_AGENT
extern void		(*_func_wdbResumeSystem) (void);
extern void		(*_func_wdbExternNotifyHost) (void);
extern void		(*_func_wdbExternRcvHook) (UINT32 arg);
extern void		(*_func_wdbSuspendSystem) (WDB_IU_REGS * pRegs,
					void (*callBack) (_Vx_usr_arg_t arg),
					_Vx_usr_arg_t arg);
extern STATUS		(*_func_wdbExternEnterHookAdd) (void (*hook) ());
extern STATUS		(*_func_wdbExternExitHookAdd) (void (*hook) ());
#endif  /* !_WRS_ARCH_NO_SYSTEM_MODE_AGENT */

extern STATUS		(*_func_wdbTaskBpByIdRemove) (ULONG bpId);
extern UINT32		(*_func_wdbTaskCoprocRegsSet) (WDB_CTX * pContext,
						       UINT32 type,
						       char * pRegs);
extern UINT32		(*_func_wdbTaskCoprocRegsGet) (WDB_CTX * pContext,
						       UINT32 type,
						       char ** ppRegs);
extern UINT32		(*_func_wdbExternCoprocRegsSet) (WDB_CTX * pContext,
							 UINT32 type,
							 char * pRegs);
extern UINT32		(*_func_wdbExternCoprocRegsGet) (WDB_CTX * pContext,
							 UINT32 type,
							 char ** ppRegs);

extern void *		pWdbXport;
extern WDB_COMM_IF *	pWdbCommIf;
extern void *	 	pWdbClnt;	/* VxDBG client descriptor for WDB */

/* function prototypes */

extern void	wdbInfoGet	 	(WDB_AGENT_INFO * pInfo);
extern void	wdbNotifyHost		(void);
extern BOOL	wdbTargetIsConnected	(void);

extern int	wdbIoctl	 	(int function, long arg);
extern STATUS	wdbModeSet	 	(INT32 newMode);
extern BOOL	wdbIsNowExternal	(void);
extern BOOL	wdbRunsExternal		(void);
extern BOOL	wdbIsNowTasking		(void);
extern BOOL	wdbRunsTasking		(void);
extern void	wdbCtxCreateNotify	(void * pNode);
extern void	wdbCtxDeleteNotify	(void * pNode);
extern void	wdbCtxEvtLibInit	(void);
extern void	wdbCtxStartEventGet	(void * pNode, WDB_EVT_DATA * pEvtData);
extern void	wdbCtxExitEventGet	(void * pNode, WDB_EVT_DATA * pEvtData);
extern void	wdbCtxExitNotifyHook	(WDB_CTX ctx, UINT32 exitCode,
							UINT32 errnoVal);
extern STATUS	wdbConnectHookAdd	(BOOL connect, FUNCPTR connectHook);
extern void	wdbCmdLoop		(void);
extern void	wdbRtLibInit		(WDB_RT_IF * pWdbRtIf);
extern void	wdbRtMemInit		(WDB_RT_IF * pWdbRtIf);

#ifndef	_WRS_ARCH_NO_SYSTEM_MODE_AGENT
extern void	wdbCnctModePost		(_Vx_usr_arg_t mode);
extern void	wdbExternLibInit	(void);
extern STATUS	wdbExternRegLibInit	(void);
extern STATUS	wdbExternCoprocRegLibInit (void);
extern STATUS	wdbExternEnterHookAdd	(void (*hook) ());
extern STATUS	wdbExternExitHookAdd	(void (*hook) ());
#endif  /* !_WRS_ARCH_NO_SYSTEM_MODE_AGENT */

extern STATUS	wdbModeSetHookAdd	(void (*hook) (int mode));
extern STATUS	wdbTaskRegLibInit	(void);
extern STATUS	wdbTaskCoprocRegLibInit	(void);
extern UINT32	wdbCommMtuGet		(void);
extern void	wdbCommIfEnable		(BOOL enable);

/* globals */

extern WDB_IU_REGS *    pWdbExternSystemRegs;

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbLibPh */
