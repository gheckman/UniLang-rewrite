/* usbTgtCommon.h - Common Definitions for USB GEN2 Target Stack */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01a,17may12,s_z  Writen based usbTargLib.h
*/

/*
DESCRIPTION

This file includes the common defination and routines of the USB target 
stack management modules.

INCLUDE FILES:  usb/usb.h 
*/

#ifndef __INCusbTgtCommonh
#define __INCusbTgtCommonh

/* includes */

#include <usb/usb.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define TARG_MNGMT_ATTACH         0x0000  /* TARG Attach Management Code */
#define TARG_MNGMT_DETACH         0x0001  /* TARG Detach Management Code */
#define TARG_MNGMT_DISCONNECT     0x0002  /* TARG Disconnect Management Code */
#define TARG_MNGMT_BUS_RESET      0x0003  /* TARG Bus Reset Management Code */
#define TARG_MNGMT_SUSPEND        0x0004  /* TARG Suspend Management Code */
#define TARG_MNGMT_RESUME         0x0005  /* TARG Resume Managemnt Code */
#define TARG_MNGMT_DESC_TABLE_GET 0x0006  /* Code to get descriptor table with TCD speed */



/* caller-supplied target callbacks */

/* target management callback */

typedef STATUS (*USB_TARG_MANAGEMENT_FUNC)
    (
    pVOID            param,
    USB_TARG_CHANNEL targChannel,
    UINT16           mngmtCode,  /* management code */
    pVOID            pContext
    );

/* control pipe callbacks */

typedef STATUS (*USB_TARG_FEATURE_CLEAR_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               requestType,    /* request type */
    UINT16              feature,        /* feature to clear */
    UINT16              uIndex          /* wIndex */
    );

typedef STATUS (*USB_TARG_FEATURE_SET_FUNC)
    (
    pVOID               param,          /* TCD Specific Parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               requestType,    /* request type */
    UINT16              feature,        /* feature to set */
    UINT16              index           /* wIndex */
    );

typedef STATUS (*USB_TARG_CONFIGURATION_GET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    pUINT8              pConfiguration  /* pointer to configuration value */
    );

typedef STATUS (*USB_TARG_CONFIGURATION_SET_FUNC)
    (
    pVOID               param,          /* TCD specific paramter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               configuration   /* configuration value */
    );

typedef STATUS (*USB_TARG_DESCRIPTOR_GET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               requestType,    /* request type */
    UINT8               descriptorType, /* descriptor type */
    UINT8               descriptorIndex,/* descriptor index */
    UINT16              languageId,     /* language ID */
    UINT16              length,         /* length of descriptor */
    pUINT8              pBfr,           /* pointer to buffer */
    pUINT16             pActLen         /* length of data sent */
    );

typedef STATUS (*USB_TARG_DESCRIPTOR_SET_FUNC)
    (
    pVOID               param,          /* TCD Specific Parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               requestType,    /* request type */
    UINT8               descriptorType, /* descriptor type */
    UINT8               descriptorIndex,/* descriptor index */
    UINT16              languageId,     /* language ID */
    UINT16              length,         /* length of descriptor */
    pUINT8              pBfr,           /* pointer to buffer */
    pUINT16             pActLen         /* length of data in buffer */
    );

typedef STATUS (*USB_TARG_INTERFACE_GET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT16              interface,      /* interface number */
    pUINT8              pAlternateSetting /* alternate setting */
    );

typedef STATUS (*USB_TARG_INTERFACE_SET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT16              interface,      /* interface number */
    UINT8               alternateSetting /* alternate setting */
    );

typedef STATUS (*USB_TARG_STATUS_GET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT16              requestType,    /* request type */
    UINT16              index,          /* wIndex */
    UINT16              length,         /* length */
    pUINT8              pBfr            /* pointer to buffer */
    );

typedef STATUS (*USB_TARG_ADDRESS_SET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT16              deviceAddress   /* device address */
    );

typedef STATUS (*USB_TARG_SYNCH_FRAME_GET_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT16              endpoint,       /* endpoint */
    pUINT16             pFrameNo        /* frame number obtained */
    );

typedef STATUS (*USB_TARG_VENDOR_SPECIFIC_FUNC)
    (
    pVOID               param,          /* TCD specific parameter */
    USB_TARG_CHANNEL    targChannel,    /* target channel */
    UINT8               requestType,    /* type of request */
    UINT8               request,        /* request name */
    UINT16              value,          /* wValue */
    UINT16              index,          /* wIndex */
    UINT16              length          /* wLength */
    );

typedef struct usbTargCallbackTable  /* USB_TARG_CALLBACK_TABLE */
    {
    /* device management callbacks */

    USB_TARG_MANAGEMENT_FUNC        mngmtFunc; /* management callback */

    /* Control pipe callbacks */

    USB_TARG_FEATURE_CLEAR_FUNC     featureClear;   /* feature clear */
    USB_TARG_FEATURE_SET_FUNC       featureSet;     /* feature set */
    USB_TARG_CONFIGURATION_GET_FUNC configurationGet; /*configuration get*/
    USB_TARG_CONFIGURATION_SET_FUNC configurationSet; /*configuration set*/
    USB_TARG_DESCRIPTOR_GET_FUNC    descriptorGet;  /* descriptor get */
    USB_TARG_DESCRIPTOR_SET_FUNC    descriptorSet;  /* descriptor set */
    USB_TARG_INTERFACE_GET_FUNC     interfaceGet;   /* interface get */
    USB_TARG_INTERFACE_SET_FUNC     interfaceSet;   /* interface set */
    USB_TARG_STATUS_GET_FUNC        statusGet;      /* status get */
    USB_TARG_ADDRESS_SET_FUNC       addressSet;     /* address set */
    USB_TARG_SYNCH_FRAME_GET_FUNC   synchFrameGet;  /* frame get */
    USB_TARG_VENDOR_SPECIFIC_FUNC   vendorSpecific; /* vendor specific */
    } USB_TARG_CALLBACK_TABLE, *pUSB_TARG_CALLBACK_TABLE;

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbTgtCommonh */




