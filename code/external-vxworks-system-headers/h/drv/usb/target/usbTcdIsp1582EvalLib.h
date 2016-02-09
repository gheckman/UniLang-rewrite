/* usbTcdIsp1582EvalLib.h -Defines interface to Philips usbTcdIsp1582EvalLib.c*/

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01b,19jul04,ami  Coding Convention Changes
01a,21apr04,ami  First.
*/

/*
DESCRIPTION

Defines the interface to the USB TCD (target controller driver) for the Philips
ISP 1582 evaluation board.
*/

#ifndef __INCusbTcdIsp1582EvalLibh
#define __INCusbTcdIsp1582EvalLibh

#ifdef	__cplusplus
extern "C" {
#endif


/* typedefs */

typedef struct usbTcdIsp1582Params  /* USB_TCD_ISP1582_PARAMS */
    {

    UINT32	ioBase;		/* Base I/O address range */
    UINT16	irq;		/* IRQ channel */
    UINT16	dma;		/* DMA channel */
    } USB_TCD_ISP1582_PARAMS, *pUSB_TCD_ISP1582_PARAMS;


/* function declaration */

extern STATUS usbTcdIsp1582EvalExec (pVOID pTrb);/* Primary TCD entry point */

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTcdIsp1582EvalLibh */
