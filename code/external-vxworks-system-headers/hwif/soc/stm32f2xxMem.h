/* stm32f2xxMem.h - STM32F20x/STM32F21x memory subsystem header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,16jul12,rec  Flash memory bank address error
01b,10may12,rec  add flash registers
01a,02may12,rec  Created - Content extracted from stm32f2xx.h v01a
*/

/*
DESCRIPTION
This file contains register definitions specifc to the STM32F20x/STM32F21x 
flash and static memory interface registers.

SEE ALSO:
\tb RM0033 Reference manual STM32F205xx, STM32F207xx, STM32F215xx and 
STM32F217xx advanced ARM-based 32-bit MCUs, DEC 2011
\tb PM0059 Programming manual STM32F205xx, STM32F207xx, STM32F215xx and 
STM32F217xx, Flash programming manual, MAY 2011
*/

#ifndef __INCstm32f2xxMemh
#define __INCstm32f2xxMemh

#ifdef __cplusplus
extern "C" {
#endif

/* FLASH Access Control Register */

#define   STM32F2XX_FMI_ACR          (STM32F2XX_FMI_BASE + 0x00)
#define   STM32F2XX_FMI_ACR_LATENCY0 0x00000000 /* 0 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY1 0x00000001 /* 1 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY2 0x00000002 /* 2 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY3 0x00000003 /* 3 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY4 0x00000004 /* 4 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY5 0x00000005 /* 5 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY6 0x00000006 /* 6 wait states */
#define   STM32F2XX_FMI_ACR_LATENCY7 0x00000007 /* 7 wait states */
#define   STM32F2XX_FMI_ACR_PRFTEN   0X00000100 /* Prefetch enable */
#define   STM32F2XX_FMI_ACR_ICEN     0X00000200 /* Instruction cache enable */
#define   STM32F2XX_FMI_ACR_DCEN     0X00000400 /* Data cache enable */
#define   STM32F2XX_FMI_ACR_ICRST    0X00000800 /* Instruction cache reset */
#define   STM32F2XX_FMI_ACR_DCRST    0X00001000 /* Data cache reset */

/* FLASH Key Register */

#define   STM32F2XX_FMI_KEYR         (STM32F2XX_FMI_BASE + 0x04)
#define   STM32F2XX_FMI_KEY1         0x45670123  
#define   STM32F2XX_FMI_KEY2         0xCDEF89AB

/* FLASH Options Key Register */
#define   STM32F2XX_FMI_OPTKEYR      (STM32F2XX_FMI_BASE + 0x08)
#define   STM32F2XX_FMI_OPTKEY1      0x08192A3B
#define   STM32F2XX_FMI_OPTKEY2      0x4C5D6E7F

/* FLASH Status Register */
#define   STM32F2XX_FMI_SR           (STM32F2XX_FMI_BASE + 0x0C)
#define   STM32F2XX_FMI_SR_EOP       0x00000001 /* End of operation */
#define   STM32F2XX_FMI_SR_OPERR     0x00000002 /* Operation error */
#define   STM32F2XX_FMI_SR_WRPERR    0x00000010 /* Write protect error */
#define   STM32F2XX_FMI_SR_PGAERR    0x00000020 /* Programming alignment error*/
#define   STM32F2XX_FMI_SR_PGPERR    0x00000040 /* Programming parallism error*/
#define   STM32F2XX_FMI_SR_PGSERR    0x00000080 /* Programming sequence error */
#define   STM32F2XX_FMI_SR_BSY       0x00010000 /* Busy */

/* FLASH Control Register */
#define   STM32F2XX_FMI_CR           (STM32F2XX_FMI_BASE + 0x10)
#define   STM32F2XX_FMI_CR_PG        0x00000001 /* Programming */
#define   STM32F2XX_FMI_CR_SER       0x00000002 /* Sector erase */
#define   STM32F2XX_FMI_CR_MER       0x00000004 /* Mass erase */
#define   STM32F2XX_FMI_CR_SNB(arg)  (arg << 3) /* Sector number */
#define   STM32F2XX_FMI_CR_SMSK      0x00000078 /* Sector number mask */
#define   STM32F2XX_FMI_CR_PSIZE8    0x00000000 /* Program size 8*/
#define   STM32F2XX_FMI_CR_PSIZE16   0x00000100 /* Program size 16 */
#define   STM32F2XX_FMI_CR_PSIZE32   0x00000200 /* Program size 32 */
#define   STM32F2XX_FMI_CR_PSIZE64   0x00000300 /* Program size 64 */
#define   STM32F2XX_FMI_CR_PSIZEMSK  0x00000300 /* Program size mask */
#define   STM32F2XX_FMI_CR_STRT      0x00010000 /* Start */
#define   STM32F2XX_FMI_CR_EOPIE     0x01000000 /* End of op interrupt enable */
#define   STM32F2XX_FMI_CR_ERRIE     0x02000000 /* Error interrupt enable */
#define   STM32F2XX_FMI_CR_LOCK      0x80000000 /* Lock */

/* FLASH Options Control */
#define   STM32F2XX_FMI_OPTCR        (STM32F2XX_FMI_BASE + 0x14)
#define   STM32F2XX_FMI_OPTCR_LOCK   0x00000001 /* Options lock */
#define   STM32F2XX_FMI_OPTCR_STRT   0x00000002 /* Option start */
#define   STM32F2XX_FMI_OPTCR_VBOR0  0x0000000C /* 1.8V..2.1V */
#define   STM32F2XX_FMI_OPTCR_VBOR1  0x00000008 /* 2.1V..2.4V */
#define   STM32F2XX_FMI_OPTCR_VBOR2  0x00000004 /* 2.4V..2.7V */
#define   STM32F2XX_FMI_OPTCR_VBOR3  0x00000000 /* 2.7V..3.6V */
#define   STM32F2XX_FMI_OPTCR_WDGSW  0x00000020 /* User option */
#define   STM32F2XX_FMI_OPTCR_RSTSTOP 0x00000040 /* User option */
#define   STM32F2XX_FMI_OPTCR_RSTSTBY 0x00000080 /* User option */
#define   STM32F2XX_FMI_OPTCR_RDP_OFF 0x0000AA00 /* No read protect */
#define   STM32F2XX_FMI_OPTCR_RDP_CHP 0x0000CC00 /* Chip read protect */
#define   STM32F2XX_FMI_OPTCR_RDP_MEM 0x00000000 /* Memory read protect */
#define   STM32F2XX_FMI_OPTCR_WEN(arg) (arg <<16) /* Write enable sector */

/* Flash sector base addresses */
#define   STM32F2XX_FLASHSECT00      0x08000000   
#define   STM32F2XX_FLASHSECT01      0x08004000   
#define   STM32F2XX_FLASHSECT02      0x08008000   
#define   STM32F2XX_FLASHSECT03      0x0800C000   
#define   STM32F2XX_FLASHSECT04      0x08010000   
#define   STM32F2XX_FLASHSECT05      0x08020000   
#define   STM32F2XX_FLASHSECT06      0x08040000   
#define   STM32F2XX_FLASHSECT07      0x08060000   
#define   STM32F2XX_FLASHSECT08      0x08080000   
#define   STM32F2XX_FLASHSECT09      0x080A0000   
#define   STM32F2XX_FLASHSECT10      0x080C0000   
#define   STM32F2XX_FLASHSECT11      0x080E0000   

/* Flash sector sizes */
#define   STM_SZ16K (16 * 1024)
#define   STM_SZ64K (64 * 1024)
#define   STM_SZ128K (128 * 1024)
#define   STM32F2XX_FLASHSECT_SZ00      STM_SZ16K   
#define   STM32F2XX_FLASHSECT_SZ01      STM_SZ16K   
#define   STM32F2XX_FLASHSECT_SZ02      STM_SZ16K   
#define   STM32F2XX_FLASHSECT_SZ03      STM_SZ16K   
#define   STM32F2XX_FLASHSECT_SZ04      STM_SZ64K   
#define   STM32F2XX_FLASHSECT_SZ05      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ06      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ07      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ08      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ09      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ10      STM_SZ128K   
#define   STM32F2XX_FLASHSECT_SZ11      STM_SZ128K   


#define   STM32F2XX_FSMC_BCR1                (STM32F2XX_FSMC_BASE + 0x0)
#define   STM32F2XX_FSMC_BTR1                (STM32F2XX_FSMC_BASE + 0x4)
#define   STM32F2XX_FSMC_BWTR1               (STM32F2XX_FSMC_BASE + 0x104)
#define   STM32F2XX_FSMC_BCR2                (STM32F2XX_FSMC_BASE + 0x8)
#define   STM32F2XX_FSMC_BTR2                (STM32F2XX_FSMC_BASE + 0xC)
#define   STM32F2XX_FSMC_BWTR2               (STM32F2XX_FSMC_BASE + 0x10C)
#define   STM32F2XX_FSMC_BCR3                (STM32F2XX_FSMC_BASE + 0x10)
#define   STM32F2XX_FSMC_BTR3                (STM32F2XX_FSMC_BASE + 0x14)
#define   STM32F2XX_FSMC_BWTR3               (STM32F2XX_FSMC_BASE + 0x114)
#define   STM32F2XX_FSMC_BCR4                (STM32F2XX_FSMC_BASE + 0x18)
#define   STM32F2XX_FSMC_BTR4                (STM32F2XX_FSMC_BASE + 0x1C)
#define   STM32F2XX_FSMC_BWTR4               (STM32F2XX_FSMC_BASE + 0x11C)
#define   STM32F2XX_FSMC_PCR2                (STM32F2XX_FSMC_BASE + 0x60)
#define   STM32F2XX_FSMC_PCR3                (STM32F2XX_FSMC_BASE + 0x80)
#define   STM32F2XX_FSMC_PCR4                (STM32F2XX_FSMC_BASE + 0xA0)
#define   STM32F2XX_FSMC_SR2                 (STM32F2XX_FSMC_BASE + 0x64)
#define   STM32F2XX_FSMC_SR3                 (STM32F2XX_FSMC_BASE + 0x84)
#define   STM32F2XX_FSMC_SR4                 (STM32F2XX_FSMC_BASE + 0xA4)
#define   STM32F2XX_FSMC_PMEM2               (STM32F2XX_FSMC_BASE + 0x68)
#define   STM32F2XX_FSMC_PMEM3               (STM32F2XX_FSMC_BASE + 0x88)
#define   STM32F2XX_FSMC_PMEM4               (STM32F2XX_FSMC_BASE + 0xA8)
#define   STM32F2XX_FSMC_PATT2               (STM32F2XX_FSMC_BASE + 0x6C)
#define   STM32F2XX_FSMC_PATT3               (STM32F2XX_FSMC_BASE + 0x8C)
#define   STM32F2XX_FSMC_PATT4               (STM32F2XX_FSMC_BASE + 0xAC)
#define   STM32F2XX_FSMC_PIO4                (STM32F2XX_FSMC_BASE + 0xB0)
#define   STM32F2XX_FSMC_ECCR2               (STM32F2XX_FSMC_BASE + 0x74)
#define   STM32F2XX_FSMC_ECCR3               (STM32F2XX_FSMC_BASE + 0x94)

#ifdef __cplusplus
}
#endif


#endif  /* __INCstm32f2xxMemh */
