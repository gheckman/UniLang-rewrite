/* wdbTaskLib.h - header file for task support in WDB agent */

/*
 * Copyright (c) 2003,2005-2007,2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01g,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01f,10dec09,rlp  Modified wdbTaskBpAdd prototype and removed TGT_XXX types.
01e,29sep09,rlp  Adapted to LP64 model.
01d,06jul07,p_b  Added 64bits support
01c,30oct06,rlp  Modified to use VxDBG library (REQ00007655).
01b,12jul05,bpn  Added childProcessStop field to WDB_TASK_INFO.
01a,16dec03,elg  Written.
*/

#ifndef __INCwdbTaskLibh
#define __INCwdbTaskLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WDB_INFO(p)	((WDB_TASK_INFO *) (((WIND_TCB *) (p))->pWdbInfo))

/* data types */

typedef struct wdb_task_info		/* task information for WDB */
    {
    struct
    	{
	void *	wdb1;
	void *	wdb2;
	} wdbEvtList;			/* dll for event */
    void *	taskBpAddr;		/* current breakpoint address */
    INSTR *	taskPc;			/* task program counter */
    void *	taskFp;			/* task frame pointer */
    void *	taskSp;			/* task stack pointer */
    VOIDFUNCPTR	wdbExitHook;		/* task exit hook */
    ULONG	tid;			/* task ID */
    UINT32	ctxType;		/* context stopped by breakpoint */
    UINT32	status;			/* status of context that hit BP */
    BOOL	evtQueued;		/* event queued for host */
    BOOL	childProcessStop;	/* TRUE if CPS is set for that task */
    } WDB_TASK_INFO;

/* globals */

extern BOOL	(*wdbTaskRestartHook) (EXC_INFO * pExcInfo);

/* function prototypes */

extern UINT32	wdbTaskDeleteHookAdd	(ULONG tid, void (*hook)
							    (
							    WDB_CTX ctx,
							    int	exitCode,
							    int errorStatus
							    ));
extern UINT32	wdbTaskCreateHookAdd	(void (*hook)
						(
						WDB_CTX * createdCtx,
						WDB_CTX * creationCtx
						),
						   WDB_ACTION_TYPE action);
extern UINT32	wdbTaskStep (ULONG ctxId, INSTR * startAddr, INSTR * endAddr);
extern UINT32	wdbTaskStop (ULONG ctxId);
extern UINT32	wdbTaskCont (ULONG ctxId);
extern UINT32	wdbTaskBpAdd (WDB_CTX * pCtx, WDB_ACTION * pAction,
			      void * addr, UINT32 count,
      			      UINT32 type, ULONG * pBpId);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbTaskLibh */
