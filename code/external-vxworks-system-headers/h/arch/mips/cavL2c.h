/* cavL2c.h - SDK-derived L2 cache data types, macros and addresses */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,09dec11,x_f  add defines for OcteonII CN68xx
01d,06jul11,rlg  data structures pulled. now use SDK.  addresses are still
                 defined here. Note this file was moved into h/arch/mips
                 previously resided in src/vendor/octeon
01c,14jun11,d_c  Merge SDK 2.1.0 Build 395
01b,04nov10,d_c  add address defines
01a,21sep10,rlg  written
*/


#ifndef __INCocteonL2ch
#define __INCocteonL2ch

#ifdef  __cplusplus
extern "C" {
#endif

/* defines */

#define CAV_L2C_CTL	                0x8001180080800000ULL
#define CAV_L2C_WPAR_IOBX(blkId)    0x8001180080840200ULL
#define CAV_L2C_WPAR_PPX(offset)    (0x8001180080840000ULL + ((offset) & 7) * 8)
#define CAV_L2C_TADX_INT(blkId)  \
    (0x8001180080A00028ULL + ((blkId) & 3) * 0x40000ULL)

#ifdef  __cplusplus
}
#endif

#endif /* __INCocteonL2ch */
