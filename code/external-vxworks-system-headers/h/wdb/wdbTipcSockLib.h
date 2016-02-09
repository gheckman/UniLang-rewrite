/* wdbTipcSockLib.h - header file for remote debug agent TIPC library */

/*
 * Copyright (c) 2005, 2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,30may05,dbt	 written.
*/

#ifndef __INCwdbTipcSockLibh
#define __INCwdbTipcSockLibh

/* includes */

#include "wdb/wdbCommIfLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

extern STATUS  wdbTipcSockIfInit (WDB_COMM_IF * pCommIf,
					UINT8 tipcPortType,
					UINT8 tipcPortInstance);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbTipcSockLibh */
