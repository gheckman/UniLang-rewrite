/* vxbDevPwr.h - vxBus device power states context header file */

/*
 * Copyright (c) 2010, 2011 Wind River Systems, Inc. All rights are reserved.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,11feb11,w_x remove lock in DSTATE_FUNC_CONTEXT
01a,15nov10,dbr created
*/

#ifndef _VXB_DEV_PWR_H
#define _VXB_DEV_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Device power states */

#define DEVICE_STATE_D0         0 /* D0 Fully-On is the operating state */
#define DEVICE_STATE_D1         1 /* intermediate power-state - retention */
#define DEVICE_STATE_D2         2 /* intermediate power-state */
#define DEVICE_STATE_D3         3 /* D3 power off state */
#define DEVICE_STATE_UNKNOWN    0xFFFF /* unknown state */

/* Device set state callback function */

typedef void (*DSTATE_SET_FUNC)
    (
    UINT32 dState,
    void *dStateContext
    );

/* Device state context struct */

typedef struct dStateFuncContext
    {
    DSTATE_SET_FUNC dStateSet; /* device DState function */
    void *dStateContext;       /* device context */
    } DSTATE_FUNC_CONTEXT;

#ifdef __cplusplus
}
#endif

#endif /* _VXB_DEV_PWR_H */
