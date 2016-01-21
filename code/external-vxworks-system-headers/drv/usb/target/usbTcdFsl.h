/* usbTcdFsl.h - Definitions for FSL TCD */

/*
 * Copyright (c) 2009-2011, 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01f,06jan14,wyy  replace cacheDmaMalloc with memalign (WIND00449889)
01e,09aug13,ljg  Set USB_SBUSCFG to INCR8 for MPC5125 errata workaround 
                 (WIND00405093)
01d,07jan11,ghs  Clean up compile warnings (WIND00247082)
01c,13jan10,ghs  vxWorks 6.9 LP64 adapting
01b,09sep09,w_x  support for various BSP configurations (WIND00180575)
01a,08feb09,w_x  created based on fsl_rdb8313 BSP
*/

/*
DESCRIPTION

Common definitions for the Freescale Dual Role USB controler (device side).
*/

#ifndef __INCusbTcdFslh
#define __INCusbTcdFslh

#ifdef  __cplusplus
extern "C" {
#endif

/* includes */

/* defines */

/* Endpoint Index */

#define FSL_DR_ENDPT_0                  0x0  /* Control Endpoint  */
#define FSL_DR_ENDPT_1                  0x1  /* Endpoint 1 */
#define FSL_DR_ENDPT_2                  0x2  /* Endpoint 2 */
#define FSL_DR_ENDPT_3                  0x3  /* Endpoint 3 */
#define FSL_DR_ENDPT_4                  0x4  /* Endpoint 4 */
#define FSL_DR_ENDPT_5                  0x5  /* Endpoint 5 */

#define FSL_DR_NUM_ENDPOINTS_RX         0x6
#define FSL_DR_NUM_ENDPOINTS_TX         0x6

/* number of endpoints */

/* TODO : make the number of endpoints as config options */

#define FSL_DR_NUM_ENDPOINTS             (FSL_DR_NUM_ENDPOINTS_RX + \
                                              FSL_DR_NUM_ENDPOINTS_TX)

/* I/O registers */

/* USB DR registers */

#define FSL_DR_SBUSCFG                   (0x090)

#define FSL_DR_CAPLENGTH                 (0x100)
#define FSL_DR_HCIVERSION                (0x102)
#define FSL_DR_HCSPARAMS_L               (0x104)
#define FSL_DR_HCSPARAMS_H               (0x108)
#define FSL_DR_DCIVERSION                (0x120)
#define FSL_DR_DCCPARAMS                 (0x124)

#define FSL_DR_USBCMD                    (0x140)
#define FSL_DR_USBSTS                    (0x144)
#define FSL_DR_USBINTR                   (0x148)
#define FSL_DR_FRINDEX                   (0x14c)
#define FSL_DR_DEVICEADDR                (0x154)
#define FSL_DR_ENDPOINTLISTADDR          (0x158)
#define FSL_DR_BURSTSIZE                 (0x160)
#define FSL_DR_TXTTFILLTUNING            (0x164)
#define FSL_DR_CONFIGFLAG                (0x180)
#define FSL_DR_PORTSC1                   (0x184)
#define FSL_DR_OTGSC                     (0x1a4)
#define FSL_DR_USBMODE                   (0x1a8)
#define FSL_DR_ENDPTSETUPSTAT            (0x1ac)
#define FSL_DR_ENDPTPRIME                (0x1b0)
#define FSL_DR_ENDPTFLUSH                (0x1b4)
#define FSL_DR_ENDPTSTATUS               (0x1b8)
#define FSL_DR_ENDPTCOMPLETE             (0x1bc)
#define FSL_DR_ENDPTCTRL(ep)             (0x1c0 + (sizeof(UINT32) * (ep)))
#define FSL_DR_ENDPTCTRL0                (0x1c0)
#define FSL_DR_ENDPTCTRL1                (0x1c4)
#define FSL_DR_ENDPTCTRL2                (0x1c8)
#define FSL_DR_ENDPTCTRL3                (0x1ca)
#define FSL_DR_ENDPTCTRL4                (0x1d0)
#define FSL_DR_ENDPTCTRL5                (0x1d4)

#define FSL_DR_SBUSCFG_INCR8             0x00000002 /* BURSTMODE */
#define FSL_DR_SBUSCFG_BURSTMODE_MASK    0x00000007 /* BURSTMODE MASK */

#define FSL_DR_USBCMD_RS      0x00000001 /* Run/Stop */
#define FSL_DR_USBCMD_RST     0x00000002 /* Controller Reset */
#define FSL_DR_USBCMD_SUTW    0x00002000 /* Setup tripwire */

#define FSL_DR_USBSTS_UI      0x00000001 /* USB interrupt */
#define FSL_DR_USBSTS_UEI     0x00000002 /* USB error interrupt */
#define FSL_DR_USBSTS_PCI     0x00000004 /* port change interrupt */
#define FSL_DR_USBSTS_SEI     0x00000010 /* system error interrupt */
#define FSL_DR_USBSTS_URI     0x00000040 /* USB reset interrupt */
#define FSL_DR_USBSTS_SRI     0x00000080 /* SOF received interrupt */
#define FSL_DR_USBSTS_SLI     0x00000100 /* DCSuspend interrupt */
#define FSL_DR_USBSTS_ULPII   0x00000400 /* ULPI interrupt */

#define FSL_DR_USBINTR_UE     0x00000001 /* USB interrupt enable */
#define FSL_DR_USBINTR_UEE    0x00000002 /* USB error interrupt enable */
#define FSL_DR_USBINTR_PCE    0x00000004 /* port change detect interrupt enable */
#define FSL_DR_USBINTR_SEE    0x00000010 /* system error interrupt enable */
#define FSL_DR_USBINTR_URE    0x00000040 /* USB reset interrupt enable */
#define FSL_DR_USBINTR_SRE    0x00000080 /* SOF receive interrupt enable */
#define FSL_DR_USBINTR_SLE    0x00000100 /* sleep interrupt enable */
#define FSL_DR_USBINTR_ULPIE  0x00000400 /* ULPI interrupt enable */
#define FSL_DR_USBINTR_IRQS      (FSL_DR_USBINTR_UE  |  \
                                  FSL_DR_USBINTR_UEE |  \
                                  FSL_DR_USBINTR_PCE |  \
                                  FSL_DR_USBINTR_SEE |  \
                                  FSL_DR_USBINTR_URE |  \
                                  FSL_DR_USBINTR_SLE    \
                                  )

#define FSL_DR_FRINDEX_MASK              0x00003fff /* FRINDEX mask */

#define FSL_DR_DEVICEADDR_USBADR_SHIFT   25         /* Device address starts at bit 25 */

#define FSL_DR_PORTSC1_PTS_MASK          0xc0000000 /* Port tranceiver select */
#define FSL_DR_PORTSC1_PTS_UTMI          0x00000000 /* Port tranceiver select - UTMI */
#define FSL_DR_PORTSC1_PTS_RESERVED      0x40000000 /* Port tranceiver select - reserved */
#define FSL_DR_PORTSC1_PTS_ULPI          0x80000000 /* Port tranceiver select - ULPI */
#define FSL_DR_PORTSC1_PTS_SERIAL        0xc0000000 /* Port tranceiver select - FS/LS serial */
#define FSL_DR_PORTSC1_PTW_MASK          0x10000000 /* Parallel Transceiver Width */
#define FSL_DR_PORTSC1_PTW_16BIT         0x10000000 /* 16 BIT */
#define FSL_DR_PORTSC1_PTW_8BIT          0x00000000 /* 8 BIT */
#define FSL_DR_PORTSC1_PSPD_MASK         0x0c000000 /* Port speed */
#define FSL_DR_PORTSC1_PSPD_FS           0x00000000 /* Port speed - full speed */
#define FSL_DR_PORTSC1_PSPD_LS           0x04000000 /* Port speed - low speed */
#define FSL_DR_PORTSC1_PSPD_HS           0x08000000 /* Port speed - high speed */
#define FSL_DR_PORTSC1_PTC_MASK          0x000f0000 /* Port test control - mask */
#define FSL_DR_PORTSC1_PTC_DISABLED      0x00000000 /* Port test control - disable */
#define FSL_DR_PORTSC1_PTC_J_STATE       0x00010000 /* Port test control - J_STATE */
#define FSL_DR_PORTSC1_PTC_K_STATE       0x00020000 /* Port test control - K_STATE */
#define FSL_DR_PORTSC1_PTC_SEQ_NAK       0x00030000 /* Port test control - SEQ_NAK */
#define FSL_DR_PORTSC1_PTC_PACKET        0x00040000 /* Port test control - PACKET  */
#define FSL_DR_PORTSC1_PTC_FORCE_ENABLE  0x00050000 /* Port test control - FORCE_ENABLE */
#define FSL_DR_PORTSC1_PR                0x00000100 /* Port reset */
#define FSL_DR_PORTSC1_FPR               0x00000040 /* Force port resume */
#define FSL_DR_PORTSC1_SUSP              0x00000080 /* Port in suspend */

#define FSL_DR_OTGSC_VC                  0x00000002 /* VBUS charge */

#define FSL_DR_USBMODE_CM_IDLE           0x00000000 /* Controller mode - idle */
#define FSL_DR_USBMODE_CM_RESERVED       0x00000001 /* Controller mode - reserved */
#define FSL_DR_USBMODE_CM_DEVICE         0x00000002 /* Controller mode - device controller */
#define FSL_DR_USBMODE_CM_HOST           0x00000003 /* Controller mode - host controller */
#define FSL_DR_USBMODE_CM_SLOM           0x00000008 /* Setup lockout mode */
#define FSL_DR_USBMODE_CM_ES             0x00000004 /* Endian Select */
#define FSL_DR_USBMODE_CM_MASK           0x0000000F /* Mask value */


#define FSL_DR_ENDPTPRIME_TX_SHIFT       16         /* TX bit position */

#define FSL_DR_ENDPTFLUSH_TX_SHIFT       16         /* TX bit position */

#define FSL_DR_ENDPTCOMPLETE_ERCE_MASK   0x0000003f /* endpoint receive complete event */
#define FSL_DR_ENDPTCOMPLETE_ETCE_MASK   0x003f0000 /* endpoint transmit complete event */
#define FSL_DR_ENDPTCOMPLETE_TX_SHIFT    16         /* TX bit position */

#define FSL_DR_ENDPTCTRL_RXS             0x00000001 /* RX endpoint stall */
#define FSL_DR_ENDPTCTRL_RXD             0x00000002 /* RX endpoint data sink */
#define FSL_DR_ENDPTCTRL_RXT_MASK        0x0000000c /* RX endpoint type */
#define FSL_DR_ENDPTCTRL_RXT_CTRL        0x00000000 /* RX endpoint type - control */
#define FSL_DR_ENDPTCTRL_RXT_ISOCH       0x00000004 /* RX endpoint type - isochronous */
#define FSL_DR_ENDPTCTRL_RXT_BULK        0x00000008 /* RX endpoint type - bulk */
#define FSL_DR_ENDPTCTRL_RXT_INT         0x0000000c /* RX endpoint type - interrupt */
#define FSL_DR_ENDPTCTRL_RXI             0x00000020 /* RX data toggle inhibit */
#define FSL_DR_ENDPTCTRL_RXR             0x00000040 /* RX data toggle reset */
#define FSL_DR_ENDPTCTRL_RXE             0x00000080 /* RX endpoint enable */
#define FSL_DR_ENDPTCTRL_RX_MASK         0x000000ff /* RX mask */
#define FSL_DR_ENDPTCTRL_TXS             0x00010000 /* TX endpoint stall */
#define FSL_DR_ENDPTCTRL_TXD             0x00020000 /* TX endpoint data sink */
#define FSL_DR_ENDPTCTRL_TXT_MASK        0x000c0000 /* TX endpoint type */
#define FSL_DR_ENDPTCTRL_TXT_CTRL        0x00000000 /* TX endpoint type - control */
#define FSL_DR_ENDPTCTRL_TXT_ISOCH       0x00040000 /* TX endpoint type - isochronous */
#define FSL_DR_ENDPTCTRL_TXT_BULK        0x00080000 /* TX endpoint type - bulk */
#define FSL_DR_ENDPTCTRL_TXT_INT         0x000c0000 /* TX endpoint type - interrupt */
#define FSL_DR_ENDPTCTRL_TXI             0x00200000 /* TX data toggle inhibit */
#define FSL_DR_ENDPTCTRL_TXR             0x00400000 /* TX data toggle reset */
#define FSL_DR_ENDPTCTRL_TXE             0x00800000 /* TX endpoint enable */
#define FSL_DR_ENDPTCTRL_TX_MASK         0x00ff0000 /* TX mask */
#define FSL_DR_ENDPTCTRL_TX_SHIFT        16         /* TX bit position */

/* These are big-endian */

#define FSL_DR_SNOOP1                   (0x400)
#define FSL_DR_SNOOP2                   (0x404)
#define FSL_DR_AGE_CNT_THRESH           (0x408)
#define FSL_DR_PRI_CTRL                 (0x40c)
#define FSL_DR_SI_CTRL                  (0x410)
#define FSL_DR_CONTROL                  (0x500)

#define FSL_DR_SNOOP_ADDRESS_MASK     0xfffff000
#define FSL_DR_SNOOP_DISABLE          0x00000000
#define FSL_DR_SNOOP_4KB              0x0000000b
#define FSL_DR_SNOOP_8KB              0x0000000c
#define FSL_DR_SNOOP_16KB             0x0000000d
#define FSL_DR_SNOOP_32KB             0x0000000e
#define FSL_DR_SNOOP_64KB             0x0000000f
#define FSL_DR_SNOOP_128KB            0x00000010
#define FSL_DR_SNOOP_256KB            0x00000011
#define FSL_DR_SNOOP_512KB            0x00000012
#define FSL_DR_SNOOP_1MB              0x00000013
#define FSL_DR_SNOOP_2MB              0x00000014
#define FSL_DR_SNOOP_4MB              0x00000015
#define FSL_DR_SNOOP_8MB              0x00000016
#define FSL_DR_SNOOP_16MB             0x00000017
#define FSL_DR_SNOOP_32MB             0x00000018
#define FSL_DR_SNOOP_64MB             0x00000019
#define FSL_DR_SNOOP_31MB             0x0000001a
#define FSL_DR_SNOOP_256MB            0x0000001b
#define FSL_DR_SNOOP_512MB            0x0000001c
#define FSL_DR_SNOOP_1GB              0x0000001d
#define FSL_DR_SNOOP_2GB              0x0000001e

#define FSL_DR_CONTROL_USB_EN         0x00000004 /* Enable USB interface */

/* Endpoint queue head - capabilities and characteristics */

#define FSL_DR_DQH_MULT_MASK             0xc0000000 /* mult */
#define FSL_DR_DQH_MULT_0                0x00000000 /* mult 0 */
#define FSL_DR_DQH_MULT_1                0x40000000 /* mult 1 */
#define FSL_DR_DQH_MULT_2                0x80000000 /* mult 2 */
#define FSL_DR_DQH_MULT_3                0xc0000000 /* mult 3 */
#define FSL_DR_DQH_MULT_SHIFT            30         /* mult bit position */
#define FSL_DR_DQH_ZLT_MASK              0x20000000 /* zero length termination select */
#define FSL_DR_DQH_ZLT_ENABLE            0x00000000 /* zero length termination select */
#define FSL_DR_DQH_ZLT_DISABLE           0x20000000 /* zero length termination select */
#define FSL_DR_DQH_MAXPACKETLENGTH_MASK  0x07ff0000 /* maximum packet length */
#define FSL_DR_DQH_MAXPACKETLENGTH_SHIFT 16         /* maximum packet length */
#define FSL_DR_DQH_IOS_MASK              0x00008000 /* interrupt on setup */
#define FSL_DR_DQH_IOS_ENABLE            0x00008000 /* interrupt on setup */
#define FSL_DR_DQH_IOS_DISABLE           0x00000000 /* interrupt on setup */

#define FSL_DR_DTD_TERMINATE             0x00000001 /* terminate */
#define FSL_DR_DTD_STATUS_MASK           0x000000ff /* status */
#define FSL_DR_DTD_STATUS_TRANS_ERROR    0x00000008 /* status - transaction error */
#define FSL_DR_DTD_STATUS_BUFFER_ERROR   0x00000020 /* status - data buffer error */
#define FSL_DR_DTD_STATUS_HALTED         0x00000040 /* status - halted */
#define FSL_DR_DTD_STATUS_ACTIVE         0x00000080 /* status - active */
#define FSL_DR_DTD_IOC                   0x00008000 /* interrupt on complete */
#define FSL_DR_DTD_TOTALBYTES_MASK       0x3fff0000 /* total bytes bit position */
#define FSL_DR_DTD_TOTALBYTES_SHIFT      16         /* total bytes bit position */

/* Definitions for Max Packet Size */

#define FSL_DR_MAXPSIZE_8                0x0008   /* Max Packet Size - 8 */
#define FSL_DR_MAXPSIZE_16               0x0010   /* Max Packet Size - 16 */
#define FSL_DR_MAXPSIZE_32               0x0020   /* Max Packet Size - 32 */
#define FSL_DR_MAXPSIZE_64               0x0040   /* Max Packet Size - 64 */
#define FSL_DR_MAXPSIZE_128              0x0080   /* Max Packet Size - 128 */
#define FSL_DR_MAXPSIZE_256              0x0100   /* Max Packet Size - 256 */
#define FSL_DR_MAXPSIZE_512              0x0200   /* Max Packet Size - 512 */
#define FSL_DR_MAXPSIZE_3024             0x0400   /* Max Packet Size - 3024 */

#define FSL_DR_MAXPSIZE_ENDPT_0          FSL_DR_MAXPSIZE_64

/* Alignment */

#define FSL_DR_DQH_MEM_ALIGN             0x1000
#define FSL_DR_DTD_MEM_ALIGN             0x20
#define FSL_DR_DTD_BUFFER_MEM_ALIGN      0x1000

#define FSL_DR_DTD_BUFFERS               5
#define FSL_DR_DTD_BUFFER_SIZE           0x1000
#define FSL_DR_DTD_MAX_XFER_SIZE         0x4000
#define FSL_DR_DTD_SETUP_BUFFERS         2

/* DMA */
#ifdef FSL_DR_DMA_SUPPORTED
#define FSL_DMA_IRQ                      INUM_DMA
#define FSL_MSG_IRQ                      INUM_MU
#define FSL_DR_DMA_CHANNELS              4
#endif /* FSL_DR_DMA_SUPPORTED */

/* Device Endpoint Queue Head (dQH) */

typedef struct usbFslDrDqh
    {
    UINT32      maxPacketLength;
    UINT32      currDtdPointer;
    UINT32      nextDtdPointer;
    UINT32      totalbytesStatus;
    UINT32      bufferPointer[FSL_DR_DTD_BUFFERS];
    UINT32      reserved;
    UINT32      setupBufferBytes[FSL_DR_DTD_SETUP_BUFFERS];
    UINT32      align[4];              /* Padded for 64 byte alignment */
    } USB_FSL_DR_DQH, *pUSB_FSL_DR_DQH;

/* Endpoint Transfer Descriptor (dTD) */

typedef struct usbFslDrDtd
    {
    UINT32      nextLinkPointer;
    UINT32      totalbytesStatus;
    UINT32      bufferPointer[FSL_DR_DTD_BUFFERS];
    } USB_FSL_DR_DTD, *pUSB_FSL_DR_DTD;

/* Endpoint buffer */

typedef UINT8 USB_FSL_DR_BUFFER[FSL_DR_DTD_BUFFERS *
                                         FSL_DR_DTD_BUFFER_SIZE];
typedef USB_FSL_DR_BUFFER *pUSB_FSL_DR_BUFFER;

#define USB_FSL_DEBUG_ERR        0x01   /* For Error Log Messages */
#define USB_FSL_DEBUG_DBG        0x02   /* For normal Log Messages */
#define USB_FSL_DEBUG_VDBG       0x03   /* For verbose Log Messages */

extern UINT32 usbFslDebug;       /* Define the debugging flag */
extern void usbPeriLogMsg (char *,long,long,long,long,long,long);

#define USB_FSL_VDBG                            \
        if (usbFslDebug >= USB_FSL_DEBUG_VDBG)  \
            usbPeriLogMsg            /* debugging Macros */

#define USB_FSL_DBG                             \
        if (usbFslDebug >= USB_FSL_DEBUG_DBG)   \
            usbPeriLogMsg            /* debugging Macros */

#define USB_FSL_ERR                             \
        if (usbFslDebug >= USB_FSL_DEBUG_ERR)   \
            usbPeriLogMsg            /* error macros */


/* #define FSL_POLLING */

/* Interrupt status masks */
/* These are additions to the values in usbTcd.h.  These values should not */
/* clash with existing values                                              */

#define USBTCD_UEI_INTERRUPT_MASK    0x00000100 /* USB error interrupt */
#define USBTCD_PCI_INTERRUPT_MASK    0x00000200 /* port change interrupt */
#define USBTCD_SEI_INTERRUPT_MASK    0x00000400 /* system error interrupt */
#define USBTCD_SRI_INTERRUPT_MASK    0x00000800 /* SOF received interrupt */
#define USBTCD_ULPII_INTERRUPT_MASK  0x00001000 /* ULPI interrupt */
#define USBTCD_URI_INTERRUPT_MASK    0x00002000 /* USB reset interrupt */

/* Bitmap for IN and OUT Endpoints Supported */

#define USB_FSL_TCD_OUT_ENDPOINT 0x0000003F /* bitmap for Out endpoint */
#define USB_FSL_TCD_IN_ENDPOINT  0x003F0000 /* bitmap for In endpoint */

#define USB_FSL_TCD_BUS_SPEED_WAIT      10

#define USB_FSL_TCD_DMA_TIMEOUT         50  /* in milliseconds */

/* define platform type */

#define USB_FSL_DR_DEVICE_PLATFORM_MPC5125     0x5125

/* typedefs */

typedef struct usbTcdFslTarget /* USB_TCD_FSL_TARGET */
    {
    UINT32      ioBase;               /* IO Base */
    UINT16      usbIrq;               /* USB IRQ Number */
    PART_ID     usbMemPartId;         /* USB memory partition */
    pUSB_FSL_DR_DQH pDqh;             /* Device endpoint queue head */
    pUSB_FSL_DR_DTD pDtd[FSL_DR_NUM_ENDPOINTS];    /* Endpoint Transfer Descriptor (dTD) */
    pUSB_FSL_DR_BUFFER pBuffer[FSL_DR_NUM_ENDPOINTS];
    pUSB_FSL_DR_DQH pDqhNonAlign;             /* pDqh address without aligned */
    pUSB_FSL_DR_DTD pDtdNonAlign[FSL_DR_NUM_ENDPOINTS];    /* pDtd address without aligned*/
    pUSB_FSL_DR_BUFFER pBufferNonAlign[FSL_DR_NUM_ENDPOINTS]; /* pBuffer address without aligned */
    USB_HAL_ISR_CALLBACK usbHalIsr;   /* HAL ISR Callback */
    pVOID       usbHalIsrParam;       /* HAL ISR Parameter */
    UINT8       deviceAddress;        /* Device Address */
    UINT16      endpointINIndexInUse; /* Endpoint Index being used */
    UINT16      endpointOUTIndexInUse;/* Endpoint Index being used */
    UINT16      endptINIntPending;    /* Bitmap showing Pending Endpoint Int */
    UINT16      endptOUTIntPending;   /* Bitmap showing Pending Endpoint Int */
    BOOL        setupIntPending;      /* Setup Interrupt occured */
    BOOL        controlOUTStatusPending;/* Control OUT Status Pending Report */
    BOOL        controlOUTStatusSetup; /* Control OUT Status was setup */
    BOOL        controlZlpAck;
    UINT16      maxPacketLength[FSL_DR_NUM_ENDPOINTS];
    UINT32      endpointXferLength[FSL_DR_NUM_ENDPOINTS];
    UINT32      endpointMaxXferLength[FSL_DR_NUM_ENDPOINTS];
    UINT32      usbIntr;
    BOOL        dcSuspend;
    UINT8       setupBuffer[8];
    BOOL        waitForAddrAck;       /*
                                       * Flag to track when we are waiting
                                       * for the Status ACK from
                                       * a Address Set Setup packet
                                       */
    UINT32      addrToSet;            /* Address we want to set */
    BOOL        busReset;             /* bus reset occurred */
    BOOL        forceUIInt;
    MUTEX_HANDLE tcdMutex;
    BOOL        wakeupEnable;

    BOOL        hasSysConfig;
    BOOL        hasBigEndianReg;
    BOOL        hasBigEndianDesc;
    BOOL        hasBigEndianSetup;
    BOOL        hasBufferES;
    UINT32      phyMode;
    UINT32      platformType;
    FUNCPTR     hwInitRoutine;

    UINT8       uSpeed;

#ifdef FSL_DR_DMA_SUPPORTED
    UINT32      endptDmaChanId[FSL_DR_NUM_ENDPOINTS];     /* DMA channel id */
    BOOL        endptDmaChanIdValid[FSL_DR_NUM_ENDPOINTS];/* DMA channel id valid */
    UINT16      dmaIrq;                           /* DMA IRQ channel */
    UINT16      msgIrq;                           /* Message/Doorbell IRQ */
    MPC834XDMA_CHAN *dmaChan[FSL_DR_DMA_CHANNELS];/* DMA channel */
    BOOL        dmaInUse[FSL_DR_DMA_CHANNELS];    /* DMA in use or not */
    SEM_ID      dmaSem[FSL_DR_DMA_CHANNELS];      /* DMA Semaphore */
#endif /* FSL_DR_DMA_SUPPORTED */

#ifdef FSL_POLLING
    THREAD_HANDLE       threadId;     /* Polling Mode Thread Handle */
#endif /* FSL_POLLING */
    } USB_TCD_FSL_TARGET, *pUSB_TCD_FSL_TARGET;

typedef struct usbTcdFslEndpointType /* USB_TCD_FSL_ENDPOINT */
    {
    UINT8       endpointIndex;         /* Endpoint Index */
    UINT16      transferType;          /* Endpoint Transfer Type */
    UINT8       direction;             /* Direction */
    UINT16      maxPacketSize;         /* Max Packet Size */
    } USB_TCD_FSL_ENDPOINT_TYPE, *pUSB_TCD_FSL_ENDPOINT_TYPE;

/* function declaration */

extern void usbTcdFslWriteRegLong
    (
    pUSB_TCD_FSL_TARGET     pTarget,
    void *                  addr,
    UINT32                  val
    );

extern UINT32 usbTcdFslReadRegLong
    (
    pUSB_TCD_FSL_TARGET     pTarget,
    void *                  addr
    );

extern void usbTcdFslWriteDescLong
    (
    pUSB_TCD_FSL_TARGET     pTarget,
    void *                  addr,
    UINT32                  val
    );

extern UINT32 usbTcdFslReadDescLong
    (
    pUSB_TCD_FSL_TARGET     pTarget,
    void *                  addr
    );

#define SYS_IN_LONG(port)                           \
    ((UINT32)(*(volatile UINT32 *)(port)))
#define SYS_OUT_LONG(port, data)                    \
    ((*(UINT32 *)(port) = (UINT32)(data)))

/* Keep pTarget as parameter to allow latter expansion */
/* */
#define USB_FSL_WRITE_REG32(pTarget, reg, val)      \
    usbTcdFslWriteRegLong(pTarget, (void *)(ULONG)((pTarget)->ioBase + (reg)), (val))

#define USB_FSL_READ_REG32(pTarget, reg)            \
    usbTcdFslReadRegLong(pTarget, (void *)(ULONG)((pTarget)->ioBase + (reg)))

#define USB_FSL_WRITE_DESC32(pTarget, desc, val)    \
    usbTcdFslWriteDescLong(pTarget, &(desc), (val))

#define USB_FSL_READ_DESC32(pTarget, desc)          \
    usbTcdFslReadDescLong(pTarget, &(desc))

#define USB_FSL_WRITE_BE_REG32(pTarget, reg, val)   \
    SYS_OUT_LONG((ULONG)(pTarget)->ioBase + (reg), (val))

#define USB_FSL_READ_BE_REG32(pTarget, reg)         \
    SYS_IN_LONG((ULONG)(pTarget)->ioBase + (reg))

extern VOID usbTcdFslUsbIsr(pVOID param);

#ifdef FSL_DR_DMA_SUPPORTED
extern VOID usbTcdFslDmaIsr(MPC834XDMA_CHAN *pChan, UINT32 user_data);
#endif /* FSL_DR_DMA_SUPPORTED */

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbTcdFslh */

