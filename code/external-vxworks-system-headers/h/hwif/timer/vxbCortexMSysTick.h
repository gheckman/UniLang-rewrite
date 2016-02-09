/* vxbCortexMSysTick.h - vxbus Cortex-M system tick timer header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,19apr12,rec  written.
*/

/*
DESCRIPTION

This file provides the Cortex-M timers specific definitions.

*/

#ifndef __INCvxbCortexMSysTickh
#define __INCvxbCortexMSysTickh

#ifdef __cplusplus
extern "C" {
#endif

#define CORTEXM_SYSTICK_NAME		"CortexMSysTick"

#define CORTEXM_SYST_CSR      0xE000E010    /* control and status */
#define CORTEXM_SYST_CSR_ENABLE \
                              0x00000001    /* 1 = enable */
#define CORTEXM_SYST_CSR_TICKINT \
                              0x00000002    /* Exception enable */
#define CORTEXM_SYST_CSR_CLKSOURCE \
                              0x00000004    /* 1 = system clock, 0 = external */
#define CORTEXM_SYST_CSR_COUNTFLAG \
                              0x00010000    /* reload event - reset when read */
#define CORTEXM_SYST_RVR      0xE000E014    /* reload value (24-bit) */
#define CORTEXM_SYST_CVR      0xE000E018    /* current value (24-bit) */
#define CORTEXM_SYST_CALIB    0xE000E01c    /* calibration */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbCortexMSysTickh */
