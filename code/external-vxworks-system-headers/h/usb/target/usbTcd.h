/* usbTcd.h - Defines generic interface to USB target controller drivers */

/*
 * Copyright (c) 2004, 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01h,30jun11,s_z  Move USB_TARG_PIPE to usbHandleLib.h (WIND00285554)
01g,29apr10,pad  Moved extern C statement after include statements.
01f,13jan10,ghs  vxWorks 6.9 LP64 adapting
01e,01sep04,pdg  Removed multiple definition
01d,03aug04,mta  Modification History Changes
01c,19jul04,ami  Coding Convnetion Changes
01b,14jul04,mta  ISP1582 and Mass Storage Functionality Changes
01a,04mar04,mta  First.
*/

/*
DESCRIPTION

Defines the generic interface to a USB target controller driver (TCD).
*/

#ifndef __INCusbTcdh
#define __INCusbTcdh

/* includes */

#include "usb/usbHandleLib.h"
#include "usb/usb.h"
#include "vwModNum.h"
#include "usb/target/usbHalCommon.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* defines */

/* TRB function codes */

/* Initialization and un-initialization Function Codes */

#define TCD_FNC_ATTACH          0x0000  /* attach/init target controller */
#define TCD_FNC_DETACH          0x0001  /* detach/shutdown target controller */
#define TCD_FNC_ENABLE          0x0002  /* enable target controller */
#define TCD_FNC_DISABLE         0x0003  /* disable target controller */

/* Device Control and Status Function Codes */

#define TCD_FNC_ADDRESS_SET           0x0100  /* set device address */
#define TCD_FNC_SIGNAL_RESUME         0x0101  /* drive resume signalling */
#define TCD_FNC_DEVICE_FEATURE_SET    0x0102  /* set feature on device */
#define TCD_FNC_DEVICE_FEATURE_CLEAR  0x0103  /* clear freature on device */
#define TCD_FNC_CURRENT_FRAME_GET     0x0104  /* get current frame number */

/* Endpoint Specific Function Codes */

#define TCD_FNC_ENDPOINT_ASSIGN       0x0200  /* assigns an endpoint */
#define TCD_FNC_ENDPOINT_RELEASE      0x0201  /* releases an endpoint */
#define TCD_FNC_ENDPOINT_STATE_SET    0x0202  /* set endpoint state */
#define TCD_FNC_ENDPOINT_STATUS_GET   0x0203  /* get endpoint status */
#define TCD_FNC_IS_BUFFER_EMPTY       0x0204  /* is endpoint buffer empty */
#define TCD_FNC_COPY_DATA_FROM_EPBUF  0x0205  /* copy data from endpoint buffer */
#define TCD_FNC_COPY_DATA_TO_EPBUF    0x0206  /* copy data to endpoint buffer */

/* Interrupt Specific Function Codes */

#define TCD_FNC_INTERRUPT_STATUS_GET            0x0300  /* get interrupt status*/
#define TCD_FNC_INTERRUPT_STATUS_CLEAR          0x0301  /* Clear Interrupt */
#define TCD_FNC_ENDPOINT_INTERRUPT_STATUS_GET   0x0302  /* get endpoint */
                                                        /* interrupt status */
#define TCD_FNC_ENDPOINT_INTERRUPT_STATUS_CLEAR 0x0303  /* clear endpoint */
                                                        /* interrupt status */
#define TCD_FNC_HANDLE_DISCONNECT_INTERRUPT     0x0304  /* handle disconnect */
                                                        /* interrupt */
#define TCD_FNC_HANDLE_RESET_INTERRUPT          0x0305  /* handle reset interrupt */
#define TCD_FNC_HANDLE_RESUME_INTERRUPT         0x0306  /* handle resume interrupt */
#define TCD_FNC_HANDLE_SUSPEND_INTERRUPT        0x0307  /* handle suspend interrupt */

/* TRB result codes */

/*
 * USB errnos are defined as being part of the USB peripheral Module, as are
 * all vxWorks module numbers, but the USB Module number is further divided
 * into sub-modules.  Each sub-module has upto 255 values for its own error
 * codes
 */

/* MATHEW:THESE ERROR CODES NEED TO BE REVIEWED */

#define USB_TCD_SUB_MODULE  2

#define M_usbTcdLib     ( (USB_TCD_SUB_MODULE  << 8) | M_usbPeriphLib )

#define tcdErr(x)   (M_usbTcdLib | (x))

#define S_usbTcdLib_BAD_PARAM           tcdErr(1)   /* bad parameter */
#define S_usbTcdLib_BAD_HANDLE          tcdErr(2)   /* bad handle */
#define S_usbTcdLib_OUT_OF_MEMORY       tcdErr(3)   /* out of memory */
#define S_usbTcdLib_OUT_OF_RESOURCES    tcdErr(4)   /* out of resource */
#define S_usbTcdLib_NOT_IMPLEMENTED     tcdErr(5)   /* not implemented */
#define S_usbTcdLib_GENERAL_FAULT       tcdErr(6)   /* general fault */
#define S_usbTcdLib_NOT_INITIALIZED     tcdErr(7)   /* not initialized */
#define S_usbTcdLib_INT_HOOK_FAILED     tcdErr(8)   /* faliure in int. hooking */
#define S_usbTcdLib_HW_NOT_READY        tcdErr(9)   /* hardware not ready */
#define S_usbTcdLib_NOT_SUPPORTED       tcdErr(10)  /* not supported */
#define S_usbTcdLib_ERP_CANCELED        tcdErr(11)  /* erp cancelled */
#define S_usbTcdLib_CANNOT_CANCEL       tcdErr(12)  /* cannot cancel ERP */
#define S_usbTcdLib_SHUTDOWN            tcdErr(13)  /* shutdown error */
#define S_usbTcdLib_DATA_TOGGLE_FAULT   tcdErr(14)  /* data toggle error */
#define S_usbTcdLib_PID_MISMATCH        tcdErr(15)  /* PID mismatch */
#define S_usbTcdLib_COMM_FAULT          tcdErr(16)  /* communication fault */
#define S_usbTcdLib_STALL_ERROR         tcdErr(17)  /* stall error */
#define S_usbTcdLib_NEW_SETUP_PACKET    tcdErr(18)  /* setup packet error */
#define S_usbTcdLib_DATA_OVERRUN        tcdErr(19)  /* data overrun */

/* endpoint states */

#define TCD_ENDPOINT_STALL      0x01    /* endpoint stall */
#define TCD_ENDPOINT_UNSTALL    0x02    /* endpoint unstall */

/* Interrupt status masks */
#define USBTCD_DISCONNECT_INTERRUPT_MASK    0x01    /* disconnect interrupt mask */
#define USBTCD_RESET_INTERRUPT_MASK         0x02    /* reset interrupt mask */
#define USBTCD_SUSPEND_INTERRUPT_MASK       0x04    /* suspend interrupt mask */
#define USBTCD_RESUME_INTERRUPT_MASK        0x08    /* resume interrupt mask */
#define USBTCD_ENDPOINT_INTERRUPT_MASK      0x10    /* endpoint interrupt mask */

/* Endpoint interrupt status masks */
#define USBTCD_ENDPOINT_INTERRUPT_PENDING_MASK  0x01    /* endpoint interrupt */
                                                        /* pending mask */
#define USBTCD_ENDPOINT_SETUP_PID_MASK          0x02    /* setup interrupt */
#define USBTCD_ENDPOINT_OUT_PID_MASK            0x04    /* out interrupt mask */
#define USBTCD_ENDPOINT_IN_PID_MASK             0x08    /* in interrupt mask */
#define USBTCD_ENDPOINT_TRANSFER_STATUS_MASK    0x0FF0  /* endpoint transfer */
                                                        /* status mask */

/* Endpoint interrupt status error code values */
#define USBTCD_ENDPOINT_TRANSFER_SUCCESS        0x0000  /* transfer success */
#define USBTCD_ENDPOINT_DATA_TOGGLE_ERROR       0x00E0  /* data toggle error */
#define USBTCD_ENDPOINT_PID_MISMATCH            0x00F0  /* PID mismatch */
#define USBTCD_ENDPOINT_COMMN_FAULT             0x0100  /*Communication Fault*/
#define USBTCD_ENDPOINT_STALL_ERROR             0x0110  /* stall error */
#define USBTCD_ENDPOINT_DATA_OVERRUN            0x0120  /* data overrun */
#define USBTCD_ENDPOINT_DATA_UNDERRUN           0x0130  /* data underrun */
#define USBTCD_ENDPOINT_CRC_ERROR               0x0140  /* CRC error */
#define USBTCD_ENDPOINT_TIMEOUT_ERROR           0x0150  /* Time Out error */
#define USBTCD_ENDPOINT_BIT_STUFF_ERROR         0x0160  /* bit stuff error */

/* typedefs */

typedef GENERIC_HANDLE TCD_HANDLE, *pTCD_HANDLE;

/* hal isr callback */

typedef void (*USB_HAL_ISR_CALLBACK)( pVOID pHALData);

typedef struct usbHalDeviceInfo /* USBHAL_DEVICE_INFO */
    {
    UINT8   uNumberEndpoints;   /* no of endpoints supported */
    } USBHAL_DEVICE_INFO, *pUSBHAL_DEVICE_INFO;

typedef struct trbHeader    /* TRB_HEADER */
    {
    TCD_HANDLE  handle;         /* I/O caller's TCD client handle */
    UINT16      function;       /* IN   TCD function code */
    UINT16      trbLength;      /* IN   Length of the total TRB */
    } TRB_HEADER, *pTRB_HEADER;

typedef struct trbAttach    /* TRB_ATTACH */
    {
    TRB_HEADER          header;     /* I/0 TRB header */
    pVOID               tcdParam;   /* IN TCD specific info */
    USB_HAL_ISR_CALLBACK usbHalIsr; /* IN isr callback function of HAL */
    pVOID               usbHalIsrParam; /* IN isr callback function parameter */
    pUSBHAL_DEVICE_INFO pHalDeviceInfo; /* OUT HAL specific device info ptr */
    pUSB_APPLN_DEVICE_INFO pDeviceInfo; /* OUT device specific info ptr*/
    } TRB_ATTACH, *pTRB_ATTACH;

typedef struct trbDetach    /* TRB_DETACH */
    {
    TRB_HEADER  header;             /* IN TRB header */
    } TRB_DETACH, *pTRB_DETACH;

typedef struct trbEnableDisable /* TRB_ENABLE_DISABLE */
    {
    TRB_HEADER  header;             /* IN TRB header */
    } TRB_ENABLE_DISABLE, *pTRB_ENABLE_DISABLE;

typedef struct trbAddressSet    /* TRB_ADDRESS_SET */
    {
    TRB_HEADER  header;         /* IN TRB header */
    UINT8       deviceAddress;  /* IN new device address */
    } TRB_ADDRESS_SET, *pTRB_ADDRESS_SET;

typedef struct trbSignalResume  /* TRB_SIGNAL_RESUME */
    {
    TRB_HEADER  header;         /* IN TRB header */
    } TRB_SIGNAL_RESUME, *pTRB_SIGNAL_RESUME;

typedef struct trbDeviceFeatureSetClear /* TRB_DEVICE_FEATURE_SET_CLEAR */
    {
    TRB_HEADER  header;             /* IN TRB header */
    UINT16      uFeatureSelector;   /* IN Feature to be set or cleared */
    UINT8       uTestSelector;      /* IN Test Selector Value */
    } TRB_DEVICE_FEATURE_SET_CLEAR,*pTRB_DEVICE_FEATURE_SET_CLEAR;

typedef struct trbCurrentFrameGet   /* TRB_CURRENT_FRAME_GET */
    {
    TRB_HEADER  header;             /* IN TRB header */
    UINT16      frameNo;            /* OUT  current frame number */
    } TRB_CURRENT_FRAME_GET, *pTRB_CURRENT_FRAME_GET;

typedef struct trbEndpointAssign    /* TRB_ENDPOINT_ASSIGN */
    {
    TRB_HEADER  header;                 /* IN TRB header */
    pUSB_ENDPOINT_DESCR pEndpointDesc;  /* IN Ptr to Endpoint Descriptor */
    UINT32      uConfigurationValue;    /* IN configuration calue */
    UINT32      uInterface;             /* IN interface number of endpoint */
    UINT32      uAltSetting;            /* IN alternate setting for interface */
    USB_TARG_PIPE   pipeHandle;         /* OUT pipe handle */
    }TRB_ENDPOINT_ASSIGN, *pTRB_ENDPOINT_ASSIGN;

typedef struct trbEndpointRelease   /* TRB_ENDPOINT_RELEASE */
    {
    TRB_HEADER  header;                 /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    } TRB_ENDPOINT_RELEASE, *pTRB_ENDPOINT_RELEASE;

typedef struct trbEndpointStateSet  /* TRB_ENDPOINT_STATE_SET */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    UINT16          state;              /* IN state of pipe TCD_ENDPOINT_xxxx */
    } TRB_ENDPOINT_STATE_SET, *pTRB_ENDPOINT_STATE_SET;

typedef struct trbEndpointStatusGet /* TRB_ENDPOINT_STATUS_GET */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    pUINT8          pStatus;            /* OUT ptr to status of pipe */
    } TRB_ENDPOINT_STATUS_GET, *pTRB_ENDPOINT_STATUS_GET;

typedef struct trbIsBufferEmpty     /* TRB_IS_BUFFER_EMPTY */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    BOOL            bufferEmpty;        /* OUT if buffer is empty TRUE */
    } TRB_IS_BUFFER_EMPTY, *pTRB_IS_BUFFER_EMPTY;

typedef struct trbCopyDataFromEpbuf /* TRB_COPY_DATA_FROM_EPBUF */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    UCHAR *         pBuffer;            /* IN buffer pointer */
    UINT32          uActLength;         /* I/O length of buffer before */
                                        /* function call, actual data length */
                                        /* copied on function call return */
    } TRB_COPY_DATA_FROM_EPBUF, *pTRB_COPY_DATA_FROM_EPBUF;

typedef struct trbCopyDataToEpbuf   /* TRB_COPY_DATA_TO_EPBUF */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    UCHAR *         pBuffer;            /* IN buffer pointer */
    UINT32          uActLength;         /* I/O length of buffer before */
                                        /* function call, actual data length */
                                        /* copied on function call return */
    BOOL            zeroLengthPacket;   /* IN , if TRUE zero length packet */
                                        /* is sent */
    } TRB_COPY_DATA_TO_EPBUF, *pTRB_COPY_DATA_TO_EPBUF;

typedef struct trbInterruptStatusGetClear /* TRB_INTERRUPT_STATUS_GET_CLEAR */
    {
    TRB_HEADER      header;             /* IN TRB header */
    UINT32          uInterruptStatus;   /* I/O interrupt bit mask */
    } TRB_INTERRUPT_STATUS_GET_CLEAR, *pTRB_INTERRUPT_STATUS_GET_CLEAR;

typedef struct trbEndpointInterruptStatusGet /*TRB_ENDPOINT_INTERRUPT_STATUS_GET*/
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    UINT32          uEndptInterruptStatus;  /* OUT endpoint interrupt status */
    } TRB_ENDPOINT_INTERRUPT_STATUS_GET,*pTRB_ENDPOINT_INTERRUPT_STATUS_GET;

typedef struct trbEndpointInterruptStatusClear /* TRB_ENDPOINT_INTERRUPT_STATUS_CLEAR */
    {
    TRB_HEADER      header;             /* IN TRB header */
    USB_TARG_PIPE   pipeHandle;         /* IN  pipe handle */
    } TRB_ENDPOINT_INTERRUPT_STATUS_CLEAR,*pTRB_ENDPOINT_INTERRUPT_STATUS_CLEAR;

typedef struct trbHandleDisconnectInterrupt /* TRB_HANDLE_DISCONNECT_INTERRUPT */
    {
    TRB_HEADER      header;             /* IN TRB header */
    } TRB_HANDLE_DISCONNECT_INTERRUPT,*pTRB_HANDLE_DISCONNECT_INTERRUPT;

typedef struct trbHandleResetInterrupt  /* TRB_HANDLE_RESET_INTERRUPT */
    {
    TRB_HEADER      header;             /* IN TRB header */
    UINT32          uSpeed;             /* OUT Operating speed of the device */
    } TRB_HANDLE_RESET_INTERRUPT, *pTRB_HANDLE_RESET_INTERRUPT;

typedef struct trbHandleResumeInterrupt /* TRB_HANDLE_RESUME_INTERRUPT */
    {
    TRB_HEADER      header;             /* IN TRB header */
    } TRB_HANDLE_RESUME_INTERRUPT, *pTRB_HANDLE_RESUME_INTERRUPT;

typedef struct trbHandleSuspendInterrupt  /* TRB_HANDLE_SUSPEND_INTERRUPT */
    {
    TRB_HEADER      header;             /* IN TRB header */
    } TRB_HANDLE_SUSPEND_INTERRUPT,*pTRB_HANDLE_SUSPEND_INTERRUPT;

#ifdef  __cplusplus
}
#endif

#endif	/* __INCusbTcdh */
