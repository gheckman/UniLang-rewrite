/* vxbOmap35xxGpio.h - GPIO driver header file */

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
01d,14sep11,jmz  WIND00302612 Update omap35xxGpioAllocatePin function
01c,28jan11,jmz  Add definition for GPIO pin 182
01b,28oct10,dbr  updates for power management
01a,06oct10,dbr  created and ported to vxBus
*/

#ifndef __INComap35xxGpioh
#define __INComap35xxGpioh

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
	
/* GPIO modules base addresses */

#define OMAP35XX_GPIO1          0x48310000
#define OMAP35XX_GPIO2          0x49050000
#define OMAP35XX_GPIO3          0x49052000
#define OMAP35XX_GPIO4          0x49054000
#define OMAP35XX_GPIO5          0x49056000
#define OMAP35XX_GPIO6          0x49058000

/* GPIO registers */

#define OMAP35XX_GPIO_SYSCONFIG       0x010
#define OMAP35XX_GPIO_SYSSTATUS       0x014
#define OMAP35XX_GPIO_IRQSTATUS1      0x018
#define OMAP35XX_GPIO_IRQENABLE1      0x01C
#define OMAP35XX_GPIO_WAKEUPENABLE    0x020
#define OMAP35XX_GPIO_IRQSTATUS2      0x028
#define OMAP35XX_GPIO_IRQENABLE2      0x02C
#define OMAP35XX_GPIO_CTRL            0x030
#define OMAP35XX_GPIO_OE              0x034
#define OMAP35XX_GPIO_DATAIN          0x038
#define OMAP35XX_GPIO_DATAOUT         0x03C
#define OMAP35XX_GPIO_LEVELDETECT0    0x040
#define OMAP35XX_GPIO_LEVELDETECT1    0x044
#define OMAP35XX_GPIO_RISINGDETECT    0x048
#define OMAP35XX_GPIO_FALLINGDETECT   0x04C
#define OMAP35XX_GPIO_DEBOUNCENABLE   0x050
#define OMAP35XX_GPIO_DEBOUNCINGTIME  0x054
#define OMAP35XX_GPIO_CLEARIRQENABLE1 0x060
#define OMAP35XX_GPIO_SETIRQENABLE1   0x064
#define OMAP35XX_GPIO_CLEARIRQENABLE2 0x070
#define OMAP35XX_GPIO_SETIRQENABLE2   0x074
#define OMAP35XX_GPIO_CLEARWKUENA     0x080
#define OMAP35XX_GPIO_SETWKUENA       0x084
#define OMAP35XX_GPIO_CLEARDATAOUT    0x090
#define OMAP35XX_GPIO_SETDATAOUT      0x094

/* omap35xx contains 6 modules each with 32 GPIO pins, total of 192 pins */

#define GPIO_MAX_MODULES        6
#define GPIO_NUM_PINS_IN_MODULE 32
#define GPIO_MAX_PINS           192

/* GPIO modules functional & interface clock enable masks */
 
#define OMAP35XX_GPIO2_FCLK_EN        (1<<13)
#define OMAP35XX_GPIO2_ICLK_EN        (1<<13)
#define OMAP35XX_GPIO3_FCLK_EN        (1<<14)
#define OMAP35XX_GPIO3_ICLK_EN        (1<<14)
#define OMAP35XX_GPIO4_FCLK_EN        (1<<15)
#define OMAP35XX_GPIO4_ICLK_EN        (1<<15)
#define OMAP35XX_GPIO5_FCLK_EN        (1<<16)
#define OMAP35XX_GPIO5_ICLK_EN        (1<<16)
#define OMAP35XX_GPIO6_FCLK_EN        (1<<17)
#define OMAP35XX_GPIO6_ICLK_EN        (1<<17)

/*
 *============================================================
 * GPIO pin configuration for LogicPD 
 *============================================================
 */

#define OMAP35XX_GPIO_ISP1760_SUSPEND_N     182

#define OMAP35XX_GPIO_LAN9115_IRQ_PHYS_PIN  152   /* GPIO 5, BIT 24 */
#define OMAP35XX_GPIO_LAN9115_IRQ_BANK        5
#define OMAP35XX_GPIO_LAN9115_IRQ_BIT        24
#define OMAP35XX_GPIO_LAN9115_IRQ_MASK      (0x1 << 24)

#define OMAP35XX_GPIO_LCD_ENVDD_PIN           153   /* GPIO 5, BIT 25 */
#define OMAP35XX_GPIO_LCD_ENVDD_BANK          5
#define OMAP35XX_GPIO_LCD_ENVDD_BIT           25
#define OMAP35XX_GPIO_LCD_ENVDD_MASK          (0x1 << 25)

/* addresses of six GPIO registers used to allocate memory banks */

enum  _omap_gpio_bank_reg
    {
        OMAP3_GPIO1 = 0x48310000,
        OMAP3_GPIO2 = 0x49050000,
        OMAP3_GPIO3 = 0x49052000,
        OMAP3_GPIO4 = 0x49054000,
        OMAP3_GPIO5 = 0x49056000,
        OMAP3_GPIO6 = 0x49058000
    };

/* GPIO pin modes */

enum  _omap_gpio_io_mode
    {
        OMAP3_GPIO_OUTPUT,
        OMAP3_GPIO_INPUT
    };

/* define the power domain of the GPIO */

enum omapGpioPowerDomain
    {
    OMAP_GPIO_PWR_WKUP,
    OMAP_GPIO_PWR_PER,
    OMAP_GPIO_PWR_CORE
    };

/* define six GPIO modules */

enum omapGpioModules
    {
    OMAP_GPIO_MODULE_1,
    OMAP_GPIO_MODULE_2,
    OMAP_GPIO_MODULE_3,
    OMAP_GPIO_MODULE_4,
    OMAP_GPIO_MODULE_5,
    OMAP_GPIO_MODULE_6
    };

/* define power states for a GPIO module */

enum omapGpioMoudlePowerState
        {
        OMAP_GPIO_MODULE_POWER_ON,
        OMAP_GPIO_MODULE_POWER_OFF
        };

/* struct for registers and masks used to control module power */

struct  gpioPowerRegs
    {
    UINT32 regIclk;
    UINT32 regFclk;
    UINT32 maskIclk[GPIO_MAX_MODULES];
    UINT32 maskFclk[GPIO_MAX_MODULES];
    };


#define OMAP35XX_GPIO_REGISTER_WRITE(reg, value) \
                 *(volatile UINT32*)(reg) = value
#define OMAP35XX_GPIO_REGISTER_READ(reg)  \
                 (*(volatile UINT32*)(reg))

/* prototypes */

#ifndef _ASMLANGUAGE
IMPORT STATUS omap35xxGpioAllocatePin (UINT32 pin, UINT32 mode, BOOL outputValue);
IMPORT STATUS omap35xxGpioDeallocatePin (UINT32 pin);
IMPORT void   omap35xxGpioPinSet (UINT32 pin, BOOL val);
IMPORT INT32  omap35xxGpioPinGet (UINT32 pin);
IMPORT STATUS omap35xxGpioWritePinRegister (UINT32 pin, UINT32 reg, BOOL val);
IMPORT STATUS omap35xxGpioWriteRegister (UINT32 pin, UINT32 reg, UINT32 val);
IMPORT STATUS omap35xxGpioReadRegister (UINT32 pin, UINT32 reg, UINT32 *val);
IMPORT void   omap35xxGpioPadConf (UINT32 pin, UINT16 cfg);	
IMPORT void   omap35xxGpioConnectUsrIsr (void *usrIsr, UINT32 pin);
IMPORT void   omap35xxGpioPowerModules (UINT32 mode);
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INComap35xxGpioh */
