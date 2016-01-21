/* stm32f2xx.h - SOC specific header file */

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
01c,02jul12,rec  fix USART base addresses
01b,02may12,rec  Moved to hwif/soc.  Split into lower level files.
01a,21mar12,jmz  Created
*/

/*
DESCRIPTION
This file contains register definitions specifc to the stm32f2xxx series SOC.

SEE ALSO:
\tb RM0033 Reference manual - STM32F205xx, STM32F207xx, STM32F215xx and STM32F217xx
advanced ARM-based 32-bit MCUs

*/

#ifndef __INCstm32f2xxh
#define __INCstm32f2xxh

#ifdef __cplusplus
extern "C" {
#endif

/* macros to manipulate registers */

#define STM32F2XX_REG_READ(address)                   \
    *(volatile UINT32 *)(address)

#define STM32F2XX_REG_WRITE(address, value)           \
    *(volatile UINT32 *)(address) = (UINT32)(value)
                        
#define STM32F2XX_SHORT_REG_WRITE(address, value)     \
    *(volatile UINT16*)(address) = value

#define STM32F2XX_SHORT_REG_READ(address)             \
    (*(volatile UINT16*)(address))

/* Region allocation for General-purpose I/O (GPIO) registers */

#define STM32F2XX_GPIO_BASE          0x40020000

/* Region allocation for Reset and Clock Control (RCC) registers */

#define STM32F2XX_RCC_BASE           0x40023800

/* Region allocation for Flash Memory Interface (FMI) registers */

#define STM32F2XX_FMI_BASE           0x40023C00

/* Region allocation for Flexible Static Memory Controller (FSMC) registers */

#define STM32F2XX_FSMC_BASE          0xA0000000

/*
 * Region allocation for Universal Synchronous Asynchronous Receiver Transmitter
 * (USART) registers
 */

#define STM32F2XX_USART1_BASE          0x40011000
#define STM32F2XX_USART2_BASE          0x40004400
#define STM32F2XX_USART3_BASE          0x40004800
#define STM32F2XX_UART4_BASE           0x40004C00
#define STM32F2XX_UART5_BASE           0x40005000
#define STM32F2XX_USART6_BASE          0x40011400

/* Region allocation for General Purpose Timer (GPT) registers */

#define STM32F2XX_TIM1_BASE            0x40001000
#define STM32F2XX_TIM2_BASE            0x40000000
#define STM32F2XX_TIM3_BASE            0x40000400
#define STM32F2XX_TIM4_BASE            0x40000800
#define STM32F2XX_TIM5_BASE            0x40000C00
#define STM32F2XX_TIM6_BASE            0x40001000
#define STM32F2XX_TIM7_BASE            0x40001400
#define STM32F2XX_TIM8_BASE            0x40010400
#define STM32F2XX_TIM9_BASE            0x40014000
#define STM32F2XX_TIM10_BASE           0x40014400
#define STM32F2XX_TIM11_BASE           0x40014800
#define STM32F2XX_TIM12_BASE           0x40001800
#define STM32F2XX_TIM13_BASE           0x40001C00
#define STM32F2XX_TIM14_BASE           0x40002000

/* Region allocation for Ethernet Driver registers */

#define STM32F2XX_ETH_BASE            0x40028000

#ifdef __cplusplus
}
#endif

#endif  /* __INCstm32f2xxh */
