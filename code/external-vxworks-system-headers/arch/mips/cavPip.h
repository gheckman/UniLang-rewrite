/* cavPip.h - PIP interface data types, macros and addresses */

/*
 * Copyright (c) 2010,2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,09dec11,x_f  add defines for OcteonII CN68xx
01e,07jul11,rlg  Setup for SDK TYPEDEFS only
01d,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01c,20oct10,d_c  Include SDK data types directly from SDK
01b,05oct10,d_c  Change ull to ULL to be Diab compatible.
                 Removed unused enum CAV_PIP_PORT_PARSE_MODE_T.
01a,06aug10,d_c  written
*/

#ifndef __INCcavPiph
#define __INCcavPiph

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-utils.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-csr-enums.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-pip-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_PIP_SFT_RST    0x80011800A0000030ULL

#define CAV_PIP_PRT_CFGX(offset) \
    (0x80011800A0000200ull + ((offset) & 63) * 8)

#define CAV_PIP_PRT_TAGX(offset) \
    (0x80011800A0000400ull + ((offset) & 63) * 8)

#define CAV_PIP_PRT_CFGBX(offset) \
    (0x80011800A0008000ull + ((offset) & 63) * 8)

/* typedefs */

typedef cvmx_pip_sft_rst_t           CAV_PIP_SFT_RST_T;

/* functions */

IMPORT void cavPipPortConfig
    (
    int port,
    int qos,
    int group
    );

IMPORT void cavPipPortCrcEnable
    (
    int port
    );

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavPiph */
