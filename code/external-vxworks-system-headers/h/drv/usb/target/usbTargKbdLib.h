/* usbTargKbdLib.h - Defines exported interface from usbTargKbdLib */

/* Copyright 1999-2000 Wind River Systems, Inc. */
 
/*
Modification history
--------------------
01b,19jul04,ami  Coding Convention Changes
01a,18aug99,rcb  First.
*/

#ifndef __INCusbTargKbdLibh
#define __INCusbTargKbdLibh

#ifdef	__cplusplus
extern "C" {
#endif


/* function declaration */

extern VOID usbTargKbdCallbackInfo (struct usbTargCallbackTable ** ppCallbacks,
			            pVOID *pCallbackParam);


extern STATUS usbTargKbdInjectReport (pHID_KBD_BOOT_REPORT	pReport,
				      UINT16 reportLen);    


#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTargKbdLibh */
