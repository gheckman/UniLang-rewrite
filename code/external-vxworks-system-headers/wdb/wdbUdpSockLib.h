/* wdbUdpSockLib.h - header file for remote debug agents UDP library */

/*
 * Copyright (c) 1995, 2002, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use  of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01e,17mar11,rlp  Modified wdbUdpSockIfInit prototype to pass an IP address.
01d,29apr10,pad  Moved extern C statement after include statements.
01c,25apr02,jhw  Added C++ support (SPR 76304).
01b,05apr95,ms  new data types.
01a,08mar95,ms  written.
*/

#ifndef __INCwdbUdpSockLibh
#define __INCwdbUdpSockLibh

/* includes */

#include "wdb/wdbCommIfLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

extern STATUS  wdbUdpSockIfInit (WDB_COMM_IF *pCommIf, char * ipAddr);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbUdpSockLibh */
