/* cavMio.h -  Cavium Support Routines */
/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01h,09dec11,x_f  add defines for OcteonII CN68xx
01g,20jul11,rlg  cleanup of octeon h files in src/vendor/octeon move some
                 defines to this file
01f,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01e,20oct10,d_c  Include SDK data types directly from SDK
01d,05oct10,d_c  Change ull to ULL to be Diab compatible
01c,28sep10,d_c  Make cav header names consistent
01b,19aug10,d_c  Revert back original SDK names for copied data types
01a,04aug10,rlg  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcavMioh
#define __INCcavMioh

#ifdef __cplusplus
extern "C" {
#endif


#include <arch/mips/cavMioAddrs.h>

#ifndef _ASMLANGUAGE
#include <arch/mips/private/cavSdkDrvInclude.h>
#include CAV_SDK_DRV_INCLUDE(cvmx-csr-enums.h)
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-mio-defs.h)

typedef cvmx_mio_boot_loc_adr_t CAV_MIO_BOOT_LOC_ADR_T;
typedef cvmx_mio_boot_loc_cfgx_t CAV_MIO_BOOT_LOC_CFGX_T;
typedef cvmx_mio_boot_loc_dat_t CAV_MIO_BOOT_LOC_DAT_T;
typedef cvmx_mio_qlmx_cfg_t CAV_MIO_QLMX_CFG_T;
typedef cvmx_mio_twsx_sw_twsi_t CAV_MIO_TWSX_SW_TWSI_T;
typedef cvmx_mio_twsx_sw_twsi_ext_t CAV_MIO_TWSX_SW_TWSI_EXT_T;
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif
#endif /* __INCcavMioh */
