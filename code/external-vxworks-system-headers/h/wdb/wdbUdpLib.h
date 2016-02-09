/* wdbUdpLib.h - header file for remote debug agents UDP library */

/* Copyright 1984-2002, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,25apr02,jhw  Added C++ support (SPR 76304).
01b,05apr95,ms  new data types.
01a,20dec94,ms  written.
*/

#ifndef __INCwdbUdpLibh
#define __INCwdbUdpLibh

/* includes */

#include "wdb/wdbCommIfLib.h"
#include "wdb/wdbMbufLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

#if defined(__STDC__)

extern STATUS	udpCommIfInit (WDB_COMM_IF *pWdbCommIf, WDB_DRV_IF *pDrvIf);
extern void     udpRcv        (struct mbuf *pMbuf);

#else   /* __STDC__ */

extern STATUS	udpCommIfInit ();
extern void     udpRcv        ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbUdpLibh */
