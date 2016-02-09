/* usbSpeakerLib.h - Definitions for USB speaker class driver */

/*
 * Copyright (c) 2000-2001, 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,13jan10,ghs  vxWorks 6.9 LP64 adapting
01g,02oct06,j_l  Add HID functions
01f,08sep06,j_l  Modify for USB headset driver
01e,18sep01,wef  merge from wrs.tor2_0.usb1_1-f for veloce
01d,07may01,wef  changed module number to be (module num << 8) | M_usbHostLib
01c,02may01,wef  changed module number to be M_<module> + M_usbHostLib
01b,05dec00,wef  moved Module number defs to vwModNum.h - add this
                 to #includes
01a,12jan00,rcb  First.
*/

#ifndef __INCusbSpeakerLibh
#define __INCusbSpeakerLibh


/* includes */

#include <seqIo.h>
#include <usb/usbPlatform.h>
#include <vwModNum.h>           /* USB Module Number Def's */
#include <usb/usb.h>

#ifdef  __cplusplus
extern "C" {
#endif


/* defines */

/* usbSpeakerLib error values */

/*
 * USB errnos are defined as being part of the USB host Module, as are all
 * vxWorks module numbers, but the USB Module number is further divided into
 * sub-modules.  Each sub-module has upto 255 values for its own error codes
 */

#define USB_SPEAKER_SUB_MODULE  9

#define M_usbSpeakerLib ( (USB_SPEAKER_SUB_MODULE << 8) | M_usbHostLib )

#define usbSpkrErr(x)   (M_usbSpeakerLib | (x))

#define S_usbSpeakerLib_NOT_INITIALIZED     usbSpkrErr (1)
#define S_usbSpeakerLib_BAD_PARAM           usbSpkrErr (2)
#define S_usbSpeakerLib_OUT_OF_MEMORY       usbSpkrErr (3)
#define S_usbSpeakerLib_OUT_OF_RESOURCES    usbSpkrErr (4)
#define S_usbSpeakerLib_GENERAL_FAULT       usbSpkrErr (5)
#define S_usbSpeakerLib_NOT_IMPLEMENTED     usbSpkrErr (6)
#define S_usbSpeakerLib_USBD_FAULT          usbSpkrErr (7)
#define S_usbSpeakerLib_NOT_REGISTERED      usbSpkrErr (8)
#define S_usbSpeakerLib_NOT_LOCKED          usbSpkrErr (9)

/* USB_SPKR_xxxx define "attach codes" used by USB_SPKR_ATTACH_CALLBACK. */

#define USB_SPKR_ATTACH 0       /* new speaker attached */
#define USB_SPKR_REMOVE 1       /* speaker has been removed */
                                /* SEQ_DEV no longer valid */

/* IOCTL codes unique to usbSpeakerLib. */

#define USB_SPKR_IOCTL_GET_FORMAT_COUNT         0x8000
#define USB_SPKR_IOCTL_GET_FORMAT_LIST          0x8001
#define USB_SPKR_IOCTL_GET_FORMAT_COUNT_MIC     0x8002
#define USB_SPKR_IOCTL_GET_FORMAT_LIST_MIC      0x8003

#define USB_SPKR_IOCTL_GET_CHANNEL_COUNT        0x8010
#define USB_SPKR_IOCTL_GET_CHANNEL_CONFIG       0x8011
#define USB_SPKR_IOCTL_GET_CHANNEL_CAPS         0x8012
#define USB_SPKR_IOCTL_GET_CHANNEL_COUNT_MIC    0x8013
#define USB_SPKR_IOCTL_GET_CHANNEL_CONFIG_MIC   0x8014
#define USB_SPKR_IOCTL_GET_CHANNEL_CAPS_MIC     0x8015

#define USB_SPKR_IOCTL_SET_AUDIO_FORMAT         0x8020
#define USB_SPKR_IOCTL_OPEN_AUDIO_STREAM        0x8021
#define USB_SPKR_IOCTL_CLOSE_AUDIO_STREAM       0x8022
#define USB_SPKR_IOCTL_AUDIO_STREAM_STATUS      0x8023
#define USB_SPKR_IOCTL_SET_AUDIO_FORMAT_MIC     0x8024
#define USB_SPKR_IOCTL_AUDIO_STREAM_STATUS_MIC  0x8025

#define USB_SPKR_IOCTL_SET_MUTE                 0x8030
#define USB_SPKR_IOCTL_SET_VOLUME               0x8031
#define USB_SPKR_IOCTL_SET_BASS                 0x8032
#define USB_SPKR_IOCTL_SET_MID                  0x8033
#define USB_SPKR_IOCTL_SET_TREBLE               0x8034
#define USB_SPKR_IOCTL_SET_MUTE_MIC             0x8035
#define USB_SPKR_IOCTL_SET_VOLUME_MIC           0x8036
#define USB_SPKR_IOCTL_SET_BASS_MIC             0x8037
#define USB_SPKR_IOCTL_SET_MID_MIC              0x8038
#define USB_SPKR_IOCTL_SET_TREBLE_MIC           0x8039

#define USB_SPKR_IOCTL_SET_HALF_BUF_IN_MSEC     0x8040
#define USB_SPKR_IOCTL_SET_HALF_BUF_IN_MSEC_MIC 0x8041
#define USB_SPKR_IOCTL_SET_BUF_FULL_BLOCK       0x8042

#define USB_SPKR_IOCTL_GET_DEV_INFO             0x8050
#define USB_SPKR_IOCTL_SET_HID_CALLBACK         0x8051
#define USB_SPKR_IOCTL_GET_HID_REPORT           0x8052
#define USB_SPKR_IOCTL_SET_HID_REPORT           0x8053
#define USB_SPKR_IOCTL_READ_HID_REPORT          0x8054
#define USB_SPKR_IOCTL_WRITE_HID_REPORT         0x8055

/* Status bit mask returned by USB_SPKR_IOCTL_AUDIO_STREAM_STATUS. */

#define USB_SPKR_STATUS_OPEN                    0x0001
#define USB_SPKR_STATUS_DATA_IN_BFR             0x0002

#define SPKR_NAME_LEN_MAX           100
#define USB_SPKR_NAME               "/usbSp/"

#ifndef SPKR_MAX_DEVS
#define SPKR_MAX_DEVS 1
#endif

/* typedefs */

typedef enum
    {
    USB_SPKR_DEVICE_SPKR,
    USB_SPKR_DEVICE_MIC
    } USB_SPKR_DEVICE_TYPE;

/* USB_SPKR_ATTACH_CALLBACK defines a callback routine which will be
 * invoked by usbSpeakerLib.c when the attachment or removal of a speaker
 * is detected.  When the callback is invoked with an attach code of
 * USB_SPKR_ATTACH, the pSeqDev points to a newly created SEQ_DEV.  When
 * the attach code is USB_SPKR_REMOVE, the pSeqDev points to a pSeqDev
 * for a speaker which is no longer attached.
 */

typedef VOID (*USB_SPKR_ATTACH_CALLBACK)
    (
    pVOID arg,                  /* caller-defined argument */
    SEQ_DEV *pSeqDev,           /* pointer to affected SEQ_DEV */
    UINT16 attachCode           /* defined as USB_SPKR_xxxx */
    );

typedef VOID (*USB_SPKR_FUNC_DYN_ATTACH_CALLBACK)
    (
    UINT16 attachAction
    );

typedef VOID (*USB_SPKR_FUNC_DYN_DETACH_CALLBACK)
    (
    UINT16 attachAction
    );

typedef VOID (*USB_SPKR_HID_CALLBACK)
    (
    int fd, /* user argument */
    UINT16 length, /* length of report */
    pUINT8 pReport /* HID report */
    );

/* USB_SPKR_CTL_CAPS defines the capabilities of a given speaker control */

typedef struct usb_spkr_ctl_caps
    {
    BOOL supported;         /* true if capability supported */
    UINT16 res;             /* resolution of capability */
    INT16 min;              /* minimum setting */
    INT16 max;              /* maximum setting */
    INT16 cur;              /* current setting */
    } USB_SPKR_CTL_CAPS, *pUSB_SPKR_CTL_CAPS;

/* USB_SPKR_CHANNEL_CAPS defines the audio capabilities for a given channel. */

typedef struct usb_spkr_channel_caps
    {
    UINT16 capsLen;             /* length of this structure */

    USB_SPKR_CTL_CAPS mute;     /* mute */
    USB_SPKR_CTL_CAPS volume;   /* volume */
    USB_SPKR_CTL_CAPS bass;     /* bass */
    USB_SPKR_CTL_CAPS mid;      /* mid-range */
    USB_SPKR_CTL_CAPS treble;   /* treble */

    } USB_SPKR_CHANNEL_CAPS, *pUSB_SPKR_CHANNEL_CAPS;

/* USB_SPKR_AUDIO_FORMAT defines an audio format supported by the speaker. */

typedef struct usb_spkr_audio_format
    {
    UINT8 interface;            /* interface number */
    UINT8 altSetting;           /* alternate setting for this fmt */
    UINT8 delay;                /* internal delay on this endpoint */
    UINT8 endpoint;             /* endpoint to receive data */
    UINT16 maxPacketSize;       /* max packet size for endpoint */
    UINT8 attributes;           /* bmAttributes */
    UINT16 formatTag;           /* format tag */
    UINT8 formatType;           /* type I, II, or III. */

                                /* fields for Type I & III formats */
    UINT8 channels;             /* number of channels */
    UINT8 subFrameSize;         /* size of audio sub frame */
    UINT8 bitRes;               /* bit resolution per sample */
    UINT32 sampleFrequency;     /* frequency specified by caller */

                                /* Fields for Type II formats */
    UINT16 maxBitRate;          /* max bps supported by interface */
    UINT16 samplesPerFrame;     /* nbr of audio samples per frame */

    UINT8   freqType;           /* how sampling freq. can be programmed */
    UINT32  lowerFreq;          /* lower bound */
    UINT32  upperFreq;          /* upper bound */
    UINT32 *freq;               /* discrete sampling frequencies */

    } USB_SPKR_AUDIO_FORMAT, *pUSB_SPKR_AUDIO_FORMAT;

/* USB_SPKR_DEV_INFO_TYPE holds manufacterer and model info  */
typedef struct usb_spkr_dev_info_type
    {
    UINT16  vendorId;
    UINT16  productId;
    char    manufacturerName[(USB_MAX_DESCR_LEN/2)+1];
    char    productName[(USB_MAX_DESCR_LEN/2)+1];
    } USB_SPKR_DEV_INFO_TYPE, *pUSB_SPKR_DEV_INFO_TYPE;

typedef struct usb_spkr_hid_callback_type
    {
    int                   arg;
    USB_SPKR_HID_CALLBACK function;
    } USB_SPKR_HID_CALLBACK_TYPE, *pUSB_SPKR_HID_CALLBACK_TYPE;

typedef struct usb_spkr_hid_get_report_type
    {
    UINT16 reportTypeAndId; /* report type and ID */
    UINT16 length;          /* report length */
    pUINT8 pReport;         /* returned report */
    } USB_SPKR_HID_GET_REPORT_TYPE, *pUSB_SPKR_HID_GET_REPORT_TYPE;

typedef struct usb_spkr_hid_set_report_type
    {
    UINT16 reportTypeAndId; /* report type and ID */
    UINT16 length;          /* report length */
    pUINT8 pReport;         /* report sent to headset */
    } USB_SPKR_HID_SET_REPORT_TYPE, *pUSB_SPKR_HID_SET_REPORT_TYPE;

typedef struct usb_spkr_hid_read_report_type
    {
    UINT16 length;          /* report length */
    pUINT8 pReport;         /* returned report */
    } USB_SPKR_HID_READ_REPORT_TYPE, *pUSB_SPKR_HID_READ_REPORT_TYPE;

typedef struct usb_spkr_hid_write_report_type
    {
    UINT16 length;          /* report length */
    pUINT8 pReport;         /* returned report */
    } USB_SPKR_HID_WRITE_REPORT_TYPE, *pUSB_SPKR_HID_WRITE_REPORT_TYPE;

/* function prototypes */

STATUS usbSpeakerDevInit (void);
STATUS usbSpeakerDevShutdown (void);

STATUS usbSpeakerDynamicAttachRegister
    (
    USB_SPKR_ATTACH_CALLBACK callback,  /* new callback to be registered */
    pVOID arg                           /* user-defined arg to callback */
    );

STATUS usbSpeakerDynamicAttachUnRegister
    (
    USB_SPKR_ATTACH_CALLBACK callback,  /* callback to be unregistered */
    pVOID arg                           /* user-defined arg to callback */
    );

STATUS usbSpeakerSeqDevLock
    (
    SEQ_DEV *pSeqDev                    /* SEQ_DEV to be marked as in use */
    );

STATUS usbSpeakerSeqDevUnlock
    (
    SEQ_DEV *pSeqDev                    /* SEQ_DEV to be marked as unused */
    );

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbSpeakerLibh */

/* End of file. */

