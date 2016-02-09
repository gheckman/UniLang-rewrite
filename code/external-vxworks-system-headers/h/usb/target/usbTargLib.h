/* usbTargLib.h - Defines interface to usbTargLib.c */

/*
 * Copyright (c) 1999-2001, 2004, 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01l,30jun12,s_z  Remove some common definition to usbTgtCommon.h
01l,30jun11,s_z  Remove USB_TARG_PIPE and USB_TARG_CHANNEL(WIND00285554)
01k,29apr10,pad  Moved extern C statement after include statements.
01j,13jan10,ghs  vxWorks 6.9 LP64 adapting
01i,03aug04,mta  Modification History Changes
01h,19jul04,ami  Coding Convention Changes
01g,18may04,mta  Modification to USB_TARG_STATUS_GET_FUNC
01f,30mar04,ami  changes made according to USB 2.0 Extn Design doc
01e,18sep01,wef  merge from wrs.tor2_0.usb1_1-f for veloce
01d,07may01,wef  changed module number to be (module sub num << 8) |
                 M_usbPeriphLib
01c,02may01,wef  changed module number to be M_<module> + M_usbPeriphLib
01b,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes
01a,04aug99,rcb  First.
*/

/*
DESCRIPTION

Defines the interface to usbTargLib.c.  usbTargLib.c implements a hardware-
independent interface to USB target controller drivers.
*/

#ifndef __INCusbTargLibh
#define __INCusbTargLibh

/* includes */

#include "usb/usbHandleLib.h"
#include "usb/usb.h"
#include "vwModNum.h"
#include "usb/target/usbHalCommon.h"
#include "usb/target/usbHalLib.h"
#include "usb/usbListLib.h"
#include "usb/usbTgtCommon.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* defines */

#define TARG_TCD_SIG    ((UINT32) 0xaaaa00cd) /* signature for Tcd */
#define TARG_PIPE_SIG   ((UINT32) 0xaaaa000e) /* signature for Pipe */

/* usbTargLib error codes */

/*
 * USB errnos are defined as being part of the USB peripheral Module, as are
 * all vxWorks module numbers, but the USB Module number is further divided
 * into sub-modules.  Each sub-module has upto 255 values for its own error
 * codes
 */

#define USB_TARG_SUB_MODULE  1

#define M_usbTargLib    ( (USB_TARG_SUB_MODULE  << 8) | M_usbPeriphLib )

#define usbTargErr(x)   (M_usbTargLib | (x))

#define S_usbTargLib_BAD_PARAM          usbTargErr(1)   /* bad parameter */
#define S_usbTargLib_BAD_HANDLE         usbTargErr(2)   /* bad handle */
#define S_usbTargLib_OUT_OF_MEMORY      usbTargErr(3)   /* out of memory */
#define S_usbTargLib_OUT_OF_RESOURCES   usbTargErr(4)   /* Out of resource */
#define S_usbTargLib_NOT_IMPLEMENTED    usbTargErr(5)   /* not Implemented */
#define S_usbTargLib_GENERAL_FAULT      usbTargErr(6)   /* general fault */
#define S_usbTargLib_NOT_INITIALIZED    usbTargErr(7)   /* uninilialized */
#define S_usbTargLib_CANNOT_CANCEL      usbTargErr(8)   /* cannot cancel */
#define S_usbTargLib_TCD_FAULT          usbTargErr(9)   /* TCD related fault */
#define S_usbTargLib_ENDPOINT_IN_USE    usbTargErr(10)  /* endpoint in use */
#define S_usbTargLib_APP_FAULT          usbTargErr(11)  /* application fault */

/* typedefs */

typedef UINT32 USB_TARG_DESCR, *pUSB_TARG_DESCR;

/* caller-supplied target callbacks */
/* Data Structures of the USB Target Library */

typedef struct targTcd      /* TARG_TCD */
    {
    LINK                tcdLink;             /* link to the next TCD */
    USB_TARG_CHANNEL    targChannel;         /* handle to TCD */
    pUSB_TARG_CALLBACK_TABLE    pCallbacks;  /* table of application callback*/
    pVOID               callbackParam;  /* callback defined callback parameter*/
    USBHAL_TCD_NEXUS    tcdNexus;            /* TCD Nexus Pointer */
    UINT16              speed;               /* speed of operation */
    USB_TARG_PIPE       defaultControlPipeIN;/* handle to default control In */
                                              /* pipe */
    USB_TARG_PIPE       defaultControlPipeOUT;/*handle to default control Out*/
                                              /* pipe */
    USB_ERP             setupErp;            /* to handle setup transfers */
    USB_ERP             defaultControlErp;   /* erp used to transfer to/from */
                                             /* default pipe */
    UINT8               setupBfr [sizeof (USB_SETUP)];/*for receiving */
                                                      /* setup packet */
    UINT8               dataBfr [USB_MAX_DESCR_LEN]; /* sending/receiving data */
                                             /* to/from default control */
                                             /* pipe */
    BOOL                controlErpPending;   /* flag indicating setup erp pending*/
    MUTEX_HANDLE        tcdMutex;            /* for synchronization operations */
    } TARG_TCD, *pTARG_TCD;

typedef struct targPipe     /* TARG_PIPE */
    {
    USB_TARG_PIPE       pipeHandle;     /* pipe handle information */
    pVOID               pHalPipeHandle; /* HAL specific pipe handle */
    pTARG_TCD           pTargTcd;       /* pointer to targ_tcd data structure*/
    } TARG_PIPE, *pTARG_PIPE;

/* function declarations */

/*  Function declarations for initializing & uninitializing */

extern STATUS usbTargInitialize (void);

extern STATUS usbTargShutdown (void);

extern STATUS usbTargTcdAttach (USB_TCD_EXEC_FUNC tcdExecFunc, pVOID tcdParam,
                                pUSB_TARG_CALLBACK_TABLE pCallbacks,
                                pVOID callbackParam,
                                pUSB_TARG_CHANNEL pTargChannel);

extern STATUS usbTargTcdDetach (USB_TARG_CHANNEL targChannel);

extern STATUS usbTargEnable (USB_TARG_CHANNEL targChannel);

extern STATUS usbTargDisable (USB_TARG_CHANNEL targChannel);

/* Function declarations for Pipe Specific Request */

extern STATUS usbTargPipeCreate (USB_TARG_CHANNEL targChannel,
                                 pUSB_ENDPOINT_DESCR pEndpointDesc,
                                 UINT16 uConfigurationValue, UINT16 uInterface,
                                 UINT16 uAltSetting,
                                 pUSB_TARG_PIPE pPipeHandle);

extern STATUS usbTargPipeDestroy (USB_TARG_PIPE pipeHandle);

extern STATUS usbTargTransfer (USB_TARG_PIPE pipeHandle, pUSB_ERP pErp);

extern STATUS usbTargTransferAbort (USB_TARG_PIPE pipeHandle, pUSB_ERP pErp);

extern STATUS usbTargPipeStatusSet (USB_TARG_PIPE pipeHandle, UINT16 state);

extern STATUS usbTargPipeStatusGet (USB_TARG_PIPE pipeHandle, pUINT8 pBuf);

/* Function declarations for default pipe requests */

extern STATUS usbTargControlResponseSend (USB_TARG_CHANNEL targChannel,
                                          UINT16 bfrLen, pUINT8 pBfr);

extern STATUS usbTargControlPayloadRcv (USB_TARG_CHANNEL targChannel,
                                        UINT16 bfrLen, pUINT8 pBfr,
                                        ERP_CALLBACK userCallback);

extern STATUS usbTargControlStatusSend (USB_TARG_CHANNEL targChannel);

/* Function declarations for Device Control & Status Information */

extern STATUS usbTargCurrentFrameGet (USB_TARG_CHANNEL targChannel,
                                      pUINT16 pFrameNo);

extern STATUS usbTargSignalResume (USB_TARG_CHANNEL targChannel);

extern STATUS usbTargDeviceFeatureSet (USB_TARG_CHANNEL targChannel,
                                       UINT16 ufeatureSelector,
                                       UINT8    uTestSelector);

extern STATUS usbTargDeviceFeatureClear (USB_TARG_CHANNEL targChannel,
                                         UINT16   ufeatureSelector);

#ifdef  __cplusplus
}
#endif

#endif	/* __INCusbTargLibh */
