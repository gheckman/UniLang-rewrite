
/* stm32f2xxRcc.h - STM32F20x/STM32F21x reset and clock control header file */

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
01c,03jul12,m_h  APB1 bit definitions
01b,24may12,jmz  added bit field definitions for AHB1ENR and APB1ENR registers
01a,02may12,rec  Created - Content extracted from stm32f2xx.h v01a
*/

/*
DESCRIPTION
This file contains register definitions specifc to the STM32F20x/STM32F21x 
reset and clock control interface registers.

SEE ALSO:
\tb RM0033 Reference manual STM32F205xx, STM32F207xx, STM32F215xx and STM32F217xx
advanced ARM-based 32-bit MCUs, DEC 2011

*/

#ifndef __INCstm32f2xxRcch
#define __INCstm32f2xxRcch

#ifdef __cplusplus
extern "C" {
#endif

/* Base register definitions */

#define   STM32F2XX_RCC_CR                   (STM32F2XX_RCC_BASE + 0x0)
#define   STM32F2XX_RCC_PLLCFGR              (STM32F2XX_RCC_BASE + 0x4)
#define   STM32F2XX_RCC_CFGR                 (STM32F2XX_RCC_BASE + 0x8)
#define   STM32F2XX_RCC_CIR                  (STM32F2XX_RCC_BASE + 0xC)
#define   STM32F2XX_RCC_AHB1RSTR             (STM32F2XX_RCC_BASE + 0x10) 
#define   STM32F2XX_RCC_AHB2RSTR             (STM32F2XX_RCC_BASE + 0x14) 
#define   STM32F2XX_RCC_AHB3RSTR             (STM32F2XX_RCC_BASE + 0x18)
#define   STM32F2XX_RCC_APB1RSTR             (STM32F2XX_RCC_BASE + 0x20)
#define   STM32F2XX_RCC_APB2RSTR             (STM32F2XX_RCC_BASE + 0x24)
#define   STM32F2XX_RCC_AHB1ENR              (STM32F2XX_RCC_BASE + 0x30)
#define   STM32F2XX_RCC_AHB2ENR              (STM32F2XX_RCC_BASE + 0x34)
#define   STM32F2XX_RCC_APB3ENR              (STM32F2XX_RCC_BASE + 0x38)
#define   STM32F2XX_RCC_APB1ENR              (STM32F2XX_RCC_BASE + 0x40)
#define   STM32F2XX_RCC_APB2ENR              (STM32F2XX_RCC_BASE + 0x44)
#define   STM32F2XX_RCC_AHB1LPENR            (STM32F2XX_RCC_BASE + 0x50)
#define   STM32F2XX_RCC_AHB2LPENR            (STM32F2XX_RCC_BASE + 0x54)  
#define   STM32F2XX_RCC_AHB3LPENR            (STM32F2XX_RCC_BASE + 0x58)
#define   STM32F2XX_RCC_APB1LPENR            (STM32F2XX_RCC_BASE + 0x60)
#define   STM32F2XX_RCC_APB2LPENR            (STM32F2XX_RCC_BASE + 0x64) 
#define   STM32F2XX_RCC_BDCR                 (STM32F2XX_RCC_BASE + 0x70)
#define   STM32F2XX_RCC_CSR                  (STM32F2XX_RCC_BASE + 0x74) 
#define   STM32F2XX_RCC_SSCGR                (STM32F2XX_RCC_BASE + 0x80)
#define   STM32F2XX_RCC_PLLI2SCFGR           (STM32F2XX_RCC_BASE + 0x84)

/* Bit field definitions */

#define STM32F2XX_RCC_AHB1ENR_GPIOAEN        (1<<0)
#define STM32F2XX_RCC_AHB1ENR_GPIOBEN        (1<<1)
#define STM32F2XX_RCC_AHB1ENR_GPIOCEN        (1<<2)
#define STM32F2XX_RCC_AHB1ENR_GPIOGEN        (1<<6)
#define STM32F2XX_RCC_AHB1ENR_GPIOHEN        (1<<7)
#define STM32F2XX_RCC_AHB1ENR_GPIOIEN        (1<<8)
#define STM32F2XX_RCC_AHB1ENR_ETHMACEN       (1<<25)
#define STM32F2XX_RCC_AHB1ENR_ETHMACTXEN     (1<<26)
#define STM32F2XX_RCC_AHB1ENR_ETHMACRXEN     (1<<27)

/* RCC APB1 periphial clock enable register */

#define STM32F2XX_RCC_APB1ENR_TIM2EN         (1<<0)
#define STM32F2XX_RCC_APB1ENR_TIM3EN         (1<<1)
#define STM32F2XX_RCC_APB1ENR_TIM4EN         (1<<2)
#define STM32F2XX_RCC_APB1ENR_TIM5EN         (1<<3)
#define STM32F2XX_RCC_APB1ENR_TIM6EN         (1<<4)
#define STM32F2XX_RCC_APB1ENR_TIM7EN         (1<<5)
#define STM32F2XX_RCC_APB1ENR_TIM12EN        (1<<6)
#define STM32F2XX_RCC_APB1ENR_TIM13EN        (1<<7)
#define STM32F2XX_RCC_APB1ENR_TIM14EN        (1<<8)
#define STM32F2XX_RCC_APB1ENR_WWDGEN         (1<<11)
#define STM32F2XX_RCC_APB1ENR_SPI2EN         (1<<14)
#define STM32F2XX_RCC_APB1ENR_SPI3EN         (1<<15)
#define STM32F2XX_RCC_APB1ENR_USART2EN       (1<<17)
#define STM32F2XX_RCC_APB1ENR_USART3EN       (1<<18)
#define STM32F2XX_RCC_APB1ENR_USART4EN       (1<<19)
#define STM32F2XX_RCC_APB1ENR_USART5EN       (1<<20)
#define STM32F2XX_RCC_APB1ENR_IC1EN          (1<<21)
#define STM32F2XX_RCC_APB1ENR_IC2EN          (1<<22)
#define STM32F2XX_RCC_APB1ENR_IC3EN          (1<<23)
#define STM32F2XX_RCC_APB1ENR_CAN1EN         (1<<25)
#define STM32F2XX_RCC_APB1ENR_CAN2EN         (1<<26)
#define STM32F2XX_RCC_APB1ENR_PWREN          (1<<28)
#define STM32F2XX_RCC_APB1ENR_DACEN          (1<<29)


#ifdef __cplusplus
}
#endif

#endif  /* __INCstm32f2xxRcch */
