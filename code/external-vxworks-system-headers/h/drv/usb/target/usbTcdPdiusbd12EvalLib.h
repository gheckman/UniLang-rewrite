/* usbTcdPdiusbd12EvalLib.h - Defines interface to Philips usbTcdPdiusbd12Lib.c */

/* Copyright 1999-2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01b,21jul04,hch  Create the element in tl_drv_t22_usb-int branch
                 Merge from development branch
01b,19jul04,ami  Coding Convention Changes
01a,05aug99,rcb  First.
*/

/*
DESCRIPTION

Defines the interface to the USB TCD (target controller driver) for the Philips
PDIUSBD12 evaluation board.
*/

#ifndef __INCusbTcdPdiusbd12EvalLibh
#define __INCusbTcdPdiusbd12EvalLibh

#ifdef	__cplusplus
extern "C" {
#endif


/* typedefs */

/* USB_TCD_PDIUSBD12_PARAMS
 *
 * The <tcdParam> to the USB_TCD_ATTACH function for this TCD must be a pointer
 * to the following structure.	The caller must initialize the structure with the
 * correct parameters for the hardware to be attached.
 */

typedef struct usbTcdPdiusbd12Params  /* USB_TCD_PDIUSBD12_PARAMS */
    {
    UINT32	ioBase;		/* Base I/O address range */
    UINT16	irq;		/* IRQ channel (e.g., 5 = IRQ5) */
    UINT16	dma;		/* DMA channel (e.g., 3 = DMA3) */
    } USB_TCD_PDIUSBD12_PARAMS, *pUSB_TCD_PDIUSBD12_PARAMS;


/* function declarations */

extern STATUS usbTcdPdiusbd12EvalExec (pVOID pTrb);


#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTcdPdiusbd12EvalLibh */
