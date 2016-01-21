/* cavMioAddrs.h -  Cavium Support Routines */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,09dec11,x_f  Add defines for CN68XX
01a,07jul11,rlg  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcavMioAddrsh
#define __INCcavMioAddrsh

#ifdef __cplusplus
extern "C" {
#endif



#define CAV_MIO_BASE_ADDR                0x8001180000000000ULL
#define CAV_MIO_FUS_PLL                  0x8001180000001580ULL
#define CAV_MIO_FUS_DAT3                 0x8001180000001418ULL


#define CAV_MIO_BOOT_LOC_CFG0_OFF        0x80
#define CAV_MIO_BOOT_LOC_CFG_SP          0x8


#define CAV_MIO_BOOT_LOC_CFGX(x) \
     ((CAV_MIO_BASE_ADDR + CAV_MIO_BOOT_LOC_CFG0_OFF)	\
     + ((x & 1) * CAV_MIO_BOOT_LOC_CFG_SP))

#define CAV_MIO_BOOT_LOC_DAT_OFF         0x98
#define CAV_MIO_BOOT_LOC_DAT_ADR         (CAV_MIO_BASE_ADDR + CAV_MIO_BOOT_LOC_DAT_OFF)

#define CAV_MIO_BOOT_LOC_OFF             0x90
#define CAV_MIO_BOOT_LOC_ADR             (CAV_MIO_BASE_ADDR + CAV_MIO_BOOT_LOC_OFF)

#define CAV_MIO_BOOT_REG_CFGX(offset)   (CAV_MIO_BASE_ADDR + \
                                         (((offset) & 7) * 8))
#define CAV_MIO_BOOT_REG_TIMX(offset)   (CAV_MIO_BASE_ADDR + 0x40 + \
                                         (((offset) & 7) * 8))
#define CAV_MIO_TWSX_SW_OFF             0x1000
#define CAV_MIO_TWSX_SW_TWSI(offset)     \
    (CAV_MIO_BASE_ADDR + CAV_MIO_TWSX_SW_OFF + (((offset) & 1) * 512))

#define CAV_MIO_TWSX_SW_EXT_OFF         0x1018
#define CAV_MIO_TWSX_SW_TWSI_EXT(offset) \
    (CAV_MIO_BASE_ADDR + CAV_MIO_TWSX_SW_EXT_OFF + ((offset) & 1) * 512)

#define CAV_MIO_QLMX_CFG_OFF            0x1590
#define CAV_MIO_QLMX_CFG(index)          \
    (CAV_MIO_BASE_ADDR + CAV_MIO_QLMX_CFG_OFF + ((index) & 7) * 8)

/*
 *	the following defines were added since they are used in
 *	octeon entry - as part of the multicore load and startup
 *	process,  
 */
/* Addresses used to pass parameters to secondary cores at startup */
#define BOOT_REGION_STORE_START         0x80000600
#define BOOT_REGION_STORE_ENTRY         (BOOT_REGION_STORE_START+0x00)
#define BOOT_REGION_STORE_PARAMETER     (BOOT_REGION_STORE_START+0x08)
#define BOOT_REGION_STORE_SP            (BOOT_REGION_STORE_START+0x10)
#define BOOT_REGION_STORE_GP            (BOOT_REGION_STORE_START+0x18)
#define BOOT_REGION_WAIT_CHANNEL        BOOT_REGION_STORE_ENTRY

#ifdef __cplusplus
}
#endif
#endif /* __INCcavMioAddrsh */
