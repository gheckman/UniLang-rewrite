/* usbTargMsLib.h - Defines for USB mass storage driver */

/* Copyright 2004, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,30jan09,w_x  Remove host side header file dependency
01d,23jul04,ami  Coding Convention Changes
01c,21jul04,pdg  Changed IRP_CALLBACK to ERP_CALLBACK
01b,19jul04,hch  created the file element 
01a,15mar04,jac  written.
*/

/*
DESCRIPTION

Defines the USB mass storage driver interface to the USB target controller 
driver (TCD).

*/

#ifndef _USBTARGMSLIB_H
#define _USBTARGMSLIB_H

#ifdef    __cplusplus
extern "C" {
#endif

/* defines */

#ifndef BYTES_PER_BLOCK
    #define BYTES_PER_BLOCK	512	/* user configuration parameter */
#endif

#ifndef NUM_BLOCKS
    #define NUM_BLOCKS	    20480  /* number of blocks */
#endif

#define BLK_DEV_NAME        "/bd/0"   /* bulk device name */

#define DEVICE_ID_LGTH	    8		    /* device id length */ 		
#define DEVICE_ID	        'V','x','W','o','r','k','s',':'	/* device id */

#define USB_DEBUG_PRINT

#define USE_SCSI_SUBCLASS  /* SCSI Protocol */

#ifdef USE_SCSI_SUBCLASS
#undef  USE_RBC_SUBCLASS
#else
#define USE_RBC_SUBCLASS     /* RBC Protocol */    
#endif

#ifdef USB_DEBUG_PRINT
    void usbDbgPrintOn (void);
    void usbDbgPrintOff (void);
    void usbDbgPrint(char *fmt, ...); /* Debug messages */
#else
    #define usbDbgPrint 
#endif

/* USB Mass Storage Class */
#define USB_MSC_CLASS_MASS_STORAGE 0x08 

#define USB_MSC_SUBCLASS_RBC       0x01 /* Reduced Block Commands (RBC) */

#define USB_MSC_SUBCLASS_SCSI      0x06 /* SCSI transparent command set */
                                         /* (Use the SCSI INQUIRY        */
                                         /* command to determine the     */
                                         /* peripheral device type for   */
                                         /* most devices.)               */

#define USB2_MSC_PROTOCOL_BOT      0x50  /* Bulk Only (Recommended      */
                                         /* for most devices)           */

/* Class specific Mass storage reset request    */ 
#define USB_MSC_RESET                           0xFF 

/* Class specific Get Max LUN request           */
#define USB_MSC_GET_MAX_LUN                     0xFE 

/* Command Block Wrapper Signature 'USBC'       */
#define USB_MSC_CBW_SIGNATURE                   0x43425355
#define USB_MSC_CBW_MAX_CDB_LEN                 16 

/* Command Block Wrapper Flag                   */
#define USB_MSC_CBW_FLAGS_DATA_IN               0x80
#define USB_MSC_CBW_FLAGS_DATA_OUT              0x00
#define USB_MSC_CBW_FLAGS_DATA_NONE             0x00

/* Command Status Wrapper Signature 'USBS'      */
#define USB_MSC_CSW_SIGNATURE                   0x53425355

/* Command Status Wrapper Status                */
#define USB_MSC_CSW_STATUS_SUCCESS              0x00
#define USB_MSC_CSW_STATUS_FAILED               0x01
#define USB_MSC_CSW_STATUS_PHASE_ERROR          0x02

/* CBW and CSW length */
#define USB_MSC_CBW_LENGTH                     31
#define USB_MSC_CSW_LENGTH                     13

/* Command Block Wrapper */
typedef struct usbMscCbw
    {
    UINT32    dCBWSignature;              /* CBW Signature                  */
    UINT32    dCBWTag;                    /* Tag field                      */
    UINT32    dCBWDataTransferLength;     /* Size of data (bytes)           */
    UINT8     bmCBWFlags;                 /* direction bit                  */
    UINT8     bCBWLUN;                    /* Logical Unit Number            */
    UINT8     bCBWCBLength;               /* Length of command block        */
    UINT8     CBWCB [16];                 /* buffer for command block       */
    } WRS_PACK_ALIGN(1) USB_MSC_CBW; 

/* Command Status Wrapper */
typedef struct usbMscCsw
    {
    UINT32    dCSWSignature;              /* CBW Signature                  */
    UINT32    dCSWTag;                    /* Tag field                      */
    UINT32    dCSWDataResidue;            /* Size of residual data (bytes)  */
    UINT8     bCSWStatus;                 /* buffer for command block       */
    } WRS_PACK_ALIGN(1) USB_MSC_CSW;

/* function declaration */

extern USB_MSC_CBW     *usbMsCBWGet(void);
extern USB_MSC_CBW     *usbMsCBWInit(void);
extern USB_MSC_CSW     *usbMsCSWInit(void);
extern USB_MSC_CSW     *usbMsCSWGet(void);

extern STATUS    usbMsBulkInStall(void);
extern STATUS    usbMsBulkInUnStall(void);
extern STATUS    usbMsBulkOutStall(void);
extern STATUS    usbMsBulkOutUnStall(void);
extern BOOL    usbMsIsConfigured(void);
extern BOOL    usbMsBulkInErpInUseFlagGet(void);
extern BOOL    usbMsBulkOutErpInUseFlagGet(void);
extern VOID    usbMsBulkInErpInUseFlagSet(BOOL state);
extern VOID    usbMsBulkOutErpInUseFlagSet(BOOL state);

extern VOID usbTargMsCallbackInfo (struct usbTargCallbackTable ** ppCallbacks,
                                   VOID ** pCallbackParam);

extern STATUS usbMsBulkInErpInit (UINT8 * pData, UINT32 size, 
                                  ERP_CALLBACK    erpCallback, pVOID usrPtr);

extern STATUS usbMsBulkOutErpInit (UINT8 * pData, UINT32 size,
                                   ERP_CALLBACK    erpCallback,pVOID usrPtr);

#ifdef    __cplusplus
}
#endif

#endif
