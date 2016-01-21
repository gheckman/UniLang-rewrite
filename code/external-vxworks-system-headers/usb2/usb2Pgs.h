/* usb2Pgs.h - Generation 2 USB pegasus driver */

/*
 * Copyright (c) 2008 - 2010 Wind River Systems, Inc.
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
01b,22arp09,s_z  Remove the gun compiler warning and code cleaning
01a,12nov08,s_z  written

*/
#ifndef __INCusb2Pgsh
#define __INCusb2Pgsh

/* includes */
#include <vxWorks.h>
#include <iosLib.h>
#include <usb2/usb2Helper.h>
#include <usb2/usb2End.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* USB pegasus class specific requests */

#define USB2_PGS_GET_REGISTER_VENDOR_RQ         0xF0 /* get register */
#define USB2_PGS_SET_REGISTER_VENDOR_RQ         0xF1 /* set register */

#define USB2_PGS_LINK_STATUS_OFFSET             0x05
#define USB2_PGS_LINK_STATUS_MASK               0x01
#define USB2_PGS_HEADER                         0x02

/* Pegasus Register Definition */

#define USB2_PGS_RGS_ETHERNET_CTRL0      0x00   /* Ethernet Control 0 */
#define USB2_PGS_RGS_ETHERNET_CTRL1      0x01   /* Ethernet Control 1 */
#define USB2_PGS_RGS_ETHERNET_CTRL2      0x02   /* Ethernet Control 2 */

#define USB2_PGS_MULTICAST_ADDR          0x08   /* Multicast Address 0 */

                                         
#define USB2_PGS_ETHERNET_ID             0x10   /* Ethernet ID 0 */

#define USB2_PGS_RGS_RXFIFO_CTRL         0x1D   /* RX FIFO Control */
#define USB2_PEGASUS_RGS_BIST            0x1E   /* BIST */

/* EEPROM Interface Registers */
#define USB2_PGS_EEPROM_OFFSET           0x20   /* EEPROM Offset Reg */
#define USB2_PGS_EEPROM_DATA             0x21   /* EEPROM Data Low Reg*/
#define USB2_PGS_EEPROM_CONTROL          0x23   /* EEPROM Access Control Reg*/

/* EEPROM Control Reg Bitmap definition */
#define USB2_PGS_EEPROM_CONTROL_DONE    (0x1 << 2)  /* EEPROM Done*/
#define USB2_PGS_EEPROM_CONTROL_READ    (0x1 << 1)  /* EEPROM write */
#define USB2_PGS_EEPROM_CONTROL_WRITE   (0x1 << 0)  /* EEPROM read */

/* MII Interface Transceiver Registers */
#define USB2_PGS_MII_RGS_CONTROL         0x0   /* Control Reg */
#define USB2_PGS_MII_RGS_STATUS          0x1   /* Status Reg */
#define USB2_PGS_MII_RGS_PHY_ID1         0x2   /* PHY Identifier 1 Reg */
#define USB2_PGS_MII_RGS_PHY_ID2         0x3   /* PHY Identifier 2 Reg */
#define USB2_PGS_MII_RGS_NEGO_AD         0x4   /* Auto-Negotiation Advertisement */
#define USB2_PGS_MII_RGS_NEGO_ABILITY    0x5   /* Auto-Negotiation Link Partnet Ability */
#define USB2_PGS_MII_RGS_NEGO_EXP        0x6   /* Auto-Negotiation Expansion */

/* PHY Access Register */
#define USB2_PGS_RGS_PHY_ADDR            0x25   /* PHY Address */
#define USB2_PGS_RGS_PHY_DATA            0x26   /* PHY Data Low */
#define USB2_PGS_RGS_PHY_CTRL            0x28   /* PHY Access Control */
/* PHY Access Control Register Bitmap defineition */

#define USB2_PGS_PHY_CTRL_ADDR_MASK      0x1F
#define USB2_PGS_PHY_CTRL_WRITE          0x20
#define USB2_PGS_PHY_CTRL_READ           0x40
#define USB2_PGS_PHY_CTRL_DONE           0x80

#define USB2_PGS_RGS_WAKEUP_CTRL         0x78   /* Wakeup Control */
                                         
#define USB2_PGS_RGS_INTERNAL_PHY_CTRL   0x7B   /* Internal PHY Control */

#define USB2_PGS_RGS_GPIO_10_CTRL        0x7E   /* GPIO[1:0] Control */
#define USB2_PGS_RGS_GPIO_32_CTRL        0x7F   /* GPIO[3:2] Control */


/* Pegasus Control Registers definition */

#define PEGASUS_CTL0_INCLUDE_RXCRC       0x01
#define PEGASUS_CTL0_ALLMULTI            0x02
#define PEGASUS_CTL0_STOP_BACKOFF        0x04
#define PEGASUS_CTL0_RXSTAT_APPEND       0x08
#define PEGASUS_CTL0_WAKEON_ENB          0x10
#define PEGASUS_CTL0_RXPAUSE_ENB         0x20
#define PEGASUS_CTL0_RX_ENB              0x40
#define PEGASUS_CTL0_TX_ENB              0x80

                                         
#define PEGASUS_CTL1_HOMELAN             0x04
#define PEGASUS_CTL1_RESETMAC            0x08
#define PEGASUS_CTL1_SPEEDSEL            0x10    /* 0 = 10mbps, 1 = 100mbps */
#define PEGASUS_CTL1_DUPLEX              0x20    /* 0 = half, 1 = full */
#define PEGASUS_CTL1_DELAYHOME           0x40
                                         
#define PEGASUS_CTL2_EP3_CLR             0x01    /* reading EP3 clrs status regs */
#define PEGASUS_CTL2_RX_BADFRAMES        0x02
#define PEGASUS_CTL2_RX_PROMISC          0x04
#define PEGASUS_CTL2_LOOPBACK            0x08
#define PEGASUS_CTL2_EEPROMWR_ENB        0x10
#define PEGASUS_CTL2_EEPROM_LOAD         0x20

/*
 * Define Vendor ID and Product ID which supported 
 * by pegasus driver,add such devices into pgs list
 */
 
/* ADMtek */

#define ADMTEK_ADM8515_PRODUCT_ID        0x8515
#define ADMTEK_ADM8513_PRODUCT_ID        0x8513
#define ADMTEK_ADM8511_PRODUCT_ID        0x8511
                                                
/* Sohoware */          

#define SOHOWARE_NUB110_PRODUCT_ID       0x9110
                                                
/* D-Link */                                    
                                                
#define DLINK_DSB650_PRODUCT_ID          0xABC1
                                                
#define DLINK_DSB650TX1_PRODUCT_ID       0x4001
#define DLINK_DSB650TX2_PRODUCT_ID       0x4002
#define DLINK_DSB650TX12_PRODUCT_ID      0x4102
#define DLINK_DSB650TXB_PRODUCT_ID       0x400B
                                                
/* Belkin */   

#define BELKIN_F5D5050_PRODUCT_ID        0x0121
                                                
/* Netgear */  

#define NETGEAR_FA101_PRODUCT_ID         0x1020
 
/* IO Data */

#define IODATA_ETTXS_PRODUCT_ID          0x0913

/* 3COM */

#define _3COM_3C460B_PRODUCT_ID          0x4601

/* SIEMENS */

#define SIEMENS_SPEEDSTREAM_PRODUCT_ID   0x1001

/* 
 * Define the max number of the pegasus devcie table, can be expanded 
 * according the device 
 */
#define USB2_PGS_MAX_DEVICE_NUMBER       32

/* Forward declarations */

extern void usb2PgsDeInit
    (
    void
    );
extern STATUS usb2PgsInit
    (
    char * pName 
    );

#ifdef __cplusplus
}
#endif
#endif  /* __INCusb2Pgsh */

