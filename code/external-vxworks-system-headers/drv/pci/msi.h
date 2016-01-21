/* msi.h - Message Signaled Interrupts header file */

/*
 * Copyright (c) 2005, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,12jan13,j_z  add MSI-X register.(WIND00333514)
01a,24jun05,mdo  Written.
*/

#ifndef msi_H
#define msi_H

#ifdef __cplusplus
extern "C" {
#endif

/* MSI-X registers */

#define PCI_MSIX_CTL                    0x02    /* Offset of MSI-X control register */
#define PCI_MSIX_CTL_TABLE_SIZE         0x7ff
#define PCI_MSIX_CTL_FUNCTION_MASK      0x4000
#define PCI_MSIX_CTL_ENABLE             0x8000  /* MSI-X enable */

#define PCI_MSIX_TABLE                  0x04
#define PCI_MSIX_TABLE_OFFSET_MASK      0xfffffff8
#define PCI_MSIX_TABLE_BIR_MASK         0x07

#define PCI_MSIX_PBA                    0x08
#define PCI_MSIX_PBA_OFFSET_MASK        0xfffffff8
#define PCI_MSIX_PBA_BIR_MASK           0x07

/* MSI-X Table Entry Dword offset */

#define PCI_MSIX_MSG_ADDR_LOW           0x00
#define PCI_MSIX_MSG_ADDR_HIGH          0x01
#define PCI_MSIX_MSG_DATA               0x02
#define PCI_MSIX_MSG_CTRL               0x03
#define PCI_MSIX_MSG_CTRL_MASK          (1 << 0)

/* Message Signaled Interrupts registers */

/* Message Control Register */

#define PCI_MSI_CTL                     0x02    /* Offset of MSI control register */
#define PCI_MSI_CTL_ENABLE              0x01    /* MSI enable */
#define PCI_MSI_CTL_MSG_ALLOC           0x70    /* Number of Messages allocated */
#define PCI_MSI_CTL_MSG_MAX             0x0E    /* Maximum Messages Allowed */
#define PCI_MSI_CTL_64BIT               0x80    /* 64-bit addresses allowed */
#define PCI_MSI_CTL_MASK                0x100   /* Per-vector masking capable */

/* Message Address Register */

#define PCI_MSI_ADDR_LO                 0x04    /* Offset of MSI Address Lower 32 bits */
                                                /* Used for 32-bit MSI */  
#define PCI_MSI_ADDR_HI                 0x08    /* Offset of MSI Address Upper 32 bits */
                                                /* Used with 64-bit MSI */
/* Message Data Register */

#define PCI_MSI_DATA_32                 0x08    /* Offset of MSI Data Register */
                                                /* Used for 32-bit MSI */
#define PCI_MSI_DATA_64                 0x0C    /* Offset of MSI Data Register */
                                                /* Used for 64-bit MSI */
/* Message Per-Vector Mask Register */

#define PCI_MSI_MASK_32                 0x0C    /* Offset of MSI Mask Register */
                                                /* Used for 32-bit MSI */
#define PCI_MSI_MASK_64                 0x10    /* Offset of MSI Mask Register */
                                                /* Used for 64-bit MSI */

#define MSI_ENABLED (ctlReg)       (ctlReg & PCI_MSI_CTL_ENABLE)
#define ADDR_64BIT (ctlReg)        (ctlReg & PCI_MSI_CTL_64BIT)

#define MSI_ENABLE_MSG (ctlReg, msgNum) \
    ctlReg |= (((msgNum >> 1) << 4) & PCI_MSI_CTL_MESS_ALLOC);

#define MSI_ENABLE (ctlReg, msgNum) MSI_ENABLE_MSG (ctlReg, msgNum); \
    ctlReg |= PCI_MSI_FLAGS_ENABLE

#define MSI_DISABLE (ctlReg)        ctlReg &= ~PCI_MSI_CTL_ENABLE

#ifdef __cplusplus
}
#endif
                                 /* Used for 64-bit MSI */
#endif /* msi_H */

