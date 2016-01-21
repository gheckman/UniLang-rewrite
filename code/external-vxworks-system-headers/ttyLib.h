/* ttyLib.h - header file for terminal drivers on top of sio core drivers */

/* Copyright 1984-2004, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,20mar09,lyc  LP64 support
01d,05may04,dat  fix ttyDrv declaration, 96824
01c,15jun95,ms   updated for new serial driver.
01b,22may95,ms   removed unneded include file.
01a,21feb95,ms   written.
*/

#ifndef __INCttyLibh
#define __INCttyLibh

#include "types/vxTypes.h"
#include "sioLib.h"

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS ttyDrv (void);
extern STATUS ttyDevCreate (char * name, SIO_CHAN * pChan,
                            int rdBufSize, int wrtBufSize);

#ifdef __cplusplus
}
#endif

#endif  /* __INCttyLibh */

