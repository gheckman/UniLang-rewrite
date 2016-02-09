/* cavGmx.h - Gigabit Media interface data types, macros and addresses */

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
01g,11may12,l_z  Compute the register address dynamically
01f,09dec11,x_f  add defines for OcteonII CN68xx
01e,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01d,20oct10,d_c  Include SDK data types directly from SDK
01c,05oct10,d_c  Change ull to ULL to be Diab compatible
01b,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01a,06aug10,d_c  written
*/

#ifndef __INCcavGmxh
#define __INCcavGmxh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-gmxx-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/*
 * Base address and offsets for Gigabit Media interface. These
 * constants are used in the address computation macros
 * below. Generally, the offset to the first register of a particular
 * type is defined here. The address computation macros then use
 * arithmetic to compute the Nth instance of a register.
 */

#define CAV_GMX0_BASE_ADDR              0x8001180008000000ULL
#define CAV_GMX0_PRT0_CFG_OFF           0x010
#define CAV_GMX0_SMAC0_OFF              0x230
#define CAV_GMX0_RX_PRTS_OFF            0x410
#define CAV_GMX0_TX_PRTS_OFF            0x480
#define CAV_GMX0_RX0_ADR_CAM0_OFF       0x180
#define CAV_GMX0_RX0_ADR_CAM_EN_OFF     0x108
#define CAV_GMX0_RX0_ADR_CTL_OFF        0x100
#define CAV_GMX0_TX0_CLK_OFF            0x208
#define CAV_GMX0_TX0_SLOT_OFF           0x220
#define CAV_GMX0_TX0_BURST_OFF          0x228
#define CAV_GMX0_TX0_THRESH_OFF         0x210
#define CAV_GMX0_TX0_PIPE_OFF           0x310
#define CAV_GMX0_BPID_MAPX_OFF          0x680
#define CAV_GMX0_BPID_MSK_OFF           0x700
#define CAV_GMX0_INF_MODE_OFF           0x7f8

/*
 * Compute offset to register for a particular port, based on the
 * interface number, and the offset within that interface.
 */

LOCAL __inline__  uint64_t CAV_GMXX_PORT_OFF (offset, interface)
    {
    if (CAV_PROC_ID_IN(CAV_PROC_ID_CN68XX))
        return ((uint64_t)(((offset & 3) + (interface & 7) * 0x2000ULL) * 2048));
    else
        return ((uint64_t)(((offset & 3) + (interface & 1) * 0x10000ULL) * 2048));
    }

LOCAL __inline__  uint64_t CAV_GMXX_RX_PRTS (interface)
    {
    if (CAV_PROC_ID_IN(CAV_PROC_ID_CN68XX))
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_RX_PRTS_OFF \
               + (interface & 7) * 0x1000000ULL);
    else
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_RX_PRTS_OFF \
               + (interface & 1) * 0x8000000ULL);
    }

LOCAL __inline__  uint64_t CAV_GMXX_TX_PRTS (interface)
    {
    if (CAV_PROC_ID_IN(CAV_PROC_ID_CN68XX))
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX_PRTS_OFF \
               + (interface & 7) * 0x1000000ULL);
    else
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX_PRTS_OFF \
               + (interface & 1) * 0x8000000ULL);
    }
    
LOCAL __inline__  uint64_t CAV_GMXX_INF_MODE (interface)
    {
    if (CAV_PROC_ID_IN(CAV_PROC_ID_CN68XX))
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_INF_MODE_OFF \
                + (interface & 7) * 0x1000000ULL);
    else
        return (CAV_GMX0_BASE_ADDR + CAV_GMX0_INF_MODE_OFF \
               + (interface & 1) * 0x8000000ULL);
    }

#define CAV_GMXX_BPID_MAPX(index, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_BPID_MAPX_OFF \
     + ((index & 0xF) + (interface & 7) * 0x200000ULL) * 8)

#define CAV_GMXX_BPID_MSK(interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_BPID_MSK_OFF \
     + (interface & 7) * 0x1000000ULL)

#define CAV_GMXX_PRTX_CFG(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_PRT0_CFG_OFF \
    + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_SMACX(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_SMAC0_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_RXX_ADR_CAMX(cam, offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_RX0_ADR_CAM0_OFF + (cam * 8) \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_RXX_ADR_CAM_EN(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_RX0_ADR_CAM_EN_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_RXX_ADR_CTL(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_RX0_ADR_CTL_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_TXX_CLK(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX0_CLK_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_TXX_SLOT(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX0_SLOT_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_TXX_BURST(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX0_BURST_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_TXX_THRESH(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX0_THRESH_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

#define CAV_GMXX_TXX_PIPE(offset, interface) \
    (CAV_GMX0_BASE_ADDR + CAV_GMX0_TX0_PIPE_OFF \
     + CAV_GMXX_PORT_OFF(offset, interface))

/* typedefs */

typedef cvmx_gmxx_prtx_cfg_t           CAV_GMXX_PRTX_CFG_T;
typedef cvmx_gmxx_rxx_adr_ctl_t        CAV_GMXX_RXX_ADR_CTL_T;
typedef cvmx_gmxx_rxx_adr_cam_en_t     CAV_GMXX_RXX_ADR_CAM_EN_T;
typedef cvmx_gmxx_inf_mode_t           CAV_GMXX_INF_MODE_T;
typedef cvmx_gmxx_bpid_mapx_t          CAV_GMXX_BPID_MAPX_T;
typedef cvmx_gmxx_bpid_msk_t           CAV_GMXX_BPID_MSK_T;
typedef cvmx_gmxx_txx_thresh_t         CAV_GMXX_TXX_THRESH_T;
typedef cvmx_gmxx_txx_pipe_t           CAV_GMXX_TXX_PIPE_T;

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavGmxh */
