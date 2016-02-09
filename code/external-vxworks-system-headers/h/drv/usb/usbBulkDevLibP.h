/* usbBulkDevLibP.h - USB Bulk only Mass Storage class private header file */

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
01d,07oct05,hch  Add usbBulkStatusCheckBypass function definition
01c,21sep05,hch  Add usbBulkXbdTest, usbBulkXbdEject, usbBulkXbdMediaTest 
01b,08aug05,hch  change return value of usbBulkDevIoctl from STATUS to int
01a,01aug05,hch  Created.
*/

#ifndef __INCusbBulkDevLibPh
#define __INCusbBulkDevLibPh


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* function prototype */ 

int usbBulkDevIoctl (XBD * pBlkDev, int request, void * someArg);
STATUS usbBulkDevStatusChk (XBD *);
int usbBulkXbdTest (pUSB_BULK_DEV_XBD_LUN);
int usbBulkXbdEject (pUSB_BULK_DEV_XBD_LUN);
int usbBulkXbdMediaTest (pUSB_BULK_DEV_XBD_LUN);
BOOL usbBulkStatusCheckBypass();

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCusbBulkDevLibPh */
