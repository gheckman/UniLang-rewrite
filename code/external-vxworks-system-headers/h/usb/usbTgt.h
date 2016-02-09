/* usbTgt.h - Definitions for USB GEN2 Target Stack Management Module */

/*
 * Copyright (c) 2010-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01q,01jan15,lan  Add WCID support (VXW6-83565)
01p,01aug13,wyy  Correct misspelled uFuncStatus in struct usbtgt_func_driver
                 (WIND00428358)
01o,21nov12,s_z  Add workaround to pass MSC CV case 10 (WIND00389964)
01n,15oct12,s_z  Add USBTGT_TCD_MAX_CONFIG_COUNT (WIND00382057)
01m,04sep12,s_z  Add usbTgtTcdRegister/usbTgtTcdUnRegister API
01l,18may12,s_z  Add support for USB 3.0 target (WIND00326012)
01k,18may12,s_z  Add support for PLX USB 3.0 TCD support (WIND00188662)
01j,28jul11,s_z  Add bIadNeeded element in struct usbtgt_config
01i,08apr11,ghs  Fix code coverity issue(WIND00264893)
01h,31mar11,s_z  Change definition of struct usbtgt_device_info
01g,28mar11,s_z  Add the definiation of USBTGT_LANG_DESC_INDEX
01f,24mar11,s_z  Remove unused routines and code clean
01e,23mar11,m_y  add USBTGT_COMMON_STR_LEN
01d,08mar11,s_z  Code clean up
01c,14feb11,s_z  Add ioctl in the USBTGT_TCD_FUNCS
01b,29jan11,ghs  Add usbTgtErpCallback() to this file
01a,17may10,s_z  created
*/

/*
DESCRIPTION

This file includes the defination and routines of the USB GEN2 target stack
management modules.

INCLUDE FILES:  vxWorks.h, ioLib.h, lstLib.h, semLib.h, vwModNum.h 
                hwif/vxbus/vxBus.h, usb/usb.h, usb/usbOtg.h, usb/usbOsal.h
                usb/ossLib.h, usb/usbDescrCopyLib.h, usb/usbOsalDebug.h,
                usb/usbTgtCommon.h
*/

#ifndef __INCusbTgth
#define __INCusbTgth

/* includes */

#include <vxWorks.h>
#include <ioLib.h>
#include <semLib.h>
#include <lstLib.h>
#include <vwModNum.h>
#include <hwif/vxbus/vxBus.h>
#include <usb/usb.h>
#include <usb/usbOtg.h>
#include <usb/usbOsal.h>
#include <usb/ossLib.h>
#include <usb/usbDescrCopyLib.h>
#include <usb/usbOsalDebug.h>
#include <usb/usbTgtCommon.h> 


#ifdef  __cplusplus
extern "C" {
#endif

/* defines */

/* Define the USB target stack show routines */

#ifndef USBTGT_SHOW_ENABLE
#define USBTGT_SHOW_ENABLE
#endif


/* Defines for the supported usb spec version  */

#define USBTGT_VERSION_10          (0x0100)     /* USB full speed */
#define USBTGT_VERSION_11          (0x0110)     /* USB full speed */
#define USBTGT_VERSION_20          (0x0200)     /* USB high speed */
#define USBTGT_VERSION_21          (0x0210)     /* USB high speed for USB3 dev */
#define USBTGT_VERSION_30          (0x0300)     /* USB susper speed */
#define USBTGT_VERSION_SUPPORTED   USBTGT_VERSION_20

#define USBTGT_MAX_NAME_SZ         (31)
#define USBTGT_MAX_MSG_COUNT       (10)
#define USBTGT_COMMON_STR_LEN      (32)
#define USBTGT_TCD_NAME_DEFAULT    "/usbTgt"

#define USBTGT_TCD_MIN_CONFIG_COUNT 1
#define USBTGT_TCD_MAX_CONFIG_COUNT 5
#define USBTGT_TCD_DEFAULT_CONFIG_COUNT USBTGT_TCD_MIN_CONFIG_COUNT

#define USB_ENDPOINT_MAX_COUNT   (16)
#define USB_ENDPOINT_MAXPSIZE(n)                (0xFFFF & (n))


/* 
 * USB_TCD_EP0_STAGE_SETUP_PEND:
 * This stage is used to indicate that, when the setup packet
 * has received in the buffer by the hardware, there is still no request
 * on the list to get this data. This setup packet can be read when one 
 * setup request is issued.
 *
 * USB_TCD_EP0_STAGE_DATA_OUT_PEND:
 * Some hardware issues the DATA OUT packet followed by the setup packet.
 * While, if there still no DATA OUT request to get those data, this stage
 * will be set.
 *
 * Why no DATA IN PEND or STATUS IN PEND stages?
 * The pending status only used for such case. eg, the hardware interrupt faster
 * and need move on next stage, but software slower to prepare resource.
 * 
 * For example, the HOST issued the DATA OUT to the device, and the device
 * hardware received in its FIFO, but there is no ERP buffer to store the 
 * data, we set the DATA OUT pending stage.
 * 
 */
 
typedef enum  usb_tcd_ep0_stage
    {
    USB_TCD_EP0_STAGE_IDLE            = (0),
    USB_TCD_EP0_STAGE_SETUP           = (1),
    USB_TCD_EP0_STAGE_DATA_IN         = (2),
    USB_TCD_EP0_STAGE_DATA_OUT        = (3),
    USB_TCD_EP0_STAGE_STATUS_IN       = (4),
    USB_TCD_EP0_STAGE_STATUS_OUT      = (5),
    USB_TCD_EP0_STAGE_ACK_WAIT        = (6),
    USB_TCD_EP0_STAGE_SETUP_PEND      = (7), /* Get setup packet without request */
    USB_TCD_EP0_STAGE_DATA_OUT_PEND   = (8),
    USB_TCD_EP0_STAGE_STATUS_OUT_PEND = (9)
    }USB_TCD_EP0_STAGE;


#define USB_MEMBER_TO_OBJECT(pMember, type, memberName) \
    ((type *)((char *)(pMember) - offsetof (type, memberName)))


/* Defines the Hardware controller type */

/* Ascii code of 'T'arget 'C'ontroller 'D'river to define the TCD signature */

#define USBTGT_TCD_SIG             (0x54430000)           /* Ascii code of 'TC' */
#define USBTGT_TCD_MAGIC_CODE(x)   (USBTGT_TCD_SIG | (x)) /* 0x01 <= x <= 0xFFFF */

/* Ascii code of 'F'unction 'C'lass 'D'river to define the FCD signature */

#define USBTGT_FUNC_SIG            (0x46430000)            /* Ascii code of 'FC' */
#define USBTGT_FUNC_MAGIC_CODE(x)  (USBTGT_FUNC_SIG | (x)) /* 0x01 <= x <= 0xFFFF */
#define USBTGT_MAGIC_ID_DEAD       (0xDEADFDCD)
#define USBTGT_MAGIC_ID_ADD_EN     (0xE0000ADD)

/* Ascii code of targ channel 'CH' */

#define USBTGT_TARG_CHANNEL_SIG    ((USB_TARG_CHANNEL)0x43480000)
#define USBTGT_TARG_CHANNEL_DEAD   ((USB_TARG_CHANNEL)0)

#define IS_TCD_MAGICID_VALID(magicID)                                           \
    ((USBTGT_TCD_SIG == (magicID & USBTGT_TCD_SIG)) ? TRUE : FALSE)

#define IS_FUNC_DRIVER_MAGICID_VALID(magicID)                                   \
    ((USBTGT_FUNC_SIG == (magicID & USBTGT_FUNC_SIG)) ? TRUE : FALSE)

#define IS_USBTGT_TARG_CHANNEL_VALID(targChannel)                               \
    ((USBTGT_TARG_CHANNEL_SIG == (targChannel & USBTGT_TARG_CHANNEL_SIG)) ?     \
      TRUE : FALSE)


#define USBTGT_MUTEX_CREATION_OPTS (SEM_Q_PRIORITY |                            \
                                    SEM_INVERSION_SAFE |                        \
                                    SEM_DELETE_SAFE)

#define USBTGT_WAIT_TIMEOUT_FOREVER     WAIT_FOREVER
#define USBTGT_WAIT_TIMEOUT             USBTGT_WAIT_TIMEOUT_FOREVER

#define USBTGT_MIN_CONFIG_NUM    1
#define USBTGT_MAX_CONFIG_NUM    0x10

/*
 * From the usb 2.0 spec 8.3.2.2, there is one four-bit
 * endpoint (ENDP) field in one usb packet. So the max endpoint number is 16
 */

#define USBTGT_MAX_EP_NUM        0x10


#define USBTGT_EP0_MAX_PKT_SZIE  0x40 /* Control endpoint max packet size in high speed */
#define USBTGT_EP0_MIN_PKT_SZIE  0x08 /* Control endpoint min packet size in low speed */
#define USBTGT_EP0_SUPERSPEED_PKT_INDEX  0x9 /* Control endpoint max packet size in high speed */
#define USBTGT_EP0_SUPERSPEED_PKT_SIZE  512 /* Control endpoint max packet size in high speed */



#define USBTGT_EP_PKT_SIZE_08    0x08  /* Endpoint packet size 8 */
#define USBTGT_EP_PKT_SIZE_16    0x10  /* Endpoint packet size 16 */
#define USBTGT_EP_PKT_SIZE_32    0x20  /* Endpoint packet size 32 */
#define USBTGT_EP_PKT_SIZE_64    0x40  /* Endpoint packet size 64 */
#define USBTGT_EP_PKT_SIZE_512   0x200 /* Endpoint packet size 512 */
#define USBTGT_EP_PKT_SIZE_1023  0x3FF /* Endpoint packet size 1023 */
#define USBTGT_EP_PKT_SIZE_1024  0x400 /* Endpoint packet size 1024 */

#define USBTGT_MAX_CONTORL_BUF_SIZE 0x100

#define USB_TCD_COUNT_1                  1
#define USB_TCD_COUNT_2                  2
#define USB_TCD_COUNT_3                  3
#define USB_TCD_COUNT_4                  4
#define USBTGT_DEFALUT_CONFIGURE_NUM     1
#define USBTGT_DEFALUT_INTERFACE_NUM     0
#define USBTGT_DEFALUT_ENDPOINT_NUM      1 /* Enpoint 0 can be used at least */
#define USBTGT_DEFALUT_CONFIG_DESC_LEN   USB_CONFIG_DESCR_LEN

/* Followed will be move to other place, not in this file */

#define USBTGT_LANG_DESC_INDEX           0x0       /* Language descripor index */
#define USBTGT_MFG_STRING_INDEX          0x1       /* iManufacturer */
#define USBTGT_PROD_STRING_INDEX         0x2       /* iProduct */
#define USBTGT_SERIAL_STRING_INDEX       0x3       /* iSerialNumber */
#define USBTGT_OS_DESC_STRING_INDEX      0xEE      /* OS String Descriptor */
#define USBTGT_OS_EXT_COMP_STRING_INDEX  0x4       /* Extended compat ID OS descriptor */

/*
 * Add here to define another hardware controller magic ID
 * Note, we support 255 kinds of usb hardware controller type, which should be
 * enough for real using.
 */


#define USBTGT_UNICODE_ENGLISH    (0x0409)      /* Unicode English */

/*
 * The following defines used by errnoSet routine.
 */

#define USBTGT_MNG_SUB_MODULE   (0x10)         /* Target Managment sub-Module */
#define USBTGT_TCD_SUB_MODULE   (0x11)         /* TCD sub-Module */
#define USBTGT_FUNC_SUB_MODULE  (0x12)         /* Function Driver sub-Module */

#define MusbTgtMngLib     ((USBTGT_MNG_SUB_MODULE << 8) | M_usbPeriphLib)
#define MusbTgtTcdLib     ((USBTGT_TCD_SUB_MODULE << 8) | M_usbPeriphLib)
#define MusbTgtFcdLib     ((USBTGT_FUNC_SUB_MODULE << 8) | M_usbPeriphLib)

#define usbTgtMngLibErr(x) (MusbTgtMngLib | (x))

#define usbTgtTcdLibErr(x) (MusbTgtTcdLib | (x))

#define usbTgtFcdLibErr(x) (MusbTgtFcdLib | (x))

/* Usb target management sub-module error num */

#define S_usbTgtMngLib_INVALID_PARAM      (M_usbPeriphLib | (0x10 << 8) | 1)  /* Invalid parameter */
#define S_usbTgtMngLib_BAD_HANDLE         (M_usbPeriphLib | (0x10 << 8) | 2)   /* bad handle */
#define S_usbTgtMngLib_OUT_OF_MEMORY      (M_usbPeriphLib | (0x10 << 8) | 3)   /* out of memory */
#define S_usbTgtMngLib_OUT_OF_RESOURCES   (M_usbPeriphLib | (0x10 << 8) | 4)   /* Out of resource */
#define S_usbTgtMngLib_NOT_IMPLEMENTED    (M_usbPeriphLib | (0x10 << 8) | 5)   /* not Implemented */
#define S_usbTgtMngLib_GENERAL_FAULT      (M_usbPeriphLib | (0x10 << 8) | 6)   /* general fault */
#define S_usbTgtMngLib_NOT_INITIALIZED    (M_usbPeriphLib | (0x10 << 8) | 7)   /* uninilialized */
#define S_usbTgtMngLib_CANNOT_CANCEL      (M_usbPeriphLib | (0x10 << 8) | 8)   /* cannot cancel */
#define S_usbTgtMngLib_TCD_FAULT          (M_usbPeriphLib | (0x10 << 8) | 9)   /* TCD related fault */
#define S_usbTgtMngLib_ENDPOINT_IN_USE    (M_usbPeriphLib | (0x10 << 8) | 10)  /* endpoint in use */
#define S_usbTgtMngLib_APP_FAULT          (M_usbPeriphLib | (0x10 << 8) | 11)  /* application fault */

/* Usb TCD sub-module error num */

#define S_usbTgtTcdLib_INVALID_PARAM      (M_usbPeriphLib | (0x11 << 8) | 1)  /* Invalid parameter */
#define S_usbTgtTcdLib_BAD_HANDLE         (M_usbPeriphLib | (0x11 << 8) | 2)   /* bad handle */
#define S_usbTgtTcdLib_OUT_OF_MEMORY      (M_usbPeriphLib | (0x11 << 8) | 3)   /* out of memory */
#define S_usbTgtTcdLib_OUT_OF_RESOURCES   (M_usbPeriphLib | (0x11 << 8) | 4)   /* Out of resource */
#define S_usbTgtTcdLib_NOT_IMPLEMENTED    (M_usbPeriphLib | (0x11 << 8) | 5)   /* not Implemented */
#define S_usbTgtTcdLib_GENERAL_FAULT      (M_usbPeriphLib | (0x11 << 8) | 6)   /* general fault */
#define S_usbTgtTcdLib_NOT_INITIALIZED    (M_usbPeriphLib | (0x11 << 8) | 7)   /* uninilialized */
#define S_usbTgtTcdLib_CANNOT_CANCEL      (M_usbPeriphLib | (0x11 << 8) | 8)   /* cannot cancel */
#define S_usbTgtTcdLib_TCD_FAULT          (M_usbPeriphLib | (0x11 << 8) | 9)   /* TCD related fault */
#define S_usbTgtTcdLib_ENDPOINT_IN_USE    (M_usbPeriphLib | (0x11 << 8) | 10)  /* endpoint in use */
#define S_usbTgtTcdLib_APP_FAULT          (M_usbPeriphLib | (0x11 << 8) | 11)  /* application fault */

#define S_usbTgtTcdLib_ERP_SUCCESS        (M_usbPeriphLib | (0x11 << 8) | 0)
#define S_usbTgtTcdLib_ERP_RESTART        (M_usbPeriphLib | (0x11 << 8) | 12)
#define S_usbTgtTcdLib_ERP_CANCELED       (M_usbPeriphLib | (0x11 << 8) | 13)

/* Usb Function driver sub-module error num */

#define S_usbTgtFcdLib_INVALID_PARAM      (M_usbPeriphLib | (0x12 << 8) | 1)   /* Invalid parameter */
#define S_usbTgtFcdLib_BAD_HANDLE         (M_usbPeriphLib | (0x12 << 8) | 2)   /* bad handle */
#define S_usbTgtFcdLib_OUT_OF_MEMORY      (M_usbPeriphLib | (0x12 << 8) | 3)   /* out of memory */
#define S_usbTgtFcdLib_OUT_OF_RESOURCES   (M_usbPeriphLib | (0x12 << 8) | 4)   /* Out of resource */
#define S_usbTgtFcdLib_NOT_IMPLEMENTED    (M_usbPeriphLib | (0x12 << 8) | 5)   /* not Implemented */
#define S_usbTgtFcdLib_GENERAL_FAULT      (M_usbPeriphLib | (0x12 << 8) | 6)   /* general fault */
#define S_usbTgtFcdLib_NOT_INITIALIZED    (M_usbPeriphLib | (0x12 << 8) | 7)   /* uninilialized */
#define S_usbTgtFcdLib_CANNOT_CANCEL      (M_usbPeriphLib | (0x12 << 8) | 8)   /* cannot cancel */
#define S_usbTgtFcdLib_TCD_FAULT          (M_usbPeriphLib | (0x12 << 8) | 9)   /* TCD related fault */
#define S_usbTgtFcdLib_ENDPOINT_IN_USE    (M_usbPeriphLib | (0x12 << 8) | 10)  /* endpoint in use */
#define S_usbTgtFcdLib_APP_FAULT          (M_usbPeriphLib | (0x12 << 8) | 11)  /* application fault */


#define USBTGT_STATUS                       INT8
#define USBTGT_SUCCESS                      ((INT8)0)
#define USBTGT_TRANSFER_COMPLETED           ((INT8)1)
#define USBTGT_FAILURE                      ((INT8)-1)
#define USBTGT_MEMORY_NOT_ALLOCATED         ((INT8)-2)
#define USBTGT_INSUFFICIENT_BANDWIDTH       ((INT8)-3)
#define USBTGT_INSUFFICIENT_MEMORY          ((INT8)-4)
#define USBTGT_INSUFFICIENT_RESOURCE        ((INT8)-5)
#define USBTGT_INVALID_REQUEST              ((INT8)-6)
#define USBTGT_INVALID_PARAMETER            ((INT8)-7)
#define USBTGT_STALL_ERROR                  ((INT8)-8)
#define USBTGT_DEVICE_NOT_RESPONDING_ERROR  ((INT8)-9)
#define USBTGT_DATA_OVERRUN_ERROR           ((INT8)-10)
#define USBTGT_DATA_UNDERRUN_ERROR          ((INT8)-11)
#define USBTGT_BUFFER_OVERRUN_ERROR         ((INT8)-12)
#define USBTGT_BUFFER_UNDERRUN_ERROR        ((INT8)-13)
#define USBTGT_TRANSFER_CANCELLED           ((INT8)-14)
#define USBTGT_TIMEOUT                      ((INT8)-15)
#define USBTGT_BAD_START_OF_FRAME           ((INT8)-16)

#define USBTGT_TCD_HANDLE_CONV_TO_TCD(tcdHandle)                                \
        (pUSBTGT_TCD)tcdHandle
        
#define USBTGT_TCD_CONV_TO_TCD_HANDLE(pTcd)                                     \
        (USBTGT_TCD_HANDLE)pTcd

#include <vsbConfig.h>

/* typedefs */

typedef pVOID USBTGT_TCD_HANDLE;

#define USBTGT_TCD_HANDLE_INVALID (USBTGT_TCD_HANDLE)(NULL)

typedef enum usb_tgt_callback_flag
    {
    CALLBACK_NORMAL = (1),
    CALLBACK_FORCE_RESTART = (2)
    }USBTGT_CALLBACK_FLAG;


/* Early declaration */

struct usbtgt_tcd;

/* The endpoint capability structure */

typedef struct usbtgt_ep_caps
    {
    /* The max packet size supported by this endpoint */

    UINT16 uMaxPktSize;

    /*
     * uXferTypeBitMap is the transfer type attribites of the endpoint.
     * It indicates whether the endpoint supports control/iso/bulk/interrupt
     * transfer types.
     *
     * Use one UINT8 for each endpoint to describ it's capability.
     *
     * In usb.h we defined :
     *    #define USB_ATTR_CONTROL     0x00
     *    #define USB_ATTR_ISOCH       0x01
     *    #define USB_ATTR_BULK        0x02
     *    #define USB_ATTR_INTERRUPT   0x03
     *
     * So we use the Bit map to indicate if this endpoint can support such kinds
     * of transaction.
     *
     * |7|6|5|4|3|2|1|0|
     *          | | | |___ 1: support CONTROL transaction, 0: not support
     *          | | |_____ 1: support ISOCH transaction, 0: not
     *          | |_______ 1: support BULK transaction, 0: not
     *          |_________ 1: support INTERRUPT transaction, 0: not
     *
     *  eg.
     *  Endpoint 0, which can only used as Control transaction, set the bit map
     *              uXferTypeBitMap as 0x01.
     *  Endpoint 1, which can used as ISOCH/BULK/INTERRUPT, set the bit map
     *              uXferTypeBitMap as 0x0E.
     */

    UINT8  uXferTypeBitMap;

    /*
     * uSyncTypeBitMap is the Synchronization Type attribites of the endpoint.
     * It is used only when the endpoint supported ISO transfer type, and
     * indicates whether the endpoint supports No Synchronization/Asynchronous
     * /Adaptive/Synchronous synchronization types.
     *
     * Use one UINT8 for each endpoint to describ it's capability.
     *
     * In usb.h we defined :
     *    #define USB_ATTR_EP_SYNCH_TYPE_NOSYNCH         (0x00)
     *    #define USB_ATTR_EP_SYNCH_TYPE_ASYNCH          (0x01)
     *    #define USB_ATTR_EP_SYNCH_TYPE_ADAPTIVE        (0x02)
     *    #define USB_ATTR_EP_SYNCH_TYPE_SYNCH           (0x03)
     *
     * So we use the Bit map to indicate if this endpoint can support such kinds
     * of transaction.
     *
     * |7|6|5|4|3|2|1|0|
     *          | | | |___ 1: support No Synchronization, 0: not support
     *          | | |_____ 1: support asynchronization type, 0: not
     *          | |_______ 1: support adaptive type, 0: not
     *          |_________ 1: support synchronization, 0: not
     */

    UINT8  uSyncTypeBitMap;

    /*
     * uSyncTypeBitMap is the usage Type attribites of the endpoint.
     * It is used only when the endpoint supported ISO transfer type, and
     * indicates whether the endpoint supports DATA/Feedback
     * /Implicit feedback data/Reserverd usage types.
     *
     * Use one UINT8 for each endpoint to describ it's capability.
     *
     * In usb.h we defined :
     *    #define USB_ATTR_EP_USAGE_TYPE_DATA            (0x00)
     *    #define USB_ATTR_EP_USAGE_TYPE_FEEDBACK        (0x01)
     *    #define USB_ATTR_EP_USAGE_TYPE_IMFEEDBACK      (0x02)
     *    #define USB_ATTR_EP_USAGE_TYPE_RESERVED        (0x03)
     *
     * So we use the Bit map to indicate if this endpoint can support such kinds
     * of transaction.
     *
     * |7|6|5|4|3|2|1|0|
     *            | | |___ 1: support Data usage, 0: not support
     *            | |_____ 1: support Feedback usage, 0: not
     *            |_______ 1: support Implicit feedback data, 0: not
     */

    UINT8  uUsageTypeBitMap;

    /*
     * The max transactions per (micro)frame. It indicates the ISO/Interupt
     * endpoints capibilitys. It must bigger than the additional transaction
     * number described in wMaxPacketSize item in endpoint desctiptor.
     */

    UINT8  uMaxTransactions;

    /*
     * Is this endpoint usable
     */

    BOOL   bUsable;
    BOOL   bRxTxShared;

    }USBTGT_EP_CAPS, *pUSBTGT_EP_CAPS;

    
/*
 * #define USB_SPEED_FULL          0   /@ full speed devcie (12 mbit) @/
 * #define USB_SPEED_LOW           1   /@ low speed device (1.5 mbit) @/
 * #define USB_SPEED_HIGH          2   /@ high speed device (480 mbit) @/
 * #define USB_SPEED_SUPER         3   /@ super speed device (5 gbit) @/
 */

#define USBTGT_SPEED_CAP_FULL  (0x1 << USB_SPEED_FULL)
#define USBTGT_SPEED_CAP_LOW   (0x1 << USB_SPEED_LOW)
#define USBTGT_SPEED_CAP_HIGH  (0x1 << USB_SPEED_HIGH)
#define USBTGT_SPEED_CAP_SUPER (0x1 << USB_SPEED_SUPER)

typedef struct usbtgt_device_info /* USBTGT_DEVICE_INFO */
    {
    struct usbtgt_ep_caps txEpCaps[USBTGT_MAX_EP_NUM];
    struct usbtgt_ep_caps rxEpCaps[USBTGT_MAX_EP_NUM];

    /*
     * Bitmap status of device
     *
     * #define USB_DEV_STS_LOCAL_POWER             0x0001
     * #define USB_DEV_STS_REMOTE_WAKEUP           0x0002
     * #define USB_DEV_STS_U1_ENABLE               0x0004  
     * #define USB_DEV_STS_U2_ENABLE               0x0008  
     * #define USB_DEV_STS_LMT_ENABLE              0x0010  
     */

    UINT16 uDeviceFeature;
    UINT8   uDevSpeedCap;
    UINT8   uUsb2Extension;
    UINT8   uLTMCap;
    UINT8 * pExtAttr; 

    }USBTGT_DEVICE_INFO, *pUSBTGT_DEVICE_INFO;

typedef struct usbtgt_config
    {
    NODE               configNode;
    struct usbtgt_tcd * pTcd;
    USB_CONFIG_DESCR   ConfigDesc;
    USB_CONFIG_DESCR   OtherSpeedConfigDesc;
    USBOTG_OTG_DESCR   OtgDesc;
    USBTGT_DEVICE_INFO DeviceInfo;
    SEM_ID             ConfigMutex;
    UINT8              uConfigIndex;
    UINT8              uIfNumUsed;
    UINT8              uEpNumUsed;
    BOOL               bIadNeeded;
    }USBTGT_CONFIG,*pUSBTGT_CONFIG;

/*
 * USB Target Function Driver Information
 * Which used to create struct usbtgt_func_driver
 */

typedef struct usbtgt_func_info
    {
    USB_DESCR_HDR **           ppFsFuncDescTable;    /* Function descriptors table in USB 1.0 speed */
    USB_DESCR_HDR **           ppHsFuncDescTable;    /* Function descriptors table in High speed mode */
    USB_DESCR_HDR **           ppSsFuncDescTable;    /* Function descriptors table in High speed mode */
    USB_TARG_CALLBACK_TABLE *  pFuncCallbackTable;   /* Function driver callback table */
    pVOID                      pCallbackParam;       /* Callback parameter */
    pVOID                      pFuncSpecific;        /* Function device specific data */

    char *                     pFuncName;            /* Function driver name */
    char *                     pTcdName;             /* Used for the TCD's name */
    UINT8                      uFuncUnit;            /* Function driver unit */
    UINT8                      uTcdUnit;             /* Used for the TCD's unit */
    UINT8                      uConfigToBind;        /* The configuration group in */
    void *                     pExtInfo;             /* The extra information */	
    char *                     pWcidString;          /* Windows compatibleID string */
    char *                     pSubWcidString;       /* Windows subCompatibleID string */
    UINT8                      uWcidVc;              /* WCID vendor code */
    }USBTGT_FUNC_INFO, *pUSBTGT_FUNC_INFO;

/*
 * USB Target Function Driver Abstraction
 */


struct usbtgt_func_driver;


typedef struct usbtgt_func_driver
    {
    NODE                       funcDriverNode;
    NODE                       funcInTcdListNode;
    VXB_DEVICE_ID              pDev;         /* Pointer to VxBus Device instance */
    SEM_ID                     funcMutex;    /* Used to protect the resource */

    UINT32                     uFuncMagicID;         /* Func magic Id */
    USB_TARG_CHANNEL           targChannel;          /* Targ channel */
    LIST                       pipeList;             /* List of the pipes */
    struct usbtgt_tcd *        pTcd;                 /* Attach to the TCD */

    USB_DESCR_HDR **           ppFsFuncDescTable;    /* Function descriptors table */
    USB_DESCR_HDR **           ppHsFuncDescTable;    /* Function descriptors table in High speed mode */
    USB_DESCR_HDR **           ppSsFuncDescTable;    /* Function descriptors table in super speed mode */
    USB_TARG_CALLBACK_TABLE *  pFuncCallbackTable;   /* Function driver callback table */
    pVOID                      pCallbackParam;       /* Callback parameter */
    pVOID                      pFuncSpecific;        /* Function device specific data */

    char *                     pFuncName;            /* Function driver name */
    char *                     pTcdName;             /* Used for the TCD's name */
    UINT8                      uFuncUnit;            /* Function driver unit */
    UINT8                      uTcdUnit;             /* Used for the TCD's unit */
    UINT8                      uConfigToBind;        /* The configuration group in */
    UINT8                      uCurrentConfig;       /* The configuration num included in */
    UINT32                     uExFlag;
    pUSBTGT_CONFIG             pConfig;              /* The configuration which be attached */
    UINT8 *                    pSsDescBuf;           /* High speed descriptor data buf */
    UINT8 *                    pHsDescBuf;           /* High speed descriptor data buf */
    UINT8 *                    pFsDescBuf;           /* Full speed descriptor data buf */
    UINT16                     uSsDescBufLen;        /* High Speed Descriptor len */
    UINT16                     uHsDescBufLen;        /* High Speed Descriptor len */
    UINT16                     uFsDescBufLen;        /* Full Speed Descriptor len */
    UINT8                      uIADDesc[8];          /* IAD descriptor buffer */	
    char *                     pWcidString;          /* Windows compatibleID string */
    char *                     pSubWcidString;       /* Windows subCompatibleID string */
    UINT8                      uWcidVc;              /* WCID vendor code */

    /* BitMaps of function status
     * 
     * #define USB_FUNC_REMOVET_WACKUP_CAP       0x0001
     * #define USB_FUNC_REMOVET_WACKUP_ENABLE    0x0002
     */
    UINT16                     uFuncStatus;
    UINT8                      uIfNumUsed;           /* How many interface in this function */
    UINT8                      uIfNumMin;            /* The min interface num */
    UINT8                      uIfNumMax;            /* The max interface num */
    }USBTGT_FUNC_DRIVER, *pUSBTGT_FUNC_DRIVER;


#define DRIVER_NODE_TO_USBTGT_FUNC(pNode)              \
     ((USBTGT_FUNC_DRIVER *) ((char *) (pNode) -      \
                            OFFSET(USBTGT_FUNC_DRIVER, funcDriverNode)))

#define TCD_LIST_NODE_TO_USBTGT_FUNC(pNode)            \
     ((USBTGT_FUNC_DRIVER *) ((char *) (pNode) -      \
                            OFFSET(USBTGT_FUNC_DRIVER, funcInTcdListNode)))


typedef struct usbtgt_func_channel
    {
    NODE                funcChNode;   /* Node used to link on the func channel list */
    USB_TARG_CHANNEL    targChannel;  /* Currently assigned handle */
    UINT32              uChannelSig;  /* Signature used to validate handle */
    pUSBTGT_FUNC_DRIVER pFuncDriver;  /* Arbitrary parameter used by caller */
    } USBTGT_FUNC_CHANNEL, *pUSBTGT_FUNC_CHANNEL;

/*
 * Target Controller Driver abstraction
 */

typedef struct usbtgt_tcd_funcs
    {
    STATUS (* pTcdCreatePipe)
        (
        struct usbtgt_tcd * pTcd,
        pUSB_ENDPOINT_DESCR pEndpointDesc,
        UINT16              uConfigurationValue,
        UINT16              uInterface,
        UINT16              uAltSetting,
        pUSB_TARG_PIPE      pPipeHandle
        );
    STATUS (* pTcdDeletePipe)
        (
        struct usbtgt_tcd * pTcd,
        USB_TARG_PIPE       pipeHandle
        );
    STATUS (* pTcdSubmitErp)
        (
        struct usbtgt_tcd * pTcd,
        USB_TARG_PIPE       pipeHandle,
        pUSB_ERP            pErp
        );
    STATUS (* pTcdCancelErp)
        (
        struct usbtgt_tcd * pTcd,
        USB_TARG_PIPE       pipeHandle,
        pUSB_ERP            pErp
        );
    STATUS (* pTcdPipeStatusSet)
        (
        struct usbtgt_tcd * pTcd,
        USB_TARG_PIPE       pipeHandle,
        UINT16              uStatus
        );
    STATUS (* pTcdPipeStatusGet)
        (
        struct usbtgt_tcd * pTcd,
        USB_TARG_PIPE       pipeHandle,
        UINT16 *            pStatus
        );
    STATUS (* pTcdWakeup)
        (
        struct usbtgt_tcd * pTcd
        );
    STATUS (* pTcdGetFrameNum)
        (
        struct usbtgt_tcd * pTcd,
        UINT16 * pFrameNum 
        );
    STATUS (* pTcdSoftConnect)
        (
        struct usbtgt_tcd * pTcd,
        BOOL isConnectUp
        );
    int    (* pTcdIoctl)
        (
        struct usbtgt_tcd * pTcd,
        int cmd,
        void * pContext
        );
    }USBTGT_TCD_FUNCS, *pUSBTGT_TCD_FUNCS;


typedef struct usbtgt_feature_param
    {
    UINT16 uIndex;    
    UINT16 uFeature; 
    UINT8  uRequestType;
    }USBTGT_FEATURE_PARAM;

/* This structure is used for pipe configuration parameters */

typedef struct usbtgt_pipe_config_param
    {
    UINT32   uMaxErpCount;    /* Maxium ERP count used by this pipe */
    UINT32   uMaxErpBufCount; /* Maxium ERP buffer count for each ERP */
    UINT32   uMaxErpBufSize;  /* Maxium ERP buffer size for each ERP */
    UINT32   uFlags;          /* Speicfic flags */
    void *   pPrivData;       /* Private data */
    }USBTGT_PIPE_CONFIG_PARAM, *pUSBTGT_PIPE_CONFIG_PARAM;


typedef enum usbtgt_tcd_ioctl_cmd
    {
    USBTGT_TCD_IOCTL_CMD_NULL          = 0,
    USBTGT_TCD_IOCTL_CMD_CLEAR_FEATURE = 1,
    USBTGT_TCD_IOCTL_CMD_SET_FEATURE   = 2,
    USBTGT_TCD_IOCTL_CMD_SET_SEL         = (USB_REQ_SET_SEL),         /* 48 */
    USBTGT_TCD_IOCTL_CMD_SET_ISOCH_DELAY = (USB_REQ_SET_ISOCH_DELAY), /* 49 */
    USBTGT_TCD_IOCTL_CMD_SPEED_UPDATE    = (0x0100), 
    USBTGT_TCD_IOCTL_CMD_CONIG_PIPE      = (0x0200),
    USBTGT_TCD_IOCTL_CMD_UNCONIG_PIPE    = (0x0400)
    }USBTGT_TCD_IOCTL_CMD;

typedef enum usbtgt_func_mngmt_pm
    {
    USBTGT_FUNC_MNGMT_PM_NULL             = 0,
    USBTGT_FUNC_MNGMT_PM_FUNCTION_SUSPEND = 1
    }USBTGT_FUNC_MNGMT_PM;


#define USBTGT_STRING_LEN  62

typedef struct usbtgt_string
    {
    NODE                strNode;     /* Node in the string list */
    pUSBTGT_FUNC_DRIVER pFuncDriver; /* The function driver uses this string */
    UINT16              uLangId;     /* Language ID */
    UINT8               uOldStrIndex;/* The original string index */
    UINT8               uNewStrIndex;/* The updated index */
    UINT8               strBuf[USBTGT_STRING_LEN];
    }USBTGT_STRING,*pUSBTGT_STRING;

typedef struct usbtgt_erp_buf
    {
    NODE             node;
    void *           pExtData;
    void *           pOwner;
    UINT8 *          pBfr;  
    UINT32           uBfrLen;
    UINT32           uActLen;
    UINT32           uHeaderLen;
    UINT32           uPayloadLen;
    UINT32           uTailLen;
    }USBTGT_ERP_BUF, * pUSBTGT_ERP_BUF;
/*
 * USB Target Erp
 *
 * This structure is used to packet the <'USB_ERP'> structure, and do not
 * modify anything of the <'USB_ERP'>. We need 2 members to add new feature
 * on USB GEN2 target stack. <erpFlags> indicates the ERP transaction flags,
 * such as whether one ZLP pecket will be needed after all the data
 * transfered. <'pContext'> used to store the private data
 * which used by the function drivers.For example, the USB network function
 * driver will use it to record the binder buffer information.
 */

typedef struct usbtgt_erp
    {
    NODE    node;
    LIST    bufList;
    void *  pContext;
    void *  pExtData;
    UINT32  uTransferSize;
    UINT32  uMaxBufSize;
    UINT16  uUsedBufCount;
    USB_ERP Erp;      /* USB ERP */
    }USBTGT_ERP, * pUSBTGT_ERP;

/*
 * USB Target TCD Information
 * Which used to create struct usbtgt_tcd
 */

typedef struct usbtgt_tcd_info
    {
    VXB_DEVICE_ID         pDev;         /* Pointer to VxBus Device instance */
    USBTGT_TCD_FUNCS *    pTcdFuncs;    /* Functions implemented by the TCD */
    pVOID                 pTcdSpecific; /* Pointer to TCD specific structure */
    USBTGT_DEVICE_INFO    DeviceInfo;   /* Device information */

    UINT16                uVendorID;    /* VID */
    UINT16                uProductID;   /* PID */
    UINT16                uBcdDevice;   /* bcdDevice */
    char *                pMfgString;   /* Manufacture string */
    char *                pProdString;  /* Producture string */
    char *                pSerialString;/* Serial num string */
    char *                pTcdName;     /* TCD name */
    UINT8                 uTcdUnit;     /* Tcd unit number */
    UINT8                 uConfigCount; /* The configuration count */
    }USBTGT_TCD_INFO, *pUSBTGT_TCD_INFO;

/*
 * USB Target Management Abstraction
 */

typedef struct usbtgt_tcd
    {
    NODE                  usbTgtTcdNode; /* Tcd node in the global list */
    SEM_ID                tcdMutex;      /* Used to protect the resource */
    LIST                  funcList;      /* Function drivers list */
    LIST                  configList;    /* Configuration list */
    LIST                  strDescList;   /* String descriptors list */
    atomic_t              controlErpUsed;/* The control ERP is pending or not */
    USB_TARG_PIPE         controlPipe;   /* Handle to default control pipe */
    USB_ERP               controlErp;    /* Erp used to transfer to/from */
    USB_SETUP             SetupPkt;      /* Setup pecket */
    UINT8                 dataBfr[USBTGT_MAX_CONTORL_BUF_SIZE]; /* Sending/receiving data */

    /* User configurable parameters */

    UINT32                uTCDMagicID;  /* TCD magic ID */

    UINT16                uVendorID;    /* VID */
    UINT16                uProductID;   /* PID */
    UINT16                uBcdDevice;   /* bcdDevice */
    char *                pMfgString;   /* Manufacture string */
    char *                pProdString;  /* Producture string */
    char *                pSerialString;/* Serial num string */
    char *                pTcdName;     /* TCD name */
    UINT8                 uTcdUnit;     /* Tcd unit number */

    /* Device specific parameters */

    VXB_DEVICE_ID         pDev;         /* Pointer to VxBus Device instance */
    USBTGT_TCD_FUNCS *    pTcdFuncs;    /* Functions implemented by the TCD */
    pVOID                 pTcdSpecific; /* Pointer to TCD specific structure */
    USBTGT_DEVICE_INFO    DeviceInfo;   /* Device information */

    USB_DEVICE_DESCR      DeviceDesc;   /* device Descriptor */
    USB_DEVICE_QUALIFIER_DESCR devQualifierDesc;/* Device qualifier descriptor */
    USB_LANGUAGE_DESCR *  pUsbTgtLangDescr;
    UINT8 *               pBosBuf;                
    UINT16                uBosBufLen;

    UINT8                 uSpeed;
    UINT8                 uDeviceAddress; /* Device Address */
    UINT8                 uAddrToSet;     /* Address we want to set */
    UINT8                 uCurrentConfig; /* 0 means the target is unconfigured */
    UINT8                 uStrListIndexUsed;
    BOOL                  bWakeupEnable;

    }USBTGT_TCD, *pUSBTGT_TCD;

typedef enum usbtgt_pipe_status
    {
    USBTGT_PIPE_STATUS_STALL        = (0x01 << 0),
    USBTGT_PIPE_STATUS_UNSTALL      = (0x01 << 1),
    USBTGT_PIPE_STATUS_DELETING     = (0x01 << 2),
    USBTGT_PIPE_STATUS_TOBE_STALL   = (0x01 << 3),
    USBTGT_PIPE_STATUS_TOBE_UNSTALL = (0x01 << 4),
    USBTGT_PIPE_STATUS_PROCESSING   = (0x01 << 5),
    USBTGT_PIPE_STATUS_DATA_PENDING = (0x01 << 6),
    USBTGT_PIPE_STATUS_MSC_CASE_10  = (0x01 << 7)
    }USBTGT_PIPE_STATUS;

/* Target pipe */

typedef struct usbtgt_pipe
    {
    NODE             pipeListNode;       /* Pipe List node */
    SEM_ID           pipeSynchMutex;     /* Mutex to protect the pipe resource */
    USB_TARG_PIPE    pipeHandle;
    pUSBTGT_FUNC_DRIVER pFuncDriver;
    UINT8               uEpAddr;            /* Endpoint dir and endpoint Address */


    UINT8               uInterface;
    UINT8               uAltSetting;
    UINT8               uEpDir;             /* Endpoint dir 0x80 IN; 0x00 OUT */
    UINT8               uEpType;            /* Type of endpoint */
    USBTGT_PIPE_STATUS  status;

    }USBTGT_PIPE, * pUSBTGT_PIPE;


typedef enum  usbtgt_tcd_ep0_stage
    {
    USBTGT_TCD_EP0_STAGE_IDLE       = (0),
    USBTGT_TCD_EP0_STAGE_SETUP      = (1),
    USBTGT_TCD_EP0_STAGE_DATA_IN    = (2),
    USBTGT_TCD_EP0_STAGE_DATA_OUT   = (3),
    USBTGT_TCD_EP0_STAGE_STATUS_IN  = (4),
    USBTGT_TCD_EP0_STAGE_STATUS_OUT = (5),
    USBTGT_TCD_EP0_STAGE_TOBE_DONE  = (6),
    USBTGT_TCD_EP0_STAGE_DATA_END   = (7),
    USBTGT_TCD_EP0_STAGE_DATA_ZLP_NEED = (8)
    }USBTGT_TCD_EP0_STAGE;

typedef enum usbtgt_notify_code
    {
    USBTGT_NOTIFY_UNKNOWN          = (0x10),
    USBTGT_NOTIFY_RESET_EVENT      = (0x11),
    USBTGT_NOTIFY_DISCONNECT_EVENT = (0x12),
    USBTGT_NOTIFY_SUSPEND_EVENT    = (0x13),
    USBTGT_NOTIFY_RESUME_EVENT     = (0x14),
    USBTGT_NOTIFY_ATTACH_EVENT     = (0x15),
    USBTGT_NOTIFY_DETACH_EVENT     = (0x16)
    }USBTGT_NOTIFY_CODE;

typedef struct usbtgt_notify_info
    {
    struct usbtgt_tcd *  pTcd;       /* Device point */
    USBTGT_NOTIFY_CODE   NotifyCode; /* connand code */
    } USBTGT_NOTIFY_INFO;


/* Imports */

IMPORT STATUS usbTgtCreatePipe
    (
    USB_TARG_CHANNEL     targChannel,
    pUSB_ENDPOINT_DESCR  pEndpointDesc,
    UINT8                uConfigurationValue,
    UINT8                uInterface,
    UINT8                uAltSetting,
    pUSB_TARG_PIPE       pPipeHandle
    );

IMPORT STATUS usbTgtDeletePipe
    (
    USB_TARG_PIPE pipeHandle
    );
IMPORT STATUS usbTgtUnConfigPipe
    (
    USB_TARG_PIPE        pipeHandle
    );
IMPORT STATUS usbTgtConfigPipe
    (
    USB_TARG_PIPE             pipeHandle,    /* Pipe handle */
    pUSBTGT_PIPE_CONFIG_PARAM pParam         /* Pointer to pipe handle */
    );

IMPORT STATUS usbTgtSubmitErp
    (
    USB_TARG_PIPE pipeHandle,
    pUSB_ERP      pErp
    );

IMPORT STATUS usbTgtCancelErp
    (
    USB_TARG_PIPE pipeHandle,
    pUSB_ERP      pErp
    );

IMPORT STATUS usbTgtSetPipeStatus
    (
    USB_TARG_PIPE pipeHandle,
    UINT16        state
    );

IMPORT STATUS usbTgtGetPipeStatus
    (
    USB_TARG_PIPE pipeHandle,
    UINT16 *      pBuf
    );

IMPORT STATUS usbTgtTcdDestroy
    (
    pUSBTGT_TCD pTcd
    );

IMPORT pUSBTGT_TCD usbTgtTcdCreate
    (
    pUSBTGT_TCD_INFO pTcdInfo
    );

IMPORT STATUS usbTgtFuncDestroy
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver
    );

IMPORT pUSBTGT_FUNC_DRIVER usbTgtFuncCreate
    (
    pUSBTGT_FUNC_INFO pFuncInfo
    );

IMPORT STATUS usbTgtFuncRemove
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver
    );

IMPORT STATUS usbTgtFuncAdd
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver
    );

IMPORT STATUS usbTgtTcdRemove
    (
    pUSBTGT_TCD pTcd
    );

IMPORT STATUS usbTgtTcdAdd
    (
    pUSBTGT_TCD pTcd
    );

IMPORT STATUS usbTgtInit
    (
    void
    );

IMPORT STATUS usbTgtExit
    (
    void
    );

IMPORT void usbTgtTcdEventNotify
    (
    pUSBTGT_TCD        pTcd,
    USBTGT_NOTIFY_CODE NotifyCode
    );

IMPORT pUSBTGT_FUNC_DRIVER usbTgtFindFuncByName
    (
    char * pFuncName,
    UINT8  uFuncUnit
    );

IMPORT pUSBTGT_TCD usbTgtFindTcdByName
    (
    char * pTcdName,
    UINT8  uTcdUnit
    );

IMPORT STATUS usbTgtFuncControlSetupErpSubmit
    (
    USB_TARG_CHANNEL targChannel
    );

IMPORT STATUS usbTgtFuncControlDataErpSubmit
    (
    USB_TARG_CHANNEL targChannel, /* Target channel */
    UINT16           bfrLen,      /* Length of response 0 */
    pUINT8           pBfr,        /* Pointer to the data buffer */
    ERP_CALLBACK     userCallback,/* USB Target Applcaition Callback */
    BOOL             bDataIn,     /* Is this for data in erp */
    USB_ERP_FLAGS    erpFlags     /* The ERP transaction flags */
    );

IMPORT STATUS usbTgtFuncControlStatusErpSubmit
    (
    USB_TARG_CHANNEL targChannel,    /* Target channel */
    BOOL             bStatusIn       /* Is status in */
    );

IMPORT VOID usbTgtErpCallback
    (
    pVOID    pErp            /* ptr to ERP */
    );

IMPORT STATUS usbTgtFuncControlPipeStall
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver
    );

IMPORT pUSBTGT_FUNC_DRIVER usbTgtTargChannelToFuncDriver
    (
    USB_TARG_CHANNEL     targChannel
    );

IMPORT STATUS usbTgtFuncRemoteWakeUp
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver
    );

IMPORT STATUS usbTgtFuncFrameNumGet
    (
    pUSBTGT_FUNC_DRIVER pFuncDriver,
    UINT16 *            pFrameNum
    );

IMPORT STATUS usbTgtControlPayloadRcv
    (
    USB_TARG_CHANNEL    targChannel,
    UINT16              bfrLen,
    pUINT8              pBfr,
    ERP_CALLBACK        userCallback
    );

IMPORT STATUS usbTgtControlResponseSend
    (
    USB_TARG_CHANNEL    targChannel,
    UINT16              bfrLen,
    pUINT8              pBfr,
    USB_ERP_FLAGS       erpFlags
    );

IMPORT STATUS usbTgtControlStatusSend
    (
    USB_TARG_CHANNEL    targChannel,
    BOOL                bStatusIn
    );
IMPORT STATUS usbTgtFuncUnRegister
    (
    USB_TARG_CHANNEL    targChannel
    );

IMPORT USB_TARG_CHANNEL usbTgtFuncRegister
    (
    pUSBTGT_FUNC_INFO pFuncInfo
    );

IMPORT STATUS usbTgtTcdUnRegister
    (
    pUSBTGT_TCD pTcd
    );
IMPORT pUSBTGT_TCD usbTgtTcdRegister
    (
    pUSBTGT_TCD_INFO pTcdInfo
    );

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbTgth */



