/* usbTgtSer.h - usb target serial emulator common header file */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,18may12,s_z  Add support for USB 3.0 target (WIND00326012)
01e,08apr11,ghs  Fix code coverity issue(WIND00264893)
01d,22mar11,ghs  Fix structure declare error
01c,09mar11,ghs  Adapt code format
01b,07mar11,ghs  Fix code review issues
01a,26jan11,ghs  written
*/

#ifndef __INCusbTgtSerh
#define __INCusbTgtSerh

/* includes */

#include <usb/usbTgt.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MAX_TCD_NAME_LEN                   50

#define USBTGT_SER_MAX_BUFF_LEN            512
#define USBTGT_SER_MAX_ERP_BUFF_SIZE       2048

/* typedefs */

/* structure of target serial device */

typedef struct usbtgt_ser_dev
    {
    USB_TARG_CHANNEL        targChannel;    /* Target channel */
    UINT8                   uConfiguration;
    UINT8                   uControlIfAltSetting;
    UINT8                   uDataIfAltSetting;

    USB_TARG_PIPE           bulkOutPipe;
    USB_ERP                 bulkOutErp;
    BOOL                    bulkOutInUse;
    BOOL                    bulkOutBfrValid;
    BOOL                    bulkOutStallStatus;

    USB_TARG_PIPE           bulkInPipe;
    USB_ERP                 bulkInErp;
    BOOL                    bulkInInUse;
    BOOL                    bulkInBfrValid;
    BOOL                    bulkInStallStatus;

    USB_ERP                 intInErp;
    BOOL                    intInInUse;
    pVOID                   intInPipe;

    UINT8 *                 bulkOutData;
    BOOL                    bulkOutDataInUse;
    UINT8 *                 bulkInData;
    BOOL                    bulkInDataInUse;

    struct usbtgt_acm_sio_chan * pChan;
    } USBTGT_SER_DEV, *pUSBTGT_SER_DEV;

/* state of emulator port */

typedef enum usbTgtDevPortState
    {
    USBTGT_SER_PORT_CLOSE = 0,
    USBTGT_SER_PORT_CONNECT = 1,
    USBTGT_SER_PORT_OPEN = 2
    } USB_TGT_SER_PORT_STATE;

/* sioChan structure for device and SIO libs */

typedef struct usbtgt_acm_sio_chan
    {
    /* SIO_DRV_FUNCS *MUST* be first */

    SIO_DRV_FUNCS *         pDrvFuncs;        /* driver functions */

    /* callbacks */

    STATUS               (* getTxChar) (void *, char *);
    STATUS               (* putRcvChar) (void *, char);
    void *                  getTxArg;
    void *                  putRcvArg;

    /* misc */

    VXB_DEVICE_ID           pDev;           /* bus subsystem: device ID */
    int                     channelNo;      /* channel number */
    int                     baudFreq;       /* current baud rate */
    int                     mode;           /* current mode (interrupt or poll) */
    uint_t                  options;        /* Hardware options */
    THREAD_HANDLE           txThread;
    int                     devId;

    USB_CDC_LINE_CODING     lineCoding;
    UINT16                  controlLineStae;
    BOOL                    onClosing;
    int                     ttyNum;

    USB_TGT_SER_PORT_STATE  portState;

    char *                  dummyBfr;
    size_t                  dummyBfrSize;
    size_t                  dummyBfrDataSize;

    UINT32                  reqTxLen;
    UINT32                  actTxLen;
    UINT32                  actRxLen;
    struct usbtgt_ser_dev * pUsbTgtSerDev;
    } USBTGT_ACM_SIO_CHAN;

/* globals */

void usbTgtSerTtyRemove(int);

void usbTgtSerInstInit(VXB_DEVICE_ID);

void usbTgtSerInstInit2(VXB_DEVICE_ID);

void usbTgtSerInstConnect(VXB_DEVICE_ID);

void usbTgtSerBulkInErpCallback(pVOID);

void usbTgtSerBulkOutErpCallback(pVOID);

void usbTgtSerSioIntRcv(USBTGT_ACM_SIO_CHAN *);

void usbTgtSerSioFlushBuffer(USBTGT_ACM_SIO_CHAN *);

void usbTgtSerTest(char *);

BOOL usbTgtSerPortStateCheck(USBTGT_ACM_SIO_CHAN *);

STATUS usbTgtSerInit(int);

STATUS usbTgtSerUnInit(int);

STATUS usbTgtSerBulkInErpInit(pUSBTGT_SER_DEV, UINT8 *, UINT32,
                              ERP_CALLBACK, pVOID);

STATUS usbTgtSerBulkOutErpInit(pUSBTGT_SER_DEV, UINT8 *, UINT32,
                               ERP_CALLBACK, pVOID);

STATUS usbTgtSerBulkInTransfer(pUSBTGT_SER_DEV, char *, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __INCusbTgtSerh */

