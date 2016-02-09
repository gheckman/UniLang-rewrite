/* pwrOrphanPciDevices.h - definitions for Pwr Orphan PCI Devices */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,10jul12,rbc  WIND00361107 - Fix issue with multiple devices that have same
                 VendorId and DeviceId
01c,09apr12,rbc  WIND00315814 - Fix power management image reboot if
                 INCLUDE_NETWORK is excluded
01b,05aug11,rbc  WIND00290401 - Callback for orphan device power management
01a,22jul11,rbc  WIND00255358 - Initial Creation
*/

#ifndef __INCpwrOrphanPciDevicesh
#define __INCpwrOrphanPciDevicesh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Private adapter context structure.
 */

/* Power Management Capabilities Cfg Space Offsets */

#define PMCAP_ID_OFFSET       0x00
#define PMCAP_NEXTPTR_OFFSET  0x01
#define PMCAP_PMC_OFFSET      0x02
#define PMCAP_PMCSR_OFFSET    0x04
#define PMCAP_PMCSRBSE_OFFSET 0x06
#define PMCAP_DATA_OFFSET     0x07

/* Power Management Capabilities Register */

#define PMC_SPEC_MASK 0x0007
#define PMC_SPEC_1_0  0x0001
#define PMC_SPEC_1_1  0x0002
#define PMC_SPEC_1_2  0x0003

#define PMC_PME_CLK_MASK 0x0008
#define PMC_PME_CLK_REQ  0x0008

#define PMC_DSI_MASK 0x0020
#define PMC_DSI      0x0020

#define PMC_AUX_CURR_MASK 0x01C0
#define PMC_AUX_CURR_000  0x0000
#define PMC_AUX_CURR_055  0x0040
#define PMC_AUX_CURR_100  0x0080
#define PMC_AUX_CURR_160  0x00C0
#define PMC_AUX_CURR_220  0x0100
#define PMC_AUX_CURR_270  0x0140
#define PMC_AUX_CURR_320  0x0180
#define PMC_AUX_CURR_375  0x01C0

#define PMC_D1_SUPPORT_MASK 0x0200
#define PMC_D1_SUPPORT      0x0200

#define PMC_D2_SUPPORT_MASK 0x0400
#define PMC_D2_SUPPORT      0x0400

#define PMC_PME_SUPPORT_MASK   0xF800
#define PMC_PME_SUPPORT_D0     0x0800
#define PMC_PME_SUPPORT_D1     0x1000
#define PMC_PME_SUPPORT_D2     0x2000
#define PMC_PME_SUPPORT_D3HOT  0x4000
#define PMC_PME_SUPPORT_D3COLD 0x8000

/* Power Management Control and Status Register */

#define PMCSR_PWR_STATE_MASK  0x0003
#define PMCSR_PWR_STATE_D0    0x0000
#define PMCSR_PWR_STATE_D1    0x0001
#define PMCSR_PWR_STATE_D2    0x0002
#define PMCSR_PWR_STATE_D3    0x0003

#define PMCSR_PME_ENABLE_MASK 0x0100
#define PMCSR_PME_ENABLE      0x0100

#define PMCSR_DATA_SELECT_MASK 0x1E00

#define PMCSR_DATA_SCALE_MASK 0x6000

#define PMCSR_PME_STATUS_MASK 0x8000
#define PMCSR_PME_ASSERTED    0x8000

/* Power Management Capabilities Structure */

typedef struct pci_pm_capability
    {
    UINT8  pmCapId;
    UINT8  pmCapNextPtr;
    UINT16 pmCapPMC;
    UINT16 pmCapPMCSR;
    UINT8  pmCapPMCSRBSE;
    UINT8  pmCapData;
    } PCI_PM_CAPABILITY;

#define PCI_CFG_SIZE 16

typedef struct pwr_orphan_pci_device
    {
    VXB_DEVICE_ID pDev;             /* pointer to vxbus device */
    UINT16 pciVendId;               /* PCI Vendor ID for orphan device */
    UINT16 pciDevId;                /* PCI Device ID for orphan device */
    UINT32 pciConfig[PCI_CFG_SIZE]; /* PCI Config storage for orphan device */
    } PWR_ORPHAN_PCI_DEVICE;

/* Driver Control Structure */

typedef struct pci_orphan_device
    {
    VXB_DEVICE_ID devId;
    UINT32 unit;
    BOOL pmCapable;
    UINT8 pmCapableOffset;
    PCI_PM_CAPABILITY pciPmCap;
    } PCI_ORPHAN_DEVICE;

/* Utility functions */

void pwrPciOrphanInit(void);
void pwrPciOrphansD0(void);
void pwrPciOrphansD3(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCpwrOrphanPciDevicesh */
