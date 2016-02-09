/* cavWqe.h - WQE data types, macros and addresses */

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
01e,07jul11,rlg  Setup for SDK TYPEDEFS only
01d,14jun11,d_c  Merge SDK 2.1.0 Build 395
01c,10nov10,d_c  add include of octeonMips64.h to pull in definitions of
                 CVMX_CACHE_LINE_ALIGNED
01b,20oct10,d_c  Include SDK data types directly from SDK
01a,06aug10,d_c  written
*/

#ifndef __INCcavWqeh
#define __INCcavWqeh

#include <arch/mips/private/octeonMips64.h>
#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-utils.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-csr-enums.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-packet.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-wqe.h)


#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

typedef cvmx_wqe_t                CAV_WQE_T;

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavWqeh */
