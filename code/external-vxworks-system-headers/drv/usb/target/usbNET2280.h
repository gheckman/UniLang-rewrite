/* usbNET2280.h - Definitions for NetChip NET 2280 USB target controller */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,13jan10,ghs  vxWorks 6.9 LP64 adapting
01g,30sep04,pdg  Removed the endianness macros and function calls for register
                 reads and writes
01f,29sep04,ami  Changes related to Mips Testing
01e,20sep04,ami  NET2280 tested in High Speed
01d,17sep04,ami  After Control, Interrupt IN and Bulk OUT Testing
01c,08sep04,ami	 Code Review Incorporated
01b,03sep04,ami	 Design Changes
01a,29jun04,pmr  written.
*/

/*
DESCRIPTION

Defines constants related to the NetChip NET 2280 USB device (target) IC.
*/

#ifndef __INCusbNet2280h
#define __INCusbNet2280h

/* includes */
#include "usb/usbPciLib.h"
#include "cacheLib.h"

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* Endpoint Indices */

#define NET2280_ENDPT_0_OUT   		0x0	/* Endpoint 0 OUT */
#define NET2280_ENDPT_A			0x1	/* Endpoint A */
#define NET2280_ENDPT_B			0x2	/* Endpoint B */
#define NET2280_ENDPT_C			0x3	/* Endpoint C */
#define NET2280_ENDPT_D			0x4	/* Endpoint D */
#define NET2280_ENDPT_E			0x5	/* Endpoint E */
#define NET2280_ENDPT_F			0x6	/* Endpoint F */
#define NET2280_ENDPT_0_IN              0x7     /* Endpoint 0 IN */

#define NET2280_ENDPT_CFGOUT		0xA	/* Endpoint CFG OUT */
#define NET2280_ENDPT_CFGIN		0xB	/* Endpoint CFG IN */
#define NET2280_ENDPT_PCIOUT		0xC	/* Endpoint PCI OUT */
#define NET2280_ENDPT_PCIIN		0xD	/* Endpoint PCI IN */
#define NET2280_ENDPT_STATIN		0xF	/* ENDpoint STATIN */

/* Main Control Registers */

#define NET2280_DEVINIT_REG		0x00	/* Device Initialization */
#define NET2280_EECTL_REG		0x04	/* EEPROM Control */
#define NET2280_EECLKFREQ_REG		0x08	/* EEPROM Clock Frequency */
#define NET2280_PCIIRQENB0_REG		0x10/* PCI Interrupt Request Enable 0*/
#define NET2280_PCIIRQENB1_REG		0x14/* PCI Interrupt Request Enable 1*/
#define NET2280_CPUIRQENB0_REG		0x18/* CPU Interrupt Request Enable 0*/
#define NET2280_CPUIRQENB1_REG		0x1C/* CPU Interrupt Request Enable 1*/
#define NET2280_USBIRQENB1_REG		0x24/* USB Interrupt Request Enable 1*/
#define NET2280_IRQSTAT0_REG		0x28	/* Interrupt Request Status 0*/
#define NET2280_IRQSTAT1_REG		0x2C	/* Interrupt Request Status 1*/
#define NET2280_IDXADDR_REG		0x30	/* Index Regsiter Address */
#define NET2280_IDXDATA_REG		0x34	/* Index Register Data */
#define NET2280_FIFOCTL_REG		0x38	/* FIFO Control */
#define NET2280_MEMADDR_REG		0x40	/* FIFO Memory Diagnostic addr*/
#define NET2280_MEMDATA0_REG		0x44	/* FIFO Memory Diagnostic Data0*/
#define NET2280_MEMDATA1_REG		0x48	/* FIFO Memory Diagnostic Data1*/
#define NET2280_GPIOCTL_REG		0x50	/* General Purpose Control Reg.*/
#define NET2280_GPIOSTAT_REG		0x54	/* General Purpose Status Reg */

/* USB Control Registers */

#define NET2280_STDRSP_REG		0x80	/* Standard Response Regsiter */
#define NET2280_PRODVENDID_REG		0x84	/* Product/Vendor ID */
#define NET2280_RELNUM_REG		0x88	/* Release Number */
#define NET2280_USBCTL_REG		0x8C	/* USB Control */
#define NET2280_USBSTAT_REG		0x90	/* USB Status */
#define NET2280_XCVRDIAG_REG		0x94	/* Transceiver Mode Regsiter */
#define NET2280_SETUP0123_REG		0x98	/* Setup Bytes 0,1,2,3 */
#define NET2280_SETUP4567_REG		0x9C	/* Setup Bytes 4,5,6,7 */
#define NET2280_OURADDR_REG		0xA4	/* Address Register */
#define NET2280_OURCONFIG_REG		0xA8	/* Configuration Register */

/* PCI Control Registers */

#define NET2280_PCIMSTCTL_REG		0x100	/* PCI Master Control */
#define NET2280_PCIMSTADDR_REG		0x104	/* PCI Master Address */
#define NET2280_PCIMSTDATA_REG		0x108	/* PCI Master Data */
#define NET2280_PCIMSTSTAT_REG		0x10C	/* PCI Master Status */

/* DMA  Registers */

#define NET2280_DMACTL_OFFSET(x)	\
	(NET2280_DMA_REG_BASE(x) + 0x00)	/* DMA Control */
#define NET2280_DMASTAT_OFFSET(x)		\
	(NET2280_DMA_REG_BASE(x) + 0x04)	/* DMA Status */
#define NET2280_DMACOUNT_OFFSET(x)		\
	(NET2280_DMA_REG_BASE(x) + 0x10)	/* DMA Count */
#define NET2280_DMAADDR_OFFSET(x)		\
	(NET2280_DMA_REG_BASE(x) + 0x14)	/* DMA Address */
#define NET2280_DMADESC_OFFSET(x)		\
	(NET2280_DMA_REG_BASE(x) + 0x18)	/* DMA Descriptor */

/*
 * DMA channels are permanently associated with endpoints.  The driver will
 * select the DMA channel based upon which endpoint is being used. The base
 * address should be added with the offset of the register
 */

#define NET2280_DMA_REG_BASE(x)		(0x160 + 0x20 * x)

/* Dedicated Endpoint Registers */

#define NET2280_DEP_CFG_OFFSET		0x0	/* DEP_CFG Offset */
#define NET2280_DEP_RSP_OFFSET		0x4	/* DEP_RES Offset */

#define NET2280_DEP_CFGOUT_REG_BASE	0x200	/* CFG OUT Base */
#define NET2280_DEP_CFGIN_REG_BASE	0x210	/* CFG IN Base */
#define NET2280_DEP_PCIOUT_REG_BASE	0x220	/* PCI OUT Base */
#define NET2280_DEP_PCIIN_REG_BASE	0x230	/* PCI IN Base */
#define NET2280_DEP_STATIN_REG_BASE	0x240	/* STAT IN Base */

/* Configurable Endpoint / FIFO Registers */

#define NET2280_EP_CFG_OFFSET(x)	\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x00)	/* endpt config. offset */
#define NET2280_EP_RSP_OFFSET(x)		\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x04)	/* endpt response offset */
#define NET2280_EP_IRQENB_OFFSET(x)	\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x08)	/* endpt intr enable offset */
#define NET2280_EP_STAT_OFFSET(x)		\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x0C)	/* endpt status offset */
#define NET2280_EP_AVAIL_OFFSET(x)		\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x10)	/* endpt avail offset */
#define NET2280_EP_DATA_OFFSET(x)		\
       	(NET2280_EP_REG_BASE((UINT32)x) + 0x14)	/* endpt data offset */

/*
 * Every endpoint has a seperate set of register. Add the endpoint register
 * offset with  the base address
 */

#define NET2280_EP_REG_BASE(x)		(0x300 + 0x20 * x)

/* Indexed Registers */

#define NET2280_DIAG_IDX		0x00	/* Diagnostic Control Reg */
#define NET2280_PKTLEN_IDX		0x01	/* Packet Length Reg */
#define NET2280_FRAME_IDX		0x02	/* Frame Counter Reg */
#define NET2280_CHIPREV_IDX		0x03	/* Chip Revision Reg */
#define NET2280_HS_MAXPOWER_IDX		0x06	/* HS Max Power Reg */
#define NET2280_FS_MAXPOWER_IDX		0x07	/* FS Max Power Reg */
#define NET2280_HS_INTPOLL_RATE_IDX	0x08	/* HS Int Polling Rate */
#define NET2280_FS_INTPOLL_RATE_IDX	0x09	/* FS Int Poling Rate */
#define NET2280_HS_NAK_RATE_IDX		0x0A	/* HS NAK Rate Reg */
#define NET2280_SCRATCH_IDX		0x0B	/* Scratch Pad */

#define NET2280_EP_X_HS_MAXPKT_IDX(x)   (0x10 + x * 0x10)
#define NET2280_EP_X_FS_MAXPKT_IDX(x)   (0x11 + x * 0x10)

/* Bits & Masks */

#define NET2280_OURADDR_REG_MASK	0x7F	/* OURADDR: Address Mask */
#define NET2280_OURADDR_REG_FI		0x80	/* OURADDR: Force Immediate */

#define NET2280_USBSTAT_REG_MASK	0xF0	/* USBSTAT: Register Mask */
#define NET2280_USBSTAT_REG_GENDEVREMWKUP	0x10	/* USBSTAT: */
							/* Generate Remote */
							/* Wakeup */
#define NET2280_USBSTAT_REG_GENRES	0x20	/* USBSTAT: Generate Resume */
#define NET2280_USBSTAT_FS		0x40	/* USBSTAT: Full Speed */
#define NET2280_USBSTAT_HS		0x80  	/* USBSTAT: High Speed */

#define NET2280_USBCTL_REG_MASK		0x00FF3EFF  /* USBCTL: Reg Mask */
#define NET2280_USBCTL_REG_SERNUMID	0x00FF0000  /* USBCTL: Serial */
						    /* Index Number */
#define NET2280_USBCTL_REG_PRODIDEN	0x00002000  /* USBCTL: Prod ID */
#define NET2280_USBCTL_REG_VENDIDEN	0x00001000  /* USBCTL: Vend ID */
#define NET2280_USBCTL_REG_RPWE		0x00000800  /* USBCTL: Rem WKUP */
#define NET2280_USBCTL_REG_VBUSPIN	0x00000400  /* USBCTL: VBUS */
#define NET2280_USBCTL_REG_SUSPIMM	0x00000080  /* USBCTL: SUSP IMMD */
#define NET2280_USBCTL_REG_SPUD		0x00000040  /* USBCTL: Self Powered*/
#define NET2280_USBCTL_REG_RWS		0x00000020  /* USBCTL: Rem WKUP Sup */
#define NET2280_USBCTL_REG_USBDE	0x00000008  /* USBCTL: USB Detect Enb */
#define NET2280_USBCTL_REG_DRWUE	0x00000002  /* USBCTL: Dev Remote */
                                                    /* Wake Enable*/
#define NET2280_USBCTL_REG_SPWRSTAT	0x00000001  /* USBCTL: Self Powered */
						    /* Status */

#define NET2280_FRAME_REG_MASK		0x7FF	/* FRAME: Frame Mask */

#define NET2280_DEVINIT_REG_MASK	0xFFF	/* DEVINIT: Reg Mask */
#define NET2280_DEVINIT_REG_FRC_PCI_RESET 0x080	/* DEVINIT: Force PCI Reset */
#define NET2280_DEVINIT_REG_PCI_ID	0x040	/* DEVINIT: PCI ID */
#define NET2280_DEVINIT_PCIEN		0x020	/* DEVINIT: PCI Enable */
#define NET2280_DEVINIT_FIFO_RESET	0x010	/* DEVINIT: FIFO Reset */
#define NET2280_DEVINIT_CFG_RESET	0x008	/* DEVINIT: CFG Reset */
#define NET2280_DEVINIT_PCI_RESET	0x004	/* DEVINIT: PCI Reset */
#define NET2280_DEVINIT_USB_RESET	0x002	/* DEVINIT: USB Reset */
#define NET2280_DEVINIT_8051_RESET	0x001	/* DEVINIT: 851 Reset */
#define NET2280_DEVINIT_FULL_RESET	(NET2280_DEVINIT_FIFO_RESET | \
					 NET2280_DEVINIT_USB_RESET | \
					 NET2280_DEVINIT_8051_RESET)
#define NET2280_DEVINIT_CLK_FREQ        (8 << 8)/* DEVINIT: CLK FREQUENCY */

/* Interrupt enable registers (CPU, PCI, & USB) */

#define NET2280_XIRQENB0_SETUP		0x00000080
#define NET2280_XIRQENB0_EP(x)		(1 << x)
#define NET2280_XIRQENB0_MASK           0x000000FF

#define NET2280_XIRQENB1_REG_MASK	0x8E1B3FDF  /* Reg. Mask */
#define NET2280_XIRQENB1_INTEN		0x80000000  /* XIRQENB1: PCI INT Enable*/
#define NET2280_XIRQENB1_PSCINTEN	0x08000000  /* XIRQENB1: PWR State */
                                                    /* Change Interrupt Enable */
#define NET2280_XIRQENB1_PCIARTTIMEOUT  0x04000000  /* XIRQENB1: PCI Arbiter */
						    /* Timeout Interrupt Enable */
#define NET2280_XIRQENB1_PCIPARITYERR	0x02000000  /* PCI Parity Error */
#define NET2280_XIRQENB1_PCIRTYABORT	0x00020000  /* PCI Retry Abort */
#define NET2280_XIRQENB1_PCIMASCYCLEDN	0x00010000  /* PCI Master Cycle Done */
#define NET2280_XIRQENB1_GPIO		0x00002000  /* General I/O */
#define NET2280_XIRQENB1_DMA(x)		(0x00000100 << x) /* DMA Int Enable */
#define NET2280_XIRQENB1_EEPD		0x00000100	/* EEPROM done */
#define NET2280_XIRQENB1_VBUS		0x00000080	/* VBUS change */
#define NET2280_XIRQENB1_CS		0x00000040	/* control status */
#define NET2280_XIRQENB1_RPRESET	0x00000010	/* root port reset */
#define NET2280_XIRQENB1_SUSP		0x00000008	/* suspend request */
#define NET2280_XIRQENB1_SUSREQCHG	0x00000004	/* susp. req. change */
#define NET2280_XIRQENB1_RESM		0x00000002	/* resume */
#define NET2280_XIRQENB1_SOF		0x00000001	/* start-of-frame */

/* Interrupt status registers - status bits are cleared by writing a 1 */

#define NET2280_IRQENB0_SETUP		0x00000080
#define NET2280_IRQENB0_EP(x)		(1 << x)
#define NET2280_IRQENB0_EPMASK          0x0000007F

#define NET2280_IRQENB1_REG_MASK	0x8E1B3FDF  /* Reg. Mask */
#define NET2280_IRQENB1_INTEN		0x80000000  /* IRQENB1: PCI INT */
#define NET2280_IRQENB1_PSCINTEN	0x08000000  /* IRQENB1: PWR State */
                                                    /* Change Interrupt */
#define NET2280_IRQENB1_PCIARTTIMEOUT  0x04000000  /* XIRQENB1: PCI Arbiter */
						    /* Timeout Interrupt */
#define NET2280_IRQENB1_PCIPARITYERR	0x02000000  /* PCI Parity Error */
#define NET2280_IRQENB1_PCIRTYABORT	0x00020000  /* PCI Retry Abort */
#define NET2280_IRQENB1_PCIMASCYCLEDN	0x00010000  /* PCI Master Cycle Done */
#define NET2280_IRQENB1_GPIO		0x00002000  /* General I/O */
#define NET2280_IRQENB1_DMA(x)		(0x00000100 << x) /* DMA Int */
#define NET2280_IRQENB1_EEPD		0x00000100	/* EEPROM done */
#define NET2280_IRQENB1_VBUS		0x00000080	/* VBUS change */
#define NET2280_IRQENB1_CS		0x00000040	/* control status */
#define NET2280_IRQENB1_RPRESET	        0x00000010	/* root port reset */
#define NET2280_IRQENB1_SUSP		0x00000008	/* suspend request */
#define NET2280_IRQENB1_SUSREQCHG	0x00000004	/* susp. req. change */
#define NET2280_IRQENB1_RESM		0x00000002	/* resume */
#define NET2280_IRQENB1_SOF		0x00000001	/* start-of-frame */
#define NET2280_IRQENB1_DMA_SHIFT       9               /* DMA shift value */

/* DMA registers */

#define NET2280_DMACTL_SG_INT_EN	0x02000000	/* scatter/gather int */
#define NET2280_DMACTL_SGE		0x00010000	/* scatter/gather en */
#define NET2280_DMACTL_ASE		0x00000010	/* auto start enable */
#define NET2280_DMACTL_PREENB		0x00000008	/* dma preempt enable */
#define NET2280_DMACTL_FIFOVAL		0x00000004	/* dma fifo validate */
#define NET2280_DMACTL_EN		0x00000002	/* dma enable */
#define NET2280_DMACTL_ADDRHOLD		0x00000001	/* dma address hold */

#define NET2280_DMASTAT_SG_INT		0x02000000	/* scatter/gather */
#define NET2280_DMASTAT_TD_INT		0x01000000	/* transact. done */
#define NET2280_DMASTAT_ABORT		0x00000002	/* abort DMA trans. */
#define NET2280_DMASTAT_START		0x00000001	/* start DMA trans. */

#define NET2280_DMACOUNT_VB		0x80000000	/* DMA valid bit */
#define NET2280_DMACOUNT_DIR		0x40000000	/* DMA direction */
#define NET2280_DMACOUNT_DIE		0x20000000	/* done int. enable */
#define	NET2280_DMACOUNT_BC		0x00FFFFFF	/* Byte count */

/* Test Mode Register */

#define NET2280_XCVRDIAG_TEST_MASK      0x07000000    /* XCVRDIAG: Mask bits */
#define NET2280_XCVRDIAG_TEST_SHIFT_VAL 24
#define NET2280_XCVRDIAG_TEST_MODE_SET(x) \
                                        ((x) << NET2280_XCVRDIAG_TEST_SHIFT_VAL)

/* Endpoint registers */
#define NET2280_EP_STAT_FIFOVC		0x0F000000	/* FIFO valid count */
#define NET2280_EP_STAT_HBOUTPID	0x00C00000	/* high bw OUT PID */
#define NET2280_EP_STAT_TIMEOUT		0x00200000	/* time out */
#define NET2280_EP_STAT_STALLSNT	0x00100000	/* stall sent */
#define NET2280_EP_STAT_INNAKSNT	0x00080000	/* USB IN NAK Sent */
#define NET2280_EP_STAT_INACKRCV	0x00040000	/* USB IN ACK Sent */
#define NET2280_EP_STAT_OPNAKSNT	0x00020000	/* USB OUT NAK Sent */
#define NET2280_EP_STAT_OUTACKSNT	0x00010000	/* USB OUT ACK Sent */
#define NET2280_EP_STAT_FIFO_OVERF	0x00002000	/* USB FIFO Overflow */
#define NET2280_EP_STAT_FIFO_UNDERF	0x00001000	/* USB FIFO Underflow*/
#define NET2280_EP_STAT_FIFO_FULL	0x00000800	/* USB FIFO Full */
#define NET2280_EP_STAT_FIFO_EMPTY	0x00000400	/* USB FIFO Empty */
#define NET2280_EP_STAT_FIFO_FLUSH	0x00000200	/* USB FIFO Flush */
#define NET2280_EP_STAT_SPOD		0x00000040	/* Short Packet Out */
							/* Done Interrupt */
#define NET2280_EP_STAT_SPT		0x00000020	/* Short Packet */
							/* Transmitted Intpt */
#define NET2280_EP_STAT_NAKOUT		0x00000010	/* NAK OUT Packets */
#define NET2280_EP_STAT_DPR		0x00000008	/* Data Packet */
							/* Received Interrupt */
#define NET2280_EP_STAT_DPT		0x00000004	/* Data Packet */
							/* Trnasmitted Intpt */
#define NET2280_EP_STAT_DOPT		0x00000002	/* Data OUT Token Int */
#define NET2280_EP_STAT_DIT		0x00000001	/* Data IN Toke Int */

#define NET2280_EP_CFG_REG_MASK		0x0007078F	/* EP_CFG: Mask Value */
#define NET2280_EP_CFG_EBC		0x00070000	/* EP_CFG: */
							/* Ept byte count */
#define NET2280_EP_CFG_ENABLE		0x00000400	/* EP_CFG: endpt enable*/
#define NET2280_EP_CFG_TYPE_INT		0x00000300	/* EP_CFG: interrupt */
							/* endpt type */
#define NET2280_EP_CFG_TYPE_BULK	0x00000200	/* EP_CFG: bulk endpt */
#define NET2280_EP_CFG_TYPE_ISO		0x00000100	/* EP_CFG: iso endpt */
#define NET2280_EP_CFG_TYPE_MASK        0x00000300	/* EP_CFG: Ept type */
#define NET2280_EP_CFG_DIRECTION	0x00000080	/* EP_CFG: Ept dir */
#define NET2280_EP_CFG_NUMBER		0x0000000F	/* EP_CFG: Ept no */
#define NET2280_EP_CFG_DIR_SHIFT        7               /* EP_CFG: dir shift */
#define NET2280_EP_CFG_TYPE_SHIFT       8               /* EP_CFG: type shift */
#define NET2280_EP_CFG_BYTE_CNT_SHIFT   16

/* Endpoint response register - bits are cleared on 0:7 and set on 8:15 */

#define NET2280_EP_RSP_NAKOUT		0x00000080
#define NET2280_EP_RSP_HIDSTAT		0x00000040
#define NET2280_EP_RSP_FCRCERR		0x00000020
#define NET2280_EP_RSP_INTMODE		0x00000010
#define NET2280_EP_RSP_CSPH		0x00000008	/* ctrl stat ph. h/s */
#define NET2280_EP_RSP_NAKOUTMOD	0x00000004
#define NET2280_EP_RSP_TOGGLE		0x00000002
#define NET2280_EP_RSP_STALL		0x00000001	/* endpoint halt */
#define NET2280_EP_RSP_SET(x)		(x << 8)
#define NET2280_EP_RSP_CLEAR(x)		(x)

/* Endpoint Interrupts */
#define NET2280_EP_IRQENB_SPOD		0x00000040	/* short pkt out done */
#define NET2280_EP_IRQENB_SPT		0x00000020	/* short pkt trans. */
#define NET2280_EP_IRQENB_DPR		0x00000008	/* data pkt recv'd */
#define NET2280_EP_IRQENB_DPT		0x00000004	/* data pkt trans. */
#define NET2280_EP_IRQENB_DOPT		0x00000002	/* data out/ping token*/
#define NET2280_EP_IRQENB_DIT		0x00000001	/* data in token */
#define NET2280_EP_IRQENB_DEFAULT	(NET2280_EP_IRQENB_SPOD | \
					NET2280_EP_IRQENB_SPT | \
					NET2280_EP_IRQENB_DPR | \
					NET2280_EP_IRQENB_DPT | \
					NET2280_EP_IRQENB_DOPT | \
					NET2280_EP_IRQENB_DIT)
#define NET2280_EP_IRQEBN_MASK          0x7F

/* NET 2280 endpoints */

#define NET2280_NUM_ENDPOINTS		8		/* 6 generic endpoint */
		    					/* 2 control endpoint */
							/* should be reported */
							/* to HAL */
/* NET 2280 DMA channels */

#define NET2280_DMA_CHANS		4

#define NET2280_DMA_ENPT_MASK           0xF

/* FIFO Configurations */

#define NET2280_FIFOCTL_CFG0		0		/* configuration 0 */
#define NET2280_FIFOCTL_CFG1		1		/* configuration 1 */
#define NET2280_FIFOCTL_CFG2		2		/* configuration 2 */

#define NET2280_FIFOCTL_CFG_MASK	0x03		/* Fifo config mask */

/* Maximum Packet Size */
#define NET2280_MAXPSIZE_8		0x0008
#define NET2280_MAXPSIZE_16		0x0010
#define NET2280_MAXPSIZE_32		0x0020
#define NET2280_MAXPSIZE_64		0x0040
#define NET2280_MAXPSIZE_128		0x0080
#define NET2280_MAXPSIZE_256		0x0100
#define NET2280_MAXPSIZE_512		0x0200
#define NET2280_MAXPSIZE_1024		0x0400

/* Definitions for number of transactions per frame */
#define NET2280_NTRANS_1       0x0  /* 1 packet per microframe */
#define NET2280_NTRANS_2       0x1  /* 2 packets per microframe */
#define NET2280_NTRANS_3       0x2  /* 3 packet per microframe */
#define NET2280_NTRANS_SHIFT   11

/* Device product / vendor information */
#define NET2280_PRODVENDID_PROD_MASK	0xFFFF0000
#define NET2280_PROD_ID			0x2280
#define NET2280_PRODID_SHIFT            16

/* Macros for reading from and writing to the net2280 registers */

#define NET2280_CFG_READ(pTarget,offset) \
	TO_LITTLEL(*(UINT32 *)(ULONG)(pTarget->ioBase[0] + offset))

#define NET2280_8051_READ(pTarget,offset) \
	TO_LITTLEL(*(UINT32 *)(ULONG)(pTarget->ioBase[1] + offset))

#define NET2280_FIFO_READ(pTarget,offset) \
	TO_LITTLEL(*(UINT32 *)(ULONG)(pTarget->ioBase[2] + offset))

#define NET2280_CFG_WRITE(pTarget,offset,value) \
	(*(UINT32 *)(ULONG)(pTarget->ioBase[0] + offset) = FROM_LITTLEL(value))

#define NET2280_8051_WRITE(pTarget,offset, value) \
	(*(UINT32 *)(ULONG)(pTarget->ioBase[1] + offset) = FROM_LITTLEL(value))

#define NET2280_FIFO_WRITE(pTarget,offset,value) \
	(*(UINT32 *)(ULONG)(pTarget->ioBase[2] + offset) = FROM_LITTLEL(value))

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbNet2280h */
