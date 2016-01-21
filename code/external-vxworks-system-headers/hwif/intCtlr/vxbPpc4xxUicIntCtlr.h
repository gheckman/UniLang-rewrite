/* vxbPpc4xxUicIntCtlr.h - PPC4xx Universal Interrupt Controller driver */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,31mar08,b_m  written.
*/

/*
DESCRIPTION

This header file supplies several UIC interrupt attributes macros that are
expected to be used in hwconf.c by a specific BSP that uses this driver.
*/

#ifndef __INCvxbPpc4xxUicIntCtlrh
#define __INCvxbPpc4xxUicIntCtlrh

#ifdef __cplusplus
extern "C" {
#endif

/* UIC Registers Offsets */

#define UIC_SR                  0x00    /* Status Register */
#define UIC_SSR                 0x01    /* Set Status Register */
#define UIC_ER                  0x02    /* Enable Register */
#define UIC_CR                  0x03    /* Critical Register */
#define UIC_PR                  0x04    /* Polarity Register */
#define UIC_TR                  0x05    /* Trigger Register */
#define UIC_MSR                 0x06    /* Masked Status Register */
#define UIC_VR                  0x07    /* Vector Register */
#define UIC_VCR                 0x08    /* Vector Configuration Register */

#define UIC_NAME                "uic"

/* Vector Configuration Register */

#define UIC_PRI_HIGHEST_SR0     0x00000001
#define UIC_PRI_HIGHEST_SR31    0x00000000

/* UIC Interrupt Attributes */

#define UIC_INT_NORMAL          0x00
#define UIC_INT_CRITICAL        0x01

#define UIC_INT_LEVEL_LOW       0x00
#define UIC_INT_LEVEL_HIGH      0x02

#define UIC_INT_EDGE_FALLING    0x00
#define UIC_INT_EDGE_RISING     0x04

#define UIC_INT_LEVEL           0x00
#define UIC_INT_EDGE            0x08

#define UIC_INT_MAX_NUM         32

#define UIC_PIN_TO_BIT(pin)     (0x00000001 << (31 - (pin)))
#define UIC_PIN_TO_MASK(pin)    (0xffffffff << (32 - (pin)))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbPpc4xxUicIntCtlrh */
