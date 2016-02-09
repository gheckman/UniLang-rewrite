/* wtxexch.h - wtx message exchange header file */

/*
 * Copyright (c) 1984-2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,27may10,pad  Moved extern C statement after include statements.
01e,01apr03,fle  added wtxExchangeSvcAdd() routine
01d,05jan00,fle  added usePMap parameter to wtxExchangeCreate()
01c,21oct99,fle  added declaration of wtxEchangeTimeoutSet() routine
01b,11may99,fle  changed wtxExchangeInstall declaration since wtxRpcExchange
                 changes
01a,30sep96,elp  put in share/src/wtx (SPR# 6775).
01a,15may95s_w  written. Based on original design by John Fogelin
*/

#ifndef __INCwtxexchh
#define __INCwtxexchh	1

#include <wtxtypes.h>
#include <wtxerr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define WTX_EXCHANGE_CTL_TIMEOUT_GET		1
#define WTX_EXCHANGE_CTL_TIMEOUT_SET		2
#define WTX_EXCHANGE_CTL_TRANSPORT_ERR_GET	3

/* typedefs */

typedef struct _wtx_exchange * WTX_XID;

/* function declarations */

STATUS	wtxExchangeInitialize (WTX_XID * pXid);

STATUS	wtxExchangeInstall	/* install exchange marshall funcs for handle */
    (
    WTX_XID xid,
    STATUS (*xCreate)		/* connect the exchange id to a WTX server    */
	(
	WTX_XID,		/* WTX exchange ID to create                  */
	const char *,		/* server key string                          */
	BOOL			/* do we use port mapper for connection ?     */
	),
    STATUS (*xDelete)		/* disconnect exchange id from a WTX server   */
	(
	WTX_XID			/* WTX exchange ID                            */
	),
    STATUS (*xExchange)		/* perform an exchange request                */
	(
	WTX_XID,		/* WTX exchange ID                            */
	WTX_REQUEST,		/* exchange request number                    */
	void *,			/* pointer to input arg message               */
	void *			/* pointer to output arg (result) message     */
	),
    WTX_ERROR_T (*xFree)	/* free result of exchange request            */
	(
	WTX_REQUEST,		/* WTX request number                         */
	void *			/* pointer to result message                  */
	),
    STATUS (*xControl)		/* perform misccontrol requests on exchange   */
	(
	WTX_XID,		/* WTX exchange ID                            */
	UINT32,			/* control request number                     */
	void *			/* pointer to control request arg data        */
	),
    STATUS (*xSvcAdd)		/* add a service to this transport            */
	(
	WTX_XID,		/* WTX exchange ID                            */
	WTX_REQUEST,		/* service number to add to services table    */
	FUNCPTR,		/* new service input routine                  */
	FUNCPTR			/* new service output routine                 */
	)
    );

WTX_ERROR_T	wtxExchangeErrGet (WTX_XID xid);
STATUS	wtxExchangeErrClear (WTX_XID xid);
STATUS	wtxExchangeTerminate (WTX_XID xid);

STATUS	wtxExchange (WTX_XID xid, WTX_REQUEST request, void * pIn, void * pOut);
STATUS	wtxExchangeFree (WTX_XID xid, WTX_REQUEST request, void * pData);
STATUS	wtxExchangeControl (WTX_XID xid, UINT32 ctlRequest, void * pArg);
STATUS	wtxExchangeCreate (WTX_XID xid, const char * key, BOOL usePMap);
STATUS	wtxExchangeDelete (WTX_XID xid);
STATUS  wtxExchangeSvcAdd (WTX_XID xid, WTX_REQUEST request, FUNCPTR fIn,
			   FUNCPTR fOut);

extern STATUS wtxExchangeTimeoutSet	/* set the exchage timeout value      */
    (
    WTX_XID	xid,		/* transport handle to set timeout of         */
    int		timeout		/* timeout value to be set                    */
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCwtxexchh */
