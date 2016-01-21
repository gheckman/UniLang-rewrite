/* usb2Prn.h - Generation 2 USB printer driver */

/*
 * Copyright (c) 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01c,30mar10,w_x  Back port GEN2 class drivers for old VxWorks (WIND00192167)
01b,23apr09,w_x  coding convention changes
01a,05nov08,adh  written
*/

#ifndef __INCusb2Prnh
#define __INCusb2Prnh

/* includes */

#include <vxWorks.h>
#include <iosLib.h>
#include <usb2/usb2Helper.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define USB2_PRN_CLASS                          0x07 /* Printer class (spec)  */
#define USB2_PRN_SUBCLASS                       0x01 /* Printer subclass(spec)*/

/* USB printer protocol codes */

#define USB2_PRN_UNIDIR_PROTOCOL                0x01 /* protocol dir (spec) */
#define USB2_PRN_BIDIR_PROTOCOL                 0x02 /* protocol dir (spec) */
#define USB2_PRN_1284_PROTOCOL                  0x03 /* protocol dir (spec) */

/* IOCTL codes (see module definition) */

#define USB2_PRN_IOCTL_GET_CAPABILITIES_FULL     0x1001
#define USB2_PRN_IOCTL_GET_CAPABILITIES_LENGTH   0x1002
#define USB2_PRN_IOCTL_GET_PORT_STATUS           0x1003
#define USB2_PRN_IOCTL_SET_SOFT_RESET            0x1004
#define USB2_PRN_IOCTL_GET_PROTOCOL              0x1005
#define USB2_PRN_IOCTL_CANCEL_ALL                0x1006
#define USB2_PRN_IOCTL_SET_TIMEOUT               0x1007
#define USB2_PRN_IOCTL_GET_TIMEOUT               0x1008

/* typedefs */

/* Capabiity string for the USB2PRN_IOCTL_GET_CAPABILITIES_FULL ioctl */

typedef struct usb2_prn_capabilities
    {
    UINT16 length;              /* length in word size as per spec */
    unsigned char pBuffer[1];   /* buffer of variable length as per spec */
    } __attribute__((packed)) USB2_PRN_CAPABILITIES;

/* Port status struct for the USB2PRN_IOCTL_GET_PORT_STATUS ioctl */

typedef struct usb2_prn_port_status
    {
    UINT8 portStatus;           /* byte that contains the port status reg */
    } __attribute__((packed)) USB2_PRN_PORT_STATUS;

/* Forward declarations */

extern void usb2PrnDeinit
    (
    void
    );

extern STATUS usb2PrnInit
    (
    char *  pName /* Default base name that will be used, or NULL if no names */
    );

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2Prnh */
