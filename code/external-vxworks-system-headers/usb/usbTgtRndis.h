/* usbTgtRndis.h - Definitions of USB rndis function drivers */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01c,04aug12,s_z  Adjust the usbtgt_rndis sturcture
01f,29sep11,s_z  Add direct callback mode to avoid asynch issue (WIND00306920)
01e,17aug11,s_z  Remove redefined macro
01d,11apr11,s_z  Add Open Specifications Documentation description
01c,22mar11,s_z  Code clean based on code review
01b,08mar11,s_z  Code clean up
01a,04jan11,s_z  written
*/

/*
DESCRIPTION

This file includes the definitions of USB RNDIS function driver.

This RNDIS function driver follows the [MS-RNDIS]:Remote Network Driver 
Interface Specification (RNDIS) Protocol Specification 1.0, which is one of the
Open Specifications Documentation.

Following is the Intellectual Property Rights Notice for Open Specifications 
Documentation:

\h Intellectual Property Rights Notice for Open Specifications Documentation

\h Technical Documentation. 

Microsoft publishes Open Specifications documentation for protocols, 
file formats, languages, standards as well as overviews of the interaction 
among each of these technologies.

\h Copyrights. 

This documentation is covered by Microsoft copyrights. Regardless of any other 
terms that are contained in the terms of use for the Microsoft website that
hosts this documentation, you may make copies of it in order to develop 
implementations of the technologies described in the Open Specifications 
and may distribute portions of it in your implementations using these 
technologies or your documentation as necessary to properly document the 
implementation. You may also distribute in your implementation, with or without 
modification, any schema, IDL's, or code samples that are included in the 
documentation. This permission also applies to any documents that are 
referenced in the Open Specifications.

\h No Trade Secrets.

Microsoft does not claim any trade secret rights in this documentation.

\h Patents.

Microsoft has patents that may cover your implementations of the technologies 
described in the Open Specifications. Neither this notice nor Microsoft's 
delivery of the documentation grants any licenses under those or any other 
Microsoft patents. However, a given Open Specification may be covered by 
Microsoft's Open Specification Promise (available here: 
http://www.microsoft.com/interop/osp) or the Community Promise 
(available here: http://www.microsoft.com/interop/cp/default.mspx).
If you would prefer a written license, or if the technologies described in 
the Open Specifications are not covered by the Open Specifications Promise 
or Community Promise, as applicable, patent licenses are available by 
contacting iplg@microsoft.com.

\h Trademarks. 

The names of companies and products contained in this 
documentation may be covered by trademarks or similar intellectual 
property rights. This notice does not grant any licenses under those rights.

\h Fictitious Names.

The example companies, organizations, products, 
domain names, e-mail addresses, logos, people, places, and events depicted in 
this documentation are fictitious. No association with any real company, 
organization, product, domain name, email address, logo, person, place, or 
event is intended or should be inferred.

\h Reservation of Rights. 

All other rights are reserved, and this notice does 
not grant any rights other than specifically described above, whether by 
implication, estoppel, or otherwise.

\h Tools. 

The Open Specifications do not require the use of Microsoft 
programming tools or programming environments in order for you to develop an 
implementation. If you have access to Microsoft programming tools and 
environments you are free to take advantage of them. Certain Open 
Specifications are intended for use in conjunction with publicly available 
standard specifications and network programming art, and assumes that the 
reader either is familiar with the aforementioned material or has immediate 
access to it.

INCLUDE FILES: usb/usbTgt.h 
*/

#ifndef __INCusbTgtRndish
#define __INCusbTgtRndish

#include <usb/usbTgt.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MEDIUM_TYPE_END_EMULATOR  0x01
#define MEDIUM_TYPE_END_BRIDGE    0x02

/* The RNDIS multicast list count */

#define RNDIS_MAX_MCAST_LIST_SZ     12
#define RNDIS_CTRL_MSG_BUF_SIZE     256

IMPORT int sysClkRateGet();


#define RNDIS_TX_TIMEOUT            (5 * sysClkRateGet()) /* in ticks */
#define RNDIS_TX_TIMEOUT_NO_WAIT    (0)

/* 2.8 Remote NDIS Version (RNDIS Specification 1.1) */

#define RNDIS_MAJOR_VERSION         1
#define RNDIS_MINOR_VERSION         0

/* 2.9 Status Value (RNDIS Specification 1.1) */

#define RNDIS_STATUS_SUCCESS              0x00000000  /* Success */
#define RNDIS_STATUS_FAILURE              0xC0000001
#define RNDIS_STATUS_INVALID_DATA         0xC0010015
#define RNDIS_STATUS_NOT_SUPPORTED        0xC00000BB
#define RNDIS_STATUS_MEDIA_CONNECT        0x4001000B
#define RNDIS_STATUS_MEDIA_DISCONNECT     0x4001000C

/* 3 Message Set for Connectionless (802.3) Device (RNDIS Specification 1.1) */

#define REMOTE_NDID_PACKET_MSG            0x00000001

#define REMOTE_NDIS_INITIALIZE_MSG        0x00000002  /* Init the device */
#define REMOTE_NDIS_HALT_MSG              0x00000003  /* Halt the device */
#define REMOTE_NDIS_QUERY_MSG             0x00000004  /* Send a query OID */
#define REMOTE_NDIS_SET_MSG               0x00000005  /* Send a set OID */
#define REMOTE_NDIS_RESET_MSG             0x00000006  /* Perform a soft reset on the device */
#define REMOTE_NDIS_INDICATE_STATUS_MSG   0x00000007  /* 802.3 link status or undefined msg error */
#define REMOTE_NDIS_KEEPALIVE_MSG         0x00000008  /* Keep alive */

#define REMOTE_NDIS_INITIALIZE_CMPLT      0x80000002  /* Response init msg */
#define REMOTE_NDIS_QUERY_CMPLT           0x80000004  /* Response query msg */
#define REMOTE_NDIS_SET_CMPLT             0x80000005  /* Response set msg */
#define REMOTE_NDIS_RESET_CMPLT           0x80000006  /* Response reset msg */
#define REMOTE_NDIS_KEEPALIVE_CMPLT       0x80000008  /* Response keepalive msg */


/* 4. Required NDIS OIDs (RNDIS Specification 1.1) */

/* 4.1 General OIDs (RNDIS Specification 1.1) */

#define OID_GEN_SUPPORTED_LIST            0x00010101 /* List of supported OIDs */
#define OID_GEN_HARDWARE_STATUS           0x00010102 /* Hardware status */
#define OID_GEN_MEDIA_SUPPORTED           0x00010103 /* Media types supported */
#define OID_GEN_MEDIA_IN_USE              0x00010104 /* Media types in use */


#define OID_GEN_MAXIMUM_LOOKAHEAD         0x00010105 /**/

#define OID_GEN_MAXIMUM_FRAME_SIZE        0x00010106
#define OID_GEN_LINK_SPEED                0x00010107

#define OID_GEN_TRANSMIT_BUFFER_SPACE     0x00010108 /**/
#define OID_GEN_RECEIVE_BUFFER_SPACE      0x00010109 /**/

#define OID_GEN_TRANSMIT_BLOCK_SIZE       0x0001010A
#define OID_GEN_RECEIVE_BLOCK_SIZE        0x0001010B
#define OID_GEN_VENDOR_ID                 0x0001010C
#define OID_GEN_VENDOR_DESCRIPTION        0x0001010D

#define OID_GEN_CURRENT_PACKET_FILTER     0x0001010E

#define OID_GEN_CURRENT_LOOKAHEAD         0x0001010F /**/
#define OID_GEN_DRIVER_VERSION            0x00010110 /**/


#define OID_GEN_MAXIMUM_TOTAL_SIZE        0x00010111

#define OID_GEN_PROTOCOL_OPTIONS          0x00010112
#define OID_GEN_MAC_OPTIONS               0x00010113
#define OID_GEN_MEDIA_CONNECT_STATUS      0x00010114
#define OID_GEN_MAXIMUM_SEND_PACKETS      0x00010115
#define OID_GEN_VENDOR_DRIVER_VERSION     0x00010116
#define OID_GEN_SUPPORTED_GUIDS           0x00010117
#define OID_GEN_NETWORK_LAYER_ADDRESSES   0x00010118
#define OID_GEN_TRANSPORT_HEADER_OFFSET   0x00010119
#define OID_GEN_MACHINE_NAME              0x0001021A
#define OID_GEN_RNDIS_CONFIG_PARAMETER    0x0001021B
#define OID_GEN_VLAN_ID                   0x0001021C

/* Optional OIDs */

#define OID_GEN_MEDIA_CAPABILITIES        0x00010201
#define OID_GEN_PHYSICAL_MEDIUM           0x00010202

/* Required statistics OIDs */

#define OID_GEN_XMIT_OK                   0x00020101
#define OID_GEN_RCV_OK                    0x00020102
#define OID_GEN_XMIT_ERROR                0x00020103
#define OID_GEN_RCV_ERROR                 0x00020104
#define OID_GEN_RCV_NO_BUFFER             0x00020105

/* Optional statistics OIDs */

#define OID_GEN_DIRECTED_BYTES_XMIT       0x00020201
#define OID_GEN_DIRECTED_FRAMES_XMIT      0x00020202
#define OID_GEN_MULTICAST_BYTES_XMIT      0x00020203
#define OID_GEN_MULTICAST_FRAMES_XMIT     0x00020204
#define OID_GEN_BROADCAST_BYTES_XMIT      0x00020205
#define OID_GEN_BROADCAST_FRAMES_XMIT     0x00020206
#define OID_GEN_DIRECTED_BYTES_RCV        0x00020207
#define OID_GEN_DIRECTED_FRAMES_RCV       0x00020208
#define OID_GEN_MULTICAST_BYTES_RCV       0x00020209
#define OID_GEN_MULTICAST_FRAMES_RCV      0x0002020A
#define OID_GEN_BROADCAST_BYTES_RCV       0x0002020B
#define OID_GEN_BROADCAST_FRAMES_RCV      0x0002020C
#define OID_GEN_RCV_CRC_ERROR             0x0002020D
#define OID_GEN_TRANSMIT_QUEUE_LENGTH     0x0002020E
#define OID_GEN_GET_TIME_CAPS             0x0002020F
#define OID_GEN_GET_NETCARD_TIME          0x00020210
#define OID_GEN_NETCARD_LOAD              0x00020211
#define OID_GEN_DEVICE_PROFILE            0x00020212
#define OID_GEN_INIT_TIME_MS              0x00020213
#define OID_GEN_RESET_COUNTS              0x00020214
#define OID_GEN_MEDIA_SENSE_COUNTS        0x00020215
#define OID_GEN_FRIENDLY_NAME             0x00020216
#define OID_GEN_MINIPORT_INFO             0x00020217
#define OID_GEN_RESET_VERIFY_PARAMETERS   0x00020218

/* IEEE 802.3 (Ethernet) OIDs */

#define NDIS_802_3_MAC_OPTION_PRIORITY    0x00000001

#define OID_802_3_PERMANENT_ADDRESS       0x01010101
#define OID_802_3_CURRENT_ADDRESS         0x01010102
#define OID_802_3_MULTICAST_LIST          0x01010103
#define OID_802_3_MAXIMUM_LIST_SIZE       0x01010104
#define OID_802_3_MAC_OPTIONS             0x01010105
#define OID_802_3_RCV_ERROR_ALIGNMENT     0x01020101
#define OID_802_3_XMIT_ONE_COLLISION      0x01020102
#define OID_802_3_XMIT_MORE_COLLISIONS    0x01020103
#define OID_802_3_XMIT_DEFERRED           0x01020201
#define OID_802_3_XMIT_MAX_COLLISIONS     0x01020202
#define OID_802_3_RCV_OVERRUN             0x01020203
#define OID_802_3_XMIT_UNDERRUN           0x01020204
#define OID_802_3_XMIT_HEARTBEAT_FAILURE  0x01020205
#define OID_802_3_XMIT_TIMES_CRS_LOST     0x01020206
#define OID_802_3_XMIT_LATE_COLLISIONS    0x01020207

/* OID_GEN_MINIPORT_INFO constants */

#define NDIS_MINIPORT_BUS_MASTER                      0x00000001
#define NDIS_MINIPORT_WDM_DRIVER                      0x00000002
#define NDIS_MINIPORT_SG_LIST                         0x00000004
#define NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY            0x00000008
#define NDIS_MINIPORT_INDICATES_PACKETS               0x00000010
#define NDIS_MINIPORT_IGNORE_PACKET_QUEUE             0x00000020
#define NDIS_MINIPORT_IGNORE_REQUEST_QUEUE            0x00000040
#define NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS        0x00000080
#define NDIS_MINIPORT_INTERMEDIATE_DRIVER             0x00000100
#define NDIS_MINIPORT_IS_NDIS_5                       0x00000200
#define NDIS_MINIPORT_IS_CO                           0x00000400
#define NDIS_MINIPORT_DESERIALIZE                     0x00000800
#define NDIS_MINIPORT_REQUIRES_MEDIA_POLLING          0x00001000
#define NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE            0x00002000
#define NDIS_MINIPORT_NETBOOT_CARD                    0x00004000
#define NDIS_MINIPORT_PM_SUPPORTED                    0x00008000
#define NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE  0x00010000
#define NDIS_MINIPORT_USES_SAFE_BUFFER_APIS           0x00020000
#define NDIS_MINIPORT_HIDDEN                          0x00040000
#define NDIS_MINIPORT_SWENUM                          0x00080000
#define NDIS_MINIPORT_SURPRISE_REMOVE_OK              0x00100000
#define NDIS_MINIPORT_NO_HALT_ON_SUSPEND              0x00200000
#define NDIS_MINIPORT_HARDWARE_DEVICE                 0x00400000
#define NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS    0x00800000
#define NDIS_MINIPORT_64BITS_DMA                      0x01000000


#define OID_GEN_SUPPORTED_LIST                  0x00010101
#define OID_GEN_HARDWARE_STATUS                 0x00010102
#define OID_GEN_MEDIA_SUPPORTED                 0x00010103
#define OID_GEN_MEDIA_IN_USE                    0x00010104
#define OID_GEN_MAXIMUM_FRAME_SIZE              0x00010106
#define OID_GEN_LINK_SPEED                      0x00010107
#define OID_GEN_TRANSMIT_BLOCK_SIZE             0x0001010A
#define OID_GEN_RECEIVE_BLOCK_SIZE              0x0001010B
#define OID_GEN_VENDOR_ID                       0x0001010C
#define OID_GEN_VENDOR_DESCRIPTION              0x0001010D
#define OID_GEN_CURRENT_PACKET_FILTER           0x0001010E
#define OID_GEN_MAXIMUM_TOTAL_SIZE              0x00010111
#define OID_GEN_MAC_OPTIONS                     0x00010113
#define OID_GEN_MEDIA_CONNECT_STATUS            0x00010114
#define OID_GEN_SUPPORTED_GUIDS                 0x00010117

#define RNDIS_DF_CONNECTIONLESS                (0x00000001)

/* Optional Power Management OIDs */

#define OID_PNP_CAPABILITIES                    0xFD010100
#define OID_PNP_SET_POWER                       0xFD010101
#define OID_PNP_QUERY_POWER                     0xFD010102

/* Optional Network Wakeup */

#define OID_PNP_ADD_WAKE_UP_PATTERN             0xFD010103
#define OID_PNP_REMOVE_WAKE_UP_PATTERN          0xFD010104
#define OID_PNP_ENABLE_WAKE_UP                  0xFD010106

/* The RNDIS MAC options */

#define RNDIS_MAC_OPTION_RECEIVE_SERIALIZED     0x00000002
#define RNDIS_MAC_OPTION_FULL_DUPLEX            0x00000010

/*  Bits for OID_PNP_ENABLE_WAKE_UP */

#define RNDIS_PNP_WAKE_UP_MAGIC_PACKET          0x00000001
#define RNDIS_PNP_WAKE_UP_PATTERN_MATCH         0x00000002
#define RNDIS_PNP_WAKE_UP_LINK_CHANGE           0x00000004

/* wake-up capabilities */

#define RNDIS_DEVICE_WAKE_UP_ENABLE               0x00000001
#define RNDIS_DEVICE_WAKE_ON_PATTERN_MATCH_ENABLE 0x00000002
#define RNDIS_DEVICE_WAKE_ON_MAGIC_PACKET_ENABLE  0x00000004

/* The medium type which can be supported by RNDIS */

#define RNDIS_MEDIUM_802_3        0x00000000  /* Specifies an Ethernet medium. */
#define RNDIS_MEDIUM_802_5        0x00000001  /* Specifies a token ring medium. */
#define RNDIS_MEDIUM_Fddi         0x00000002  /* FDDI */
#define RNDIS_MEDIUM_Wan          0x00000003  /* Specifies a WAN medium. */
#define RNDIS_MEDIUM_LocalTalk    0x00000004  /* LocalTalk. */
#define RNDIS_MEDIUM_ArcnetRaw    0x00000006  /* ArcnetRaw */
#define RNDIS_MEDIUM_Arcnet878_2  0x00000007  /* Arcnet878_2 */
#define RNDIS_MEDIUM_Atm          0x00000008  /* Atm */
#define RNDIS_MEDIUM_WirelessWan  0x00000009  /* WirelessWan */
#define RNDIS_MEDIUM_Irda         0x0000000a  /* Specifies an IrDA (infrared) medium. */
#define RNDIS_MEDIUM_CoWan        0x0000000b  /* CoWan */
#define RNDIS_MEDIUM_Max          0x0000000d  /* Not a real medium, defined as an upper-bound. */


/* typedefs */

typedef enum
    {
    RNDIS_UNINITIALIZED,
    RNDIS_INITIALIZED,
    RNDIS_DATA_INITIALIZED
    } RNDIS_STATE;

typedef enum
    {
    RNDIS_MEDIA_STATE_CONNECTED = 0,
    RNDIS_MEDIA_STATE_DISCONNECTED
    } NDIS_MEDIA_STATE;

typedef enum
    {
    RNDIS_HARDWARE_STATUS_READY,
    RNDIS_HARDWARE_STATUS_INITIALIZING,
    RNDIS_HARDWARE_STATUS_RESET,
    RNDIS_HARDWARE_STATUS_CLOSING,
    RNDIS_HARDWARE_STATUS_NOTREADY
    } NDIS_HARDWARE_STATUS;

typedef struct
    {
    UINT32 msgType;
    UINT32 msgLen;
    } RNDIS_MSG_HDR,*pRNDIS_MSG_HDR;
    
typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 majorVersion;
    UINT32 minorVersion;
    UINT32 maxXferSize;
    }RNDIS_INITIALIZE_MSG,*pRNDIS_INITIALIZE_MSG;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 status;
    UINT32 majorVersion;
    UINT32 minorVersion;
    UINT32 deviceFlags;
    UINT32 medium;
    UINT32 maxPktsPerMsg;
    UINT32 maxXferSize;
    UINT32 pktAlignmentFactor;
    UINT32 AFListOffset;
    UINT32 AFListSize;
    }RNDIS_INITIALIZE_CMPLT,*pRNDIS_INITIALIZE_CMPLT;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    }RNDIS_HALT_MSG,*pRNDIS_HALT_MSG;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    }RNDIS_KEEPALIVE_MSG,*pRNDIS_KEEPALIVE_MSG;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 oid;
    UINT32 infoBufLen;
    UINT32 infoBufOffset;
    UINT32 devVcHandle;
    }RNDIS_QUERY_MSG,*pRNDIS_QUERY_MSG;

typedef RNDIS_QUERY_MSG RNDIS_SET_MSG;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 status;
    UINT32 infoBufLen;
    UINT32 infoBufOffset;
    }RNDIS_QUERY_CMPLT,*pRNDIS_QUERY_CMPLT;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 status;
    }RNDIS_SET_CMPLT,*pRNDIS_SET_CMPLT;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 requestId;
    UINT32 status;
    }RNDIS_KEEPALIVE_CMPLT,*pRNDIS_KEEPALIVE_CMPLT;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 reserved;
    }RNDIS_RESET_MSG,*pRNDIS_RESET_MSG;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 status;
    UINT32 addressingReset;
    }RNDIS_RESET_CMPLT,*pRNDIS_RESET_CMPLT;

typedef struct
    {
    RNDIS_MSG_HDR hdr;
    UINT32 status;
    UINT32 statusBufLen;
    UINT32 statusBufOffset;
    }RNDIS_INDICATE_STATUS_MSG,*pRNDIS_INDICATE_STATUS_MSG;

typedef struct
    {
    UINT32 msgType;
    UINT32 reserved;
    }RESPONSE_AVAILABLE_MSG,*pRESPONSE_AVAILABLE_MSG;

typedef struct 
    {
    UINT32 msgType;
    UINT32 msgLen;
    UINT32 dataOffset;
    UINT32 dataLen;
    UINT32 oobDataOffset;
    UINT32 oobDataLen;
    UINT32 oobNumDataElem;
    UINT32 perPktInfoOffset;
    UINT32 perPktInfoLength;
    UINT32 vcHandle;
    UINT32 reserved;
    }RNDIS_PACKET_MSG,*pRNDIS_PACKET_MSG;

/*  power states */

typedef enum
    {
    RNDIS_DEVICE_STATE_UNSPECIFIED,
    RNDIS_DEVICE_STATE_D0,
    RNDIS_DEVICE_STATE_D1,
    RNDIS_DEVICE_STATE_D2,
    RNDIS_DEVICE_STATE_D3,
    RNDIS_DEVICE_STATE_MAXIMUM
    }RNDIS_DEVICE_POWER_STATE;

/* wake-up capabilities */

typedef struct
    {
    RNDIS_DEVICE_POWER_STATE minMagicPacketWakeUp;
    RNDIS_DEVICE_POWER_STATE minPatternWakeUp;
    RNDIS_DEVICE_POWER_STATE minLinkChangeWakeUp;
    }RNDIS_PM_WAKE_UP_CAPABILITIES, *pRNDIS_PM_WAKE_UP_CAPABILITIES;

/* PnP capabilities */

typedef struct
    {
    UINT32                        flags;
    RNDIS_PM_WAKE_UP_CAPABILITIES wakeUpCapabilities;
    }RNDIS_PNP_CAPABILITIES,*pRNDIS_PNP_CAPABILITIES;

/* Packet pattern */

typedef struct
    {
    UINT32 priority;
    UINT32 reserved;
    UINT32 maskSize;
    UINT32 patternOffset;
    UINT32 patternSize;
    UINT32 patternFlags;
    }RNDIS_PM_PACKET_PATTERN,*pRNDIS_PM_PACKET_PATTERN;

typedef struct
    {
    NODE   node;
    UINT32 length;
    }RNDIS_PM_PATTERN_LIST_HEADER,* pRNDIS_PM_PATTERN_LIST_HEADER;

/* The power management pattern list entry */

typedef struct
    {
    RNDIS_PM_PATTERN_LIST_HEADER header;
    RNDIS_PM_PACKET_PATTERN      pattern;
    }RNDIS_PM_PATTERN_LIST_ENTRY,* pRNDIS_PM_PATTERN_LIST_ENTRY;

/* The configuration parameter */

typedef struct
    {
    UINT32 parameterNameOffset;
    UINT32 parameterNameLength;
    UINT32 parameterType;
    UINT32 parameterValueOffset;
    UINT32 parameterValueLength;
    }RNDIS_CONFIG_PARAMETER,*pRNDIS_CONFIG_PARAMETER;

/* Add macro to mask the RNDIS task mode */

#undef USBTGT_NET_TASK_MODE

/* The RNDIS data structure */

typedef struct usbtgt_rndis
    {
    NODE                rndisNode;           /* Node used to link on the dev list */
    USB_TARG_CHANNEL    targChannel;         /* TargChannel */
    SEM_ID              rndisMutex;          /* Used to protect the resource */    
    char *              pMediumName;         /* Medium name attached on RNDIS */
    UINT8               uMediumUnit;         /* Medium unit attached on RNDIS */
    UINT8               uMediumType;         /* Medium type attached on RNDIS */ 
    struct usbtgt_binder * pBinder;          /* Pointer of the medium binder */
#if defined (USBTGT_NET_TASK_MODE)
    MSG_Q_ID            RndisTaskMsgQID;     /* Task msgQ id */
    OS_THREAD_ID        RndisTaskID;         /* Tasl ID */
#endif /* USBTGT_NET_TASK_MODE */    
    UINT8               requestMsgBuf[RNDIS_CTRL_MSG_BUF_SIZE];
    UINT8               replyMsgBuf[RNDIS_CTRL_MSG_BUF_SIZE];
    UINT16              uRequestMsgLen;      /* Length of the request message */
    UINT16              uReplyMsgLen;        /* Length of the reply message */
    USB_TARG_PIPE       intInPipeHandle;     /* Interrup In pipe handle */
    USB_ERP             intInErp;            /* Interrup In ERP */
    UINT8               intInBuf[8];         /* Buffer used by Interrupt In transaction */
    SEM_ID              intInErpMutex;       /* Interrupt In transfer mutex */
    UINT8               uIntInPipeStatus;    /* Interrupt In pipe stall or not */
    BOOL                bIntInErpUsed;       /* Interrupt In ERP is used or not */
    USB_TARG_PIPE       bulkOutPipeHandle;   /* Bulk pipe handle */
    USB_ERP             bulkOutErp;          /* Bulk ERP */
    UINT8 *             pBulkOutBuf;         /* Buffer used by Bulk Out transaction */
    SEM_ID              bulkOutErpMutex;     /* Bulk Out transfer mutex */
    UINT8               uBulkOutPipeStatus;  /* Bulk Out pipe stall or not */
    BOOL                bBulkOutErpUsed;     /* Bulk Out ERP is used or not */
    USB_TARG_PIPE       bulkInPipeHandle;    /* Bulk pipe handle */
    USB_ERP             bulkInErp;           /* Bulk ERP */
    UINT8 *             pBulkInBuf;          /* Buffer used by Bulk In transaction */
    SEM_ID              bulkInErpMutex;      /* Bulk In transfer mutex */
    UINT8               uBulkInPipeStatus;   /* Bulk In pipe stall or not */
    BOOL                bBulkInErpUsed;      /* Bulk In ERP is used or not */
    RNDIS_STATE         rndisState;          /* Rndis state */
    UINT32              rndisFilterValue;    /* Filter value used by the NIC */
    UINT8               uConfigurationValue; /* Configuration value */
    UINT8               uInterfaceNubmer;    /* Number of interface which holds this endpoint */
    UINT8               uAltSetting;         /* Alternate Setting */
    UINT32              uSpeed;              /* USB Speed */
    RNDIS_DEVICE_POWER_STATE powerState;     /* Power state */
    BOOL                wakeUpnMagicPacketEnable;
    BOOL                wakeUpPatternMatchEnable;
    BOOL                wakeUpLinkChangeEnable;
    LIST                wakeUpPatternList;
    }USBTGT_RNDIS,*pUSBTGT_RNDIS;

/* The notify command */

typedef enum usbtgt_rndis_notify_code
    {
    USBTGT_RNDIS_NOTIFY_UNKNOWN              = (0),
    USBTGT_RNDIS_NOTIFY_RESET_EVENT          = (1),
    USBTGT_RNDIS_NOTIFY_DISCONNECT_EVENT     = (2),
    USBTGT_RNDIS_NOTIFY_SUSPEND_EVENT        = (3),
    USBTGT_RNDIS_NOTIFY_RESUME_EVENT         = (4),
    USBTGT_RNDIS_NOTIFY_DATA_CHANNEL_RESET   = (5),
    USBTGT_RNDIS_NOTIFY_REQUIRE_DATA_OUT     = (6),
    USBTGT_RNDIS_NOTIFY_XMIT_DATA_TO_MEDIUM  = (7),
    USBTGT_RNDIS_NOTIFY_RCV_DATA_FROM_MEDIUM = (8)
    }USBTGT_RNDIS_NOTIFY_CODE;

/* Notify info data structure */

typedef struct usbtgt_rndis_notify_info
    {
    struct usbtgt_rndis *    pUsbTgtRndis;     /* RNDIS device pointer */
    USBTGT_RNDIS_NOTIFY_CODE NotifyCode;       /* The code of the notification */
    void *                   pContext;         /* The context used by the notification */
    } USBTGT_RNDIS_NOTIFY_INFO,*pUSBTGT_RNDIS_NOTIFY_INFO;

/* externs */

IMPORT STATUS usbTgtRndisUnInit
    (
    void
    );

IMPORT STATUS usbTgtRndisInit
    (
    void
    );

IMPORT void usbTgtRndisManagementNotify
    (
    pUSBTGT_RNDIS            pUsbTgtRndis,
    USBTGT_RNDIS_NOTIFY_CODE NotifyCode,
    void *                   pContext
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCusbTgtRndish */


