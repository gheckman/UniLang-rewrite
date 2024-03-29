/* pciClass.h - PCI Standard Classifications definition header */

/*
Copyright (c) 1984-2005 Wind River Systems, Inc. 
The right to copy, distribute, modify, or otherwise make use 
of this software may be licensed only pursuant to the terms of 
an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
01b,23jun05,mdo  Updating per latest spec.
01a,18aug99,mas  created from merge of PCI class info from dmsLib.h/01b and
         pciConfigLib.h/02b.
*/

#ifndef __INCpciClassh
#define __INCpciClassh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PCI classifications are composed from the concatenation of four byte-size
 * components: primary (base) class, sub-class, register interface, and
 * revision ID.  The following comprise the standard PCI classification
 * definitions.
 */

/*
 * PCI Primary (Base) Class definitions for find by class function
 * Classes 0x12 - 0xFE are reserved for future enhancements
 */

#define PCI_CLASS_PRE_PCI20     0x00
#define PCI_CLASS_MASS_STORAGE  0x01
#define PCI_CLASS_NETWORK_CTLR  0x02
#define PCI_CLASS_DISPLAY_CTLR  0x03
#define PCI_CLASS_MMEDIA_DEVICE 0x04
#define PCI_CLASS_MEM_CTLR      0x05
#define PCI_CLASS_BRIDGE_CTLR   0x06
#define PCI_CLASS_COMM_CTLR     0x07
#define PCI_CLASS_BASE_PERIPH   0x08
#define PCI_CLASS_INPUT_DEVICE  0x09
#define PCI_CLASS_DOCK_DEVICE   0x0A
#define PCI_CLASS_PROCESSOR     0x0B
#define PCI_CLASS_SERIAL_BUS    0x0C
#define PCI_CLASS_WIRELESS      0x0D
#define PCI_CLASS_INTLGNT_IO    0x0E
#define PCI_CLASS_SAT_COMM      0x0F
#define PCI_CLASS_EN_DECRYPTION 0x10
#define PCI_CLASS_DAQ_DSP       0x11
#define PCI_CLASS_UNDEFINED     0xFF


/* PCI Subclass definitions */

#define PCI_SUBCLASS_00         0x00
#define PCI_SUBCLASS_01         0x01
#define PCI_SUBCLASS_02         0x02
#define PCI_SUBCLASS_03         0x03
#define PCI_SUBCLASS_04         0x04
#define PCI_SUBCLASS_05         0x05
#define PCI_SUBCLASS_06         0x06
#define PCI_SUBCLASS_07         0x07
#define PCI_SUBCLASS_08         0x08
#define PCI_SUBCLASS_09         0x09
#define PCI_SUBCLASS_0A         0x0A
#define PCI_SUBCLASS_10         0x10
#define PCI_SUBCLASS_11         0x11
#define PCI_SUBCLASS_12         0x12
#define PCI_SUBCLASS_20         0x20
#define PCI_SUBCLASS_40         0x40
#define PCI_SUBCLASS_80         0x80

/* Base Class 00 are Rev 1.0 and are not defined here. */

/* Mass Storage subclasses - Base Class 01h */

#define PCI_SUBCLASS_MASS_SCSI      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MASS_IDE       (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MASS_FLOPPY    (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MASS_IPI       (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_MASS_RAID      (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_MASS_ATA       (PCI_SUBCLASS_05)
#  define PCI_REG_IF_ATA_SNGL        0x20
#  define PCI_REG_IF_ATA_CHND        0x30
#define PCI_SUBCLASS_MASS_OTHER     (PCI_SUBCLASS_80)

/* Network subclasses - Base Class 02h */

#define PCI_SUBCLASS_NET_ETHERNET   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_NET_TOKEN_RING (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_NET_FDDI       (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_NET_ATM        (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_NET_ISDN       (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_NET_WFIP       (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_NET_PCMIG214   (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_NET_OTHER      (PCI_SUBCLASS_80)

/* Display subclasses - Base Class 03h */

#define PCI_SUBCLASS_DISPLAY_VGA    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_VGA_STD         0x00
#  define PCI_REG_IF_VGA_8514        0x01
#define PCI_SUBCLASS_DISPLAY_XGA    (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_DISPLAY_3D     (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_DISPLAY_OTHER  (PCI_SUBCLASS_80)

/* Multimedia subclasses  - Base Class 04h */

#define PCI_SUBCLASS_MMEDIA_VIDEO   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MMEDIA_AUDIO   (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MMEDIA_PHONY   (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MMEDIA_OTHER   (PCI_SUBCLASS_80)

/* Memory subclasses - Base Class 05h */

#define PCI_SUBCLASS_MEM_RAM        (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_MEM_FLASH      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_MEM_OTHER      (PCI_SUBCLASS_80)

/* Bus Bridge Device subclasses - Base Class 06h */

#define PCI_SUBCLASS_HOST_PCI_BRIDGE    (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_ISA_BRIDGE         (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_EISA_BRIDGE        (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_MCA_BRIDGE         (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_P2P_BRIDGE         (PCI_SUBCLASS_04)
#  define PCI_REG_IF_P2P_STD             0x00
#  define PCI_REG_IF_P2P_SUB_DECODE      0x01
#define PCI_SUBCLASS_PCMCIA_BRIDGE      (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_NUBUS_BRIDGE       (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_CARDBUS_BRIDGE     (PCI_SUBCLASS_07)
#define PCI_SUBCLASS_RACEWAY_BRIDGE     (PCI_SUBCLASS_08)
#  define PCI_REG_IF_RACEWAY_XPARENT     0x00
#  define PCI_REG_IF_RACEWAY_END_PNT     0x01
#define PCI_SUBCLASS_SEMI_XPARENT       (PCI_SUBCLASS_09)
#  define PCI_REG_IF_SEMI_XPARENT_PRI    0x40
#  define PCI_REG_IF_SEMI_XPARENT_SEC    0x80
#define PCI_SUBCLASS_INFINI2PCI         (PCI_SUBCLASS_0A)
#define PCI_SUBCLASS_OTHER_BRIDGE       (PCI_SUBCLASS_80)

/* Simple Communications Controller subclasses - Base Class 07h */

#define PCI_SUBCLASS_SCC_SERIAL     (PCI_SUBCLASS_00)
#  define PCI_REG_IF_SERIAL_XT       0x00
#  define PCI_REG_IF_SERIAL_16450    0x01
#  define PCI_REG_IF_SERIAL_16550    0x02
#  define PCI_REG_IF_SERIAL_16650    0x03
#  define PCI_REG_IF_SERIAL_16750    0x04
#  define PCI_REG_IF_SERIAL_16850    0x05
#  define PCI_REG_IF_SERIAL_16950    0x06
#define PCI_SUBCLASS_SCC_PARLEL     (PCI_SUBCLASS_01)
#  define PCI_REG_IF_PARLEL_XT       0x00
#  define PCI_REG_IF_PARLEL_BIDIR    0x01
#  define PCI_REG_IF_PARLEL_ECP      0x02
#  define PCI_REG_IF_PARLEL_1284CTLR 0x03
#  define PCI_REG_IF_PARLEL_1284TGT  0xFE
#define PCI_SUBCLASS_SCC_MULTI      (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_SCC_MODEM      (PCI_SUBCLASS_03)
#  define PCI_REG_IF_MODEM_GENERIC   0x00
#  define PCI_REG_IF_MODEM_16450     0x01
#  define PCI_REG_IF_MODEM_16550     0x02
#  define PCI_REG_IF_MODEM_16650     0x03
#  define PCI_REG_IF_MODEM_16750     0x04
#define PCI_SUBCLASS_SCC_GPIB       (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SCC_SMRTCRD    (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_SCC_OTHER      (PCI_SUBCLASS_80)


/* Base System subclasses - Base Class 08h */

#define PCI_SUBCLASS_BASESYS_PIC    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_PIC_GEN8259      0x00
#  define PCI_REG_IF_PIC_ISA          0x01
#  define PCI_REG_IF_PIC_EISA         0x02
#  define PCI_REG_IF_PIC_APIC         0x10
#  define PCI_REG_IF_PIC_xAPIC        0x20
#define PCI_SUBCLASS_BASESYS_DMA    (PCI_SUBCLASS_01)
#  define PCI_REG_IF_DMA_GEN8237      0x00
#  define PCI_REG_IF_DMA_ISA          0x01
#  define PCI_REG_IF_DMA_EISA         0x02
#define PCI_SUBCLASS_BASESYS_TIMER  (PCI_SUBCLASS_02)
#  define PCI_REG_IF_TIMER_GEN8254    0x00
#  define PCI_REG_IF_TIMER_ISA        0x01
#  define PCI_REG_IF_TIMER_EISA       0x02
#define PCI_SUBCLASS_BASESYS_RTC    (PCI_SUBCLASS_03)
#  define PCI_REG_IF_RTC_GENERIC      0x00
#  define PCI_REG_IF_RTC_ISA          0x01
#define PCI_SUBCLASS_BASESYS_HOTPLUG    (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_BASESYS_OTHER  (PCI_SUBCLASS_80)

/* Input Device subclasses - Base Class 09h */

#define PCI_SUBCLASS_INPUT_KEYBD    (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_INPUT_PEN      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_INPUT_MOUSE    (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_INPUT_SCANR    (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_INPUT_GAMEPORT (PCI_SUBCLASS_04)
#  define PCI_REG_IF_GAMEPORT_GENERIC     0x00
#  define PCI_REG_IF_GAMEPORT_LEGACY      0x10
#define PCI_SUBCLASS_INPUT_OTHER    (PCI_SUBCLASS_80)

/* Docking Station subclasses - Base Class 0Ah */

#define PCI_SUBCLASS_DOCSTATN_GENERIC   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_DOCSTATN_OTHER (PCI_SUBCLASS_80)

/* Processor subclasses - Base Class 0Bh */

#define PCI_SUBCLASS_PROCESSOR_386      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_PROCESSOR_486      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_PROCESSOR_PENTIUM  (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_PROCESSOR_ALPHA    (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_PROCESSOR_POWERPC  (PCI_SUBCLASS_20)
#define PCI_SUBCLASS_PROCESSOR_MIPS     (PCI_SUBCLASS_30)
#define PCI_SUBCLASS_PROCESSOR_COPROC   (PCI_SUBCLASS_40)

/* Serial bus subclasses - Base Class 0Ch */

#define PCI_SUBCLASS_SERBUS_FIREWIRE    (PCI_SUBCLASS_00)
#  define PCI_REG_IF_FIREWIRE_1394       0x00
#  define PCI_REG_IF_FIREWIRE_HCI1394    0x10
#define PCI_SUBCLASS_SERBUS_ACCESS      (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_SERBUS_SSA         (PCI_SUBCLASS_02)
#define PCI_SUBCLASS_SERBUS_USB         (PCI_SUBCLASS_03)
#  define PCI_REG_IF_USB_UHCI            0x00
#  define PCI_REG_IF_USB_OHCI            0x10
#  define PCI_REG_IF_USB_ANY             0x80
#  define PCI_REG_IF_USB_NONHOST         0xFE
#define PCI_SUBCLASS_SERBUS_FIBRE_CHAN  (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SERBUS_SMBUS       (PCI_SUBCLASS_05)
#define PCI_SUBCLASS_SERBUS_INFINI      (PCI_SUBCLASS_06)
#define PCI_SUBCLASS_SERBUS_IPMI        (PCI_SUBCLASS_07)
#  define PCI_REG_IF_IPMI_SMIC           0x00
#  define PCI_REG_IF_IPMI_KYBD           0x01
#  define PCI_REG_IF_IPMI_BLCK           0x02
#define PCI_SUBCLASS_SERBUS_SERCOS      (PCI_SUBCLASS_08)
#define PCI_SUBCLASS_SERBUS_CAN         (PCI_SUBCLASS_09)
#define PCI_SUBCLASS_SERBUS_OTHER       (PCI_SUBCLASS_80)

/* Wireless subclasses - Base Class 0Dh */

#define PCI_SUBCLASS_WIRELESS_IRDA      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_WIRELESS_OTHER_IR  (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_WIRELESS_RF        (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_WIRELESS_BTOOTH    (PCI_SUBCLASS_11)
#define PCI_SUBCLASS_WIRELESS_BBAND     (PCI_SUBCLASS_12)
#define PCI_SUBCLASS_WIRELESS_OTHER     (PCI_SUBCLASS_80)

/*
 * Intelligent I/O subclasses - Base Class 0Eh
 * REG_IF values greater than 0x00 are reserved for I2O
 */

#define PCI_SUBCLASS_INTELIO        (PCI_SUBCLASS_00)
#  define PCI_REG_IF_INTELIO_MSG_FIFO     0x00
#define PCI_8UBCLASS_INTELIO_OTHER  (PCI_SUBCLASS_00)

/* Satellite Device Communication subclasses - Base Class 0Fh */

#define PCI_SUBCLASS_SATCOM_TV      (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_SATCOM_AUDIO   (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_SATCOM_VOICE   (PCI_SUBCLASS_03)
#define PCI_SUBCLASS_SATCOM_DATA    (PCI_SUBCLASS_04)
#define PCI_SUBCLASS_SATCOM_OTHER   (PCI_SUBCLASS_80)

/* Encryption/Decryption subclasses - Base Class 10h */

#define PCI_SUBCLASS_EN_DECRYP_NETWORK  (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_EN_DECRYP_ENTRTMNT (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_EN_DECRYP_OTHER    (PCI_SUBCLASS_80)

/* Data Acquisition and Signal Processing subclasses - Base Class 11h */

#define PCI_SUBCLASS_DAQ_DSP_DPIO   (PCI_SUBCLASS_00)
#define PCI_SUBCLASS_DAQ_DSP_PCTRS  (PCI_SUBCLASS_01)
#define PCI_SUBCLASS_DAQ_DSP_COMM   (PCI_SUBCLASS_10)
#define PCI_SUBCLASS_DAQ_DSP_MGMT   (PCI_SUBCLASS_20)
#define PCI_SUBCLASS_DAQ_DSP_OTHER  (PCI_SUBCLASS_80)

#ifdef __cplusplus
}
#endif

#endif  /* __INCpciClassh */

