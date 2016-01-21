/* usbCdc.h - Definitions for USB CDC class */

/*
 * Copyright (c) 2009, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,05mar09,w_x  Created.
*/

#ifndef __INCusbCdch
#define __INCusbCdch

/* includes */

#include <usb/usb.h>
#include <usb/usbPlatform.h>

#ifdef    __cplusplus
extern "C" {
#endif

/* defines */

/*
 * USB CDC classes
 */

/*
 * 4.1 Communication Device Class Code
 * 4.2 Communication Interface Class Code
 *
 * Note that both the device level and interface level use
 * the same value as the class code.
 */

#define USB_CLASS_COMM              0x02

/*
 * 4.5 Data Interface Class Codes
 */

#define USB_CLASS_CDC_DATA          0x0A

/*
 * USB CDC subclasses
 */

/*
 * 4.3 Communication Interface Class SubClass Codes
 *
 * Note that codes from 0x08 up to 0x0C are added
 * in CDC 1.2 specification.
 */

#define USB_CDC_SUBCLASS_DLCM       0x01 /* Direct Line Control Model */
#define USB_CDC_SUBCLASS_ACM        0x02 /* Abstract Control Model */
#define USB_CDC_SUBCLASS_TCM        0x03 /* Telephone Control Model */
#define USB_CDC_SUBCLASS_MCCM       0x04 /* Multi-Channel Control Model */
#define USB_CDC_SUBCLASS_CAPI       0x05 /* CAPI Control Model */
#define USB_CDC_SUBCLASS_ETH        0x06 /* Ethernet Networking Control Model */
#define USB_CDC_SUBCLASS_ATM        0x07 /* ATM Networking Control Model */
#define USB_CDC_SUBCLASS_WHCM       0x08 /* Wireless Handset Control Model */
#define USB_CDC_SUBCLASS_DM         0x09 /* Device Management */
#define USB_CDC_SUBCLASS_MDLM       0x0A /* Mobile Direct Line Model */
#define USB_CDC_SUBCLASS_OBEX       0x0B /* OBject EXchange */
#define USB_CDC_SUBCLASS_EEM        0x0C /* Ethernet Emulation Model */

/*
 * USB CDC protocols
 */

/*
 * 4.4 Communication Interface Class Control Protocol Codes
 *
 * Note that codes from 0x02 and up are added in CDC 1.2
 * specification.
 */

#define USB_CDC_PROTO_NONE              0x00 /* No class specific protocol required */
#define USB_CDC_PROTO_AT_V25TER         0x01 /* AT Commands: V.250 etc */
#define USB_CDC_PROTO_AT_PCCA101        0x02 /* AT Commands defined by PCCA-101 */
#define USB_CDC_PROTO_AT_PCCA101_ANNEX  0x03 /* AT Commands defined by PCCA-101 & Annex O */
#define USB_CDC_PROTO_AT_GSM            0x04 /* AT Commands defined by GSM 07.07 */
#define USB_CDC_PROTO_AT_3GPP           0x05 /* AT Commands defined by 3GPP 27.007 */
#define USB_CDC_PROTO_AT_CDMA           0x06 /* AT Commands defined by TIA for CDMA */
#define USB_CDC_PROTO_EEM               0x07 /* Ethernet Emulation Model */
#define USB_CDC_PROTO_EXT               0xFE /* External Protocol: Commands
                                              * defined by Command Set
                                              * Functional Descriptor */
#define USB_CDC_ACM_PROTO_VENDOR        0xFF /* Vendor-specific */

/*
 * 5.2.3 Functional Descriptors
 *
 * Table 24: Type Values for the bDescriptorType Field
 *
 * Note that these are class specific descriptor types,
 * may need to move to common places.
 */

#define USB_DESCR_CS_INTERFACE                  (0x20 | USB_DESCR_INTERFACE)
#define USB_DESCR_CS_ENDPOINT                   (0x20 | USB_DESCR_ENDPOINT)

/*
 * USB CDC class specific sub-descriptor types
 *
 * Table 25: bDescriptor SubType in Functional Descriptors
 */

#define USB_CDC_CS_HEADER_TYPE                  0x00 /* Header */
#define USB_CDC_CS_CALL_MANAGEMENT_TYPE         0x01 /* Call Management */
#define USB_CDC_CS_ACM_TYPE                     0x02 /* Abstract Control Management */
#define USB_CDC_CS_DLM_TYPE                     0x03 /* Direct Line Management */
#define USB_CDC_CS_TEL_RING_TYPE                0x04 /* Telephone Ringer */
#define USB_CDC_CS_TEL_CALL_CAP_TYPE            0x05 /* Telephone Call and Line
                                                      * State Reporting Capabilities */
#define USB_CDC_CS_UNION_TYPE                   0x06 /* Union */
#define USB_CDC_CS_COUNTRY_TYPE                 0x07 /* Country Selection */
#define USB_CDC_CS_TEL_OP_MODE_TYPE             0x08 /* Telephone Operational Modes */
#define USB_CDC_CS_USB_TERMINAL_TYPE            0x09 /* USB Terminal */
#define USB_CDC_CS_NWK_TERMINAL_TYPE            0x0A /* Network Channel Terminal */
#define USB_CDC_CS_PROTO_UNION_TYPE             0x0B /* Protocol Unit */
#define USB_CDC_CS_EXTENSION_UNION_TYPE         0x0C /* Extension Unit */
#define USB_CDC_CS_MULTI_CHAN_MGMT_TYPE         0x0D /* Multi-Channel Management */
#define USB_CDC_CS_CAPI_CTRL_MGMT_TYPE          0x0E /* CAPI Control Management */
#define USB_CDC_CS_ETH_NWK_TYPE                 0x0F /* Ethernet Networking */
#define USB_CDC_CS_ATM_NWK_TYPE                 0x10 /* ATM Networking */
#define USB_CDC_CS_WHCM_TYPE                    0x11 /* Wireless Handset Control Model */
#define USB_CDC_CS_MDLM_TYPE                    0x12 /* Mobile Direct Line Model */
#define USB_CDC_CS_MDLM_DETAIL_TYPE             0x13 /* MDLM Detail */
#define USB_CDC_CS_DEV_MGMT_MODEL_TYPE          0x14 /* Device Management Model */
#define USB_CDC_CS_OBEX_TYPE                    0x15 /* OBEX */
#define USB_CDC_CS_CMD_SET_TYPE                 0x16 /* Command Set */
#define USB_CDC_CS_CMD_SET_DETAIL_TYPE          0x17 /* Command Set Detail */
#define USB_CDC_CS_TEL_CTRL_MODEL_TYPE          0x18 /* Telephone Control Model */
#define USB_CDC_CS_OBEX_SERVICE_ID_TYPE         0x19 /* OBEX Service Identifier */

/*
 * 5.2.3.1 Header Functional Descriptor
 *
 * The class-specific descriptor shall start with a header
 * that is defined in Table 23. The bcdCDC field identifies
 * the release of the USB Class Definitions for Communication
 * Devices Specification (this specification) with which this
 * interface and its descriptors comply.
 */

typedef struct usb_cdc_header_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Header functional descriptor subtype */
    UINT16   bcdCDC;                /* USB Class Definitions for Communication
                                     * Devices Specification release number in
                                     * binary-coded decimal */
    } __attribute__ ((packed)) USB_CDC_HEADER_DESCR;

/*
 * 5.2.3.2 Call Management Functional Descriptor
 *
 * The Call Management functional descriptor describes the
 * processing of calls for the Communication Class interface.
 * It can only occur within the class-specific portion of
 * an Interface descriptor.
 */

typedef struct usb_cdc_call_mgmt_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Call Management functional descriptor */
    UINT8    bmCapabilities;        /* The capabilities this configuration supports */
    UINT8    bDataInterface;        /* Interface number of Data Class interface
                                     * optionally used for call management */
    } __attribute__ ((packed)) USB_CDC_CALL_MGMT_DESCR;

/* USB_CDC_CALL_MGMT_DESCR::bmCapabilities bitmap definitions - START */

/*
 * Call management indication:
 *
 * 0 - Device does not handle call management itself.
 * 1 - Device handles call management itself.
 */

#define USB_CDC_CALL_MGMT_CAP_CALL_MGMT        0x01

/*
 * Call management information interface indication:
 *
 * 0 - Device sends/receives call management information only over
 * the Communication Class interface.
 * 1 - Device can send/receive call management information over a
 * Data Class interface.
 */

#define USB_CDC_CALL_MGMT_CAP_DATA_INTF        0x02

/* USB_CDC_CALL_MGMT_DESCR::bmCapabilities bitmap definitions - END */

/*
 * 5.2.3.3 Abstract Control Management Functional Descriptor
 *
 * The Abstract Control Management functional descriptor
 * describes the commands supported by the Communication
 * Class interface, as defined in Section 3.6.2, with the
 * SubClass code of Abstract Control Model. It can only occur
 * within the class-specific portion of an Interface descriptor.
 */

typedef struct usb_cdc_acm_mgmt_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Abstract Control Management functional descriptor */
    UINT8    bmCapabilities;        /* The capabilities this configuration supports */
    } __attribute__ ((packed)) USB_CDC_ACM_MGMT_DESCR;

/* USB_CDC_ACM_MGMT_DESCR::bmCapabilities bitmap definitions - START */

/*
 * Device supports the request combination of
 * Set_Comm_Feature,Clear_Comm_Feature, and Get_Comm_Feature.
 */

#define USB_CDC_COMM_FEATURE         0x01

/*
 * Device supports the request combination of Set_Line_Coding,
 * Set_Control_Line_State, Get_Line_Coding, and the notification
 * Serial_State.
 */

#define USB_CDC_CAP_LINE_CODING       0x02

/* Device supports the request Send_Break */

#define USB_CDC_CAP_SEND_BREAK        0x04

/* Device supports the notification Network_Connection */

#define USB_CDC_CAP_NOTIFY_NWK_CONN   0x08

/* USB_CDC_ACM_MGMT_DESCR::bmCapabilities bitmap definitions - END */

/*
 * 5.2.3.8 Union Functional Descriptor
 *
 * The Union functional descriptor describes the relationship
 * between a group of interfaces that can be considered to form
 * a functional unit. It can only occur within the class-specific
 * portion of an Interface descriptor. One of the interfaces in
 * the group is designated as a master or controlling interface
 * for the group, and certain class-specific messages can be
 * sent to this interface to act upon the group as a whole.
 * Similarly, notifications for the entire group can be sent from
 * this interface but apply to the entire group of interfaces.
 * Interfaces in this group can include Communication, Data, or
 * any other valid USB interface class (including, but not limited
 * to, Audio, HID, and Monitor).
 */

typedef struct usb_cdc_union_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Union functional descriptor */
    UINT8    bMasterInterface0;     /* The interface number of the Communications
                                     * or Data Class interface, designated as
                                     * the controlling interface for the union
                                     */
    UINT8    bSlaveInterface0;      /* Interface number of first interface in the union */
    /* This may be followed by more slave interface numbers */
    } __attribute__ ((packed)) USB_CDC_UNION_DESCR;

/*
 * 5.2.3.9 Country Selection Functional Descriptor
 *
 * The Country Selection functional descriptor identifies
 * the countries in which the communication device is qualified to
 * operate. The parameters of the network connection often vary
 * from one country to another, especially in Europe. Also legal
 * requirements impose certain restrictions on devices because of
 * different regulations by the governing body of the network to
 * which the device must adhere. This descriptor can only occur
 * within the class-specific portion of an Interface descriptor
 * and should only be provided to a master Communication Class
 * interface of a union. The country codes used in the Country
 * Selection Functional Descriptor are not the same as the country
 * codes used in dialing international telephone calls. Implementers
 * should refer to the ISO 3166 specification for more information.
 */

typedef struct usb_cdc_country_selection_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Country Selection functional descriptor */
    UINT8    iCountryCodeRelDate;   /* Index of a string giving the release date
                                     * for the implemented ISO 3166 Country Codes.
                                     * Date shall be presented as ddmmyyyy with
                                     * dd=day, mm=month, and yyyy=year */
    UINT16   wCountyCode0;          /* Country code in the format as defined
                                     * in [ISO3166], release date as specified
                                     * in offset 3 for the first supported
                                     * country
                                     */
    /* This may be followed by more supported country code */
    } __attribute__ ((packed)) USB_CDC_COUNTRY_SELECTION_DESCR;

/*
 * 5.2.3.11 Network Channel Terminal Functional Descriptor
 *
 * The Network Channel Terminal Functional descriptor provides
 * a means to indicate a relationship between a Unit and a
 * Network Channel. It can only occur within the class-specific
 * portion of an Interface descriptor.
 */

typedef struct usb_cdc_network_channel_terminal_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Network Channel Terminal functional descriptor */
    UINT8    bEntityId;             /* Constant uniquely identifying the Terminal */
    UINT8    iName;                 /* Index of string descriptor, describing
                                     * the name of the Network Channel Terminal.\
                                     */
    UINT8    bChannelIndex;         /* The channel index of the associated network
                                     * channel according to indexing rules
                                     */
    UINT8    bPhysicalInterface;    /* Type of physical interface */
    } __attribute__ ((packed)) USB_CDC_NETWORK_CHANNEL_TERMINAL_DESCR;

/*
 * 5.2.3.16 Ethernet Networking Functional Descriptor
 *
 * The Ethernet Networking functional descriptor describes
 * the operational modes supported by the Communication Class
 * interface, as defined in Section 3.8.2, with the SubClass
 * code of Ethernet Networking Control. It can only occur within
 * the class-specific portion of an Interface descriptor.
 */

typedef struct usb_cdc_ether_descr
    {
    UINT8    bLength;               /* Size of this descriptor in bytes */
    UINT8    bDescriptorType;       /* CS_INTERFACE descriptor type */
    UINT8    bDescriptorSubType;    /* Ethernet Networking functional descriptor */
    UINT8    iMACAddress;           /* Index of string descriptor. The string
                                     * descriptor holds the 48bit Ethernet MAC
                                     * address.
                                     */
    UINT32   bmEthernetStatistics;  /* Indicates which Ethernet statistics functions
                                     * the device collects. If a bit is set to 0,
                                     * the host network driver is expected to keep
                                     * count for the corresponding statistic (if able).
                                     */
    UINT16   wMaxSegmentSize;       /* The maximum segment size that the Ethernet
                                     * device is capable of supporting. This is
                                     * typically 1514 bytes, but could be extended
                                     *(e.g., 802.1d VLAN)
                                     */
    UINT16   wNumberMCFilters;      /* Contains the number of multicast filters that
                                     * can be configured by the host.
                                     */
    UINT8    bNumberPowerFilters;   /* Contains the number of pattern filters that are
                                     * available for causing wake-up of the host.
                                     */
    } __attribute__ ((packed)) USB_CDC_ETHER_DESCR;

/*
 * Class-Specific Notifications
 *
 * Table 68: Class-Specific Notification Codes
 */

#define USB_CDC_NOTIFY_NETWORK_CONNECTION            0x00
#define USB_CDC_NOTIFY_RESPONSE_AVAILABLE            0x01
#define USB_CDC_NOTIFY_AUX_JACK_HOOK_STATE           0x08
#define USB_CDC_NOTIFY_RING_DETECT                   0x09
#define USB_CDC_NOTIFY_SERIAL_STATE                  0x20
#define USB_CDC_NOTIFY_CALL_STATE_CHANGE             0x28
#define USB_CDC_NOTIFY_LINE_STATE_CHANGE             0x29
#define USB_CDC_NOTIFY_CONNECTION_SPEED_CHANGE       0x2A

typedef struct usb_cdc_notification
    {
    UINT8    bmRequestType;
    UINT8    bNotification;
    UINT16   wValue;
    UINT16   wIndex;
    UINT16   wLength;
    } __attribute__ ((packed)) USB_CDC_NOTIFICATION;

/*
 * USB CDC Class-Specific Control Requests
 *
 * Table 46: Class-Specific Request Codes
 */

#define USB_CDC_SEND_ENCAPSULATED_COMMAND           0x00
#define USB_CDC_GET_ENCAPSULATED_RESPONSE           0x01
#define USB_CDC_SET_COMM_FEATURE                    0x02
#define USB_CDC_GET_COMM_FEATURE                    0x03
#define USB_CDC_CLEAR_COMM_FEATURE                  0x04
/* 05h-0Fh reserved */
#define USB_CDC_SET_AUX_LINE_STATE                  0x10
#define USB_CDC_SET_HOOK_STATE                      0x11
#define USB_CDC_PULSE_SETUP                         0x12
#define USB_CDC_SEND_PULSE                          0x13
#define USB_CDC_SET_PULSE_TIME                      0x14
#define USB_CDC_RING_AUX_JACK                       0x15
/* 16h-1Fh reserved */
#define USB_CDC_REQ_SET_LINE_CODING                 0x20
#define USB_CDC_REQ_GET_LINE_CODING                 0x21
#define USB_CDC_REQ_SET_CONTROL_LINE_STATE          0x22
#define USB_CDC_REQ_SEND_BREAK                      0x23
/* 24h-2Fh reserved */
#define USB_CDC_SET_RINGER_PARMS                    0x30
#define USB_CDC_GET_RINGER_PARMS                    0x31
#define USB_CDC_SET_OPERATION_PARMS                 0x32
#define USB_CDC_GET_OPERATION_PARMS                 0x33
#define USB_CDC_SET_LINE_PARMS                      0x34
#define USB_CDC_GET_LINE_PARMS                      0x35
#define USB_CDC_DIAL_DIGITS                         0x36
#define USB_CDC_SET_UNIT_PARAMETER                  0x37
#define USB_CDC_GET_UNIT_PARAMETER                  0x38
#define USB_CDC_CLEAR_UNIT_PARAMETER                0x39
#define USB_CDC_GET_PROFILE                         0x3A
/* 3Bh-3Fh reserved */
#define USB_CDC_SET_ETHERNET_MULTICAST_FILTERS      0x40
#define USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER      0x41
#define USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER      0x42
#define USB_CDC_SET_ETHERNET_PACKET_FILTER          0x43
#define USB_CDC_GET_ETHERNET_STATISTIC              0x44
/* 45h-4Fh reserved */
#define USB_CDC_SET_ATM_DATA_FORMAT                 0x50
#define USB_CDC_GET_ATM_DEVICE_STATISTICS           0x51
#define USB_CDC_SET_ATM_DEFAULT_VC                  0x52
#define USB_CDC_GET_ATM_VC_STATISTICS               0x53
/* 54h-5Fh reserved */
/* 60h-7Fh MDLM Semantic-Model specific Requests */

/* Table 50: Line Coding Structure */

typedef struct usb_cdc_line_coding
    {
    UINT32   dwDTERate;         /* Data terminal rate, in bits per second */
    UINT8    bCharFormat;       /* Stop bits */
    UINT8    bParityType;       /* Parity */
    UINT8    bDataBits;         /* Data bits */
    } __attribute__ ((packed)) USB_CDC_LINE_CODING;

/* USB_CDC_LINE_CODING:: bCharFormat bitmap defintions - START */

#define USB_CDC_1_STOP_BITS                      0

#define USB_CDC_1_5_STOP_BITS                    1

#define USB_CDC_2_STOP_BITS                      2

/* USB_CDC_LINE_CODING:: bCharFormat bitmap defintions - END */

/* USB_CDC_LINE_CODING:: bParityType bitmap defintions - START */

#define USB_CDC_NO_PARITY                        0
#define USB_CDC_ODD_PARITY                       1
#define USB_CDC_EVEN_PARITY                      2
#define USB_CDC_MARK_PARITY                      3
#define USB_CDC_SPACE_PARITY                     4

/* USB_CDC_LINE_CODING:: bParityType bitmap defintions - END */

/* 6.2.30 SetEthernetPacketFilter */

/* Table 62: Ethernet Packet Filter Bitmap */

#define    USB_CDC_PACKET_TYPE_PROMISCUOUS          (1 << 0)
#define    USB_CDC_PACKET_TYPE_ALL_MULTICAST        (1 << 1) /* no filter */
#define    USB_CDC_PACKET_TYPE_DIRECTED             (1 << 2)
#define    USB_CDC_PACKET_TYPE_BROADCAST            (1 << 3)
#define    USB_CDC_PACKET_TYPE_MULTICAST            (1 << 4) /* filtered */

#ifdef    __cplusplus
}
#endif

#endif    /* __INCusbCdch */

