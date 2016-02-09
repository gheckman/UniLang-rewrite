/* cavIpd.h - IPD interface data types, macros and addresses */

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
01d,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01c,20oct10,d_c  Include SDK data types directly from SDK
01b,05oct10,d_c  Change ull to ULL to be Diab compatible
01a,06aug10,d_c  written
*/

#ifndef __INCcavIpdh
#define __INCcavIpdh

#include <arch/mips/private/cavSdkDrvInclude.h>
#include CAV_SDK_DRV_INCLUDE(cvmx-csr-enums.h)
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-ipd-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_IPD_BASE_ADDR              0x80014F0000000000ULL
#define CAV_IPD_CTL_STATUS_OFF         0x018
#define CAV_IPD_QOS0_RED_MARKS_OFF     0x178
#define CAV_IPD_RED_QUE0_PARAM_OFF     0x2e0
#define CAV_IPD_PORT0_BP_PAGE_CNT_OFF  0x028
#define CAV_IPD_RED_PORT_ENABLE_OFF    0x2d8
#define CAV_IPD_BP_PRT_RED_END_OFF     0x328
#define CAV_IPD_BPIDX_MBUF_TH_OFF      0x2000
#define CAV_IPD_ON_BP_DROP_PKT0_OFF    0x4100
#define CAV_IPD_RED_BPID_ENABLE0_OFF   0x4200
#define CAV_IPD_RED_DELAY_OFF          0x4300

#define CAV_IPD_CTL_STATUS				\
    (CAV_IPD_BASE_ADDR + CAV_IPD_CTL_STATUS_OFF)

#define CAV_IPD_QOSX_RED_MARKS(queue) \
    (CAV_IPD_BASE_ADDR + CAV_IPD_QOS0_RED_MARKS_OFF + (queue & 7) * 8)

#define CAV_IPD_RED_QUEX_PARAM(queue) \
    (CAV_IPD_BASE_ADDR + CAV_IPD_RED_QUE0_PARAM_OFF + (queue & 7) * 8)

#define CAV_IPD_PORTX_BP_PAGE_CNT(port) \
    (CAV_IPD_BASE_ADDR + CAV_IPD_PORT0_BP_PAGE_CNT_OFF + (port & 63) * 8)

#define CAV_IPD_RED_PORT_ENABLE \
    (CAV_IPD_BASE_ADDR + CAV_IPD_RED_PORT_ENABLE_OFF)

#define CAV_IPD_BP_PRT_RED_END \
    (CAV_IPD_BASE_ADDR + CAV_IPD_BP_PRT_RED_END_OFF) 

#define CAV_IPD_BPIDX_MBUF_TH(offset) \
    (CAV_IPD_BASE_ADDR + CAV_IPD_BPIDX_MBUF_TH_OFF + ((offset) & 63) * 8)

#define CAV_IPD_ON_BP_DROP_PKT0 \
    (CAV_IPD_BASE_ADDR + CAV_IPD_ON_BP_DROP_PKT0_OFF)

#define CAV_IPD_RED_DELAY \
    (CAV_IPD_BASE_ADDR + CAV_IPD_RED_DELAY_OFF)

#define CAV_IPD_RED_BPID_ENABLE0 \
    (CAV_IPD_BASE_ADDR + CAV_IPD_RED_BPID_ENABLE0_OFF)

/* Port number defines below are only for CN68XX */

#define CAV_CN68XX_IPD_PORT_LOOPBACK   0x0
#define CAV_CN68XX_IPD_PORT_DPI        0x100
#define CAV_CN68XX_IPD_PORT_ILK0       0x400
#define CAV_CN68XX_IPD_PORT_ILK1       0x500
#define CAV_CN68XX_IPD_PORT_GMX0       0x800
#define CAV_CN68XX_IPD_PORT_GMX1       0x900
#define CAV_CN68XX_IPD_PORT_GMX2       0xA00
#define CAV_CN68XX_IPD_PORT_GMX3       0xB00
#define CAV_CN68XX_IPD_PORT_GMX4       0xC00

/* typedefs */

typedef enum {
    CAV_IPD_OPC_MODE_STT        = CVMX_IPD_OPC_MODE_STT,
    CAV_IPD_OPC_MODE_STF        = CVMX_IPD_OPC_MODE_STF,
    CAV_IPD_OPC_MODE_STF1_STT   = CVMX_IPD_OPC_MODE_STF1_STT,
    CAV_IPD_OPC_MODE_STF2_STT   = CVMX_IPD_OPC_MODE_STF2_STT
} CAV_IPD_MODE_T;

typedef cvmx_ipd_ctl_status_t           CAV_IPD_CTL_STATUS_T;
typedef cvmx_ipd_qosx_red_marks_t       CAV_IPD_QOSX_RED_MARKS_T;
typedef cvmx_ipd_red_quex_param_t       CAV_IPD_RED_QUEX_PARAM_T;
typedef cvmx_ipd_portx_bp_page_cnt_t    CAV_IPD_PORTX_BP_PAGE_CNT_T;
typedef cvmx_ipd_bp_prt_red_end_t       CAV_IPD_BP_PRT_RED_END_T;
typedef cvmx_ipd_red_port_enable_t      CAV_IPD_RED_PORT_ENABLE_T;
#if (OCTEON_MODEL == OCTEON_CN68XX)
typedef cvmx_ipd_red_delay_t            CAV_IPD_RED_DELAY_T;
typedef cvmx_ipd_red_bpid_enablex_t     CAV_IPD_RED_BPID_ENABLEX_T;
#endif /* (OCTEON_MODEL == OCTEON_CN68XX) */

/* functions */

IMPORT void cavIpdConfig
    (
    int poolSize
    );
IMPORT void cavIpdEnable (void);
  
#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavIpdh */
