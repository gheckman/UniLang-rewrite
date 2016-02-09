
/* vxbK70Timer.h - vxbus Freescale K70 timer header file */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,20jun13,mpc  written.
*/

/*
DESCRIPTION

This file provides the ARM Cortex-M Freescale K70  timer specific definitions.

*/

#ifndef __INCvxbK70Timerh
#define __INCvxbK70Timerh

#ifdef __cplusplus
extern "C" {
#endif

#define K70_TIMER_NAME		"vxbK70Timer"

/* register offset */

#define K70_PIT_MCR             0x0   /* PIT Module Control Register offset */

#define K70_PIT_LDVAL           0x0   /* Timer Load Value Register offset */

#define K70_PIT_CVAL            0x4   /* Current Timer Value Register offset */ 

#define K70_PIT_TCTRL           0x8   /* Timer Control Register offset */

#define K70_PIT_TFLG            0xc   /* Timer Flag Register offset */

#define K70_PIT_TCTRL_TIE       0x2   /* Timer Interrupt Enable */
#define K70_PIT_TCTRL_TEN       0x1   /* Timer Enable */

#define K70_PIT_TFLG_TIF        0x1   /* Timer Interrupt Flag */

#define K70_PIT_MCR_FRZ         0x1   /* Freeze in debug */
#ifdef __cplusplus
}
#endif

#endif /* __INCvxbK70Timerh */

