/* wdbMipcSockLib.h - header file for remote debug agent MIPC library */

/*
 * Copyright (c) 2008, 2010 Wind River Systems, Inc.  
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

#ifndef __INCwdbMipcSockLibh
#define __INCwdbMipcSockLibh

/* includes */

#include "wdb/wdbCommIfLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

extern STATUS  wdbMipcSockIfInit (WDB_COMM_IF * pCommIf,
					char * mipcBusName,
					int mipcPortNumber);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbMipcSockLibh */
