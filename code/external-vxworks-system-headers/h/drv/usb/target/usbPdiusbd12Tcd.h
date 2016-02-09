/* usbPdiusbd12Tcd.h - Definitions used by PDIUSBD12 TCD */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
Modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,02aug04,mta  Modification History Changes
01b,19jul04,ami Coding Convention Changes
01a,15mar04,mta First.
*/

/*
DESCRIPTION

Defines structures used by Philips PDIUSBD12 TCD.
*/

#ifndef __INCusbPdiusbd12Tcdh
#define __INCusbPdiusbd12Tcdh

/* includes */

#include "usb/target/usbTcd.h"	    /* generic TCD interface */

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* Bitmap for IN and OUT Endpoints Supported */

#define USB_PDIUSBD12_TCD_OUT_ENDPOINT 0x00000007 /* bitmap for Out endpoint */
#define USB_PDIUSBD12_TCD_IN_ENDPOINT  0x00070000  /* bitmap for In endpoint */

extern UINT32 usbPdiusbd12Debug;
/* typedefs */

/* USB_TCD_PDIUSBD12_TARGET
 *
 * USB_TCD_PDIUSBD12_TARGET is the primary data structure created to manage
 * an individual target controller.
 */

typedef struct usbTcdPdiusbd12Target    /* USB_TCD_PDIUSBD12_TARGET */
    {

    UINT32	ioBase;		/* base Address */
    UINT16	irq;		/* irq Number */
    UINT16	dma;		/* dma Channel */
    USB_HAL_ISR_CALLBACK  usbHalIsr;	/* hal Isr */
    pVOID	usbHalIsrParam;	/* isr Parameter */
    UINT8	goutByte;	/* gout byte */
    UINT8	configByte;	/* configuration byte */
    UINT8	clkDivByte;     /* clock division byte */
    UINT8	dmaByte;	/* dma byte */
    UINT16	epMainCount;	/* main endpoint count */ 
    UINT8	epMainGenericCount; /* generic count */
    UINT16	epOneAndTwoCount;   /* endpoint 1 & 2 Count */
    BOOL	dmaInUse;	/* dma inuse or not */ 
    UINT16	dmaEndpointId;	/* dma endpoint id */ 
    BOOL	dmaEot;		/* dma end of transfer */
    UINT8	endpointIndexInUse; /* endpoint indexes in use */
    UINT8	deviceAddress;	/* device address */
    UINT8	endptIntPending;/* pending endpoint interrutps */
    UINT8	uLastTransactionStatus[D12_NUM_ENDPOINTS];
				/* last transaction in endpoint */
    BOOL	setupErpPending;/* setup ERP is pending */ 

#ifdef PDIUSBD12_POLLING
    THREAD_HANDLE	threadId;	/* polling thread handler */
#endif

    } USB_TCD_PDIUSBD12_TARGET, *pUSB_TCD_PDIUSBD12_TARGET;

typedef struct usbTcdPdiusbd12Endpoint	/* USB_TCD_PDIUSBD12_ENDPOINT */
    {
    UINT8	endpointNo;	/* endpoint Number */
    UINT8	endpointIndex;	/* endpoint index */
    UINT16	dmaXfrLen;	/* dma transfer length */
    UINT16	transferType;	/* transfer type */
    UINT8	direction;	/* direction */
    UINT16	maxPacketSize;	/* max packet size */
    } USB_TCD_PDIUSBD12_ENDPOINT, *pUSB_TCD_PDIUSBD12_ENDPOINT;

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbPdiusbd12Tcdh */
