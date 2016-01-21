/* vbFrameSchedIntHook.h - VB frame scheduler start and end interrupt hook */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,11jun10,l_z  Written.
*/

#ifndef __INCvbFrameSchedIntHookh
#define __INCvbFrameSchedIntHookh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

/* the frame schedule interrupt type */

typedef enum
    {
    VB_FRAME_START    = 0,
    VB_FRAME_END      = 1
    } VB_FRAME_SCHED_INT_TYPE;

/* Enable VB schedule interrupts */

STATUS   vbFrameSchedIntEnable (VB_FRAME_SCHED_INT_TYPE, FUNCPTR, int);

/* Disable VB schedule interrupts */

STATUS   vbFrameSchedIntDisable (VB_FRAME_SCHED_INT_TYPE);

/* Initializes the VB scheduler interrupt vector */

void     vbFrameSchedIntInit (void);

/* Connects the VB scheuler interrupts */

void     vbFrameSchedIntInit2 (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbFrameSchedIntHookh */
