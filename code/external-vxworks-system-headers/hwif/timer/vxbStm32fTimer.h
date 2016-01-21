
/* vxbStm32fTimer.h - vxbus STM32F20x/STM32F21x timer header file */

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
01a,26apr12,rec  written.
*/

/*
DESCRIPTION

This file provides the ARM Cortex-M STM32F20x/STM32F21x General Purpose timer
specific definitions

*/

#ifndef __INCvxbStm32fTimerh
#define __INCvxbStm32fTimerh

#ifdef __cplusplus
extern "C" {
#endif

#define STM32F_TIMER_NAME		"vxbStm32fTimer"

/* Control Register 1 */
#define STM32FTIM_CR1            0x0000 /* Register offset */
#define STM32FTIM_CR1CEN     0x00000001 /* Counter enable */
#define STM32FTIM_CR1UDIS    0x00000002 /* Update disable */
#define STM32FTIM_CR1URS     0x00000004 /* Update request src, 1=overflow only*/
#define STM32FTIM_CR1OPM     0x00000008 /* One pules mode */
#define STM32FTIM_CR1DIR     0x00000010 /* Direction, 1=down */
#define STM32FTIM_CR1CMSMSK  0x00000060 /* Center-aligned mask (leave zero) */
#define STM32FTIM_CR1ARPE    0x00000080 /* Auto-reload preload enable */
#define STM32FTIM_CR1CKDMSK  0x00000300 /* Clock division mask */
#define STM32FTIM_CR1CKD1X   0x00000000 /* Clock division 1x */
#define STM32FTIM_CR1CKD2X   0x00000100 /* Clock division 2x */
#define STM32FTIM_CR1CKD4x   0x00000200 /* Clock division 4x */

/* Control Register 2 */
#define STM32FTIM_CR2            0x0004 /* Register offset */
#define STM32FTIM_CR2CCDS    0x00000008 /* Capture/compare DMA selection */
#define STM32FTIM_CR2MMSMSK  0x00000070 /* Master mode selection mask */
#define STM32FTIM_CR2TI1S    0x00000080 /* TI1 selection */

/* Slave Mode Control Register */
#define STM32FTIM_SMCR           0x0008 /* Register offset */
#define STM32FTIM_SMCRSMSMSK 0x00000003 /* Slave mode select mask */
#define STM32FTIM_SMCRTSMSK  0x00000070 /* Trigger selection mask */
#define STM32FTIM_SMCRMSMMSK 0x00000080 /* Master/slave mode */
#define STM32FTIM_SMCRETFMSK 0x00000F00 /* External trigger filter mask */
#define STM32FTIM_SMCRETPSOFF 0x00000000 /* External trigger prescaler OFF */
#define STM32FTIM_SMCRETPS2  0x00001000 /* External trigger prescale /2 */
#define STM32FTIM_SMCRETPS4  0x00002000 /* External trigger prescale /4 */
#define STM32FTIM_SMCRETPS8  0x00003000 /* External trigger prescale /8 */
#define STM32FTIM_SMCRECE    0x00004000 /* External clock enable */
#define STM32FTIM_SMCRETP    0x00008000 /* External trigger polarity 1=low>hi */

/* DMA/Interrupt Enable Register */
#define STM32FTIM_DIER          0x0000C /* Register offset */
#define STM32FTIM_DIERUIE    0x00000001 /* Update interrupt enable */
#define STM32FTIM_DIERCC1IE  0x00000002 /* Capture/Compare 1 interrupt enable */
#define STM32FTIM_DIERCC2IE  0x00000004 /* Capture/Compare 2 interrupt enable */
#define STM32FTIM_DIERCC3IE  0x00000008 /* Capture/Compare 3 interrupt enable */
#define STM32FTIM_DIERCC4IE  0x00000010 /* Capture/Compare 4 interrupt enable */
#define STM32FTIM_DIERTIE    0x00000040 /* Trigger interrupt enable */
#define STM32FTIM_DIERUDE    0x00000100 /* Update DMA request enble */
#define STM32FTIM_DIERCC1DE  0x00000200 /* Capture/Compare 1 DMA req enable */
#define STM32FTIM_DIERCC2DE  0x00000400 /* Capture/Compare 2 DMA req enable */
#define STM32FTIM_DIERCC3DE  0x00000800 /* Capture/Compare 3 DMA req enable */
#define STM32FTIM_DIERCC4DE  0x00001000 /* Capture/Compare 4 DMA req enable */
#define STM32FTIM_DIERTDE    0x00004000 /* Trigger DMA request enable */

/* Timer Status Register */
#define STM32FTIM_SR             0x0010 /* Register offset */
#define STM32FTIM_SRUIF      0x00000001 /* Update interrupt flag */
#define STM32FTIM_SRCC1IF    0x00000002 /* Capture/compare 1 interrupt flag */
#define STM32FTIM_SRCC2IF    0x00000004 /* Capture/compare 2 interrupt flag */
#define STM32FTIM_SRCC3IF    0x00000008 /* Capture/compare 3 interrupt flag */
#define STM32FTIM_SRCC4IF    0x00000010 /* Capture/compare 4 interrupt flag */
#define STM32FTIM_SRTIF      0x00000040 /* Trigger interrupt flag */
#define STM32FTIM_SRCC1OF    0x00000200 /* Capture/compare 1 overcapture flag */
#define STM32FTIM_SRCC2OF    0x00000400 /* Capture/compare 2 overcapture flag */
#define STM32FTIM_SRCC3OF    0x00000800 /* Capture/compare 3 overcapture flag */
#define STM32FTIM_SRCC4OF    0x00001000 /* Capture/compare 4 overcapture flag */

/* Event Generation Register */
#define STM32FTIM_EGR            0x0014 /* Register offset */
#define STM32FTIM_EGRUG      0x00000001 /* Update generation */
#define STM32FTIM_EGRCC1G    0x00000002 /* Capture/comare 1 generation */
#define STM32FTIM_EGRCC2G    0x00000004 /* Capture/comare 2 generation */
#define STM32FTIM_EGRCC3G    0x00000008 /* Capture/comare 3 generation */
#define STM32FTIM_EGRCC4G    0x00000010 /* Capture/comare 4 generation */
#define STM32FTIM_EGRTG      0x00000040 /* Trigger generation */

/* Timer Count Register (32-bit) */
#define STM32FTIM_CNT            0x0024 /* Register offset */
 
/* Prescaler Register */
#define STM32FTIM_PSC            0x0028 /* Register offset */
#define STM32FTIM_PSCMSK     0x0000FFFF /* Prescaler mask */

/* Auto-reload Register (32-bits) */
#define STM32FTIM_ARR            0x002C /* Register offset */

/* 
 * The following registers are used in capture/compare mode only.
 * This feature is unsupported.
 */

/* Capture Compare Mode Register 1 */
#define STM32FTIM_CCMR1          0x0018 /* Register offset */

/* Capture Compare Mode Register 2 */
#define STM32FTIM_CCMR2          0x001C /* Register offset */
 
/*  Capture Compare Mode Interrupt Enable Register */
#define STM32FTIM_CCER           0x0020 /* Register offset */
 

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbStm32fTimerh */
