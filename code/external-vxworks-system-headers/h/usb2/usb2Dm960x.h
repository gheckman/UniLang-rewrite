/* usb2Dm960x.h - Generation 2 USB Dm960x driver */

/*
 * Copyright (c) 2009 - 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01b,30mar10,w_x  Back port GEN2 class drivers for old VxWorks (WIND00192167)
01a,02jul09,s_z  written

*/
#ifndef __INCusb2Dm960xh
#define __INCusb2Dm960xh

/* includes */

#include <vxWorks.h>
#include <iosLib.h>
#include <usb2/usb2Helper.h>
#include <usb2/usb2End.h>

#ifdef __cplusplus
extern "C" {
#endif



/* Status checking */

#define USB2_MD960X_LINK_STATUS_MASK         0x40

#define USB2_END_DM960X_HEADER               0x02

/* DM960X Command */

#define USB2_DM960X_READ_REGISTERS           0x00
#define USB2_DM960X_WRITE_REGISTERS          0x01
#define USB2_DM960X_WRITE_SINGLE_REGISTER    0x03

#define USB2_DM960X_READ_MEMORYS             0x02
#define USB2_DM960X_WRITE_MEMMORYS           0x05
#define USB2_DM960X_WRITE_SINGLE_MEMORY      0x07

/* DM960X Registers */

#define USB2_DM960X_NETWORK_CTRL_REG         0x00
#define USB2_DM960X_RX_CTRL                  0x05

#define USB2_DM960X_EEPROM_AND_PHY_CTRL      0x0b
#define USB2_DM960X_EEPROM_AND_PHY_ADDR      0x0c
#define USB2_DM960X_EEPROM_AND_PHY_DATA      0x0d

#define USB2_DM960X_MAC_ADDR                 0x10
#define USB2_DM960X_MCAST_ADDR               0x16

#define USB2_DM960X_MII_BMCR                 0x00
#define USB2_DM960X_MII_BMSR                 0x01
#define USB2_DM960X_MII_ADVERTISE            0x04


#define USB2_DM960X_GPR_CTRL                 0x1e
#define USB2_DM960X_GPR_DATA                 0x1f


#define USB2_DM960X_MAX_MCAST                64
#define USB2_DM960X_MCAST_SIZE               8
#define USB2_DM960X_EEPROM_LEN               256
#define USB2_DM960X_TX_OVERHEAD              2
#define USB2_DM960X_RX_OVERHEAD              7
#define USB2_DM960X_TIMEOUT                  1000


#define USB2_DM960X_MAX_DEVICE_NUMBER       32

/* Forward declarations */

extern void usb2Dm960xDeInit
    (
    void
    );
extern STATUS usb2Dm960xInit
    (
    char * pName
    );

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2Dm960xh */



