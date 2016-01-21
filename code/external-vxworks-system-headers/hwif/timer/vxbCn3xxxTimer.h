/* vxbCn3xxxTimer.h - Cavium  timer driver   */

/*
 * Copyright (c) 2010  Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,19jul10,rlg  created.
*/

#ifndef __INCvxbCn3xxxTimerh
#define __INCvxbCn3xxxTimerh

/*
 * address of  core clock count register
 * number of cycles since release of reset
 * read only 
 */
#define CAV_IPD_CLK_COUNT 0x80014f0000000338ull

/* 
 * base address of timers
 */
#define CAV_CIU_TIMX 0x8001070000000480ull
#define CAV_CIU_TIMX_SP 0x8

#define CAV_CIU_TIMER(unit) \
    (CAV_CIU_TIMX + ((unit) * CAV_CIU_TIMX_SP ))


/* BIT MASK AND SHIFT FOR TIMER REGISTERS */

#define CAV_CIU_TIMER_MODE_SHIFT         36
#define CAV_CIU_TIMER_MODE_MASK          0x0000000000000001ull



#endif /* __INCvxbCn3xxxTimerh */

