/* iPIIX4Dma.h - Intel 82371ab PCI-TO-ISA/IDEXCELERATOR(PIIX4) Driver Header file */

/* 
 * Copyright (c) 2001, 2005, 2007, 2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01g,06jul10,sye  Add support to 82801DB(ICH4). (WIND00125477)
01f,29apr10,pad  Moved extern C statement after include statements.
01e,15jun07,dee  WIND00097125 - support 82801 and 6300esb I/O hub controllers
01d,23sep05,dee  SPR#112529, define additional dma controller pci types
01c,02aug05,dee  dma support for PIIX4 ATA controller
01b,20dec01,bsp  function declaration changed.
01a,21Nov01,bsp  written.
*/

/*
 * Please refer to Intel Document Order Number: 290562-001
 * 82371AB PCI-TO-ISA / IDE XCELERATOR (PIIX4)
 */

#ifndef __INCiPIIX4Dmah
#define __INCiPIIX4Dmah

#ifndef _ASMLANGUAGE

    /* includes */

#include <vxWorks.h>
#include <drv/pci/pciConfigLib.h>
#include <drv/pci/pciHeaderDefs.h>
#include <wdLib.h>

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

#define I82371AB_VENDOR_ID         0x8086   /* Intel Corp. */
#define I82371AB_DEVICE_ID         0x7111   /* i82371AB PIIX4 */
#define I82801AA_DEVICE_ID         0x2411   /* i82801AA ICH */
#define I82801AB_DEVICE_ID         0x2421   /* i82801AB ICH0 */
#define I82801DB_DEVICE_ID         0x24CB   /* i82801DB ICH4 */
#define I82801_ICH6_DEVICE_ID	   0x2651   /* i82801FB ICH6 sata */
#define I82801FB_DEVICE_ID	   0x266F   /* i82801FB ICH6 ide */
#define I82801_ICH7A_DEVICE_ID	   0x27C4   /* i82801FB ICH7 sata */
#define I82801_ICH7B_DEVICE_ID	   0x27C0   /* i82801FB ICH7 ata */
#define I82372FB_DEVICE_ID         0x7601   /* i82372FB */
#define I6300ESB_P_DEVICE_ID	   0x25A2   /* 6300esb ata mode */
#define I6300ESB_C_DEVICE_ID	   0x25A3   /* 6300esb combined mode */

#define I82371AB_MAC_64_K          0x10000  /* pow(2,16) */
#define I82371AB_MAC_4_K           0x01000  /* pow(2,12) */
#define I82371AB_MAC_512           0x00200  /* pow(2,9) */

    /* max number of controllers */
#define I82371AB_MAX_CTRLS         0x2      /* 0 and 1 only */

    /* Offset in the PCI configuaration space */

#define PCI_CFG_BMIBA             PCI_CFG_BASE_ADDRESS_4

    /* 0x20-0x23 default = 0x0000 R/W */
#define PCI_CFG_IDETIM(ctrl)      (0x40 + ctrl * 2)
#define PCI_CFG_IDETIM_PRI        0x40   /* 0x40-0x41 default = 0x0000 R/W */
#define PCI_CFG_IDETIM_SEC        0x42   /* 0x42-0x43 default = 0x0000 R/W */
#define PCI_CFG_SIDETIME          0x44   /* 0x44      default = 0x00   R/W */
#define PCI_CFG_UDMACTL           0x48   /* 0x48      default = 0x00   R/W */
#define PCI_CFG_UDMATIM           0x4A   /* 0x4A-0x4B default = 0x0000 R/W */

    /* Page-78, 2.7, Ref-1 */

#define I82371AB_BMICOMadd(ctrl)  (ideController.ioBaseAddress + 0x0 + ctrl * 8)
#define I82371AB_BMISTAadd(ctrl)  (ideController.ioBaseAddress + 0x2 + ctrl * 8)
#define I82371AB_BMIDTPadd(ctrl)  (ideController.ioBaseAddress + 0x4 + ctrl * 8)
#define I82371AB_BMI_ALL          0xff
#define I82371AB_BMICOM           0x00
#define I82371AB_BMISTA           0x01
#define I82371AB_BMIDTP           0x02

    /* BMICOM */

#define I82371AB_RWCON            0x08
#define I82371AB_SSBM             0x01

    /* BMISTA */

#define I82371AB_DMA1CAP          0x40
#define I82371AB_DMA0CAP          0x20
#define I82371AB_INT_STATUS       0x04
#define I82371AB_IDEDMA_ERROR     0x02
#define I82371AB_BMIDE_ACTIVE     0x01

    /* bit masks */

#define I82371AB_BMBIA_ADD_MASK   0xfff0   /* valid bits 15 to 4 */
    
    /* PCI status */
#define I82371AB_PCISTS_BME   0x0004   /* bus master enable bit*/
#define I82371AB_PCISTS_IOSE  0x0001   /* I/O space enable bit */

    /* IDE Timing Register */
#define I82371AB_IDETIM_ENE   0x8000   /* IDE enable */
#define I82371AB_IDETIM_PPE0  0x0004   /* PPC0 enable */
#define I82371AB_IDETIM_IE0   0x0002   /* IORDY Sample Point  
                                          Enable Drive 0 */

/* A small delay for register hardware settling time*/

#define I82371AB_DELAY(ctrl)     sysInByte(I82371AB_BMISTAadd(ctrl)); \
                                 sysInByte(I82371AB_BMISTAadd(ctrl)); \
                                 sysInByte(I82371AB_BMISTAadd(ctrl)); \
                                 sysInByte(I82371AB_BMISTAadd(ctrl))

/* typedefs */

typedef struct pci_ide_controller
    {
    int               pciBusNo;
    int               pciDeviceNo;
    int               pciFuncNo;

    /* PCI configuaration Registers */

    PCI_HEADER_DEVICE pciHeader;
    UINT16            ideTim[2];    /* Primary   channel - 40,41 */
                                    /* Secondary channel - 42,43 */
    UINT8             slaveIdeTim;  /* 44    */
    UINT8             uDmaCtl;      /* 48    */
    UINT16            uDmaTime;     /* 4A-4B */

    /* IO Space Registers */

    UINT32            ioBaseAddress;
    UINT8             bmiCom[2];   /* 0x00 */
    UINT8             bmiSta[2];   /* 0x02 */
    UINT32            bmiDtp[2];   /* 0x04 */

    WDOG_ID           bmiWdogId[2];
    BOOL              bmiWdogOkay[2];
    UINT32          * pPRDTable[I82371AB_MAX_CTRLS];
    }PCI_IDE_CONTROLLER;

typedef struct i82371DescTable
    {
    void * buffer;
    UINT16 count;
    UINT16 eot;
#define END_OF_TABLE  0x8000;  /* end of table bit indication */
    } i82371_DESC_TBL;

/* function declarations  */

extern STATUS iPIIX4PciIdeCtrlInit      (int ctrl);
extern STATUS iPIIX4InitAtaDmaEngine    (int ctrl, int drive, char * pBuf, 
                                         UINT32 bufLength, int direction);
extern STATUS iPIIX4StartAtaDmaEngine   (int ctrl);
extern STATUS iPIIX4StopAtaDmaEngine    (int ctrl);
extern STATUS iPIIX4AtaDmaTrnsfrWait    (int ctrl, int time);
extern short  iPIIX4AtaDmaModeNegotiate (short rwmode);
extern void   iPIIX4IdeCtrlReset        (void);
extern STATUS iPIIX4AtaDmaModeSet       (int ctrl,int drive,short rwmode);

#ifdef IDEDMA_DEBUG
extern void   iPIIX4IdeDebugVerbosityLevelSet (int level);
extern int    iPIIX4IdeDebugVerbosityLevelGet (void);
#endif /* IDEDMA_DEBUG */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCiPIIX4Dmah */
