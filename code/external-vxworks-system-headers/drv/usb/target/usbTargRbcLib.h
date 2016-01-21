/* usbTargRbcLib.h - Mass Storage RBC library header*/

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,23jul04,ami  Coding Convention Changes   
01b,19jul04,hch  created the file element 
01a,15mar04,jac  written.
*/

#ifndef _USB_RBC_LIB_H
#define _USB_RBC_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif

extern VOID bulkOutErpCallbackCBW (pVOID erp);

extern VOID bulkInErpCallbackCSW (pVOID erp);

extern VOID bulkInErpCallbackData (pVOID erp);

extern VOID bulkOutErpCallbackData (pVOID erp);

#ifdef	__cplusplus
}
#endif

#endif

