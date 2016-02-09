/* usbTargPrnLib.h - Defines exported interface from usbTargPrnLib */

/* Copyright 1999-2004 Wind River Systems, Inc. */
 
/*
Modification history
--------------------
01b,19jul04,ami  Coding Convention Changes
01a,18aug99,rcb  First.
*/

#ifndef __INCusbTargPrnLibh
#define __INCusbTargPrnLibh

#ifdef	__cplusplus
extern "C" {
#endif


/* function declaration */

extern VOID usbTargPrnCallbackInfo (pUSB_TARG_CALLBACK_TABLE	*ppCallbacks,
				    pVOID *pCallbackParam);

extern STATUS usbTargPrnDataInfo (pUINT8 *ppBfr, pUINT16 pActLen);

extern STATUS usbTargPrnDataRestart (void);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTargPrnLibh */
