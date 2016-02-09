/* vxbCortexMIntCtlr.h - interrupt controller for ARM Cortex-M CPU Cores */

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
01d,19aug13,mpc  code clean
01c,02jul12,m_h  Fix macro offsets: multiply by sizeof(UINT32), not 8
01b,22may12,j_b  move system registers to architecture header, arm-m.h
01a,06apr12,m_h  created
*/

/*
 * This file implements macro definitions used by the ARM Cortex-M NVIC
 * interrupt controller driver.
 */

#ifndef	__INCvxbCortexMIntCtlrh
#define	__INCvxbCortexMIntCtlrh

#include "arch/arm/arm-m/arm-m.h"	/* system register definitions */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/********* Default values *********/

#define CORTEXM_INTCTLR_MAX_PRIORITY 0xFF

/*
 * Note. Although Cortex-M3 and Cortex-M4 support a maximum of 256 pins (which
 * includes the 16 exception vectors at the beginning of the table), ARMv7M
 * supports a maximum of 512.
 */

#define CORTEXM_INTCTLR_MAX_PINS 512

/********* Register Bit Values *********/

/* ICTR Bit Values */

/*
 * CORTEXM_INTCTLR_GET_NUM_VECTORS queries the ICTR register and adjusts the
 * result to represent the total number of exception- and interrupt-vectors
 * supported by the hardware implementation.  The first 16 of these vectors
 * are reserved for exceptions, the rest are the external interrupts.
 *
 * ICTR.INTLINESNUM returns the maximum number of external interrupts
 * supported. We add 16 to account for the additional 16 exception vectors.
 *
 * If ICTR.INTLINESNUM contains 0xF, this actually indicates that there are
 * 496 interrupt lines, not 512.  So, for this case, the value of
 * CORTEXM_INTCTLR_GET_NUM_VECTORS is adjusted accordingly.
 */

#define CORTEXM_INTCTLR_GET_NUM_VECTORS                  \
    ((CORTEXM_INT_READ_4(CORTEXM_ICTR)&0xF) == 0xF)      \
        ? 512                                            \
        : (((CORTEXM_INT_READ_4(CORTEXM_ICTR)&0xF) + 1) * 32) + 16

/************ Register Address Mappings *****************/

/* Interrupt Set-Enable Registers */

/* write a "1" to the appropriate bit to enable the interrupt */

#define CORTEXM_NVIC_ISER0  (0xE000E100)  /* IRQ   0-31  enable */
#define CORTEXM_NVIC_ISER1  (0xE000E104)  /* IRQ  32-63  enable */
#define CORTEXM_NVIC_ISER2  (0xE000E108)  /* IRQ  64-95  enable */
#define CORTEXM_NVIC_ISER3  (0xE000E10C)  /* IRQ  96-127 enable */
#define CORTEXM_NVIC_ISER4  (0xE000E110)  /* IRQ 128-159 enable */
#define CORTEXM_NVIC_ISER5  (0xE000E114)  /* IRQ 160-191 enable */
#define CORTEXM_NVIC_ISER6  (0xE000E118)  /* IRQ 192-223 enable */
#define CORTEXM_NVIC_ISER7  (0xE000E11C)  /* IRQ 224-255 enable */
#define CORTEXM_NVIC_ISER8  (0xE000E120)  /* IRQ 256-287 enable */
#define CORTEXM_NVIC_ISER9  (0xE000E124)  /* IRQ 288-319 enable */
#define CORTEXM_NVIC_ISER10 (0xE000E128)  /* IRQ 320-351 enable */
#define CORTEXM_NVIC_ISER11 (0xE000E12C)  /* IRQ 352-383 enable */
#define CORTEXM_NVIC_ISER12 (0xE000E130)  /* IRQ 384-415 enable */
#define CORTEXM_NVIC_ISER13 (0xE000E134)  /* IRQ 416-447 enable */
#define CORTEXM_NVIC_ISER14 (0xE000E138)  /* IRQ 448-479 enable */
#define CORTEXM_NVIC_ISER15 (0xE000E13C)  /* IRQ 480-495 enable */

#define CORTEXM_NVIC_ISER(n) (CORTEXM_NVIC_ISER0 + (sizeof(UINT32) * (n)))

/* Interrupt Clear-Enable Registers */

/* write a "1" to the appropriate bit to disable the interrupt */

#define CORTEXM_NVIC_ICER0  (0xE000E180)  /* IRQ   0-31  clear-enable */
#define CORTEXM_NVIC_ICER1  (0xE000E184)  /* IRQ  32-63  clear-enable */
#define CORTEXM_NVIC_ICER2  (0xE000E188)  /* IRQ  64-95  clear-enable */
#define CORTEXM_NVIC_ICER3  (0xE000E18C)  /* IRQ  96-127 clear-enable */
#define CORTEXM_NVIC_ICER4  (0xE000E190)  /* IRQ 128-159 clear-enable */
#define CORTEXM_NVIC_ICER5  (0xE000E194)  /* IRQ 160-191 clear-enable */
#define CORTEXM_NVIC_ICER6  (0xE000E198)  /* IRQ 192-223 clear-enable */
#define CORTEXM_NVIC_ICER7  (0xE000E19C)  /* IRQ 224-255 clear-enable */
#define CORTEXM_NVIC_ICER8  (0xE000E1A0)  /* IRQ 256-287 clear-enable */
#define CORTEXM_NVIC_ICER9  (0xE000E1A4)  /* IRQ 288-319 clear-enable */
#define CORTEXM_NVIC_ICER10 (0xE000E1A8)  /* IRQ 320-351 clear-enable */
#define CORTEXM_NVIC_ICER11 (0xE000E1AC)  /* IRQ 352-383 clear-enable */
#define CORTEXM_NVIC_ICER12 (0xE000E1B0)  /* IRQ 384-415 clear-enable */
#define CORTEXM_NVIC_ICER13 (0xE000E1B4)  /* IRQ 416-447 clear-enable */
#define CORTEXM_NVIC_ICER14 (0xE000E1B8)  /* IRQ 448-479 clear-enable */
#define CORTEXM_NVIC_ICER15 (0xE000E1BC)  /* IRQ 480-495 clear-enable */

#define CORTEXM_NVIC_ICER(n) (CORTEXM_NVIC_ICER0 + (sizeof(UINT32) * (n)))

/* Interrupt Set-Pending Registers */

/* write a "1" to the appropriate bit to force an interrupt to pend */

#define CORTEXM_NVIC_ISPR0  (0xE000E200)  /* IRQ   0-31  set-pending */
#define CORTEXM_NVIC_ISPR1  (0xE000E204)  /* IRQ  32-63  set-pending */
#define CORTEXM_NVIC_ISPR2  (0xE000E208)  /* IRQ  64-95  set-pending */
#define CORTEXM_NVIC_ISPR3  (0xE000E20C)  /* IRQ  96-127 set-pending */
#define CORTEXM_NVIC_ISPR4  (0xE000E210)  /* IRQ 128-159 set-pending */
#define CORTEXM_NVIC_ISPR5  (0xE000E214)  /* IRQ 160-191 set-pending */
#define CORTEXM_NVIC_ISPR6  (0xE000E218)  /* IRQ 192-223 set-pending */
#define CORTEXM_NVIC_ISPR7  (0xE000E21C)  /* IRQ 224-255 set-pending */
#define CORTEXM_NVIC_ISPR8  (0xE000E220)  /* IRQ 256-287 set-pending */
#define CORTEXM_NVIC_ISPR9  (0xE000E224)  /* IRQ 288-319 set-pending */
#define CORTEXM_NVIC_ISPR10 (0xE000E228)  /* IRQ 320-351 set-pending */
#define CORTEXM_NVIC_ISPR11 (0xE000E22C)  /* IRQ 352-383 set-pending */
#define CORTEXM_NVIC_ISPR12 (0xE000E230)  /* IRQ 384-415 set-pending */
#define CORTEXM_NVIC_ISPR13 (0xE000E234)  /* IRQ 416-447 set-pending */
#define CORTEXM_NVIC_ISPR14 (0xE000E238)  /* IRQ 448-479 set-pending */
#define CORTEXM_NVIC_ISPR15 (0xE000E23C)  /* IRQ 480-495 set-pending */

#define CORTEXM_NVIC_ISPR(n) (CORTEXM_NVIC_ISPR0 + (sizeof(UINT32) * (n)))

/* Interrupt Clear-Pending Registers */

/* write a "1" to the appropriate bit to un-pend a pended interrupt */

#define CORTEXM_NVIC_ICPR0  (0xE000E280)  /* IRQ   0-31  clear-pending */
#define CORTEXM_NVIC_ICPR1  (0xE000E284)  /* IRQ  32-63  clear-pending */
#define CORTEXM_NVIC_ICPR2  (0xE000E288)  /* IRQ  64-95  clear-pending */
#define CORTEXM_NVIC_ICPR3  (0xE000E28C)  /* IRQ  96-127 clear-pending */
#define CORTEXM_NVIC_ICPR4  (0xE000E290)  /* IRQ 128-159 clear-pending */
#define CORTEXM_NVIC_ICPR5  (0xE000E294)  /* IRQ 160-191 clear-pending */
#define CORTEXM_NVIC_ICPR6  (0xE000E298)  /* IRQ 192-223 clear-pending */
#define CORTEXM_NVIC_ICPR7  (0xE000E29C)  /* IRQ 224-255 clear-pending */
#define CORTEXM_NVIC_ICPR8  (0xE000E2A0)  /* IRQ 256-287 clear-pending */
#define CORTEXM_NVIC_ICPR9  (0xE000E2A4)  /* IRQ 288-319 clear-pending */
#define CORTEXM_NVIC_ICPR10 (0xE000E2A8)  /* IRQ 320-351 clear-pending */
#define CORTEXM_NVIC_ICPR11 (0xE000E2AC)  /* IRQ 352-383 clear-pending */
#define CORTEXM_NVIC_ICPR12 (0xE000E2B0)  /* IRQ 384-415 clear-pending */
#define CORTEXM_NVIC_ICPR13 (0xE000E2B4)  /* IRQ 416-447 clear-pending */
#define CORTEXM_NVIC_ICPR14 (0xE000E2B8)  /* IRQ 448-479 clear-pending */
#define CORTEXM_NVIC_ICPR15 (0xE000E2BC)  /* IRQ 480-495 clear-pending */

#define CORTEXM_NVIC_ICPR(n) (CORTEXM_NVIC_ICPR0 + (sizeof(UINT32) * (n)))


/* Interrupt Active Bit Register */

/*
 * Combine with ISPR to read status of an interrupt:
 *   Inactive, Active, Pending, or Active and Pending
 */

#define CORTEXM_NVIC_IABR0  (0xE000E300)  /* IRQ   0-31  active */
#define CORTEXM_NVIC_IABR1  (0xE000E304)  /* IRQ  32-63  active */
#define CORTEXM_NVIC_IABR2  (0xE000E308)  /* IRQ  64-95  active */
#define CORTEXM_NVIC_IABR3  (0xE000E30C)  /* IRQ  96-127 active */
#define CORTEXM_NVIC_IABR4  (0xE000E310)  /* IRQ 128-159 active */
#define CORTEXM_NVIC_IABR5  (0xE000E314)  /* IRQ 160-191 active */
#define CORTEXM_NVIC_IABR6  (0xE000E318)  /* IRQ 192-223 active */
#define CORTEXM_NVIC_IABR7  (0xE000E31C)  /* IRQ 224-255 active */
#define CORTEXM_NVIC_IABR8  (0xE000E320)  /* IRQ 256-287 active */
#define CORTEXM_NVIC_IABR9  (0xE000E324)  /* IRQ 288-319 active */
#define CORTEXM_NVIC_IABR10 (0xE000E328)  /* IRQ 320-351 active */
#define CORTEXM_NVIC_IABR11 (0xE000E32C)  /* IRQ 352-383 active */
#define CORTEXM_NVIC_IABR12 (0xE000E330)  /* IRQ 384-415 active */
#define CORTEXM_NVIC_IABR13 (0xE000E334)  /* IRQ 416-447 active */
#define CORTEXM_NVIC_IABR14 (0xE000E338)  /* IRQ 448-479 active */
#define CORTEXM_NVIC_IABR15 (0xE000E33C)  /* IRQ 480-495 active */

#define CORTEXM_NVIC_IABR(n) (CORTEXM_NVIC_IABR0 + (sizeof(UINT32) * (n)))

/* Interrupt Priority Register */

#define CORTEXM_NVIC_IPR0   (0xE000E400)  /* IRQ   0-3   priority */
#define CORTEXM_NVIC_IPR1   (0xE000E404)  /* IRQ   4-7   priority */
#define CORTEXM_NVIC_IPR2   (0xE000E408)  /* IRQ   8-11  priority */
#define CORTEXM_NVIC_IPR3   (0xE000E40C)  /* IRQ  12-15  priority */
#define CORTEXM_NVIC_IPR4   (0xE000E410)  /* IRQ  16-19  priority */
#define CORTEXM_NVIC_IPR5   (0xE000E414)  /* IRQ  20-23  priority */
#define CORTEXM_NVIC_IPR6   (0xE000E418)  /* IRQ  24-27  priority */
#define CORTEXM_NVIC_IPR7   (0xE000E41C)  /* IRQ  28-31  priority */
#define CORTEXM_NVIC_IPR8   (0xE000E420)  /* IRQ  32-35  priority */
#define CORTEXM_NVIC_IPR9   (0xE000E424)  /* IRQ  36-39  priority */
#define CORTEXM_NVIC_IPR10  (0xE000E428)  /* IRQ  40-43  priority */
#define CORTEXM_NVIC_IPR11  (0xE000E42C)  /* IRQ  44-47  priority */
#define CORTEXM_NVIC_IPR12  (0xE000E430)  /* IRQ  48-51  priority */
#define CORTEXM_NVIC_IPR13  (0xE000E434)  /* IRQ  52-55  priority */
#define CORTEXM_NVIC_IPR14  (0xE000E438)  /* IRQ  56-59  priority */
#define CORTEXM_NVIC_IPR15  (0xE000E43C)  /* IRQ  60-63  priority */
#define CORTEXM_NVIC_IPR16  (0xE000E440)  /* IRQ  64-67  priority */
#define CORTEXM_NVIC_IPR17  (0xE000E444)  /* IRQ  68-71  priority */
#define CORTEXM_NVIC_IPR18  (0xE000E448)  /* IRQ  72-75  priority */
#define CORTEXM_NVIC_IPR19  (0xE000E44C)  /* IRQ  76-79  priority */
#define CORTEXM_NVIC_IPR20  (0xE000E450)  /* IRQ  80-83  priority */
#define CORTEXM_NVIC_IPR21  (0xE000E454)  /* IRQ  84-87  priority */
#define CORTEXM_NVIC_IPR22  (0xE000E458)  /* IRQ  88-91  priority */
#define CORTEXM_NVIC_IPR23  (0xE000E45C)  /* IRQ  92-95  priority */
#define CORTEXM_NVIC_IPR24  (0xE000E460)  /* IRQ  96-99  priority */
#define CORTEXM_NVIC_IPR25  (0xE000E464)  /* IRQ 100-103 priority */
#define CORTEXM_NVIC_IPR26  (0xE000E468)  /* IRQ 104-107 priority */
#define CORTEXM_NVIC_IPR27  (0xE000E46C)  /* IRQ 108-111 priority */
#define CORTEXM_NVIC_IPR28  (0xE000E470)  /* IRQ 112-115 priority */
#define CORTEXM_NVIC_IPR29  (0xE000E474)  /* IRQ 116-119 priority */
#define CORTEXM_NVIC_IPR30  (0xE000E478)  /* IRQ 120-123 priority */
#define CORTEXM_NVIC_IPR31  (0xE000E47C)  /* IRQ 124-127 priority */
#define CORTEXM_NVIC_IPR32  (0xE000E480)  /* IRQ 128-131 priority */
#define CORTEXM_NVIC_IPR33  (0xE000E484)  /* IRQ 132-135 priority */
#define CORTEXM_NVIC_IPR34  (0xE000E488)  /* IRQ 136-139 priority */
#define CORTEXM_NVIC_IPR35  (0xE000E48C)  /* IRQ 140-143 priority */
#define CORTEXM_NVIC_IPR36  (0xE000E490)  /* IRQ 144-147 priority */
#define CORTEXM_NVIC_IPR37  (0xE000E494)  /* IRQ 148-151 priority */
#define CORTEXM_NVIC_IPR38  (0xE000E498)  /* IRQ 152-155 priority */
#define CORTEXM_NVIC_IPR39  (0xE000E49C)  /* IRQ 156-159 priority */
#define CORTEXM_NVIC_IPR40  (0xE000E4A0)  /* IRQ 160-163 priority */
#define CORTEXM_NVIC_IPR41  (0xE000E4A4)  /* IRQ 164-167 priority */
#define CORTEXM_NVIC_IPR42  (0xE000E4A8)  /* IRQ 168-171 priority */
#define CORTEXM_NVIC_IPR43  (0xE000E4AC)  /* IRQ 172-175 priority */
#define CORTEXM_NVIC_IPR44  (0xE000E4B0)  /* IRQ 176-179 priority */
#define CORTEXM_NVIC_IPR45  (0xE000E4B4)  /* IRQ 180-183 priority */
#define CORTEXM_NVIC_IPR46  (0xE000E4B8)  /* IRQ 184-187 priority */
#define CORTEXM_NVIC_IPR47  (0xE000E4BC)  /* IRQ 188-191 priority */
#define CORTEXM_NVIC_IPR48  (0xE000E4C0)  /* IRQ 192-195 priority */
#define CORTEXM_NVIC_IPR49  (0xE000E4C4)  /* IRQ 196-199 priority */
#define CORTEXM_NVIC_IPR50  (0xE000E4C8)  /* IRQ 200-203 priority */
#define CORTEXM_NVIC_IPR51  (0xE000E4CC)  /* IRQ 204-207 priority */
#define CORTEXM_NVIC_IPR52  (0xE000E4D0)  /* IRQ 208-211 priority */
#define CORTEXM_NVIC_IPR53  (0xE000E4D4)  /* IRQ 212-215 priority */
#define CORTEXM_NVIC_IPR54  (0xE000E4D8)  /* IRQ 216-219 priority */
#define CORTEXM_NVIC_IPR55  (0xE000E4DC)  /* IRQ 220-223 priority */
#define CORTEXM_NVIC_IPR56  (0xE000E4E0)  /* IRQ 224-227 priority */
#define CORTEXM_NVIC_IPR57  (0xE000E4E4)  /* IRQ 228-231 priority */
#define CORTEXM_NVIC_IPR58  (0xE000E4E8)  /* IRQ 232-235 priority */
#define CORTEXM_NVIC_IPR59  (0xE000E4EC)  /* IRQ 236-239 priority */
#define CORTEXM_NVIC_IPR60  (0xE000E4F0)  /* IRQ 240-243 priority */
#define CORTEXM_NVIC_IPR61  (0xE000E4F4)  /* IRQ 244-247 priority */
#define CORTEXM_NVIC_IPR62  (0xE000E4F8)  /* IRQ 248-251 priority */
#define CORTEXM_NVIC_IPR63  (0xE000E4FC)  /* IRQ 252-255 priority */
#define CORTEXM_NVIC_IPR64  (0xE000E500)  /* IRQ 256-259 priority */
#define CORTEXM_NVIC_IPR65  (0xE000E504)  /* IRQ 260-263 priority */
#define CORTEXM_NVIC_IPR66  (0xE000E508)  /* IRQ 264-267 priority */
#define CORTEXM_NVIC_IPR67  (0xE000E50C)  /* IRQ 268-271 priority */
#define CORTEXM_NVIC_IPR68  (0xE000E510)  /* IRQ 272-275 priority */
#define CORTEXM_NVIC_IPR69  (0xE000E514)  /* IRQ 276-279 priority */
#define CORTEXM_NVIC_IPR70  (0xE000E518)  /* IRQ 280-283 priority */
#define CORTEXM_NVIC_IPR71  (0xE000E51C)  /* IRQ 284-287 priority */
#define CORTEXM_NVIC_IPR72  (0xE000E520)  /* IRQ 288-291 priority */
#define CORTEXM_NVIC_IPR73  (0xE000E524)  /* IRQ 292-295 priority */
#define CORTEXM_NVIC_IPR74  (0xE000E528)  /* IRQ 296-299 priority */
#define CORTEXM_NVIC_IPR75  (0xE000E52C)  /* IRQ 300-303 priority */
#define CORTEXM_NVIC_IPR76  (0xE000E530)  /* IRQ 304-307 priority */
#define CORTEXM_NVIC_IPR77  (0xE000E534)  /* IRQ 308-311 priority */
#define CORTEXM_NVIC_IPR78  (0xE000E538)  /* IRQ 312-315 priority */
#define CORTEXM_NVIC_IPR79  (0xE000E53C)  /* IRQ 316-319 priority */
#define CORTEXM_NVIC_IPR80  (0xE000E540)  /* IRQ 320-323 priority */
#define CORTEXM_NVIC_IPR81  (0xE000E544)  /* IRQ 324-327 priority */
#define CORTEXM_NVIC_IPR82  (0xE000E548)  /* IRQ 328-331 priority */
#define CORTEXM_NVIC_IPR83  (0xE000E54C)  /* IRQ 332-335 priority */
#define CORTEXM_NVIC_IPR84  (0xE000E550)  /* IRQ 336-339 priority */
#define CORTEXM_NVIC_IPR85  (0xE000E554)  /* IRQ 340-343 priority */
#define CORTEXM_NVIC_IPR86  (0xE000E558)  /* IRQ 344-347 priority */
#define CORTEXM_NVIC_IPR87  (0xE000E55C)  /* IRQ 348-351 priority */
#define CORTEXM_NVIC_IPR88  (0xE000E560)  /* IRQ 352-355 priority */
#define CORTEXM_NVIC_IPR89  (0xE000E564)  /* IRQ 356-359 priority */
#define CORTEXM_NVIC_IPR90  (0xE000E568)  /* IRQ 360-363 priority */
#define CORTEXM_NVIC_IPR91  (0xE000E56C)  /* IRQ 364-367 priority */
#define CORTEXM_NVIC_IPR92  (0xE000E570)  /* IRQ 368-371 priority */
#define CORTEXM_NVIC_IPR93  (0xE000E574)  /* IRQ 372-375 priority */
#define CORTEXM_NVIC_IPR94  (0xE000E578)  /* IRQ 376-379 priority */
#define CORTEXM_NVIC_IPR95  (0xE000E57C)  /* IRQ 380-383 priority */
#define CORTEXM_NVIC_IPR96  (0xE000E580)  /* IRQ 384-387 priority */
#define CORTEXM_NVIC_IPR97  (0xE000E584)  /* IRQ 388-391 priority */
#define CORTEXM_NVIC_IPR98  (0xE000E588)  /* IRQ 392-395 priority */
#define CORTEXM_NVIC_IPR99  (0xE000E58C)  /* IRQ 396-399 priority */
#define CORTEXM_NVIC_IPR100 (0xE000E590)  /* IRQ 400-403 priority */
#define CORTEXM_NVIC_IPR101 (0xE000E594)  /* IRQ 404-407 priority */
#define CORTEXM_NVIC_IPR102 (0xE000E598)  /* IRQ 408-411 priority */
#define CORTEXM_NVIC_IPR103 (0xE000E59C)  /* IRQ 412-415 priority */
#define CORTEXM_NVIC_IPR104 (0xE000E5A0)  /* IRQ 416-419 priority */
#define CORTEXM_NVIC_IPR105 (0xE000E5A4)  /* IRQ 420-423 priority */
#define CORTEXM_NVIC_IPR106 (0xE000E5A8)  /* IRQ 424-427 priority */
#define CORTEXM_NVIC_IPR107 (0xE000E5AC)  /* IRQ 428-431 priority */
#define CORTEXM_NVIC_IPR108 (0xE000E5B0)  /* IRQ 432-435 priority */
#define CORTEXM_NVIC_IPR109 (0xE000E5B4)  /* IRQ 436-439 priority */
#define CORTEXM_NVIC_IPR110 (0xE000E5B8)  /* IRQ 440-443 priority */
#define CORTEXM_NVIC_IPR111 (0xE000E5BC)  /* IRQ 444-447 priority */
#define CORTEXM_NVIC_IPR112 (0xE000E5C0)  /* IRQ 448-451 priority */
#define CORTEXM_NVIC_IPR113 (0xE000E5C4)  /* IRQ 452-455 priority */
#define CORTEXM_NVIC_IPR114 (0xE000E5C8)  /* IRQ 456-459 priority */
#define CORTEXM_NVIC_IPR115 (0xE000E5CC)  /* IRQ 460-463 priority */
#define CORTEXM_NVIC_IPR116 (0xE000E5D0)  /* IRQ 464-467 priority */
#define CORTEXM_NVIC_IPR117 (0xE000E5D4)  /* IRQ 468-471 priority */
#define CORTEXM_NVIC_IPR118 (0xE000E5D8)  /* IRQ 472-475 priority */
#define CORTEXM_NVIC_IPR119 (0xE000E5DC)  /* IRQ 476-479 priority */
#define CORTEXM_NVIC_IPR120 (0xE000E5E0)  /* IRQ 480-483 priority */
#define CORTEXM_NVIC_IPR121 (0xE000E5E4)  /* IRQ 484-487 priority */
#define CORTEXM_NVIC_IPR122 (0xE000E5E8)  /* IRQ 488-491 priority */
#define CORTEXM_NVIC_IPR123 (0xE000E5EC)  /* IRQ 492-495 priority */

#define CORTEXM_NVIC_IPR(n)      (CORTEXM_NVIC_IPR0 + (sizeof(UINT32) * (n)))
#define CORTEXM_NVIC_IPR_BYTE(n) (CORTEXM_NVIC_IPR0 + (n))

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxbCortexMIntCtlrh */

