/* usbTargRbcCmd.h - Mass Storage RBC command library header*/

/* Copyright 2004, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,30jan09,w_x  Move some unrelated definitions to usbTargMsLib.h
01d,24apr06,ami  Mode Sense (10) and Mode Select (10) support (SPR#116239)
01c,23jul04,ami  Coding Convention Changes
01b,19jul04,hch  created the file element 
01a,15mar04,jac  written.
*/

#ifndef _WRS_TARG_RBC_CMD_H_
#define _WRS_TARG_RBC_CMD_H_

#ifdef	__cplusplus
extern "C" {
#endif

/* SCSI Sense codes */

#define SCSI_SENSE_NO_SENSE         0x00  /* no specific sense key info */
                                          /* no error */		
#define SCSI_SENSE_RECOVERED_ERROR  0x01  /* last command completed with */
					  /* some recovery action by UFI */
#define SCSI_SENSE_NOT_READY        0x02  /* UFI device can't be accessed */	
#define SCSI_SENSE_MEDIUM_ERROR     0x03  /* flaw in the mediaum */	  
#define SCSI_SENSE_HARDWARE_ERROR   0x04  /* non-recoverable hardware failure */	
#define SCSI_SENSE_ILLEGAL_REQUEST  0x05  /* illegal paramter in command */	
#define SCSI_SENSE_UNIT_ATTENTION   0x06  /* removeable media may have been */
                                          /* changed or UFI device reset */
#define SCSI_SENSE_DATA_PROTECT     0x07  /* write protected media */ 
#define SCSI_SENSE_BLANK_CHECK      0x08  /* device encountered a blank */
                                         /* medium while reading or non-blank*/
                                          /* medium while writing */ 
#define SCSI_SENSE_UNIQUE           0x09  /* vendor specific conditions */
#define SCSI_SENSE_COPY_ABORTED     0x0A  /* copy aborted */
#define SCSI_SENSE_ABORTED_COMMAND  0x0B  /* UFI device aborted the command */
#define SCSI_SENSE_EQUAL            0x0C  
#define SCSI_SENSE_VOL_OVERFLOW     0x0D  /* buffer overflow */
#define SCSI_SENSE_MISCOMPARE       0x0E  /* data mismatch occured */
#define SCSI_SENSE_RESERVED         0x0F  /* reserved */

/* Additional Sense codes (ASC) */

#define SCSI_ADSENSE_NO_SENSE           0x00	/* no sense key- no error */
#define SCSI_ADSENSE_LUN_NOT_READY      0x04	/* logical drive not ready */
#define SCSI_ADSENSE_ILLEGAL_COMMAND    0x20	/* illegal command */
#define SCSI_ADSENSE_ILLEGAL_BLOCK      0x21	/* block address out of range */
#define SCSI_ADSENSE_INVALID_PARAMETER  0x26	/* paramter value invalid */
#define SCSI_ADSENSE_INVALID_LUN        0x25	/* logical unit not supported */
#define SCSI_ADSENSE_INVALID_CDB        0x24	/* invalid command packet */
#define SCSI_ADSENSE_MUSIC_AREA         0xA0	/* additional sense code */
#define SCSI_ADSENSE_DATA_AREA          0xA1	/* additional sense code */
#define SCSI_ADSENSE_VOLUME_OVERFLOW    0xA7	/* volume overflow */

#define SCSI_ADSENSE_NO_MEDIA_IN_DEVICE 0x3A	/* media not present */
#define SCSI_ADSENSE_FORMAT_ERROR	0x31	/* format command failed */
#define SCSI_ADSENSE_CMDSEQ_ERROR	0x2C	/* command sequence error */
#define SCSI_ADSENSE_MEDIUM_CHANGED     0x28	/* media changed */
#define SCSI_ADSENSE_BUS_RESET          0x29	/* bus reset detected */
#define SCSI_ADWRITE_PROTECT            0x27	/* write protected */
#define SCSI_ADSENSE_TRACK_ERROR        0x14	/* recorded track not found */
#define SCSI_ADSENSE_SAVE_ERROR         0x39	/* saving parameters not */
                                                /* supported */
#define SCSI_ADSENSE_SEEK_ERROR         0x15	/* seek error */
#define SCSI_ADSENSE_REC_DATA_NOECC     0x17	/* recoverd data with retries */
#define SCSI_ADSENSE_REC_DATA_ECC       0x18	/* recovered data with ecc */ 
#define SCSI_PARAMETER_LIST_LENGTH_ERROR 0x1A	/* paramter list length error */

/* SCSI Additional sense code qualifier (ASCQ) */

#define SCSI_SENSEQ_FORMAT_IN_PROGRESS              0x04 /*format in progress*/	
                                                         /* LUN not supported */  
#define SCSI_SENSEQ_INIT_COMMAND_REQUIRED           0x02 /* initialization */
							 /* required */
#define SCSI_SENSEQ_MANUAL_INTERVENTION_REQUIRED    0x03 /*manual intervention*/
#define SCSI_SENSEQ_BECOMING_READY                  0x01 /* becoming ready */
#define SCSI_SENSEQ_FILEMARK_DETECTED               0x01 /*file mark detected*/
#define SCSI_SENSEQ_SETMARK_DETECTED                0x03 /* set mark detected*/
#define SCSI_SENSEQ_END_OF_MEDIA_DETECTED           0x02 /* end of media */
#define SCSI_SENSEQ_BEGINNING_OF_MEDIA_DETECTED     0x04 /* start of media */
#define SCSI_SENSEQ_ILLEGAL_POWER_CONDITION_REQUEST 0x05 /* bad power */
                                                         /* conditions*/
/* typedefs */

typedef struct stdInquiryData	/* STD_INQUIRY_DATA */
    {
    UINT8	devQualType;	/* peripheral device type */
    UINT8	RemovableMedia; /* removeable media bit */
    UINT8	version;	/* 0x0 The device does not claim */
                                /* conformance to any standard. */
    UINT8	byte3;		/* response data format in lower 4 bits */
				/* upper 4 bits reserved */
    UINT8	additionalLgth;	/* length of parameters in bytes */
    UINT8	sccs;
    UINT8	byte6;		/* reserved */
    UINT8	byte7;		/* reserved */
    UINT8	vendorId[8];	/* vendor indentification */          
    UINT8	productId[16];	/* producat indentification */
    UINT8	productRevLevel[4]; /* product revision data */
                                    /* 36 bytes is the minimum required */
    UINT8	vendorSpecific[20]; /* vendor specific info */
    UINT8	byte56;		/* Reserved */
    UINT8	reserved1;	/* reserved - 1 */
    UINT16	versionDescriptor[8];	/* version descripttion */	
    UINT8	reserved2[22];	/* reservered - 2 */
    } WRS_PACK_ALIGN(1) STD_INQUIRY_DATA, *pSTD_INQUIRY_DATA;


typedef struct vpdSupportedPage	/* VPD_SUPPORTED_PAGE */
    {
    UINT8	devQualType;	/* peripheral device type */	
    UINT8	pageCode;	/* page code */
    UINT8	reserved;	/* reserved */
    UINT8	pageLgth;	/* page length */
    UINT8	page_0;		
    UINT8	page_80;	
    UINT8	page_83;
    }WRS_PACK_ALIGN(1) VPD_SUPPORTED_PAGE, *pVPD_SUPPORTED_PAGE;

typedef struct commandData	/* COMMAND_DATA */
    {
    UINT8	devQualType;	/* peripheral device type */
    UINT8	support;	/* future support */	
    UINT8	reserved[2];	/* reserved */
    UINT8	cdbSize;	/* command block size */
    UINT8	cdbOpCode;	/* operation opcode */
    UINT8	cdbUsageMap;	/* command usage map */
    } WRS_PACK_ALIGN(1) COMMAND_DATA, *pCOMMAND_DATA;

typedef struct vpdDeviceIdDescriptor	/* VPD_DEVICE_ID_DESCRIPTOR */
    {
    UINT8	codeSet;		
    UINT8	assocIdType;
    UINT8	reserved;		/* reserved */
    UINT8	idLgth;			/* device id descriptor length */
    UINT8	devId[DEVICE_ID_LGTH];	/* device id */
    } WRS_PACK_ALIGN(1) VPD_DEVICE_ID_DESCRIPTOR, *pVPD_DEVICE_ID_DESCRIPTOR;

typedef struct vpdDeviceIdPge 		/* VPD_DEVICE_ID_PAGE */
    {
    UINT8	devQualType;		/* peripheral device type */	
    UINT8	pageCode;		/* page code */
    UINT8	reserved;		/* reserved */
    UINT8	pageLgth;		/* page lenght */
    VPD_DEVICE_ID_DESCRIPTOR devIdDescr;/* device descriptor id */
    } WRS_PACK_ALIGN(1) VPD_DEVICE_ID_PAGE, *pVPD_DEVICE_ID_PAGE;

typedef struct vpdUnitSerialNumPage	/* VPD_UNIT_SERIAL_NUM_PAGE */
    {
    UINT8	devQualType;		/* peripheral device type */
    UINT8	pageCode;		/* page code */
    UINT8	reserved;		/* reserved */
    UINT8	pageLgth;		/* page length */
    UINT8	serialNum[24];		/* serial number */
    } WRS_PACK_ALIGN(1) VPD_UNIT_SERIAL_NUM_PAGE, *pVPD_UNIT_SERIAL_NUM_PAGE;

typedef struct modeParameterHeader	/* MODE_PARAMETER_HEADER */
    {
    UINT8	dataLen;		/* mode data length */ 
    UINT8	mediumType;		/* type of media */
    UINT8	deviceParameter;	/* device paramter */
    UINT8	blockDescriptorLgth;	/* block desc. length */
    } WRS_PACK_ALIGN(1) MODE_PARAMETER_HEADER, *pMODE_PARAMETER_HEAD;

typedef struct modeParamterPage		/* MODE_PARAMETER_PAGE */	
    {
    UINT8	pageCode;		/* page code */
    UINT8	pageLth;		/* page length */
    UINT8	writeCacheDisable;	/* cache disabled for writes */
    UINT8	logicalBlockSize[2];	/* logical block size */
    UINT8	numberOfLogicalBlocks[5];/* number of logical blocks */
    }WRS_PACK_ALIGN(1) MODE_PARAMETER_PAGE, *pMODE_PARAMETER_PAGE;

typedef struct modeParametrList 	/* MODE_PARAMETER_LIST */
    {
    MODE_PARAMETER_HEADER	header;	/* MODE_PARAMETER_HEADER */
    MODE_PARAMETER_PAGE		params;	/* MODE_PARAMETER_PAGE */
    } WRS_PACK_ALIGN(1) MODE_PARAMETER_LIST, *pMODE_PARAMETER_LIST;

typedef struct senseData 		/* SENSE_DATA */
    {
    UINT8	responseCode;		/* request code */ 
    UINT8	obsolete;		/* zero always */
    UINT8	senseKey;     		/* sense key - depends on command */
    UINT8	info[4];      		/* info field - command specific */
    UINT8	additionalSenseLgth;	/* additional data to follow */
					/* UFI device set this to 10 */	
    UINT8	cmdSpecificInfo[4];	/* command specific info */
    UINT8	asc;                    /* additional sense code */
    UINT8	ascq;                   /* additional sense code qualifier */
    UINT8	fieldReplaceableUnitCode;/* optional field set to zero */
    UINT8	senseKeySpecific[3];	/* reserved for additiona data */
    } WRS_PACK_ALIGN(1) SENSE_DATA, *pSENSE_DATA;

typedef struct capacityData 		/* CAPACITY_DATA */
    {
    UINT8	lba_3;			/* logical block address - byte 3 */
    UINT8	lba_2;			/* logical block address - byte 2 */
    UINT8	lba_1;			/* logical block address - byte 1 */ 
    UINT8	lba_0;			/* logical block address - byte 0 */
    UINT8	blockLen_3;		/* block length - byte 3 */
    UINT8	blockLen_2;		/* block length - byte 2 */
    UINT8	blockLen_1;		/* block length - byte 1 */
    UINT8	blockLen_0;		/* block length - byte 0 */
    } WRS_PACK_ALIGN(1) CAPACITY_DATA, *pCAPACITY_DATA;
    
typedef struct modeParameterHeader10	/* MODE_PARAMETER_HEADER10 for mode
                                           sense10 command */
    {
    UINT8	dataLenMSB;		/* mode data length MSB */
    UINT8       dataLenLSB;             /* mode data length MSB */
    UINT8	mediumType;		/* type of media */
    UINT8	deviceParameter;	/* device paramter */
    UINT16      reservedBytes;          /* reserved */
    UINT16	blockDescriptorLgth;	/* block desc. length */
    } WRS_PACK_ALIGN(1) MODE_PARAMETER_HEADER10, *pMODE_PARAMETER_HEAD10;

typedef struct modeParametrList10 	/* MODE_PARAMETER_LIST10 for mode
                                           sense 10 command */
    {
    MODE_PARAMETER_HEADER10	header;	/* MODE_PARAMETER_HEADER10 */
    MODE_PARAMETER_PAGE		params;	/* MODE_PARAMETER_PAGE */
    } WRS_PACK_ALIGN(1) MODE_PARAMETER_LIST10, *pMODE_PARAMETER_LIST10;

/* function declaration */

extern pVOID usbTargRbcBlockDevGet (void);

extern STATUS  usbTargRbcBlockDevSet (pVOID *blkDev);

extern STATUS  usbTargRbcBlockDevCreated (void);

extern STATUS usbTargRbcRead (UINT8   arg[10], UINT8 ** pData, UINT32  *size);

extern STATUS usbTargRbcCapacityRead (UINT8 arg[10], 
                                      UINT8 ** pData,UINT32 *size);

extern STATUS usbTargRbcStartStop (UINT8 arg[6]);

extern STATUS usbTargRbcPreventAllowRemoval (UINT8 arg[6]);

extern STATUS usbTargRbcVerify (UINT8 arg[10]);

extern STATUS usbTargRbcWrite (UINT8   arg[10], UINT8 ** pData, UINT32  * size);

extern STATUS usbTargRbcInquiry (UINT8 cmd[6], UINT8 ** pData, UINT32 * size);

extern STATUS usbTargRbcModeSelect (UINT8 arg[6], UINT8 ** pData, UINT32 *size);

extern STATUS usbTargRbcModeSense (UINT8 arg[6], UINT8 ** pData, UINT32  *size);

extern STATUS usbTargRbcTestUnitReady (UINT8 arg[6]);

extern STATUS usbTargRbcBufferWrite (UINT8   arg[10], UINT8   **pData,
                                     UINT32  *size);

extern STATUS usbTargRbcFormat (UINT8 arg[6]);

extern STATUS usbTargRbcPersistentReserveIn (UINT8 arg[10], UINT8 ** pData, 
                                      UINT32  * size);

extern STATUS usbTargRbcPersistentReserveOut (UINT8 arg[10], UINT8 ** pData,
                                              UINT32  * size);

extern STATUS usbTargRbcRelease (UINT8 arg[6]);

extern STATUS usbTargRbcRequestSense (UINT8 arg[6], UINT8 ** pData,  
                                      UINT32  *size);

extern STATUS usbTargRbcReserve (UINT8 arg[6]);

extern STATUS usbTargRbcCacheSync (UINT8 arg[10]);

extern STATUS usbTargRbcVendorSpecific (UINT8   arg[10], UINT8   **pData, 
                                        UINT32  *size);

extern STATUS usbTargRbcModeSense10 (UINT8 arg[10], UINT8 ** ppData,
                                      UINT32 * pSize);
STATUS usbTargRbcModeSelect10 (UINT8 arg[10], UINT8 ** ppData,
                                UINT32 * pSize);


#ifdef	__cplusplus
}
#endif

#endif
