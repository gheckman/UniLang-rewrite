/* cavPci.h */

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
01d,06jul11,rlg  import typedefs directly from SDK
01c,21jan11,d_c  WIND00249323 - bring up PCIe on 63xx
01b,11oct10,d_c  Make compatible with Diab.
01a,26aug10,pgh  Written

DESCRIPTION

*/

#ifndef __CAV_PCI_H
#define __CAV_PCI_H

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-npi-defs.h)

/* defines */

#define CAV_NPEI_PCIE_MSI_RCV    0x0000000000003CB0ULL
#define CAV_SLI_PCIE_MSI_RCV     0x0000000000003CB0ULL

#define CAV_PEXP_NPEI_MSI_ENB0   0x80011F000000BC50ULL
#define CAV_PEXP_SLI_MSI_ENB0    0x80011F0000013C50ULL
	    
#define CAV_PEXP_NPEI_MSI_RCV0   0x80011F000000BC10ULL
#define CAV_PEXP_SLI_MSI_RCV0    0x80011F0000013C10ULL

#define CAV_NPI_CTL_STATUS       0x80011F0000000010ull

IMPORT void cavPciHostBridgeInit
    (
    unsigned long   base,
    UINT64 *        pciCfgDid,
    UINT64 *        pciIoDid,
    UINT64 *        pciMemDid
    );
IMPORT void cavPciExHostBridgeInit
    (
    int         pciExPortNum,
    BOOL *      initDone,
    UINT64 *    pciIoDid,
    UINT64 *    pciMemDid
    );
IMPORT UINT32 cavPciRead
    (
    int     width,      /* data width, in bytes */
    UINT64  pciAddr     /* PCI address to read from */
    );
IMPORT void cavPciWrite
    (
    int     width,      /* data width, in bytes */
    UINT64  pciAddr,    /* PCI address to write to */
    UINT32  data        /* Data to write to PCI */
    );
IMPORT UINT32 cavPciExRead
    (
    int     port,   /* PCIE port the device is on */
    int     bus,    /* sub bus */
    int     dev,    /* device ID */
    int     func,   /* device sub function */
    int     reg,    /* register to access */
    int     width   /* data width, in bytes */
    );
IMPORT void cavPciExWrite
    (
    int     port,   /* PCIE port the device is on */
    int     bus,    /* sub bus */
    int     dev,    /* device ID */
    int     func,   /* device sub function */
    int     reg,    /* register to access */
    int     width,  /* data width, in bytes */
    UINT32  data    /* Data to write to PCIE */
    );

#endif /* __CAV_PCI_H */
