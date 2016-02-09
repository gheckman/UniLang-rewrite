/* cavUsb.h - USB Interface data types, macros and addresses */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,19dec11,x_f  written

DESCRIPTION

This file declares macros, typedefs, and prototypes for Cavium USB hardware.

*/

#ifndef __INCcavUsbh
#define __INCcavUsbh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-uctlx-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_UCTLX_CLK_RST_CTL(blkId)     (0x800118006F000000ull)
#define CAV_UCTLX_UPHY_CTL_STATUS(blkId) (0x800118006F000008ull)
#define CAV_UCTLX_UPHY_PORT0_CTL_STATUS(blkId) (0x800118006F000010ull)
#define CAV_UCTLX_UPHY_PORT1_CTL_STATUS(blkId) (0x800118006F000018ull)
#define CAV_UCTLX_INT_REG(blkId)         (0x800118006F000020ull)
#define CAV_UCTLX_INT_ENA(blkId)         (0x800118006F000028ull)
#define CAV_UCTLX_IF_ENA(blkId)          (0x800118006F000030ull)
#define CAV_UCTLX_PPAF_WM(blkId)         (0x800118006F000038ull)
#define CAV_UCTLX_EHCI_CTL(blkId)        (0x800118006F000080ull)
#define CAV_UCTLX_OHCI_CTL(blkId)        (0x800118006F000088ull)
#define CAV_UCTLX_ERTO_CTL(blkId)        (0x800118006F000090ull)
#define CAV_UCTLX_ORTO_CTL(blkId)        (0x800118006F000098ull)
#define CAV_UCTLX_BIST_STATUS(blkId)     (0x800118006F0000A0ull)
#define CAV_UCTLX_EHCI_FLA(blkId)        (0x800118006F0000A8ull)
#define CAV_UAHC0_EHCI_HCCAPBASE         (0x80016F0000000000ull)
#define CAV_UAHC0_OHCI_HCREVISION        (0x80016F0000000400ull)

/* typedefs */

typedef cvmx_uctlx_if_ena_t             CAV_UCTLX_IF_ENA_T;
typedef cvmx_uctlx_clk_rst_ctl_t        CAV_UCTLX_CLK_RST_CTL_T;
typedef cvmx_uctlx_uphy_ctl_status_t    CAV_UCTLX_UPHY_CTL_STATUS_T;
typedef cvmx_uctlx_uphy_portx_ctl_status_t CAV_UCTLX_UPHY_PORTX_CTL_STATUS_T;
typedef cvmx_uctlx_ehci_fla_t           CAV_UCTLX_EHCI_FLA_T;
typedef cvmx_uctlx_ehci_ctl_t           CAV_UCTLX_EHCI_CTL_T;
typedef cvmx_uctlx_ohci_ctl_t           CAV_UCTLX_OHCI_CTL_T;

/* functions */

void   cavUsbClockStart(void);
STATUS cavUsbEhciHcdInit(void);
STATUS cavUsbOhciHcdInit(void);

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavUsbh */

