/* vxbSmSupport.h - shared memory support library for VxBus drivers */

/*
 * Copyright (c) 2006-2007, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,06jan11,cfm  Modified the prototype of sysBusTasHelper() to align with its
                 definition. (WIND00236270)
01b,07aug07,dtr  Use extern for function ptrs.
01a,06jul06,dtr  written.
*/

/*
This module provides VxBus-compliant support for shared memory.
*/

#ifndef __INCvxbSmSupporth
#define __INCvxbSmSupporth

/* API function pointers */

struct sharedMemSupportAPI
    {
    FUNCPTR tas;
    FUNCPTR tasClear;
    FUNCPTR intGen;
    FUNCPTR intAck;
    FUNCPTR busIntInit;
    FUNCPTR mailboxInt;
    FUNCPTR mailboxEnable;
    FUNCPTR mailboxDisable;
    FUNCPTR mailboxIntInit;
    };

/* hooks */

extern void (*vxbBusTasClearHook)(char*);
extern BOOL (*vxbBusTasHook)(char*);
extern STATUS (*vxbBusIntGenHook)(int,int);
extern STATUS (*vxbBusIntAckHook)(int);

/* function declarations */

void sysBusTasClearHelper
    (
    VXB_DEVICE_ID	pInst,
    void *		adrs
    );

void sysBusTasHelper
    (
    VXB_DEVICE_ID	pInst,
    ULONG *		adrs
    );
void sysBusIntGenHelper
    (
    VXB_DEVICE_ID	pInst,
    void *		pArgs
    );
void sysBusIntAckHelper
    (
    VXB_DEVICE_ID	pInst,
    int 		intLevel
    );

#endif /* __INCvxbSmSupporth */
