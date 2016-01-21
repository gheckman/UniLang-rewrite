/* cavPcs.h - PCS interface data types, macros and addresses */

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
01b,24aug10,pgh  Fix mismatch ()
01a,06aug10,d_c  written
*/

#ifndef __INCcavPcsh
#define __INCcavPcsh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-pcsx-defs.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-pcsxx-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */
#define CAV_PCS_BASE_ADDR                 0x80011800B0001000ULL
#define CAV_PCS0_MR0_CONTROL_REG_OFF      0x00
#define CAV_PCS0_AN0_ADV_REG_OFF          0x10
#define CAV_PCS0_MR0_STATUS_REG_OFF       0x08
/*
 * Compute offset to register for a particular port, based on the
 * interface number, and the offset within that interface.
 */

LOCAL __inline__  uint64_t CAV_PCSX_PORT_OFF(offset, interface)
    {
    if (CAV_PROC_ID_IN(CAV_PROC_ID_CN68XX))
        return (((offset & 3) + ((interface & 7) * 0x4000ULL)) * 1024);
    else
        return (((offset & 3) + ((interface & 1) * 0x20000ULL)) * 1024);
    }

/* PCS address computation macros */
      
#define CAV_PCSX_MRX_CONTROL_REG(offset, interface) \
    (CAV_PCS_BASE_ADDR + CAV_PCS0_MR0_CONTROL_REG_OFF \
     + CAV_PCSX_PORT_OFF(offset, interface))

#define CAV_PCSX_ANX_ADV_REG(offset, interface) \
    (CAV_PCS_BASE_ADDR + CAV_PCS0_AN0_ADV_REG_OFF \
     + CAV_PCSX_PORT_OFF(offset, interface))

#define CAV_PCSX_MRX_STATUS_REG(offset, interface) \
    (CAV_PCS_BASE_ADDR + CAV_PCS0_MR0_STATUS_REG_OFF \
     + CAV_PCSX_PORT_OFF(offset, interface))

/* typedefs */

typedef cvmx_pcsx_mrx_control_reg_t    CAV_PCSX_MRX_CONTROL_REG_T;
typedef cvmx_pcsx_anx_adv_reg_t        CAV_PCSX_ANX_ADV_REG_T;
typedef cvmx_pcsx_mrx_status_reg_t     CAV_PCSX_MRX_STATUS_REG_T;


#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavPcsh */
