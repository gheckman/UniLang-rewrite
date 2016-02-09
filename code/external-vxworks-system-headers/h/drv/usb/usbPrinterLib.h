/* usbPrinterLib.h - USB printer SIO driver definitions */

/*
 * Copyright (c) 1999-2001, 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,13jan10,ghs  vxWorks 6.9 LP64 adapting
01g,11may04,hch  merge after D12 driver testing
01f,04may04,???  Support for cancelling a print job
01e,18sep01,wef  merge from wrs.tor2_0.usb1_1-f for veloce
01d,07may01,wef  changed module number to be (module num << 8) | M_usbHostLib
01c,02may01,wef  changed module number to be M_<module> + M_usbHostLib
01b,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes
01a,01sep99,rcb  First.
*/

#ifndef __INCusbPrinterLibh
#define __INCusbPrinterLibh


/* includes */

#include "sioLib.h"
#include "usb/usbPlatform.h"
#include "vwModNum.h"           /* USB Module Number Def's */

#ifdef  __cplusplus
extern "C" {
#endif


/* defines */

/* usbPrinterLib error values */

/*
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */

#define USB_PRINTER_SUB_MODULE 7

#define M_usbPrinterLib ( ( USB_PRINTER_SUB_MODULE   << 8) | M_usbHostLib )

#define usbPrnErr(x)    (M_usbPrinterLib | (x))

#define S_usbPrinterLib_NOT_INITIALIZED     usbPrnErr (1)
#define S_usbPrinterLib_BAD_PARAM           usbPrnErr (2)
#define S_usbPrinterLib_OUT_OF_MEMORY       usbPrnErr (3)
#define S_usbPrinterLib_OUT_OF_RESOURCES    usbPrnErr (4)
#define S_usbPrinterLib_GENERAL_FAULT       usbPrnErr (5)
#define S_usbPrinterLib_QUEUE_FULL          usbPrnErr (6)
#define S_usbPrinterLib_QUEUE_EMPTY         usbPrnErr (7)
#define S_usbPrinterLib_NOT_IMPLEMENTED     usbPrnErr (8)
#define S_usbPrinterLib_USBD_FAULT          usbPrnErr (9)
#define S_usbPrinterLib_NOT_REGISTERED      usbPrnErr (10)
#define S_usbPrinterLib_NOT_LOCKED          usbPrnErr (11)

/* USB_PRN_xxxx define "attach codes" used by USB_PRN_ATTACH_CALLBACK. */

#define USB_PRN_ATTACH  0       /* new printer attached */
#define USB_PRN_REMOVE  1       /* printer has been removed */
                                /* SIO_CHAN no longer valid */

/* IOCTL codes unique to usbPrinterLib. */

#define SIO_USB_PRN_DEVICE_ID_GET   0x8000
#define SIO_USB_PRN_PROTOCOL_GET    0x8001
#define SIO_USB_PRN_STATUS_GET      0x8002
#define SIO_USB_PRN_SOFT_RESET      0x8003
#define SIO_USB_PRN_CANCEL          0x8004

/* typedefs */

/* USB_PRN_ATTACH_CALLBACK defines a callback routine which will be
 * invoked by usbPrinterLib.c when the attachment or removal of a printer
 * is detected.  When the callback is invoked with an attach code of
 * USB_PRN_ATTACH, the pSioChan points to a newly created SIO_CHAN.  When
 * the attach code is USB_PRN_REMOVE, the pSioChan points to a pSioChan
 * for a printer which is no longer attached.
 */

typedef VOID (*USB_PRN_ATTACH_CALLBACK)
    (
    pVOID arg,                  /* caller-defined argument */
    SIO_CHAN *pChan,            /* pointer to affected SIO_CHAN */
    UINT16 attachCode           /* defined as USB_PRN_xxxx */
    );

/* function prototypes */

STATUS usbPrinterDevInit (void);
STATUS usbPrinterDevShutdown (void);

STATUS usbPrinterDynamicAttachRegister
    (
    USB_PRN_ATTACH_CALLBACK callback,   /* new callback to be registered */
    pVOID arg                           /* user-defined arg to callback */
    );

STATUS usbPrinterDynamicAttachUnRegister
    (
    USB_PRN_ATTACH_CALLBACK callback,   /* callback to be unregistered */
    pVOID arg                           /* user-defined arg to callback */
    );

STATUS usbPrinterSioChanLock
    (
    SIO_CHAN *pChan                     /* SIO_CHAN to be marked as in use */
    );

STATUS usbPrinterSioChanUnlock
    (
    SIO_CHAN *pChan                     /* SIO_CHAN to be marked as unused */
    );

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbPrinterLibh */

/* End of file. */

