/* usb2Serial.h - Generation 2 USB USB-to-Serial driver */

/*
 * Copyright (c) 2010-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,09aug13,ghs  Add support for RTP (WIND00424933)
01g,16apr13,ghs  Add USB PL2303 serial device support (WIND00412983)
01f,19feb13,ghs  Add select IO support (WIND00403162)
01e,21dec12,ghs  Add interface field for support of multi-interface device
                 (WIND00394550)
01d,01aug11,ghs  Fix VxWorks version check macro (WIND00287708)
01c,06jul11,ghs  Use USBD match function for matching device ID (WIND00183500)
01b,29jul10,pad  Moved extern C statement after include statements.
01a,13apr10,ghs  written
*/

#ifndef __INCusb2Serialh
#define __INCusb2Serialh

/* includes */

#include <vxWorks.h>
#include <iosLib.h>
#include <rngLib.h>
#include <usb/usbHst.h>
#include <usb2/usb2Helper.h>
#include <selectLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define USB2_SERIAL_MAX_DRIVER                  16
#define USB2_SERIAL_MAX_VENDOR                  100

#define USB2_SER_PCCON_STARTUP_MSG              \
    "Console has been redirected to USB-to-Serial port...\n\r"

#define USB2_SER_WAIT_COUNT                     10

#if  !((_WRS_VXWORKS_MAJOR > 6) || \
     ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR >= 9)))
#define USB2_SER_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    USB2_CLASS_ERR(usb2Ser, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_SER_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    USB2_CLASS_DBG(usb2Ser, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_SER_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_VDBG(usb2Ser, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_SER_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_INFO(usb2Ser, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define USB2_SER_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    USB2_CLASS_WARN(usb2Ser, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#endif

/* typedefs */

typedef USBHST_DEVICE_ID USB2_SERIAL_DEVICE_ID;

typedef struct usb2_serial_device
    {
    DEV_HDR                 deviceHeader;
    USB2_CLASS_DEVICE *     pUsb2ClassDevice;
    UINT16                  uStatusReg;
    INT32                   deviceTimeout;
    UINT32                  wMaxPacketSizeOut;
    UINT32                  wMaxPacketSizeIn;
    UINT32                  wMaxPacketSizeSetup;
    pUSBHST_URB             pSetupUrb;
    pUSBHST_URB             pOutUrb;
    pUSBHST_URB             pInUrb;
    UINT8                   bOutEndPointAddr;
    UINT8                   bInEndPointAddr;
    UINT8                   bSetupEndPointAddr;
    char *                  pDeviceGeneralName;
    UINT32                  uDeviceIndex;
    USB2_FILE_DESC *        pOwner;
    UINT32                  baudRate;
#if  (_WRS_VXWORKS_MAJOR > 6) || \
     ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR >= 9))
    TASK_ID                 inTaskId;
#else
    int                     inTaskId;
#endif
    ssize_t                 inDataSize;
    char *                  inDataBuffer;
    SEM_ID                  inDataMutex;
    SEM_ID                  inDataEvent;
    SEM_ID                  terminateEvent;
    RING_ID                 hInRingBuffer;
    struct usb_pc_console_sio_chan * pUsbPcConSioChan;
    struct usb2_serial_adapter_info * pDriverInfo;
    int                     interfaceNum;
    int                     options;
    USB2_SERIAL_DEVICE_ID * devId;
    SEL_WAKEUP_LIST *       pSelWakeupList;     /* Select wakeup list */
    } USB2_SERIAL_DEVICE;

typedef struct usb2_serial_device_config_info
    {
    UINT8   uInEndPointAddr;
    UINT8   uOutEndPointAddr;
    UINT8   uIntEndPointAddr;
    UINT8   uSetupEndPointAddr;
    UINT8   configurationIndex;
    UINT8   uAlternateSetting;
    UINT32  wMaxPacketSizeIn;
    UINT32  wMaxPacketSizeOut;
    UINT32  wMaxPacketSizeInt;
    UINT32  wMaxPacketSizeSetup;
    } USB2_SERIAL_DEVICE_CONFIG_INFO;

/* define IOS funtion pointers */

typedef struct usb2_serial_adapter_private_funcs
    {
    STATUS (* usb2SerialOpen)
        (
        USB2_SERIAL_DEVICE * pDevice,
        INT32 mode
        );
    ssize_t (* usb2SerialRead)
        (
        USB2_SERIAL_DEVICE * pDevice,
        char *               pBuffer,
        int                  bfrSize
        );
    ssize_t (* usb2SerialWrite)
        (
        USB2_SERIAL_DEVICE * pDevice,
        char *               pBuffer,
        int                  bfrSize
        );
    STATUS (* usb2SerialClose)
        (
        USB2_SERIAL_DEVICE * pDevice
        );
    int (* usb2SerialIoctl)
        (
        USB2_SERIAL_DEVICE * pDevice,
        INT32 function,
        VOID *arg
        );
    USBHST_STATUS (* usb2SerialParseConfig)
        (
        struct usb2_serial_adapter_info * pDriverInfo,
        UINT32      hDevice,
        UINT8       bInterfaceNumber,
        USB2_SERIAL_DEVICE_CONFIG_INFO * pConfigInfo
        );
    VOID (* usb2SerialDeviceCreateCallback)
        (
        USB2_SERIAL_DEVICE * pDevice
        );
    VOID (* usb2SerialDeviceRemoveCallback)
        (
        USB2_SERIAL_DEVICE * pDevice
        );
    } USB2_SERIAL_ADAPTER_FUNCS;

typedef struct usb2_serial_adapter_info
    {
    INT8 *                      deviceName;
    /*
     * NOTE:
     *   If max packet size is set to zero duiring register to class driver,
     * class driver will use device's max packet size value of endpoint report.
     */
    UINT32                      uMaxInPacketSize;/* Max IN packet size */
    UINT32                      uMaxOutPacketSize;/* Max OUT packet size */
    USB2_SERIAL_ADAPTER_FUNCS   privateFuncs;/* private IOS function ptr */
    } USB2_SERIAL_ADAPTER_INFO;

typedef struct usb_pc_console_sio_chan
    {
    SIO_CHAN        SioChan;
    VXB_DEVICE_ID   pDev;
    BOOL            bufNotEmpty;
    STATUS       (* getTxChar)();
    STATUS       (* putRcvChar)();
    VOID *          getTxArg;
    VOID *          putRcvArg;
    UINT16          channelMode;
    int             channelNo;
    SEM_ID          hTxEvent;
    int             fd;
    SEM_ID          hFdMutex;
    char *          dummyBfr;
    size_t          dummyBfrSize;
    char *          outBfr;
    size_t          outBfrSize;
    int             dummyBfrDataSize;
#if  (_WRS_VXWORKS_MAJOR > 6) || \
     ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR >= 9))
    TASK_ID         hTxTaskId;
#else
    int             hTxTaskId;
#endif
    int             baudRate;
    int             devId;
    char            bindDevName[MAX_DRV_NAME_LEN + 1];
    int             rtpIoctl;
    int             rtpStatus;
    void *          rtpArg;
    SEM_ID          rtpMutex;
    SEM_ID          rtpEvent;
    } USB_PC_CON_SIO_CHAN;

IMPORT STATUS usb2SerialInit(INT8 *);

IMPORT STATUS usb2SerialFtdi232Init(INT8 *);

IMPORT STATUS usb2SerialWrsInit(INT8 *);

IMPORT STATUS usb2SerialPL2303Init(INT8 *);

IMPORT STATUS usb2SerialSubmitSetupUrb(USB2_SERIAL_DEVICE *, UINT8, UINT8,
                                       UINT16, UINT16, UINT16 *, UINT8 *);

IMPORT STATUS usb2SerialBulkTransfer(USB2_SERIAL_DEVICE *, pUSBHST_URB, UINT8,
                                     UINT32 *, UINT8 *);

IMPORT STATUS usbPcConDevInit(USB_PC_CON_SIO_CHAN *, size_t, size_t);

IMPORT VOID   usrUsb2SerialAttachPcCon(USB2_SERIAL_DEVICE *);

IMPORT VOID   usrUsb2SerialDetachPcCon(USB2_SERIAL_DEVICE *);

IMPORT int    sioNextChannelNumberAssign(void);

IMPORT STATUS usb2SerialDeviceIdAdd(USB2_SERIAL_DEVICE_ID *,
                                    USB2_SERIAL_ADAPTER_INFO *, UINT16);

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2Serialh */

