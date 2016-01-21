/* usbHal.h - Defines structures/interfaces used only by HAL */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,13jan10,ghs  vxWorks 6.9 LP64 adapting
01d,03aug04,mta  Modification History Changes
01c,19jul04,ami  Coding Convention Changes
01b,03may04,pdg  Fix for receiving less than expected data from the host
01a,04mar04,mta  First.
*/

/*
DESCRIPTION

Defines structures/interfaces used only by Hardware Adaption Layer (HAL).
*/

#ifndef __INCusbHalh
#define __INCusbHalh

/* includes */

#include "usb/usbHandleLib.h"
#include "usb/usb.h"
#include "usb/target/usbTcd.h"
#include "usb/target/usbHalLib.h"

#ifdef	__cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct usbHalPipeInfo  /* USBHAL_PIPE_INFO */
    {
    UINT8	uEndpointAddress;	/* endpoint address */
    UINT16	maxPacketSize;	/* maximum packet size of the endpoint */
    pVOID	pipeHandle;	/* pipe handle returned from the TCD */
    LIST_HEAD	listHead;	/* head of the list of ERPs queued */
                                /* for this endpoint */
    UINT32	uEndpointInterruptStatus;/* endpoint interrupt status */
    MUTEX_HANDLE  mutexHandle;	/* pointer to the mutex handle */
    } USBHAL_PIPE_INFO, *pUSBHAL_PIPE_INFO;

typedef struct usbHalTcd	/* USBHAL_TCD */
    {
    pVOID		pTCDHandle;	/* pointer to the TCD handle */
    USB_TCD_EXEC_FUNC	tcdExecFunc;	/* single entry point of the TCD */
    SEM_HANDLE		intPendingSemaphore; /* semaphore of the interrupt */
                                             /* handler thread */
    UINT32		uInterruptStatus;    /* bitmap specifying interrupt */
                                             /* status */
    MUTEX_HANDLE	mutex;		/* mutex for accessing the shared */
					/* resources  */
    struct usbHalPipeInfo ** pPipeInfo; /* pointer to array of */
                                        /* USBHAL_PIPE_INFO structures */
    UINT32		uActiveEndpointsBitmap;	/* bitmap holding the */
                                                /* endpoints which are active*/

    UINT8		uActiveEndpoints;   /* number of endpoints which */
                                            /* are active */
    USBHAL_DEVICE_INFO	halDeviceInfo;/* information about features supported */
    USB_TCD_MNGMT_CALLBACK mngmtCallback; /* pointer to the Management callback*/
                                          /* function of the usbTargLib */
    pVOID		mngmtCallbackParam;/* parameter to the management */
                                           /* callback function */
    THREAD_HANDLE	threadId;	/* interrupt handler thread ID */
    } USBHAL_TCD, *pUSBHAL_TCD;

/* functions declarations */

extern STATUS usbHalProcessEndpointOUT (pUSBHAL_TCD	pHalInfo,
					pUSBHAL_PIPE_INFO pPipeInfo);

extern STATUS usbHalProcessEndpointIN  (pUSBHAL_TCD	pHalInfo,
					pUSBHAL_PIPE_INFO pPipeInfo);

extern VOID usbHalIsr (pUSBHAL_TCD	pHalTcd);

extern VOID usbHalInterruptThread (pUSBHAL_TCD pHalTcd);

extern VOID trbHeaderInit (pTRB_HEADER pTrb, pVOID pTCDHandle,
			   UINT16 uFunctionCode,UINT16 uTotalLen);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbHalh */
