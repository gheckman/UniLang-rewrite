/* usbBulkDevLib.h - USB Bulk only Mass Storage class header file */

/*
 * Copyright (c) 2000-2001,2003-2006, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01y,30jul10,m_y  Add usbBulkDevDestroyByNode declaration to remove compile
                 warning
01x,29apr10,pad  Moved extern C statement after include statements.
01w,13jan10,ghs  vxWorks 6.9 LP64 adapting
01v,24nov08,w_x  Changed USB_SCSI_REQ_SENSE_LEN from 0x0E to 0x12 for popular OS
                 compatibility;
01u,04sep08,w_x  Added mutex to sync up eject and device removal (WIND00131719)
01t,29aug08,w_x  Added flag to stop further IO when unmounting device (WIND00131719)
01s,09feb06,ami  New structure member added (SPR #109616)
01r,13dec05,ami  This allocation length for MODE_SENSE request increased to
                 0xFF (SPR #109512 Fix)
01q,12oct05,hch  Add usbBulkStatusCheckBypassSet function definition
01p,21sep05,hch  Update USB_BULK_DEV_XBD_LUN structure for XBD instantiation
                 and zero size disk support
01o,01aug05,hch  move *Ioctl() and *StatusChk() functions to usbBulkDevLibP.h
01n,13jun05,hch  Change for USB bulk driver XBD implementation
                 add geometry and format params macro
                 make usbBulkDevIoctl and usbBulkDevStatusChk external
01m,14mar05,ami  SPR #106153 (Introduction of macro for mode sense header
                 length)
01l,07dec04,hch  Fixed SPR #93797
01k,05dec04,hch  Merge fix for SPR #94946 from Alexandre Dietsch.
01j,04aug04,hch  added WRS_PACK_ALIGN(1) for usbBulkCbw and usbBulkCsw
01i,02apr04,cfc  Merge bulkResetEnable()
01h,07nov03,mdg  Added support for multiple LUN's and card insertion
                 removal and show routines.
01g,07may01,wef  changed module number to be (module num << 8) | M_usbHostLib
01f,02may01,wef  changed module number to be M_<module> + M_usbHostLib
01e,30mar01,wef  added READ10/WRITE10 command
01d,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes, removed command status codes that lived
                 here and in usbCbiUfiDevLib.h and put into own file in
                 h/usb/usbMassStorage.h
01c,02sep00,bri  added support for multiple devices.
01b,04aug00,bri  updated as per review.
01a,22may00,bri  created.
*/

#ifndef __INCusbBulkDevLibh
#define __INCusbBulkDevLibh


#ifndef _ASMLANGUAGE

/* includes */

#include <vwModNum.h>               /* USB Module Number Def's */
#include <usb/usbMassStorage.h>     /* Command Status codes */
#include <drv/xbd/xbd.h>            /* XBD library header */
#include <drv/erf/erfLib.h>         /* event frame work library header */

#ifdef __cplusplus
extern "C" {
#endif

/* Module number and error code definitions */

/*
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */

#define USB_BULK_SUB_MODULE  11

#define M_usbBulkLib 	( (USB_BULK_SUB_MODULE  << 8) | M_usbHostLib )

#define usbBulkErr(x)   (M_usbBulkLib | (x))

#define S_usbBulkDevLib_NOT_INITIALIZED     usbBulkErr (1)
#define S_usbBulkDevLib_BAD_PARAM           usbBulkErr (2)
#define S_usbBulkDevLib_OUT_OF_MEMORY       usbBulkErr (3)
#define S_usbBulkDevLib_OUT_OF_RESOURCES    usbBulkErr (4)
#define S_usbBulkDevLib_GENERAL_FAULT       usbBulkErr (5)
#define S_usbBulkDevLib_QUEUE_FULL          usbBulkErr (6)
#define S_usbBulkDevLib_QUEUE_EMPTY         usbBulkErr (7)
#define S_usbBulkDevLib_NOT_IMPLEMENTED     usbBulkErr (8)
#define S_usbBulkDevLib_USBD_FAULT          usbBulkErr (9)
#define S_usbBulkDevLib_NOT_REGISTERED      usbBulkErr (10)
#define S_usbBulkDevLib_NOT_LOCKED          usbBulkErr (11)

#define USB_CLASS_MASS_STORAGE           0x08 /* USB Mass storage class code */
#define USB_SUBCLASS_SCSI_COMMAND_SET    0x06 /* SCSI command set definition */
#define USB_INTERFACE_PROTOCOL_BULK_ONLY 0x50 /* BULK only interface protocol*/
#define USB_SUBCLASS_SFF8070I            0x05 /* USB SFF8070I subclass       */

/*
 * usbBulkDevIoctl function codes - chosen outside existing IO control
 * codes supported by file systems
 */

#define USB_BULK_DESCRIPTOR_GET          0xF0 /* Shows all descriptors  */
#define USB_BULK_DEV_RESET               0xF1 /* Class-specific reset   */
#define USB_BULK_MAX_LUN                 0xF2 /* Max. LUN on the device */
#define USB_BULK_EJECT_MEDIA             0xF3 /* Eject media command    */

/* Bulk only protocol constants */

#define USB_CBW_SIGNATURE                0x43425355   /* Command block ID  */
#define USB_CBW_TAG                      0xA5A5A5A5   /* Command block Tag */
#define USB_CSW_SIGNATURE                0x53425355   /* Status block ID   */

#define USB_CBW_DIR_NONE                 0x00 /* No direction => no data xfer */
#define USB_CBW_DIR_OUT                  0x00 /* Direction OUT - to device    */
#define USB_CBW_DIR_IN                   0x80 /* Direction IN  - from device  */
#define USB_CBW_LUN_MASK                 0x0F /* Mask for LUN field in CBW    */
#define USB_CBW_CBLEN_MASK               0x1F /* Mask for Command length field*/
#define USB_CBW_LENGTH                   0x1F /* Length of CBW                */
#define USB_CBW_MAX_CBLEN                0x10 /* Max. length of command block */
#define USB_CSW_LENGTH                   0x0D /* Length of CSW                */

/* Status code in CSW */

#define USB_CSW_STATUS_PASS              0x00 /* CBW Command success */
#define USB_CSW_STATUS_FAIL              0x01 /* CBW Command failed  */
#define USB_CSW_PHASE_ERROR              0x02 /* Phase Error         */

/* IRP Time out in millisecs */

#define USB_BULK_IRP_TIME_OUT            5000

/* SCSI Commands and related constants */

#define USB_SCSI_WRITE6                  0x0A /* 6-byte WRITE command     */
#define USB_SCSI_WRITE10                 0x2A /* 6-byte WRITE command     */
#define USB_SCSI_READ6	                 0x08 /* 6-byte READ command      */
#define USB_SCSI_READ10	                 0x28 /* 10-byte READ command      */
#define USB_SCSI_INQUIRY                 0x12 /* Standard INQUIRY command */
#define USB_SCSI_START_STOP_UNIT         0x1B /* Start Stop Unit command  */
#define USB_SCSI_REQ_SENSE               0x03 /* REQUEST SENSE data       */
#define USB_SCSI_TEST_UNIT_READY         0x00 /* TEST UNIT READY command  */
#define USB_SCSI_READ_CAPACITY           0x25 /* READ CAPACITY command    */
#define USB_SCSI_PREVENT_REMOVAL         0x1E /* Prevent media removal    */
#define USB_SCSI_FORMAT_UNIT             0x04 /* FORMAT UNIT Command      */
#define USB_SCSI_MODE_SENSE              0x1A /* MODE SENSE Command       */

/* specific bit definitions in SCSI commands */

#define USB_SCSI_STD_INQUIRY_LEN         0x24 /* Length of std INQUIRY data */
#define USB_SCSI_REQ_SENSE_LEN           0x12 /* Length of Req Sense data   */
#define USB_SCSI_READ_CAP_LEN            0x08 /* Length of RD_CAP response  */
#define USB_SCSI_INQUIRY_RMB_BIT         0x80 /* Media Type bit             */
#define USB_SCSI_START_STOP_LOEJ         0x02 /* Media load eject bit       */
#define USB_SCSI_START_STOP_START        0x01 /* Media start bit            */

/* definitions with in request sense data */

#define USB_SCSI_SENSE_KEY_OFFSET        0x02 /* Sense key offset in sense   */
#define USB_SCSI_SENSE_ASC               0x0C /* Add'tl sense code offset    */
#define USB_SCSI_SENSE_ASCQ              0x0D /* Add'tl sense code qualifier */
#define USB_SCSI_SENSE_CUR_ERR           0x70 /* code for Current Errors     */
#define USB_SCSI_SENSE_KEY_MASK          0x0F /* Mask for sense key          */
#define USB_SCSI_KEY_NO_SENSE            0x00 /* No specific sense key       */
#define USB_SCSI_KEY_NOT_READY           0x02 /* Not ready value for key     */
#define USB_SCSI_KEY_UNIT_ATTN           0x06 /* Unit Attn value for key     */
#define USB_SCSI_KEY_HW_ERROR            0x04 /* Hardware Err value for key  */
#define USB_SCSI_ASC_NO_MEDIA            0x3A /* Media not present code      */
#define USB_SCSI_ASC_MEDIA_CHANGE        0x28 /* Media change code  */
#define USB_SCSI_ASC_RESET               0x29 /* Reset or media change code  */
#define USB_SCSI_MODE_SENSE_PAGE_CODE    0x3f /* Mode Sense page code        */
#define USB_SCSI_MODE_SENSE_ALLOC_LEN    0xFF /* Mode Sense allocation length*/

#define USB_SCSI_MODE_SENSE_GEOMETRY_PAGE_CODE 0x04  /* Mode Sense geometry
                                                      * command page code
                                                      */
#define USB_SCSI_MODE_SENSE_GEOMETRY_ALLOC_LEN  0x20 /* Mode Sense geometry
                                                      * allocation length
                                                      */
#define USB_SCSI_MODE_SENSE_FORMAT_PARAMS_PAGE_CODE 0x03 /* Mode Sense format
                                                          * unit command page
                                                          * code
                                                          */
#define USB_SCSI_MODE_SENSE_FORMAT_PARAMS_ALLOC_LEN 0x20 /* Mode Sense format
                                                          * unit allocation
                                                          * length
                                                          */
#define USB_SCSI_MODE_SENSE_HEADER_ALLOC_LEN    0x04   /* Mode Sense length
                                                        * for block header
                                                        */
#define USB_SCSI_SEC_PER_TRACK_OFFSET    0x12  /* offset for sec per track info
                                                * in format params page
                                                */
#define USB_SCSI_CYLINDER_OFFSET         0x9   /* offset for cylinder info in
                                                * rigid drive geometry page
                                                */
#define USB_SCSI_HEADS_OFFSET            0xd   /* offset for heads info in rigid
                                                * drive geometry page
                                                */

/* default device geometry info */
#define USB_BULK_DEV_DEFAULT_SECS_PER_TRACK 0x3f  /* Default secPerTrack info */

/* device create flag bits */

/*
 * The fourth parameter to usbBulkBlkDevCreate is an int inteded to be a bit
 * field.  The first bit is used to determine which type of SCSI read / write
 * command is used.  All other bits are undefined and available for furture use.
 */

#define USB_SCSI_FLAG_READ_WRITE10	0x00000001  /* READ/WRITE10 */
#define USB_SCSI_FLAG_READ_WRITE6	0x00000000  /* READ/WRITE6 */

/* Class specific commands */

#define USB_BULK_RESET                   0xFF /* Mass storage reset command  */
#define USB_BULK_GET_MAX_LUN             0xFE /* Acquire Max. LUN command    */

/* Attach codes used by USB_BULK_ATTACH_CALLBACK. */

#define USB_BULK_ATTACH	                0      /* Bulk-only Device attached  */
#define USB_BULK_REMOVE	                1      /* Bulk-only Device removed   */

/* Swap macros */

/*
 * SCSI Response is in BIG ENDIAN format. Needs swapping on LITTLE ENDIAN
 * platforms.
 */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define USB_SCSI_SWAP_32
#define USB_SCSI_SWAP_16

#else

#define USB_SCSI_SWAP_32(x)  LONGSWAP((UINT)x)
#define USB_SCSI_SWAP_16(x)  ((LSB(x) << 8)|MSB(x))

#endif

/*
 * Command blocks for Bulk-only devices are in LITTLE ENDIAN format. Need
 * swapping on BIG ENDIAN platforms.
 */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define USB_BULK_SWAP_32(x)  LONGSWAP((UINT)x)
#define USB_BULK_SWAP_16(x)  ((LSB(x) << 8)|MSB(x))

#else   /* _BYTE_ORDER == _BIG_ENDIAN   */

#define USB_BULK_SWAP_32
#define USB_BULK_SWAP_16

#endif  /* _BYTE_ORDER == _BIG_ENDIAN   */

typedef struct usbBulkDevXbdLun
    {
    XBD               usbBulkXbdDev;      /* XBD structure for this device  */
    SEM_ID            usbBulkXbdMutex;    /* lock for this wraper           */
    SEM_ID            usbBulkEjectMutex;  /* lock for eject                 */
    SEM_ID            usbBulkXbdReady;    /* work available for service     */
    BOOL              usbBulkXbdReadyChanged; /* Ready Changed bit          */
    FUNCPTR           usbBulkDevRd;       /* driver read function pointer   */
    FUNCPTR           usbBulkDevWrt;      /* driver write function pointer  */
    struct bio *      usbBulkXbdQueueh;    /* List of bios to process       */
    struct bio *      usbBulkXbdQueuet;    /* Tail of the bio list          */
    TASK_ID           usbBulkXbdService;   /* Service task for this wrapper */
    int               usbBulkRWMode;       /* device read write mode        */
    BOOL              usbBulkXbdRemovable; /* if the device is removable    */
    UINT8             blkLun;       /* lun value for this unit       */
    BOOL              blkDrvEmpty;  /* if the drive has no media     */
    UINT32            blkNumBlks;   /* number of blocks              */
    UINT32            blkOffset;    /* device offset                 */
    UINT8             blkVendorInfo[8]; /* vendor info               */
    UINT8             blkProdId[16];    /* product id                */
    UINT8             blkProdRev[4];    /* product revision id       */
    BOOL              usbBulkXbdInstantiated; /* USB XBD instantiation flag */
    SEM_ID            usbBulkXbdSyncId;      /* used for XBD instantiation */
    BOOL              usbBulkXbdInserted;    /* USB device insertion flag */
    BOOL              bioStatus;            /* to determine whether all bios */
                                            /* are services */
    BOOL              unmounting; /* indicates if this LUN will be unmouned */
    } USB_BULK_DEV_XBD_LUN, *pUSB_BULK_DEV_XBD_LUN;

/* Maximum number of logical units per device supported */
#define MAX_LUN 5

/* command block wrapper */

typedef struct usbBulkCbw
    {
    UINT32  signature;              /* CBW Signature */
    UINT32  tag;                    /* Tag field     */
    UINT32  dataXferLength;         /* Size of data (bytes) */
    UINT8   direction;              /* direction bit */
    UINT8   lun;                    /* Logical Unit Number */
    UINT8   length;                 /* Length of command block */
    UINT8   CBD [USB_CBW_MAX_CBLEN];/* buffer for command block */
    } WRS_PACK_ALIGN(1) USB_BULK_CBW, *pUSB_BULK_CBW;

typedef struct usbBulkCsw
    {
    UINT32  signature;              /* CBW Signature */
    UINT32  tag;                    /* Tag field  */
    UINT32  dataResidue;            /* Size of residual data(bytes) */
    UINT8   status;                 /* buffer for command block */
    } WRS_PACK_ALIGN(1) USB_BULK_CSW, *pUSB_BULK_CSW;

/* USB_BULK_ATTACH_CALLBACK defines a callback routine which will be
 * invoked by usbBulkDevLib.c when the attachment or removal of a MSC/SCSI/
 * BULK-ONLY device is detected.  When the callback is invoked with an attach
 * code of USB_BULK_ATTACH, the nodeId represents the ID of newly added device.
 * When the attach code is USB_BULK_REMOVE, nodeId points to the Bulk-only device
 * which is no longer attached.
 */

typedef VOID (*USB_BULK_ATTACH_CALLBACK)
    (
    pVOID arg,           /* caller-defined argument           */
    USBD_NODE_ID nodeId, /* nodeId of the bulk-only device    */
    UINT16 attachCode    /* attach or remove code             */
    );

/* function prototypes */

STATUS usbBulkDevInit (void);
STATUS usbBulkDevShutDown (int errCode);
STATUS usbBulkDynamicAttachRegister ( USB_BULK_ATTACH_CALLBACK callback,
                                        pVOID arg);

XBD * usbBulkBlkDevCreate (USBD_NODE_ID nodeId, UINT8 lun, UINT32 numBlks,
                              UINT32 blkOffset, UINT32 flags);

STATUS usbBulkDynamicAttachUnregister ( USB_BULK_ATTACH_CALLBACK callback,
                                        pVOID arg);
STATUS usbBulkDevLock (USBD_NODE_ID nodeId);
STATUS usbBulkDevUnlock (USBD_NODE_ID nodeId);
STATUS usbBulkDriveResetEnable( BOOL enable );
UINT8  usbBulkGetMaxLun (USBD_NODE_ID nodeId);

BOOL   usbBulkDriveEmpty (USBD_NODE_ID nodeId, UINT8 lun);
void   usbBulkDriveShow(USBD_NODE_ID nodeId, UINT8 lun);
void   usbBulkDevShow(USBD_NODE_ID nodeId);
void   usbBulkShow(void);
void   usbBulkStatusCheckBypassSet(BOOL);
VOID   usbBulkDevDestroyByNode(USBD_NODE_ID nodeId);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /* __INCusbBulkDevLibh */

