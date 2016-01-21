/* wdbRpcLib.h - header file for remote debug agents RPC interface */

/*
 * Copyright (c) 1995-2005, 2008, 2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01h,29jul10,pad  Moved extern C statement after include statements.
01g,26sep08,rlp  Added the wdbRpcFreeArgs prototype (CQ:WIND00133970).
01f,05dec05,dbt  Added more RPC definitions.
		 Removed references to sockaddr_in
01e,01dec05,dbt  Removed references to timeval structure.
01d,25apr02,jhw  Added C++ support (SPR 76304).
01c,03jun95,ms	 added wdbRpcNotifyConnect.
01b,05apr95,ms	 new data types.
01a,06feb95,ms	 written.
*/

#ifndef __INCwdbRpcLibh
#define __INCwdbRpcLibh

/* includes */

#include <wdb/wdbCommIfLib.h>
#include <wdb/wdbXdrLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* RPC return values */

#define	SUCCESS			0
#define	PROG_UNAVAIL		1
#define	PROG_MISMATCH		2
#define	PROC_UNAVAIL		3
#define	GARBAGE_ARGS		4
#define	SYSTEM_ERR		5

/* RPC message types */

#define	CALL			0
#define	REPLY			1

/* RPC reply status */

#define MSG_ACCEPTED		0
#define MSG_DENIED		1

/* address size */

#define	WDB_RPC_ADDR_SIZE	(4 * sizeof (UINT32))

/* data types */

typedef struct		/* hidden */
    {
    WDB_COMM_IF *	pCommIf;	/* communication interface */
    WDB_XDR		xdrs;		/* XDR stream */
    UINT32 *		pInBuf;		/* input buffer */
    INT32		numBytesIn;	/* # bytes recv'ed */
    UINT32 *		pOutBuf;	/* output buffer */
    UINT32		numBytesOut;	/* # bytes sent */
    UINT32		bufSize;	/* size of buffers in bytes */
    UINT32		xid;		/* transport ID */
    UINT32		notifyAddr [WDB_RPC_ADDR_SIZE/4]; /* address to send */
    							  /* event data */
    UINT32		replyAddr [WDB_RPC_ADDR_SIZE/4];  /* address to send */
    							  /* reply */
    } WDB_XPORT;

/* function prototypes */

extern void	wdbRpcXportInit	 	(WDB_XPORT *pXport, WDB_COMM_IF *pIf,
				  	 char * pInBuf, char * pOutBuf,
				  	 UINT32 bufSize);
extern BOOL	wdbRpcRcv	 	(void *pXport, INT32 timeout);
extern BOOL	wdbRpcGetArgs	 	(void *pXport, BOOL (*inProc)(),
				  	 char * args);
#if defined(_WRS_WDB_XDR_USE_MEMORY_MANAGER)
extern BOOL	wdbRpcFreeArgs		(void *pXport, BOOL (*inProc)(),
					char * args);
#endif	/* _WRS_WDB_XDR_USE_MEMORY_MANAGER */
extern void     wdbRpcReply      	(void *pXport, BOOL (*inProc)(),
				  	 char * addr);
extern void     wdbRpcReplyErr   	(void *pXport, UINT32 errStatus);
extern void     wdbRpcResendReply	(void *pXport);
extern void     wdbRpcNotifyHost	(void *pXport);
extern void	wdbRpcNotifyConnect	(void *pXport);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbRpcLibh */
