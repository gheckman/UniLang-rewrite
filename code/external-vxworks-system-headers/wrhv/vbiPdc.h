/* vbiPdc.h - Process Data Channel definitions */

/* 
 * Copyright 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,17feb12,c_t  Sync with HV 2.0 27-Jan-12 DVD
01f,16jun11,jlv  WIND00282402 revert deviceChannel vbi change
01e,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01d,03nov10,rab  workaround 6.9 compiler alignment problem
01c,20apr10,mpk  add documentation for device driver api
01b,18dec09,mpk  remove device specific info from IDC
01a,15sep09,mpk  created
*/

/* DESCRIPTION
 *
 * Message format for Process Data Channel (PDC)
 * from Stub Device Driver (SDD)
 * to Actual Device Driver Guest Interface (ADD-GI)
 */

#ifndef __INCvbiPdch
#define __INCvbiPdch


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ASMLANGUAGE

typedef void * VOID_PTR;

typedef VBI_NS_HANDLE VBI_PDC_HANDLE;

typedef struct vbi_msg_hdr 
    {
    uint32_t msgId;	/* message type identification */
    uint32_t msgArg;	/* argument associated with message type */
    } VBI_MSG_HDR;

/*******************************************************************************
*
* MSG_PDC - process data channel PDC message format
*
* MSG_PDC is a C data type structure that provides the definition of the
* message format used to communicate between the stub device driver (SDD)
* and the Actual Device Driver (ADD).
* 
* SYNOPSIS
*
*\cs
* typedef struct 
*     {
*     MSG_HEADER hdr;			/@ message header @/
*     VB_ALIGN_FIELD_64 (void *buf, pad1);
*     VB_ALIGN_FIELD_64 (size_t buflen, pad2);
*     uint16_t request;			/@ request type @/
*     uint16_t op;			/@ request type @/
* #ifdef DEV_ASYNC_IOCTL
*     VB_ALIGN_FIELD_64 (uint64_t token, pad3); /@ token @/
* #endif
*     } MSG_PDC;
* 
*\ce
*
* The type of operations supported are 
*
*
*\cs
*
* * PDC_REQUEST_IOCTL
*
* * PDC_REQUEST_READ
*
* * PDC_REQUEST_WRITE
*
* * PDC_REQUEST_INIT
*
*\ce
*
*
* SEE ALSO: 
*\COMMAND
* This is a hypervisor PRIVATE data structure, hence marking it as 
* NOMANUAL to drop it from BSP guide documentation.
*
* \NOMANUAL
*/
  
typedef struct 
    {
    VBI_MSG_HDR hdr;			/* message header */
    VB_ALIGN_FIELD_64 (VOID_PTR buf, pad1);
    VB_ALIGN_FIELD_64 (size_t buflen, pad2);
    uint16_t request;			/* request type */
    uint16_t op;			/* request type */
#ifdef DEV_ASYNC_IOCTL
    VB_ALIGN_FIELD_64 (uint64_t token, pad3); /* token */
#endif
    } MSG_PDC;

/*******************************************************************************
*
* MSG_PDC_REPLY - process data channel PDC message reply format
*
* MSG_PDC is a C data type structure that provides the definition of the
* message reply format used to communicate to the stub device driver (SDD)
* from the Actual Device Driver (ADD).
* 
*  
* SYNOPSIS
*
*\cs
* 
* typedef struct 
*     {
*     MSG_HEADER hdr;			/@ message header @/
*     uint32_t   status;			/@ request completion status @/
*     uint32_t   dataVal;
*     } MSG_PDC_REPLY;
*\ce
*
* SEE ALSO: 
*\COMMAND
* This is a hypervisor PRIVATE data structure, hence marking it as 
* NOMANUAL to drop it from BSP guide documentation.
*
* \NOMANUAL
*/
typedef struct 
    {
    VBI_MSG_HDR hdr;			/* message header */
    uint32_t   status;			/* request completion status */
    uint32_t   dataVal;
    } MSG_PDC_REPLY;

/*******************************************************************************
*
* intrDeviceChannelBuffer - IDC Buffer
*
* IDC Buffer is a C data type structure that provides the definition of the
* interrupt device channel used by Hypervisor to pass information back to
* Stub device driver as a result of interrupt operation.
*  
* SYNOPSIS
*
* 
*\cs
* 
* #ifdef DEV_ASYNC_IOCTL
* typedef struct 
*     {
*     void *	buf;
*     uint64_t 	token;
*     VB_ALIGN_FIELD_64 (uint32_t op, pad7);
*     } ioctlOp;
* #endif /@ DEV_ASYNC_IOCTL @/
* 
* typedef struct intrDeviceChannelBuffer_ 
*     {
*     VB_ALIGN_FIELD_64 (void *rxBuf, pad1);	/@ rx buffer to receive @/
*     VB_ALIGN_FIELD_64 (size_t rxBufLen, pad2);	/@ rx buffer length @/
*     VB_ALIGN_FIELD_64 (void *txBuf, pad3);	/@ tx buffer to transmit @/
*     VB_ALIGN_FIELD_64 (size_t txBufLen, pad4);	/@ tx buffer length @/
*     uint32_t rxBufRdPtr;			/@ rx buffer read pointer @/
*     uint32_t rxBufWrPtr;			/@ rx buffer write pointer @/
*     uint32_t txBufRdPtr;			/@ tx buffer read pointer @/
*     uint32_t txBufWrPtr;			/@ tx buffer write pointer @/
*     uint32_t intStatus;				/@ intStatus, or what intr @/
* #ifdef DEV_ASYNC_IOCTL
*     VB_ALIGN_FIELD_64 (ioctlOp *ioctlBuf, pad5);	/@ ioctl buffer to receive @/
*     VB_ALIGN_FIELD_64 (size_t ioctlBufLen, pad6);	/@ ioctl buffer length @/
*     uint64_t ioctlBufRdPtr;			/@ ioctl buffer read pointer @/
*     uint64_t ioctlBufWrPtr;			/@ ioctl buffer write pointer @/
* #endif
*     } intrDeviceChannelBuffer;
*\ce
*
* RETURNS: N/A
*
* SEE ALSO: 
*\COMMAND
*/

#ifdef DEV_ASYNC_IOCTL
typedef struct 
    {
    VOID_PTR	buf;
    uint64_t 	token;
    VB_ALIGN_FIELD_64 (uint32_t op, pad7);
    } ioctlOp;
#endif /* DEV_ASYNC_IOCTL */
  
typedef struct intrDeviceChannelBuffer_ 
    {
    /*
     * From here down to intStatus things have to be the same as those of
     * intrDeviceChannelBuffer in HY wrhvDevCore.h.
     * One same struct may be read, shared in both VB and HY.
     */
    VB_ALIGN_FIELD_64 (VOID_PTR rxBuf, pad1);	/* rx buffer to receive */
    VB_ALIGN_FIELD_64 (size_t rxBufLen, pad2);	/* rx buffer length */
    VB_ALIGN_FIELD_64 (VOID_PTR txBuf, pad3);	/* tx buffer to transmit */
    VB_ALIGN_FIELD_64 (size_t txBufLen, pad4);	/* tx buffer length */
    uint32_t rxBufRdPtr;			/* rx buffer read pointer */
    uint32_t rxBufWrPtr;			/* rx buffer write pointer */
    uint32_t txBufRdPtr;			/* tx buffer read pointer */
    uint32_t txBufWrPtr;			/* tx buffer write pointer */
    uint32_t intStatus;				/* intStatus, or what intr */
#ifdef DEV_ASYNC_IOCTL
    VB_ALIGN_FIELD_64 (ioctlOp *ioctlBuf, pad5);  /* ioctl buffer to receive */
    VB_ALIGN_FIELD_64 (size_t ioctlBufLen, pad6); /* ioctl buffer length */
    uint64_t ioctlBufRdPtr;			/* ioctl buffer read pointer */
    uint64_t ioctlBufWrPtr;			/* ioctl buffer write pointer */
#endif
    } intrDeviceChannelBuffer;

typedef struct pdc_buf_set 
    {
    uint64_t  gpaBufBase;
    uint64_t  gpaBufLen;
    } PDC_BUF_SET;

#define SYS_PDC_REQUEST_OK 0
#define SYS_PDC_REQUEST_FAILED -1

#define PDC_IOCTL_SIO_BAUD_SET	 	1
#define PDC_IOCTL_SIO_MODE_SET	 	2
#define PDC_IOCTL_SIO_HW_OPTS_SET 	3
#define PDC_IOCTL_SIO_HUP	 	4
#define PDC_IOCTL_SIO_OPEN	 	5
#define PDC_IOCTL_BUF_GPA_GET           10
#define PDC_IOCTL_BUF_GPA_SET           11
#define PDC_IOCTL_BUF_SIZE_GET          12

#define PDC_IOCTL_AMIO_CHANNEL_SET      20

#define PDC_IOCTL_SIO_REQUEST_RESPONSE  0x8000
#define PDC_IOCTL_SIO_GET_IER	 	(PDC_IOCTL_SIO_REQUEST_RESPONSE | 2)


typedef enum vbiPdcRequest {
    PDC_REQUEST_MIN 		      = 1,
    PDC_REQUEST_IOCTL 		      = 1,
    PDC_REQUEST_READ 		      = 2,
    PDC_REQUEST_WRITE 		      = 3,
    PDC_REQUEST_INIT 		      = 4,
    PDC_REQUEST_ATTACH_GUEST	      = 5,
    PDC_REQUEST_DETACH_GUEST	      = 6,
    PDC_REQUEST_CORE_MSG	      = 7,
    PDC_REQUEST_MAX 		      = 7
    } VBI_PDC_REQUEST_TYPE;

extern vbiStatus_t vbiPdcOp (VBI_PDC_HANDLE pdcHandle,
			     VBI_PDC_REQUEST_TYPE requestType,
			     uint32_t ioctlOp,
			     void *bufferPtr,
			     size_t bufferLen,
			     uint64_t token);

extern vbiStatus_t vbiPdcInit(const char *instanceName,
			      VBI_PDC_HANDLE *pPdcHandle);

#endif 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbipdch */
