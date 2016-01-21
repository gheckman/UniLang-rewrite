/* shellLibP.h - private header file for the kernel shell module */

/*
 * Copyright (c) 2003-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * license agreement.
 */

/*
modification history
--------------------
02m,21nov12,v_r  Added boolean marking shell startup (CQID Fix WIND00389134).
02l,27jun12,rlp  CQ:WIND00357688. Added shellActivate() and shellGenericCreate()
		 prototypes.
02k,14jan11,sdt  Update shellHostInitialize prototype
02j,15dec10,v_r  Moved SHELL_DFLT_TID_KEY key from shellLib.c
02i,23sep10,v_r  shellMaxSessionsSet() now returns a STATUS.
		 Added SHELL_CFG_LOGIN_RTN_BYPASS shell session parameter.
		 Removed shellSecureInit ().
02h,13jul10,v_r  No more fiddling with user IDs within the shell anymore (req
                 CQ:WIND00190686).
02g,12may10,rlp  Added VxDBG client descriptor definition.
02f,29apr10,pad  Moved extern C statement after include statements.
02e,04feb10,v_r  Do not include vxDbg header on the host.
02d,09nov09,jmp  Fixed merge failure.
02c,08sep09,v_r  Added shellMaxSessionsSet() prototype (def CQ:WIND00155318,
                 merged from 6.5 sustaining).
02f,01jul09,jmp  Moved shell function pointers from funcBindP.h.
02e,29may09,dlk  The sessionId passed to shellParserControl should be
                 capable of holding a pointer in either ILP32 or LP64.
02d,14may09,jmp  Adapted for 64-bit support
02c,26feb09,v_r  Fixed issues brought up by the LP64 review process.
		 Moved private routines from shellLib.h
02b,30jan08,v_r  Do not fiddle with path handling in the shell contexts
                 anymore (CQ:WIND00107329).
02a,04apr07,v_r  Added shellLibInit prototype (req CQ:WIND00045277).
01z,23feb07,v_r  Implemented shell output locking (req CQ:WIND00045277).
01y,19feb07,v_r  Added semaphore-reclamation hooks routine and shell context
		 list locking APIs for SMP (req CQ:WIND00045277).
01x,04aug06,dbt  Moved shellInterpEvaluate() to shellInterpLib.h
                 (CQ:WIND00060713 ).
01w,23nov05,bpn  Added isLocked field (SPR#114137).
01v,14feb05,bpn  Moved shellPromptFormatSet() prototype to shellPromptLib.h
01u,01feb05,bpn  Added shellPromptFormatSet() prototype.
01t,10jan05,bpn  Removed dependencies with dbgLib.o.
01s,23sep04,bpn  Updated include files.
01r,28jul04,bpn  Added APIs from shellLib.h.
01q,25may04,bpn  Added SHELL_LKUP_PG_KEY string.
01p,11may04,bpn  Added fgndShellId field to SHELL_CTX structure.
01o,15apr04,bpn  Added isBackground field to SHELL_CTX structure.
01n,07apr04,bpn  Export shellConsoleTaskId value.
01m,26mar04,bpn  Added errnoValue field to SHELL_CTX structure.
01l,28jan04,bpn  Added several fields to SHELL_CTX structure to fix I/O
                 redirection bugs.
01k,14jan04,bpn  Added inputLine field to SHELL_CTX structure to fix memory
                 leaks.
01j,28oct03,bpn  Moved SHELL_USER_DATA structure to shellDataLibP.h. Removed
                 shellLedCompletion() prototype (local function now).
01i,24oct03,bpn  Added shellLedCompletion() prototype.
01h,22sep03,bpn  Added shellInterpEvaluate() prototype.
01g,25jun03,bpn  Removed shellHistSize field from SHELL_CTX structure.
01f,19may03,bpn  Add the user data structure definition.
01e,17apr03,lcs  Add routines to configure shell environment.
01d,08apr03,bpn  Added fields to the shell_ctx structure to detect a shell task
                 restart and to avoid saving user/passwd several times.
01c,12mar03,lcs  Added support for host shell.
01b,10mar03,bpn  Added interpreter switch mechanism. Changed SHELL_CONTEXT 
		 structure name to SHELL_CTX.
01a,20feb03,bpn  Written.
*/

#ifndef __INCshellLibPh
#define __INCshellLibPh

/* Includes */

#ifndef HOST
#include <ioLib.h>
#include <remLib.h>
#include <private/vxdbgLibP.h>
#else
#include <host.h>
#include <shell.h>
#endif

#include <ledLib.h>
#include <lstLib.h>

#include <shellInterpLib.h>
#include <shellLib.h>
#include <private/shellInternalLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define SHELL_LKUP_PG_KEY	    "_WRS_lkupPgSz"
#define SHELL_DFLT_TID_KEY	    "_WRS_dftTask"

#define SHELL_CFG_LOGIN_RTN_BYPASS  "LOGIN_RTN_BYPASS"
#define LOGIN_RTN_BYPASS_SPEC	    (SHELL_CFG_LOGIN_RTN_BYPASS "=on")

/*
 * Ensure mutual exclusion when accessing the shell context list. This is
 * defined for the target only, as there is no need for it on the host now. It
 * can also be used as a debugging aid by adding checks for the return value.
 * Since the semaphore is static, we do not check the return values of the
 * semLib APIs (as a failure here would mean things are very wrong already).
 */

#ifdef HOST
#define SHELL_CONTEXT_LIST_LOCK
#define SHELL_CONTEXT_LIST_UNLOCK
#else
#define SHELL_CONTEXT_LIST_LOCK     shellContextListLock ()
#define SHELL_CONTEXT_LIST_UNLOCK   shellContextListUnlock ()
#endif

/* Typedefs */

typedef STATUS	(* SHELL_LOGIN_RTN)	(void * loginParam, UINT32 options,
					 char * pUserName, size_t nameLength,
					 char * pUserPasswd,
					 size_t passwdLength);
typedef void	(* SHELL_LOGOUT_RTN)	(void * logoutParam);

typedef struct shell_inline_node
    {
    NODE	node;
    char *	inputLine;	/* buffer for the input line */
    } SHELL_INLINE_NODE;

typedef struct shell_ctx_login
    {
    SHELL_LOGIN_RTN	loginFunc;	/* shell login function */
    SHELL_LOGOUT_RTN	logoutFunc;	/* shell logout function */
    void *		loginParam;	/* param. passed to login function */
    void *		logoutParam;	/* param. passed to logout function */
    } SHELL_CTX_LOGIN;

typedef struct shell_ctx_io
    {
    int		    shellStdin;		/* standard stdin */
    int		    shellStdout;	/* standard stdout */
    int		    shellStderr;	/* standard stdout */
    } SHELL_CTX_IO;

typedef struct shell_ctx_values
    {
    const char *    config;		/* configuration string */
    SHELL_CTX_LOGIN login;		/* login stucture */
    SHELL_CTX_IO    io;			/* io structure */
    BOOL	    isInteractive;	/* interactive or script? */
    } SHELL_CTX_VALUES;

typedef struct shell_ctx_compat
    {
    SHELL_CTX_VALUES	initial;	/* initial values */ 
    SHELL_CTX_VALUES	current;	/* initial values */ 
    BOOL		loginAccess;	/* connection with a login? */
    } SHELL_CTX_COMPAT;

typedef void (* SHELL_RES_RELEASE_HOOK) (SHELL_ID shellId, BOOL force);

/* The shell context structure */

typedef struct shell_ctx
    {
    NODE	    node;
    const char *    taskName;		/* shell task name */
    SHELL_INTERP_CTX * pInterpCtx;	/* interpreter parameters */
    SHELL_INTERP *  pInterpSwitch;	/* next interpreter to use */
    SHELL_ID	    bgndShellId;	/* background session Id */
    SHELL_ID	    fgndShellId;	/* foreground session Id */
    LED_ID	    ledId;		/* line editor ID */
    TASK_ID	    taskId;		/* shell task ID */
#ifndef HOST
    SEM_ID	    outputSemId;	/* output locking semaphore */
#endif
    LIST            userData;           /* list of the user data */
    LIST	    interpCtxLst;	/* list of interp context */
    LIST	    ioFileDescLst;	/* list of IO file descriptors */
    LIST	    inputLineLst;	/* list input line buffers */
    SHELL_CTX_VALUES	initial;	/* initial values */ 
    SHELL_CTX_VALUES	current;	/* initial values */ 
    SHELL_CTX_COMPAT	compatible;	/* for compatibility */
    BOOL	    loginAccess;	/* connection with a login? */
    int		    errnoValue;		/* errno value */
    size_t	    taskStackSize;	/* shell task stack size */
    BOOL	    isAbortReq;		/* abort requested? */
    BOOL	    isRestarted;	/* task restarted? */
    BOOL	    isBackground;	/* background session? */
    BOOL	    isLocked;		/* locked session? */
    BOOL	    isShellStartup;	/* before interactive mode is enabled */
    } SHELL_CTX;

/* global variables */

extern TASK_ID	shellConsoleTaskId;

#ifndef HOST
extern VXDBG_CLNT_ID   pDbgClnt;	/* VxDBG client descriptor for shell */

extern STATUS	(* _func_shellDbgStackTrace) (TASK_ID taskId,
					      const char * errorStr);
extern void	(* _func_shellDbgCallPrint) (INSTR * callAdrs, INSTR * funcAdrs,
                                            int nargs, _Vx_usr_arg_t * args,
					    TASK_ID taskId, BOOL isKernelAdrs);
extern STATUS	(* _func_shellBpByIdRemove) (VXDBG_BP_ID bpId);
extern void	(* _func_shellExcPrint)	(TASK_ID taskId, const char * fmt, ...);
#endif	/* !HOST */

/* Function Declarations */

extern STATUS	    shellLibInit	(void);
extern STATUS	    shellLogout2	(SHELL_ID shellId,
					 const char * errorStr);
extern STATUS	    shellScriptNoAbort	(void);
extern void	    shellPromptPrint	(SHELL_ID shellId);
extern STATUS	    shellActivate (SHELL_ID shellId);
extern SHELL_ID	    shellBackgroundInit	(const char * interpName,
					 const char * evalString);
extern char *	    shellBackgroundRead	(LIST * pMemList, INT32 memFlags);
extern UINT	    shellLineLenGet	(void);
extern STATUS	    shellExec		(SHELL_CTX * pShellCtx);
extern void	    shellExitWrapper	(int code);
extern SHELL_ID	    shellGenericCreate	(const char * config, size_t stackSize,
					 const char * shellName,
					 char ** pShellName, BOOL interactive,
					 BOOL loginAccess, int fdin, int fdout,
					 int fderr);
extern STATUS	    shellConsoleInit	(const char * config, size_t stackSize,
					 const char * shellName, 
					 char ** pShellName);
extern void	    shellContextFinalize (SHELL_CTX * pShellCtx);
extern SHELL_CTX *  shellContextInit	(const char * config, size_t stackSize,
					 const char * shellName,
					 BOOL isForEvaluation,
					 BOOL interactive);
extern void	    shellLoginInstall (SHELL_LOGIN_RTN logRtn, void * logVar);
extern void	    shellLogoutInstall (SHELL_LOGOUT_RTN logRtn, void * logVar);
extern STATUS	    shellLogout (SHELL_ID shellId);

#ifdef HOST
extern STATUS	    shellHostInitialize	(SHELL_CTX * pShellCtx,
					 struct timeval * pStdinPollTimeout,
					 void (* eventPoll) (void));
extern void	    shellContextHostFinalize	(SHELL_CTX * pShellCtx);
#else
extern STATUS	    shellContextListLock	    (void);
extern STATUS	    shellContextListUnlock	    (void);
extern SHELL_CTX *  shellFromTaskParentContextGet   (TASK_ID taskId);
extern STATUS	    shellResourceReleaseHookAdd	    (SHELL_RES_RELEASE_HOOK hk);
extern STATUS	    shellMaxSessionsSet (INT32 maxSessions);
#endif
extern STATUS	    shellParserControl (UINT32 remoteEvent, ULONG sessionId,
					UINT32 slaveFd, VOIDFUNCPTR logoutFunc);

extern void     shellCompatibleSet (BOOL isCompatible);
extern void     shellTaskDefaultOptionsSet (int taskOpt);
extern int      shellTaskDefaultOptionsGet (void);
extern void     shellTaskDefaultStackSizeSet (size_t stackSize);
extern size_t	shellTaskDefaultStackSizeGet (void);
extern void     shellTaskDefaultPrioritySet (int priority);
extern int      shellTaskDefaultPriorityGet (void);
extern void     shellTaskDefaultBaseNameSet (const char * taskBaseName);
extern char *   shellTaskDefaultBaseNameGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellLibPh */
