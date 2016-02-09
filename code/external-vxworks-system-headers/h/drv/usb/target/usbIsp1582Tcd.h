/* usbIsp1582Tcd.h - Definitions used by PDIUSBD12 TCD */

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01d,02aug04,mta  Modification History Changes
01c,19jul04,ami  Coding Convention Changes
01b,01jun04,mta  Changes for Interrupt Mode
01a,21apr04,ami  First.
*/

/*
DESCRIPTION

Defines structures used by Philips PDIUSBD12 TCD.
*/


#ifndef __INCusbIsp1582Tcdh
#define __INCusbIsp1582Tcdh

#ifdef	__cplusplus
extern "C" {
#endif

/* Bitmap for IN and OUT Endpoints Supported */

#define USB_ISP1582_TCD_OUT_ENDPOINT 0x000000FF /* bitmap for Out endpoint */
#define USB_ISP1582_TCD_IN_ENDPOINT  0x00FF0000  /* bitmap for In endpoint */


/* typedefs */

typedef struct usbTcdIsp1582Target    /* USB_TCD_ISP1582_TARGET */
    {
    UINT32	ioBase;               /* IO Base */
    UINT16	irq;                  /* IRQ Number */
    UINT16	dma;                  /* DMA Channel */
    USB_HAL_ISR_CALLBACK usbHalIsr;   /* HAL ISR Callback */
    pVOID	usbHalIsrParam;       /* HAL ISR Parameter */
    UINT8	deviceAddress;        /* Device Address */
    UINT32	bufSize;              /* Buffer Size */
    UINT16	endpointIndexInUse;   /* Endpoint Index being used */
    BOOL	dmaInUse;             /* Flag for DMA in use or not */
    UINT8	dmaEndpointId;        /* DMA Endpoint ID */
    UINT8	dmaEndptNotInUse;     /* DMA Endpoint not being used */
    BOOL	dmaEot;               /* DMA End of Transfer */
    UINT16	endptIntPending;      /* Bitmap showing Pending Endpoint Int */
    BOOL	setupIntPending;      /* Setup Interrupt occured */
    UINT16	dmaXferLen;           /* DMA Transfer Length */
    BOOL	controlINStatusPending; /* Control IN Status Pending Report */
    BOOL	controlOUTStatusPending;/* Control OUT Status Pending Report */
#ifdef ISP1582_POLLING
    THREAD_HANDLE	threadId;     /* Polling Mode Thread Handle */
#endif
    } USB_TCD_ISP1582_TARGET, *pUSB_TCD_ISP1582_TARGET;

typedef struct usbTcdIsp1582Endpoint   /* USB_TCD_ISP1582_ENDPOINT */
    {
    UINT8	endpointIndex;         /* Endpoint Index */
    UINT16	transferType;          /* Endpoint Transfer Type */
    UINT8	direction;             /* Direction */
    UINT16	maxPacketSize;         /* Max Packet Size */
    BOOL	isDoubleBufSup;        /* Double Buffering */
    } USB_TCD_ISP1582_ENDPOINT, *pUSB_TCD_ISP1582_ENDPOINT;

/* function declaration */
extern VOID usbTcdIsp1582Isr(pVOID param);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbIsp1582Tcdh */
