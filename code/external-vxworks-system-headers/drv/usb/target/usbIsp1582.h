/* usbIsp1582.h - Definitions for Philips ISP 1582 USB target controller */

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01b,15jun04,hch  Merge after ISP1582 driver testing done on MIPS, SH.
01b,19jul04,ami Coding Convention Changes
01a,19apr04,ami First
*/

/*
DESCRIPTION

Defines constants related to the Philips ISP 1582 USB device (target) IC.
*/

#ifndef __INCusbIsp1582h
#define __INCusbIsp1582h

#ifdef	__cplusplus
extern "C" {
#endif


/* defines */

/* ISP 1582 Endpoint Index */

#define ISP1582_ENDPT_0_RX               0x0  /* Control Out Endpoint  */
#define ISP1582_ENDPT_1_RX               0x2  /* Out Endpoint 1 */
#define ISP1582_ENDPT_2_RX               0x4  /* Out Endpoint 2 */
#define ISP1582_ENDPT_3_RX               0x6  /* Out Endpoint 3 */
#define ISP1582_ENDPT_4_RX               0x8  /* Out Endpoint 4 */
#define ISP1582_ENDPT_5_RX               0xA  /* Out Endpoint 5 */
#define ISP1582_ENDPT_6_RX               0xC  /* Out Endpoint 6 */
#define ISP1582_ENDPT_7_RX               0xE  /* Out Endpoint 7 */

#define ISP1582_ENDPT_0_TX               0x1  /* Control In Endpoint */
#define ISP1582_ENDPT_1_TX               0x3  /* In Endpoint 1 */
#define ISP1582_ENDPT_2_TX               0x5  /* In Endpoint 2 */
#define ISP1582_ENDPT_3_TX               0x7  /* In Endpoint 3 */
#define ISP1582_ENDPT_4_TX               0x9  /* In Endpoint 4 */
#define ISP1582_ENDPT_5_TX               0xB  /* In Endpoint 5 */
#define ISP1582_ENDPT_6_TX               0xD  /* In Endpoint 6 */
#define ISP1582_ENDPT_7_TX               0xF  /* In Endpoint 7 */

/* ISP 1582 I/O registers */

/* Initialization Registers */
#define ISP1582_ADDRESS_REG              0x00     /* Address Register */
#define ISP1582_MODE_REG                 0x0C     /* Mode Register */
#define ISP1582_INT_CONFIG_REG           0x10     /* Interrupt Config. Reg. */
#define ISP_1582_OTG_REG                 0x12     /* OTG Register */
#define ISP_1582_INT_ENABLE_REG          0x14     /* Interrupt Enable Reg. */

/* Dataflow Registers */
#define ISP1582_ENDPT_INDEX_REG          0x2C   /* Endpoint Index Register */
#define ISP1582_CNTL_FUNC_REG            0x28   /* Control Function Register */
#define ISP1582_DATA_PORT_REG            0x20   /* Data Port Register */
#define ISP1582_BUF_LEN_REG              0x1C   /* Buffer Length Register */
#define ISP1582_BUF_STATUS_REG           0x1E   /* Buffer Status Register */
#define ISP1582_ENDPT_MAXPSIZE_REG       0x04   /* Max. Packet Size Register */
#define ISP1582_ENDPT_TYPE_REG           0x08   /* Endpoint Type Regsiter */

/* DMA Registers */
#define ISP1582_DMA_COMMAND_REG          0x30   /* DMA Command Register */
#define ISP1582_DMA_TRANS_CNT_REG        0x34   /* DMA Transfer Counter Reg. */
#define ISP1582_DMA_CONFIG_REG           0x38   /* DMA Config. Register */
#define ISP1582_DMA_HARDWARE_REG         0x3C   /* DMA Hardware Register */
#define ISP1582_DMA_INT_RESN_REG         0x50   /* DMA Interrupt Reason Reg */
#define ISP1582_DMA_INT_ENBL_REG         0x54   /* DMA Interrupt Enable Reg. */
#define ISP1582_DMA_ENDPT_REG            0x58   /* DMA Endpoint Regsiter */
#define ISP1582_DMA_BURST_COUNT_REG      0x64   /* DMA Burst Count Regsiter */

/* General Register */
#define ISP1582_INT_REG                  0x18   /* Interrupt Register */
#define ISP1582_CHIP_ID_REG              0x70   /* Chip ID */
#define ISP1582_FRM_NUM_REG              0x74   /* Frame Number Register */
#define ISP1582_SCRATCH_REG              0x78   /* Scratch Regsiter */
#define ISP1582_UNLOCK_DEV_REG           0x7C   /* Device Unlock Register */
#define ISP1582_TEST_MODE_REG            0x84   /* Test Mode Regsiter */

/* ISP 1582 endpoints */

#define ISP1582_NUM_ENDPOINTS		     16	   /* number of endpoints */

/* Maximum FIFO Size */
#define ISP1582_FIFO_SIZE                8192  /* 8 KBytes */

/* address register (read/write 1 byte) */

#define ISP1582_ADRS_REG_ADRS_MASK       0x7f    /* address bits */
#define ISP1582_ADRS_REG_ENABLE          0x80    /* enable bit */

/* mode register (read/write 2 bytes) */

#define ISP1582_MODE_REG_MASK            0x03FF  /* Mode Regsiter Mask */
#define ISP1582_MODE_REG_SOFTCT          0x0001  /* Soft Connect */
#define ISP1582_MODE_REG_POWRON          0x0002  /* Power On */
#define ISP1582_MODE_REG_WKUPCS          0x0004  /* Wake Up on Select */
#define ISP1582_MODE_REG_GLINTENA        0x0008  /* Global Interrupt Enable */
#define ISP1582_MODE_REG_SFRESET         0x0010  /* Soft Reset */
#define ISP1582_MODE_REG_GOSUSP          0x0020  /* Suspend Mode */
#define ISP1582_MODE_REG_SNDRSU          0x0040  /* Resume Signal */
#define ISP1582_MODE_REG_CLKAON          0x0080  /* Clock Always On */
#define ISP1582_MODE_REG_VBUSSTAT        0x0100  /* V-Bus Status */
#define ISP1582_MODE_REG_DMACLKON        0x0200  /* DMA Clock Always On */

/* interupt configuration register (read/write 1 byte) */

/* Control Debugging Modes */
#define ISP1582_INT_CONF_REG_CDBGMOD_MASK        0xC0 /* Control Mode Mask */
#define ISP1582_INT_CONF_REG_CDBGMOD_ACK_NAK     0x00 /* Interrupts on all */
                                                      /*ACKS & NAKS on Control */
                                                      /* Endpoint */

#define ISP1582_INT_CONF_REG_CDBGMOD_ACK_ONLY    0x01 /* Interrupts on only */
                                                      /* ACKS on Control */
                                                      /* Endpoint */
#define ISP1582_INT_CONF_REG_CDBGMOD_ACK_FST_NAK 0x02 /*Interrupts on all ACKS */
                                                      /* and first NAK on */
                                                      /* control endpoint */
#define ISP1582_INT_CONF_REG_CDBGMOD_SHIFT(b)    ((b)<<6) /* Shift Value */

/* Data Debug Mode IN */
#define ISP1582_INT_CONF_REG_DDBGMODIN_MASK        0x30 /* Data Debug Mode IN */
                                                        /* Mask Value*/
#define ISP1582_INT_CONF_REG_DDBGMODIN_ACK_NAK     0x00 /* Interrupts on */
                                                        /* ACKs and NAKs on */
                                                        /* IN Endpoint */
#define ISP1582_INT_CONF_REG_DDBGMODIN_ACK_ONLY    0x01 /* Interrupts on only */
                                                        /* ACKS on IN Endpoint*/

#define ISP1582_INT_CONF_REG_DDBGMODIN_ACK_FST_NAK 0x02 /* Interrupts on all */
                                                        /* ACKS and first NAK */
                                                        /* on IN endpoint */
#define ISP1582_INT_CONF_REG_DDBGMODIN_SHIFT(b)    ((b)<<4) /* Shift Value */

/* Data Debug Mode Out */
#define ISP1582_INT_CONF_REG_DDBGMODOUT_MASK       0x0C /* Data Debug Mode OUT*/
                                                        /* Mask Value */
#define ISP1582_INT_CONF_REG_DDBGMODOUT_ACK_NAK_NYET  0x00 /* Interrupts on */
                                                           /* ACKs, NYETs and */
                                                           /* NAKs on OUT */
                                                           /* Endpoint */
#define ISP1582_INT_CONF_REG_DDBGMODOUT_ACK_NYET  0x01  /* Interrupts on only */
                                                        /* ACKS & NYETs on */
                                                        /* OUT Endpoint */

#define ISP1582_INT_CONF_REG_DDBGMODOUT_ACK__NYET_FST_NAK  0x02 /* Interrupts */
                                                                /* on ACKS, */
                                                                /* NYETs &  */
                                                                /* first NAK */

#define ISP1582_INT_CONF_REG_DDBGMODOUT_SHIFT(b)  ((b)<<2) /* Shift Value */

/* Interrupt Level Bit */
#define ISP1582_INT_CONF_REG_INTLVL_PULSED      0x02   /* Pulsed Mode */

/* Interrupt Polarity Bit */
#define ISP1582_INT_CONF_REG_INTPOL_HIGH       0x01    /* Polarity */


/* Interrupt Enable Register (read/write 4 bytes) */

#define ISP1582_INT_ENABLE_REG_MASK       0x03FFFFFF /* Mask Value */
#define ISP1582_INT_ENABLE_REG_IEBRST     0x0001  /* Bus Reset */
#define ISP1582_INT_ENABLE_REG_IESOF      0x0002  /* Start of Frame */
#define ISP1582_INT_ENABLE_REG_IEPSOF     0x0004  /* Pseudo Start of Frame */
#define ISP1582_INT_ENABLE_REG_IESUSP     0x0008  /* Suspend */
#define ISP1582_INT_ENABLE_REG_IERESM     0x0010  /* Resume */
#define ISP1582_INT_ENABLE_REG_IEHS_STA   0x0020  /* High Speed Detection */
#define ISP1582_INT_ENABLE_REG_IEDMA      0x0040  /* DMA */
#define ISP1582_INT_ENABLE_REG_IEVBUS     0x0080  /* V-Bus Detection */
#define ISP1582_INT_ENABLE_REG_IEP0SETUP  0x0100  /* Setup Buffer on Endpt 0 */

/* To enable the endpoints for interrupts. The value of "b" should be one of
 * endpoint Index.
 */
#define ISP1582_INT_ENABLE_REG_ENDPT_SFT_VAL 0xA   /* Shift Value */
#define ISP1582_INT_ENABLE_REG_ENDPT_SET(b) (1 << ((b) + \
                                          ISP1582_INT_ENABLE_REG_ENDPT_SFT_VAL))

/* Endpoint Index Register (read/write 1 byte) */

#define ISP1582_ENDPT_INDEX_REG_MASK       0x3F   /* Index Register Mask */
#define ISP1582_ENDPT_INDEX_REG_EP0SETUP   0x20   /* Setup Buffer */
#define ISP1582_ENDPT_INDEX_REG_DIR_MASK   0x01   /* Direction Mask */

/* Control Function Register (read/write 1 byte)
 * This register is an indexed register. Prior to accessing this register
 * the endpoint index register must always be set.
 */

#define ISP1582_CNTL_FUNC_REG_MASK     0x1F /* Control Function Reg Mask */
#define ISP1582_CNTL_FUNC_REG_STALL    0x01 /* Stall the indexed endpoint */
#define ISP1582_CNTL_FUNC_REG_STATUS   0x02 /* Status of Indexed Endpoint */
#define ISP1582_CNTL_FUNC_REG_DSEN     0x04 /* Data Stage Enable */
#define ISP1582_CNTL_FUNC_REG_VENDP    0x08 /* Validate Indexed Endpoint */
#define ISP1582_CNTL_FUNC_REG_CLBUF    0x10 /* Clear Indexed Endpoint */

/* Buffer Status Register (read 1 byte) */

#define ISP1582_BUF_STATUS_REG_MASK        0x03  /* Buffer Status Reg. Mask */
#define ISP1582_BUF_STATUS_REG_BOTH_EMPT   0x00  /* Both buffers are empty */
#define ISP1582_BUF_STATUS_REG_ONE_FILL    0x01 /*One of the buffers is filled*/
#define ISP1582_BUF_STATUS_REG_TWO_FILL    0x02 /*One of the buffers is filled*/
#define ISP1582_BUF_STATUS_REG_BOTH_FILLED 0x03 /* Both buffers are filled */

/* Endpoint Max Packet Size Register (read/write 2 bytes) */

#define ISP1582_ENDPT_MAXPSIZE_REG_MASK    0x1FFF /* Max. Packet Size Reg Mask */
#define ISP1582_ENDPT_MAXPSIZE_REG_MAXP_MASK 0x07FF /* Packet Size Mask */
#define ISP1582_ENDPT_MAXPSIZE_REG_NTRANS_MASK 0x1800 /* NTRANS Mask Value */

/* Definitions for number of transactions per frame */
#define ISP1582_NTRANS_1       0x0  /* 1 packet per microframe */
#define ISP1582_NTRANS_2       0x1  /* 2 packets per microframe */
#define ISP1582_NTRANS_3       0x2  /* 3 packet per microframe */

/* Definitions for Max Packet Size */

#define ISP1582_MAXPSIZE_8	    0x0008   /* Max Packet Size - 8 */
#define ISP1582_MAXPSIZE_16	    0x0010   /* Max Packet Size - 16 */
#define ISP1582_MAXPSIZE_32	    0x0020   /* Max Packet Size - 32 */
#define ISP1582_MAXPSIZE_64	    0x0040   /* Max Packet Size - 64 */
#define ISP1582_MAXPSIZE_128	0x0080   /* Max Packet Size - 128 */
#define ISP1582_MAXPSIZE_256	0x0100   /* Max Packet Size - 256 */
#define ISP1582_MAXPSIZE_512	0x0200   /* Max Packet Size - 512 */
#define ISP1582_MAXPSIZE_3024	0x0400   /* Max Packet Size - 3024 */

/* Definition for Setting the number of transaction in  Endpoint Max Packet
 * Size Register.
 */
#define ISP1582_ENDPT_MAXPSIZE_REG_NTRANS_SHIFT_VAL  0xB  /* Shift Value */
#define ISP1582_ENDPT_MAXPSIZE_REG_SHIFT_NTRANS(b) ((b) << \
                                  ISP1582_ENDPT_MAXPSIZE_REG_NTRANS_SHIFT_VAL)

/* Endpoint Type Register (read/write 2 bytes) */

#define ISP1582_ENDPT_TYPE_REG_MASK             0x1F /* Endpt. Type Reg. Mask */
#define ISP1582_ENDPT_TYPE_REG_EPTYPE_NOT_USED  0x00 /* Not used */
#define ISP1582_ENDPT_TYPE_REG_EPTYPE_ISO       0x01 /* Isochronous Type */
#define ISP1582_ENDPT_TYPE_REG_EPTYPE_BULK      0x02 /* Bulk Type */
#define ISP1582_ENDPT_TYPE_REG_EPTYPE_INTP      0x03 /* Interrupt Type */
#define ISP1582_ENDPT_TYPE_REG_DOUBLE_BUF       0x04 /* Double Buffering */
#define ISP1582_ENDPT_TYPE_REG_ENDPT_ENABLE     0x08 /* Endpoint Enable */
#define ISP1582_ENDPT_TYPE_REG_NOEMPKT          0x10 /* No Empty Packet */

/* DMA Command Register (write 1 byte) */

#define ISP1582_DMA_COMMAND_REG_GDMA_READ       0x00 /* GDMA Read */
#define ISP1582_DMA_COMMAND_REG_GDMA_WRITE      0x01 /* GDMA Write */
#define ISP1582_DMA_COMMAND_REG_VAL_BUF         0x0E /* Validate Buffer */
#define ISP1582_DMA_COMMAND_REG_CLR_BUF         0x0F /* Clear Buffer */
#define ISP1582_DMA_COMMAND_REG_DMA_RESET       0x11 /* DMA Reset */
#define ISP1582_DMA_COMMAND_REG_GDMA_STOP       0x13 /* GDMA Stop */

/* DMA Configuration Register (read/write 2 byte) */

#define ISP1582_DMA_CONFIG_REG_WIDTH_8          0x00 /* 8 bit bus width */
#define ISP1582_DMA_CONFIG_REG_WIDTH_16         0x01 /* 16 bit bus width */
#define ISP1582_DMA_CONFIG_REG_MODE_00          0x00 /* Config Mode 0 */
#define ISP1582_DMA_CONFIG_REG_MODE_01          0x01 /* Config Mode 1 */
#define ISP1582_DMA_CONFIG_REG_MODE_10          0x10 /* Config Mode 2 */
#define ISP1582_DMA_CONFIG_REG_MODE_SHIFT_VAL   0x02 /* Config Shift Value */
#define ISP1582_DMA_CONFIG_REG_MODE_SET(b)      ((b) << \
                                      ISP1582_DMA_CONFIG_REG_MODE_SHIFT_VAL)
#define ISP1582_DMA_CONFIG_REG_MODE_DIS_XFER_CNT   0x80 /* DMA Transfer Count */

/* DMA Hardware Register (read/write 1 byte) */

#define ISP1582_DMA_HARDWARE_REG_READ_POL       0x01 /* DIOR is active high */
#define ISP1582_DMA_HARDWARE_REG_WRITE_POL      0x02 /* DIOW is active high */
#define ISP1582_DMA_HARDWARE_REG_DREQ_POL       0x04 /* DREQ is active high */
#define ISP1582_DMA_HARDWARE_REG_ACK_POL        0x08 /* DACK is active high */
#define ISP1582_DMA_HARDWARE_REG_EOT_POL        0x20 /* EOT is acitve high */
#define ISP1582_DMA_HARDWARE_REG_ENDIAN_00      0x00 /* Normal Representaion */
#define ISP1582_DMA_HARDWARE_REG_ENDIAN_01      0x01 /* Swapped Representaion */
#define ISP1582_DMA_HARDWARE_REG_ENDIAN_SHIFT_VAL 0x06 /* Endianess Shift Val */
#define ISP1582_DMA_HARDWARE_REG_READ_ENDIAN_SET(b) ((b) << \
                  ISP1582_DMA_HARDWARE_REG_ENDIAN_SHIFT_VAL) /* Endianess Val */

/* DMA Interrupt Reason Register (read/write 2 bytes) */

#define ISP1582_DMA_INT_RESN_MASK        0x9D00  /* DMA Int. Reason Reg Mask */
#define ISP1582_DMA_INT_RESN_REG_DMA_XFER_OK  0x0100 /* DMA Trans.Counter Int */
#define ISP1582_DMA_INT_RESN_REG_INT_EOT        0x0400 /* Int. EOT Interrupt */
#define ISP1582_DMA_INT_RESN_REG_EXT_EOT        0x0800 /* Ext. EOT Interrupt */
#define ISP1582_DMA_INT_RESN_REG_GDMA_STOP      0x1000 /* GDMA Stop Interrupt */
#define ISP1582_DMA_INT_RESN_REG_TEST3          0x8000 /* Test3 Interrupt */

/* DMA Interrupt Enable Register (read/write 2 bytes ) */

#define ISP1582_DMA_INT_ENBL_REG_IE_DMA_XFER_OK  0x0100 /*DMA Trans.Counter Int*/
#define ISP1582_DMA_INT_ENBL_REG_IE_INT_EOT      0x0400 /* Int. EOT Interrupt */
#define ISP1582_DMA_INT_ENBL_REG_IE_EXT_EOT      0x0800 /* Ext. EOT Interrupt */
#define ISP1582_DMA_INT_ENBL_REG_IE_GDMA_STOP    0x1000 /* GDMA Stop Interrupt*/
#define ISP1582_DMA_INT_ENBL_REG_IE_TEST4        0x8000 /* Test Interrupt */

/* DMA Endpoint Regsiter (read/write 1 byte) */

#define ISP1582_DMA_ENDPOINT_REG_MASK   0x0F   /* DMA Endpoint Mask */

/* Interrupt Register (read/write 4 bytes) */

#define ISP1582_INT_REG_CLEAR       0x03FFFDFF  /* To clear all interrupts */
#define ISP1582_INT_REG_BRST        0x0001  /* Bus Reset */
#define ISP1582_INT_REG_SOF         0x0002  /* Start of Frame */
#define ISP1582_INT_REG_PSOF        0x0004  /* Pseudo Start of Frame */
#define ISP1582_INT_REG_SUSP        0x0008  /* Suspend */
#define ISP1582_INT_REG_RESM        0x0010  /* Resume */
#define ISP1582_INT_REG_HS_STA      0x0020  /* High Speed Detection */
#define ISP1582_INT_REG_DMA         0x0040  /* DMA */
#define ISP1582_INT_REG_VBUS        0x0080  /* V-Bus Detection */
#define ISP1582_INT_REG_EP0SETUP    0x0100  /* Setup Buffer on Endpt 0 */
#define ISP1582_INT_ENDPT_MASK      0x03FFFC00  /* Int. Register Mask */
#define ISP1582_INT_REG_ENDPT_SFT_VAL 0xA   /* Endpoint Shift Value */

#define ISP1582_INT_REG_ENDPT_SET(b) ((b) << ISP1582_INT_REG_ENDPT_SFT_VAL)

/* ISP 1582 signature (read through Read Chip Id command) */

#define ISP1582_CHIP_ID_MASK     0xFFFF00   /* Chip ID Mask */
#define ISP1582_CHIP_ID          0x158200   /* ISP 1582 Chip ID */
#define ISP1582_CHIP_VER         0x000010   /* Version Number */

/* Frame Number Register (read 2 bytes) */
#define ISP1582_FRM_NUM_REG_SOFR_MASK     0x07FF  /* SOF Mask */
#define ISP1582_FRM_NUM_REG_MSOFR_MASK    0x3800 /* MSOF Mask */
#define ISP1582_FRM_NUM_REG_MSOFR_VAL(b)  (((b) & \
              ISP1582_FRM_NUM_REG_MSOFR_MASK) >> 0xB) /* Shift Value */

/* Unlock Device Register (write  2 bytes) */
#define ISP1582_UNLOCK_DEV_REG_CODE       0xAA37 /* Device Unlock Code */

/* Test Mode Register (read/write 1 byte) */

#define ISP1582_TEST_MODE_REG_SE0_ACK     0x01 /* Sets DP & DM to HS State */
#define ISP1582_TEST_MODE_REG_JSTATE      0x02 /* Sets to J-STATE */
#define ISP1582_TEST_MODE_REG_KSTATE      0x04 /* Sets to K-STATE */
#define ISP1582_TEST_MODE_REG_PRBS        0x08 /* Predetermined randon pattern*/
#define ISP1582_TEST_MODE_REG_FORCEFS     0x10 /* Forces to FS mode only */
#define ISP1582_TEST_MODE_REG_FORCEHS     0x80 /* Forces to HS mode only */


#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbIsp1582h */
