/* usbHalLib.h - define the API's exposed by HAL */

/* Copyright 2004, 2010 Wind River Systems, Inc. */

/*
Modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,03aug04,mta  Modification History Changes
01b,19jul04,amit Coding Convention Changes
01a,04mar04,mta  First.
*/

/*
DESCRIPTION

This file defines the interfaces and data structures exposed by the
Hardware Adaption Layer to the usbTargLib layer
*/

#ifndef __INCusbHalLibh
#define __INCusbHalLibh


/* includes */

#include "usb/usbHandleLib.h"
#include "usb/usb.h"
#include "usb/target/usbTcd.h"

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

/* managment codes passed to USB_TCD_MANAGEMENT_CALLBACK */

#define TCD_MNGMT_BUS_RESET	1	/* bus reset */
#define TCD_MNGMT_SUSPEND	2	/* suspend signalling detected */
#define TCD_MNGMT_RESUME	3	/* resume signalling detected */
#define TCD_MNGMT_DISCONNECT	4	/* disconnect detected */

/* typedefs */

typedef struct usbHalTcdNexus	/* USBHAL_TCD_NEXUS */
    {
    USB_TCD_EXEC_FUNC	tcdExecFunc;	/* TCD primary entry point */
    TCD_HANDLE		handle;		/* client's handle with TCD */
    } USBHAL_TCD_NEXUS, *pUSBHAL_TCD_NEXUS;

/* management notification callback function */

typedef VOID (*USB_TCD_MNGMT_CALLBACK)
    (
    pVOID mngmtCallbackParam,
    UINT16 mngmtCode,
    pVOID pContext
    );

/* functions declarration */

extern STATUS usbHalTcdAttach (USB_TCD_EXEC_FUNC tcdExecFunc, pVOID tcdParam,
                               pUSBHAL_TCD_NEXUS pNexus,
                               pUSB_APPLN_DEVICE_INFO pDeviceInfo,
                               USB_TCD_MNGMT_CALLBACK mngmtCallback,
                               pVOID mngmtCallbackParam);

extern STATUS usbHalTcdDetach (pUSBHAL_TCD_NEXUS pNexus);

extern STATUS usbHalTcdEnable (pUSBHAL_TCD_NEXUS pNexus);

extern STATUS usbHalTcdDisable (pUSBHAL_TCD_NEXUS pNexus);

extern STATUS usbHalTcdAddressSet (pUSBHAL_TCD_NEXUS pNexus,UINT8 deviceAddress);

extern STATUS usbHalTcdSignalResume (pUSBHAL_TCD_NEXUS pNexus);

extern STATUS usbHalTcdDeviceFeatureSet (pUSBHAL_TCD_NEXUS pNexus,
                                         UINT16 uFeatureSelector,
                                         UINT8 uTestSelector);

extern STATUS usbHalTcdDeviceFeatureClear (pUSBHAL_TCD_NEXUS pNexus,
                                           UINT16 uFeatureSelector);

extern STATUS usbHalTcdCurrentFrameGet (pUSBHAL_TCD_NEXUS pNexus,
                                        pUINT16 pFrameNo);

extern STATUS usbHalTcdEndpointAssign (pUSBHAL_TCD_NEXUS pNexus,
                                       pUSB_ENDPOINT_DESCR pEndpointDesc,
				       UINT16 uConfigurationValue,
				       UINT16 uInterface,
				       UINT16 uAltSetting,
				       VOID ** ppPipeHandle);

extern STATUS usbHalTcdEndpointRelease (pUSBHAL_TCD_NEXUS pNexus,
                                        pVOID pPipeHandle);

extern STATUS usbHalTcdEndpointStateSet (pUSBHAL_TCD_NEXUS pNexus,
					 pVOID pPipeHandle, UINT16 state);

extern STATUS usbHalTcdEndpointStatusGet (pUSBHAL_TCD_NEXUS pNexus,
                                          pVOID pPipeHandle, pUINT8 pStatus);

extern STATUS usbHalTcdErpSubmit (pUSBHAL_TCD_NEXUS pNexus, pUSB_ERP pErp);

extern STATUS usbHalTcdErpCancel (pUSBHAL_TCD_NEXUS pNexus, pUSB_ERP pErp);

#ifdef	__cplusplus
}
#endif

#endif	/* __INCusbHalLibh */
