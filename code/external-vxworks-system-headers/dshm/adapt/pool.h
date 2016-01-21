/* pool.h - dSHM network buffer and pools */

/*
 * Copyright (c) 2006-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01e,29apr10,pad  Moved extern C statement after include statements.
01d,08jun07,bwa  added sm buffer manipulation.
01c,02mar07,bwa  more buffer manipulation macros.
01b,21feb07,bwa  added network buffer manipulation.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmadaptpoolh
#define __INCdshmadaptpoolh

#include <wrn/coreip/netBufLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DSHM_NET_BUF M_BLK_ID
#define DSHM_SM_BUF  DSHM_LIST_NODE

void * dshmAdaptNetPoolCreate ( void * const pSmPool,
				    const int smPoolSize,
				    const int smBufferSize )
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");
STATUS dshmAdaptNetPoolDelete ( void * const pNetPool ) 
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_GET - obtain a network buffer from a buffer pool
*
* The buffer obtained is of type DSHM_NET_BUF.
*
* RETURNS: a pointer to the buffer or NULL if none available
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_GET(pNetPool) \
    netMblkGet((pNetPool), M_DONTWAIT, MT_DATA)

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_RELEASE - release a buffer back to its originating pool
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_RELEASE(pBuf) netMblkClFree (pBuf)

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_NEXT_GET - obtain the next buffer in a chain
*
* The buffer obtained is of type DSHM_NET_BUF
*
* CAUTION: The <pBuf> must be a real buffer: no check is done on its validity.
*
* RETURNS: a pointer to the next buffer or NULL if this buffer was the tail
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_NEXT_GET(pBuf) (pBuf)->mBlkHdr.mNext

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_NEXT_SET - add a buffer to a chain
*
* Add a buffer <pBuf> to a chain, by chaining the buffer to the tail <pTail>.
* Care must be taken to pass in the last buffer of a chain as the tail. If the
* buffer passed-in as the tail is not a real tail, the reference to buffers
* chained to it will be overwritten.
*
* CAUTION: The <pTail> must be a real buffer: no check is done on its validity.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_NEXT_SET(pTail, pBuf) \
    do { (pTail)->mBlkHdr.mNext = (pBuf); } while ((0))

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_PREPARE_FOR_STACK - prepare a buffer to be handed to stack
*
* Does OS custom preparation of a buffer before it is handed to protocol stack.
*
* CAUTION: The <pBuf> must be a real buffer: no check is done on its validity.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_PREPARE_FOR_STACK(pBuf) \
    do { (pBuf)->mBlkHdr.mFlags |= M_PKTHDR; } while ((0))

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_DATA_GET - obtain pointer to data portion of buffer
*
* CAUTION: The <pBuf> must be a real buffer: no check is done on its validity.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_DATA_GET(pBuf) \
    (pBuf)->mBlkHdr.mData

/*******************************************************************************
*
* DSHM_ADAPT_NET_BUF_LEN_SET - set length of data stored in buffer
*
* CAUTION: The <pBuf> must be a real buffer: no check is done on its validity.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_NET_BUF_LEN_SET(pBuf, size) \
    do { (pBuf)->mBlkPktHdr.len = (pBuf)->mBlkHdr.mLen = (size); } while ((0))

/*******************************************************************************
*
* DSHM_ADAPT_SM_BUF_DATA_GET - obtain data portion from an sm buffer
*
* CAUTION: The <pBuf> must be a real buffer: no check is done on its validity.
*
* RETURNS: N/A
*
* NOMANUAL
*/

#define DSHM_ADAPT_SM_BUF_DATA_GET(pBuf) \
    ((char *)pBuf + sizeof (DSHM_LIST_NODE))

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmadaptpoolh */
 

