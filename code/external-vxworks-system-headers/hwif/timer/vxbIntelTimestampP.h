/* vxbIntelTimestampP.h - private Intel Architecture timestamp header */

/* 
 * Copyright (c) 2011 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,02aug11,j_l  WIND00255353: created
*/

#ifndef __INCvxbIntelTimestampPh
#define __INCvxbIntelTimestampPh

#ifdef __cplusplus
extern "C" {
#endif

/* structure holding timestamp details */

struct iaTimestampData
    {
    struct vxbTimerFunctionality timerFunc; /* 
                                             * functionality of the timer
                                             * used by the 
                                             * application/timer library
                                             */
    UINT32                       divider;   /* */
    VXB_DEVICE_ID                pInst;     /* instance pointer */
    spinlockIsr_t                lock;      /* spin lock for protection */
    BOOL                         timerInitialized;/* timer initialized flag */
    UINT32                       timestampBase; /* timestamp base value */
    WDOG_ID                      wdId;      /* watchdog id */    
    BOOL                         hpetUsed;  /* indicate whether HPET is used */
    };

/* structure to be used in watchdog timer function */

struct iaTimestampWdData
    {
    UINT32                      initialCount; /* initial count */
    struct iaTimestampData *    pTimerData;   /* timestamp data */
    };

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbIntelTimestampPh */
