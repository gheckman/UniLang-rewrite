/* isrDeferLibP.h - Task-level support for ISR deferral */

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
01b,02mar09,h_k  updated for LP64 support.
01a,20mar07,sru  written
*/

#ifndef __INCisrDeferLibPh
#define __INCisrDeferLibPh

#include <vxWorks.h>
#include <lstLib.h>
#include <spinLockLib.h>
#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct isrDeferQueue
    {
    LIST 		list;	  /* list of pending work */
    SEMAPHORE		syncSem;  /* given by ISR, taken by task */
    spinlockIsr_t	lock;     /* for list maintenance operations */
    TASK_ID		tid;	  /* deferral task id */
    int			cpuIdx;	  /* CPU for task handling this queue */
    } ISR_DEFER_QUEUE;

#ifdef __cplusplus
}
#endif

#endif /* __INCisrDeferLibPh */
