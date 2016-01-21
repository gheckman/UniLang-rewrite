/* usbNET2280Tcd.h - Definitions used by NET2280 TCD */

/*
 * Copyright (c) 2004-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01j,29apr10,pad  Moved extern C statement after include statements.
01i,13jan10,ghs  vxWorks 6.9 LP64 adapting
01h,17nov05,ami  Datatype for dmaTransferLength changed to UINT32 (SPR
                 #115172)
01g,30sep04,pdg  DMA testing fix
01f,23sep04,pdg  Fix for short packet handling
01e,22sep04,pdg  Fix for setting the address
01d,21sep04,pdg  Full speed testing fixes
01c,08sep04,ami  Code Review Comments Incorporated
01b,03sep04,gpg  incorporated the design changes
01a,30jun04,pmr  adapted from usbisp1582Tcd.h, version 01b.
*/

/*
DESCRIPTION

Defines structures used by NetChip NET2280 TCD.
*/

#ifndef __INCusbNET2280Tcdh
#define __INCusbNET2280Tcdh

/* includes */

#include "usbTcdNET2280Lib.h"
#include "usbNET2280.h"

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define USB_NET2280_TCD_ENDPOINT_BITMAP    0x007F007F

/* Endpoint Direction */

#define USB_TCD_ENDPT_OUT                    0       /* direction -OUT */
#define USB_TCD_ENDPT_IN                     1       /* direction - IN */

/* typedefs */

/*
 * USB_TCD_NET2280_TARGET is a structure maintained by the net2280 TCD
 * for holding information required for the net2280 Target controller
 * operation.
 */

typedef struct usbTcdNET2280Target
    {
    UINT32  ioBase[NET2280_NO_OF_PCI_BADDR];	/* IO base array */
    UINT8	irq;				/* IRQ value */
    USB_HAL_ISR_CALLBACK	usbHalIsr;	/* HAL ISR pointer */
    pVOID	usbHalIsrParam;			/* HAL ISR parameter */
    UINT8	endpointIndexInUse;		/* bitmap for endpoint usage */
    UINT8	endptIntPending;		/*
						 * bitmap for endpoint
						 * interrupts.
						 */
    BOOL	setupIntPending; 		/*
						 * flag indicating a
						 * setup interrupt.
						 */
    UINT8	speed;  	                /* TC operational speed */
    UINT8	dmaEot; 			/*
				                 * bitmap
						 * for dma EOTs on endpoints
						 */
    BOOL	statusINPending;		/*
						 * Flag indicating that
						 * status IN is pending
						 */
    BOOL	statusOUTPending;		/*
						 * Flag indicating that
						 * status OUT is pending
						 */

    UINT32	addressTobeSet;			/*
						 * Value to be written to
						 * OURADDR register.
						 */

    } USB_TCD_NET2280_TARGET, *pUSB_TCD_NET2280_TARGET;

/*
 * USB_TCD_NET2280_ENDPOINT is a structure maintained by the net2280 TCD
 * for holding information required about an endpoint
 */

typedef struct usbTcdNET2280Endpoint
    {
    UINT8	endpointIndex;	/* endpoint index */
    UINT8	transferType;	/* transfer type */
    UINT8	direction; 	/* direction of the endpoint */
    UINT16	maxPacketSize;	/* Maximum packet size for the endpoint */
    UINT32	dataLength;	/* Available data in FIFO */

#ifdef NET2280_DMA_SUPPORTED
    UINT32	dmaTransferLength;/* DMA transfer length */
    BOOL	isDmaSupported;	/* Flag indicating dma support */
    BOOL	dmaInUse; 	/* Flag indicating the dma usage */
    UCHAR    * dmaBuffer;    	/* Buffer for DMA */
    BOOL	shortPacket;	/* Flag indicating a short packet */

#endif

    } USB_TCD_NET2280_ENDPOINT, *pUSB_TCD_NET2280_ENDPOINT;

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbNET2280Tcdh */

