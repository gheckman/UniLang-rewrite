
/* cavPow.h -  Cavium Support Routines */
/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01j,09dec11,x_f  add defines for OcteonII CN68xx
01i,07jul11,rlg  Setup for SDK TYPEDEFS only
01h,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01g,07feb11,d_c  Fix defect WIND00253754. Add define for number of POW groups
01f,28jan11,d_c  Fix compile warning
01e,20oct10,d_c  Include SDK data types directly from SDK
01d,05oct10,d_c  Change ull to ULL to be Diab compatible
01c,28sep10,d_c  Make cav header names consistent.
01b,13aug10,d_c  Add interface elements to support vxbOcteonEnd.c
01a,26jul10,rlg  Written
*/

/*
DESCRIPTION

This file declares macros, typedefs, and prototypes for general,
non-device-specific access routines for Cavium hardware.

*/

#ifndef __INCcavPowh
#define __INCcavPowh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-utils.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-csr-enums.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-packet.h)

#include CAV_SDK_DRV_INCLUDE(cvmx-pow-defs.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-sso-defs.h)
#include <arch/mips/cavWqe.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAV_POW_BASE_ADDR       0x8001670000000000ULL

#define CAV_POW_NUM_GROUPS      16

#define CAV_POW_PP_GRP_MSK0_OFF 0x0
#define CAV_POW_PP_GRP_MSKX_SP  0x8

#define CAV_POW_WQ_INT_THR0_OFF 0x80
#define CAV_POW_WQ_INT_THRX_SP  0x8

#define CAV_POW_WQ_INT_CNT0_OFF 0x100
#define CAV_POW_WQ_INT_CNTX_SP  0x8

#define CAV_POW_QOS_THR0_OFF    0x180
#define CAV_POW_QOS_THRX_SP     0x8

#define CAV_POW_QOS_RND0_OFF    0x1C0
#define CAV_POW_QOS_RNDX_SP     0x8


#define CAV_POW_WQ_INT_OFF      0x200
#define CAV_POW_WQ_INT_PC_OFF   0x208
#define CAV_POW_NW_TIM_OFF      0x210
#define CAV_POW_ECC_ERR_OFF     0x218
#define CAV_POW_NOS_CNT_OFF     0x228
#define CAV_POW_PF_RST_MSK_OFF  0x230
#define CAV_POW_IQ_INT_OFF      0x238
#define CAV_POW_IQ_INT_EN_OFF   0x240

#define CAV_POW_WS_PC0_OFF      0x280
#define CAV_POW_WS_PCX_SP       0x8

#define CAV_POW_WA_PC0_OFF      0x300
#define CAV_POW_WA_PCX_SP       0x8

#define CAV_POW_IQ_CNT0_OFF     0x340
#define CAV_POW_IQ_CNTX_SP      0x8

#define CAV_POW_WA_COM_PC_OFF   0x380
#define CAV_POW_IQ_COM_CNT_OFF  0x388
#define CAV_POW_TS_PC_OFF       0x390
#define CAV_POW_DS_PC_OFF       0x398

#define CAV_POW_IQ_THR0_OFF     0x3A0
#define CAV_POW_IQ_THRX_SP      0x8

#define CAV_POW_BIST_STAT_OFF   0x3F8

#define CAV_SSO_NUM_GROUPS      64

#define CAV_SSO_WQ_INT          0x8001670000001000ULL
#define CAV_SSO_WQ_IQ_DIS       0x8001670000001010ULL
#define CAV_SSO_WQ_INT_PC       0x8001670000001020ULL
#define CAV_SSO_PPX_GRP_MSK(i)  (0x8001670000006000ULL + (i) * 8)
#define CAV_SSO_WQ_INT_THRX(i)  (0x8001670000007000ULL + (i) * 8)
#define CAV_SSO_WQ_INT_CNTX(i)  (0x8001670000008000ULL + (i) * 8)
#define CAV_SSO_IQ_CNTX(i)      (0x8001670000009000ULL + (i) * 8)
#define CAV_SSO_IQ_THRX(i)      (0x800167000000a000ULL + (i) * 8)

/* ACCESS MACROS */

#define CAV_POW_PP_GRP_MSKX(group) \
    (CAV_POW_BASE_ADDR + (CAV_POW_PP_GRP_MSK0_OFF + \
    ((group & 15) * CAV_POW_PP_GRP_MSKX_SP))) 

#if _BYTE_ORDER == _BIG_ENDIAN
#define CAV_POW_PP_GRP_MASK    0x000000000000ffffULL
#define CAV_POW_PP_GRP_MSK_SHIFT(x) (x)
#else
#define CAV_POW_PP_GRP_MASK    0xffff000000000000ULL
#define CAV_POW_PP_GRP_MSK_SHIFT(x) (x) << 48
#endif /* _BYTE_ORDER */

#define CAV_POW_WQ_INT_PC \
  (CAV_POW_BASE_ADDR + CAV_POW_WQ_INT_PC_OFF)

#define CAV_POW_WQ_INT \
    (CAV_POW_BASE_ADDR + CAV_POW_WQ_INT_OFF)
  

#define CAV_POW_WQ_INT_THRX(group) \
    (CAV_POW_BASE_ADDR + CAV_POW_WQ_INT_THR0_OFF \
     + (group & 15) * CAV_POW_WQ_INT_THRX_SP)
 

#define CAV_POW_TAG_TYPE_ORDERED    CVMX_POW_TAG_TYPE_ORDERED
#define CAV_POW_TAG_TYPE_ATOMIC     CVMX_POW_TAG_TYPE_ATOMIC
#define CAV_POW_TAG_TYPE_NULL       CVMX_POW_TAG_TYPE_NULL
#define CAV_POW_TAG_TYPE_NULL_NULL  CVMX_POW_TAG_TYPE_NULL_NULL

/* typedefs */

typedef enum
{
    CAV_POW_WAIT      = 1,
    CAV_POW_NO_WAIT   = 0
} CAV_POW_WAIT_T;

typedef cvmx_pow_wq_int_thrx_t    CAV_POW_WQ_INT_THRX_T;
typedef cvmx_pow_wq_int_t         CAV_POW_WQ_INT_T;
#if (OCTEON_MODEL == OCTEON_CN68XX)
typedef cvmx_sso_wq_int_thrx_t    CAV_SSO_WQ_INT_THRX_T;
typedef cvmx_sso_wq_int_t         CAV_SSO_WQ_INT_T;
#endif /* (OCTEON_MODEL == OCTEON_CN68XX) */

/* functions */

CAV_WQE_T * cavPowWorkRequestSync
    (
    CAV_POW_WAIT_T wait
    );


#ifdef __cplusplus
}
#endif
#endif /* __INCcavPowh */
