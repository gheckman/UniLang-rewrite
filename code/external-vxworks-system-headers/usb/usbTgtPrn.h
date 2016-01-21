/* usbTgtPrn.h - USB Target Printer Class library module common header file */

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
01c,04aug12,s_z  Adjust the usbtgt_prn_dev sturcture
01b,12jul11,s_z  Import usbTgtPrnInit and usbTgtPrnUnInit routines
01a,22feb11,ljg  created
*/

#ifndef __INCusbTgtPrnh
#define __INCusbTgtPrnh

/* includes */

#include <usb/usbPrinter.h>
#include <usb/usbTgt.h>

#ifdef __cplusplus
extern "C" {
#endif

/* printer configuration */

#define USBTGT_PRN_INTERFACE_NUM                       0      /* interface number */
#define USBTGT_PRN_INTERFACE_ALT_SETTING               0      /* alternate setting */
#define USBTGT_PRN_NUM_ENDPOINTS                       2      /* number of endpoints */

#define USBTGT_PRN_HIGH_SPEED_MAX_PACKET_SIZE          512    /* maximum packet size for
                                                               * the default control
                                                               * endpoint, if the device
                                                               * is operating at high
                                                               * speed
                                                               */

#define USBTGT_PRN_FULL_SPEED_MAX_PACKET_SIZE          64     /* maximum packet size for
                                                               * the default control
                                                               * endpoint, if the device
                                                               * is operating at high
                                                               * speed
                                                               */

#define USBTGT_PRN_MAX_BUFF_LEN          USBTGT_PRN_HIGH_SPEED_MAX_PACKET_SIZE

#define USBTGT_PRN_BULK_OUT_ENDPOINT_NUM     0x01             /* PIO mode bulk out endpoint number */

#define USBTGT_PRN_BULK_IN_ENDPOINT_NUM      0x81             /* PIO mode bulk in endpoint number */

#define USBTGT_PRN_BULK_TASK_PRIORITY        254              /* PIO - Bulk OUT endpoint ID */

#define USBTGT_PRN_DEFAULT_TIMEOUT           1000             /* Default bulk in/out time out */


#define USBTGT_PRN_MAX_ERP_BUF_SIZE       0x800

typedef struct usr_usbTgt_prn_config
    {
    char  tcdName[USBTGT_MAX_NAME_SZ];                        /* The TCD name to be attached */
    UINT8 uTcdUnit;                                           /* The TCD unit to be attached */
    char  prnName[USBTGT_MAX_NAME_SZ];                        /* The Prn function driver name */
    UINT8 uPrnUnit;                                           /* The Prn function driver unit */
    UINT8 uConfigNum;                                         /* The configuration num build in the TCD */
    char  prnCapsString[USB_PRN_MAX_DEVICE_ID_LEN - 2];       /* The Prn capabilities string exclude 2 bytes length */
    }USR_USBTGT_PRN_CONFIG, *pUSR_USBTGT_PRN_CONFIG;

#define USBTGT_PRN_COUNT NELEMENTS(usrUsbTgtPrnConfigTable)

/* structure of target prn device */

typedef struct usbtgt_prn_dev
    {
    NODE                     prnNode;                  
    USB_TARG_CHANNEL         targChannel;              /* Target channel */
    MSG_Q_ID                 prnTaskMsgQID;            /* Task msgQ id */
    OS_THREAD_ID             prnTaskID;                /* Tasl ID */
    USB_PRINTER_PORT_STATUS  prnState;
    UINT8                    uAlternateSetting;        /* Current altsetting value */
    UINT8                    uConfigurationValue;      /* Configuration value */
    UINT8                    uInterfaceNubmer;         /* Number of interface which holds this endpoint */
    int                      deviceTimeout;            /* Timeout (ms) to wait reqs. */
    UINT32                   uDeviceFeature;           /* Device feature */
                             
    USB_TARG_PIPE            bulkOutPipeHandle;        /* Bulk pipe handle */
    USB_TARG_PIPE            bulkInPipeHandle;         /* Bulk pipe handle */
    USB_ERP                  bulkOutErp;               /* Bulk ERP */
    USB_ERP                  bulkInErp;                /* Bulk ERP */
    UINT8 *                  pBulkOutBuf;              
    UINT8 *                  pBulkInBuf;               
    SEM_HANDLE               bulkOutErpSem;            /* Bulk Out transfer mutex */
    SEM_HANDLE               bulkInErpSem;             /* Bulk In transfer mutex */
    UINT8                    uBulkOutPipeStatus;
    UINT8                    uBulkInPipeStatus;
    BOOL                     bBulkOutErpUsed;
    BOOL                     bBulkInErpUsed;
    BOOL                     bBulkOutBufValid;
    BOOL                     bBulkInBufValid;
    }USBTGT_PRN_DEV,*pUSBTGT_PRN_DEV;

/* The notify command */

typedef enum usbtgt_prn_notify_code
    {
    USBTGT_PRN_NOTIFY_UNKNOWN              = (0),
    USBTGT_PRN_NOTIFY_RESET                = (1),
    USBTGT_PRN_NOTIFY_BULK_IN              = (6),
    USBTGT_PRN_NOTIFY_BULK_OUT             = (7)
    }USBTGT_PRN_NOTIFY_CODE;

/* Notify info data structure */

typedef struct usbtgt_prn_notify_info
    {
    struct usbtgt_prn_dev *    pUsbTgtPrn;       /* PRN device pointer */
    USBTGT_PRN_NOTIFY_CODE     notifyCode;       /* The code of the notification */
    } USBTGT_PRN_NOTIFY_INFO, *pUSBTGT_PRN_NOTIFY_INFO;

typedef enum usbtgt_prn_pipe_state
    {
    USBTGT_PRN_PIPE_IDLE    = 0,
    USBTGT_PRN_PIPE_STALL   = 1,
    USBTGT_PRN_PIPE_UNSTALL = 2,
    USBTGT_PRN_PIPE_BUSY    = 3
    }USBTGT_PRN_PIPE_STATE;

IMPORT STATUS usbTgtPrnInit
    (
    int devCount
    );
IMPORT STATUS usbTgtPrnUnInit
    (
    void
    );


#ifdef __cplusplus
}
#endif

#endif /* __INCusbTgtPrnh */

