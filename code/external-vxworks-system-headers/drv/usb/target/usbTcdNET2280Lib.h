/* usbTcdNet2280Lib.h - Interfaces of Net2280 TCD */

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
01c,18sep04,ami  Change in usbTcdNET2280Exec Function Name
01b,08sep04,ami  Code Review Comments Incorporated
01a,03sep04,gpd  written
*/

/*
DESCRIPTION

This file contains the interface data structures and the functions which
can be used by the application and the Netchip2280 TCD.
*/


#ifndef __INCusbTcdNet2280Libh
#define __INCusbTcdNet2280Libh

#ifdef	__cplusplus
extern "C" {
#endif

#define NET2280_NO_OF_PCI_BADDR	3	/* Number of base addresses */

/* typedefs */

/* USB_TCD_NET2280_PARAMS-tcd parameters */

typedef struct usbTcdNET2280Params
    {
    UINT32	ioBase[NET2280_NO_OF_PCI_BADDR];	/* IO base array */
    UINT8	irq;					/* IRQ value */
    } USB_TCD_NET2280_PARAMS, *pUSB_TCD_NET2280_PARAMS;

/* function declarations */

extern STATUS usbTcdNET2280Exec (pVOID pTrb);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTcdNet2280Libh */
