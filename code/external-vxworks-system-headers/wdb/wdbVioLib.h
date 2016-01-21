/* wdbVioLib.h - VIO header file for remote debug server */

/*
 * Copyright 1994-1998,2002,2007,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,29apr10,pad  Moved extern C statement after include statements.
01k,04feb10,rlp  Removed wdbVioDrv prototype.
01j,03feb10,rlp  LP64 adaptation.
01i,04jul07,rlp  Modified wdbVioChannelUnregister prototype.
01h,25apr02,jhw  Added C++ support (SPR 76304).
01g,27may98,cth removed get snd/rcv buffer ioctl commands for tsfs sockets
01f,19mar98,cth add ioctl commands for tsfs sockets
01e,18aug97,cth add FIOSNDURGB ioctl cmd for tsfs
01d,12nov96,c_s add wdbTsfsDrv prototype
01c,24may95,ms  added wdbVioChannelUnregister().
01b,05apr95,ms  new data types.
01a,15nov94,ms  written.
*/

#ifndef __INCwdbVioLibh
#define __INCwdbVioLibh

/* includes */

#include <wdb/wdb.h>
#include <wdb/dll.h>

#ifdef __cplusplus
extern "C" {
#endif

/* data types */

typedef struct wdb_vio_node
    {
    dll_t	node;
    UINT32      channel;
    UINT32	(*inputRtn)
			(
			struct wdb_vio_node *	pNode,
			char *			pData,
			UINT32			nBytes);
    void *      pVioDev;
    } WDB_VIO_NODE;

/* ioctl commands for Target-Server File System (TSFS) */

#define SO_SNDURGB	5000	/* send an out-of-band byte on sock */
#define SO_SETDEBUG	5001	/* setsockopt SO_DEBUG for sock (int) */
#define SO_GETDEBUG	5002	/* getsockopt SO_DEBUG for sock (int) */
#define SO_SETSNDBUF	5003	/* setsockopt SO_SNDBUF for sock (int) */
#define SO_SETRCVBUF	5005	/* setsockopt SO_RCVBUF for sock (int) */
#define SO_SETDONTROUTE	5007	/* setsockopt SO_DONTROUTE for sock (int) */
#define SO_GETDONTROUTE	5008	/* getsockopt SO_DONTROUTE for sock (int) */
#define SO_SETOOBINLINE	5009	/* setsockopt SO_OOBINLINE for sock (int) */
#define SO_GETOOBINLINE	5010	/* getsockopt SO_OOBINLINE for sock (int) */
			

/* function prototypes */

extern void	wdbVioLibInit	  	(void);
extern STATUS	wdbVioChannelRegister	(WDB_VIO_NODE *pVioNode);
extern STATUS	wdbVioChannelUnregister (WDB_VIO_NODE *pVioNode);
extern STATUS	wdbTsfsDrv		(char * root);

#ifdef __cplusplus
}
#endif

#endif /* __INCwdbVioLibh */
