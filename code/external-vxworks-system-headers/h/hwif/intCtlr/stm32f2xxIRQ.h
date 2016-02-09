/* stm32f2xxIRQ.h - STM32F20x/STM32F21x interrupt request header file */

/*
 * Copyright (c) 2012, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,25jul13,mpc  Changed priority of system tick timer
01a,02may12,rec  Created
*/

/*
DESCRIPTION
This file contains IRQ number and vector assigments specifc to the 
STM32F20x/STM32F21x interrupt controler.

SEE ALSO:
\tb RM0033 Reference manual STM32F205xx, STM32F207xx, STM32F215xx and STM32F217xx
advanced ARM-based 32-bit MCUs, DEC 2011

*/

#ifndef __INCstm32f2xxIRQh
#define __INCstm32f2xxIRQh

#ifdef __cplusplus
extern "C" {
#endif

/* REF: RM0033 Table-20 */

/* IRQ vector numbers */

#define SYSTICK_IRQ          -1 /* System tick timer */
#define WWDG_IRQ              0 /* Window Watchdog */
#define PVD_IRQ               1 /* PVD through EXTI line detection */
#define TAMP_STAMP_IRQ        2 /* Tamper & TimeStamp through the EXTI line */
#define RTC_WKUP_IRQ          3 /* RTC Wakeup interrupt through the EXTI line */
#define FLASH_IRQ             4 /* Flash global */
#define RCC_IRQ               5 /* RCC global */
#define EXTI0_IRQ             6 /* EXTI Line0 */
#define EXTI1_IRQ             7 /* EXTI Line1 */
#define EXTI2_IRQ             8 /* EXTI Line2 */
#define EXTI3_IRQ             9 /* EXTI Line3 */
#define EXTI4_IRQ            10 /* EXTI Line4 */
#define DMA1_Stream0_IRQ     11 /* DMA1 Stream0 global */
#define DMA1_Stream1_IRQ     12 /* DMA1 Stream1 global */
#define DMA1_Stream2_IRQ     13 /* DMA1 Stream2 global */
#define DMA1_Stream3_IRQ     14 /* DMA1 Stream3 global */
#define DMA1_Stream4_IRQ     15 /* DMA1 Stream4 global */
#define DMA1_Stream5_IRQ     16 /* DMA1 Stream5 global */
#define DMA1_Stream6_IRQ     17 /* DMA1 Stream6 global */
#define ADC_IRQ              18 /* ADC1 ADC2 and ADC3 globalinterrupts */
#define CAN1_TX_IRQ          19 /* CAN1 TX interrupts */
#define CAN1_RX0_IRQ         20 /* CAN1 RX0 interrupts */
#define CAN1_RX1_IRQ         21 /* CAN1 RX1 */
#define CAN1_SCE_IRQ         22 /* CAN1 SCE */
#define EXTI9_5_IRQ          23 /* EXTI Line[9:5] interrupts */
#define TIM1_BRK_TIM9_IRQ    24 /* TIM1 Break, TIM9 global */
#define TIM1_UP_TIM10_IRQ    25 /* TIM1 Update, TIM10 global */
#define TIM1_TRG_COM_TIM11_IRQ 26 /* TIM1 Trig & Commutation TIM11 global */
#define TIM1_CC_IRQ          27 /* TIM1 Capture Compare */
#define TIM2_IRQ             28 /* TIM2 global */
#define TIM3_IRQ             29 /* TIM3 global */
#define TIM4_IRQ             30 /* TIM4 global */
#define I2C1_EV_IRQ          31 /* I2C1 event */
#define I2C1_ER_IRQ          32 /* I2C1 error */
#define I2C2_EV_IRQ          33 /* I2C2 event */
#define I2C2_ER_IRQ          34 /* I2C2 error */
#define SPI1_IRQ             35 /* SPI1 global */
#define SPI2_IRQ             36 /* SPI2 global */
#define USART1_IRQ           37 /* USART1 global */
#define USART2_IRQ           38 /* USART2 global */
#define USART3_IRQ           39 /* USART3 global */
#define EXTI15_10_IRQ        40 /* EXTI Line[15:10] interrupts */
#define RTC_Alarm_IRQ        41 /* RTC Alarms (A and B) through EXTI line */
#define OTG_FS_WKUP_IRQ      42 /* USB On-The-Go FS Wakeup through EXTI line */
#define TIM8_BRK_TIM12_IRQ   43 /* TIM8 Break interrupt and TIM12 global */
#define TIM8_UP_TIM13_IRQ    44 /* TIM8 Update interrupt and TIM13 global */
#define TIM8_TRG_COM_TIM1_IRQ 45 /* TIM8 Trig & Commutation, TIM14 global */
#define TIM8_CC_TIM8_IRQ     46 /* Capture Compare */
#define DMA1_Stream7_IRQ     47 /* DMA1 Stream7 global */
#define FSMC_IRQ             48 /* FSMC global */
#define SDIO_IRQ             49 /* SDIO global */
#define TIM5_IRQ             50 /* TIM5 global */
#define SPI3_IRQ             51 /* SPI3 global */
#define UART4_IRQ            52 /* UART4 global */
#define UART5_IRQ            53 /* UART5 global */
#define TIM6_DAC_IRQ         54 /* TIM6 global DAC1, DAC2 underrun error */
#define TIM7_TIM7_IRQ        55 /* global */
#define DMA2_Stream0_IRQ     56 /* DMA2 Stream0 global */
#define DMA2_Stream1_IRQ     57 /* DMA2 Stream1 global */
#define DMA2_Stream2_IRQ     58 /* DMA2 Stream2 global */
#define DMA2_Stream3_IRQ     59 /* DMA2 Stream3 global */
#define DMA2_Stream4_IRQ     60 /* DMA2 Stream4 global */
#define ETH_IRQ              61 /* Ethernet global */
#define ETH_WKUP_IRQ         62 /* Ethernet Wakeup through EXTI line */
#define CAN2_TX_IRQ          63 /* CAN2 TX interrupts */
#define CAN2_RX0_IRQ         64 /* CAN2 RX0 interrupts */
#define CAN2_RX1_IRQ         65 /* CAN2 RX1 */
#define CAN2_SCE_IRQ         66 /* CAN2 SCE */
#define OTG_FS_IRQ           67 /* USB On The Go FS global */
#define DMA2_Stream5_IRQ     68 /* DMA2 Stream5 global */
#define DMA2_Stream6_IRQ     69 /* DMA2 Stream6 global */
#define DMA2_Stream7_IRQ     70 /* DMA2 Stream7 global */
#define USART6_IRQ           71 /* USART6 global */
#define I2C3_EV_IRQ          72 /* I2C3 event */
#define I2C3_ER_IRQ          73 /* I2C3 error */
#define OTG_HS_EP1_OUT_IRQ   74 /* USB On The Go HS End Point 1 Out global */
#define OTG_HS_EP1_IN_IRQ    75 /* USB On The Go HS End Point 1 In global */
#define OTG_HS_WKUP_IRQ      76 /* USB On The Go HS Wakeup through EXTI */
#define OTG_HS_USB_IRQ       77 /* On The Go HS global */
#define DCMI_IRQ             78 /* DCMI global */
#define CRYP_IRQ             79 /* crypto global */
#define HASH_RNG_IRQ         80 /* Hash and Rng global */

/* IRQ default priorities (changable) */

#define SYSTICK_IRQ_PRI      0xff /* System tick timer */
#define TIM2_IRQ_PRI         0x20 /* TIM2 global */
#define USART3_IRQ_PRI       0x30 /* USART3 global */
#define ETH_IRQ_PRI          0x40 /* Ethernet global */

#ifdef __cplusplus
}
#endif

#endif  /* __INCstm32f2xxIRQh */
