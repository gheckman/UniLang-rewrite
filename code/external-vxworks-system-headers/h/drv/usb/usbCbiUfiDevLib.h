/* usbCbiUfiDevLib.h - USB CBI Mass Storage class driver for UFI sub-class */

/*
 * Copyright (c) 2000-2001,2005, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01p,03aug10,m_y  Add bioBusy into structure usbCbiUfiDev to indicate the bio
                 is still executed by the usbCbiUfiXbdService (WIND00226144)
01o,30jul10,m_y  Add usbCbiUfiDevDestroyByNode declaration to remove
                 compile warning
01n,29apr10,pad  Moved extern C statement after include statements.
01m,13jan10,ghs  vxWorks 6.9 LP64 adapting
01l,20oct08,w_x  Added per devcie cbiDevMutex (WIND00130664)
01k,22sep05,hch  Update USB_CBI_UFI_DEV structure for XBD instantiation
                 and zero size disk support
01j,01aug05,hch  Moved the *Ioctl() and *StChk() to private header file
01i,09jul05,hch  Add the USB_CBI_UFI_DEV type definition for XBD implementation
01h,28mar05,pdg  Usage of hardware accessable memory changed
01g,18feb05,ami  Macros added to support USB_UFI_READ_FORMAT_CAPACITY command
01f,07may01,wef  changed module number to be (module num << 8) | M_usbHostLib
01e,02may01,wef  changed module number to be M_<module> + M_usbHostLib
01d,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes, removed command status codes that lived
                 there and in usbBulkDevLib.h and put into own file in
                 h/usb/usbMassStorage.h
01c,02sep00,bri  added support for multiple devices.
01b,04aug00,bri  updated as per review.
01a,26jun00,bri  created.
*/

#ifndef __INCusbCbiUfiDevLibh
#define __INCusbCbiUfiDevLibh


#ifndef _ASMLANGUAGE

/* includes */

#include <vwModNum.h>           /* USB Module Number Def's */
#include <usb/usbMassStorage.h> /* Command status codes */
#include <drv/xbd/xbd.h>        /* XBD library header */
#include <drv/erf/erfLib.h>     /* Event Frame Work library header */

#ifdef __cplusplus
extern "C" {
#endif

/* Module number and error code definitions */

/*
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */

#define USB_CBI_SUB_MODULE      12

#define M_usbCbiUfiLib          ( (USB_CBI_SUB_MODULE  << 8) | M_usbHostLib )

#define usbCbiUfiErr(x)         (M_usbCbiUfiLib | (x))

#define S_usbCbiUfiDevLib_OUT_OF_RESOURCES  usbCbiUfiErr (1)
#define S_usbCbiUfiDevLib_USBD_FAULT        usbCbiUfiErr (2)
#define S_usbCbiUfiDevLib_NOT_INITIALIZED   usbCbiUfiErr (3)
#define S_usbCbiUfiDevLib_BAD_PARAM         usbCbiUfiErr (4)
#define S_usbCbiUfiDevLib_OUT_OF_MEMORY     usbCbiUfiErr (5)
#define S_usbCbiUfiDevLib_NOT_REGISTERED    usbCbiUfiErr (6)
#define S_usbCBiUfiDevLib_NOT_LOCKED        usbCbiUfiErr (7)

#define USB_CLASS_MASS_STORAGE           0x08 /* USB Mass storage class code */
#define USB_SUBCLASS_UFI_COMMAND_SET     0x04 /* UFI command set definition  */
#define USB_INTERFACE_PROTOCOL_CBI       0x00 /* CBI interface protocol      */

#define USB_UFI_MAX_CMD_LEN              0x0C /* UFI Maximum command length  */
#define USB_UFI_INT_STATUS_LEN           2    /* Length of status data */

/* UFI Commands */

#define USB_UFI_FORMAT_UNIT              0x04 /* UFI Format Unit command   */
#define USB_UFI_INQUIRY                  0x12 /* UFI Inquiry command       */
#define USB_UFI_MODE_SELECT              0x55 /* UFI Mode Select command   */
#define USB_UFI_MODE_SENSE               0x5A /* UFI Mode Sense command    */
#define USB_UFI_PREVENT_MEDIA_REMOVAL    0x1E /* UFI Prevent/ Allow media  */
                                              /* removal command           */
#define USB_UFI_READ10                   0x28 /* UFI 10-byte Read comamnd  */
#define USB_UFI_READ12                   0xA8 /* UFI 12-byte Read command  */
#define USB_UFI_READ_CAPACITY            0x25 /* UFI Read Capacity command */
#define USB_UFI_READ_FORMAT_CAPACITY     0x23 /* UFI Read Format capacities*/
#define USB_UFI_REQUEST_SENSE            0x03 /* UFI Request sense command */
#define USB_UFI_REZERO                   0x01 /* UFI Rezero command        */
#define USB_UFI_SEEK10                   0x2B /* UFI 10-byte Seek command  */
#define USB_UFI_SEND_DIAGNOSTIC          0x1D /* UFI Send Diagnostic cmd   */
#define USB_UFI_START_STOP_UNIT          0x1B /* UFI Start Stop unit cmd   */
#define USB_UFI_TEST_UNIT_READY          0x00 /* UFI Test Unit Ready cmd   */
#define USB_UFI_VERIFY                   0x2F /* UFI Verify command        */
#define USB_UFI_WRITE10                  0x2A /* UFI 10-byte Write command */
#define USB_UFI_WRITE12                  0xAA /* UFI 12-byte Write command */
#define USB_UFI_WRITE_AND_VERIFY         0x2E /* UFI Write and Verify cmd  */

/* Bit Definitions with in UFI Command blocks */

#define USB_UFI_FORMAT_FMTDATA           0x10 /* Format Data bit       */
#define USB_UFI_FORMAT_FMT_DEFECT        0x07 /* Defect List format    */
#define USB_UFI_MODE_SEL_PF              0x10 /* Page Format bit       */
#define USB_UFI_MEDIA_REMOVAL_BIT        0x01 /* Prevent media removal */
#define USB_UFI_INQUIRY_RMB_BIT          0x80 /* Removable bit         */
#define USB_UFI_START_STOP_LOEJ          0x02 /* Media load eject bit  */
#define USB_UFI_WRITE_PROTECT_BIT        0x80 /* Write protect bit     */

/* Ioctl Control codes */

#define USB_UFI_ALL_DESCRIPTOR_GET       0xF0 /* Shows all descriptors */
#define USB_UFI_DEV_RESET                0xF1 /* Performs command reset*/

/* Miscellaneous Definitions */

#define UFI_STD_REQ_SENSE_LEN            0x12 /* Request sense data length  */
#define UFI_STD_INQUIRY_LEN              0x24 /* Length of Inquiry data     */
#define USB_UFI_MS_HEADER_LEN            0x08 /* Mode sense Header Length   */

/* Mode Sense Flexible Disk Page Lengh */
#define USB_UFI_FLEXIBLE_DISK_PAGE_LEN        0x20

/* Mode Sense Flexible Disk Page code */
#define USB_UFI_FLEXIBLE_DISK_PAGE_CODE  0x05

/* Disk head offset in Mode Sense Flexible Disk Page */
#define USB_UFI_MS_HEADS_OFFSET          0x04

/* Disk Cylinder offset in Mode Sense Flexible Disk Page */
#define USB_UFI_MS_CYLINDER_OFFSET       0x08

/* Disk Sector Per Track offset n Mode Sense Flexible Disk Page */
#define USB_UFI_MS_SPT_OFFSET            0x05

#define USB_FORMAT_UNIT_PARAM_LEN        0x0C /* Paramter List length for */
                                              /* format command */
#define UFI_READ_FORMAT_MAX_LENGTH       0xFF /* Maximum transfer length for */
                                              /* Read format capacity command */
#define USB_FORMAT_DESC_LEN              0x08 /* format descriptor lenght */

#define USB_UFI_DIR_IN                   0x80 /* Direction bit -> to host   */
#define USB_UFI_DIR_OUT                  0x00 /* Direction bit -> to device */

#define USB_UFI_SENSE_KEY_OFFSET        0x02 /* Sense key offset in sense   */
#define USB_UFI_SENSE_ASC               0x0C /* Add'tl sense code offset    */
#define USB_UFI_SENSE_ASCQ              0x0D /* Add'tl sense code qualifier */
#define USB_UFI_SENSE_KEY_MASK          0x0F /* Mask for sense key          */
#define USB_UFI_KEY_UNIT_ATTN           0x06 /* Unit Attn value for key     */
#define USB_UFI_KEY_NOT_READY           0x02 /* Not ready value for key     */
#define USB_UFI_ASC_NO_MEDIA            0x3A /* Media not present code      */
#define USB_UFI_ASC_MEDIA_CHANGE        0x28 /* Media change code  */

/* Sense key values */

#define USB_UFI_NO_SENSE                0x00 /* No Sense data                */
#define USB_UFI_RECOVERED_ERROR         0x01 /* Recovered from error         */
#define USB_UFI_NOT_READY               0x02 /* Device is not ready          */
#define USB_UFI_MEDIUM_ERROR            0x03 /* Flaw in the medium or data   */
#define USB_UFI_HARDWARE_ERROR          0x04 /* Non-recoverable h/w error    */
#define USB_UFI_ILL_REQUEST             0x05 /* Illegal parameter in command */
#define USB_UFI_UNIT_ATTN               0x06 /* Media change or reset        */
#define USB_UFI_DATA_PROTECT            0x07 /* Media write protect          */

/* ASC and ASCQ combinations */



#define USB_UFI_COMMAND_SUCCESS                                 0x0000  /* No sense data-success */
#define USB_UFI_RECOVERED_DATA_WITH_RETRIES                     0x1701
#define USB_UFI_RECOVERED_DATA_WITH_ECC	                        0x1800
#define USB_UFI_BECOMING_READY                                  0x0401
#define USB_UFI_INITIALIZATION_REQUIRED                         0x0402
#define USB_UFI_FORMAT_IN_PROGRESS                              0x0404
#define USB_UFI_DEVICE_IS_BUSY                                  0x04ff
#define USB_UFI_NO_REFERENCE_POSITION_FOUND                     0x0600
#define USB_UFI_COMMUNICATION_FAILURE                           0x0800
#define USB_UFI_COMMUNICATION_TIMEOUT                           0x0801
#define USB_UFI_COMMUNICATION_OVERRUN                           0x0880
#define USB_UFI_MEDIUM_NOT_PRESENT                              0x3a00
#define USB_UFI_INTERFACE_FAILURE                               0x5400
#define USB_UFI_INSUFFICIENT_RESOURCES                          0x8000
#define USB_UFI_UNKNOWN_ERROR                                   0xffff
#define USB_UFI_NO_SEEK_COMPLETE                                0x0200
#define USB_UFI_WRITE_FAULT                                     0x0300
#define USB_UFI_ID_CRC_ERROR                                    0x1000
#define USB_UFI_UNRECOVERED_READ_ERROR	                        0x1100
#define USB_UFI_ADDRESS_MARK_NOT_FOUND_FOR_ID_FIELD             0x1200
#define USB_UFI_ADDRESS_MARK_NOT_FOUND_FOR_DATA_FIELD           0x1300
#define USB_UFI_RECORDED_ENTITY_NOT_FOUND                       0x1400
#define USB_UFI_CANNOT_READ_MEDIUM_UNKNOWN_FORMAT               0x3001
#define USB_UFI_FORMAT_COMMAND_FAILED                           0x3101
#define USB_UFI_DIAGNOSTIC_FAILURE                              0x4000
#define USB_UFI_PARAMETER_LIST_LENGTH_ERROR                     0x1a00
#define USB_UFI_INVALID_COMMAND_OPERATION_CODE                  0x2000
#define USB_UFI_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE              0x2100
#define USB_UFI_INVALID_FIELD_IN_COMMAND_PACKET                 0x2400
#define USB_UFI_LOGICAL_UNIT_NOT_SUPPORTED                      0x2500
#define USB_UFI_INVALID_FIELD_IN_PARAMETER_LIST                 0x2600
#define USB_UFI_PARAMETER_NOT_SUPPORTED	                        0x2601
#define USB_UFI_PARAMETER_VALUE_INVALID	                        0x2602
#define USB_UFI_SAVING_PARAMETERS_NOT_SUPPORT                   0x3900
#define USB_UFI_MEDIA_CHANGE                                    0x2800 /* Media change          */
#define USB_UFI_POWER_ON_RESET                                  0x2900 /* Power on reset        */
#define USB_UFI_COMMANDS_CLEARED_BY_ANOTHER_INITIATOR           0x2f00
#define USB_UFI_WRITE_PROTECT                                   0x2700 /* Write protected media */
#define USB_UFI_OVERLAPPED_COMMAND_ATTEMPTED                    0x4e00

#define USB_CBI_IRP_TIME_OUT            5000

/* Attach codes used by USB_UFI_ATTACH_CALLBACK. */

#define USB_UFI_ATTACH                  0      /* CBI_UFI Device attached */
#define USB_UFI_REMOVE                  1      /* CBI_UFI Device removed  */

/* Swap macros */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define USB_SWAP_32
#define USB_SWAP_16

#else   /* _BYTE_ORDER == _BIG_ENDIAN   */

#define USB_SWAP_32(x)  LONGSWAP((UINT)x)
#define USB_SWAP_16(x)  ((LSB(x) << 8)|MSB(x))

#endif  /* _BYTE_ORDER == _BIG_ENDIAN   */

/* typedefs */

typedef struct usbUfiCmdBlock
    {
    UINT   dataXferLen;                  /* data transfer length       */
    UINT   direction;                    /* direction of data transfer */
    UINT8 *  pCmd;                       /* UFI Command block          */
    } USB_UFI_CMD_BLOCK, *pUSB_UFI_CMD_BLOCK;

typedef struct usbCbiUfiDev
    {
    XBD               usbCbiUfiXbdDev;   /* Vxworks block device structure */
                                         /* Must be the first one          */
    USBD_NODE_ID      cbiUfiDevId;       /* USBD node ID of the device     */
    SEM_ID            usbCbiUfiXbdMutex; /* lock for this Wrapper          */
    SEM_ID            usbCbiUfiReady;    /* work available for service     */
    UINT16            configuration;     /* Configuration value            */
    UINT16            interface;         /* Interface number               */
    UINT16            altSetting;        /* Alternate setting of interface */
    UINT16            outEpAddress;      /* Bulk out EP address            */
    UINT16            inEpAddress;       /* Bulk in EP address             */
    UINT16            intrEpAddress;     /* Interrupt EP address           */
    USBD_PIPE_HANDLE  outPipeHandle;     /* Pipe handle for Bulk out EP    */
    USBD_PIPE_HANDLE  inPipeHandle;      /* Pipe handle for Bulk in EP     */
    USBD_PIPE_HANDLE  intrPipeHandle;    /* Pipe handle for interrupt EP   */
    USB_IRP           inIrp;             /* IRP used for bulk-in data      */
    USB_IRP           outIrp;            /* IRP used for bulk-out data     */
    USB_IRP           statusIrp;         /* IRP used for status data       */
    USB_UFI_CMD_BLOCK ufiCmdBlk;         /* Store for UFI Command block    */
    UINT8 *           bulkInData;        /* Pointer for bulk-in data       */
    UINT8 *           bulkOutData;       /* Pointer for bulk-out data      */
    UINT8 *           pIntrStatus;       /* Store for Status bytes         */
    UINT16            lockCount;         /* Count of times structure locked*/
    UINT16            inEpAddressMaxPkt; /* Max In Pipe Packet size        */
    UINT16            outEpAddressMaxPkt;/* Max Out Pipe Packet size       */
    FUNCPTR           usbCbiUfiDevRd;    /* funciton pointer to device read  */
    FUNCPTR           usbCbiUfiDevWrt;   /* funciton pointer to device write */
    BOOL              connected;         /* TRUE if CBI_UFI device connected */
    SEM_HANDLE        cbiUfiIrpSem;      /* Semaphore for IRP Synchronisation */
    MUTEX_HANDLE      cbiDevMutex;       /* Mutex used to protect driver unit access */
    LINK              cbiUfiDevLink;     /* Link to other USB_CBI_UFI devices */
    int               usbCbiUfiRWMode;   /* device is write protected or not */
    struct bio *      usbCbiUfiXbdQueueh;/* List of bios to process        */
    struct bio *      usbCbiUfiXbdQueuet;/* tail of the bio list           */
    TASK_ID           usbCbiUfiXbdService;/* Service task for this wrapper */
    BOOL              usbCbiUfiDevReadyChanged; /* ready changed bit */
    BOOL              usbCbiUfiDevRemovable;   /* if the device is removable */
    BOOL              usbCbiUfiXbdDrvEmpty;    /* if the device is empty     */
    BOOL              usbCbiXbdInstantiated;   /* XBD instantiation flag */
    SEM_ID            usbCbiXbdSyncId;         /* used for XBD instantiation */
    BOOL              usbCbiXbdInserted;       /* USB device insertion flag  */
    BOOL              bioBusy;                 /* busy doing BIO */
   } USB_CBI_UFI_DEV, *pUSB_CBI_UFI_DEV;

/* USB_UFI_ATTACH_CALLBACK defines a callback routine which will be
 * invoked by usbCbiUfiDevLib.c when the attachment or removal of a CBI_UFI
 * device is detected.  When the callback is invoked with an attach code of
 * USB_UFI_ATTACH, the nodeId represents the ID of newly added device.  When
 * the attach code is USB_UFI_REMOVE, nodeId points to the CBI_UFI device which
 * is no longer attached.
 */

typedef VOID (*USB_UFI_ATTACH_CALLBACK)
    (
    pVOID arg,           /* caller-defined argument     */
    USBD_NODE_ID nodeId, /* nodeId of the UFI device    */
    UINT16 attachCode    /* attach or remove code       */
    );

/* function prototypes */

STATUS usbCbiUfiDevInit (void);
STATUS usbCbiUfiDevShutDown (int errCode);
STATUS usbCbiUfiDynamicAttachRegister ( USB_UFI_ATTACH_CALLBACK callback,
                                        pVOID arg);
XBD * usbCbiUfiBlkDevCreate (USBD_NODE_ID nodeId);

STATUS usbCbiUfiDynamicAttachUnregister ( USB_UFI_ATTACH_CALLBACK callback,
                                          pVOID arg);
STATUS usbCbiUfiDevLock (USBD_NODE_ID nodeId);
STATUS usbCbiUfiDevUnlock (USBD_NODE_ID nodeId);
VOID   usbCbiUfiDevDestroyByNode(USBD_NODE_ID nodeId);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus

}

#endif /* __cplusplus */

#endif /* __INCusbCbiUfiDevLibh */

