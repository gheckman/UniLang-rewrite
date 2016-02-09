/* vxbEndQctrl.h - vxbEndQctrl header file */

/*
 * Copyright (c) 2007-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/* 
modification history
--------------------
01b,03mar09,h_k  added prototype for vxbEndRxQParamRestore(),
                 vxbEndDevQueueSet(), vxbEndQueueSet().
01a,10oct07,dlk  Written.
*/


#ifndef __INCvxbEndQctrlh
#define __INCvxbEndQctrlh 

#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>
#include <jobQueueLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS vxbEndQctrlInit (void);
extern STATUS vxbEndQnumSet (char * instName, int unit, unsigned int qnum);
extern STATUS vxbEndRxQParamRestore
    (
    char * instName,            /* VxBus device instance name */
    int unit                    /* device unit number */
    );
extern STATUS vxbEndDevQueueSet
    (
    VXB_DEVICE_ID pDev,
    JOB_QUEUE_ID  qId
    );
extern STATUS vxbEndQueueSet
    (
    char * instName,
    int unit,
    JOB_QUEUE_ID  qId
    );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbEndQctrlh */ 
