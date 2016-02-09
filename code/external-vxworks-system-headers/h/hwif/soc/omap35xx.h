/* omap35xx.h - LogicPD OMAP35x header file */

/*
 * Copyright (c) 2008-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,24aug11,jmz  WIND00292261 add new definitions
01l,24may11,jmz  Update with additional registers and definitions
01k,24feb11,rec  fix system clock rate for 13mhz part
01j,16feb11,rec  add sysclk2 output enable
01i,12feb11,w_x  add CLOCK module ICLK/FCLK bit masks
01h,10feb11,rdl  add define for SR functional clocks
01g,04feb11,jmz  Update ISP1760 memory location to be x-loader compatible
01f,03feb11,rdl  move reg macros to a more central place
01e,26jan11,jmz  Add support for ISP1760 USB Host Controller
01d,10jan11,rdl  add definition for product ID region
01c,25oct10,rec  fix file header
01b,29sep10,rec  add smart reflex base addresses
01a,27sep10,rdl  created from omap.h v01c
*/

/*
This file contains memory and I/O address and related constants for the
LogicPD OMAP35x board. This board features the Texas Instruments OMAP3530
processor with an ARM OMAP3 Cortex-A8 core.

See Also OMAP35xx Applications Processor Technical Reference Manual, Texas Instruments.

*/

#ifndef __INComaph
#define __INComaph

#include <hwif/soc/omap35xxIRQ.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Handy sizes */

#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_32K                          0x00008000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define SZ_1G                           0x40000000
#define SZ_2G                           0x80000000

#define TARGET_OMAP

/* Exception vectors are located at 0x00014000 if using WindRiver nand loader*/
#define OMAP3_EXC_VEC_BASE   0x14000

/* 48 MHz input clock */

#define UART_CLK_FREQ        (48000000)

/* 32KHz Always-on Clock */

#define SYS_32K_CLK_FREQ     (32768)

#define OMAP32XX_CLK_SOURCE_32K 0
#define OMAP32XX_CLK_SOURCE_SYS 1

/* macros to manipulate registers */

#define OMAP35XX_REG_READ(address)	        \
    *(volatile UINT32 *)(address)

#define OMAP35XX_REG_WRITE(address, value)	        	\
    *(volatile UINT32 *)(address) = (UINT32)(value)

#define OMAP35XX_REG_MODIFY(address, mask, value)	        \
    OMAP35XX_REG_WRITE (address, (OMAP35XX_REG_READ(address) & ~(mask)) | \
                        (value))

#define OMAP35XX_SHORT_REG_WRITE(address, value) \
    *(volatile UINT16*)(address) = value

#define OMAP35XX_SHORT_REG_READ(address)  \
    (*(volatile UINT16*)(address))



/*
 * ============================================================
 * Region allocation for PRCM registers
 * ============================================================
 */


/*
 * Clock manager registers
 */

#define OMAP35XX_PRCM_CM_REGS  0x48004000


#define   OMAP35XX_IVA2_CM            (OMAP35XX_PRCM_CM_REGS + 0x0)
#define     OMAP35XX_CM_FCLKEN_IVA2        (OMAP35XX_IVA2_CM +0x00)
#define     OMAP35XX_CM_CLKEN_PLL_IVA2     (OMAP35XX_IVA2_CM +0x04)
#define     OMAP35XX_CM_IDLEST_IVA2        (OMAP35XX_IVA2_CM +0x20)
#define     OMAP35XX_CM_IDLEST_PLL_IVA2    (OMAP35XX_IVA2_CM +0x24)
#define     OMAP35XX_CM_AUTOIDLE_PLL_IVA2  (OMAP35XX_IVA2_CM +0x34)
#define     OMAP35XX_CM_CLKSEL1_PLL_IVA2   (OMAP35XX_IVA2_CM +0x40)
#define     OMAP35XX_CM_CLKSEL2_PLL_IVA2   (OMAP35XX_IVA2_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_IVA2     (OMAP35XX_IVA2_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_IVA2       (OMAP35XX_IVA2_CM +0x4C)

#define   OMAP35XX_OCP_CM           (OMAP35XX_PRCM_CM_REGS + 0x800)
#define     OMAP35XX_CM_REVISION            (OMAP35XX_OCP_CM +0x00)
#define     OMAP35XX_CM_SYSCONFIG           (OMAP35XX_OCP_CM +0x10)

#define   OMAP35XX_MPU_CM           (OMAP35XX_PRCM_CM_REGS + 0x900)
#define     OMAP35XX_CM_CLKEN_PLL_MPU       (OMAP35XX_MPU_CM +0x04)
#define     OMAP35XX_CM_IDLEST_MPU          (OMAP35XX_MPU_CM +0x20)
#define     OMAP35XX_CM_IDLEST_PLL_MPU      (OMAP35XX_MPU_CM +0x24)
#define     OMAP35XX_CM_AUTOIDLE_PLL_MPU    (OMAP35XX_MPU_CM +0x34)
#define     OMAP35XX_CM_CLKSEL1_PLL_MPU     (OMAP35XX_MPU_CM +0x40)
#define     OMAP35XX_CM_CLKSEL2_PLL_MPU     (OMAP35XX_MPU_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_MPU       (OMAP35XX_MPU_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_MPU         (OMAP35XX_MPU_CM +0x4C)

#define   OMAP35XX_CORE_CM          (OMAP35XX_PRCM_CM_REGS + 0xA00)
#define     OMAP35XX_CM_FCLKEN1_CORE       (OMAP35XX_CORE_CM +0x00)
#define     OMAP35XX_CM_FCLKEN3_CORE       (OMAP35XX_CORE_CM +0x08)
#define     OMAP35XX_CM_ICLKEN1_CORE       (OMAP35XX_CORE_CM +0x10)
#define     OMAP35XX_CM_ICLKEN2_CORE       (OMAP35XX_CORE_CM +0x14)
#define     OMAP35XX_CM_ICLKEN3_CORE       (OMAP35XX_CORE_CM +0x18)
#define     OMAP35XX_CM_IDLEST1_CORE       (OMAP35XX_CORE_CM +0x20)
#define     OMAP35XX_CM_IDLEST3_CORE       (OMAP35XX_CORE_CM +0x28)
#define     OMAP35XX_CM_AUTOIDLE1_CORE     (OMAP35XX_CORE_CM +0x30)
#define     OMAP35XX_CM_AUTOIDLE2_CORE     (OMAP35XX_CORE_CM +0x34)
#define     OMAP35XX_CM_AUTOIDLE3_CORE     (OMAP35XX_CORE_CM +0x38)
#define     OMAP35XX_CM_CLKSEL_CORE        (OMAP35XX_CORE_CM +0x40)
#define     OMAP35XX_CM_CLKSTCTRL_CORE     (OMAP35XX_CORE_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_CORE       (OMAP35XX_CORE_CM +0x4C)

#define   OMAP35XX_SGX_CM           (OMAP35XX_PRCM_CM_REGS + 0xB00)
#define     OMAP35XX_CM_FCLKEN_SGX          (OMAP35XX_SGX_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_SGX          (OMAP35XX_SGX_CM +0x10)
#define     OMAP35XX_CM_IDLEST_SGX          (OMAP35XX_SGX_CM +0x20)
#define     OMAP35XX_CM_CLKSEL_SGX          (OMAP35XX_SGX_CM +0x40)
#define     OMAP35XX_CM_SLEEPDEP_SGX        (OMAP35XX_SGX_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_SGX       (OMAP35XX_SGX_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_SGX         (OMAP35XX_SGX_CM +0x4C)

#define   OMAP35XX_WKUP_CM          (OMAP35XX_PRCM_CM_REGS + 0xC00)
#define     OMAP35XX_CM_FCLKEN_WKUP        (OMAP35XX_WKUP_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_WKUP        (OMAP35XX_WKUP_CM +0x10)
#define     OMAP35XX_CM_IDLEST_WKUP        (OMAP35XX_WKUP_CM +0x20)
#define     OMAP35XX_CM_AUTOIDLE_WKUP      (OMAP35XX_WKUP_CM +0x30)
#define     OMAP35XX_CM_CLKSEL_WKUP        (OMAP35XX_WKUP_CM +0x40)

#define   OMAP35XX_CCR_CM           (OMAP35XX_PRCM_CM_REGS + 0xD00)
#define     OMAP35XX_CM_CLKEN_PLL           (OMAP35XX_CCR_CM +0x00)
#define     OMAP35XX_CM_CLKEN2_PLL          (OMAP35XX_CCR_CM +0x04)
#define     OMAP35XX_CM_IDLEST_CKGEN        (OMAP35XX_CCR_CM +0x20)
#define     OMAP35XX_CM_IDLEST2_CKGEN       (OMAP35XX_CCR_CM +0x24)
#define     OMAP35XX_CM_AUTOIDLE_PLL        (OMAP35XX_CCR_CM +0x30)
#define     OMAP35XX_CM_AUTOIDLE2_PLL       (OMAP35XX_CCR_CM +0x34)
#define     OMAP35XX_CM_CLKSEL1_PLL         (OMAP35XX_CCR_CM +0x40)
#define     OMAP35XX_CM_CLKSEL2_PLL         (OMAP35XX_CCR_CM +0x44)
#define     OMAP35XX_CM_CLKSEL3_PLL         (OMAP35XX_CCR_CM +0x48)
#define     OMAP35XX_CM_CLKSEL4_PLL         (OMAP35XX_CCR_CM +0x4C)
#define     OMAP35XX_CM_CLKSEL5_PLL         (OMAP35XX_CCR_CM +0x50)
#define     OMAP35XX_CM_CLKOUT_CTRL         (OMAP35XX_CCR_CM +0x70)

#define   OMAP35XX_DSS_CM           (OMAP35XX_PRCM_CM_REGS + 0xE00)
#define     OMAP35XX_CM_FCLKEN_DSS          (OMAP35XX_DSS_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_DSS          (OMAP35XX_DSS_CM +0x10)
#define     OMAP35XX_CM_IDLEST_DSS          (OMAP35XX_DSS_CM +0x20)
#define     OMAP35XX_CM_AUTOIDLE_DSS        (OMAP35XX_DSS_CM +0x30)
#define     OMAP35XX_CM_CLKSEL_DSS          (OMAP35XX_DSS_CM +0x40)
#define     OMAP35XX_CM_SLEEPDEP_DSS        (OMAP35XX_DSS_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_DSS       (OMAP35XX_DSS_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_DSS         (OMAP35XX_DSS_CM +0x4C)

#define   OMAP35XX_CAM_CM           (OMAP35XX_PRCM_CM_REGS + 0xF00)
#define     OMAP35XX_CM_FCLKEN_CAM          (OMAP35XX_CAM_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_CAM          (OMAP35XX_CAM_CM +0x10)
#define     OMAP35XX_CM_IDLEST_CAM          (OMAP35XX_CAM_CM +0x20)
#define     OMAP35XX_CM_AUTOIDLE_CAM        (OMAP35XX_CAM_CM +0x30)
#define     OMAP35XX_CM_CLKSEL_CAM          (OMAP35XX_CAM_CM +0x40)
#define     OMAP35XX_CM_SLEEPDEP_CAM        (OMAP35XX_CAM_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_CAM       (OMAP35XX_CAM_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_CAM         (OMAP35XX_CAM_CM +0x4C)

#define   OMAP35XX_PER_CM          (OMAP35XX_PRCM_CM_REGS + 0x1000)
#define     OMAP35XX_CM_FCLKEN_PER          (OMAP35XX_PER_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_PER          (OMAP35XX_PER_CM +0x10)
#define     OMAP35XX_CM_IDLEST_PER          (OMAP35XX_PER_CM +0x20)
#define     OMAP35XX_CM_AUTOIDLE_PER        (OMAP35XX_PER_CM +0x30)
#define     OMAP35XX_CM_CLKSEL_PER          (OMAP35XX_PER_CM +0x40)
#define     OMAP35XX_CM_SLEEPDEP_PER        (OMAP35XX_PER_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_PER       (OMAP35XX_PER_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_PER         (OMAP35XX_PER_CM +0x4C)

#define   OMAP35XX_EMU_CM          (OMAP35XX_PRCM_CM_REGS + 0x1100)
#define     OMAP35XX_CM_CLKSEL1_EMU         (OMAP35XX_EMU_CM +0x40)
#define     OMAP35XX_CM_CLKSTCTRL_EMU       (OMAP35XX_EMU_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_EMU         (OMAP35XX_EMU_CM +0x4C)
#define     OMAP35XX_CM_CLKSEL2_EMU         (OMAP35XX_EMU_CM +0x50)
#define     OMAP35XX_CM_CLKSEL3_EMU         (OMAP35XX_EMU_CM +0x54)

#define   OMAP35XX_GLOBAL_CM       (OMAP35XX_PRCM_CM_REGS + 0x1200)
#define     OMAP35XX_CM_POLCTRL_GLOBAL   (OMAP35XX_GLOBAL_CM +0x9C)

#define   OMAP35XX_NEON_CM         (OMAP35XX_PRCM_CM_REGS + 0x1300)
#define     OMAP35XX_CM_IDLEST_NEON        (OMAP35XX_NEON_CM +0x20)
#define     OMAP35XX_CM_CLKSTCTRL_NEON     (OMAP35XX_NEON_CM +0x48)

#define   OMAP35XX_USBHOST_CM      (OMAP35XX_PRCM_CM_REGS + 0x1400)
#define     OMAP35XX_CM_FCLKEN_USBHOST    (OMAP35XX_USBHOST_CM +0x00)
#define     OMAP35XX_CM_ICLKEN_USBHOST    (OMAP35XX_USBHOST_CM +0x10)
#define     OMAP35XX_CM_IDLEST_USBHOST    (OMAP35XX_USBHOST_CM +0x20)
#define     OMAP35XX_CM_AUTOIDLE_USBHOST  (OMAP35XX_USBHOST_CM +0x30)
#define     OMAP35XX_CM_CLKSEL_USBHOST    (OMAP35XX_USBHOST_CM +0x40)
#define     OMAP35XX_CM_SLEEPDEP_USBHOST  (OMAP35XX_USBHOST_CM +0x44)
#define     OMAP35XX_CM_CLKSTCTRL_USBHOST (OMAP35XX_USBHOST_CM +0x48)
#define     OMAP35XX_CM_CLKSTST_USBHOST   (OMAP35XX_USBHOST_CM +0x4C)

/* Clock manager bits offset */

#define OMAP35XX_CM_CLKEN2_PLL_PERIPH2_DPLL_FREQSEL_SHIFT     (4)
#define OMAP35XX_CM_CLKEN2_PLL_PERIPH2_DPLL_FREQSEL           (0xf << 4)
#define OMAP35XX_CM_CLKEN2_PLL_EN_PERIPH2_DPLL_SHIFT          (0)
#define OMAP35XX_CM_CLKEN2_PLL_EN_PERIPH2_DPLL                (0x7 << 0)
#define OMAP35XX_CM_CLKSEL4_PLL_PERIPH2_DPLL_DIV_SHIFT        (0)
#define OMAP35XX_CM_CLKSEL4_PLL_PERIPH2_DPLL_DIV              (0x7f << 0)
#define OMAP35XX_CM_CLKSEL4_PLL_PERIPH2_DPLL_MULT_SHIFT       (8)
#define OMAP35XX_CM_CLKSEL4_PLL_PERIPH2_DPLL_MULT             (0x7ff << 8)
#define OMAP35XX_CM_CLKSEL5_PLL_DIV_120M_SHIFT                (0)
#define OMAP35XX_CM_CLKSEL5_PLL_DIV_120M                      (0x1f << 0)

/*
 * power and reset manager registers
 */

#define OMAP35XX_PRCM_PRM_REGS 0x48306000

#define   OMAP35XX_IVA2_PRM          (OMAP35XX_PRCM_PRM_REGS + 0x0)
#define     OMAP35XX_RM_RSTCTRL_IVA2     (OMAP35XX_IVA2_PRM + 0x50)
#define     OMAP35XX_RM_RSTST_IVA2       (OMAP35XX_IVA2_PRM + 0x58)
#define     OMAP35XX_PM_WKDEP_IVA2       (OMAP35XX_IVA2_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_IVA2    (OMAP35XX_IVA2_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_IVA2      (OMAP35XX_IVA2_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_IVA2   (OMAP35XX_IVA2_PRM + 0xE8)
#define     OMAP35XX_PRM_IRQSTATUS_IVA2  (OMAP35XX_IVA2_PRM + 0xF8)
#define     OMAP35XX_PRM_IRQENABLE_IVA2  (OMAP35XX_IVA2_PRM + 0xFC)

#define   OMAP35XX_OCP_PRM         (OMAP35XX_PRCM_PRM_REGS + 0x800)
#define     OMAP35XX_PRM_REVISION         (OMAP35XX_OCP_PRM + 0x04)
#define     OMAP35XX_PRM_SYSCONFIG        (OMAP35XX_OCP_PRM + 0x14)
#define     OMAP35XX_PRM_IRQSTATUS_MPU    (OMAP35XX_OCP_PRM + 0x18)
#define     OMAP35XX_PRM_IRQENABLE_MPU    (OMAP35XX_OCP_PRM + 0x1C)

#define   OMAP35XX_MPU_PRM         (OMAP35XX_PRCM_PRM_REGS + 0x900)
#define     OMAP35XX_RM_RSTST_MPU         (OMAP35XX_MPU_PRM + 0x58)
#define     OMAP35XX_PM_WKDEP_MPU         (OMAP35XX_MPU_PRM + 0xC8)
#define     OMAP35XX_RM_EVGENCTRL_MPU     (OMAP35XX_MPU_PRM + 0xD4)
#define     OMAP35XX_PM_EVGENONTIM_MPU    (OMAP35XX_MPU_PRM + 0xD8)
#define     OMAP35XX_PM_EVGENOFFTIM_MPU   (OMAP35XX_MPU_PRM + 0xDC)
#define     OMAP35XX_PM_PWSTCTRL_MPU      (OMAP35XX_MPU_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_MPU        (OMAP35XX_MPU_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_MPU     (OMAP35XX_MPU_PRM + 0xE8)

#define   OMAP35XX_CORE_PRM        (OMAP35XX_PRCM_PRM_REGS + 0xA00)
#define     OMAP35XX_RM_RSTST_CORE       (OMAP35XX_CORE_PRM + 0x58)
#define     OMAP35XX_PM_WKEN1_CORE       (OMAP35XX_CORE_PRM + 0xA0)
#define     OMAP35XX_PM_MPUGRPSEL1_CORE  (OMAP35XX_CORE_PRM + 0xA4)
#define     OMAP35XX_PM_IVA2GRPSEL1_CORE (OMAP35XX_CORE_PRM + 0xA8)
#define     OMAP35XX_PM_WKST1_CORE       (OMAP35XX_CORE_PRM + 0xB0)
#define     OMAP35XX_PM_WKST3_CORE       (OMAP35XX_CORE_PRM + 0xB8)
#define     OMAP35XX_PM_PWSTCTRL_CORE    (OMAP35XX_CORE_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_CORE      (OMAP35XX_CORE_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_CORE   (OMAP35XX_CORE_PRM + 0xE8)
#define     OMAP35XX_PM_WKEN3_CORE       (OMAP35XX_CORE_PRM + 0xF0)
#define     OMAP35XX_PM_IVA2GRPSEL3_CORE (OMAP35XX_CORE_PRM + 0xF4)
#define     OMAP35XX_PM_MPUGRPSEL3_CORE  (OMAP35XX_CORE_PRM + 0xF8)

#define   OMAP35XX_SGX_PRM         (OMAP35XX_PRCM_PRM_REGS + 0xB00)
#define     OMAP35XX_RM_RSTST_SGX         (OMAP35XX_SGX_PRM + 0x58)
#define     OMAP35XX_PM_WKDEP_SGX         (OMAP35XX_SGX_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_SGX      (OMAP35XX_SGX_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_SGX        (OMAP35XX_SGX_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_SGX     (OMAP35XX_SGX_PRM + 0xE8)

#define   OMAP35XX_WKUP_PRM        (OMAP35XX_PRCM_PRM_REGS + 0xC00)
#define     OMAP35XX_PM_WKEN_WKUP        (OMAP35XX_WKUP_PRM + 0xA0)
#define     OMAP35XX_PM_MPUGRPSEL_WKUP   (OMAP35XX_WKUP_PRM + 0xA4)
#define     OMAP35XX_PM_IVA2GRPSEL_WKUP  (OMAP35XX_WKUP_PRM + 0xA8)
#define     OMAP35XX_PM_WKST_WKUP        (OMAP35XX_WKUP_PRM + 0xB0)

#define   OMAP35XX_CCR_PRM         (OMAP35XX_PRCM_PRM_REGS + 0xD00)
#define     OMAP35XX_PRM_CLKSEL           (OMAP35XX_CCR_PRM + 0x40)
#define     OMAP35XX_PRM_CLKOUT_CTRL      (OMAP35XX_CCR_PRM + 0x70)

#define   OMAP35XX_DSS_PRM         (OMAP35XX_PRCM_PRM_REGS + 0xE00)
#define     OMAP35XX_RM_RSTST_DSS         (OMAP35XX_DSS_PRM + 0x58)
#define     OMAP35XX_PM_WKEN_DSS          (OMAP35XX_DSS_PRM + 0xA0)
#define     OMAP35XX_PM_WKDEP_DSS         (OMAP35XX_DSS_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_DSS      (OMAP35XX_DSS_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_DSS        (OMAP35XX_DSS_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_DSS     (OMAP35XX_DSS_PRM + 0xE8)

#define   OMAP35XX_CAM_PRM         (OMAP35XX_PRCM_PRM_REGS + 0xF00)
#define     OMAP35XX_RM_RSTST_CAM         (OMAP35XX_CAM_PRM + 0x58)
#define     OMAP35XX_PM_WKDEP_CAM         (OMAP35XX_CAM_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_CAM      (OMAP35XX_CAM_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_CAM        (OMAP35XX_CAM_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_CAM     (OMAP35XX_CAM_PRM + 0xE8)

#define   OMAP35XX_PER_PRM        (OMAP35XX_PRCM_PRM_REGS + 0x1000)
#define     OMAP35XX_RM_RSTST_PER         (OMAP35XX_PER_PRM + 0x58)
#define     OMAP35XX_PM_WKEN_PER          (OMAP35XX_PER_PRM + 0xA0)
#define     OMAP35XX_PM_MPUGRPSEL_PER     (OMAP35XX_PER_PRM + 0xA4)
#define     OMAP35XX_PM_IVA2GRPSEL_PER    (OMAP35XX_PER_PRM + 0xA8)
#define     OMAP35XX_PM_WKST_PER          (OMAP35XX_PER_PRM + 0xB0)
#define     OMAP35XX_PM_WKDEP_PER         (OMAP35XX_PER_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_PER      (OMAP35XX_PER_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_PER        (OMAP35XX_PER_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_PER     (OMAP35XX_PER_PRM + 0xE8)

#define   OMAP35XX_EMU_PRM        (OMAP35XX_PRCM_PRM_REGS + 0x1100)
#define     OMAP35XX_RM_RSTST_EMU         (OMAP35XX_EMU_PRM + 0x58)
#define     OMAP35XX_PM_PWSTST_EMU        (OMAP35XX_EMU_PRM + 0xE4)

#define   OMAP35XX_GLOBAL_PRM     (OMAP35XX_PRCM_PRM_REGS + 0x1200)
#define     OMAP35XX_PRM_VC_SMPS_SA      (OMAP35XX_GLOBAL_PRM+0x20)
#define     OMAP35XX_PRM_VC_SMPS_VOL_RA  (OMAP35XX_GLOBAL_PRM+0x24)
#define     OMAP35XX_PRM_VC_SMPS_CMD_RA  (OMAP35XX_GLOBAL_PRM+0x28)
#define     OMAP35XX_PRM_VC_CMD_VAL_0    (OMAP35XX_GLOBAL_PRM+0x2C)
#define     OMAP35XX_PRM_VC_CMD_VAL_1    (OMAP35XX_GLOBAL_PRM+0x30)
#define     OMAP35XX_PRM_VC_CH_CONF      (OMAP35XX_GLOBAL_PRM+0x34)
#define     OMAP35XX_PRM_VC_I2C_CFG      (OMAP35XX_GLOBAL_PRM+0x38)
#define     OMAP35XX_PRM_VC_BYPASS_VAL   (OMAP35XX_GLOBAL_PRM+0x3C)
#define     OMAP35XX_PRM_RSTCTRL         (OMAP35XX_GLOBAL_PRM+0x50)
#define     OMAP35XX_PRM_RSTTIME         (OMAP35XX_GLOBAL_PRM+0x54)
#define     OMAP35XX_PRM_RSTST           (OMAP35XX_GLOBAL_PRM+0x58)
#define     OMAP35XX_PRM_VOLTCTRL        (OMAP35XX_GLOBAL_PRM+0x60)
#define     OMAP35XX_PRM_SRAM_PCHARGE    (OMAP35XX_GLOBAL_PRM+0x64)
#define     OMAP35XX_PRM_CLKSRC_CTRL     (OMAP35XX_GLOBAL_PRM+0x70)
#define     OMAP35XX_PRM_OBS             (OMAP35XX_GLOBAL_PRM+0x80)
#define     OMAP35XX_PRM_VOLTSETUP1      (OMAP35XX_GLOBAL_PRM+0x90)
#define     OMAP35XX_PRM_VOLTOFFSET      (OMAP35XX_GLOBAL_PRM+0x94)
#define     OMAP35XX_PRM_CLKSETUP        (OMAP35XX_GLOBAL_PRM+0x98)
#define     OMAP35XX_PRM_POLCTRL         (OMAP35XX_GLOBAL_PRM+0x9C)
#define     OMAP35XX_PRM_VOLTSETUP2      (OMAP35XX_GLOBAL_PRM+0xA0)
#define     OMAP35XX_PRM_VP1_CONFIG      (OMAP35XX_GLOBAL_PRM+0xB0)
#define     OMAP35XX_PRM_VP1_VSTEPMIN    (OMAP35XX_GLOBAL_PRM+0xB4)
#define     OMAP35XX_PRM_VP1_VSTEPMAX    (OMAP35XX_GLOBAL_PRM+0xB8)
#define     OMAP35XX_PRM_VP1_VLIMITTO    (OMAP35XX_GLOBAL_PRM+0xBC)
#define     OMAP35XX_PRM_VP1_VOLTAGE     (OMAP35XX_GLOBAL_PRM+0xC0)
#define     OMAP35XX_PRM_VP1_STATUS      (OMAP35XX_GLOBAL_PRM+0xC4)
#define     OMAP35XX_PRM_VP2_CONFIG      (OMAP35XX_GLOBAL_PRM+0xD0)
#define     OMAP35XX_PRM_VP2_VSTEPMIN    (OMAP35XX_GLOBAL_PRM+0xD4)
#define     OMAP35XX_PRM_VP2_VSTEPMAX    (OMAP35XX_GLOBAL_PRM+0xD8)
#define     OMAP35XX_PRM_VP2_VLIMITTO    (OMAP35XX_GLOBAL_PRM+0xDC)
#define     OMAP35XX_PRM_VP2_VOLTAGE     (OMAP35XX_GLOBAL_PRM+0xE0)
#define     OMAP35XX_PRM_VP2_STATUS      (OMAP35XX_GLOBAL_PRM+0xE4)

#define   OMAP35XX_NEON_PRM       (OMAP35XX_PRCM_PRM_REGS + 0x1300)
#define     OMAP35XX_RM_RSTST_NEON       (OMAP35XX_NEON_PRM + 0x58)
#define     OMAP35XX_PM_WKDEP_NEON       (OMAP35XX_NEON_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_NEON    (OMAP35XX_NEON_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_NEON      (OMAP35XX_NEON_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_NEON   (OMAP35XX_NEON_PRM + 0xE8)

#define   OMAP35XX_USBHOST_PRM          (OMAP35XX_PRCM_PRM_REGS + 0x1400)
#define     OMAP35XX_RM_RSTST_USBHOST       (OMAP35XX_USBHOST_PRM + 0x58)
#define     OMAP35XX_PM_WKEN_USBOST         (OMAP35XX_USBHOST_PRM + 0xA0)
#define     OMAP35XX_PM_MPUGRPSEL_USBHOST   (OMAP35XX_USBHOST_PRM + 0xA4)
#define     OMAP35XX_PM_IVA2GRPSEL_USBHOST  (OMAP35XX_USBHOST_PRM + 0xA8)
#define     OMAP35XX_PM_WKST_USBHOST        (OMAP35XX_USBHOST_PRM + 0xB0)
#define     OMAP35XX_PM_WKDEP_USBHOST       (OMAP35XX_USBHOST_PRM + 0xC8)
#define     OMAP35XX_PM_PWSTCTRL_USBHOST    (OMAP35XX_USBHOST_PRM + 0xE0)
#define     OMAP35XX_PM_PWSTST_USBHOST      (OMAP35XX_USBHOST_PRM + 0xE4)
#define     OMAP35XX_PM_PREPWSTST_USBHOST   (OMAP35XX_USBHOST_PRM + 0xE8)

/*
 * ============================================================
 * Region Allocation for Product ID
 * ============================================================
 */

#define	OMAP34XX_PRODID			0x4830A000
#define	  OMAP34XX_PRODID_IDCODE	(OMAP34XX_PRODID + 0x204)
#define	  OMAP34XX_PRODID_SKUID		(OMAP34XX_PRODID + 0x20C)


/*
 * ============================================================
 * Region Allocation for L4-Core Interconnect
 * ============================================================
 */

#define OMAP35XX_L4_SYSCTRL               0x48002000
#define   OMAP35XX_L4_SYSCTRL_MOD         (OMAP35XX_L4_SYSCTRL + 0x0)
#define   OMAP35XX_L4_SYSCTRL_INTCT       (OMAP35XX_L4_SYSCTRL + 0x1000)

#define OMAP35XX_L4_CLOCK_MANAGER         0x48004000
#define   OMAP35XX_L4_CLOCK_MANAGER_MODA  (OMAP35XX_L4_CLOCK_MANAGER + 0x0)
#define   OMAP35XX_L4_CLOCK_MANAGER_MODB  (OMAP35XX_L4_CLOCK_MANAGER + 0x1000)
#define   OMAP35XX_L4_CLOCK_MANAGER_INTCT (OMAP35XX_L4_CLOCK_MANAGER + 0x3000)

#define OMAP35XX_L4_L4_CORE_CONFIG        0x48040000
#define   OMAP35XX_L4_L4_CORE_CONFIG_AP  (OMAP35XX_L4_L4_CORE_CONFIG + 0x0)
#define   OMAP35XX_L4_L4_CORE_CONFIG_IP  (OMAP35XX_L4_L4_CORE_CONFIG + 0x0800)
#define   OMAP35XX_L4_L4_CORE_CONFIG_LA  (OMAP35XX_L4_L4_CORE_CONFIG + 0x1000)

#define OMAP35XX_L4_DISPLAY_SUBSYSTEM           0x4804FC00
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_DSI     \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x0)
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_TOP     \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x0400)
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_CTRL    \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x0800)
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_RFBI    \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x0C00)
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_VID     \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x1000)
#define   OMAP35XX_L4_DISPLAY_SUBSYSTEM_INTCT   \
                  (OMAP35XX_L4_DISPLAY_SUBSYSTEM + 0x1400)

#define OMAP35XX_L4_SDMA                  0x48056000
#define   OMAP35XX_L4_SDMA_MOD                  (OMAP35XX_L4_SDMA + 0x0)
#define   OMAP35XX_L4_SDMA_INTCT                (OMAP35XX_L4_SDMA + 0x1000)

#define OMAP35XX_L4_I2C3                  0x48060000
#define   OMAP35XX_L4_I2C3_MOD                  (OMAP35XX_L4_I2C3 + 0x0)
#define   OMAP35XX_L4_I2C3_INTCT                (OMAP35XX_L4_I2C3 + 0x1000)

#define OMAP35XX_L4_USBTLL                0x48062000
#define   OMAP35XX_L4_USBTLL_MOD                (OMAP35XX_L4_USBTLL + 0x0)
#define   OMAP35XX_L4_USBTLL_INTCT              (OMAP35XX_L4_USBTLL + 0x1000)

#define OMAP35XX_L4_USBHS_HOST            0x48064000
#define   OMAP35XX_L4_USBHS_HOST_MOD            (OMAP35XX_L4_USBHS_HOST + 0x0)
#define   OMAP35XX_L4_USBHS_HOST_INTCT          (OMAP35XX_L4_USBHS_HOST + 0x1000)

#define OMAP35XX_L4_UART1                 0x4806A000
#define   OMAP35XX_L4_UART1_MOD                 (OMAP35XX_L4_UART1 + 0x0)
#define   OMAP35XX_L4_UART1_INTCT               (OMAP35XX_L4_UART1 + 0x1000)

#define OMAP35XX_L4_UART2                 0x4806C000
#define   OMAP35XX_L4_UART2_MOD                 (OMAP35XX_L4_UART2 + 0x0)
#define   OMAP35XX_L4_UART2_INTCT               (OMAP35XX_L4_UART2 + 0x1000)

#define OMAP35XX_L4_I2C1                  0x48070000
#define   OMAP35XX_L4_I2C1_MOD                  (OMAP35XX_L4_I2C1 + 0x0)
#define   OMAP35XX_L4_I2C1_INTCT                (OMAP35XX_L4_I2C1 + 0x1000)

#define OMAP35XX_L4_I2C2                  0x48072000
#define   OMAP35XX_L4_I2C2_MOD                  (OMAP35XX_L4_I2C2 + 0x0)
#define   OMAP35XX_L4_I2C2_INTCT                (OMAP35XX_L4_I2C2 + 0x1000)

#define OMAP35XX_L4_MCBSP1                0x48074000
#define   OMAP35XX_L4_MCBSP1_MOD                (OMAP35XX_L4_MCBSP1 + 0x0)
#define   OMAP35XX_L4_MCBSP1_INTCT              (OMAP35XX_L4_MCBSP1 + 0x1000)

#define OMAP35XX_L4_GPTIMER10             0x48086000
#define   OMAP35XX_L4_GPTIMER10_MOD             (OMAP35XX_L4_GPTIMER10 + 0x0)
#define   OMAP35XX_L4_GPTIMER10_INTCT           (OMAP35XX_L4_GPTIMER10 + 0x1000)

#define OMAP35XX_L4_GPTIMER11             0x48088000
#define   OMAP35XX_L4_GPTIMER11_MOD             (OMAP35XX_L4_GPTIMER11 + 0x0)
#define   OMAP35XX_L4_GPTIMER11_INTCT           (OMAP35XX_L4_GPTIMER11 + 0x1000)

#define OMAP35XX_L4_MAILBOX               0x48094000
#define   OMAP35XX_L4_MAILBOX_MOD               (OMAP35XX_L4_MAILBOX + 0x0)
#define   OMAP35XX_L4_MAILBOX_INTCT             (OMAP35XX_L4_MAILBOX + 0x1000)

#define OMAP35XX_L4_MCBSP5                0x48096000
#define   OMAP35XX_L4_MCBSP5_MOD                (OMAP35XX_L4_MCBSP5 + 0x0)
#define   OMAP35XX_L4_MCBSP5_INTCT              (OMAP35XX_L4_MCBSP5 + 0x1000)

#define OMAP35XX_L4_SPI1                  0x48098000
#define   OMAP35XX_L4_SPI1_MOD                  (OMAP35XX_L4_SPI1 + 0x0)
#define   OMAP35XX_L4_SPI1_INTCT                (OMAP35XX_L4_SPI1 + 0x1000)

#define OMAP35XX_L4_SPI2                  0x4809A000
#define   OMAP35XX_L4_SPI2_MOD                  (OMAP35XX_L4_SPI2 + 0x0)
#define   OMAP35XX_L4_SPI2_INTCT                (OMAP35XX_L4_SPI2 + 0x1000)

#define OMAP35XX_L4_MMC_SD_SDIO1          0x4809C000
#define   OMAP35XX_L4_MMC_SD_SDIO1_MOD          (OMAP35XX_L4_MMC_SD_SDIO1 + 0x0)
#define   OMAP35XX_L4_MMC_SD_SDIO1_INTCT        \
                  (OMAP35XX_L4_MMC_SD_SDIO1 + 0x1000)

#define OMAP35XX_L4_MS_PRO                0x4809E000
#define   OMAP35XX_L4_MS_PRO_MOD                (OMAP35XX_L4_MS_PRO + 0x0)
#define   OMAP35XX_L4_MS_PRO_INTCT              (OMAP35XX_L4_MS_PRO + 0x1000)

#define OMAP35XX_L4_RNG_1                 0x480A0000
#define   OMAP35XX_L4_RNG_1_MOD                 (OMAP35XX_L4_RNG_1 + 0x0)
#define   OMAP35XX_L4_RNG_1_INTCT               (OMAP35XX_L4_RNG_1 + 0x1000)

#define OMAP35XX_L4_D3D1_1                0x480A2000
#define   OMAP35XX_L4_D3D1_1_MOD                (OMAP35XX_L4_D3D1_1 + 0x0)
#define   OMAP35XX_L4_D3D1_1_INTCT              (OMAP35XX_L4_D3D1_1 + 0x1000)

#define OMAP35XX_L4_SHAM2_1               0x480A4000
#define   OMAP35XX_L4_SHAM2_1_MOD               (OMAP35XX_L4_SHAM2_1 + 0x0)
#define   OMAP35XX_L4_SHAM2_1_INTCT             (OMAP35XX_L4_SHAM2_1 + 0x1000)

#define OMAP35XX_L4_AES1_1                0x480A6000
#define   OMAP35XX_L4_AES1_1_MOD                (OMAP35XX_L4_AES1_1 + 0x0)
#define   OMAP35XX_L4_AES1_1_INTCT              (OMAP35XX_L4_AES1_1 + 0x1000)

#define OMAP35XX_L4_FPKA_1                0x480A8000
#define   OMAP35XX_L4_FPKA_1_MOD                (OMAP35XX_L4_FPKA_1 + 0x0)
#define   OMAP35XX_L4_FPKA_1_INTCT              (OMAP35XX_L4_FPKA_1 + 0x1000)

#define OMAP35XX_L4_USBHS_OTG             0x480AB000
#define   OMAP35XX_L4_USBHS_OTG_MOD             (OMAP35XX_L4_USBHS_OTG + 0x0)
#define   OMAP35XX_L4_USBHS_OTG_SYSCONFIG       (OMAP35XX_L4_USBHS_OTG + 0x404)
#define   OMAP35XX_L4_USBHS_OTG_INTCT           (OMAP35XX_L4_USBHS_OTG + 0x1000)

#define OMAP35XX_L4_MMC_SD_SDIO3          0x480AD000
#define   OMAP35XX_L4_MMC_SD_SDIO3_MOD          (OMAP35XX_L4_MMC_SD_SDIO3 + 0x0)
#define   OMAP35XX_L4_MMC_SD_SDIO3_INTCT        \
                  (OMAP35XX_L4_MMC_SD_SDIO3 + 0x1000)

#define OMAP35XX_L4_MG                    0x480B0000
#define   OMAP35XX_L4_MG_MOD                    (OMAP35XX_L4_MG + 0x0)
#define   OMAP35XX_L4_MG_INTCT                  (OMAP35XX_L4_MG + 0x1000)

#define OMAP35XX_L4_HDQ_1_WIRE            0x480B2000
#define   OMAP35XX_L4_HDQ_1_WIRE_MOD            (OMAP35XX_L4_HDQ_1_WIRE + 0x0)
#define   OMAP35XX_L4_HDQ_1_WIRE_INTCT          \
                  (OMAP35XX_L4_HDQ_1_WIRE + 0x1000)

#define OMAP35XX_L4_MMC_SD_SDIO2          0x480B4000
#define   OMAP35XX_L4_MMC_SD_SDIO2_MOD          (OMAP35XX_L4_MMC_SD_SDIO2 + 0x0)
#define   OMAP35XX_L4_MMC_SD_SDIO2_INTCT        \
                  (OMAP35XX_L4_MMC_SD_SDIO2 + 0x1000)

#define OMAP35XX_L4_ICR1                  0x480B6000
#define   OMAP35XX_L4_ICR1_MOD                  (OMAP35XX_L4_ICR + 0x0)
#define   OMAP35XX_L4_ICR1_INTCT                (OMAP35XX_L4_ICR + 0x1000)

#define OMAP35XX_L4_SPI3                  0x480B8000
#define   OMAP35XX_L4_SPI3_MOD                  (OMAP35XX_L4_SPI3 + 0x0)
#define   OMAP35XX_L4_SPI3_INTCT                (OMAP35XX_L4_SPI3 + 0x1000)

#define OMAP35XX_L4_SPI4                  0x480BA000
#define   OMAP35XX_L4_SPI4_MOD                  (OMAP35XX_L4_SPI4 + 0x0)
#define   OMAP35XX_L4_SPI4_INTCT                (OMAP35XX_L4_SPI4 + 0x1000)

#define OMAP35XX_L4_CAMERA_ISP            0x480BC000
#define   OMAP35XX_L4_CAMERA_ISP_MOD            (OMAP35XX_L4_CAMERA_ISP + 0x0)
#define   OMAP35XX_L4_CAMERA_ISP_INTCT          \
                  (OMAP35XX_L4_CAMERA_ISP + 0x1000)

#define OMAP35XX_L4_D3D2_1                0x480C1000
#define   OMAP35XX_L4_D3D2_1_MOD                (OMAP35XX_L4_D3D2_1 + 0x0)
#define   OMAP35XX_L4_D3D2_1_INTCT              (OMAP35XX_L4_D3D2_1 + 0x1000)

#define OMAP35XX_L4_SHAM1_1               0x480C3000
#define   OMAP35XX_L4_SHAM1_1_MOD               (OMAP35XX_L4_SHAM1_1 + 0x0)
#define   OMAP35XX_L4_SHAM1_1_INTCT             (OMAP35XX_L4_SHAM1_1 + 0x1000)

#define OMAP35XX_L4_AES2_1                0x480C5000
#define   OMAP35XX_L4_AES2_1_MOD                (OMAP35XX_L4_AES2_1 + 0x0)
#define   OMAP35XX_L4_AES2_1_INTCT              (OMAP35XX_L4_AES2_1 + 0x1000)

#define OMAP35XX_L4_MODEM_INTC            0x480C7000
#define   OMAP35XX_L4_MODEM_INTC_MOD            (OMAP35XX_L4_MODEM_INTC + 0x0)
#define   OMAP35XX_L4_MODEM_INTC_INTCT          (OMAP35XX_L4_MODEM_INTC + 0x1000)

#define OMAP35XX_L4_ICR                   0x480CD000
#define   OMAP35XX_L4_ICR_MOD                   (OMAP35XX_L4_ICR + 0x0)
#define   OMAP35XX_L4_ICR_INTCT                 (OMAP35XX_L4_ICR + 0x1000)

#define OMAP35XX_L4_SGX                   0x50000000
#define   OMAP35XX_L4_SGX_MOD                   (OMAP35XX_L4_SGX + 0x0)
#define   OMAP35XX_L4_SGX_INTCT                 (OMAP35XX_L4_SGX + 0x1000)

/* Interrupt controller */

#define OMAP35XX_L4_MPU_INTC              0x48200000
#define   OMAP35XX_L4_MPU_INTC_MIR1             (OMAP35XX_L4_MPU_INTC + 0xA4)

#define OMAP35XX_L4_SSM                   0x48280000

#define OMAP35XX_L4_L4_WAKEUP_INTERCNCT   0x48300000
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUPGP12 \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x0)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP2    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x06000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP3    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x08000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP4    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x09000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP5    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x0C000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP6    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x10000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP7    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x20000)
#define   OMAP35XX_L4_L4_WAKEUP_INTERCNCT_WKUP8    \
                  (OMAP35XX_L4_L4_WAKEUP_INTERCNCT + 0x40000)

/*
 *============================================================
 * GP Timers
 *============================================================
 */

#define OMAP35XX_GPTIMER1          0x48318000
#define   OMAP35XX_GPTIMER1_TIOCP_CFG    (OMAP35XX_GPTIMER1 + 0x10)
#define   OMAP35XX_GPTIMER1_TISR         (OMAP35XX_GPTIMER1 + 0x18)
#define   OMAP35XX_GPTIMER1_TIER         (OMAP35XX_GPTIMER1 + 0x1C)
#define   OMAP35XX_GPTIMER1_TWER         (OMAP35XX_GPTIMER1 + 0x20)
#define   OMAP35XX_GPTIMER1_TCLR         (OMAP35XX_GPTIMER1 + 0x24)
#define   OMAP35XX_GPTIMER1_TLDR         (OMAP35XX_GPTIMER1 + 0x2C)
#define   OMAP35XX_GPTIMER1_TTGR         (OMAP35XX_GPTIMER1 + 0x30)
#define   OMAP35XX_GPTIMER1_TSICR        (OMAP35XX_GPTIMER1 + 0x40)

#define OMAP35XX_GPTIMER2          0x49032000
#define OMAP35XX_GPTIMER3          0x49034000
#define OMAP35XX_GPTIMER4          0x49036000
#define OMAP35XX_GPTIMER5          0x49038000
#define OMAP35XX_GPTIMER6          0x4903A000
#define OMAP35XX_GPTIMER7          0x4903C000
#define OMAP35XX_GPTIMER8          0x4903E000
#define OMAP35XX_GPTIMER9          0x49040000
#define OMAP35XX_GPTIMER10         0x48086000
#define OMAP35XX_GPTIMER11         0x48088000
#define OMAP35XX_GPTIMER12         0x48304000

/* Timer registers offset */

#define OMAP35XX_GPTIMER_TIOCP_CFG                  0x010
#define OMAP35XX_GPTIMER_TISTAT                     0x014
#define OMAP35XX_GPTIMER_TCLR                       0x024
#define OMAP35XX_GPTIMER_TCRR                       0x028
#define OMAP35XX_GPTIMER_TLDR                       0x02C
#define OMAP35XX_GPTIMER_TTGR                       0x030
#define OMAP35XX_GPTIMER_TWPS                       0x034

/* Timer registers bits offset */

#define OMAP35XX_GPTIMER_TIOCP_CFG_SOFTRESET                (0x1 << 1)
#define OMAP35XX_GPTIMER_TISTAT_RESETDONE                   (0x1 << 0)
#define OMAP35XX_GPTIMER_TCLR_ST                            (0x1 << 0)
#define OMAP35XX_GPTIMER_TCLR_AR                            (0x1 << 1)
#define OMAP35XX_GPTIMER_TCLR_TRG_SHIFT                     10

/*
 *============================================================
 * General Purpose Interface Registers
 *============================================================
 */

#define OMAP35XX_GPIO_REGISTER(base, offset) \
                 (base + offset)
#define OMAP35XX_GPIO_REGISTER_WRITE(reg, value) \
                 *(volatile UINT32*)(reg) = value
#define OMAP35XX_GPIO_REGISTER_READ(reg)  \
                 (*(volatile UINT32*)(reg))

#define OMAP35XX_GPIO1          0x48310000
#define OMAP35XX_GPIO2          0x49050000
#define OMAP35XX_GPIO3          0x49052000
#define OMAP35XX_GPIO4          0x49054000
#define OMAP35XX_GPIO5          0x49056000
#define OMAP35XX_GPIO6          0x49058000

/* GPIO 1 F and I clock enable value */

#define OMAP35XX_GPIO1_FCLK_EN        0x8
#define OMAP35XX_GPIO1_ICLK_EN        0x8

/* UART 1 F and I clock enable value */

#define OMAP35XX_UART1_FCLK_EN        (0x1 << 13)
#define OMAP35XX_UART1_ICLK_EN        (0x1 << 13)

/* UART 2 F and I clock enable value */

#define OMAP35XX_UART2_FCLK_EN        (0x1 << 14)
#define OMAP35XX_UART2_ICLK_EN        (0x1 << 14)

/* UART 2 mode register */

#define OMAP35XX_UART2_MODE           0x4806c020

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

/* Register Mask Bits */

#define OMAP35XX_GPIO_SYSCONFIG_ENAWAKEUP_MASK            (0x1 << 2)

/*
 *============================================================
 * Region Allocation for L4-Per Interconnect
 *============================================================
 */

#define OMAP35XX_L4_L4_PER_CONFIG         0x49000000
#define   OMAP35XX_L4_L4_PER_CONFIG_AP       (OMAP35XX_L4_L4_PER_CONFIG + 0x0)
#define   OMAP35XX_L4_L4_PER_CONFIG_IP       \
                  (OMAP35XX_L4_L4_PER_CONFIG + 0x0800)
#define   OMAP35XX_L4_L4_PER_CONFIG_LA       \
                  (OMAP35XX_L4_L4_PER_CONFIG + 0x1000)

#define OMAP35XX_L4_UART3                 0x49020000
#define   OMAP35XX_L4_UART3_MOD                 (OMAP35XX_L4_UART3 + 0x0)
#define   OMAP35XX_L4_UART3_INTCT               (OMAP35XX_L4_UART3 + 0x1000)

#define OMAP35XX_L4_MCBSP2_AUDIO          0x49022000
#define   OMAP35XX_L4_MCBSP2_AUDIO_MOD          (OMAP35XX_L4_MCBSP2_AUDIO + 0x0)
#define   OMAP35XX_L4_MCBSP2_AUDIO_INTCT        \
                  (OMAP35XX_L4_MCBSP2_AUDIO + 0x1000)

#define OMAP35XX_L4_MCBSP3_BLUETOOTH      0x49024000
#define   OMAP35XX_L4_MCBSP3_BLUETOOTH_MOD      \
                  (OMAP35XX_L4_MCBSP3_BLUETOOTH + 0x0)
#define   OMAP35XX_L4_MCBSP3_BLUETOOTH_INTCT    \
                  (OMAP35XX_L4_MCBSP3_BLUETOOTH + 0x1000)

#define OMAP35XX_L4_MCBSP4_VOICE_DATA     0x49026000
#define   OMAP35XX_L4_MCBSP4_VOICE_DATA_MOD     \
                  (OMAP35XX_L4_MCBSP4_VOICE_DATA + 0x0)
#define   OMAP35XX_L4_MCBSP4_VOICE_DATA_INTCT   \
                  (OMAP35XX_L4_MCBSP4_VOICE_DATA + 0x1000)

#define OMAP35XX_L4_MCBSP2_SIDETONE       0x49028000
#define   OMAP35XX_L4_MCBSP2_SIDETONE_MOD       \
                  (OMAP35XX_L4_MCBSP2_SIDETONE + 0x0)
#define   OMAP35XX_L4_MCBSP2_SIDETONE_INTCT     \
                  (OMAP35XX_L4_MCBSP2_SIDETONE + 0x1000)

#define OMAP35XX_L4_MCBSP3_SIDETONE       0x4902A000
#define   OMAP35XX_L4_MCBSP3_SIDETONE_MOD       \
                  (OMAP35XX_L4_MCBSP3_SIDETONE + 0x0)
#define   OMAP35XX_L4_MCBSP3_SIDETONE_INTCT     \
                  (OMAP35XX_L4_MCBSP3_SIDETONE + 0x1000)

#define OMAP35XX_L4_WDTIMER3              0x49030000
#define   OMAP35XX_L4_WDTIMER3_MOD              (OMAP35XX_L4_WDTIMER3 + 0x0)
#define   OMAP35XX_L4_WDTIMER3_INTCT            (OMAP35XX_L4_WDTIMER3 + 0x1000)

#define OMAP35XX_L4_GPTIMER2              0x49032000
#define   OMAP35XX_L4_GPTIMER2_MOD              (OMAP35XX_L4_GPTIMER2 + 0x0)
#define   OMAP35XX_L4_GPTIMER2_INTCT            (OMAP35XX_L4_GPTIMER2 + 0x1000)

#define OMAP35XX_L4_GPTIMER3              0x49034000
#define   OMAP35XX_L4_GPTIMER3_MOD              (OMAP35XX_L4_GPTIMER3 + 0x0)
#define   OMAP35XX_L4_GPTIMER3_INTCT            (OMAP35XX_L4_GPTIMER3 + 0x1000)

#define OMAP35XX_L4_GPTIMER4              0x49036000
#define   OMAP35XX_L4_GPTIMER4_MOD              (OMAP35XX_L4_GPTIMER4 + 0x0)
#define   OMAP35XX_L4_GPTIMER4_INTCT            (OMAP35XX_L4_GPTIMER4 + 0x1000)

#define OMAP35XX_L4_GPTIMER5              0x49038000
#define   OMAP35XX_L4_GPTIMER5_MOD              (OMAP35XX_L4_GPTIMER5 + 0x0)
#define   OMAP35XX_L4_GPTIMER5_INTCT            (OMAP35XX_L4_GPTIMER5 + 0x1000)

#define OMAP35XX_L4_GPTIMER6              0x4903A000
#define   OMAP35XX_L4_GPTIMER6_MOD              (OMAP35XX_L4_GPTIMER6 + 0x0)
#define   OMAP35XX_L4_GPTIMER6_INTCT            (OMAP35XX_L4_GPTIMER6 + 0x1000)

#define OMAP35XX_L4_GPTIMER7              0x4903C000
#define   OMAP35XX_L4_GPTIMER7_MOD              (OMAP35XX_L4_GPTIMER7 + 0x0)
#define   OMAP35XX_L4_GPTIMER7_INTCT            (OMAP35XX_L4_GPTIMER7 + 0x1000)

#define OMAP35XX_L4_GPTIMER8              0x4903E000
#define   OMAP35XX_L4_GPTIMER8_MOD              (OMAP35XX_L4_GPTIMER8 + 0x0)
#define   OMAP35XX_L4_GPTIMER8_INTCT            (OMAP35XX_L4_GPTIMER8 + 0x1000)

#define OMAP35XX_L4_GPTIMER9              0x49040000
#define   OMAP35XX_L4_GPTIMER9_MOD              (OMAP35XX_L4_GPTIMER9 + 0x0)
#define   OMAP35XX_L4_GPTIMER9_INTCT            (OMAP35XX_L4_GPTIMER9 + 0x1000)

#define OMAP35XX_L4_GPIO2                 0x49050000
#define   OMAP35XX_L4_GPIO2_MOD                 (OMAP35XX_L4_GPIO2 + 0x0)
#define   OMAP35XX_L4_GPIO2_INTCT               (OMAP35XX_L4_GPIO2 + 0x1000)

#define OMAP35XX_L4_GPIO3                 0x49052000
#define   OMAP35XX_L4_GPIO3_MOD                 (OMAP35XX_L4_GPIO3 + 0x0)
#define   OMAP35XX_L4_GPIO3_INTCT               (OMAP35XX_L4_GPIO3 + 0x1000)

#define OMAP35XX_L4_GPIO4                 0x49054000
#define   OMAP35XX_L4_GPIO4_MOD                 (OMAP35XX_L4_GPIO4 + 0x0)
#define   OMAP35XX_L4_GPIO4_INTCT               (OMAP35XX_L4_GPIO4 + 0x1000)

#define OMAP35XX_L4_GPIO5                 0x49056000
#define   OMAP35XX_L4_GPIO5_MOD                 (OMAP35XX_L4_GPIO5 + 0x0)
#define   OMAP35XX_L4_GPIO5_SYSCONFIG           (OMAP35XX_L4_GPIO5 + 0x10)
#define   OMAP35XX_L4_GPIO5_IRQSTATUS1          (OMAP35XX_L4_GPIO5 + 0x18)
#define   OMAP35XX_L4_GPIO5_IRQSTATUS2          (OMAP35XX_L4_GPIO5 + 0x28)
#define   OMAP35XX_L4_GPIO5_INTCT               (OMAP35XX_L4_GPIO5 + 0x1000)

#define OMAP35XX_L4_GPIO6                 0x49058000
#define   OMAP35XX_L4_GPIO6_MOD                 (OMAP35XX_L4_GPIO6 + 0x0)
#define   OMAP35XX_L4_GPIO6_INTCT               (OMAP35XX_L4_GPIO6 + 0x1000)

/*
 *============================================================
 * Region Allocation for L4-Emu Interconnect
 *============================================================
 */

#define OMAP35XX_L4_TEST_CHIP_LEVEL_TAP   0x54004000
#define   OMAP35XX_L4_TEST_CHIP_LEVEL_TAP_MOD   \
                     (OMAP35XX_L4_TEST_CHIP_LEVEL_TAP + 0x0)
#define   OMAP35XX_L4_TEST_CHIP_LEVEL_TAP_INTCT \
                     (OMAP35XX_L4_TEST_CHIP_LEVEL_TAP + 0x1000)

#define OMAP35XX_L4_L4_EMU_CONFIG         0x54006000
#define   OMAP35XX_L4_L4_EMU_CONFIG_AP         \
                  (OMAP35XX_L4_L4_EMU_CONFIG + 0x0)
#define   OMAP35XX_L4_L4_EMU_CONFIG_IP_L4_CORE \
                  (OMAP35XX_L4_L4_EMU_CONFIG + 0x0800)
#define   OMAP35XX_L4_L4_EMU_CONFIG_LA         \
                  (OMAP35XX_L4_L4_EMU_CONFIG + 0x1000)
#define   OMAP35XX_L4_L4_EMU_CONFIG_IP_DAP     \
                  (OMAP35XX_L4_L4_EMU_CONFIG + 0x2000)

#define OMAP35XX_L4_MPU_SS                0x54010000
#define   OMAP35XX_L4_MPU_SS_MOD                (OMAP35XX_L4_MPU_SS + 0x0)
#define   OMAP35XX_L4_MPU_SS_INTCT              (OMAP35XX_L4_MPU_SS + 0x1000)

#define OMAP35XX_L4_TPIU                  0x54019000
#define   OMAP35XX_L4_TPIU_MOD                  (OMAP35XX_L4_TPIU + 0x0)
#define   OMAP35XX_L4_TPIU_INTCT                (OMAP35XX_L4_TPIU + 0x1000)

#define OMAP35XX_L4_ETB                   0x5401B000
#define   OMAP35XX_L4_ETB_MOD                   (OMAP35XX_L4_ETB + 0x0)
#define   OMAP35XX_L4_ETB_INTCT                 (OMAP35XX_L4_ETB + 0x1000)

#define OMAP35XX_L4_DAPCTL                0x5401D000
#define   OMAP35XX_L4_DAPCTL_MOD                (OMAP35XX_L4_DAPCTL + 0x0)
#define   OMAP35XX_L4_DAPCTL_INTCT              (OMAP35XX_L4_DAPCTL + 0x1000)

#define OMAP35XX_L4_SDTI                  0x5401F000
#define   OMAP35XX_L4_SDTI_INTCT                  (OMAP35XX_L4_SDTI + 0x0)
#define   OMAP35XX_L4_SDTI_CONFIG                 \
                  (OMAP35XX_L4_SDTI + 0x004E1000)
#define   OMAP35XX_L4_SDTI_WINDOW                 \
                  (OMAP35XX_L4_SDTI + 0x005E1000)

#define OMAP35XX_L4_GPTIMER12_1           0x54704000
#define   OMAP35XX_L4_GPTIMER12_1_MOD           \
                  (OMAP35XX_L4_GPTIMER12_1 + 0x0)
#define   OMAP35XX_L4_GPTIMER12_1_INTCT         \
                  (OMAP35XX_L4_GPTIMER12_1 + 0x1000)

#define OMAP35XX_L4_POWER_RST_MGR         0x54706000
#define   OMAP35XX_L4_POWER_RST_MGR_MODA        \
                  (OMAP35XX_L4_POWER_RST_MGR + 0x0)
#define   OMAP35XX_L4_POWER_RST_MGR_MODB        \
                  (OMAP35XX_L4_POWER_RST_MGR + 0x2000)
#define   OMAP35XX_L4_POWER_RST_MGR_INTCT       \
                  (OMAP35XX_L4_POWER_RST_MGR + 0x3000)

#define OMAP35XX_L4_WDTIMER1              0x5470C000
#define   OMAP35XX_L4_WDTIMER1_MOD              (OMAP35XX_L4_WDTIMER1 + 0x0)
#define   OMAP35XX_L4_WDTIMER1_INTCT            (OMAP35XX_L4_WDTIMER1 + 0x1000)

#define OMAP35XX_L4_GPIO1                 0x54710000
#define   OMAP35XX_L4_GPIO1_MOD                 (OMAP35XX_L4_GPIO1 + 0x0)
#define   OMAP35XX_L4_GPIO1_INTCT               (OMAP35XX_L4_GPIO1 + 0x1000)

#define OMAP35XX_L4_WDTIMER2              0x54714000
#define   OMAP35XX_L4_WDTIMER2_MOD              (OMAP35XX_L4_WDTIMER2 + 0x0)
#define   OMAP35XX_L4_WDTIMER2_INTCT            (OMAP35XX_L4_WDTIMER2 + 0x1000)

#define OMAP35XX_L4_GPTIMER1              0x54718000
#define   OMAP35XX_L4_GPTIMER1_MOD              (OMAP35XX_L4_GPTIMER1 + 0x0)
#define   OMAP35XX_L4_GPTIMER1_INTCT            (OMAP35XX_L4_GPTIMER1 + 0x1000)

#define OMAP35XX_L4_32KTIMER              0x54720000
#define   OMAP35XX_L4_32KTIMER_MOD              (OMAP35XX_L4_32KTIMER + 0x0)
#define   OMAP35XX_L4_32KTIMER_INTCT            (OMAP35XX_L4_32KTIMER + 0x1000)

#define OMAP35XX_L4_L4_WAKEUP_CONFIG      0x54728000
#define   OMAP35XX_L4_L4_WAKEUP_CONFIG_AP      \
                  (OMAP35XX_L4_L4_WAKEUP_CONFIG + 0x0)
#define   OMAP35XX_L4_L4_WAKEUP_CONFIG_IP_CORE \
                  (OMAP35XX_L4_L4_WAKEUP_CONFIG + 0x0800)
#define   OMAP35XX_L4_L4_WAKEUP_CONFIG_LA      \
                  (OMAP35XX_L4_L4_WAKEUP_CONFIG + 0x1000)
#define   OMAP35XX_L4_L4_WAKEUP_CONFIG_IP_EMU  \
                  (OMAP35XX_L4_L4_WAKEUP_CONFIG + 0x2000)

#define OMAP35XX_L4_L4_WAKEUP             0x54730000
#define   OMAP35XX_L4_L4_WAKEUP_INTCT           (OMAP35XX_L4_L4_WAKEUP + 0x0)

/* Functional Registers */

/* Static Device Configuration */

#define OMAP35XX_CONTROL_DEVCONF0     (OMAP35XX_L4_SYSCTRL_MOD + 0x274)
#define OMAP35XX_CONTROL_DEVCONF1     (OMAP35XX_L4_SYSCTRL_MOD + 0x2D8)

/* Control CSIRXFE Register */

#define OMAP35XX_CONTROL_CSIRXFE      (OMAP35XX_L4_SYSCTRL_MOD + 0x2DC)

/* MSuspendMux Control Registers */

#define OMAP35XX_CONTROL_MSUSPENDMUX_0 (OMAP35XX_L4_SYSCTRL_MOD + 0x290)
#define OMAP35XX_CONTROL_MSUSPENDMUX_1 (OMAP35XX_L4_SYSCTRL_MOD + 0x294)
#define OMAP35XX_CONTROL_MSUSPENDMUX_2 (OMAP35XX_L4_SYSCTRL_MOD + 0x298)
#define OMAP35XX_CONTROL_MSUSPENDMUX_3 (OMAP35XX_L4_SYSCTRL_MOD + 0x29C)
#define OMAP35XX_CONTROL_MSUSPENDMUX_4 (OMAP35XX_L4_SYSCTRL_MOD + 0x2A0)
#define OMAP35XX_CONTROL_MSUSPENDMUX_5 (OMAP35XX_L4_SYSCTRL_MOD + 0x2A4)

/* IVA2.2 Boot Registers */

#define OMAP35XX_CONTROL_IVA2_BOOTADDR (OMAP35XX_L4_SYSCTRL_MOD + 0x400)
#define OMAP35XX_CONTROL_IVA2_BOOTMOD  (OMAP35XX_L4_SYSCTRL_MOD + 0x404)

/* PBIAS Control Register */

#define OMAP35XX_CONTROL_PBIAS_LITE    (OMAP35XX_L4_SYSCTRL_MOD + 0x520)

/* SRAMLDO Control Register */

#define OMAP35XX_CONTROL_SRAMLDO4      (OMAP35XX_L4_SYSCTRL_MOD + 0x528)
#define OMAP35XX_CONTROL_SRAMLDO5      (OMAP35XX_L4_SYSCTRL_MOD + 0x52C)

/* CSI Receiver Control Register */

#define OMAP35XX_CONTROL_CSI           (OMAP35XX_L4_SYSCTRL_MOD + 0x530)

/* Security Control Registers */

#define OMAP35XX_CONTROL_SEC_CTRL      (OMAP35XX_L4_SYSCTRL_MOD + 0x2B0)
#define OMAP35XX_CONTROL_SEC_EMU       (OMAP35XX_L4_SYSCTRL_MOD + 0xA64)
#define OMAP35XX_CONTROL_SEC_TAP       (OMAP35XX_L4_SYSCTRL_MOD + 0xA60)
#define OMAP35XX_CONTROL_SEC_DAP       (OMAP35XX_L4_SYSCTRL_MOD + 0xA7C)

/* Security Status Registers */

#define OMAP35XX_CONTROL_SEC_STATUS          (OMAP35XX_L4_SYSCTRL_MOD + 0x2E0)
#define OMAP35XX_CONTROL_SEC_ERR_STATUS      (OMAP35XX_L4_SYSCTRL_MOD + 0x2E4)
#define OMAP35XX_CONTROL_SEC_ERR_STATUS_DEBU (OMAP35XX_L4_SYSCTRL_MOD + 0x2E8)

/* Device Status Registers */

#define OMAP35XX_CONTROL_STATUS              (OMAP35XX_L4_SYSCTRL_MOD + 0x2F0)
#define OMAP35XX_CONTROL_GENERAL_PURPOSE_STA (OMAP35XX_L4_SYSCTRL_MOD + 0x2F4)

/* Secure SDRC Registers */

#define OMAP35XX_CONTROL_SECURE_SDRC_SHARING (OMAP35XX_L4_SYSCTRL_MOD + 0x460)
#define OMAP35XX_CONTROL_SECURE_SDRC_MCFG0   (OMAP35XX_L4_SYSCTRL_MOD + 0x464)
#define OMAP35XX_CONTROL_SECURE_SDRC_MCFG1   (OMAP35XX_L4_SYSCTRL_MOD + 0x468)

/* OCMROM Secure Debug Register */

#define OMAP35XX_CONTROL_OCMROM_SECURE_DEBUG (OMAP35XX_L4_SYSCTRL_MOD + 0x4C0)

/* Firewall Configuration Lock Register */

#define OMAP35XX_CONTROL_MODEM_FW_CONFIGURATION_LOCK \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x46C)

/* GPMC Boot Code Register */

#define OMAP35XX_CONTROL_MODEM_GPMC_BOOT_CODE (OMAP35XX_L4_SYSCTRL_MOD + 0x480)

/* Modem Memory Resources Configuration Register */

#define OMAP35XX_CONTROL_MODEM_MEMORY_RESOURCES_CONF \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x470)

/* GPMC Modem Firewall Registers */

#define OMAP35XX_CONTROL_MODEM_GPMC_DT_FW_REQ_INFO \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x474)
#define OMAP35XX_CONTROL_MODEM_GPMC_DT_FW_RD       \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x478)
#define OMAP35XX_CONTROL_MODEM_GPMC_DT_FW_WR       \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x47C)

/* SMS Modem Firewall Registers */

#define OMAP35XX_CONTROL_MODEM_SMS_RG_ATT1           \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x484)
#define OMAP35XX_CONTROL_MODEM_SMS_RG_RDPERM1        \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x488)
#define OMAP35XX_CONTROL_MODEM_SMS_RG_SMS_RG_WRPERM1 \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x48C)

/* D2D Firewall Stacked Device Security Registers */

#define OMAP35XX_CONTROL_D2D_FW_STACKED_DEVICE_SECURITY  \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4D8)
#define OMAP35XX_CONTROL_D2D_FW_STACKED_DEVICE_SEC_DEBUG \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4C4)

/* Modem D2D Firewall Stacked Device Debug Mode Register */

#define OMAP35XX_CONTROL_MODEM_D2D_FW_DEBUG_MODE \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x490)

/* APE Firewall Default Secure Lock Register */

#define OMAP35XX_CONTROL_APE_FW_DEFAULT_SECURE_LOCK \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4BC)

/* External Security Control Register */

#define OMAP35XX_CONTROL_EXT_SEC_CONTROL (OMAP35XX_L4_SYSCTRL_MOD + 0x4D4)

/* Keys Access Registers */

#define OMAP35XX_CONTROL_RPUB_KEY_H (OMAP35XX_L4_SYSCTRL_MOD + 0x300)
#define OMAP35XX_CONTROL_RAND_KEY   (OMAP35XX_L4_SYSCTRL_MOD + 0x318)
#define OMAP35XX_CONTROL_CUST_KEY   (OMAP35XX_L4_SYSCTRL_MOD + 0x328)
#define OMAP35XX_CONTROL_USB_CONF   (OMAP35XX_L4_SYSCTRL_MOD + 0x370)
#define OMAP35XX_CONTROL_FUSE_OPP   (OMAP35XX_L4_SYSCTRL_MOD + 0x380)

/* Memory DFT Read/Write Control Registers */

#define OMAP35XX_CONTROL_MEM_DFTRW0 (OMAP35XX_L4_SYSCTRL_MOD + 0x278)
#define OMAP35XX_CONTROL_MEM_DFTRW1 (OMAP35XX_L4_SYSCTRL_MOD + 0x27C)

/* Control DPF Region Registers */

#define OMAP35XX_CONTROL_DPF_OCM_RAM_FW_ADDR_MATCH      \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x498)
#define OMAP35XX_CONTROL_DPF_OCM_RAM_FW_REQINFO         \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x49C)
#define OMAP35XX_CONTROL_DPF_OCM_RAM_FW_WR              \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4A0)
#define OMAP35XX_CONTROL_DPF_REGION4_GPMC_FW_ADDR_MATCH \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4A4)
#define OMAP35XX_CONTROL_DPF_REGION4_GPMC_FW_REQINFO    \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4A8)
#define OMAP35XX_CONTROL_DPF_REGION4_GPMC_FW_WR         \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4AC)
#define OMAP35XX_CONTROL_DPF_REGION1_IVA2_FW_ADDR_MATCH \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4B0)
#define OMAP35XX_CONTROL_DPF_REGION1_IVA2_FW_REQINFO    \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4B4)
#define OMAP35XX_CONTROL_DPF_REGION1_IVA2_FW_WR         \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x4B8)
#define OMAP35XX_CONTROL_DPF_MAD2D_FW_ADDR_MATCH        \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x538)
#define OMAP35XX_CONTROL_DPF_MAD2D_FW_REQINFO           \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x53C)
#define OMAP35XX_CONTROL_DPF_MAD2D_FW_WR                \
                  (OMAP35XX_L4_SYSCTRL_MOD + 0x540)

/* Observability Registers */

#define OMAP35XX_CONTROL_DEBOBS_0      (OMAP35XX_L4_SYSCTRL_MOD + 0x420)
#define OMAP35XX_CONTROL_DEBOBS_1      (OMAP35XX_L4_SYSCTRL_MOD + 0x424)
#define OMAP35XX_CONTROL_DEBOBS_2      (OMAP35XX_L4_SYSCTRL_MOD + 0x428)
#define OMAP35XX_CONTROL_DEBOBS_3      (OMAP35XX_L4_SYSCTRL_MOD + 0x42C)
#define OMAP35XX_CONTROL_DEBOBS_4      (OMAP35XX_L4_SYSCTRL_MOD + 0x430)
#define OMAP35XX_CONTROL_DEBOBS_5      (OMAP35XX_L4_SYSCTRL_MOD + 0x434)
#define OMAP35XX_CONTROL_DEBOBS_6      (OMAP35XX_L4_SYSCTRL_MOD + 0x438)
#define OMAP35XX_CONTROL_DEBOBS_7      (OMAP35XX_L4_SYSCTRL_MOD + 0x43C)
#define OMAP35XX_CONTROL_DEBOBS_8      (OMAP35XX_L4_SYSCTRL_MOD + 0x440)
#define OMAP35XX_CONTROL_WKUP_DEBOBS_0 (OMAP35XX_L4_SYSCTRL_MOD + 0xA68)
#define OMAP35XX_CONTROL_WKUP_DEBOBS_1 (OMAP35XX_L4_SYSCTRL_MOD + 0xA6C)
#define OMAP35XX_CONTROL_WKUP_DEBOBS_2 (OMAP35XX_L4_SYSCTRL_MOD + 0xA70)
#define OMAP35XX_CONTROL_WKUP_DEBOBS_3 (OMAP35XX_L4_SYSCTRL_MOD + 0xA74)
#define OMAP35XX_CONTROL_WKUP_DEBOBS_4 (OMAP35XX_L4_SYSCTRL_MOD + 0xA78)

/* Modules interface clock register */

#define OMAP35XX_CLOCK_MANAGER_FCLKEN_WKUP                    (OMAP35XX_L4_CLOCK_MANAGER + 0xC00)

/* CM_FCLKEN_WKUP register bits offset */

#define OMAP35XX_CLOCK_MANAGER_FCLKEN_WKUP_EN_GPIO1_OFFSET    3
#define OMAP35XX_CLOCK_MANAGER_FCLKEN_WKUP_EN_SR1_OFFSET      6
#define OMAP35XX_CLOCK_MANAGER_FCLKEN_WKUP_EN_SR2_OFFSET      7

/* Modules interface clock register */

#define OMAP35XX_CLOCK_MANAGER_ICLKEN_WKUP                    (OMAP35XX_L4_CLOCK_MANAGER + 0xC10)

/* CM_ICLKEN_WKUP register bits offset */

#define OMAP35XX_CLOCK_MANAGER_ICLKEN_WKUP_EN_GPIO1_OFFSET    3

/*
 *============================================================
 *                 Exception Vectors
 *============================================================
 */

#define OMAP_EXCEPTION_VECTOR_ROM_PHYS_ADDR1    0x00014000
#define OMAP_EXCEPTION_VECTOR_RAM_PHYS_ADDR1    0x80200000
#define OMAP_EXCEPTION_VECTOR_VIRT_ADDR1        0x00014000
#define OMAP_EXCEPTION_VECTOR_ALIAS_VIRT_ADDR1  0x00000000

#define OMAP_EXCEPTION_VECTOR_PHYS_ADDR2        0x4020f000
#define OMAP_EXCEPTION_VECTOR_VIRT_ADDR2        0x4020f000
#define OMAP_EXCEPTION_VECTOR_SIZE              SZ_4K

/*
 *============================================================
 *                 Devices
 *============================================================
 */

#define OMAP_SDRC_NCS0      0x80000000
#define OMAP_SDRC_NCS0_END  0x87ffffff
#define OMAP_SDRC_NCS0_SIZE SZ_128M

#define OMAP_GPMC_CS0       0x20000000
#define OMAP_GPMC_CS0_END   0x27ffffff
#define OMAP_GPMC_CS0_SIZE  SZ_128M

#define OMAP_GPMC_CS1       0x08000000
#define OMAP_GPMC_CS1_END   0x0fffffff
#define OMAP_GPMC_CS1_SIZE  SZ_128M

#define OMAP_GPMC_CS3       0x18000000
#define OMAP_GPMC_CS3_END   0x1fffffff
#define OMAP_GPMC_CS3_SIZE  SZ_128M

#define OMAP_GPMC_CS4       0x28000000
#define OMAP_GPMC_CS4_END   0x28ffffff
#define OMAP_GPMC_CS4_SIZE  SZ_128M

#define OMAP_GPMC_CS5       0x2c000000
#define OMAP_GPMC_CS5_END   0x2c0003ff
#define OMAP_GPMC_CS5_SIZE  1024

#define OMAP_GPMC_CS6       0x1c000000
#define OMAP_GPMC_CS6_END   0x1fffffff
#define OMAP_GPMC_CS6_SIZE  SZ_64M

#define OMAP_GPMC_CS7       0x38000000
#define OMAP_GPMC_CS7_END   0x3fffffff
#define OMAP_GPMC_CS7_SIZE  SZ_128M

#define OMAP_UART_1         0x4806a000
#define OMAP_UART_1_END     0x4806afff
#define OMAP_UART_1_SIZE    SZ_4K

#define OMAP_UART_2         0x4806c000
#define OMAP_UART_2_END     0x4806cfff
#define OMAP_UART_2_SIZE    SZ_4K

#define OMAP_UART_3         0x49020000
#define OMAP_UART_3_END     0x49020fff
#define OMAP_UART_3_SIZE    SZ_4K

#define OMAP_I2C_1          0x48070000
#define OMAP_I2C_1_END      0x48070fff
#define OMAP_I2C_1_SIZE     SZ_4K

#define OMAP_I2C_2          0x48072000
#define OMAP_I2C_2_END      0x48072fff
#define OMAP_I2C_2_SIZE     SZ_4K

#define OMAP_I2C_3          0x48060000
#define OMAP_I2C_3_END      0x48060fff
#define OMAP_I2C_3_SIZE     SZ_4K

#define OMAP_SPI_1          0x48098000
#define OMAP_SPI_1_END      0x480980ff
#define OMAP_SPI_1_SIZE     256

#define OMAP_SPI_2          0x4809a000
#define OMAP_SPI_2_END      0x4809a0ff
#define OMAP_SPI_2_SIZE     256

#define OMAP_SPI_3          0x480b8000
#define OMAP_SPI_3_END      0x480b80ff
#define OMAP_SPI_3_SIZE     256

#define OMAP_MMC1           0x4809c000
#define OMAP_MMC1_END       0x4809cfff
#define OMAP_MMC1_SIZE      SZ_4K

#define OMAP_MMC2           0x480b4000
#define OMAP_MMC2_END       0x480b4fff
#define OMAP_MMC2_SIZE      SZ_4K

#define OMAP_GPMC           0x6e000000
#define OMAP_GPMC_END       0x6effffff
#define OMAP_GPMC_SIZE      SZ_16M

#define OMAP_FLASH          OMAP_GPMC_CS0
#define OMAP_FLASH_END      OMAP_GPMC_CS0_END
#define OMAP_FLASH_SIZE     OMAP_GPMC_CS0_SIZE

#define OMAP_LAN9115        OMAP_GPMC_CS1
#define OMAP_LAN9115_END    OMAP_GPMC_CS1_END
#define OMAP_LAN9115_SIZE   OMAP_GPMC_CS1_SIZE

#define OMAP_USB_ISP1760        OMAP_GPMC_CS6
#define OMAP_USB_ISP1760_END    OMAP_GPMC_CS6_END
#define OMAP_USB_ISP1760_SIZE   OMAP_GPMC_CS6_SIZE

/*
 *============================================================
 * GPIO pin configuration
 *============================================================
 */

#define OMAP35XX_GPIO_LAN9115_IRQ_PHYS_PIN  152   /* GPIO 5, BIT 24 */
#define OMAP35XX_GPIO_LAN9115_IRQ_BANK        5
#define OMAP35XX_GPIO_LAN9115_IRQ_BIT        24
#define OMAP35XX_GPIO_LAN9115_IRQ_MASK      (0x1 << 24)

#define OMAP35XX_GPIO_LCD_ENVDD_PIN           153   /* GPIO 5, BIT 25 */
#define OMAP35XX_GPIO_LCD_ENVDD_BANK          5
#define OMAP35XX_GPIO_LCD_ENVDD_BIT           25
#define OMAP35XX_GPIO_LCD_ENVDD_MASK          (0x1 << 25)

/*
 *============================================================
 * GPMC configuration
 *============================================================
 */
#define OMAP35XX_GPMC_REGISTER_WRITE(reg, value) \
                 *(volatile UINT32*)(reg) = value
#define OMAP35XX_GPMC_REGISTER_READ(reg)  \
                 (*(volatile UINT32*)(reg))
#define OMAP_GPMC_CONFIG1           0x60
#define OMAP_GPMC_CONFIG2           0x64
#define OMAP_GPMC_CONFIG3           0x68
#define OMAP_GPMC_CONFIG4           0x6C
#define OMAP_GPMC_CONFIG5           0x70
#define OMAP_GPMC_CONFIG6           0x74
#define OMAP_GPMC_CONFIG7           0x78

#define OMAP_GPMC_CONFIG_CS_OFFSET 0x30
#define OMAP_GPMC_CONFIG1_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG1 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG2_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG2 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG3_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG3 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG4_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG4 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG5_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG5 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG6_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG6 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)
#define OMAP_GPMC_CONFIG7_CS_ADDR(cs) \
	(OMAP_GPMC + OMAP_GPMC_CONFIG7 + cs*OMAP_GPMC_CONFIG_CS_OFFSET)

#define OMAP_GPMC_NAND_CS         0x0
#define OMAP_GPMC_LAN_CS          0x1
#define OMAP_GPMC_NOR_CS          0x2
#define OMAP_GPMC_CF_CS           0x3
#define OMAP_GPMC_CSA_CS          0x4
#define OMAP_GPMC_CSB_CS          0x5
#define OMAP_GPMC_USB_CS          0x6

#define OMAP_GPMC_LAN_CONFIG1  0x00001000
#define OMAP_GPMC_LAN_CONFIG2  0x00080701
#define OMAP_GPMC_LAN_CONFIG3  0x00000000
#define OMAP_GPMC_LAN_CONFIG4  0x08010702
#define OMAP_GPMC_LAN_CONFIG5  0x00080a0a
#define OMAP_GPMC_LAN_CONFIG6  0x03000280
#define OMAP_GPMC_LAN_CONFIG7  0x00000f48

#define OMAP_GPMC_NAND_CONFIG1 0x00001800
#define OMAP_GPMC_NAND_CONFIG2 0x00070700
#define OMAP_GPMC_NAND_CONFIG3 0x00070700
#define OMAP_GPMC_NAND_CONFIG4 0x05000500
#define OMAP_GPMC_NAND_CONFIG5 0x00060707
#define OMAP_GPMC_NAND_CONFIG6 0x000002CF
#define OMAP_GPMC_NAND_CONFIG7 0x00000860

#define OMAP_GPMC_ISP1760_CONFIG1 0x00001200
#define OMAP_GPMC_ISP1760_CONFIG2 0x00090901
#define OMAP_GPMC_ISP1760_CONFIG3 0x00091001
#define OMAP_GPMC_ISP1760_CONFIG4 0x07031002
#define OMAP_GPMC_ISP1760_CONFIG5 0x00080C0A
#define OMAP_GPMC_ISP1760_CONFIG6 0x08030200
#define OMAP_GPMC_ISP1760_CONFIG7 0x00000F5C

#define OMAP_GPMC_SYSCONFIG                  (OMAP_GPMC + 0x00000010)
#define OMAP_GPMC_SYSSTATUS                  (OMAP_GPMC + 0x00000014)
#define OMAP_GPMC_IRQENABLE                  (OMAP_GPMC + 0x0000001C)
#define OMAP_GPMC_TIMEOUT_CONTROL            (OMAP_GPMC + 0x00000040)
#define OMAP_GPMC_CONFIG_REG                 (OMAP_GPMC + 0x00000050)

#define OMAP_GPMC_SYSCONFIG_VAL               0x00000010
#define OMAP_GPMC_IRQSTATUS_VAL               0x00000000
#define OMAP_GPMC_IRQENABLE_VAL               0x00000000
#define OMAP_GPMC_TIMEOUT_CONTROL_VAL         0x00000000
#define OMAP_GPMC_CONFIG_VAL                  0x00000000

#define OMAP35XX_REGISTER_WRITE(reg, value) \
                 *(volatile UINT32*)(reg) = value
#define OMAP35XX_REGISTER_READ(reg)  \
                 (*(volatile UINT32*)(reg))
/*
 *============================================================
 * Watchdog Timer (WDT) Registers
 *============================================================
 */

#define OMAP35XX_WDTIMER1          0x4830C000
#define OMAP35XX_WDTIMER2          0x48314000
#define OMAP35XX_WDTIMER3          0x49030000

#define OMAP35XX_WDTIMER_WSPR      0x48
#define OMAP35XX_WDTIMER_WWPS      0x34
#define OMAP35XX_WDTIMER_DIS_1     0xAAAAAAAA
#define OMAP35XX_WDTIMER_DIS_2     0x55555555
#define OMAP35XX_WDTIMER_EN_1      0xBBBBBBBB
#define OMAP35XX_WDTIMER_EN_2      0x44444444
#define OMAP35XX_WDTIMER_PEND_WSPR	(1<<4)
#define OMAP35XX_WDTIMER_PEND_WTGR	(1<<3)
#define OMAP35XX_WDTIMER_PEND_WLDR	(1<<2)
#define OMAP35XX_WDTIMER_PEND_WCRR	(1<<1)
#define OMAP35XX_WDTIMER_PEND_WCLR	(1<<0)

#define OMAP35XX_GPT               0x48320010
#define OMAP35XX_GPT_32K		0x48320000

/*
 *============================================================
 * SDRAM Registers
 *============================================================
 */

#define OMAP35XX_SDRC                   0x6D000000
#define OMAP35XX_SDRC_SYSCONFIG         0x6D000010
#define OMAP35XX_SDRC_SYSSTATUS         0x6D000014
#define OMAP35XX_SDRC_CS_CFG            0x6D000040
#define OMAP35XX_SDRC_SHARING           0x6D000044
#define OMAP35XX_SDRC_ERR_ADDR          0x6D000048
#define OMAP35XX_SDRC_ERR_TYPE          0x6D00004C
#define OMAP35XX_SDRC_DLLA_CTRL         0x6D000060
#define OMAP35XX_SDRC_DLLA_STATUS       0x6D000064
#define OMAP35XX_SDRC_POWER_REG         0x6D000070
#define OMAP35XX_SDRC_MCFG_0            0x6D000080
#define OMAP35XX_SDRC_MR_0              0x6D000084
#define OMAP35XX_SDRC_EMR2_0            0x6D00008C
#define OMAP35XX_SDRC_ACTIM_CTRLA_0     0x6D00009C
#define OMAP35XX_SDRC_ACTIM_CTRLB_0     0x6D0000A0
#define OMAP35XX_SDRC_RFR_CTRL_0        0x6D0000A4
#define OMAP35XX_SDRC_MANUAL_0          0x6D0000A8
#define OMAP35XX_SDRC_MCFG_1            0x6D0000B0
#define OMAP35XX_SDRC_MR_1              0x6D0000B4
#define OMAP35XX_SDRC_EMR2_1            0x6D0000BC
#define OMAP35XX_SDRC_ACTIM_CTRLA_1     0x6D0000CC
#define OMAP35XX_SDRC_ACTIM_CTRLB_1     0x6D0000D0
#define OMAP35XX_SDRC_RFR_CTRL_1        0x6D0000D4
#define OMAP35XX_SDRC_MANUAL_1          0x6D0000D8

#define OMAP35XX_SDRC_SOFTRESET         0x11
#define OMAP35XX_SDRC_NORESET           0x10
#define OMAP35XX_SDRC_RESETDONE         0x1
#define OMAP35XX_SDRC_SHARING_VAL       0x100
#define OMAP35XX_SDRC_MCFG_0_VAL        0x02584099
#define OMAP35XX_SDRC_ACTIM_CTRLA_0_VAL 0xAA9DB4C6
#define OMAP35XX_SDRC_ACTIM_CTRLB_0_VAL 0x00011517
#define OMAP35XX_SDRC_RFR_CTRL_0_VAL    0x0003C701

#define OMAP35XX_SDRC_NOP_CMD           0x0
#define OMAP35XX_SDRC_PRECHARGE_CMD     0x0
#define OMAP35XX_SDRC_AUTOREFRESH_CMD   0x0

#define OMAP35XX_SDRC_MR_0_VAL          0x32
#define OMAP35XX_SDRC_DLLA_CTRL_VAL     0xA

/*
 *============================================================
 * MMCHS registers
 *============================================================
 */

#define OMAP35XX_MMC1_BASE          0x4809c000

#define   OMAP35XX_MMC1_CAPA                   (OMAP35XX_MMC1_BASE + 0x140)

/* Register Mask Bits */

#define OMAP35XX_CAPA_VS30_MASK                (0x1 << 25)
#define OMAP35XX_CAPA_VS18_MASK                (0x1 << 26)

/*
 *============================================================
 * USB registers
 *============================================================
 */

#define OMAP35XX_USBHS_UHH_BASE     0x48064000
#define OMAP35XX_USBHS_UHH_SYSCONFIG           (OMAP35XX_USBHS_UHH_BASE + 0x10)
#define OMAP35XX_USBHS_UHH_SYSSTATUS           (OMAP35XX_USBHS_UHH_BASE + 0x14)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG          (OMAP35XX_USBHS_UHH_BASE + 0x40)

#define OMAP35XX_USBHS_USBTLL       0x48062000
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG        (OMAP35XX_USBHS_USBTLL + 0x10)
#define OMAP35XX_USBHS_USBTLL_SYSSTATUS        (OMAP35XX_USBHS_USBTLL + 0x14)

/* Register Mask Bits */

#define OMAP35XX_USBHS_UHH_SYSCONFIG_AUTOIDLE_MASK           (0x1 << 0)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_SOFTRESET_MASK          (0x1 << 1)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_ENAWAKEUP_MASK          (0x1 << 2)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_SIDLEMASK               (0x2)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_SIDLEMASK_SHIFT         (3)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_SIDLEMASK_MASK          (0x3 << 3)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_CLOCKACTIVITY_MASK      (0x1 << 8)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_MIDLEMODE               (0x2)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_MIDLEMODE_SHIFT         (12)
#define OMAP35XX_USBHS_UHH_SYSCONFIG_MIDLEMODE_MASK          (0x3 << 12)

#define OMAP35XX_USBHS_UHH_SYSSTATUS_RESETDONE               (0x1 << 0)

#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ULPI_BYPASS_SHIFT      (0)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ULPI_BYPASS_MASK       (0x1 << 0)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ENA_INCR4_MASK         (0x1 << 2)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ENA_INCR8_MASK         (0x1 << 3)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ENA_INCR16_MASK        (0x1 << 4)
#define OMAP35XX_USBHS_UHH_HOSTCONFIG_ENA_INCR_ALIGN         (0x1 << 5)

#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_AUTOIDLE_MASK        (0x1 << 0)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_SOFTRESET_MASK       (0x1 << 1)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_ENAWAKEUP_MASK       (0x1 << 2)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_SIDLEMODE            (0x2)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_SIDLEMODE_SHIFT      (3)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_SIDLEMODE_MASK       (0x3 << 3)
#define OMAP35XX_USBHS_USBTLL_SYSCONFIG_CLOCKACTIVITY_MASK   (0x1 << 8)

#define OMAP35XX_USBHS_USBTLL_SYSSTATUS_RESETDONE            (0x1 << 0)

/*
 *============================================================
 * System Control Module configuration
 *============================================================
 */

#define OMAP_PADCONF_GPMC_BASE			0x48002030
#define OMAP_PADCONF_GPMC_NADV_ALE      OMAP_PADCONF_GPMC_BASE + 0x90
#define OMAP_PADCONF_GPMC_NWE           OMAP_PADCONF_GPMC_BASE + 0x9C
#define OMAP_PADCONF_MCBSP4_CLKX		OMAP_PADCONF_GPMC_BASE + 0x154
#define OMAP_PADCONF_UART1_TX           OMAP_PADCONF_GPMC_BASE + 0x14C
#define OMAP_PADCONF_UART1_CTS          OMAP_PADCONF_GPMC_BASE + 0x150
#define OMAP_PADCONF_GPMC_NCS1           OMAP_PADCONF_GPMC_BASE + 0x80

#define OMAP_PADCONF_GPIO_30             0x4800215C
#define OMAP_PADCONF_GPIO_30_IN          0x00040000

/*Off mode enabled*/
#define OMAP_GPMC_NOE					0x0E000000
#define OMAP_GPMC_NADV_ALE				0x0E00
#define OMAP_GPMC_NWE					0x0E00
#define OMAP_GPIO_152_LAN_INT   		0x00000114
#define OMPA_CM_MASK_LOW				0xFFFF0000
#define OMPA_CM_MASK_HIGH				0x0000FFFF
#define OMAP_GPMC_NCS1_EN               0x01180000
#define OMAP_GPMC_A_H                   0x00000000
#define OMAP_GPMC_A_L                   0x00000000
#define OMAP_GPMC_D_H                   0x01000000
#define OMAP_GPMC_D_L                   0x00000100

/* Pin mux bits */

#define OMAP_GPMC_MUX_MASK                 (0x7 << 0)
#define OMAP_GPMC_MUX_MODE0                (0x0 << 0)
#define OMAP_GPMC_MUX_MODE3                (0x3 << 0)
#define OMAP_GPMC_MUX_MODE4                (0x4 << 0)
#define OMAP_GPMC_PULL_ENA                 (0x1 << 3)
#define OMAP_GPMC_PULL_SEL_ENA             (0x1 << 4)
#define OMAP_GPMC_INPUT_EN                 (0x1 << 8)
#define OMAP_GPMC_PIN_INPUT_PULLDOWN       (OMAP_GPMC_PULL_ENA | OMAP_GPMC_INPUT_EN)
#define OMAP_GPMC_PIN_INPUT_PULLUP         (OMAP_GPMC_PULL_ENA | OMAP_GPMC_INPUT_EN | \
                                        OMAP_GPMC_PULL_ENA)

#define OMAP_UART1_OUTPUT_PIN   		0x010F0000
#define OMAP_UART1_INPUT_PIN   		    0x0118010F
#define OMAP_UART1_SYSC_REG				(OMAP_UART_1 + 0x54)
#define OMAP_UART1_SOFTRESET			0x2
#define OMAP_UART1_SYSS_REG				(OMAP_UART_1 + 0x58)
#define OMAP_UART1_RESETDONE			0x1
#define OMAP_UART1_MDR1_REG				(OMAP_UART_1 + 0x20)
#define OMAP_UART1_DISABLE_MODE          0x7
#define OMAP_UART1_ENABLE_MODE           0x0

#define OMAP_GPIO_0                     (1<<0)
#define OMAP_GPIO_1                     (1<<1)
#define OMAP_GPIO_2                     (1<<2)
#define OMAP_GPIO_3                     (1<<3)
#define OMAP_GPIO_4                     (1<<4)
#define OMAP_GPIO_5                     (1<<5)
#define OMAP_GPIO_6                     (1<<6)
#define OMAP_GPIO_7                     (1<<7)
#define OMAP_GPIO_8                     (1<<8)
#define OMAP_GPIO_9                     (1<<9)
#define OMAP_GPIO_10                    (1<<10)
#define OMAP_GPIO_11                    (1<<11)
#define OMAP_GPIO_12                    (1<<12)
#define OMAP_GPIO_13                    (1<<13)
#define OMAP_GPIO_14                    (1<<14)
#define OMAP_GPIO_15                    (1<<15)
#define OMAP_GPIO_16                    (1<<16)
#define OMAP_GPIO_17                    (1<<17)
#define OMAP_GPIO_18                    (1<<18)
#define OMAP_GPIO_19                    (1<<19)
#define OMAP_GPIO_20                    (1<<20)
#define OMAP_GPIO_21                    (1<<21)
#define OMAP_GPIO_22                    (1<<22)
#define OMAP_GPIO_23                    (1<<23)
#define OMAP_GPIO_24                    (1<<24)
#define OMAP_GPIO_25                    (1<<25)
#define OMAP_GPIO_26                    (1<<26)
#define OMAP_GPIO_27                    (1<<27)
#define OMAP_GPIO_28                    (1<<28)
#define OMAP_GPIO_29                    (1<<29)
#define OMAP_GPIO_30                    (1<<30)
#define OMAP_GPIO_31                    (1<<31)

#define OMAP_GPIO_5_VAL (OMAP_GPIO_1|OMAP_GPIO_2|OMAP_GPIO_8|OMAP_GPIO_10|OMAP_GPIO_23)
#define OMAP_GPIO_6_VAL (OMAP_GPIO_12|OMAP_GPIO_13|OMAP_GPIO_14|OMAP_GPIO_15|OMAP_GPIO_21| \
	OMAP_GPIO_22|OMAP_GPIO_28|OMAP_GPIO_29|OMAP_GPIO_30|OMAP_GPIO_31)


#define OMAP35XX_CONTROL_PADCONF_SDRC_DQS3       0x48002078
#define OMAP35XX_CONTROL_PADCONF_GPMC_A2         0x4800207C
#define OMAP35XX_CONTROL_PADCONF_GPMC_A4         0x48002080
#define OMAP35XX_CONTROL_PADCONF_GPMC_A6         0x48002084
#define OMAP35XX_CONTROL_PADCONF_GPMC_A8         0x48002088
#define OMAP35XX_CONTROL_PADCONF_GPMC_A10        0x4800208C
#define OMAP35XX_CONTROL_PADCONF_GPMC_D1         0x48002090
#define OMAP35XX_CONTROL_PADCONF_GPMC_D3         0x48002094
#define OMAP35XX_CONTROL_PADCONF_GPMC_D5         0x48002098
#define OMAP35XX_CONTROL_PADCONF_GPMC_D7         0x4800209C
#define OMAP35XX_CONTROL_PADCONF_GPMC_D9         0x480020A0
#define OMAP35XX_CONTROL_PADCONF_GPMC_D11        0x480020A4
#define OMAP35XX_CONTROL_PADCONF_GPMC_D13        0x480020A8
#define OMAP35XX_CONTROL_PADCONF_GPMC_D15        0x480020AC
#define OMAP35XX_CONTROL_PADCONF_GPMC_NCS1       0x480020B0
#define OMAP35XX_CONTROL_PADCONF_GPMC_NCS3       0x480020B4
#define OMAP35XX_CONTROL_PADCONF_GPMC_NCS5       0x480020B8
#define OMAP35XX_CONTROL_PADCONF_GPMC_NCS5H      0x480020BA
#define OMAP35XX_CONTROL_PADCONF_GPMC_NCS7       0x480020BC
#define OMAP35XX_CONTROL_PADCONF_MMC1_CLK        0x48002144
#define OMAP35XX_CONTROL_PADCONF_MMC1_CMD        0x48002146
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT0       0x48002148
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT1       0x4800214A
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT2       0x4800214C
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT3       0x4800214E
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT4       0x48002150
#define OMAP35XX_CONTROL_PADCONF_MMC1_DAT5       0x48002152
#define OMAP35XX_PADCONF_GPMC_NADV_ALE           0x480020C0
#define OMAP35XX_PADCONF_GPMC_NWE                0x480020C4
#define OMAP35XX_PADCONF_GPMC_NWE1               0x480020C8
#define OMAP35XX_PADCONF_GPMC_WAIT0              0x480020CC
#define OMAP35XX_PADCONF_GPMC_WAIT1              0x480020D0
#define OMAP35XX_PADCONF_GPMC_PCLK               0x480020D4
#define OMAP35XX_PADCONF_GPMC_VSYNC              0x480020D8

#define OMAP35XX_PADCONF_HSUSB0_DATA7            0x480021B8
#define OMAP35XX_PADCONF_I2C1_SDA                0x480021BC
#define OMAP35XX_PADCONF_I2C2_SDA                0x480021C0
#define OMAP35XX_PADCONF_I2C3_SDA                0x480021C4

#define OMAP35XX_PADCONF_SAD2D_MSTDBY            0x48002250
#define OMAP35XX_PADCONF_SAD2D_IDLEACK           0x48002254

#define OMAP35XX_CONTROL_PADCONF_HSUSB1_CLK      0x480025DA
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_STP      0x480025D8
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DIR      0x480025EC
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_NXT      0x480025EE
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA0    0x480025DC
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA1    0x480025DE
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA2    0x480025E0
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA3    0x480025EA
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA4    0x480025E4
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA5    0x480025E6
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA6    0x480025E8
#define OMAP35XX_CONTROL_PADCONF_HSUSB1_DATA7    0x480025E2

#define OMAP35XX_I2C_SDA                         0x00000110
#define OMAP35XX_I2C_SCL                         0x01100000
#define OMAP35XX_I2C3_SDA                        0x00000100
#define OMAP35XX_I2C3_SCL_INIT                   0x00000000
#define OMAP35XX_I2C3_SCL                        0x01180000

#define N_UART_CHANNELS                       2

/*
 *============================================================
 * Register Definitions for DSP/BIOS Link support
 *============================================================
 */

#define OMAP35XX_GEN_CTRL_BASE               0x48002270
#define OMAP35XX_IVA2_CM_BASE                0x48004000
#define OMAP35XX_CORE_CM_BASE                0x48004a00
#define OMAP35XX_PER_CM_BASE                 0x48005000
#define OMAP35XX_IVA2_PRM_BASE               0x48306000
#define OMAP_IVA2PRM_SIZE                    SZ_8K
#define OMAP35XX_MAILBOX_BASE                0x48094000
#define OMAP_MAILBOX_SIZE                    SZ_4K
#define OMAP35XX_MMU_BASE                    0x5d000000

/*
 *============================================================
 * Register Definitions for Smart Reflex (just register bases)
 *============================================================
 */

/* Smart Reflex register base address definitions (TRM 4.14.3) */

#define OMAP35XX_SR1_BASE 0x480c9000
#define OMAP35XX_SR2_BASE 0x480cb000

/*
 *============================================================
 * bitfields for OMAP35XX_CM_CLKOUT_CTRL
 *============================================================
 */
 
#define OMAP35XX_SYSCLKOUT2_EN  0x80    /* 1=enable sysclk2 output (bit-7) */

/*
 *============================================================
 * CLOCK module ICLK/FCLK bit masks
 *============================================================
 */

/* CM_FCLKEN_IVA2 bit masks */

#define OMAP35xx_CM_FCLKEN_IVA2_EN_IVA2         (1 << 0)

/* CM_FCLKEN_SGX bit masks */

#define OMAP35xx_CM_FCLKEN_SGX_EN_SGX           (1 << 1)

/* CM_ICLKEN_SGX bit masks */

#define OMAP35xx_CM_ICLKEN_SGX_EN_SGX           (1 << 0)

/* CM_FCLKEN_WKUP bit masks */

#define OMAP35xx_CM_FCLKEN_WKUP_EN_GPT1         (1 << 0)
#define OMAP35xx_CM_FCLKEN_WKUP_EN_GPIO1        (1 << 3)
#define OMAP35xx_CM_FCLKEN_WKUP_EN_WDT2         (1 << 5)

/* CM_ICLKEN_WKUP bit masks */

#define OMAP35xx_CM_ILKEN_WKUP_EN_GPT1          (1 << 0)
#define OMAP35xx_CM_ILKEN_WKUP_EN_32KSYNC       (1 << 2)
#define OMAP35xx_CM_ILKEN_WKUP_EN_GPIO1         (1 << 3)
#define OMAP35xx_CM_ILKEN_WKUP_EN_WDT2          (1 << 5)

/* CM_FCLKEN_DSS bit masks */

#define OMAP35xx_CM_FCLKEN_DSS_EN_DSS1          (1 << 0)
#define OMAP35xx_CM_FCLKEN_DSS_EN_DSS2          (1 << 1)
#define OMAP35xx_CM_FCLKEN_DSS_EN_TV            (1 << 2)

/* CM_ICLKEN_DSS bit masks */

#define OMAP35xx_CM_ICLKEN_DSS_EN_DSS           (1 << 0)

/* CM_FCLKEN_CAM bit masks */

#define OMAP35xx_CM_FCLKEN_CAM_EN_CAM           (1 << 0)
#define OMAP35xx_CM_FCLKEN_CAM_EN_CSI2          (1 << 1)

/* CM_ICLKEN_CAM bit masks */

#define OMAP35xx_CM_ICLKEN_CAM_EN_CAM           (1 << 0)

/* CM_FCLKEN_USBHOST bit masks */

#define OMAP35xx_CM_FCLKEN_USBHOST_EN_USBHOST1  (1 << 0)
#define OMAP35xx_CM_FCLKEN_USBHOST_EN_USBHOST2  (1 << 1)

/* CM_ICLKEN_USBHOST bit masks */

#define OMAP35xx_CM_ICLKEN_USBHOST_EN_USBHOST   (1 << 0)

/* CM_FCLKEN1_CORE bit masks */

#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCBSP1      (1 << 9)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCBSP5      (1 << 10)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_GPT10       (1 << 11)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_GPT11       (1 << 12)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_UART1       (1 << 13)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_UART2       (1 << 14)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_I2C1        (1 << 15)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_I2C2        (1 << 16)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_I2C3        (1 << 17)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCSPI1      (1 << 18)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCSPI2      (1 << 19)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCSPI3      (1 << 20)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MCSPI4      (1 << 21)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_HDQ         (1 << 22)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MMC1        (1 << 24)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MMC2        (1 << 25)
#define OMAP35xx_CM_FCLKEN1_CORE_EN_MMC3        (1 << 30)

/* CM_FCLKEN3_CORE bit masks */

#define OMAP35xx_CM_FCLKEN3_CORE_EN_TS          (1 << 1)
#define OMAP35xx_CM_FCLKEN3_CORE_EN_USBTLL      (1 << 2)

/* CM_ICLKEN1_CORE bit masks */

#define OMAP35xx_CM_ICLKEN1_CORE_EN_SDRC        (1 << 1)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_HSOTGUSB    (1 << 4)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_OMAPCTRL    (1 << 6)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MAILBOXES   (1 << 7)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCBSP1      (1 << 9)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCBSP5      (1 << 10)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_GPT10       (1 << 11)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_GPT11       (1 << 12)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_UART1       (1 << 13)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_UART2       (1 << 14)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_I2C1        (1 << 15)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_I2C2        (1 << 16)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_I2C3        (1 << 17)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCSPI1      (1 << 18)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCSPI2      (1 << 19)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCSPI3      (1 << 20)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MCSPI4      (1 << 21)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_HDQ         (1 << 22)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MMC1        (1 << 24)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MMC2        (1 << 25)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_ICR         (1 << 29)
#define OMAP35xx_CM_ICLKEN1_CORE_EN_MMC3        (1 << 30)

/* CM_ICLKEN3_CORE bit masks */

#define OMAP35xx_CM_ICLKEN3_CORE_EN_USBTLL      (1 << 2)

/* CM_IDLEST3_CORE bit masks*/

#define OMAP35xx_CM_IDLEST3_CORE_ST_USBTLL      (1 << 2)

/* CM_FCLKEN_PER bit masks */

#define OMAP35xx_CM_FCLKEN_PER_EN_MCBSP2        (1 << 0)
#define OMAP35xx_CM_FCLKEN_PER_EN_MCBSP3        (1 << 1)
#define OMAP35xx_CM_FCLKEN_PER_EN_MCBSP4        (1 << 2)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT2          (1 << 3)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT3          (1 << 4)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT4          (1 << 5)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT5          (1 << 6)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT6          (1 << 7)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT7          (1 << 8)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT8          (1 << 9)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPT9          (1 << 10)
#define OMAP35xx_CM_FCLKEN_PER_EN_UART3         (1 << 11)
#define OMAP35xx_CM_FCLKEN_PER_EN_WDT3          (1 << 12)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPIO2         (1 << 13)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPIO3         (1 << 14)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPIO4         (1 << 15)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPIO5         (1 << 16)
#define OMAP35xx_CM_FCLKEN_PER_EN_GPIO6         (1 << 17)

/* CM_ICLKEN_PER bit masks */

#define OMAP35xx_CM_ICLKEN_PER_EN_MCBSP2        (1 << 0)
#define OMAP35xx_CM_ICLKEN_PER_EN_MCBSP3        (1 << 1)
#define OMAP35xx_CM_ICLKEN_PER_EN_MCBSP4        (1 << 2)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT2          (1 << 3)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT3          (1 << 4)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT4          (1 << 5)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT5          (1 << 6)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT6          (1 << 7)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT7          (1 << 8)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT8          (1 << 9)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPT9          (1 << 10)
#define OMAP35xx_CM_ICLKEN_PER_EN_UART3         (1 << 11)
#define OMAP35xx_CM_ICLKEN_PER_EN_WDT3          (1 << 12)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPIO2         (1 << 13)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPIO3         (1 << 14)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPIO4         (1 << 15)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPIO5         (1 << 16)
#define OMAP35xx_CM_ICLKEN_PER_EN_GPIO6         (1 << 17)


#ifdef __cplusplus
}
#endif

#endif  /* __INComaph */
