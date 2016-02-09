/* xdrwdb.h - External Data Representation Serialization Routines for WDB */

/*
 * Copyright (c) 2005,2007,2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01d,29jul10,pad  Moved extern C statement after include statements.
01c,11jun09,rlp  Created xdr_INT32 (WIND00169866).
01b,26jun07,tbu  added 64 bit support
          + p_b  completed support
01a,06dec05,dbt	 written based on xdr.h
*/

#ifndef __INCxdrwdbh
#define __INCxdrwdbh

/* includes */

#include <wdb/wdb.h>
#ifdef HOST
#include <rpc/rpc.h>
#else /* HOST */
#include <wdb/wdbXdrLib.h>
#endif	/* HOST */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define BYTES_PER_WDB_XDR_UNIT	4

#define WDB_XDR_RNDUP(x)  ((((x) + BYTES_PER_WDB_XDR_UNIT - 1) /	\
			    BYTES_PER_WDB_XDR_UNIT)			\
			    * BYTES_PER_WDB_XDR_UNIT)

#ifdef	HOST
#define	WDB_XDR_SETPOS		XDR_SETPOS
#define	WDB_XDR_GETPOS		XDR_GETPOS
#define	WDB_XDR_INLINE		XDR_INLINE
#define	WDB_XDR_PUTBYTES	XDR_PUTBYTES
#define	WDB_XDR_GETLONG		XDR_GETLONG
#define	WDB_XDR_PUTLONG		XDR_PUTLONG
#define wdbXdrProc_t		xdrproc_t
#define	WDB_XDR			XDR
#define WDB_XDR_OP		XDR_OP
#define	WDB_XDR_ENCODE		XDR_ENCODE
#define	WDB_XDR_DECODE		XDR_DECODE
#define	WDB_XDR_FREE		XDR_FREE
#define	WDB_XDR_GETUINT32	XDR_GETLONG
#define	WDB_XDR_PUTUINT32	XDR_PUTLONG
#define WDB_XDR_GETADDR		XDR_GETLONG
#define WDB_XDR_PUTADDR		XDR_PUTLONG

#endif	/* HOST */

#define xdr_TGT_INT_T(xdrs,pInt) xdr_UINT32((xdrs),(UINT32*) (pInt))
#define xdr_INT32(xdrs,pInt)	 xdr_UINT32((xdrs),(UINT32*) (pInt))

/* type definitions */

typedef struct wdb_param_wrapper
    {
    struct wdb_core	wdbCore;	/* core parameters */
    void *		pParams;	/* real parameters */
    BOOL 		(*xdr)();	/* XDR filter for the real params */
    UINT32		seqNum;		/* sequence number */
    } WDB_PARAM_WRAPPER;

typedef struct wdb_reply_wrapper
    {
    void *		pReply;		/* real reply */
    BOOL		(*xdr)();	/* XDR filter for the real reply */
    UINT32		errCode;	/* error status */
    } WDB_REPLY_WRAPPER;

/* function declarations */

extern BOOL	xdr_UINT32		(WDB_XDR *xdrs, UINT32 *objp);
extern BOOL	xdr_TGT_ADDR_T		(WDB_XDR *xdrs, TGT_ADDR_T *objp);
extern BOOL	xdr_TGT_LONG_T		(WDB_XDR *xdrs, TGT_LONG_T *objp);
extern BOOL	xdr_WDB_CORE		(WDB_XDR *xdrs, WDB_CORE *objp);
extern BOOL	xdr_WDB_STRING_T	(WDB_XDR *xdrs, WDB_STRING_T *objp);
extern BOOL	xdr_WDB_OPQ_DATA_T	(WDB_XDR *xdrs, WDB_OPQ_DATA_T *objp,
					 UINT32 len);
extern BOOL	xdr_ARRAY		(WDB_XDR *xdrs, char **, UINT32 *,
					 UINT32, size_t,
					 wdbXdrProc_t elproc);
extern BOOL	xdr_WDB_STRING_ARRAY	(WDB_XDR * xdrs, char **,
					 UINT32 *, UINT32);
extern BOOL	xdr_CHECKSUM		(WDB_XDR *xdrs, UINT32 xdrCksumVal,
					 UINT32 xdrStreamSize,
					 UINT32 xdrCksumValPos,
					 UINT32 xdrStreamSizePos);
extern BOOL	xdr_REFERENCE		(WDB_XDR * xdrs, char ** pp,
					 size_t size, wdbXdrProc_t elproc);
extern BOOL	xdr_WDB_PARAM_WRAPPER	(WDB_XDR *xdrs,
					 WDB_PARAM_WRAPPER *objp);
extern BOOL	xdr_WDB_REPLY_WRAPPER	(WDB_XDR *xdrs,
					 WDB_REPLY_WRAPPER *objp);
extern BOOL	xdr_WDB_AGENT_INFO 	(WDB_XDR *xdrs,
					 WDB_AGENT_INFO *objp);
extern BOOL	xdr_WDB_CONNECT_INFO 	(WDB_XDR *xdrs,
					 WDB_CONNECT_INFO *objp);
extern BOOL	xdr_WDB_TGT_INFO 	(WDB_XDR *xdrs,
					 WDB_TGT_INFO *objp);
extern BOOL	xdr_WDB_MEM_REGION	(WDB_XDR *xdrs,
					 WDB_MEM_REGION *objp);
extern BOOL	xdr_WDB_MEM_XFER	(WDB_XDR *xdrs,
					 WDB_MEM_XFER *objp);
extern BOOL	xdr_WDB_MEM_SCAN_DESC	(WDB_XDR *xdrs,
					 WDB_MEM_SCAN_DESC *objp);
extern BOOL	xdr_WDB_CTX		(WDB_XDR *xdrs, WDB_CTX *objp);
extern BOOL	xdr_WDB_CTX_CREATE_DESC	(WDB_XDR *xdrs,
					 WDB_CTX_CREATE_DESC *objp);
extern BOOL	xdr_WDB_CTX_KILL_DESC	(WDB_XDR *xdrs,
					 WDB_CTX_KILL_DESC *objp);
extern BOOL	xdr_WDB_CTX_STEP_DESC	(WDB_XDR *xdrs,
					 WDB_CTX_STEP_DESC *objp);
extern BOOL	xdr_WDB_DIRECT_CALL_RET	(WDB_XDR *xdrs,
					 WDB_DIRECT_CALL_RET *objp);
extern BOOL	xdr_WDB_CALL_RETURN_INFO(WDB_XDR *xdrs,
					 WDB_CALL_RET_INFO *objp);
extern BOOL	xdr_WDB_REG_READ_DESC	(WDB_XDR *xdrs,
					 WDB_REG_READ_DESC *objp);
extern BOOL	xdr_WDB_REG_WRITE_DESC	(WDB_XDR *xdrs,
					 WDB_REG_WRITE_DESC *objp);
extern BOOL	xdr_WDB_EVTPT_ADD_DESC	(WDB_XDR *xdrs,
					 WDB_EVTPT_ADD_DESC *objp);
extern BOOL	xdr_WDB_EVTPT_DEL_DESC	(WDB_XDR *xdrs,
					 WDB_EVTPT_DEL_DESC *objp);
extern BOOL	xdr_WDB_EVT_DATA	(WDB_XDR *xdrs,
					 WDB_EVT_DATA *objp);
extern BOOL	xdr_WDB_EVT_INFO	(WDB_XDR *xdrs, WDB_EVT_INFO *objp);
extern BOOL	xdr_WDB_SYM_INFO	(WDB_XDR * xdrs, WDB_SYM_INFO * objp);
extern BOOL	xdr_WDB_SYM_LIST	(WDB_XDR * xdrs, WDB_SYM_LIST * objp);
extern BOOL	xdr_WDB_SECT_INFO	(WDB_XDR * xdrs, WDB_SECT_INFO * objp);
extern BOOL	xdr_WDB_SEG_INFO	(WDB_XDR * xdrs, WDB_SEG_INFO * objp);
extern BOOL	xdr_WDB_MOD_INFO	(WDB_XDR * xdrs, WDB_MOD_INFO * objp);
extern BOOL	xdr_WDB_SYM_MOD_DESC	(WDB_XDR * xdrs,
					 WDB_SYM_MOD_DESC * objp);
extern BOOL	xdr_WDB_SYM_ID_LIST	(WDB_XDR * xdrs,
					 WDB_SYM_ID_LIST * objp);	
extern BOOL	xdr_WDB_SYM_ID		(WDB_XDR * xdrs, WDB_SYM_ID * objp);	
extern BOOL	xdr_WDB_RT_INFO		(WDB_XDR * xdrs, WDB_RT_INFO * objp);	
extern BOOL	xdr_WDB_USR_SVC_CTRL_INFO (WDB_XDR * xdrs,
					WDB_USR_SVC_CTRL_INFO * objp);

extern BOOL	xdr_VOID		(WDB_XDR * xdrs);
extern BOOL	xdr_BOOL		(WDB_XDR * xdrs, BOOL * bp);
extern BOOL	xdr_ENUM		(WDB_XDR * xdrs, UINT32 * ep);

extern BOOL	xdr_WDB_TGT_INFO_2	(WDB_XDR * xdrs,
					 WDB_TGT_INFO_2 * objp);
extern BOOL	xdr_WDB_CONNECT_PARAMS (WDB_XDR * xdrs,
					WDB_CONNECT_PARAMS * objp);
#ifdef __cplusplus
}
#endif

#endif /* __INCxdrwdbh */
