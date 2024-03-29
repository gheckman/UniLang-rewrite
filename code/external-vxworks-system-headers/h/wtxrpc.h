/* wtxrpc.h - wtx rpc header file */

/*
 * Copyright (c) 1995-1996, 1998-2001, 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01q,27may10,pad  Moved extern C statement after include statements.
01p,26oct04,jeg  added remoteServerPing() prototye
01o,01apr03,fle  added wtxRpcExchangeSvcAdd() routine
01n,26mar03,x_p  Set version to 4
01m,21nov01,c_c  Changedrpc include location.
01l,05jan00,fle  added usePMap to wtxRpcExchangeCreate() routine parameters
01k,25oct99,fle  added wtxRpcKeyIPListUpdate() routine declaration
01j,11may99,fle  changed wtxRpcExchangeFree - removed xid from parameters and
                 turned it into a WTX_ERROR_T
01i,06apr98,c_c  Changed the registry listenning port for the official one.
01h,24mar98,c_c  Get rid of portmapper.
01g,30sep96,elp  put in share/src/wtx (SPR# 6775).
01f,30may95,c_s  added ipAddr to WTX_RPC_SPLIT_KEY.
01e,17may95,s_w  update functions to form RPC implementation of exchange
		 protocol. Key management functions unchanged.
01d,05may95,p_m  changed WTX_RPC_PROG to differentiate Beta from SDK release.
01c,04may95,s_w  changes to make this the central include file for RPC based
		 implementation files. Moved in defines of WTX_SVC_BASE,
                 WTX_FIRST_ADDL_PROC_NUM, typedef of WTX_ID. Added include of
		 <rpc/rpc.h>.
01b,26jan95,p_m  added UNIX style authentication.
01a,15jan95,p_m  written.
*/

#ifndef __INCwtxrpch
#define __INCwtxrpch	1

#include <wtxexch.h>
#ifdef SUN4_SOLARIS2
#define PORTMAP			/* for backward compatibility */
#endif
#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define	WTX_RPC_PROG	0x55555551	/* WTX RPC program number */
#define	WTX_RPC_VERSION	4		/* WTX RPC version number */

#define WTX_RPC_MAX_VERSION 4		/* Maximum WTX version handled */

#define WTX_SVC_BASE	0x22000000	/* base service number */

/* "official" registry port number */

#define REGISTRY_PORT	((unsigned short)2340)

/*
 * Valid service numbers range between 0 and 500. Standard service have numbers
 * 0 to 300. Additionnal services have numbers 301 to 500.
 */

#define WTX_FIRST_ADDL_PROC_NUM	301

/* typedefs */

typedef struct wtx_rpc_split_key
    {
    int			progNum;	/* rpc program number           */
    int			version;	/* rpc version number           */
    int			protocol;	/* rpc protocol type            */
    unsigned short	port;		/* rpc protocol type            */
    char		host [32];	/* host where service resides   */
    char **		ipAddrList;	/* IP addr list in a.b.c.d form */
    } WTX_RPC_SPLIT_KEY;

/* function declarations */


/* Basic exchange functions */

extern STATUS wtxRpcExchangeCreate	/* create new exchange clnt using RPC */
    (
    WTX_XID		xid,		/* Exchange handle                    */
    const char *	key,		/* Key for server to connect to       */
    BOOL		usePMap		/* do we use port mapper to connect ? */
    );

extern STATUS wtxRpcExchangeDelete	/* delete exchange handle             */
    (
    WTX_XID		xid		/* Exchange handle                    */
    );

extern STATUS wtxRpcExchange		/* do a WTX call via exchange         */
    (
    WTX_XID		xid,		/* Exchange handle                    */
    WTX_REQUEST		reqId,		/* exchange service number            */
    void *		pIn,		/* exchange service in args           */
    void *		pOut		/* exchange service out args          */
    );

extern WTX_ERROR_T wtxRpcExchangeFree	/* free a exchange call result message*/
    (
    WTX_REQUEST		reqId,		/* service ID to free                 */
    void *		pMsg		/* pointer to result message to free  */
    );

extern STATUS wtxRpcExchangeControl	/* perform exchange control functions */
    (
    WTX_XID		xid,		/* Exchange handle                    */
    UINT32		request,	/* Exchange control request number    */
    void *		arg		/* Pointer to request argument        */
    );

extern STATUS wtxRpcExchangeSvcAdd	/* adds a new service                 */
    (
    WTX_XID		xid,		/* exchange handle                    */
    WTX_REQUEST		request,	/* request number to add to services  */
    FUNCPTR		fIn,		/* service input function             */
    FUNCPTR		fOut		/* service output functions           */
    );

extern STATUS wtxRemoteServerPing	/* ping the remote server	      */
    (
    const struct sockaddr_in *  pAddr	/* address to ping		      */
    );

/* RPC key utilities exported for convenience */

extern STATUS wtxRpcKeySplit		/* split RPC key string in components */
    (
    const char *	rpcKey,		/* key to split                       */
    WTX_RPC_SPLIT_KEY *	pSplitKey	/* split key                          */
    );

extern STATUS wtxRpcKeySplitFree	/* free a splitted  RPC key members   */
    (
    WTX_RPC_SPLIT_KEY *	pRpcSplitKey	/* RPC key to free members of         */
    );

extern STATUS wtxRpcSvcUnregister	/* performs svc_unregister using RPC  */
    (
    const char *	rpcKey		/* service key of service to unreg    */
    );

extern char * wtxRpcKey			/* construt an RPC key given params   */
    (
    UINT32		progNum,	/* rpc prog number, or NULL TBA       */
    UINT32		version,	/* rpc version number                 */
    UINT32		protocol,	/* IPPROTO_TCP or IPPROTO_UDP         */
    void		(*dispatch)	/* rpc dispatch routine               */
			(struct svc_req *, SVCXPRT *),
    BOOL		register2pmap,	/* Register to the local portmapper ? */
    SVCXPRT **		ppNewXprt	/* where to return transport          */
    );

char * wtxRpcKeyIPListUpdate		/* update an RPC key address list     */
    (
    const char *	rpcKeyStr,	/* rpc Key string to update with IP   */
    int			ipNum		/* IP address num to set as default   */
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCwtxrpch */
