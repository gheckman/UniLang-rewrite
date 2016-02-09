/* vxbOmap35xxI2C.h - I2C driver header file */

/*
 * Copyright (c) 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
01e,07nov11,rec  WIND00316491 - fix I2C_STAT bits for multi-byte messages
01d,07mar11,bsk  fix compiler warnings
01c,02dec10,bsk  Added comments to explain I2C registers
01b,01nov10,dbr  add i2c device power management defines
01a,03sep10,dbr  created
*/

#ifndef __INComap35xxI2ch
#define __INComap35xxI2ch

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* OMAP I2C Clock on/off bits for three I2C devices */

#define I2C1_FCLK_EN       (1<<15)
#define I2C1_ICLK_EN       (1<<15)
#define I2C2_FCLK_EN       (1<<16)
#define I2C2_ICLK_EN       (1<<16)
#define I2C3_FCLK_EN       (1<<17)
#define I2C3_ICLK_EN       (1<<17)

/* enable mask for all three devices */

#define I2C_CLK_ENABLE     0x38000

/* register definitions (for I2Ci, i = 0, 1, 2) */

#define I2C_IE             0x04  /* interrupt enable bits  */
#define I2C_STAT           0x08  /* status information including interrupt */
#define I2C_WE             0x0C  /* wakeup enable bits */
#define I2C_SYSS           0x10  /* status information, excluding interrupt  */
#define I2C_BUF            0x14  /* receive DMA channel disabled */
#define I2C_CNT            0x18  /* numbers of bytes in I2C data payload */
#define I2C_DATA           0x1C  /* end point/entry point for read/write */
#define I2C_SYSC           0x20  /* parameters of L4-Core interface */
#define I2C_CON            0x24  /* controls functional features */
#define I2C_OA0            0x28  /* module address 7 or 10-bit (I2C) 8-bit (SCCB)  */
#define I2C_SA             0x2C  /* slave address 7 or 10-bit (I2C) 7 bit (SCCB)  */
#define I2C_PSC            0x30  /* internal clocking  */
#define I2C_SCLL           0x34  /* SCL low time value when master. */
#define I2C_SCLH           0x38  /* SCL high time value when master */
#define I2C_SYSTEST        0x3C  /* control  system-level test mode */
#define I2C_BUFSTAT        0x40  /* FIFO status information. */
#define I2C_OA1            0x44  /* I2C 7-bit or 10-bit address */
#define I2C_OA2            0x48  /* I2C 7-bit or 10-bit address */
#define I2C_OA3            0x4C  /* I2C 7-bit or 10-bit address */
#define I2C_ACTOA          0x50  /* accessed slave Own Address indicators */
#define I2C_SBLOCK         0x54  /* slave mode i2c bus lock features */

#define I2C_STAT_AL        (0x1 << 0)  /* arbitration lost */
#define I2C_STAT_NACK      (0x1 << 1 ) /* no-acknowledgement  */
#define I2C_STAT_ARDY      (0x1 << 2)  /* Register Access Ready */
#define I2C_STAT_RRDY      (0x1 << 3)  /* Receive Data Ready */
#define I2C_STAT_XRDY      (0x1 << 4)  /* Transmit Data Ready */
#define I2C_STAT_AERR      (0x1 << 7)  /* Access Error */
#define I2C_STAT_BB        (0x1 << 12) /* Bus busy status  */
#define I2C_STAT_XDR       (0x1 << 14) /* Transmit Draining IRQ status */

#define I2C_STAT_MASK      (I2C_STAT_AL | I2C_STAT_RRDY | I2C_STAT_XRDY | I2C_STAT_NACK)

#define I2C_CON_STB        (0x1 << 11) /* Start byte mode (master mode only) */
#define I2C_CON_MST        (0x1 << 10) /* Master/slave mode selection */
#define I2C_CON_TRX        (0x1 << 9 ) /* Transmitter/Receiver mode (master mode only) */
#define I2C_CON_XSA        (0x1 << 8 ) /* Expand slave address enable bit */
#define I2C_CON_STP        (0x1 << 1 ) /* Stop condition (master mode only) */
#define I2C_CON_STT        (0x1 << 0 ) /* Start condition (master mode only) */
#define I2C_CON_EN         (0x1 << 15) /* Module enable bit */

/* OMAP35XX I2C4 register definitions */

#define PRM_VC_I2C_CFG     0x38	/* I2C4 config register */
#define I2C4_HSEN          0x8	/* Enables I2C bus High Speed mode */
#define I2C4_SREN          0x10	/* Enables repeated start operation mode */

#define PRM_VC_BYPASS_VAL  0x3c          /* I2C4 operating register */
#define I2C4_VALID         (1 << 24)
#define I2C4_DATA_BIT      16
#define I2C4_REG_BIT       8

#define I2C_TIMEOUT        10000000      /* i2c read & write timeout value */

/* address of pad configuration registers for I2C devices */
	
#define OMAP35XX_PADCONF_HSUSB0_DATA7            0x480021B8
#define OMAP35XX_PADCONF_I2C1_SDA                0x480021BC
#define OMAP35XX_PADCONF_I2C2_SDA                0x480021C0
#define OMAP35XX_PADCONF_I2C3_SDA                0x480021C4

/* address of 16 bit wide access of SCL/SDA pad configuration registers  */
	
#define OMAP35XX_PADCONF_I2C1_SDA_ADR	OMAP35XX_PADCONF_I2C1_SDA
#define OMAP35XX_PADCONF_I2C1_SCL_ADR	(OMAP35XX_PADCONF_HSUSB0_DATA7+2)
#define OMAP35XX_PADCONF_I2C2_SDA_ADR	OMAP35XX_PADCONF_I2C2_SDA
#define OMAP35XX_PADCONF_I2C2_SCL_ADR	(OMAP35XX_PADCONF_I2C1_SDA+2)	
#define OMAP35XX_PADCONF_I2C3_SDA_ADR	OMAP35XX_PADCONF_I2C3_SDA
#define OMAP35XX_PADCONF_I2C3_SCL_ADR	(OMAP35XX_PADCONF_I2C2_SDA+2)		

/* default pad configuration register values */

#define OMAP35XX_I2C_SDA_CFG		0x0110
#define OMAP35XX_I2C_SCL_CFG		0x0110

/* define I2C devices for OMAP 35xx */

#define I2C_MAX_DEVICES    		3
#define I2C_DEVICE_1      		0
#define I2C_DEVICE_2			1
#define I2C_DEVICE_3			2


#define FUNCTIONAL_CLOCK_FREQ 96000000    /* system functional clock */ 
#define INTERFACE_CLOCK_FREQ  12000000    /* internal sampling clock */ 
#define DEFAULT_BITS_PER_SEC  100         /* default speed is 100k bps speed */

	
/* define  power domains of I2C device */

enum omapI2cPowerDomain
    {
    OMAP_I2C_PWR_WKUP,
    OMAP_I2C_PWR_CORE
    };

/* define power states for a I2C devices */

enum omapI2cDevPowerState
        {
        OMAP_I2C_DEV_POWER_ON,
        OMAP_I2C_DEV_POWER_OFF
        };

/* struct for storage of pad config registers addresses */

struct I2cPadConfigRegs
    {
    UINT32 padConfigSda[I2C_MAX_DEVICES];
    UINT32 padConfigScl[I2C_MAX_DEVICES];
    };

/* struct for storage of masks to enable/disable device power */

struct I2cDevPwrMasks
    {
    UINT32 devPwrMaskIclk[I2C_MAX_DEVICES];
    UINT32 devPwrMaskFclk[I2C_MAX_DEVICES];
    };




/* prototypes */

#ifndef _ASMLANGUAGE
IMPORT STATUS omap35xxI2cAllocateDev (UINT32 dev);
IMPORT STATUS omap35xxI2cDeallocateDev (UINT32 dev);
IMPORT STATUS omap35xxI2cPadConfig (UINT32 dev, UINT16 sdaCfg, UINT16 sclCfg);
IMPORT STATUS omap35xxI2cWrite (UINT32 i2cDevNum, UINT8  devAddr, 
						    INT8 * buf, size_t len);
IMPORT STATUS omap35xxI2cRead (UINT32 i2cDevNum, UINT8  devAddr, 
						 UINT8  regAddr,
						 INT8 * buf, size_t len);
#endif /* _ASMLANGUAGE */

#ifdef OMAP35XX_I2C_DEBUG
#define OMAP35XX_I2C_LOG(fmt,a,b,c,d,e,f)  \
	if (_func_logMsg != NULL) \
		(* _func_logMsg)(fmt,a,b,c,d,e,f)
#else  /* OMAP35XX_I2C_DEBUG */
#define OMAP35XX_I2C_LOG(fmt,a,b,c,d,e,f)   
#endif

#ifdef __cplusplus
}
#endif

#endif

