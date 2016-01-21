/* usbHalCommon.h - Defines structures/interfaces used by HAL and above layers */

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01c,03aug04,mta  Modification History Changes
01b,19jul04,ami  Coding Convention Changes
01a,04mar04,mta  First.
*/

/*
DESCRIPTION

Defines structures/interfaces used by Hardware Adaption Layer (HAL) and above
layers.
*/


#ifndef __INCusbHalCommonh
#define __INCusbHalCommonh

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* Device features */
#define USB_FEATURE_DEVICE_REMOTE_WAKEUP	0x01  /* remote wake up */
#define USB_FEATURE_TEST_MODE			0x02  /* test mode feature */
#define USB_FEATURE_USB20			0x04  /* USB 2.0 Device */

/* Device speeds */
#define USB_TCD_FULL_SPEED	(UINT8)0x00    /* full speed device */
#define USB_TCD_LOW_SPEED	(UINT8)0x01    /* low speed device */
#define USB_TCD_HIGH_SPEED	(UINT8)0x02    /* high speed device */

/* typedefs */

typedef struct usbApplnDeviceInfo	/* USB_APPLN_DEVICE_INFO */
    {
    UINT32	uDeviceFeature; /* bitmap giving featues supported by device */
    UINT32	uEndpointNumberBitmap; /* bitmap giving endpoint numbers */
                                       /* supported by device */
    }USB_APPLN_DEVICE_INFO, *pUSB_APPLN_DEVICE_INFO;

/* primary TCD entry point */

typedef STATUS (*USB_TCD_EXEC_FUNC) (pVOID pTrb);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbHalCommomh */
