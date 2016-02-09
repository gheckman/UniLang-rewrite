/* usbTargUtil.h - Defines Utility functions */

/* Copyright 2004 Wind River Systems, Inc. */

/*
Modification history
--------------------
02b,11may04,hch  merge after D12 driver testing.
01b,19jul04,ami Coding Convention Changes
01a,30mar04,ami First

*/

/* Descriptions

This file defines the various utility functions

*/


#ifndef __INCusbTargUtilh
#define __INCusbTargUtilh

#ifdef	__cplusplus
extern "C" {
#endif

/* function declarations */

extern int validateTarg (USB_TARG_CHANNEL targChannel,struct targTcd ** ppTcd);
    
extern STATUS mngmtFunc (pTARG_TCD pTcd, UINT16 mngmtCode, pVOID pContext);

extern VOID cntlEndpointStall (pTARG_TCD pTcd);

extern STATUS usbTargMgmtCallback (pVOID pTargTcd, UINT16 mngmtCode, 
                                   pVOID pContext);

extern VOID usbTargSetupErpCallback (pUSB_ERP pErp);

extern VOID initSetupErp (pTARG_TCD pTcd);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbTargUtilh */
