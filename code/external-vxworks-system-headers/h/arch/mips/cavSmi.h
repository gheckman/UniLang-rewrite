/* cavSmi.h - System Management Interface data types, macros and addresses */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,11may12,l_z  recover CAV_GMXX_INF_MODE for other CAVIUM BSP.
01h,09dec11,x_f  move CAV_GMXX_INF_MODE macro to cavGmx.h
01g,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01f,20oct10,d_c  Include SDK data types directly from SDK
01e,05oct10,d_c  Change ull to ULL to be Diab compatible
01d,28sep10,d_c  Make cav header names consistent.
                 Merge in definitions and typedefs from cavSmiReg.h (deleted).
01c,13sep10,d_c  Update cavSmi interface to include the SMI interface number
01b,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01a,06aug10,d_c  written

DESCRIPTION

This file declares macros, typedefs, and prototypes for Cavium SMI hardware.

*/

#ifndef __INCcavSmih
#define __INCcavSmih

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-smix-defs.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-smi-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_SMI_CMD(x)    ((0x8001180000001800ULL) + ((x)&1)*256)
#define CAV_SMI_RD_DAT(x) ((0x8001180000001810ULL) + ((x)&1)*256)
#define CAV_SMI_WR_DAT(x) ((0x8001180000001808ULL) + ((x)&1)*256)
#define CAV_SMI_EN(x)     ((0x8001180000001820ULL) + ((x)&1)*256)

#ifndef CAV_GMXX_INF_MODE
#define CAV_GMXX_INF_MODE(x)  ((0x80011800080007F8ULL) + ((x)&1)*0x8000000ULL)
#endif /* CAV_GMXX_INF_MODE */

/* typedefs */

typedef  cvmx_smix_cmd_t CAV_SMIX_CMD_T;
typedef  cvmx_smix_rd_dat_t CAV_SMIX_RD_DAT_T;
typedef  cvmx_smix_wr_dat_t CAV_SMIX_WR_DAT_T;

/* functions */

IMPORT void cavSmiEnable
    (
    int smiInterface
     );
IMPORT STATUS cavSmiRead
    (
    int smiInterface,
    UINT8 phyAddr,
    UINT8 regAddr,
    int timeout,
    UINT16 *pDataVal
    );

IMPORT STATUS cavSmiWrite
    (
    int smiInterface,
    UINT8 phyAddr,
    UINT8 regAddr,
    int timeout,
    UINT16 dataVal
    );

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavSmih */


