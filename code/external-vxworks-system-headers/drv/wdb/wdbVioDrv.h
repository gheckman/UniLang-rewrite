/* wdbVioDrv.h - header file for remote debug packet library */

/*
 * Copyright 1995,2002,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,04feb10,rlp  Updated wdbVioDrv prototype.
01b,26apr02,dat  Adding cplusplus protection, SPR 75017
01a,28jun95,ms   written.
*/

#ifndef __INCwdbVioDrvh
#define __INCwdbVioDrvh

/* includes */

#include <wdb/wdb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function prototypes */

extern STATUS	wdbVioDrv (char * devName);

#ifdef __cplusplus
}
#endif

#endif  /* __INCwdbVioDrvh */

