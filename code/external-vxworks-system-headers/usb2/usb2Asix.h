/* usb2Asix.h - Generation 2 USB Asix driver */

/*
 * Copyright (c) 2008 - 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,17feb12,s_z  Add the USB_ASIX_STATUS_NOTIFY_CH_ENABLE definition (WIND00333840)
01d,29apr10,pad  Moved extern C statement after include statements.
01c,30mar10,w_x  Back port GEN2 class drivers for old VxWorks (WIND00192167)
01b,22arp09,s_z  Remove the gun compiler warning and code cleaning
01a,12nov08,s_z  written

*/
#ifndef __INCusb2Asixh
#define __INCusb2Asixh

/* includes */

#include <vxWorks.h>
#include <iosLib.h>
#include <usb2/usb2Helper.h>
#include <usb2/usb2End.h>

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

/* 
 * Status checking
 * 
 * The status can be get by 
 * - notify endpoint channel,
 * - or control endpoint channel.
 *
 * By default, this macro (USB_ASIX_STATUS_NOTIFY_CH_ENABLE) is defined to enable
 * the notify endpoint channel to get the link status. Which will reduce the
 * overhead on the control endpoint. 
 * 
 * Meanwhile, the control channel also be support to reduce one more 
 * transafer on another endpoint (one some host controller, transaction channels
 * are limited).
 * 
 * Internal testing shows that, over control channel, it will be slower. Since
 * 3 transactions will be needed to get the status, while notify endpoint channel
 * need one transaction. 
 * 
 * This can be user configurable in the future release.
 */

#define USB_ASIX_STATUS_NOTIFY_CH_ENABLE

#ifdef USB_ASIX_STATUS_NOTIFY_CH_ENABLE
#define USB2_ASIX_LINK_STATUS_OFFSET           0x02 /* The link status offset */
#define USB2_ASIX_LINK_STATUS_MASK             0x03 /* The link status bit mask */
#else
#define USB2_ASIX_LINK_STATUS_OFFSET           0x00 /* The link status offset */
#define USB2_ASIX_LINK_STATUS_MASK             0x04 /* The link status bit mask */
#endif /* USB_ASIX_STATUS_NOTIFY_CH_ENABLE */

#define USB2_END_ASIX_HEADER                   0x00
#define USB2_END_ASIX_AM88772_HEADER           0x04

/* ASIX AX8817X based USB 2.0 Ethernet Devices */

#define USB2_ASIX_VENDOR_CMD_SET_SW_MII         0x06
#define USB2_ASIX_VENDOR_CMD_READ_MII_REG       0x07
#define USB2_ASIX_VENDOR_CMD_WRITE_MII_REG      0x08
#define USB2_ASIX_VENDOR_CMD_SET_HW_MII         0x0a

#define USB2_ASIX_CMD_READ_EEPROM               0x0b
#define USB2_ASIX_CMD_WRITE_EEPROM              0x0c
#define USB2_ASIX_CMD_WRITE_ENABLE              0x0d
#define USB2_ASIX_CMD_WRITE_DISABLE             0x0e

#define USB2_ASIX_VENDOR_CMD_READ_RX_CTL        0x0f

#define USB2_ASIX_VENDOR_CMD_WRITE_RX_CTL       0x10
#define USB2_ASIX_CMD_READ_IPG012               0x11

#define USB2_ASIX_VENDOR_CMD_WRITE_IPG0         0x12
#define USB2_ASIX_VENDOR_CMD_WRITE_IPG1         0x13
#define USB2_ASIX_VENDOR_CMD_WRITE_IPG2         0x14

#define USB2_ASIX_VENDOR_CMD_WRITE_MULTI_FILTER 0x16

#define USB2_ASIX88172_CMD_READ_NODE_ID         0x17
#define USB2_ASIX_VENDOR_CMD_READ_NODE_ID       0X13

#define USB2_ASIX_VENDOR_CMD_READ_PHY_ID        0x19

#define USB2_ASIX_VENDOR_CMD_READ_MEDIUM_STATUS 0x1a

#define USB2_ASIX_VENDOR_CMD_WRITE_MEDIUM_MODE  0x1b

#define USB2_ASIX_CMD_READ_MONITOR_MODE         0x1c
#define USB2_ASIX_CMD_WRITE_MONITOR_MODE        0x1d
#define USB2_ASIX_CMD_READ_GPIOS                0x1e

#define USB2_ASIX_VENDOR_CMD_WRITE_GPIOS        0x1f

#define USB2_ASIX_VENDOR_CMD_SW_RESET           0x20
#define USB2_ASIX_CMD_SW_PHY_STATUS             0x21
#define USB2_ASIX_VENDOR_CMD_SW_PHY_SELECT      0x22

/* Bitmap of AX88172 Medium Mode Register */

#define AX88172_MEDIUM_FD                       0x02
#define AX88172_MEDIUM_TX                       0x04
#define AX88172_MEDIUM_FC                       0x10
#define AX88172_MEDIUM_DEFAULT \
                ( AX88172_MEDIUM_FD | AX88172_MEDIUM_TX | AX88172_MEDIUM_FC )


/* Bitmap of MII Basic Mode Control Register (BMCR) */
#define USB2_ASIX_MII_BMCR                      0x00 /* Basic mode control register*/
#define USB2_ASIX_MII_BMSR                      0x01 /* Basic mode Status register*/

#define USB2_ASIX_MII_ADVERTISE                 0x04 /* Advertisement control reg   */

/* Bitmap for Rx CTL register */
#define USB2_ASIX_RX_CTL_PRO                    0x01
#define USB2_ASIX_RX_CTL_AMALL                  0x02
#define USB2_ASIX_RX_CTL_AB                     0x08
#define USB2_ASIX_RX_CTL_AM                     0x10

/* Asix AdapterList which can be supported */
#define USB2_ASIX_MAX_DEVICE_NUMBER             32

/* Forward declarations */

extern void usb2AsixDeInit
    (
    void
    );
extern STATUS usb2AsixInit
    (
    char * pName 
    );

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2Asixh */
