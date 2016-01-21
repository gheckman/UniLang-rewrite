/* usbLib.h - USB utility functions */

/*
 * Copyright (c) 1999-2000, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* Copyright 1999-2000, 2010 Wind River Systems, Inc.

   This software includes software licensed to Wind River Systems, Inc.
   by Wipro, Ltd. Wind River licensees may use this software according
   to the terms of their Wind River license agreement(s) applicable to
   this software.
*/

/*
Modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,13jan10,ghs  vxWorks 6.9 LP64 adapting
01d,26jan00,rcb  Modify usbRecurringTime() to accept <bandwidth> instead
                 of <bytesPerFrame>.
                 Add usbDescrCopy32() and usbDescrStrCopy32().
01c,17jan99,rcb  Add usbConfigDescrGet() function.
01b,23nov99,rcb  Add usbRecurringTime() function.
01a,16jul99,rcb  First.
*/

#ifndef __INCusbLibh
#define __INCusbLibh


/* includes */

#include "usb/usb.h"
#include "usb/usbHid.h"
#include "usb/usbdLib.h"
#include "usb/usbDescrCopyLib.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* function prototypes */

UINT32 usbTransferTime
    (
    UINT16 transferType,    /* transfer type */
    UINT16 direction,       /* transfer direction */
    UINT16 speed,           /* speed of pipe */
    UINT32 bytes,           /* number of bytes for packet to be calc'd */
    UINT32 hostDelay,       /* host controller delay per packet */
    UINT32 hostHubLsSetup   /* host controller time for low-speed setup */
    );

UINT32 usbRecurringTime
    (
    UINT16 transferType,    /* transfer type */
    UINT16 direction,       /* transfer direction */
    UINT16 speed,           /* speed of pipe */
    UINT16 packetSize,      /* max packet size for endpoint */
    UINT32 bandwidth,       /* number of bytes to transfer per second */
    UINT32 hostDelay,       /* host controller delay per packet */
    UINT32 hostHubLsSetup   /* host controller time for low-speed setup */
    );

pVOID usbDescrParseSkip
    (
    pUINT8 *ppBfr,          /* buffer to parse */
    pUINT16 pBfrLen,        /* length of buffer to parse */
    UINT8 descriptorType    /* type of descriptor being sought */
    );

pVOID usbDescrParse
    (
    pUINT8 pBfr,            /* buffer to parse */
    UINT16 bfrLen,          /* length of buffer to parse */
    UINT8 descriptorType    /* type of descriptor being sought */
    );

STATUS usbConfigCountGet
    (
    USBD_CLIENT_HANDLE usbdClientHandle,    /* caller's USBD client handle */
    USBD_NODE_ID nodeId,                    /* device node ID */
    pUINT16 pNumConfig                      /* bfr to receive nbr of config */
    );

STATUS usbConfigDescrGet
    (
    USBD_CLIENT_HANDLE usbdClientHandle,    /* caller's USBD client handle */
    USBD_NODE_ID nodeId,                    /* device node ID */
    UINT16 cfgNo,                           /* specifies configuration nbr */
    pUINT16 pBfrLen,                        /* receives length of buffer */
    pUINT8 *ppBfr                           /* receives pointer to buffer */
    );

STATUS usbHidReportSet
    (
    USBD_CLIENT_HANDLE usbdClientHandle,    /* caller's USBD client handle */
    USBD_NODE_ID nodeId,                    /* desired node */
    UINT16 interface,                       /* desired interface */
    UINT16 reportType,                      /* report type */
    UINT16 reportId,                        /* report Id */
    pUINT8 reportBfr,                       /* report value */
    UINT16 reportLen                        /* length of report */
    );

STATUS usbHidIdleSet
    (
    USBD_CLIENT_HANDLE usbdClientHandle,    /* caller's USBD client handle */
    USBD_NODE_ID nodeId,                    /* desired node */
    UINT16 interface,                       /* desired interface */
    UINT16 reportId,                        /* desired report */
    UINT16 duration                         /* idle duration */
    );

STATUS usbHidProtocolSet
    (
    USBD_CLIENT_HANDLE usbdClientHandle,    /* caller's USBD client handle */
    USBD_NODE_ID nodeId,                    /* desired node */
    UINT16 interface,                       /* desired interface */
    UINT16 protocol                         /* USB_HID_PROTOCOL_xxxx */
    );

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbLibh */

/* End of file. */

