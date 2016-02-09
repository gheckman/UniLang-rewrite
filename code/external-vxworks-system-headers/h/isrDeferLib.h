/* isrDeferLib.h - Task-level support for ISR deferral */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01c,07may07,h_k  added an extra arg isrDeferQueueGet() for a future support.
                 added a global mode arg to isrDeferLibInit();
01b,20mar07,sru  factor into public and private headers
01a,02feb07,sru  written
*/

#ifndef __INCisrDeferLibh
#define __INCisrDeferLibh

#include <vxWorks.h>
#include <lstLib.h>
#include <vxBusLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * There are two ways to implement deferral.  A shared queue for each CPU,
 * or an individual queue for each interrupt source.  This is global mode
 * for the SMP system.
 */

#define ISR_DEFER_MODE_PER_CPU		0
#define ISR_DEFER_MODE_PER_SOURCE	1


/* typedefs */

typedef struct isrDeferJob
    {
    NODE node;			/* for chaining deferred work */
    void (*func)(void *);	/* deferral function */
    void *pData; 		/* pointer to driver-specific data */
    } ISR_DEFER_JOB;

typedef struct isrDeferQueue * ISR_DEFER_QUEUE_ID;

/* function declarations */

STATUS isrDeferLibInit
    (
    int	mode			/* global deferral queue mode */
    );

ISR_DEFER_QUEUE_ID isrDeferQueueGet 
    (
    VXB_DEVICE_ID   pInst,	/* VxBus device ID of requester, or NULL */
    int		    intIdx,	/* interrupt source index */
    int		    cpuIdx,	/* CPU index for deferral task */
    int		    mode	/* deferral queue mode (for future use) */
    );

void isrDeferJobAdd 
    (
    ISR_DEFER_QUEUE_ID queueId,	/* deferral queue handling these jobs */
    ISR_DEFER_JOB *    pJob	/* work to defer */
    );

ISR_DEFER_QUEUE_ID isrDeferIsrReroute
    (
    ISR_DEFER_QUEUE_ID queueId,	/* queue allocated by isrDeferQueueGet */
    int		       cpuIdx	/* CPU to handle this queue's interrerupts */
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCisrDeferLibh */
