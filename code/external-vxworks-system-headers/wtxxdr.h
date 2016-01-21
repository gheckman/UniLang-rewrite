/* wtxxdr.h - wtx xdr header file */

/*
 * Copyright (c) 1995-2002, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02n,27may10,pad  Moved extern C statement after include statements.
02m,13dec02,p_b  changed TGT_XXX by WTX_TGT_XXX
02l,22jan02,x_p  Added wtxPdInfoSet /wtxPdInfoGet
02k,27nov01,x_p  Threads handling
02j,21nov01,c_c  Changedrpc include location.
02i,22aug01,x_p  Bsd/OS adaptation (Merge from pil1_x)
02h,20jan00,dbt  Added xdr_WTX_MSG_USR_SVC_CTRL_INFO prototype.
02g,21oct99,p_b  removed WTX_MSG_SERVICE_DESC WTX_MSG_CONSOLE_DESC
02f,13oct99,fle  made some of the XDR filters visible for WTX 2.0 bacward
                 compatibility
02e,06sep99,fle  added new XDR filters declarations for
                 WTX_MSG_REG_TGTSVR_ACTION and WTX_MSG_REG_LOG_ACTION new
                 services
02d,06jul99,c_c  Added wtxMsgContextKill
02c,05jul99,p_b  Added xdr_WTX_MSG_MOD_MATCH_DESC.
02b,05jul99,c_c  Implemented PD context definition.
02a,29jun99,fle  added xdr_WTX_MSG_PD_LIST XDR filter declaration
01z,14jun99,fle  added xdr_WTX_MSG_PARAM_WITH_PD declaration
01y,01jun99,fle  removed all _2 references for new WTX protocol model
01x,12feb99,dbt  include wtxmsg.h header file since we use types declared in
                 this file.
01w,18aug98,pcn  Re-use WTX_MSG_EVTPT_LIST_2.
01v,20jul98,pcn  Added evtptNum and toolId in the wtxEventpointListGet return
                 list.
01u,26may98,pcn  Changed WTX_MSG_EVTPT_LIST_2 in WTX_MSG_EVTPT_LIST_GET.
01t,02mar98,pcn  WTX 2: added xdr_WTX_EVENT_NODE, xdr_WTX_MSG_EVENT_LIST,
                 xdr_WTX_LD_M_FILE_DESC, xdr_WTX_MSG_FILE_LOAD_DESC,
                 xdr_MEM_WIDTH_COPY_ALLOC, xdr_WTX_MSG_MEM_WIDTH_READ_DESC,
                 xdr_WTX_MSG_MEM_WIDTH_COPY_DESC, xdr_WTX_EVENT_2,
                 xdr_WTX_EVTPT_2, xdr_WTX_MSG_EVTPT_DESC_2,
                 xdr_WTX_MSG_EVTPT_LIST_2.
01s,29aug97,fle  Adding the WTX_MEM_DISASSEMBLE service. i.e. adding
                   xdr_WTX_MSG_DASM_DESC and xdr_WTX_MSG_DASM_INST_LIST routines
01s,22aug97,c_c  Try to remove warnings during compilation.
01r,30sep96,elp  put in share/src/wtx (SPR# 6775).
01q,02feb96,elp  added declaration of xdr_WTX_TGT_ADDR_T().
01p,01jun95,p_m  removed xdr_WTX_MSG_CALL_PARAM.
01o,30may95,pad  don't include rpc/rpc.h for PARISC_HPUX9.
01n,30may95,p_m  completed WTX_MEM_SCAN and WTX_MEM_MOVE implementation.
01m,23may95,p_m  made missing name changes.
01l,22may95,jcf  name revision.
01k,16may95,p_m  added xdr_WTX_MSG_KILL_DESC().
01j,09may95,p_m  re-implemented wtxregd related XDR procedures.
		 removed unneeded prototypes.
01i,04may95,s_w  change include of rpc/rpc.h to wtxrpc.h
01h,24mar95,p_m  added xdr_WTX_MSG_MEM_BLOCK_DESC.
01g,16mar95,p_m  added xdr_WTX_MSG_VIO_FILE_LIST.
01f,03mar95,p_m  added xdr_WTX_MSG_GOPHER_TAPE.
01e,27feb95,p_m  added xdr_WTX_MSG_MEM_SCAN_DESC.
01d,25feb95,jcf  added xdr_WTX_MSG_TS_[UN]LOCK.
01c,15feb95,p_m  changed names to xdr_WTX_MSG and added xdr routines
		 to suppress coupling with WDB xdr routines.
		 added #include <rpc/rpc.h>.
01b,31jan95,p_m  added xdr_WTX_MEM_XFER(), xdr_WTX_REG_WRITE() and
		 xdr_WTX_MEM_SET_DESC().
01a,15jan95,p_m  written.
*/

#ifndef __INCwtxxdrh
#define __INCwtxxdrh	1

#include <rpc/rpc.h>
#include <wtxmsg.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

/* ------------ XDR internal for WTX 2.0 backward compatibility ------------- */

extern bool_t xdr_WRAPSTRING		/* XDR string filter                  */
    (
    XDR *	xdrs,			/* XDR information                    */
    char **	string			/* string to transfer                 */
    );

extern bool_t xdr_WTX_VALUE		/* transfers a wtx value through XDR  */
    (
    XDR *	xdrs,			/* XDR information                    */
    WTX_VALUE *	objp			/* pointer to wtx value to transfer   */
    );

extern bool_t xdr_WTX_SVR_DESC		/* wtx server desc XDR filter         */
    (
    XDR *		xdrs,		/* XDR information                    */
    WTX_SVR_DESC *	objp		/* wtx server desc to transfer        */
    );

extern bool_t xdr_WTX_SVR_DESC_Q	/* wtx server queue XDR filter        */
    (
    XDR *		xdrs,		/* XDR information                    */
    WTX_SVR_DESC_Q *	objp		/* wtx server desc queue to transfer  */
    );

/* -------------------------------------------------------------------------- */

extern bool_t xdr_WTX_TGT_ADDR_T	/* transfer a WTX_TGT_ADDR_T data    */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_TGT_ADDR_T *	objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_TOOL_ID	/* transfer a WTX_MSG_TOOL_ID data */
    (
    XDR *		xdrs,		/* XDR information                 */
    WTX_MSG_TOOL_ID *	objp		/* pointer to object to transfer   */
    );

extern bool_t xdr_WTX_MSG_TOOL_DESC	/* tranfer a WTX_MSG_TOOL_DESC data */
    (
    XDR *		xdrs,		/* XDR information                  */
    WTX_MSG_TOOL_DESC *	objp		/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_RESULT	/* transfer a WTX_MSG_RESULT data */
    (
    XDR *		xdrs,		/* XDR information                */
    WTX_MSG_RESULT *	objp		/* pointer to object to transfer  */
    );

extern bool_t xdr_WTX_MSG_PARAM		/* transfer a WTX_MSG_PARAM data */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_MSG_PARAM *	objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_PARAM_WITH_PD	/* transfer a WTX_MSG_PARAM_WITH_PD */
    (
    XDR *			xdrs,	/* XDR information                  */
    WTX_MSG_PARAM_WITH_PD *	objp	/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_PD_DESC_Q	/* transfers a PD list message   */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_MSG_PD_DESC_Q *	objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_TS_INFO	/* tranfer a WTX_MSG_TS_INFO data */
    (
    XDR *		xdrs,		/* XDR information                */
    WTX_MSG_TS_INFO *	objp		/* pointer to object to transfer  */
    );

extern bool_t xdr_WTX_MSG_TS_LOCK	/* transfer a WTX_MSG_TS_LOCK data */
    (
    XDR *		xdrs,		/* XDR information                 */
    WTX_MSG_TS_LOCK *	objp		/* pointer to object to transfer   */
    );

extern bool_t xdr_WTX_MSG_TS_UNLOCK	/* transfer a WTX_MSG_TS_UNLOCK data */
    (
    XDR *		xdrs,		/* XDR information                   */
    WTX_MSG_TS_UNLOCK *	objp		/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_MSG_EVTPT_LIST	/* transfer a WTX_MSG_EVTPT_LIST data */
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_EVTPT_LIST *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_SYM_TBL_INFO	/* transfer WTX_MSG_SYM_TBL_INFO data */
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_SYM_TBL_INFO *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_SYMBOL_DESC	/* transfer WTX_MSG_SYMBOL_DESC data */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_SYMBOL_DESC *	objp	/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_MSG_SYM_LIST	/* transfer a WTX_MSG_SYM_LIST data */
    (
    XDR *		xdrs,		/* XDR information                  */
    WTX_MSG_SYM_LIST *	objp		/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_SYM_MATCH_DESC	/* WTX_MSG_SYM_MATCH_DESC xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_SYM_MATCH_DESC *	objp		/* criteria struct            */
    );

extern bool_t xdr_WTX_MSG_MOD_MATCH_DESC        /* WTX_MSG_SYM_MATCH_DESC xdr */
    (
    XDR *                       xdrs,           /* XDR information            */
    WTX_MSG_MOD_MATCH_DESC *    objp            /* criteria struct            */
    );

extern bool_t xdr_WTX_MSG_VIO_CTL_DESC	/* tranfer WTX_MSG_VIO_CTL_DESC data */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_VIO_CTL_DESC *	objp	/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_MSG_OPEN_DESC	/* tranfer WTX_MSG_OPEN_DESC     */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_MSG_OPEN_DESC *	objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_VIO_COPY_DESC	/* transfer WTX_MSG_VIO_COPY_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_VIO_COPY_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_VIO_FILE_LIST	/* transfer WTX_MSG_VIO_FILE_LIST data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_VIO_FILE_LIST *	objp	/* pointer to object to transfer      */
    );


extern bool_t xdr_WTX_MSG_FILE_LOAD_DESC	/* WTX_MSG_FILE_LOAD_DESC xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_FILE_LOAD_DESC *	objp		/* pointer to obj to transfer */
    );

extern bool_t xdr_WTX_MSG_MODULE_LIST	/* transfer WTX_MSG_MODULE_LIST data */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_MODULE_LIST *	objp	/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_MSG_MODULE_INFO	/* transfer WTX_MSG_MODULE_INFO data */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_MODULE_INFO *	objp	/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_MSG_MOD_NAME_OR_ID	/* WTX_MSG_MOD_NAME_OR_ID xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_MOD_NAME_OR_ID *	objp		/* pointer to obj to transfer */
    );

extern bool_t xdr_WTX_TASK_CONTEXT_DEF	/* transfer WTX_TASK_CONTEXT_DEF data */
    (
    XDR *		xdrs,	/* xdr handle */
    WTX_TASK_CONTEXT_DEF *	objp
    );

extern bool_t xdr_WTX_PD_CONTEXT_DEF	/* transfer WTX_PD_CONTEXT_DEF data   */
    (
    XDR *			xdrs,	/* xdr handle                         */
    WTX_PD_CONTEXT_DEF *	objp	/* protection domain definition       */
    );

extern bool_t xdr_WTX_CONTEXT_DESC	/* transfer WTX_CONTEXT_DESC data     */
    (
    XDR *		xdrs,		/* xdr handle                         */
    WTX_CONTEXT_DESC *	objp		/* context query desc                 */
    );

extern bool_t xdr_WTX_MSG_CONTEXT_DESC	/* transfer WTX_MSG_CONTEXT_DESC data */
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_CONTEXT_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_KILL_CONTEXT	/* transfer WTX_MSG_KILL_CONTEXT data */
    (
    XDR *		xdrs,		/* XDR information                    */
    WTX_MSG_KILL_CONTEXT *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_CONTEXT	/* transfer WTX_MSG_CONTEXT data */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_MSG_CONTEXT *	objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_CONTEXT_STEP_DESC	/* WTX_MSG_CONTEXT_STEP_DESC  */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_CONTEXT_STEP_DESC *	objp		/* pointer to obj to transfer */
    );


extern bool_t xdr_WTX_MSG_EVENT_DESC	/* transfer WTX_MSG_EVENT_DESC data */
    (
    XDR *			xdrs,	/* XDR information                  */
    WTX_MSG_EVENT_DESC *	objp	/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_EVENT_LIST    /* transfer WTX_MSG_EVENT_LIST data */
    (
    XDR *                       xdrs,   /* XDR information                  */
    WTX_MSG_EVENT_LIST *        objp    /* pointer to object to transfert   */
    );

extern bool_t xdr_WTX_MSG_EVENT_REG_DESC	/* WTX_MSG_EVENT_REG_DESC xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_EVENT_REG_DESC *	objp		/* pointer to obj to transfer */
    );

extern bool_t xdr_WTX_MSG_EVTPT_DESC	/* transfer WTX_MSG_EVTPT_DESC data */
    (
    XDR *			xdrs,	/* XDR information                  */
    WTX_MSG_EVTPT_DESC *	objp	/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_FILE_LOAD_DESC	/* WTX_MSG_FILE_LOAD_DESC xdr */
    (
    XDR * 			xdrs,		/* XDR information            */
    WTX_MSG_FILE_LOAD_DESC *	objp		/* pointer to the object to   */
    						/* transfer                   */
    );

extern bool_t xdr_WTX_MSG_FILE_LOAD_DESC /* transfer WTX_MSG_FILE_LOAD_DESC   */
    (
    XDR *       xdrs,                    /* XDR information                   */
    WTX_MSG_FILE_LOAD_DESC * objp        /* pointer to the object to transfer */
    );

extern bool_t xdr_WTX_MSG_KILL_DESC	/* transfer WTX_MSG_KILL_DESC data */
    (
    XDR *		xdrs,		/* XDR information                 */
    WTX_MSG_KILL_DESC *	objp		/* pointer to object to transfer   */
    );

extern bool_t xdr_WTX_MSG_MEM_INFO	/* transfer WTX_MSG_MEM_INFO data     */
    (
    XDR *		xdrs,		/* XDR information                    */
    WTX_MSG_MEM_INFO *	objp		/* pointer to object to transfer      */
    );

extern bool_t xdr_MEM_COPY_ALLOC	/* transfer WTX_MSG_MEM_COPY_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_COPY_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_XFER_DESC	/* transfer WTX_MSG_MEM_XFER_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_XFER_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_SCAN_DESC	/* transfer WTX_MSG_MEM_SCAN_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_SCAN_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_MOVE_DESC	/* transfer WTX_MSG_MEM_MOVE_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_MOVE_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_SET_DESC	/* transfer WTX_MSG_MEM_SET_DESC data */
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_SET_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_COPY_DESC	/* transfer WTX_MSG_MEM_COPY_DESC data*/
    (
    XDR *			xdrs,	/* XDR information                    */
    WTX_MSG_MEM_COPY_DESC *	objp	/* pointer to object to transfer      */
    );

extern bool_t xdr_WTX_MSG_MEM_BLOCK_DESC	/* WTX_MSG_MEM_BLOCK_DESC xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_MEM_BLOCK_DESC *	objp		/* pointer to obj to transfer */
    );

extern bool_t xdr_WTX_MSG_DASM_DESC	/* transfer WTX_MSG_DASM_DESC data */
    (
    XDR *		xdrs,		/* XDR information                 */
    WTX_MSG_DASM_DESC *	objp		/* pointer to object to transfer   */
    );

extern bool_t xdr_WTX_MSG_DASM_INST_LIST	/* WTX_MSG_DASM_INST_LIST xdr */
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_DASM_INST_LIST *	objp		/* pointer to obj to transfer */
    );


extern bool_t xdr_WTX_MSG_REG_WRITE	/* transfer WTX_MSG_REG_WRITE data */
    (
    XDR *		xdrs,		/* XDR information                 */
    WTX_MSG_REG_WRITE *	objp		/* pointer to object to transfer   */
    );

extern bool_t xdr_WTX_MSG_REG_READ	/* transfer WTX_MSG_REG_READ data */
    (
    XDR *		xdrs,		/* XDR information                */
    WTX_MSG_REG_READ *	objp		/* pointer to object to transfer  */
    );

extern bool_t xdr_WTX_MSG_GOPHER_TAPE	/* transfer WTX_MSG_GOPHER_TAPE data */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_GOPHER_TAPE *	objp	/* pointer to object to transfer     */
    );

extern bool_t xdr_WTX_CORE		/* transfer WTX_CORE data        */
    (
    XDR *		xdrs,		/* XDR information               */
    WTX_CORE *		objp		/* pointer to object to transfer */
    );

extern bool_t xdr_WTX_MSG_SVR_DESC	/* transfer WTX_MSG_SVR_DESC data */
    (
    XDR *		xdrs,		/* XDR information                */
    WTX_MSG_SVR_DESC *	objp		/* pointer to object to transfer  */
    );

extern bool_t xdr_WTX_MSG_SVR_DESC_Q	/* transfer WTX_MSG_SVR_DESC_Q data */
    (
    XDR *			xdrs,	/* XDR information                  */
    WTX_MSG_SVR_DESC_Q *	objp	/* pointer to object to transfer    */
    );

extern bool_t xdr_WTX_MSG_WTXREGD_PATTERN	/* WTX_MSG_WTXREGD_PATTERN xdr*/
    (
    XDR *			xdrs,		/* XDR information            */
    WTX_MSG_WTXREGD_PATTERN *	objp		/* pointer to obj to transfer */
    );

extern bool_t xdr_WTX_EVENT	/* transfer WTX_EVENT data           */
    (
    XDR *	xdrs,		/* XDR information                   */
    WTX_EVENT *	objp		/* pointer to the object to transfer */
    );

extern bool_t xdr_WTX_EVTPT	/* transfer WTX_EVTPT data           */
    (
    XDR *	xdrs,		/* XDR information                   */
    WTX_EVTPT *	objp		/* pointer to the object to transfer */
    );

extern bool_t xdr_WTX_MSG_EVTPT_DESC	/* transfer WTX_MSG_EVTPT_DESC data  */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_EVTPT_DESC *	objp	/* pointer to the object to transfer */
    );

extern bool_t xdr_WTX_EVTPT_INFO	/* transfer WTX_EVTPT_INFO data      */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_EVTPT_INFO *		objp	/* Pointer to the object to transfer */
    );

extern bool_t xdr_WTX_MSG_EVTPT_LIST	/* transfer WTX_MSG_EVTPT_LIST       */
    (
    XDR *			xdrs,	/* XDR information                   */
    WTX_MSG_EVTPT_LIST *	objp	/* pointer to the object to transfer */
    );

/* ----------------------- registry messages filters ------------------------ */

extern bool_t xdr_WTX_MSG_DESC_Q	/* filter a registry desc queue msg   */
    (
    XDR *		xdrs,		/* xdrs to use to transfer message    */
    WTX_MSG_DESC_Q *	objp		/* registry returned info queue       */
    );

extern bool_t xdr_WTX_MSG_TGTSVR_ACTION	/* filter tgtsvr action               */
    (
    XDR *			xdrs,	/* xdrs to use to transfer message    */
    WTX_MSG_TGTSVR_ACTION *	objp	/* target server action message       */
    );

extern bool_t xdr_WTX_MSG_WTXREGD_LOG	/* wtxregd log filter                 */
    (
    XDR *			xdrs,	/* xdrs to use to transfer message    */
    WTX_MSG_WTXREGD_LOG *	objp	/* registry log action message        */
    );

extern bool_t xdr_WTX_MSG_WTXREGD_INFO	/* wtxregd info message filter        */
    (
    XDR *			xdrs,	/* xdrs to use to transfer message    */
    WTX_MSG_WTXREGD_INFO *	objp	/* registry info message to transfer  */
    );

extern bool_t xdr_WTX_MSG_WTXREGD_ITEM	/* wtxregd item message filter        */
    (
    XDR *			xdrs,	/* xdrs to use to transfer message    */
    WTX_MSG_WTXREGD_ITEM *	objp	/* registry item message to transfer  */
    );

extern BOOL xdr_WTX_MSG_USR_SVC_CTRL_INFO
    (
    XDR *			xdrs,	/* xdr handle */
    WTX_MSG_USR_SVC_CTRL_INFO *	objp	/* pointer to the object to process */
    );

/* ----------------------- Target File messages filters ------------------------ */
extern BOOL xdr_WTX_MSG_TARGET_FILE_COPY_DESC
    (
    XDR *				xdrs,	/* xdr handle */
    WTX_MSG_TARGET_FILE_COPY_DESC *	objp	/* pointer to the object to process */
    );

extern BOOL xdr_WTX_MSG_TARGET_FILE_REMOVE_DESC
    (
    XDR *				xdrs,	/* xdr handle */
    WTX_MSG_TARGET_FILE_REMOVE_DESC *	objp	/* pointer to the object to process */
    );

/* ----------------------- Target Filesystem ios filters ------------------- */
extern BOOL xdr_WTX_MSG_TGTFS_INODE_CTRL_INFO
    (
    XDR *				xdrs,	/* xdr handle */
    WTX_MSG_TGTFS_INODE_CTRL_INFO *	objp	/* pointer to the object to process */
    );

extern BOOL xdr_WTX_MSG_TGTFS_INODE_CTRL_RESULT
    (
    XDR *           xdrs,
    WTX_MSG_TGTFS_INODE_CTRL_RESULT * objp
    );
    
/* ----------------------- Threads (PD / TASKS) --------------------------- */
extern BOOL xdr_WTX_MSG_TASKS_INFO_DESC
    (
    XDR *			xdrs,	/* xdr handle */
    WTX_MSG_TASKS_INFO_DESC *	objp
    );

extern BOOL xdr_WTX_MSG_PD_INFO_SET_DESC
    (
    XDR *			xdrs,	/* xdr handle */
    WTX_MSG_PD_INFO_SET_DESC *	objp
    );
    
extern BOOL xdr_WTX_MSG_PD_INFO_GET_DESC
    (
    XDR *			xdrs,	/* xdr handle */
    WTX_MSG_PD_INFO_GET_DESC *	objp
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCwtxxdrh */
