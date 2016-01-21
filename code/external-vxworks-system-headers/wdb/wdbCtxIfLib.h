/* wdbCtxIfLib.h - header file for the WDB agent context runtime interface */

/*
 * Copyright (c) 2003-2006, 2009-2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01l,29jul10,pad  Moved extern C statement after include statements.
01k,14sep09,rlp  Adapted to LP64 model.
01j,11sep06,vhe  Fix CQ:WIND00061957, use of reserved word
01i,21dec05,dbt  Added WDB_CTX_ID_GET() definition.
01h,28nov05,dbt  Removed unused context stop() and continue() APIs.
01g,14nov05,dbt  Removed useless information.
01f,13apr04,elg  Remove obsolete type WDB_REG_SET_TYPE.
01e,23mar04,elg  Move macros to get information on context in wdbOsLib.h
01d,08mar04,elg  Change WDB_CTX structure.
01c,12sep03,tbu  Moved inclusion of netinet/in_systm.h to wdbOsLib.h
01b,22may03,elg  Modify context creation hook add API to add action type.
01a,11mar03,elg  Written.
*/

#ifndef __INCwdbCtxIfLibh
#define __INCwdbCtxIfLibh

/* includes */

#include <wdb/wdb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef struct wdb_ctx_if
    {
    UINT32 (*ctxCreate)		(WDB_CTX_CREATE_DESC * pCtx, ULONG * pRetVal);
    UINT32 (*ctxDelete)		(WDB_CTX_KILL_DESC * pCtx);
    UINT32 (*suspend)		(ULONG ctxId);
    UINT32 (*resume)		(ULONG ctxId);
    UINT32 (*attach)		(WDB_CTX * pCtx);
    UINT32 (*detach)		(WDB_CTX * pCtx);
    UINT32 (*regsGet)		(WDB_CTX * pCtx, UINT32 type, char ** ppRegs);
    UINT32 (*regsSet)		(WDB_CTX * pCtx, UINT32 type, char * pRegs);
    UINT32 (*createHookAdd)	(VOIDFUNCPTR hook, WDB_ACTION_TYPE actionType);
    UINT32 (*deleteHookAdd)	(ULONG pCtx, VOIDFUNCPTR hook);
    UINT32 (*statusGet)		(WDB_CTX * pCtx, UINT32 * pStatus);
    UINT32 (*idVerify)		(ULONG ctxId);
    } WDB_CTX_IF;

/* context specific macros */

#define	WDB_RT_CTX(pCtx)	pWdbRtIf->pWdbCtxIf [(pCtx)->contextType]

#define	WDB_RT_ENTRY(pEntry)						\
	pWdbRtIf->pWdbCtxIf [(pCtx)->context.contextType]

#define	WDB_CTX_ID_GET(pCtx)	((pCtx)->numArgs > 0 ? (pCtx)->args [0] : 0)

#define WDB_RT_CTX_CREATE(pCtxCreate, pCid)				\
	(WDB_RT_CTX (pCtxCreate) == NULL ?				\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtxCreate))->ctxCreate == NULL ?		\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtxCreate))->ctxCreate ((pCtxCreate), (pCid))))

#define WDB_RT_CTX_DELETE(pCtx)						\
	(WDB_RT_ENTRY (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_ENTRY (pCtx))->ctxDelete == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_ENTRY (pCtx))->ctxDelete (pCtx)))

#define WDB_RT_CTX_SUSPEND(pCtx)					\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->suspend == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		((WDB_RT_CTX (pCtx))->suspend (WDB_CTX_ID_GET (pCtx)) == OK ? \
		    WDB_OK : WDB_ERR_RT_ERROR)))

#define WDB_RT_CTX_RESUME(pCtx)						\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->resume == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		((WDB_RT_CTX (pCtx))->resume (WDB_CTX_ID_GET (pCtx)) == OK ? \
		    WDB_OK : WDB_ERR_RT_ERROR)))

#define WDB_RT_CTX_ATTACH(pCtx)						\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->attach == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->attach (pCtx)))

#define WDB_RT_CTX_DETACH(pCtx)						\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->detach == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->detach (pCtx)))

#define WDB_RT_CTX_REGS_GET(pCtx, regType, pRegs)			\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->regsGet == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->regsGet ((pCtx), (regType), (pRegs))))

#define WDB_RT_CTX_REGS_SET(pCtx, regType, pRegs)			\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->regsSet == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->regsSet ((pCtx), (regType), (pRegs))))

#define WDB_RT_CTX_CREATE_HOOK_ADD(pCtx, hook, actionType)		\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->createHookAdd == NULL ?		\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->createHookAdd ((hook), (actionType))))

#define WDB_RT_CTX_DELETE_HOOK_ADD(pCtx, hook)				\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->deleteHookAdd == NULL ?		\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->deleteHookAdd (WDB_CTX_ID_GET (pCtx), \
						    (hook))))

#define WDB_RT_CTX_STATUS_GET(pCtx, pStatus)				\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->statusGet == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->statusGet ((pCtx), (pStatus))))

#define WDB_RT_CTX_ID_VERIFY(pCtx)					\
	(WDB_RT_CTX (pCtx) == NULL ?					\
	    WDB_ERR_NO_RT_CTX :						\
	    ((WDB_RT_CTX (pCtx))->idVerify == NULL ?			\
	        WDB_ERR_NO_RT_PROC :					\
		(WDB_RT_CTX (pCtx))->idVerify (WDB_CTX_ID_GET (pCtx))))

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbCtxIfLibh */
