/* usbTcdFslConfig.h - Defines silicon config options to FSL TCD */

/*
 * Copyright (c) 2009, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
Modification history
--------------------
01b,09aug13,ljg  Set USB_SBUSCFG to INCR8 for MPC5125 errata workaround 
                 (WIND00405093)
01a,09sep09,w_x  created for various BSP configurations (WIND00180575)
*/

/*
DESCRIPTION

Defines the configuration macros to the USB TCD (target controller driver)
for the Freescale USB Dual-Role device.
*/

#ifndef __INCusbTcdFslConfigh
#define __INCusbTcdFslConfigh

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * These will be overriden by BSP config.h configurations;
 * These options must be changed according to the silicon
 * configuration.
 */

/*
 * Set to TRUE if the Dual-Role USB controller
 * USB registers (such as USBCMD/USBSTS regsiters)
 * are in big endian.
 *
 * (e.g, some MPC5121E silicon versions should be TRUE)
 */

#ifndef FSL_USB_DR_DEVICE_BE_REG
#   define FSL_USB_DR_DEVICE_BE_REG FALSE
#endif

/*
 * Set to TRUE if the Dual-Role USB controller
 * data strcuctures (such as dQH/dTD structures)
 * are in big endian.
 *
 * (e.g, some MPC5121E silicon versions should be TRUE)
 */

#ifndef FSL_USB_DR_DEVICE_BE_DESC
#   define FSL_USB_DR_DEVICE_BE_DESC FALSE
#endif

/*
 * Set to TRUE if the Dual-Role USB controller
 * has system config registers (such as SNOOP registers)
 *
 * (e.g, MPC8313E silicon versions should be TRUE)
 */

#ifndef FSL_USB_DR_DEVICE_SYS_CONF
#   define FSL_USB_DR_DEVICE_SYS_CONF FALSE
#endif

/*
 * Set to TRUE if the Dual-Role USB controller
 * setup packet buffer is in big endian. Most silicons
 * use the native CPU endian for the setup packet buffer,
 * but some MPC5121E silicon versions use litte endian
 * for setup packet buffer even it is big endian CPU.
 *
 * (e.g, some MPC5121E silicon versions should be FALSE)
 */

#ifndef FSL_USB_DR_DEVICE_BE_SETUP
#   if (_BYTE_ORDER == _BIG_ENDIAN)
#   define FSL_USB_DR_DEVICE_BE_SETUP  TRUE /* In BE system default to BE */
#   else
#   define FSL_USB_DR_DEVICE_BE_SETUP  FALSE /* In LE system default to LE */
#   endif
#endif

/*
 * Set to TRUE if the Dual-Role USB controller
 * USBMODE register has a ES (Endian Selction) field.
 * If it has this field, it can be used to change the byte
 * alignment of the transfer buffers to match CPU endian mode.
 * If the CPU has this field, the TCD will set the field
 * according to the CPU endian it runs on to match them.
 *
 * (e.g, MPC5121E and i.MX31 silicon versions should be TRUE)
 */

#ifndef FSL_USB_DR_DEVICE_BUFFER_ES
#   define FSL_USB_DR_DEVICE_BUFFER_ES  FALSE
#endif

/*
 * Each hardware platform may have different platform specific hardware
 * initialization procedures, such as PIN MUX and module CLK initilization.
 * Specify this macro with the FUNCPTR of the BSP specific USB device module
 * hardware initlization routine.
 */

#ifndef FSL_USB_DR_DEVICE_HW_INIT
#   define FSL_USB_DR_DEVICE_HW_INIT NULL
#endif

/*
 * Specify the register base address of the USB device module.
 *
 * The base address is the address that adding 0x100 will reach
 * the CAPLENGTH register, and adding 0x140 will reach the USBCMD
 * register.
 *
 * This is platform specific.
 */

#ifndef FSL_USB_DR_DEVICE_IO_BASE
#   error "Please define FSL_USB_DR_DEVICE_IO_BASE in BSP config.h"
#endif

/*
 * Specify the interrupt number of the USB device module.
 *
 * The interrupt number is the one through which a USB endpoint
 * interrupt can be reported.
 *
 * This is platform specific.
 */

#ifndef FSL_USB_DR_DEVICE_INT_NUM
#   error "Please define FSL_USB_DR_DEVICE_INT_NUM in BSP config.h"
#endif

/*
 * Specify the PHY mode of the USB device module.
 *
 * The PHY mode is specific to the silicon implementation and the board
 * hardware design. You may need to refer to both the silicon mannuals
 * for usable options for the port and the board schematic for the
 * hardware wiring (selection) of the actual used PHY.
 *
 * The avaiable FSL_USB_DR_DEVICE_PHY_MODE options are:
 *
 * #define FSL_USB_DR_PHY_ULPI         0x0001
 * #define FSL_USB_DR_PHY_UTMI8        0x0002
 * #define FSL_USB_DR_PHY_UTMI16       0x0003
 * #define FSL_USB_DR_PHY_SERIAL       0x0004
 *
 * Based on this FSL_USB_DR_DEVICE_PHY_MODE configuration, the TCD will write
 * proper values in the PORTSCn PTS and PTW fields.
 *
 * This is platform specific.
 */

#ifndef FSL_USB_DR_DEVICE_PHY_MODE
#   error "Please define FSL_USB_DR_DEVICE_PHY_MODE in BSP config.h"
#endif


/*
 * Specify the platform type of the USB device.
 */

#ifndef FSL_USB_DR_DEVICE_PLATFORM_TYPE
#   define FSL_USB_DR_DEVICE_PLATFORM_TYPE     0
#endif

#ifdef  __cplusplus
}
#endif

#endif  /* __INCusbTcdFslConfigh */

