/* cavAsx.h - Reduced Gigabit Media interface data types, macros, and addresses */

/*
 * Copyright (c) 2010 River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,05oct10,d_c  Change ull to ULL to be Diab compatible
01a,06aug10,d_c  written
*/

#ifndef __INCcavAsxh
#define __INCcavAsxh

/* includes */

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/*
 * Base address and offsets for Reduced Gigabit Media interface. These
 * constants are used in the address computation macros
 * below. Generally, the offset to the first register of a particular
 * type is defined here. The address computation macros then use
 * arithmetic to compute the Nth instance of a register.
 */

#define CAV_ASX0_BASE_ADDR            0x80011800B0000000ULL
#define CAV_ASX0_RX_PRT_EN_OFF        0x00
#define CAV_ASX0_TX_PRT_EN_OFF        0x08
#define CAV_ASX0_RX_CLK_SET0_OFF      0x20
#define CAV_ASX0_TX_CLK_SET0_OFF      0x48
#define CAV_ASX0_TX_HI_WATER0_OFF     0x80

/* Address computation macros.*/

#define CAV_ASXX_RX_PRT_EN(interface) \
    (CAV_ASX0_BASE_ADDR + CAV_ASX0_RX_PRT_EN_OFF \
     + (interface & 1) * 0x8000000ULL)

#define CAV_ASXX_TX_PRT_EN(interface) \
    (CAV_ASX0_BASE_ADDR + CAV_ASX0_TX_PRT_EN_OFF \
     + (interface & 1) * 0x8000000ULL)

#define CAV_ASXX_RX_CLK_SETX(offset, interface) \
    (CAV_ASX0_BASE_ADDR + CAV_ASX0_RX_CLK_SET0_OFF \
     + ((offset & 3) + ((interface & 1) * 0x1000000ULL)) * 8)

#define CAV_ASXX_TX_CLK_SETX(offset, interface) \
    (CAV_ASX0_BASE_ADDR + CAV_ASX0_TX_CLK_SET0_OFF \
     + ((offset & 3) + ((interface & 1) * 0x1000000ULL)) * 8)

#define CAV_ASXX_TX_HI_WATERX(offset, interface) \
    (CAV_ASX0_BASE_ADDR + CAV_ASX0_TX_HI_WATER0_OFF \
     + ((offset & 3) + ((interface & 1) * 0x1000000ULL)) * 8)

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavAsxh */
