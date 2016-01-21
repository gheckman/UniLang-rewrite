/* usbPegasusEnd.h - USB Pegasus End driver header */

/*
 * Copyright (c) 2000-2001, 2003-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01q,01sep10,ghs  Change pegasus default name (WIND00231161)
01p,29apr10,pad  Moved extern C statement after include statements.
01o,13jan10,ghs  vxWorks 6.9 LP64 adapting
01n,27oct06,rec  add D-Link DSB-650 support
01m,10aug05,ami  usbPegasusEndUninit() routine added in declaration
                 usbPegasusDynamicAttachUnregister() added
01l,23Feb04,hch  Updated the PEGASUS_DEVICE structure to eliminate the receive
                 cluster pool memeber for SPR #106581
01k,16jan05,hch  Increased the number of IRPs submitted
01j,23jun04,hch  Add the Pegasus control registers definition
01i,14oct03,nrv  update pegasus_device struct
01h,29aug03,nrv  mods for pegasus2
01g,13dec01,wef  merge from veloce view
01f,01aug01,wef  fixed the #ifndef, was all lowercase
01e,07may01,wef  changed module number to be (module num << 8) | M_usbHostLib
01d,02may01,wef  changed module number to be M_<module> + M_usbHostLib
01c,30apr01,wef  changed USB_DEV USB_PEGASUS_DEV
01b,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes
01a,02may00,bri  Created
*/

#ifndef __INCusbPegasusEndh
#define __INCusbPegasusEndh


/* includes */

#include "endLib.h"
#include "usb/usbEnet.h"
#include "vwModNum.h"           /* USB Module Number Def's */

#ifdef  __cplusplus
extern "C" {
#endif  /* __cplusplus */


/* defines */

/* Error Numbers as set the usbEnetLib  */

/* usbEnetLib error values */

/*
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */

#define USB_PEGASUS_SUB_MODULE      14

#define M_usbPegasusLib         ( (USB_PEGASUS_SUB_MODULE << 8) | M_usbHostLib )

#define usbPegasusErr(x)        (M_usbPegasusLib | (x))

#define S_usbPegasusLib_NOT_INITIALIZED     usbPegasusErr (1)
#define S_usbPegasusLib_BAD_PARAM           usbPegasusErr (2)
#define S_usbPegasusLib_OUT_OF_MEMORY       usbPegasusErr (3)
#define S_usbPegasusLib_OUT_OF_RESOURCES    usbPegasusErr (4)
#define S_usbPegasusLib_GENERAL_FAULT       usbPegasusErr (5)
#define S_usbPegasusLib_QUEUE_FULL          usbPegasusErr (6)
#define S_usbPegasusLib_QUEUE_EMPTY         usbPegasusErr (7)
#define S_usbPegasusLib_NOT_IMPLEMENTED     usbPegasusErr (8)
#define S_usbPegasusLib_USBD_FAULT          usbPegasusErr (9)
#define S_usbPegasusLib_NOT_REGISTERED      usbPegasusErr (10)
#define S_usbPegasusLib_NOT_LOCKED          usbPegasusErr (11)

#define SOHOWARE_VENDOR_ID              0x15e8
#define SOHOWARE_PRODUCT_ID             0x9110

#define DLINK650_VENDOR_ID              0X2001
#define DLINK650_PRODUCT_ID             0Xabc1

#define BELKIN_VENDOR_ID                0x050d
#define BELKIN_PRODUCT_ID               0x0121

/* Pegasus Control Registers definition */

#define PEGASUS_CTL0_INCLUDE_RXCRC  0x01
#define PEGASUS_CTL0_ALLMULTI       0x02
#define PEGASUS_CTL0_STOP_BACKOFF   0x04
#define PEGASUS_CTL0_RXSTAT_APPEND  0x08
#define PEGASUS_CTL0_WAKEON_ENB     0x10
#define PEGASUS_CTL0_RXPAUSE_ENB    0x20
#define PEGASUS_CTL0_RX_ENB         0x40
#define PEGASUS_CTL0_TX_ENB         0x80

#define PEGASUS_CTL1_HOMELAN        0x04
#define PEGASUS_CTL1_RESETMAC       0x08
#define PEGASUS_CTL1_SPEEDSEL       0x10    /* 0 = 10mbps, 1 = 100mbps */
#define PEGASUS_CTL1_DUPLEX         0x20    /* 0 = half, 1 = full */
#define PEGASUS_CTL1_DELAYHOME      0x40

#define PEGASUS_CTL2_EP3_CLR        0x01    /* reading EP3 clrs status regs */
#define PEGASUS_CTL2_RX_BADFRAMES   0x02
#define PEGASUS_CTL2_RX_PROMISC     0x04
#define PEGASUS_CTL2_LOOPBACK       0x08
#define PEGASUS_CTL2_EEPROMWR_ENB   0x10
#define PEGASUS_CTL2_EEPROM_LOAD    0x20

/* Attach codes used by USB_PEGASUS_ATTACH_CALLBACK. */

#define USB_PEGASUS_ATTACH                  0      /* PEGASUS Device attached */
#define USB_PEGASUS_REMOVE                  1      /* PEGASUS Device removed  */

/* Vendor Specific Commands */

#define USB_REQ_PEGASUS_REG_GET             0x00
#define USB_REQ_PEGASUS_SET_REG_SINGLE      0x01
#define USB_REQ_PEGASUS_SET_REG_MULTIPLE    0x02

#define USB_PEGASUS_REG_ENET_CONTL          0x00
#define USB_PEGASUS_REG_MCAST_TABL          0x08
#define USB_PEGASUS_REG_ENET_ADRS           0x10
#define USB_PEGASUS_REG_EEPROM_OFFSET       0x20
#define USB_PEGASUS_REG_EEPROM_DATA         0x21
#define USB_PEGASUS_REG_PHY_ADRS            0x25
#define USB_PEGASUS_REG_PHY_DATA            0x26
#define USB_PEGASUS_REG_PHY_ACC_CNTL        0x28
#define USB_PEGASUS_REG_GPIO_CNTL0          0x7e
#define USB_PEGASUS_REG_GPIO_CNTL1          0x7f

#define USB_PEGASUS_GET_BMREQ               0xc0
#define USB_PEGASUS_GET_BREQ                0xf0
#define USB_PEGASUS_SET_BMREQ               0x40
#define USB_PEGASUS_SET_BREQ                0xf1

#undef  ETHER_MAP_IP_MULTICAST
/* Offsets for reading the Ethernet Functional Descriptor */

#define PEGASUS_OFFSET_MACADRS          3
#define PEGASUS_OFFSET_STAT_BMP         9
#define PEGASUS_OFFSET_SEGMENT_SIZE     13
#define PEGASUS_OFFSET_MCAST            15

#define PEGASUS_M_BLK_NUM               512
#define PEGASUS_CL_NUM                  256

/* Buffer Sizes */

#define PEGASUS_OUT_BFR_SIZE       1550         /* size of output bfr */
#define PEGASUS_IN_BFR_SIZE        1550         /* size of input bfr */
#define PEGASUS_NO_IN_BFRS         40           /* No of Input Buffers */
#define PEGASUS_NO_OUT_IRPS        20           /* No of IRPs submitted */

#define USB_PEGASUS_ATTACH         0            /* CBI_UFI Device attached */
#define USB_PEGASUS_REMOVE         1            /* CBI_UFI Device removed  */

#define PEGASUS_DESCRIPTION         "usb"

/* typedefs */

/*
 * usb Device structure
 * This structure is a priliminary structure and is used in the
 * call back functions for dynamic attachment.
 * Later when the final end_obj structure is created, this structure
 * will be linked to the end_obj structure.
 */

typedef struct usb_pegasus_dev
    {
    LINK devLink;           /* linked list of device structs */
    USBD_NODE_ID nodeId;    /* Node Id of the device */
    UINT16 configuration;   /* configuration of the device */
    UINT16 interface;       /* interface of the device */
    UINT16 vendorId;        /* Pegasus Device Vendor ID */
    UINT16 productId;       /* Pegasus Device Product ID */
    UINT16 lockCount;       /* Count of times structure locked*/
    BOOL   connected;
    VOID  * pPegasusDev;
    }USB_PEGASUS_DEV, *pUsbPegasusListDev;

/*
 * Statistics, to be maintained by the device/driver
 * As on today all the stats are not supported by the driver.
 */

typedef struct pegasus_stats
    {

    UINT32 bitmap;      /* bitmap indicating the supported stats */
                        /* This bitmap will be in the same way as given */
                        /* in the Function descriptor of the device. */
                        /* Corresponding bit will be set if the stat is */
                        /* supported both by the device and the driver */

    UINT32 xmitOk;      /* Frames Transmitted without errors. XMIT_OK */
    UINT32 rvcOk;       /* Frames received without errors. RVC_OK */
    UINT32 xmitErr;     /* Frames not transmitted or transmitted with errors */
    UINT32 rvcErr;      /* Frames recd. with errors that are not delivered */
                        /* to usb Host */
    UINT32 rvcNoBuf;    /* Frames missed, nobuffers */
    UINT32 rvcCrcErr;   /* Frames recd. with CRC or FCS error */
    UINT32 rvcOverRun;  /* Frames not recd. due to over run */

    }PEGASUS_STATS, *pPegasusStats;

/*
 * the multicast filter support details.
 */

typedef struct pegasus_mcast
    {

    UINT8  isMCastPerfect;  /* if TRUE, the device supports perfect */
                            /* multicast address filtering (no hashing) */

    UINT16  noMCastFilters; /* No.of Multicast Address filters Supported */

    }PEGASUS_MCAST_DETAILS, *pPegasusMCastDetails;

/*
 * Irp buffer structure
 */

typedef struct pegasus_enet_irp
    {
    USB_IRP outIrp;         /* IRP to transmit output data */
    BOOL outIrpInUse;       /* TRUE while IRP is outstanding */
    } PEGASUS_ENET_IRP;

/* USB_PEGASUS_ATTACH_CALLBACK defines a callback routine which will be
 * invoked by usbPegasusEnd.c when the attachment or removal of a Pegasus
 * device is detected.  When the callback is invoked with an attach code of
 * USB_PEGASUS_ATTACH, the nodeId represents the ID of newly added device.
 * When the attach code is USB_PEGASUS_REMOVE, nodeId points to the
 * PEGASUS device which is no longer attached.
 */

typedef VOID (*USB_PEGASUS_ATTACH_CALLBACK)
    (
    pVOID arg,                  /* caller-defined argument     */
    USB_PEGASUS_DEV * pDev,     /* the device info             */
    UINT16 attachCode           /* attach or remove code       */
    );

/* Attach request for user callback */

typedef struct attach_request
    {
    LINK reqLink;                           /* linked list of requests */
    USB_PEGASUS_ATTACH_CALLBACK callback;   /* client callback routine */
    pVOID callbackArg;                      /* client callback argument*/
    } ATTACH_REQUEST, *pATTACH_REQUEST;

/*
 * Usb Ethernet END Device structure..
 * This structure is used both by the file usbPegasusEnd.c.
 */

typedef struct pegasus_device
    {
    END_OBJ endObj;                 /* must be first field */

    USB_PEGASUS_DEV * pDev;         /* the device info */

    UINT8 unit;

    USBD_NODE_ID nodeId;            /* Node Id of the device */

    UINT8 communicateOk;            /* TRUE after Starting */
                                    /* and FALSE if stopped */

    UINT8 macAdrs[6];               /* MAC adress */

    CL_POOL_ID pClPoolId;           /* Pointer to the Cluster Pool */

    BOOL connected;                 /* TRUE if device is currently connected */

    USBD_PIPE_HANDLE outPipeHandle; /* USBD pipe handle for bulk OUT pipe */

    PEGASUS_ENET_IRP * pEnetIrp;    /* pointer to details of Irp structure*/

    int noOfIrps;                   /* no of Irps */

    int txIrpIndex;                 /* What the last submitted IRP is */

    UINT8 * outBfr;                 /* pointer to output buffer */
    UINT16 outBfrLen;               /* size of output buffer */
    UINT32 outErrors;               /* count of IRP failures */

    USBD_PIPE_HANDLE inPipeHandle;  /* USBD pipe handle for bulk IN pipe */
    USB_IRP inIrp;                  /* IRP to monitor input from printer */
    BOOL inIrpInUse;                /* TRUE while IRP is outstanding */

    int     noOfInBfrs;             /* no of input buffers*/
    UINT8 **    pOutBfrArray;       /* pointer to output buffers */

    UINT16 inBfrLen;                /* size of input buffer */
    UINT32 inErrors;                /* count of IRP failures */

    PEGASUS_STATS stats;            /* Statistics */
    LINK   pegasusDevLink;          /* Link to other Pegasus devices */
    PEGASUS_MCAST_DETAILS mCastFilters; /* Multicast address filter details */

    UINT16 maxSegmentSize;          /* Max. Segment supported by the device */

    UINT8 maxPower;                 /* Max. Power Consumption of the device */
                                    /* in 2mA units */
    BOOL txStall; /* Indicates we ran out of TX IRP's */
    BOOL txActive;/* Indicates there is a TX IRP in process with the USB Stack */

    } PEGASUS_DEVICE, *pPegasusDevCtrl;

LOCAL UINT16 pegasusAdapterList[][3] = {
                    { SOHOWARE_VENDOR_ID, SOHOWARE_PRODUCT_ID },
                    { DLINK650_VENDOR_ID, DLINK650_PRODUCT_ID },
                    { BELKIN_VENDOR_ID, BELKIN_PRODUCT_ID }
                   };

/* Swap macros */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define USB_PEGASUS_SWAP_32(x)  LONGSWAP((UINT)x)
#define USB_PEGASUS_SWAP_16(x)  ((LSB(x) << 8)|MSB(x))

#else   /* _BYTE_ORDER == _BIG_ENDIAN   */

#define USB_PEGASUS_SWAP_32
#define USB_PEGASUS_SWAP_16

#endif  /* _BYTE_ORDER == _BIG_ENDIAN   */

/* fucntion prototypes */

STATUS usbPegasusDevLock (USBD_NODE_ID nodeId);
STATUS usbPegasusDevUnlock (USBD_NODE_ID nodeId);
STATUS usbPegasusDynamicAttachRegister (USB_PEGASUS_ATTACH_CALLBACK callback,
                                        pVOID arg);
STATUS usbPegasusDynamicAttachUnregister (USB_PEGASUS_ATTACH_CALLBACK callback,
                                          pVOID arg);

STATUS usbPegasusEndInit(void);
STATUS usbPegasusEndUninit (void);

#ifdef  __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __INCusbPegasusEndh */

