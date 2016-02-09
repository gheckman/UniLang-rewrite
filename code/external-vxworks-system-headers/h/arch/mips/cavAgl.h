/* cavAgl.h - AGL interface data types, macros and addresses */

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
01d,09dec11,x_f  add defines for OcteonII CN68xx
01c,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01b,29oct10,d_c  Correct bad addresses
01a,15oct10,d_c  written
*/

#ifndef __INCcavAglh
#define __INCcavAglh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-agl-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_AGL_GMX_BIST                 0x80011800E0000400ULL
#define CAV_AGL_GMX_INF_MODE             0x80011800E00007F8ULL
#define CAV_AGL_GMX_DRV_CTL              0x80011800E00007F0ULL

#define CAV_AGL_PRT0_CTL                 0x80011800E0002000ULL

#define CAV_GMX_ADDR(addr,offset)  \
  (addr + (offset & 1) * 2048)

#define CAV_AGL_GMX_PRTX_CFG(offset) \
  CAV_GMX_ADDR(0x80011800E0000010ULL, offset)
      
#define CAV_AGL_GMX_RXX_ADR_CAM0(offset) \
  CAV_GMX_ADDR(0x80011800E0000180ULL, offset)
       
#define CAV_AGL_GMX_RXX_ADR_CAM1(offset) \
  CAV_GMX_ADDR(0x80011800E0000188ULL, offset)

#define CAV_AGL_GMX_RXX_ADR_CAM2(offset) \
  CAV_GMX_ADDR(0x80011800E0000190ULL, offset)
  
#define CAV_AGL_GMX_RXX_ADR_CAM3(offset) \
  CAV_GMX_ADDR(0x80011800E0000198ULL, offset)
  
#define CAV_AGL_GMX_RXX_ADR_CAM4(offset) \
  CAV_GMX_ADDR(0x80011800E00001A0ULL, offset)

#define CAV_AGL_GMX_RXX_ADR_CAM5(offset) \
  CAV_GMX_ADDR(0x80011800E00001A8ULL, offset)
  
#define CAV_AGL_GMX_RXX_FRM_CTL(offset) \
  CAV_GMX_ADDR(0x80011800E0000018ULL, offset)

#define CAV_AGL_GMX_RXX_FRM_MAX(offset) \
  CAV_GMX_ADDR(0x80011800E0000030ULL, offset)
	
#define CAV_AGL_GMX_SMACX(offset)		\
  CAV_GMX_ADDR(0x80011800E0000230ULL, offset)

#define CAV_AGL_GMX_RXX_ADR_CAM_EN(offset) \
  CAV_GMX_ADDR(0x80011800E0000108ULL, offset)

#define CAV_AGL_GMX_RXX_ADR_CTL(offset) \
  CAV_GMX_ADDR(0x80011800E0000100ULL, offset)

#define CAV_AGL_GMX_RXX_JABBER(offset) \
  CAV_GMX_ADDR(0x80011800E0000038ULL, offset)

#define CAV_AGL_GMX_TXX_CLK(offset)   \
  CAV_GMX_ADDR(0x80011800E0000208ULL, offset)

/* typedefs */

typedef cvmx_agl_gmx_bist_t         CAV_AGL_GMX_BIST_T;
typedef cvmx_agl_gmx_drv_ctl_t      CAV_AGL_GMX_DRV_CTL_T;
typedef cvmx_agl_gmx_inf_mode_t     CAV_AGL_GMX_INF_MODE_T;
typedef cvmx_agl_gmx_prtx_cfg_t     CAV_AGL_GMX_PRTX_CFG_T;
typedef cvmx_agl_gmx_rxx_adr_ctl_t  CAV_AGL_GMX_RXX_ADR_CTL_T;
typedef cvmx_agl_gmx_rxx_frm_ctl_t  CAV_AGL_GMX_RXX_FRM_CTL_T;
typedef cvmx_agl_prtx_ctl_t         CAV_AGL_PRTX_CFG_T;
  
#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavAglh */
