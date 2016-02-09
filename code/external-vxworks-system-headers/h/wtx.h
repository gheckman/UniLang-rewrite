/* wtx.h - wtx protocol header file */

/*
 * Copyright (c) 1994-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05t,27may10,pad  Moved extern C statement after include statements.
05s,12oct04,jeg  added wtxLastRuntimeErrorGet() API declaration
05r,03sep04,jeg  added wtxTargetHasDspGet() declarations.
05q,18jun04,x_p  Add addOptions to wtxProcessCreate
05p,16mar04,x_p  Handle I/O redirection in wtxProcessCreate
05o,26feb04,mil  Added SPE support for PPC85XX.
05n,15apr03,sn   added wtxDemanglerStyleGet, obsoleted wtxDefaultDemanglerStyle
05m,29aug03,x_p  Changed prototype
05l,04mar03,fle  fixed (again ?) wtxEnvironRegistryOptionsGet() declaration
05k,21feb03,fle  fixed wtxEnvironRegistryOptionsGet() declaration
05j,18feb03,p_b  merge from T22-latest
05i,12feb03,elg  Fix compilation error.
05h,13dec02,p_b  changed TGT_XXX by WTX_TGT_XXX
05g,21nov02,p_b  merging margaux/T3, 64 bits support
05f,07nov02,fle  removed wtxSymAddWithGroup ()
05e,18mar02,x_p  Updated wtxPdCreate for handling env vars
05d,24jan02,x_p  Added wtxPdInfoSet / Get
05c,27nov01,x_p  Added wtxPdTasksListGet
05b,22aug01,x_p  Merge from bsdos.temp
05a,12sep00,c_c  Added wtxTargetToolNameGet, wtxTargetBspShortNameGet,
                 wtxTargetRtNameGet. Removed wtxTargetRtTypeGet.
04z,08aug00,mts  Added wtxLoadModeGet
04z,08aug00,mts  Added wtxLoadModeGet
04y,18may00,fle  added wtx log options for registry to
                 wtxEnvironRegistryOptionsGet()
04x,06apr00,fle  added wtxToolOnHostAttach() that attaches to a target server
                 registered on a remote rgistry
04w,13mar00,p_b  handled load and run facility.
04v,03mar00,fle  renamed wtxTgtsvrLogGet() into wtxTsLogGet() for API
                 consistency
04u,17feb00,fle  added wtxLogGet() routine
04t,01feb00,fle  made pFunc parameter of wtxAsyncNotifyEnable() be a
                 WTX_EVENT_HANDLER rather than a FUNCPTR
04s,26jan00,dbt  Added user service routines prototypes.
04r,15dec99,p_b  fixed wrong typos in comments.
04q,26nov99,fle  made wtxCpuInfoGet() return a char pointer, not a const char
                 pointer aymore
04p,26oct99,fle  moved registry related routines declarations into
                 wtxRegistry.h
04o,21oct99,p_b  Removed wtxEach(),wtxServiceAdd(). Renamed wtxModuleListFree()
                 in wtxObjModuleListFree(). Fixed wrong comments in wtxContext..
                 structure definitions. (Beware that it explicitly appears in
                 the documentation). Changed many "char *" to "const char *".
                 Removed wtxSymAddWithGroup (). Updated wtxPdCreate() profile.
                 Renamed wtxObjModuleList() in wtxObjModuleListGet().
04n,15oct99,fle  exported wtxDescDuplicate() since it is now used in several
                 files
		 + history cleanup
04m,13oct99,fle  made include of wtxRegistry.h into ifdef HOST
04l,07oct99,fle  added new registry related APIs declarations
04k,06oct99,pad  Replaced WTX_SYMBOL_TYPE with UINT32 in wtxSym...() routines.
04j,04oct99,pad  Added prototype of wtxSymRegister().
04i,21sep99,c_c  Added Context Stop service.
04h,27aug99,fle  added wtxPdCurrentSet(), wtxPdCurrentGet() and wtxPdRemove()
                 routines declarations
		 + changed wtxPdCreateAt() into wtxPdCreate()
04g,22jul99,p_b  changed wtxSymFind, wtxSymListGet, wtxObjModuleListGet apis.
04f,20jul99,fle  memory leaks fixes
04e,19jul99,fle  made the pdId parameters be WTX_TGT_ADDR_T and not UINT32 anymore
04d,16jul99,p_b  added wtxModuleListFree (). Change wtxSymListFree () interface.
04c,16jul99,c_c  Modified wtxMemMove.
04b,09jul99,fle  moved N_DASM_INST_DEFAULT from here to wtxtypes.h
04a,08jul99,p_b  Added wtxVioLink () & wtxVioUnlink (). Removed wtxConsoleXxx().
03z,07jul99,p_b  Changed wtxSymListByModuleIdGet & wtxSymListByModuleNameGet.
03y,06jul99,c_c  Added an option to wtxContextKill.
03x,05jul99,p_b  Modified wtxSymFind, wtxSymListGet, wtxObjModuleListGet.
03w,05jul99,c_c  Implemented PD context definition.
03v,02jul99,c_c  Removed WTX_EVENTPOINT_LIST references.
03u,01jul99,c_c  Modified wtxObjModuleLoad return value.
03t,30jun99,fle  added wtxPdInfoQGet() routine declaration
03s,25jun99,fle  added pdIds to all wtxMem calls
03r,21jun99,fle  added wtxFreeAdd() routine declaration
03q,01jun99,c_c  WTX for Protection Domain implementation: moved all type
                 definition to wtxtypes.h
03p,25may99,fle  added WTX_SVR_TYPE enum
03o,23feb99,c_c  Implemented an API to get the target IP address (SPR #25044).
03n,22sep98,l_k  Removed wtxFindExecutable.
03m,21sep98,l_k  Implement wtxFindExecutable.
03l,18sep98,pcn  Implement wtxObjModuleInfoAndPathGet.
03k,18aug98,pcn  Use WTX_MSG_EVTPT_LIST_2.
03j,20jul98,pcn  Added evtptNum and toolId in the wtxEventpointListGet return
                 list.
03i,06jul98,pcn  Removed wtxObjModuleUndefSymAdd from API.
03h,19jun98,pcn  Added wtxObjModuleLoadStart, wtxObjModuleLoadProgressReport,
                 wtxObjModuleLoadCancel.
03g,11jun98,pcn  Added an input parameter at wtxEventListGet.
03f,09jun98,jmp  added wtxAsyncResultFree and wtxAsyncEventGet().
03e,03jun98,pcn  Added 2 requests: wtxSymListByModuleNameGet and
                 wtxSymListByModuleIdGet.
03d,25may98,pcn  Changed wtxTsLock in wtxTsTimedLock, wtxEventpointList_2 in
                 wtxEventpointListGet, wtxObjModuleUnload_2 in
                 wtxObjModuleUnloadByName.
03c,30apr98,dbt  added wtxHwBreakpointAdd and wtxEventpointAdd.
03b,28apr98,pcn  Removed wtxCommandSend.
03a,23apr98,fle  added CPU name retrieving to wtxCpuInfoGet
02z,21apr98,fle  added wtxCpuInfoGet()
02y,26mar98,pcn  WTX 2: added a new parameter in wtxLogging.
02x,03mar98,fle  got rid of wtxRegistryPing() function declaration
02w,02mar98,pcn  WTX 2: moved WTX_LD_M_FILE_DESC in wtxMsg.h. Added
                 WTX_EVTPT_LIST_2 definition. Added wtxAsyncNotifyEnable,
                 wtxAsyncNotifyDisable, wtxCacheTextUpdate, wtxCommandSend,
                 wtxEventListGet, wtxEventpointList_2, wtxLogging,
                 wtxMemWidthRead, wtxMemWidthWrite, wtxObjModuleChecksum,
                 wtxObjModuleLoad_2, wtxObjModuleUnloa wtxUnregisterForEvent.
                 Changed wtxTargetRtTypeGet, wtxTargetCpuTypeGet return type.
02v,29jan98,fle  added wtxRegistryPing() declaration
		 + added WTX_REGISTRY_PING_INTERVAL definition
02u,28jan98,c_c  Packed all wtxEvtxxxStringGet routines into one.
01a,06oct94,p_m  written.
*/

#ifndef __INCwtxh
#define __INCwtxh	1

#ifdef HOST
#include <setjmp.h>
#else
#include <vxWorks.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bootLib.h>
#endif /* HOST */

#include <wtxtypes.h>
#include <wtxmsg.h>
#include <wtxerr.h>
#include <demanglerTypes.h>
#ifdef HOST
    #include <wtxRegistry.h>
#endif /* HOST */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WTX_ALL_EVENTS		~0	/* number of events returned */
#define WTX_LOG_NO_LIMIT	0	/* no max size for the log file */
#define WTX_LOCK_FOREVER	0  /* lock indefinitely the target server */

#define LOAD_MODULE_INFO_ONLY   0x1000000       /* module synchronization */

#define WTX_TRY(hWtx) \
{\
	WTX_HANDLER_T errHandler;\
	jmp_buf jumpBuf;\
\
	wtxErrClear (hWtx);\
	errHandler = wtxErrHandlerAdd (hWtx, &wtxErrExceptionFunc, &jumpBuf);\
	if (setjmp (jumpBuf) == 0)

#define WTX_CATCH(hWtx, errCode) else if (wtxErrGet (hWtx) == errCode)
#define WTX_CATCH_ALL(hWtx) else

#define WTX_TRY_END(hWtx) \
	wtxErrHandlerRemove (hWtx, errHandler);\
}

#define WTX_THROW(hWtx, errCode) wtxErrDispatch (hWtx, errCode)


#ifndef HOST
/* externals */

extern BOOT_PARAMS	sysBootParams;
#endif /* HOST */


/* function declarations */

extern char * wtxCpuInfoGet		/* get target CPU information from DB */
    (
    int		cpuNum,			/* CPU number to get info on          */
    CPU_INFO	cpuInfoType		/* CPU info type to get               */
    );

extern STATUS wtxInitialize		/* init to be called by WTX client    */
    (
    HWTX *		phWtx		/* handle to use in next API calls    */
    );

extern WTX_TGT_ADDR_T wtxPdCurrentGet	/* gets the current Protection Domain */
    (
    HWTX		hWtx		/* WTX session handler                */
    );

extern STATUS wtxPdCurrentSet		/* sets the current Protection Domain */
    (
    HWTX		hWtx,		/* WTX session handler                */
    WTX_TGT_ID_T	pdId		/* protection domain ID to be set     */
    );

extern STATUS wtxPdDelete		/* deletes given Protection Domain    */
    (
    HWTX		hWtx,		/* WTX session handler                */
    WTX_TGT_ID_T	pdId,		/* protection domain ID to delete     */
    WTX_CTX_KILL_OPT	options		/* protection domain deletion options */
    );

extern STATUS wtxProcessDelete		/* deletes given Protection Domain    */
    (
    HWTX		hWtx,		/* WTX session handler                */
    WTX_TGT_ID_T	pdId,		/* protection domain ID to delete     */
    WTX_CTX_KILL_OPT	options		/* protection domain deletion options */
    );

extern WTX_TGT_ADDR_T wtxPdKernelGet	/* get kernel Protection Domain ID    */
    (
    HWTX		hWtx		/* WTX session handler                */
    );

extern WTX_PD_DESC_Q * wtxPdInfoQGet	/* get the list of allocated PDs      */
    (
    HWTX		hWtx		/* WTX session handler                */
    );

extern STATUS wtxProbe			/* probe to see if registry is alive  */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTerminate		/* terminate use of WTX client handle */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTimeoutSet		/* set WTX timeout */
    (
    HWTX		hWtx,		/* WTX API handle */
    UINT32		msec		/* new timeout value in milliseconds */
    );

extern STATUS wtxTimeoutGet		/* get the current timeout */
    (
    HWTX		hWtx,		/* WTX API handle */
    UINT32 *		pMsec		/* pointer to timeout value in ms */
    );

extern STATUS wtxAgentModeSet		/* set the mode of the target agent */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_AGENT_MODE_TYPE	agentMode	/* debug agent mode */
    );

extern WTX_AGENT_MODE_TYPE wtxAgentModeGet	/* get agent mode */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS   wtxAsyncNotifyEnable    /* start async. event notification */
    (
    HWTX                hWtx,           /* WTX API handle */
    WTX_EVENT_HANDLER	pFunc		/* user defined function  */
    );

extern STATUS   wtxAsyncNotifyDisable   /* stop async. event notification */
    (
    HWTX                hWtx            /* WTX API handle */
    );

extern WTX_EVENT_DESC * wtxAsyncEventGet
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxAsyncResultFree
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_EVENT_DESC *	pEventDesc	/* pointer to structure to free */
    );

extern WTX_TGT_ID_T wtxBreakpointAdd	/* create a new event point */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext,
    WTX_TGT_ADDR_T	tgtAddr		/* breakpoint address */
    );

extern STATUS wtxCacheTextUpdate        /* update the target text cache */
    (
    HWTX                hWtx,           /* WTX API handle            */
    WTX_TGT_ADDR_T      addr,           /* start address             */
    UINT32              nBytes          /* number of bytes to update */
    );

extern STATUS wtxClientDataGet		/* get the client data */
    (
    HWTX		hWtx,		/* WTX API handle */
    void **		ppClientData	/* pointer to client data pointer */
    );

extern STATUS wtxClientDataSet		/* set client data */
    (
    HWTX		hWtx,		/* WTX API handle */
    void *		pClientData	/* value to associate with handle */
    );

extern STATUS wtxContextStop		/* stop execution of target context   */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext
    );

extern STATUS wtxContextCont		/* continue execution of target ctxt */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext
    );

extern WTX_CONTEXT_ID_T	wtxContextCreate /* create a context on target */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT_DESC *	pContextDesc	/* context descriptor */
    );

extern WTX_TGT_ID_T wtxContextExitNotifyAdd	/* add exit evpt notification */
    (
    HWTX		hWTx, 		/* WTX API handle */
    WTX_CONTEXT *	pContext
    );

extern STATUS wtxContextKill		/* kill a target context */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext,
    UINT32		options		/* option for the kill operation */
    );

extern STATUS wtxContextResume		/* resume execution of a target ctxt */
    (
    HWTX hWtx,				/* WTX API handle                    */
    WTX_CONTEXT *	pContext
    );

extern STATUS wtxContextStep		/* single step exec of target ctxt */
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_CONTEXT *	pContext,
    WTX_TGT_ADDR_T	stepStart,	/* stepStart PC value              */
    WTX_TGT_ADDR_T	stepEnd		/* stepEnd PC value                */
    );

extern WTX_CONTEXT_STATUS wtxContextStatusGet	/* get status of a context */
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_CONTEXT *	pContext
    );

extern STATUS wtxContextSuspend		/* suspend a target context */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext
    );

extern STATUS wtxErrClear		/* clear any error for the tool */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern WTX_ERROR_T wtxErrGet		/* return the last error for a handle */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxErrSet			/* set the error code for the handle */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    UINT32		errCode		/* error value to set                */
    );

extern const char * wtxErrMsgGet	/* fetch last WTX API error string */
    (
    HWTX		hWtx		/* WTX API handle                  */
    );

extern const char * wtxErrToMsg		/* convert error code to string */
    (
    HWTX		hWtx,		/* WTX API handle               */
    WTX_ERROR_T		errCode		/* error code to convert        */
    );

extern STATUS wtxErrDispatch		/* dispatch error with supplied code */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    WTX_ERROR_T		errCode		/* error code to register            */
    );

extern BOOL32 wtxErrExceptionFunc	/* a function to handle an error     */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    void *		pClientData,	/* pointer to a jump buffer          */
    void *		pCallData	/* error code to return via setjmp() */
    );

extern WTX_HANDLER_T wtxErrHandlerAdd	/* add an error handler      */
    (
    HWTX		hWtx,		/* WTX API handle            */
    WTX_HANDLER_FUNC	pFunc,		/* function to call on error */
    void *		pClientData	/* data to pass function     */
    );

extern STATUS wtxErrHandlerRemove	/* remove error handler for WTX handle*/
    (
    HWTX		hWtx,		/* WTX API handle                     */
    WTX_HANDLER_T	pHandler	/* error handler                      */
    );

extern STATUS wtxEventAdd		/* send an event to the target server */
    (
    HWTX		hWtx,		/* WTX API handle                     */
    const char *	event, 		/* event string to send               */
    UINT32		addlDataLen,	/* length of addl data block in bytes */
    const void *	pAddlData	/* pointer to additional data         */
    );

extern WTX_EVENT_DESC * wtxEventGet	/* get an event from the target */
    (
    HWTX		hWtx		/* WTX API handle               */
    );

extern WTX_EVENT_NODE * wtxEventListGet /* get all the events in one call */
    (
    HWTX                hWtx,           /* WTX API handle                 */
    UINT32              nEvents         /* number of events to return     */
    );

extern WTX_TGT_ID_T wtxEventpointAdd		/* create a new event point */
    (
    HWTX                hWtx,		/* WTX API handle           */
    WTX_EVTPT *		pEvtpt		/* eventpoint descriptor    */
    );

extern WTX_TGT_ID_T wtxHwBreakpointAdd	/* create a new hardware breakpoint */
    (
    HWTX                hWtx,		/* WTX API handle                   */
    WTX_CONTEXT *	pContext,
    WTX_TGT_ADDR_T	tgtAddr,	/* breakpoint address               */
    WTX_TGT_INT_T	type		/* access type (arch dependant)     */
    );
extern STATUS wtxEventpointDelete	/* delete eventpoint from the target */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    WTX_TGT_ID_T	evtptId		/* ID of eventpoint to delete        */
    );

extern WTX_EVTPT_LIST * wtxEventpointListGet	/* list event points on TS */
    (
    HWTX		hWtx			/* WTX API handle */
    );

extern STATUS wtxFileClose		/* close a file on the target server */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    INT32		fileDescriptor	/* file to close descriptor          */
    );

extern WTX_TGT_ID_T wtxFileOpen		/* open a file on the target server */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    const char *	fileName, 	/* file name                        */
    WTX_OPEN_FLAG	flags,		/* unix style flags                 */
    INT32		mode,		/* unix style mode                  */
    INT32		channel		/* channel id for redirection       */
    );

extern STATUS wtxFreeAdd		/* adds a pointer to free list        */
    (
    HWTX		hWtx,		/* WTX session handler                */
    void *		pToFree,	/* pointer to add to the free list    */
    FUNCPTR		pFreeRtn,	/* pointer to freeing routine         */
    void *		pMsgToFree,	/* message pointer containing pToFree */
    FUNCPTR		pMsgFreeRtn	/* routine to use to free pMsgToFree  */
    );

extern WTX_CONTEXT_ID_T	wtxFuncCall	/* call a function on the target    */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TASK_CONTEXT_DEF *pTaskContextDef	/* pointer to call descriptor */
    );

extern STATUS wtxDirectCall		/* call func on target within agent */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ADDR_T		entry,		/* function address                 */
    void *		pRetVal,	/* pointer to return value          */
    UINT32		argc,		/* argument count                   */
    ...					/* argument list                    */
    );

extern WTX_GOPHER_TAPE * wtxGopherEval	/* evaluate Gopher string on target */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* targeted PD                      */
    const char *	inputString	/* gopher program to evaluate       */
    );

extern STATUS wtxLogging		/* WDB/WTX logging facilities */
    (
    HWTX		hWtx,		/* WTX API handle             */
    int			type,		/* WDB or WTX logging         */
    int			action,		/* logging ON or OFF          */
    const char *	fileName,	/* logging file name          */
    int			maxSize,	/* log file max size          */
    const char *	filter		/* request filter             */
    );

extern WTX_MEM_INFO * wtxMemInfoGet	/* get info about memory pool       */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId		/* PD into which we want to operate */
    );

extern STATUS wtxMemAddToPool		/* add memory to the agent pool */
    (
    HWTX		hWtx,		/* WTX API handle               */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into           */
    WTX_TGT_ADDR_T	address,	/* base of memory block to add  */
    UINT32		size		/* size of memory block to add  */
    );

extern WTX_TGT_ADDR_T wtxMemAlign	/* allocate aligned target memory   */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    WTX_TGT_ADDR_T	alignment, 	/* alignment boundary               */
    UINT32		numBytes	/* size of block to allocate        */
    );

extern WTX_TGT_ADDR_T wtxMemAlloc	/* alloc blocks in memory pool      */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    UINT32		numBytes	/* size to allocate in bytes        */
    );

extern UINT32 wtxMemChecksum		/* perform checksum on target memory */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into                */
    WTX_TGT_ADDR_T	startAddr, 	/* remote addr to start checksum at  */
    UINT32		numBytes	/* number of bytes to checksum       */
    );

extern WTX_DASM_INST_LIST * wtxMemDisassemble   /* disassemble memory        */
    (
    HWTX                hWtx,           /* WTX API handle                    */
    WTX_TGT_ADDR_T      pdId,           /* PD ID to look into                */
    WTX_TGT_ADDR_T      startAddr,      /* inst address to match             */
    UINT32              nInst,          /* number of instructions to get     */
    WTX_TGT_ADDR_T      endAddr,        /* last address to match             */
    BOOL32              printAddr,      /* if instruction's address appended */
    BOOL32              printOpcodes,   /* if instruction's opcodes appended */
    BOOL32              hexaAddr        /* for HEX address representation    */
    );

extern STATUS wtxMemFree		/* free a block of target memory    */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    WTX_TGT_ADDR_T	address		/* target mem block address to free */
    );

extern STATUS wtxMemMove		/* move a block of target memory */
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_TGT_ID_T	srcPdId,	/* source PD                     */
    WTX_TGT_ADDR_T	srcAddr,	/* remote addr to move from      */
    WTX_TGT_ID_T	dstPdId,	/* destination PD                */
    WTX_TGT_ADDR_T	destAddr,	/* remote addr to move to        */
    UINT32		numBytes	/* number of bytes to move       */
    );

extern UINT32 wtxMemRead		/* read memory from the target */
    (
    HWTX		hWtx,		/* WTX API handle              */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into          */
    WTX_TGT_ADDR_T	fromAddr,	/* target addr to read from    */
    void *		toAddr,		/* local addr to read to       */
    UINT32		numBytes,	/* bytes to read               */
    UINT32		options		/* memory read options         */
    );

extern UINT32 wtxMemWidthRead           /* read memory on <width> bytes */
    (
    HWTX                hWtx,		/* WTX API handle               */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into           */
    WTX_TGT_ADDR_T      fromAddr,	/* target addr to read from     */
    void *              toAddr,		/* local addr to read to        */
    UINT32              numBytes,	/* bytes to read                */
    UINT8               width,		/* width to read                */
    UINT32		options		/* memory read options          */
    );

extern WTX_TGT_ADDR_T wtxMemRealloc	/* reallocate a block of target mem */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    WTX_TGT_ADDR_T	address, 	/* memory block to reallocate       */
    UINT32		numBytes	/* new size                         */
    );

extern UINT32 wtxMemSet			/* set target memory to given value */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into               */
    WTX_TGT_ADDR_T	addr,		/* remote addr to write to          */
    UINT32		numBytes, 	/* number of bytes to set           */
    UINT32		val		/* value to set                     */
    );

extern STATUS wtxMemScan		/* scan target memory for pattern   */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into               */
    BOOL32		match,		/* match/Not-match pattern boolean  */
    WTX_TGT_ADDR_T	startAddr, 	/* target address to start scan     */
    WTX_TGT_ADDR_T	endAddr,	/* target address to finish scan    */
    UINT32		numBytes, 	/* number of bytes in pattern       */
    void *		pattern,	/* pointer to pattern to search for */
    WTX_TGT_ADDR_T *	pResult		/* pointer to result address        */
    );

extern UINT32 wtxMemWrite		/* write memory on the target */
    (
    HWTX		hWtx,		/* WTX API handle             */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into         */
    void *		fromAddr,	/* local addr to write from   */
    WTX_TGT_ADDR_T	toAddr,		/* remote addr to write to    */
    UINT32		numBytes,	/* bytes to read              */
    UINT32		options		/* memory write options       */
    );

extern UINT32 wtxMemWidthWrite          /* write memory on the target */
    (
    HWTX		hWtx,		/* WTX API handle             */
    WTX_TGT_ID_T	pdId,		/* PD ID to look into         */
    void *		fromAddr,	/* local addr to write from   */
    WTX_TGT_ADDR_T	toAddr,		/* remote addr to write to    */
    UINT32		numBytes,	/* number of bytes to read    */
    UINT8		width,		/* width to read              */
    UINT32		options		/* memory write options       */
    );

extern STATUS wtxObjModuleChecksum	/* checks validity of target memory   */
    (
    HWTX		hWtx,		/* WTX API handler                    */
    WTX_TGT_ID_T	pdId,		/* protection domain ID to look into  */
    WTX_TGT_ID_T	moduleId,	/* module ID to check                 */
    char *		moduleName	/* module name to check               */
    );

extern char * wtxObjModuleFindName	/* find module name given its ID      */
    (
    HWTX		hWtx,		/* WTX API handle                     */
    WTX_TGT_ID_T	pdId,		/* protection domain in which to look */
    WTX_TGT_ID_T	moduleId	/* module ID to get name from         */
    );

extern WTX_TGT_ID_T wtxObjModuleFindId	/* find obj module ID from name       */
    (
    HWTX		hWtx,		/* WTX API handle                     */
    WTX_TGT_ID_T	pdId,		/* protection domain in which to look */
    const char *	moduleName	/* module name to get ID from         */
    );

extern WTX_MODULE_INFO * wtxObjModuleInfoGet	/* give info on obj module    */
    (
    HWTX		hWtx,		/* WTX API handler                    */
    WTX_TGT_ID_T	pdId,		/* protection domain to look into     */
    WTX_TGT_ID_T	moduleId	/* module ID to get name from         */
    );

extern WTX_MODULE_INFO * wtxObjModuleInfoAndPathGet /* give info on obj mod */
    (
    HWTX		hWtx,		/* WTX API handler                    */
    WTX_TGT_ID_T	pdId,		/* protection domain to look into     */
    WTX_TGT_ID_T	moduleId	/* module ID to get name from         */
    );

extern WTX_MODULE_LIST * wtxObjModuleListGet	/* list loaded obj modules */
    (
    HWTX                    	hWtx,		/* WTX API handle         */
    WTX_MOD_FIND_CRITERIA *	pCriteria 	/* search criteria        */
    );

extern UINT32 wtxLoadModeGet			/* get host loader load mode */
    (
    HWTX		hWtx			/* WTX API handle */    
    );
    
extern WTX_MODULE_INFO * wtxObjModuleLoad	/* load a new object module */
    (
    HWTX			hWtx,		/* WTX API handle           */
    WTX_TGT_ID_T		pdId,		/* PD we want to load in    */
    WTX_MODULE_FILE_DESC *	pFileDesc,	/* module descriptor        */
    UINT32			loadOptions	/* load options             */
    );

extern STATUS wtxObjModuleLoadStart		/* asynchronous load     */
    (
    HWTX			hWtx,		/* WTX API handle        */
    WTX_TGT_ID_T		pdId,		/* PD we want to load in */
    WTX_MODULE_FILE_DESC *	pFileDesc,	/* module descriptor     */
    UINT32			loadOptions	/* load options          */
    );

extern WTX_LOAD_REPORT_INFO * wtxObjModuleLoadProgressReport /* load status */
    (
    HWTX                        hWtx    /* WTX API handle */
    );

extern STATUS wtxObjModuleLoadCancel	/* cancel an async. load */
    (
    HWTX			hWtx	/* WTX API handle */
    );

extern STATUS wtxObjModuleUnload	/* unload an obj module from target */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    UINT32		option,		/* unload option		    */
    WTX_TGT_ID_T	modId		/* ID of module to unload           */
    );

extern STATUS wtxObjModuleByNameUnload  /* unload an obj. mod. from target  */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId,		/* PD into which we want to operate */
    UINT32		option,		/* unload option		    */
    const char *	name		/* name of module to look for       */
    );

extern WTX_TGT_ADDR_T wtxProcessCreate
    (
    HWTX		hWtx,		/* WTX API handle                     */
    const char *	name,		/* name of the PD to be created       */
    int			options,	/* options of the PD                  */
    int			addOptions,	/* additionnal options                */
    int			stackSize,	/* heap size                          */
    UINT32		uid,		/* UID				      */
    UINT32		gid,		/* GID				      */
    UINT32		priority,	/* Priority			      */
    UINT32		redirIn,	/* RedirIn			      */
    UINT32		redirOut,	/* RedirOut			      */
    UINT32		redirErr,	/* RedirErr			      */
    int			argc,		/* argc number			      */
    char **		argv,		/* argv for process		      */
    int			envc,		/* envc number			      */
    char **		envv		/* envv for process		      */
    );

extern WTX_TGT_ADDR_T wtxPdCreate
    (
    HWTX		hWtx,		/* WTX API handle                     */
    const char *	name,		/* name of the PD to be created       */
    int			options,	/* options of the PD                  */
    int			heapSize,	/* heap size                          */
    int			lowPriority,	/* lowest priority a task may have    */
    int			highPriority,	/* highest priority a task may have   */
    WTX_TGT_ADDR_T	pagePoolList,	/* a list of page pools for the PD    */
    const char *	linkPath	/* link path to specify for the PD    */
    );

extern STATUS wtxRegisterForEvent	/* send events matching expression */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	regExp		/* regular expr to select events */
    );

extern STATUS wtxRegsGet		/* read register data from the target */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext,
    WTX_REG_SET_TYPE	regSet,		/* type of register set */
    UINT32		firstByte,	/* first byte of register set */
    UINT32		numBytes,	/* number of bytes of register set */
    void *		regMemory	/* place holder for reg. values */
    );

extern STATUS wtxRegsSet		/* write to registers on the target */
    (
    HWTX		hWtx,		/* WTX API handle */
    WTX_CONTEXT *	pContext,
    WTX_REG_SET_TYPE	regSet,		/* type of register set */
    UINT32		firstByte,	/* first byte of reg. set */
    UINT32		numBytes,	/* number of bytes in reg. set. */
    void *		regMemory	/* register contents */
    );

extern void wtxSymListFree		/* free a wtx symbol list */
    (
    WTX_SYM_LIST *	pSymList	/* symbol list to free    */
    );

extern void wtxObjModuleListFree	/* free a wtx module list */
    (
    WTX_MODULE_LIST *	pModList	/* module list to free    */
    );

extern STATUS wtxResultFree		/* free mem allocated by WTX API call */
    (
    HWTX		hWtx,		/* WTX API handle */
    void *		pResult		/* pointer to WTX result structure */
    );

extern WTX_TGT_ADDR_T wtxStrToTgtAddr	/* convert str to a WTX_TGT_ADDR_T */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	str		/* string to convert */
    );

extern INT32 wtxStrToInt32		/* convert str to an INT32 */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	str		/* string to convert */
    );

extern WTX_CONTEXT_ID_T wtxStrToContextId	/* convert str to ctxt ID */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	str		/* string to convert */
    );

extern WTX_CONTEXT_TYPE wtxStrToContextType	/* convert str ton ctxt type */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	str		/* string to convert */
    );

extern WTX_EVENT_TYPE wtxStrToEventType	/* convert string to event type */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	str		/* string to convert */
    );

const char * wtxEventToStrType		/* convert event type to a string */
    (
    WTX_EVENT_TYPE	event		/* WTX Event */
    );

extern STATUS wtxSymAdd			/* add symbol with given params  */
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_TGT_ID_T	pdId,		/* PD into which we want operate */
    const char *	symName, 	/* name of symbol to add         */
    WTX_TGT_ADDR_T	symValue,	/* value of symbol to add        */
    UINT32		symType		/* type of symbol to add         */
    );

extern WTX_SYMBOL * wtxSymFind          /* find a symbol in the symbol table */
    (
    HWTX			hWtx,		/* WTX API handle            */
    WTX_SYM_FIND_CRITERIA *	pCriteria 	/* criteria structure        */
    );

extern WTX_SYM_LIST * wtxSymListGet     /* find a symbol in the symbol table */
    (
    HWTX			hWtx,		/* WTX API handler           */
    WTX_SYM_FIND_CRITERIA *	pCriteria 	/* criteria structure        */
    );

extern WTX_SYM_LIST * wtxSymListByModuleIdGet	/* get list of symbols    */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    WTX_TGT_ID_T	pdId,		/* protection domain ID to look into */
    const char *	string,		/* string to match                   */
    WTX_TGT_ID_T	moduleId,	/* module ID to search in            */
    WTX_TGT_ADDR_T	value,		/* symbol value to match             */
    BOOL32		listUnknown	/* list unknown symbols only flag    */
    );

extern WTX_SYM_LIST * wtxSymListByModuleNameGet	/* get list of symbols    */
    (
    HWTX		hWtx,		/* WTX API handle                    */
    WTX_TGT_ID_T	pdId,		/* protection domain ID to look into */
    const char *	string,		/* string to match                   */
    const char *	moduleName,	/* module name to search in          */
    WTX_TGT_ADDR_T	value,		/* symbol value to match             */
    BOOL32		listUnknown	/* list unknown symbols only flag    */
    );

extern STATUS wtxSymRegister		/* registers a new syymbol            */
    (
    HWTX                hWtx,           /* WTX API handle                     */
    WTX_TGT_ID_T        pdId,           /* PD into which we want to operate   */
    const char *        name,           /* name of symbol to add              */
    WTX_TGT_ADDR_T      value,          /* value of symbol to add             */
    UINT32              symRef,         /* reference of the symbol            */
    UINT32		type,           /* type of symbol to add              */
#ifdef	HOST	/* XXX */
    UINT32              execMode,       /* execution mode (entry points only) */
    GROUP_ID            apiGroup        /* API group of the symbol            */
#else	/* HOST */
    UINT32              execMode	/* execution mode (entry points only) */
#endif	/* HOST */
    );

extern STATUS wtxSymRemove		/* remove a symbol from sym table */
    (
    HWTX		hWtx,		/* WTX API handle                 */
    WTX_TGT_ID_T	pdId,		/* PD into which we want operate  */
    const char *	symName,	/* name of symbol to remove       */
    UINT32		symType		/* type of symbol to remove       */
    );

extern WTX_SYM_TBL_INFO * wtxSymTblInfoGet	/* return sym table info    */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	pdId		/* PD into which we want to look at */
    );

extern const char * wtxTargetRtNameGet	/* get the target-runtime name */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern const char * wtxTargetRtVersionGet	/* get target-runtime version */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern INT32 wtxTargetCpuTypeGet	/* get the target CPU type code */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern BOOL32 wtxTargetHasFppGet	/* check for floating point processor */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern BOOL32 wtxTargetHasAltivecGet    /* check for altivec processor */
    (
    HWTX                hWtx            /* WTX API handle */
    );

extern BOOL32 wtxTargetHasSpeGet        /* check for SPE processor */
    (
    HWTX                hWtx            /* WTX API handle */
    );

extern BOOL32 wtxTargetHasDspGet	/* check for DSP prcessor */
    (
    HWTX	hWtx			/* WTX API handle */
    );

extern WTX_ENDIAN_T wtxTargetEndianGet	/* get edianness of target */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern const char * wtxTargetBootlineGet	/* get target boot line info */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern const char * wtxTargetBspNameGet	/* get the BSP name string */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern const char * wtxTargetBspShortNameGet	/* get the BSP_NAME value */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern const char * wtxTargetToolNameGet/* get the tool used to build the tgt */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTargetReset		/* reset the target */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern UINT32 wtxTargetIpAddressGet     /* get the target IP address */
    (
    HWTX                hWtx            /* WTX API handle */
    );

extern STATUS wtxTargetAttach		/* reattach to the target */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxToolAttach		/* connect client to target server */
    (
    HWTX		hWtx,		/* WTX API handle */
    const char *	targetName,	/* target Server name */
    const char *	toolName	/* tool name */
    );

extern STATUS wtxToolOnHostAttach	/* attach to a remote target server   */
    (
    HWTX		hWtx,		/* WTX API handle                     */
    const char *	serverName,	/* target server name                 */
    const char *	toolName,	/* tool name                          */
    char *		host		/* host to ask for tgtsvr             */
    );

extern const char * wtxToolNameGet	/* return name of current tool */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern BOOL32 wtxToolConnected		/* check tool connection to server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxToolDetach		/* detach from the target server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern WTX_TGT_ID_T wtxToolIdGet	/* return tool ID of current tool */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern WTX_TS_INFO * wtxTsInfoGet	/* get info about target and server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTsKill			/* kill the target server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTsLock			/* lock server for exclusive access */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTsTimedLock		/* lock target server a limited time */
    (
    HWTX		hWtx,		/* WTX API handle */
    UINT32		seconds		/* duration of lock */
    );

extern const char * wtxTsNameGet	/* get target server name */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTsRestart		/* restart the target server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxTsUnlock		/* unlock the connected target server */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxUnregisterForEvent     /* unregister for some events */
    (
    HWTX                hWtx,           /* WTX API handle */
    const char *        regExp          /* regexp for the unwanted events */
    );

extern BOOL32 wtxVerify			/* verify WTX handle is valid for use */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern INT32 wtxVioChanGet		/* get a virtual I/O channel number */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxVioChanRelease		/* release a virtual I/O channel */
    (
    HWTX		hWtx,		/* WTX API handle */
    INT32		channel		/* the channel number to release */
    );

extern STATUS wtxVioCtl			/* perform control operation on VIO */
    (
    HWTX		hWtx,		/* WTX API handle */
    INT32		channel,	/* channel to do control operation on */
    UINT32		request,	/* control operation to perform */
    UINT32		arg		/* argument for call */
    );

extern WTX_VIO_FILE_DESC ** wtxVioFileListGet	/* list server files */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern UINT32 wtxVioWrite		/* write data to a VIO channel */
    (
    HWTX		hWtx,		/* WTX API handle */
    INT32		channel,	/* channel to write to */
    void *		pData,		/* pointer to data to write */
    UINT32		numBytes	/* number of bytes of data to write */
    );

extern STATUS wtxVioLink
    (
    HWTX                hWtx,           /* WTX API handle      */
    WTX_VIO_LINK_DESC   *vioLinkDesc    /* VIO link descriptor */
    );

extern STATUS wtxVioUnlink
    (
    HWTX                hWtx,           /* WTX API handle      */
    WTX_VIO_LINK_DESC   *vioLinkDesc    /* VIO link descriptor */
    );

extern const char * wtxTsVersionGet	/* return the Tornado version */
    (
    HWTX		hWtx		/* WTX API handle */
    );

extern STATUS wtxMsgObjModuleLoad
    (
    HWTX                hWtx,           /* WTX API handle */
    WTX_MSG_FILE_LOAD_DESC *pfileLoadDescIn,
    WTX_MSG_FILE_LOAD_DESC *pfileLoadDescOut
    );

extern STATUS wtxUsrSvcAdd
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_TGT_ID_T	svcId,		/* id to attribute to new service, */
    					/* 0 = use the id returned by this */
					/* request			   */
    WTX_TGT_ADDR_T	entry,		/* service function address        */
    WTX_TGT_ADDR_T	initRtn,	/* service init routine address    */
    WTX_TGT_INT_T	initRtnArg,	/* service init routine argument   */
    WTX_TGT_ID_T  * 	pSvcId		/* pointer to service id	   */
    );

extern STATUS wtxUsrSvcFind
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_TGT_ADDR_T	entry,		/* service function address        */
    WTX_TGT_ID_T *	pSvcId		/* pointer to service id	   */
    );

extern STATUS wtxUsrSvcRemove
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_TGT_ID_T	svcId,		/* id of service to remove         */
    WTX_TGT_ADDR_T	stopRtn,	/* service stop routine address    */
    WTX_TGT_INT_T	stopRtnArg	/* service stop routine argument   */
    );

WTX_MEM_XFER * wtxUsrSvcCall
    (
    HWTX		hWtx,		/* WTX API handle                  */
    WTX_TGT_ID_T	svcId,		/* id of service to call           */
    void *		buffer,		/* service arguments		   */
    UINT32		nBytes		/* number of bytes in buffer       */
    );

extern char * wtxTsLogGet
    (
    HWTX	hWtx,		/* WTX current session handle                 */
    char *	svrName,	/* target server to get log from              */
    int		seek,		/* seek to apply on target server log file    */
    char *	host		/* host on which registry is running          */
    );

extern STATUS wtxShlibAddrGet	/* Get address of sharedlib	    */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    WTX_TGT_ID_T	shlibPdId,	/* PD of the sharedlib		    */
    WTX_TGT_ID_T	prPdId,	 	/* Process PD. 0 is current process */
    WTX_TGT_ADDR_T *	pRetVal		/* Return address		    */
    );

extern STATUS wtxTargetFileCopy	/* Do a remote file copy	    */
    (
    HWTX		hWtx,		/* WTX API handle		    */
    char *		srcPathname,	/* Host source pathname 	    */
    char *		dstPathname,	/* Destination pathname		    */
    UINT32		options		/* Copy options			    */
    );
    
extern STATUS wtxTargetFileRemove	/* Do a remote file copy	    */
    (
    HWTX		hWtx,		/* WTX API handle		    */
    char *		fileName,	/* Host source pathname 	    */
    UINT32		options		/* Remove options		    */
    );

extern STATUS wtxContextAttach
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_CONTEXT *	pContext
    );
    
extern STATUS wtxContextDetach
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_CONTEXT *	pContext
    );

/* --------------------------- Environment settings ------------------------- */

extern char * wtxTgtsvrEnvGet		/* Get environment string 	      */
    (
    HWTX		hWtx,		/* WTX API handle		      */
    char *		envVariable	/* Environment variable to get 	      */
    );

extern STATUS wtxTgtsvrEnvSet 		/* Set environment string 	      */
    (
    HWTX		hWtx,		/* WTX API handle		      */
    char *		envVariable,	/* Environment variable to set 	      */
    char *		envValue	/* Value to set 		      */
    );
    
extern STATUS wtxLastRuntimeErrorGet
    (
    HWTX	hWtx,			/* WTX API handle		*/
    char *	pRetVal			/* last runtime errno string	*/
    );

/* --------------------------- kernel modules utilities --------------------- */

extern STATUS wtxModulesInfoSynchro	/* Update kernel modules symbols    */
    (
    HWTX		hWtx,		/* WTX API handle                   */
    UINT32 *		pRetVal		/* Number of synchronized modules   */
    );

/* --------------------------- Target filesystem IO ------------------------ */
extern STATUS wtxTgtfsMkdir 
    (
    HWTX			hWtx,		/* WTX API handle */
    char *	 		pathname,	/* Pathname */
    WTX_TGTFS_INODE_MODE_TYPE 	mode		/* Mode */
    );

extern STATUS wtxTgtfsRmdir
    (
    HWTX			hWtx,		/* WTX API handle  */
    char *	 		pathname	/* Pathname */
    );

extern STATUS wtxTgtfsMv
    (
    HWTX			hWtx,		/* WTX API handle   */
    char *	 		oldPath,	/* Pathname */
    char *	 		newPath		/* Pathname */
    );

extern STATUS wtxTgtfsRm
    (
    HWTX			hWtx,		/* WTX API handle   */
    char *	 		pathname	/* Pathname */
    );

extern STATUS wtxTgtfsLink
    (
    HWTX			hWtx,		/* WTX API handle   */
    char *	 		oldPath,	/* Pathname */
    char *	 		newPath		/* Pathname */
    );

extern STATUS wtxTgtfsSymlink
    (
    HWTX			hWtx,		/* WTX API handle    */
    char *	 		oldPath,	/* Pathname */
    char *	 		newPath		/* Pathname */
    );

extern STATUS wtxTgtfsCp
    (
    HWTX			hWtx,		/* WTX API handle    */
    char *	 		oldPath,	/* Pathname */
    char *	 		newPath		/* Pathname */
    );

extern STATUS wtxTgtfsMknod 
    (
    HWTX			hWtx,		/* WTX API handle    */
    char *	 		pathname,	/* Pathname */
    WTX_TGTFS_INODE_MODE_TYPE 	mode,		/* Mode */
    UINT32 			major,		/* Major */
    UINT32			minor		/* Minor */	
    );

extern STATUS wtxTgtfsReaddir
    (
    HWTX			hWtx,	/* WTX API handle                   */
    char *	 		pathname,/* Pathname (in)		    */
    WTX_TGTFS_INODE_CTRL_OPT	option,	/* Option (in)			    */
    WTX_TGTFS_INODE_READDIR_LIST * pReaddirList	/* Pointer to result list   */
    );

extern STATUS wtxTgtfsSetdir 
    (
    HWTX		hWtx,		/* WTX API handle                   */
    char *	 	pathname,	/* Pathname			    */
    char **		ppCurrentDir	/* New pathname			    */
    );

extern STATUS wtxTgtfsGetdir 
    (
    HWTX		hWtx,		/* WTX API handle                   */
    char **		ppCurrentDir	/* New pathname			    */
    );

extern STATUS wtxTgtfsStat
    (
    HWTX	hWtx,			/* WTX API handle                   */
    char *	pathname,		/* Structure dirp (in)		    */
    WTX_TGTFS_INODE_STAT_RES ** ppStatInfo	/* Pointer to info 	    */
    );
    
extern STATUS wtxTgtfsLstat
    (
    HWTX	hWtx,			/* WTX API handle                   */
    char *	pathname,		/* Structure dirp (in)		    */
    WTX_TGTFS_INODE_STAT_RES ** ppStatInfo	/* Pointer to info 	    */
    );

extern UINT32 wtxOsErrCodeGet
    (
    HWTX	hWtx		/* WTX API handle */
    );
    
extern STATUS wtxTgtfsChmod 
    (
    HWTX			hWtx,		/* WTX API handle             */
    char *	 		pathname,	/* Pathname */
    WTX_TGTFS_INODE_MODE_TYPE 	mode		/* Mode */
    );
    
extern STATUS wtxTgtfsChown 
    (
    HWTX			hWtx,		/* WTX API handle             */
    char *	 		pathname,	/* Pathname */
    UINT32		 	uid,		/* UID */
    UINT32			gid
    );
    
extern STATUS wtxTgtfsUmask
    (
    HWTX			hWtx,		/* WTX API handle            */
    WTX_TGTFS_INODE_MODE_TYPE 	umask,		/* Mode to set to */
    WTX_TGTFS_INODE_MODE_TYPE *	pPrevValue	/* Previous value */
    );
    
extern STATUS wtxReaddirFree
    (
    WTX_TGTFS_INODE_READDIR_RES *pList 
    );

extern STATUS wtxTgtfsReadlink 
    (
    HWTX		hWtx,		/* WTX API handle                   */
    char * 		pathname,	/* Pathname			    */
    char **		ppCurrentLink	/* Points to	(out)		    */
    );
     
/* ------------------------PD  threads ------------------------------------ */
extern WTX_TASKS_INFO_DESC * wtxPdTasksListGet
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_CONTEXT *	pContext	/* Input : Context */
    );
    
extern STATUS wtxPdInfoSet
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_TGT_ID_T		pdId,		/* pdId 	*/
    UINT32		options		/* Options 	*/
    );


extern WTX_PD_INFO_OPT wtxPdInfoGet
    (
    HWTX		hWtx,		/* WTX API handle                */
    WTX_TGT_ID_T		pdId		/* pdId 	*/
    );
    
/* --------------------------- exported utilities --------------------------- */

extern WTX_DESC * wtxDescDuplicate	/* duplicate a WTX_DESC            */
    (
    HWTX	hWtx,			/* current WTX session handler     */
    WTX_DESC *	pDesc			/* WTX_DESC to duplicate           */
    );

#ifdef HOST
extern const char * wtxTargetToolFamilyGet 
			/* returns toolchain family (e.g. "gnu" or "diab") */
    (
    HWTX hWtx                           /* WTX API handle */
    );
#endif

#ifdef WIN32
long wtxEnvironRegistryOptionsGet
    (
    HKEY	hKey,			/* Win32 registry key handler         */
    char *	dbDir,			/* Tornado registry DB directory      */
    int *	pPingDelay,		/* target server ping delay           */
    int *	pNUnsuccessPing,	/* target server max unsuccess ping   */
    int *	pConnectionTimeout,	/* inter-registry timeout (seconds)   */
    char **	pWtxLogFileName,	/* wtx log file path                  */
    int *	pWtxLogMaxSize,		/* wtx log file max size              */
    char **	pWtxLogFilter,		/* wtx log filter regexp              */
    int *	pWtxLogLevel		/* wtx log level                      */
    );

#endif /* WIN32 */

#ifdef HOST
extern DEMANGLER_STYLE wtxMsgDemanglerStyleGet
    (
    HWTX hWtx                           /* WTX API handle */
    );

#define wtxDemanglerStyleGet		wtxMsgDemanglerStyleGet
#define wtxDefaultDemanglerStyleGet	wtxMsgDemanglerStyleGet
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCwtxh */
