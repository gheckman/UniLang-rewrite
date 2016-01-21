/* usbTgtKbd.h - USB Target Keyboard Class library module common header file */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,04aug12,s_z  Adjust the usbtgt_kbd_dev sturcture
01c,04aug11,ljg  Add HID Desc and Report Desc (WIND00291023)
01b,12jul11,s_z  Import usbTgtKbdInit and usbTgtKbdUnInit routines
01a,11apr11,ljg  written
*/

#ifndef __INCusbTgtKbdh
#define __INCusbTgtKbdh

/* includes */

#include <usb/usbTgt.h>

#ifdef __cplusplus
extern "C" {
#endif

/* keyboard interface */

#define USBTGT_KBD_INTERFACE_NUM                   0          /* interface number */
#define USBTGT_KBD_INTERFACE_ALT_SETTING           0          /* alternate setting */
#define USBTGT_KBD_NUM_ENDPOINTS                   1          /* number of endpoints */
#define USBTGT_KBD_INT_IN_ENDPOINT_NUM             0x81       /* INT IN endpoint number */
#define USBTGT_KBD_INTERRUPT_ENDPOINT_INTERVAL     0x0A       /* milliseconds */

#define USBTGT_KBD_BINARY_CODED_DECIMAL            0x101      /* bcdHID */
#define USBTGT_KBD_HARDWARE_TARGET_COUNTRY         0          /* bCountryCode */
#define USBTGT_KBD_DESCRIPTORS_NUMBER              0x01       /* bNumDescriptors */
#define USBTGT_KBD_REPORT_DESCRIPTOR_LENGTH        0x3F       /* wDescriptorLength */

/* structure of target Kbd device */

typedef struct usbtgt_kbd_dev
    {
    NODE                  kbdNode;
    USB_TARG_CHANNEL      targChannel;           /* Target channel */
    UINT32                uDeviceFeature;        /* Device feature */
    USB_TARG_PIPE         intInPipeHandle;       /* Bulk pipe handle */
    HID_KBD_BOOT_REPORT   intInBfr;              /* Buffer used by Interrupt In transaction */
    SEM_HANDLE            intInErpSem;           /* Interrupt In transfer mutex */
    BOOL                  bIntInErpUsed;
    UINT8                 uIntInPipeStatus;      /* Interrupt In pipe stall or not */
    UINT8                 uAlternateSetting;     /* Current altsetting value */
    UINT8                 uConfigurationValue;   /* Configuration value */
    UINT8                 uInterfaceNubmer;      /* Number of interface which holds this endpoint */
    USB_ERP               intInErp;              /* Bulk ERP */
    }USBTGT_KBD_DEV,*pUSBTGT_KBD_DEV;

typedef struct usr_usbTgt_kbd_config
    {
    char  tcdName[USBTGT_MAX_NAME_SZ];           /* The TCD name to be attached */
    UINT8 uTcdUnit;                              /* The TCD unit to be attached */
    char  kbdName[USBTGT_MAX_NAME_SZ];           /* The Kbd function driver name */
    UINT8 uKbdUnit;                              /* The Kbd function driver unit */
    UINT8 uConfigNum;                            /* The configuration num build in the TCD */
    }USR_USBTGT_KBD_CONFIG, *pUSR_USBTGT_KBD_CONFIG;

typedef enum usbtgt_kbd_pipe_state
    {
    USBTGT_KBD_PIPE_IDLE    = 0,
    USBTGT_KBD_PIPE_STALL   = 1,
    USBTGT_KBD_PIPE_UNSTALL = 2,
    USBTGT_KBD_PIPE_BUSY    = 3
    }USBTGT_KBD_PIPE_STATE;

IMPORT STATUS usbTgtKbdInit
    (
    int devCount
    );

IMPORT STATUS usbTgtKbdUnInit
    (
    void
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCusbTgtKbdh */

