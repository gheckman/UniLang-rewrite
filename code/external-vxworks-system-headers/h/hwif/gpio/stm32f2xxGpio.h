/* stm32f2xxGpio.h - STM32F20x/STM32F21x General Purpose IO header file */

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
01b,24may12,jmz  added bit field definitions for MODER, OSPEEDR, PUPDR,
                 OTYPER, and AFR registers
01a,02may12,rec  Created - Content extracted from stm32f2xx.h v01a
*/

/*
DESCRIPTION
This file contains register definitions specifc to the STM32F20x/STM32F21x 
General Purpose Input/Output registers.

SEE ALSO:
\tb RM0033 Reference manual STM32F205xx, STM32F207xx, STM32F215xx and STM32F217xx
advanced ARM-based 32-bit MCUs, DEC 2011

*/

#ifndef __INCstm32f2xxGpioh
#define __INCstm32f2xxGpioh

#ifdef __cplusplus
extern "C" {
#endif


/* Base register definitions */

#define STM32F2XX_GPIOx_MODER(n)     (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x0)
#define STM32F2XX_GPIOx_OTYPER(n)    (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x4)
#define STM32F2XX_GPIOx_OSPEEDR(n)   (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x8)
#define STM32F2XX_GPIOx_PUPDR(n)     (STM32F2XX_GPIO_BASE + (n * 0x400) + 0xC)
#define STM32F2XX_GPIOx_IDR(n)       (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x10)
#define STM32F2XX_GPIOx_ODR(n)       (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x14)
#define STM32F2XX_GPIOx_LCKR(n)      (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x1C)
#define STM32F2XX_GPIOx_AFRL(n)      (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x20)
#define STM32F2XX_GPIOx_AFRH(n)      (STM32F2XX_GPIO_BASE + (n * 0x400) + 0x24)

/* Bit field definitions */

#define STM32F2XX_GPIO_MODER_INPUT    (0x0)
#define STM32F2XX_GPIO_MODER_OUTPUT   (0x1)
#define STM32F2XX_GPIO_MODER_ALT_FUNC (0x2)
#define STM32F2XX_GPIO_MODER_ANALOG   (0x3)

#define STM32F2XX_GPIO_OSPEEDR_2MHZ   (0x0)
#define STM32F2XX_GPIO_OSPEEDR_25MHZ  (0x1)
#define STM32F2XX_GPIO_OSPEEDR_50MHZ  (0x2)
#define STM32F2XX_GPIO_OSPEEDR_100MHZ (0x3)

#define STM32F2XX_GPIO_PUPDR_NONE     (0x0)
#define STM32F2XX_GPIO_PUPDR_UP       (0x1)
#define STM32F2XX_GPIO_PUPDR_DOWN     (0x2)

#define STM32F2XX_GPIO_AFR_AF0        (0x0)
#define STM32F2XX_GPIO_AFR_AF1        (0x1)
#define STM32F2XX_GPIO_AFR_AF2        (0x2)
#define STM32F2XX_GPIO_AFR_AF3        (0x3)
#define STM32F2XX_GPIO_AFR_AF4        (0x4)
#define STM32F2XX_GPIO_AFR_AF5        (0x5)
#define STM32F2XX_GPIO_AFR_AF6        (0x6)
#define STM32F2XX_GPIO_AFR_AF7        (0x7)
#define STM32F2XX_GPIO_AFR_AF8        (0x8)
#define STM32F2XX_GPIO_AFR_AF9        (0x9)
#define STM32F2XX_GPIO_AFR_AF10       (0xA)
#define STM32F2XX_GPIO_AFR_AF11       (0xB)
#define STM32F2XX_GPIO_AFR_AF12       (0xC)
#define STM32F2XX_GPIO_AFR_AF13       (0xD)
#define STM32F2XX_GPIO_AFR_AF14       (0xE)
#define STM32F2XX_GPIO_AFR_AF15       (0xF)

#define STM32F2XX_GPIO_OTYPER_PUSHPULL  (0x0)
#define STM32F2XX_GPIO_OTYPER_OPENDRAIN (0x1) 

#define STM32F2XX_GPIO_MODULE_A      0
#define STM32F2XX_GPIO_MODULE_B      1
#define STM32F2XX_GPIO_MODULE_C      2
#define STM32F2XX_GPIO_MODULE_D      3
#define STM32F2XX_GPIO_MODULE_E      4
#define STM32F2XX_GPIO_MODULE_F      5
#define STM32F2XX_GPIO_MODULE_G      6
#define STM32F2XX_GPIO_MODULE_H      7
#define STM32F2XX_GPIO_MODULE_I      8

#define STM32F2XX_GPIO_PIN_0         0
#define STM32F2XX_GPIO_PIN_1         1
#define STM32F2XX_GPIO_PIN_2         2
#define STM32F2XX_GPIO_PIN_3         3
#define STM32F2XX_GPIO_PIN_4         4
#define STM32F2XX_GPIO_PIN_5         5
#define STM32F2XX_GPIO_PIN_6         6
#define STM32F2XX_GPIO_PIN_7         7
#define STM32F2XX_GPIO_PIN_8         8
#define STM32F2XX_GPIO_PIN_9         9
#define STM32F2XX_GPIO_PIN_10        10
#define STM32F2XX_GPIO_PIN_11        11
#define STM32F2XX_GPIO_PIN_12        12
#define STM32F2XX_GPIO_PIN_13        13
#define STM32F2XX_GPIO_PIN_14        14
#define STM32F2XX_GPIO_PIN_15        15

#ifdef __cplusplus
}
#endif

#endif  /* __INCstm32f2xxGpioh */
