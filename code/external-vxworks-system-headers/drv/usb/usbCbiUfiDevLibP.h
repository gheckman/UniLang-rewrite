/* usbCbiUfiDevLibP.h - USB CBI Mass Storage UFI driver private header */

/*
 * Copyright (c) 2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,22sep05,hch  Add usbCbiXbdTest, usbCbiXbdEject, usbCbiXbdMediaTest
01b,08aug05,hch  change return value of usbCbiUfiDevIoctl from STATUS to int
01a,01aug05,hch  Created.
*/

#ifndef __INCusbCbiUfiDevLibPh
#define __INCusbCbiUfiDevLibPh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* function prototype */

int usbCbiUfiDevIoctl (XBD *, int, void *);
STATUS usbCbiUfiDevStChk (XBD *);
int usbCbiXbdTest (pUSB_CBI_UFI_DEV);
int usbCbiXbdEject (pUSB_CBI_UFI_DEV);
int usbCbiXbdMediaTest (pUSB_CBI_UFI_DEV);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCusbCbiUfiDevLibh */

