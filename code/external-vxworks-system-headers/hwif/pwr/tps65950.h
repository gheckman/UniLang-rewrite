/* tps65950.h - OMAP35x TPS65950 Companion Device header file  */

/*
 * Copyright (c) 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
                         
/*
modification history
--------------------
01d,09mar11,w_x  added VUSB dedicated bits 
01c,18feb11,w_x  added USB PHY sub-chip module registers
01b,17feb11,rdl  Add function prototypes for TPS65950 functions
01a,25jan11,bsk  created
*/

/*
DESCRIPTION
This file contains I2C addresses, internal register addresses, and bit
mask definitions for the TPS65950 OMAP35x Power Management and System 
Companion Device.             

The vxWorks power management implementation, for the Omap35x, uses the
TPS65950 registers to perform software power down of the system, making
use of the power management registers and bit masks.

I2C Bus Address:
The TPS65950 is accesses using I2C bus 0, defined as 'TPS_I2C_CONTROL_BUS'.

Registers in the I2C Address Groups:
There are 4 hard-coded I2C address groups: 0x48, 0x49, 0x4A and 0x4B, each 
allowing access to a 256-byte register address map, through which internal 
registers are accessed. The power management registers, located in address 
group #4, accessed via I2C address 0x4B (defined as 'TPS_I2C_ADDRESS_ID4')
are used by the vxWorks Omap35x power management implementation, and appear
first in this file, followed by the other address groups, in descending order.  

Bit Masks:
Bit masks are defined, as needed by the power management implementation.
Registers in the other three address groups, though not used by the power
management implementation, are included for completeness and possible future
utilization.

References:
Where page numbers are referenced, please refer to "TPS65950 OMAP Power 
Management and System Companion Device Silicon Revision 1.2 Version G".
*/

#ifndef __INCtps65950h
#define __INCtps65950h 


#ifdef __cplusplus
extern "C" {
#endif

/* 
 * The TPS65950 is accessed via I2C bus #0 
 * 
 */

#define TPS_I2C_CONTROL_BUS 0x00

/* 
 * I2C uses 4 hard-coded addresses. Each I2C address group allows 
 * access to a 256-byte register address map, through which a group 
 * of internal registers are accessed.
 */

#define TPS_I2C_ADDRESS_ID4 0x4B
#define TPS_I2C_ADDRESS_ID3 0x4A
#define TPS_I2C_ADDRESS_ID2 0x49
#define TPS_I2C_ADDRESS_ID1 0x48


/* SmartReflex I2C bus addressing uses one hard-coded address */

#define TPS_I2C_ADDRESS_ID5 0x12

/* TPS65950 TRM 2.6.1.1 Address Group - 4b Hex */

#define TPS_PM_MASTER_I2C_ADDR     TPS_I2C_ADDRESS_ID4
#define TPS_PM_RECEIVER_I2C_ADDR   TPS_I2C_ADDRESS_ID4

/* TPS65950 TRM 2.6.2 Address Group - 48 Hex */

#define TPS_PM_USBPHY_I2C_ADDR     TPS_I2C_ADDRESS_ID1

/*
 * This section is dedicated to the TPS65950
 * I2C Address group 4 (0x4B) TPS_I2C_ADDRESS_ID4 
 */

/* base addresses of the TPS modules in ADDRESS_ID4 (0x4b)*/

#define TPS_SECURED_REG_BASE 0x00000000
#define TPS_BACKUP_REG_BASE  0x00000014
#define TPS_RTC_BASE         0x0000001C
#define TPS_PWR_INT_BASE     0x0000002E   
#define TPS_PM_BASE          0x00000036

/* 
 * TPS BACKUP module
 * 8 bit R-only registers in secure active mode
 * 8 bit R/W registers in un-secure active mode * 
 */

#define TPS_SECURED_REG_A  0x00000000
#define TPS_SECURED_REG_B  0x00000001
#define TPS_SECURED_REG_C  0x00000002
#define TPS_SECURED_REG_D  0x00000003
#define TPS_SECURED_REG_E  0x00000004
#define TPS_SECURED_REG_F  0x00000005
#define TPS_SECURED_REG_G  0x00000006
#define TPS_SECURED_REG_H  0x00000007
#define TPS_SECURED_REG_I  0x00000008
#define TPS_SECURED_REG_J  0x00000009
#define TPS_SECURED_REG_K  0x0000000A
#define TPS_SECURED_REG_L  0x0000000B
#define TPS_SECURED_REG_M  0x0000000C
#define TPS_SECURED_REG_N  0x0000000D
#define TPS_SECURED_REG_O  0x0000000E
#define TPS_SECURED_REG_P  0x0000000F
#define TPS_SECURED_REG_Q  0x00000010
#define TPS_SECURED_REG_R  0x00000011
#define TPS_SECURED_REG_S  0x00000012
#define TPS_SECURED_REG_U  0x00000013

/* 
 * TPS BACKUP module
 * 8 bit R/W registers 
 */

#define TPS_BACKUP_REG_A    0x00000014
#define TPS_BACKUP_REG_B    0x00000015
#define TPS_BACKUP_REG_C    0x00000016
#define TPS_BACKUP_REG_D    0x00000017
#define TPS_BACKUP_REG_E    0x00000018
#define TPS_BACKUP_REG_F    0x00000019
#define TPS_BACKUP_REG_G    0x0000001A
#define TPS_BACKUP_REG_H    0x0000001B

/*
 * TPS RTC module
 * 8 bit registers: R/W except where indicated as R-only
 */

#define TPS_RTC_SECONDS_REG        0x0000001C /* R-only */
#define TPS_RTC_MINUTES_REG        0x0000001D /* R-only */
#define TPS_RTC_HOURS_REG          0x0000001E /* R-only */
#define TPS_RTC_DAYS_REG           0x0000001F /* R-only */
#define TPS_RTC_MONTHS_REG         0x00000020 /* R-only */
#define TPS_RTC_YEARS_REG          0x00000021 /* R-only */
#define TPS_RTC_WEEKS_REG          0x00000022 /* R-only */
#define TPS_RTC_ALARM_SECONDS_REG  0x00000023
#define TPS_RTC_ALARM_MINUTES_REG  0x00000024
#define TPS_RTC_ALARM_HOURS_REG    0x00000025
#define TPS_RTC_ALARM_DAYS_REG     0x00000026
#define TPS_RTC_ALARM_MONTHS_REG   0x00000027
#define TPS_RTC_ALARM_YEARS_REG    0x00000028
#define TPS_RTC_RTC_CTRL_REG       0x00000029 /* R-only */
#define TPS_RTC_RTC_STATUS_REG     0x0000002A
#define TPS_RTC_RTC_INTERRUPTS_REG 0x0000002B
#define TPS_RTC_RTC_COMP_LSB_REG   0x0000002C /* R-only */
#define TPS_RTC_RTC_COMP_MSB_REG   0x0000002D /* R-only */

/* 
 * TPS POWER module
 * 8 bit R/W interrupt registers 
 */

#define TPS_PWR_ISR1     0x0000002E
#define TPS_PWR_IMR1     0x0000002F
#define TPS_PWR_ISR2     0x00000030 
#define TPS_PWR_IMR2     0x00000031
#define TPS_PWR_EDR1     0x00000033
#define TPS_PWR_EDR2     0x00000034
#define TPS_PWR_SIH_CTRL 0x00000035

/* TPS POWER module bit mask definitions */

#define TPS_PWR_SC_DETECT               (1 << 7)
#define TPS_PWR_MBCHG                   (1 << 6)
#define TPS_PWR_PWROK_TIMEOUT           (1 << 5)
#define TPS_PWR_HOT_DIE                 (1 << 4)
#define TPS_PWR_RTC_IT                  (1 << 3)
#define TPS_PWR_USB_PRES                (1 << 2)
#define TPS_PWR_CHG_PRES                (1 << 1)
#define TPS_PWR_PWRON                   (1 << 0)

#define TPS_PWR_RTC_IT_RISING           (1 << 7)
#define TPS_PWR_RTC_IT_FALLING          (1 << 6)
#define TPS_PWR_USB_PRES_RISING         (1 << 5)
#define TPS_PWR_USB_PRES_FALLING        (1 << 4)
#define TPS_PWR_CHG_PRES_RISING         (1 << 3)
#define TPS_PWR_CHG_PRES_FALLING        (1 << 2)
#define TPS_PWR_PWRON_RISING            (1 << 1)
#define TPS_PWR_PWRON_FALLING           (1 << 0)

#define TPS_PWR_SC_DETECT_RISING        (1 << 7)
#define TPS_PWR_SC_DETECT_FALLING       (1 << 6)
#define TPS_PWR_MBCHG_RISING            (1 << 5)
#define TPS_PWR_MBCHG_FALLING           (1 << 4)
#define TPS_PWR_PWROK_TIMEOUT_RISING    (1 << 3)
#define TPS_PWR_PWROK_TIMEOUT_FALLING   (1 << 2)
#define TPS_PWR_HOT_DIE_RISING          (1 << 1)
#define TPS_PWR_HOT_DIE_FALLING         (1 << 0)

#define TPS_PWR_COR                     (1 << 2)
#define TPS_PWR_PENDDIS                 (1 << 1)
#define TPS_PWR_EXCLEN                  (1 << 0)
  
/* 
 * Power Management master mode registers (p 275)
 * 8 bit R/W (except where indicated as read only) 
 */

#define TPS_PM_CFG_P1_TRANSITION   0x00000036
#define TPS_PM_CFG_P2_TRANSITION   0x00000037
#define TPS_PM_CFG_P3_TRANSITION   0x00000038
#define TPS_PM_CFG_P123_TRANSITION 0x00000039
#define TPS_PM_STS_BOOT            0x0000003A
#define TPS_PM_CFG_BOOT            0x0000003B
#define TPS_PM_SHUNDAN             0x0000003C
#define TPS_PM_BOOT_BCI            0x0000003D
#define TPS_PM_CFG_PWRANA1         0x0000003E
#define TPS_PM_CFG_PWRANA2         0x0000003F
#define TPS_PM_BGAP_TRIM           0x00000040
#define TPS_PM_BACKUP_MISC_STS     0x00000041 /* R-only */
#define TPS_PM_BACKUP_MISC_CFG     0x00000042 /* R-only */
#define TPS_PM_BACKUP_MISC_TST     0x00000043 /* R-only */
#define TPS_PM_PROTECT_KEY         0x00000044
#define TPS_PM_STS_HW_CONDITIONS   0x00000045
#define TPS_PM_P1_SW_EVENTS        0x00000046
#define TPS_PM_P2_SW_EVENTS        0x00000047
#define TPS_PM_P3_SW_EVENTS        0x00000048
#define TPS_PM_STS_P123_STATE      0x00000049 /* R-only */
#define TPS_PM_PB_CFG              0x0000004A
#define TPS_PM_PB_WORD_MSB         0x0000004B
#define TPS_PM_PB_WORD_LSB         0x0000004C
#define TPS_PM_RESERVED_A          0x0000004D /* R-only */
#define TPS_PM_RESERVED_B          0x0000004E /* R-only */
#define TPS_PM_RESERVED_C          0x0000004F /* R-only */
#define TPS_PM_RESERVED_D          0x00000050 /* R-only */
#define TPS_PM_RESERVED_E          0x00000051 /* R-only */
#define TPS_PM_SEQ_ADD_W2P         0x00000052
#define TPS_PM_SEQ_ADD_P2A         0x00000053
#define TPS_PM_SEQ_ADD_A2W         0x00000054
#define TPS_PM_SEQ_ADD_A2S         0x00000055
#define TPS_PM_SEQ_ADD_S2A12       0x00000056
#define TPS_PM_SEQ_ADD_S2A3        0x00000057
#define TPS_PM_SEQ_ADD_WARM        0x00000058
#define TPS_PM_MEMORY_ADDRESS      0x00000059
#define TPS_PM_MEMORY_DATA         0x0000005A

/* 
 * Sequence to send to the the TPS_PM_PROTECT_KEY
 * register, to unlock configuration registers. (p 288)
 */ 

#define UNPROTECT_CFG_0  0xC0
#define UNPROTECT_CFG_1  0x0C

/* 
 * Sequence to send to the the TPS_PM_PROTECT_KEY
 * register, to unlock test registers. (p 288)
 */ 

#define UNPROTECT_TST_0  0x0E
#define UNPROTECT_TST_1  0xE0

/*
 * The TPS_PM_PROTECT_KEY register is written with the above sequences
 * to unlock the test registers and/or configuration registers. The 
 * values may be OR'd together to unlock both registers at once. The
 * constants below are used to verify that the TPS_PM_PROTECT_KEY register
 * has reached the desired state. It will read 0, if both config and test
 * registers are locked. It will read 0x02 if just the config registers
 * are unlocked, 0x01 if the just the test registers are unlocked, and 0x03
 * if both test and config registers are unlocked.
 */

#define KEY_LOCK            0x00
#define KEY_UNLOCK_TST      0x01
#define KEY_UNLOCK_CFG      0x02
#define KEY_UNLOCK_CFG_TST  0x03

/* CFG_Px_TRANSITION bit mask definitions (pp 277-280) */

#define TPS_PM_STARTON_SWBUG  1 << 7

/* RESERVED   */

#define TPS_PM_STARTON_VBUS             (1 << 5)
#define TPS_PM_STARTON_VBAT             (1 << 4)
#define TPS_PM_STARTON_RTC              (1 << 3)
#define TPS_PM_STARTON_USB              (1 << 2)
#define TPS_PM_STARTON_CHG              (1 << 1)
#define TPS_PM_STARTON_PWON             (1 << 0)

/* CFG_P123_TRANSITION bit mask definitions (p 675)*/

#define TPS_PM_MSK_THERMAL_SHUTDOWN     (1 << 7)
#define TPS_PM_MSK_MBLO                 (1 << 6)
#define TPS_PM_SEQ_MSK_BAT_PRESENCE     (1 << 5)
#define TPS_PM_SEQ_MSK_BAT_LEVEL        (1 << 4)
#define TPS_PM_SEQ_MSK_THERM_HD         (1 << 3)
#define TPS_PM_SEQ_FREEZE               (1 << 2)
#define TPS_PM_SEQ_ONSYNC               (1 << 1)
#define TPS_PM_SEQ_OFFSYNC              (1 << 0)

/* STS_BOOT bit mask definitions (p 282) */

#define TPS_PM_BACKUP                   (1 << 7)
#define TPS_PM_TS                       (1 << 6)
#define TPS_PM_WATCHDOG_RESET           (1 << 5) 
#define TPS_PM_ITCHECK_RESET            (1 << 4)
#define TPS_PM_PWRON_8S                 (1 << 3)
#define TPS_PM_SETUP_DONE_BCK           (1 << 2)
#define TPS_PM_SETUP_DONE_PMC           (1 << 1)
#define TPS_PM_SYSEN_RESET              (1 << 0)

/* CFG_BOOT bit mask definitions (p 247, p 283) */

#define TPS_PM_CK32K_LOWPWR_EN          (1 << 7)
#define TPS_PM_BOOT_CFG_0               (0 << 4) 
#define TPS_PM_BOOT_CFG_1               (1 << 4) 
#define TPS_PM_BOOT_CFG_2               (2 << 4) 
#define TPS_PM_BOOT_CFG_3               (3 << 4) 
#define TPS_PM_HIGH_PERF_SQ             (1 << 3)
#define TPS_PM_SLICER_BYPASS            (1 << 2) 
#define TPS_PM_HFCLK_FREQ_0             (0 << 0)
#define TPS_PM_HFCLK_FREQ_1             (1 << 0)
#define TPS_PM_HFCLK_FREQ_2             (2 << 0)
#define TPS_PM_HFCLK_FREQ_3             (3 << 0)

/* 
 * SHUNDAN determines whether the main battery has been removed for more
 * or fewer than 2 seconds. When Vbat is low, count up to 2 seconds using 
 * a 32 Hz clock (32.768 kHz/1024). The default value of this register is
 * 0x3F after the first main battery insertion. The maximum value is 0x3E.
 * Set back to 0x00 by software.
 */

#define TPS_PM_SHUNDAN_CNT  0x3F 

/* BOOT_BCI bit mask definitions */

#define TPS_PM_BCIAUTOWEN                           (1 << 5)
#define TPS_PM_CONFIG_DONE                          (1 << 4)
/*  Reserved */                                     
#define TPS_PM_CVENAC                               (1 << 2)
#define TPS_PM_BCIAUTOUSB                           (1 << 1)
#define TPS_PM_BCIAUTOAC                            (1 << 0)
                                        

/* CFG_PWRANA2 bit mask definitions */

#define TPS_PM_VRRTC_DISABLE  (1 << 7)
#define TPS_PM_VRRTC_SLEEP    (1 << 6)
#define TPS_PM_VRRTC_TRIEN    (1 << 5)
#define TPS_PM_VRRTC_TRIM_0   (0 << 3)
#define TPS_PM_VRRTC_TRIM_1   (1 << 3)
#define TPS_PM_VRRTC_TRIM_2   (2 << 3)
#define TPS_PM_VRRTC_TRIM_3   (3 << 3)
#define TPS_PM_LOJIT1_LOWV    (1 << 2)
#define TPS_PM_LOJIT0_LOWV    (1 << 1)
#define TPS_PM_BYP_32KHZ_LOWV (1 << 0)

/* STS_HW_CONDITIONS bit mask definitions */

#define TPS_PM_STS_VBUS          (1 << 7)
#define TPS_PM_STS_WAKEUP3       (1 << 6)
#define TPS_PM_STS_WAKEUP2       (1 << 5)
#define TPS_PM_STS_WAKEUP1       (1 << 4)
#define TPS_PM_STS_WARMRESET     (1 << 3)
#define TPS_PM_STS_USB           (1 << 2)
#define TPS_PM_STS_CHG           (1 << 1)
#define TPS_PM_STS_PWON          (1 << 0)

/* Px_SW_EVENTS bit mask definitions */

#define TPS_PM_STOPON_PWRON         (1 << 6)
#define TPS_PM_5STOPON_SYSEN        (1 << 5)
#define TPS_PM_ENABLE_WARMRESET     (1 << 4)
#define TPS_PM_LVL_WAKEUP           (1 << 3)
#define TPS_PM_DEVACT               (1 << 2)
#define TPS_PM_DEVSLP               (1 << 1)
#define TPS_PM_DEVOFF               (1 << 0)

/* PB_CFG bit mask definitions */

/*
 * TPS_PM_PB_P123_BW
 *
 * 00 - P1, P2, P3 equal bandwidth (33% if PB_I2C_BWEN is low; 
 * 25% if PB_I2C_BWEN is high).
 *
 * 1 - P1 has 50% power bus bandwidth; others share 50% bandwidth 
 * equally (25% if PB_I2C_BWEN is low; 16% if PB_I2C_BWEN is high).
 *
 * 2 - P2 has 50 percent power bus bandwidth; others share 50
 *  percent bandwidth equally (25  8 percent if PB_I2C_BWEN is low;
 * 16 percent if PB_I2C_BWEN is high).
 *
 * 3 - P3 has 50% power bus bandwidth; others share 50% bandwidth
 * equally (25% if PB_I2C_BWEN is low; 16% if PB_I2C_BWEN is high).
 *
 */

#define TPS_PM_PB_P123_BW_3   (3 << 2)
#define TPS_PM_PB_P123_BW_2   (2 << 2)
#define TPS_PM_PB_P123_BW_1   (1 << 2)
#define TPS_PM_PB_P123_BW_0   (0 << 2)
#define TPS_PM_PB_I2C_BWEN    (1 << 1)
#define TPS_PM_PB_I2C_BUSY    (1 << 0) 

/* 
 * TPS_PM_STS_P123_STATE bit mask definitions
 */ 

#define TPS_PM_STS_P123_STABLE     (1 << 6)
#define TPS_PM_STS_SEQ_P3          (3 << 4)
#define TPS_PM_STS_SEQ_P2          (3 << 2)   
#define TPS_PM_STS_SEQ_P1          (3 << 0)


/* Power management receiver mode (p 306) */

#define TPS_PM_SC_CONFIG            0x0000005B
#define TPS_PM_SC_DETECT1           0x0000005C
#define TPS_PM_SC_DETECT2           0x0000005D
#define TPS_PM_WATCHDOG_CFG         0x0000005E
#define TPS_PM_IT_CHECK_CFG         0x0000005F
#define TPS_PM_VIBRATOR_CFG         0x0000005F
#define TPS_PM_DCDC_GLOBAL_CFG      0x00000061
#define TPS_PM_VDD1_TRIM1           0x00000062
#define TPS_PM_VDD1_TRIM2           0x00000063
#define TPS_PM_VDD2_TRIM1           0x00000064
#define TPS_PM_VDD2_TRIM2           0x00000065
#define TPS_PM_VIO_TRIM1            0x00000066
#define TPS_PM_VIO_TRIM2            0x00000067
#define TPS_PM_MISC_CFG             0x00000068
#define TPS_PM_LS_TST_A             0x00000069
#define TPS_PM_LS_TST_B             0x0000006A
#define TPS_PM_LS_TST_C             0x0000006B
#define TPS_PM_LS_TST_D             0x0000006C
#define TPS_PM_BB_CFG               0x0000006D
#define TPS_PM_TRIM1                0x0000006F
#define TPS_PM_TRIM2                0x00000070
#define TPS_PM_DCDC_TIMEOUT         0x00000071
#define TPS_PM_VAUX1_DEV_GRP        0x00000072
#define TPS_PM_VAUX1_TYPE           0x00000073
#define TPS_PM_VAUX1_REMAP          0x00000074
#define TPS_PM_VAUX1_DEDICATED      0x00000075
#define TPS_PM_VAUX2_DEV_GRP        0x00000076
#define TPS_PM_VAUX2_TYPE           0x00000077
#define TPS_PM_VAUX2_REMAP          0x00000078
#define TPS_PM_VAUX2_DEDICATED      0x00000079
#define TPS_PM_VAUX3_DEV_GRP        0x0000007A
#define TPS_PM_VAUX3_TYPE           0x0000007B
#define TPS_PM_VAUX3_REMAP          0x0000007C
#define TPS_PM_VAUX3_DEDICATED      0x0000007D
#define TPS_PM_VAUX4_DEV_GRP        0x0000007E
#define TPS_PM_VAUX4_TYPE           0x0000007F
#define TPS_PM_VAUX4_REMAP          0x00000080
#define TPS_PM_VAUX4_DEDICATED      0x00000081
#define TPS_PM_VMMC1_DEV_GRP        0x00000082
#define TPS_PM_VMMC1_TYPE           0x00000083
#define TPS_PM_VMMC1_REMAP          0x00000084
#define TPS_PM_VMMC1_DEDICATED      0x00000085
#define TPS_PM_VMMC2_DEV_GRP        0x00000086
#define TPS_PM_VMMC2_TYPE           0x00000087
#define TPS_PM_VMMC2_REMAP          0x00000088
#define TPS_PM_VMMC2_DEDICATED      0x00000089
#define TPS_PM_VPLL1_DEV_GRP        0x0000008A
#define TPS_PM_VPLL1_TYPE           0x0000008B
#define TPS_PM_VPLL1_REMAP          0x0000008C
#define TPS_PM_VPLL1_DEDICATED      0x0000008D
#define TPS_PM_VPLL2_DEV_GRP        0x0000008D
#define TPS_PM_VPLL2_TYPE           0x0000008F
#define TPS_PM_VPLL2_REMAP          0x00000090
#define TPS_PM_VPLL2_DEDICATED      0x00000091
#define TPS_PM_VSIM_DEV_GRP         0x00000092
#define TPS_PM_VSIM_TYPE            0x00000093
#define TPS_PM_VSIM_REMAP           0x00000094
#define TPS_PM_VSIM_DEDICATED       0x00000095
#define TPS_PM_VDAC_DEV_GRP         0x00000096
#define TPS_PM_VDAC_TYPE            0x00000097
#define TPS_PM_VDAC_REMAP           0x00000098
#define TPS_PM_VDAC_DEDICATED       0x00000099
#define TPS_PM_VINTANA1_DEV_GRP     0x0000009A
#define TPS_PM_VINTANA1_TYPE        0x0000009B
#define TPS_PM_VINTANA1_REMAP       0x0000009C
#define TPS_PM_VINTANA1_DEDICATED   0x0000009D
#define TPS_PM_VINTANA2_DEV_GRP     0x0000009E
#define TPS_PM_VINTANA2_TYPE        0x0000009F
#define TPS_PM_VINTANA2_REMAP       0x000000A0
#define TPS_PM_VINTANA2_DEDICATED   0x000000A1
#define TPS_PM_VINTDIG_DEV_GRP      0x000000A2
#define TPS_PM_VINTDIG_TYPE         0x000000A3
#define TPS_PM_VINTDIG_REMAP        0x000000A4
#define TPS_PM_VINTDIG_DEDICATED    0x000000A5
#define TPS_PM_VIO_DEV_GRP          0x000000A6
#define TPS_PM_VIO_TYPE             0x000000A7
#define TPS_PM_VIO_REMAP            0x000000A8
#define TPS_PM_VIO_CFG              0x000000A9
#define TPS_PM_VIO_MISC_CFG         0x000000AA
#define TPS_PM_VIO_TEST1            0x000000AB
#define TPS_PM_VIO_TEST2            0x000000AC
#define TPS_PM_VIO_OSC              0x000000AD
#define TPS_PM_VIO_RESERVED         0x000000AE
#define TPS_PM_VIO_VSEL             0x000000AF
#define TPS_PM_VDD1_DEV_GRP         0x000000B0
#define TPS_PM_VDD1_TYPE            0x000000B1
#define TPS_PM_VDD1_REMAP           0x000000B2
#define TPS_PM_VDD1_CFG             0x000000B3
#define TPS_PM_VDD1_MISC_CFG        0x000000B4
#define TPS_PM_VDD1_TEST1           0x000000B5
#define TPS_PM_VDD1_TEST2           0x000000B6
#define TPS_PM_VDD1_OSC             0x000000B7
#define TPS_PM_VDD1_RESERVED        0x000000B8
#define TPS_PM_VDD1_VSEL            0x000000B9
#define TPS_PM_VDD1_VMODE_CFG       0x000000BA
#define TPS_PM_VDD1_VFLOOR          0x000000BB
#define TPS_PM_VDD1_VROOF           0x000000BC
#define TPS_PM_VDD1_STEP            0x000000BD
#define TPS_PM_VDD2_DEV_GRP         0x000000BE
#define TPS_PM_VDD2_TYPE            0x000000BF
#define TPS_PM_VDD2_REMAP           0x000000C0
#define TPS_PM_VDD2_CFG             0x000000C1
#define TPS_PM_VDD2_MISC_CFG        0x000000C2
#define TPS_PM_VDD2_TEST1           0x000000C3
#define TPS_PM_VDD2_TEST2           0x000000C4
#define TPS_PM_VDD2_TEST3           0x000000C5
#define TPS_PM_VDD2_RESERVED        0x000000C6
#define TPS_PM_VDD2_VSEL            0x000000C7
#define TPS_PM_VDD2_VMODE_CFG       0x000000C8
#define TPS_PM_VDD2_VFLOOR          0x000000C9
#define TPS_PM_VDD2_VROOF           0x000000CA
#define TPS_PM_VDD2_STEP            0x000000CB
#define TPS_PM_VUSB1V5_DEV_GRP      0x000000CC
#define TPS_PM_VUSB1V5_TYPE         0x000000CD
#define TPS_PM_VUSB1V5_REMAP        0x000000CE
#define TPS_PM_VUSB1V8_DEV_GRP      0x000000CF
#define TPS_PM_VUSB1V8_TYPE         0x000000D0
#define TPS_PM_VUSB1V8_REMAP        0x000000D1
#define TPS_PM_VUSB3V1_DEV_GRP      0x000000D2
#define TPS_PM_VUSB3V1_TYPE         0x000000D3
#define TPS_PM_VUSB3V1_REMAP        0x000000D4
#define TPS_PM_VUSBCP_DEV_GRP       0x000000D5
#define TPS_PM_VUSBCP_TYPE          0x000000D6
#define TPS_PM_VUSBCP_REMAP         0x000000D7
#define TPS_PM_VUSB_DEDICATED1      0x000000D8
#define TPS_PM_VUSB_DEDICATED2      0x000000D9
#define TPS_PM_REGEN_DEV_GRP        0x000000DA
#define TPS_PM_REGEN_TYPE           0x000000DB
#define TPS_PM_REGEN_REMAP          0x000000DC
#define TPS_PM_NRESPWRON_DEV_GRP    0x000000DD
#define TPS_PM_NRESPWRON_TYPE       0x000000DE
#define TPS_PM_NRESPWRON_REMAP      0x000000DF
#define TPS_PM_CLKEN_DEV_GRP        0x000000E0
#define TPS_PM_CLKEN_TYPE           0x000000E1
#define TPS_PM_CLKEN_REMAP          0x000000E2
#define TPS_PM_SYSEN_DEV_GRP        0x000000E3
#define TPS_PM_SYSEN_TYPE           0x000000E4
#define TPS_PM_SYSEN_REMAP          0x000000E5
#define TPS_PM_HFCLKOUT_DEV_GRP     0x000000E6
#define TPS_PM_HFCLKOUT_TYPE        0x000000E7
#define TPS_PM_HFCLKOUT_REMAP       0x000000E8
#define TPS_PM_32KCLKOUT_DEV_GRP    0x000000E9
#define TPS_PM_32KCLKOUT_TYPE       0x000000EA
#define TPS_PM_32KCLKOUT_REMAP      0x000000EB
#define TPS_PM_TRITON_RESET_DEV_GRP 0x000000EC
#define TPS_PM_TRITON_RESET_TYPE    0x000000ED
#define TPS_PM_TRITON_RESET_REMAP   0x000000EE
#define TPS_PM_MAINREF_DEV_GRP      0x000000EF
#define TPS_PM_MAINREF_TYPE         0x000000F0
#define TPS_PM_MAINREF_REMAP        0x000000F1

/* TPS_PM_DCDC_GLOBAL_CFG bit mask definitions */

/* bit masks and constants for TPS_PM_DCDC_GLOBAL_CFG */

#define TPS_PM_DCDC_CARD_DTCT_2_LVL         (1 << 7)
#define TPS_PM_DCDC_CARD_DTCT_1_LVL         (1 << 6)
#define TPS_PM_DCDC_REGEN_PU_DIS            (1 << 5)
#define TPS_PM_DCDC_SYSEN_PU_DIS            (1 << 4)
#define TPS_PM_DCDC_SMARTREFLEX_EN          (1 << 3)
#define TPS_PM_DCDC_CARD_DETECT_CFG         (1 << 2)
#define TPS_PM_DCDC_CLK_32K_DEGATE1         (1 << 1)
#define TPS_PM_DCDC_CLK_HF_DEGATE           (1 << 0)


/* bit masks and constants for TPS_PM_SC_CONFIG */

#define TPS_PM_SC_CFG_ENABLE                      (1 << 7)
#define TPS_PM_SC_CFG_MODE                        (1 << 6)
#define TPS_PM_SC_CFG_AUTOCUT                     (1 << 5)

/* For TEN_SEL bits [4:0] Use the following masks */

#define TPS_PM_SC_CFG_TST_AUX1_LOWV      0x00
#define TPS_PM_SC_CFG_TST_AUX2_LOWV      0x01
#define TPS_PM_SC_CFG_TST_AUX3_LOWV      0x02
#define TPS_PM_SC_CFG_TST_AUX4_LOWV      0x03
#define TPS_PM_SC_CFG_TST_MMC1_LOWV      0x04
#define TPS_PM_SC_CFG_TST_MMC2_LOWV      0x05
#define TPS_PM_SC_CFG_TST_INTDIG_LOWV    0x06
#define TPS_PM_SC_CFG_TST_VINTANA2_LOWV  0x07
#define TPS_PM_SC_CFG_TST_PLL2_LOWV      0x08
#define TPS_PM_SC_CFG_TST_VDD1_LOWV0     0x09
#define TPS_PM_SC_CFG_TST_VDD2_LOWV0     0x0A
#define TPS_PM_SC_CFG_TST_VIO_LOWV0      0x0B
#define TPS_PM_SC_CFG_TST_VDAC_LOWV      0x0C
#define TPS_PM_SC_CFG_TST_VUSB1V5_LOWV   0x0D
#define TPS_PM_SC_CFG_TST_VUSB1V8_LOWV   0x0E
#define TPS_PM_SC_CFG_TST_VUSB3V1_LOWV   0x0F
#define TPS_PM_SC_CFG_TST_VINTANA_LOWV   0x0D
#define TPS_PM_SC_CFG_TST_PLL1_LOWV      0x0E
#define TPS_PM_SC_CFG_TST_POR_LOWV       0x0F
#define TPS_PM_SC_CFG_TST_SIM_LOWV       0x010
#define TPS_PM_SC_CFG_TST_TSHUT_LOWV     0x011
#define TPS_PM_SC_CFG_TST_TSHUT_REG_LOWV 0x012
#define TPS_PM_SC_CFG_TST_UPR_LOWV       0x013
#define TPS_PM_SC_CFG_TST_VRRTC_LOWV     0x014
#define TPS_PM_SC_CFG_TST_HFCLK_LOWV     0x015
#define TPS_PM_SC_CFG_NO_OUT_DRV_HIGH    0x016 /* 0x016 through 0x01E */
#define TPS_PM_SC_CFG_TSTV_SW_CTRL       0x01F


/* 
 * bit masks and constants for SC_DETECT1 
 * Short-circuit detect 1 register (VRRTC domain)
 */

#define TPS_PM_SC_DETECT1_VINTANA2           (1 << 7)

/* RESERVED  */

#define TPS_PM_SC_DETECT1_SC_VMMC2           (1 << 5)
#define TPS_PM_SC_DETECT1_SC_VMMC1           (1 << 4)
#define TPS_PM_SC_DETECT1_SC_VAUX4           (1 << 3)
#define TPS_PM_SC_DETECT1_SC_VAUX3           (1 << 2)
#define TPS_PM_SC_DETECT1_SC_VAUX2           (1 << 1)
#define TPS_PM_SC_DETECT1_SC_VAUX1           (1 << 0) 


/* 
 * bit masks and constants for SC_DETECT2 
 * Short-circuit detect 2 register (VRRTC domain)
 */

#define TPS_PM_SC_DETECT2_VUSB3V1             (1 << 7)
#define TPS_PM_SC_DETECT2_VUSB1V8             (1 << 6)
#define TPS_PM_SC_DETECT2_VUSB1V5             (1 << 5)
#define TPS_PM_SC_DETECT2_VDAC                (1 << 4)
#define TPS_PM_SC_DETECT2_VIO                 (1 << 3)
#define TPS_PM_SC_DETECT2_VDD2                (1 << 2)
#define TPS_PM_SC_DETECT2_VDD1                (1 << 1)
#define TPS_PM_SC_DETECT2_VPLL2               (1 << 0) 
/* 
 * bit masks and constants for VDD2_VMODE_CFG
 * vmode configuration register (VRRTC domain)
 */

#define TPS_PM_VDD2_VMODE_STS_BUSY             (1 << 5)
#define TPS_PM_VDD2_VMODE_STS_ROOF             (1 << 4)
#define TPS_PM_VDD2_VMODE_STS_FLOOR            (1 << 3)
#define TPS_PM_VDD2_VMODE_DCDC_SLP             (1 << 2)
#define TPS_PM_VDD2_VMODE_READ_REG             (1 << 1)
#define TPS_PM_VDD2_VMODE_ENABLE_VMODE         (1 << 0)



/* bit masks and constants for TPS_PM_MISCCFG */


#define TPS_PM_MISCCFG_TEMP_SEL              (1 << 6)
#define TPS_PM_MISCCFG_VINTANA2_SWITCH_AUTO1 (1 << 5)
#define TPS_PM_MISCCFG_CLK_HF_DRV            (1 << 4)
#define TPS_PM_MISCCFG_RFID_EN_PU_DISABLE    (1 << 3)
#define TPS_PM_MISCCFG_RFID_EN               (1 << 2)
#define TPS_PM_MISCCFG_CLKEN2_CFG            (1 << 1)
#define TPS_PM_MISCCFG_CLKEN2_ENABLE         (1 << 0)


/* 
 * DEV_GRP P1, P2, P3 device groups
 * Bit masks and constants for device groups for USB_VR_DEV_GRP, 
 * REGEN_DEV_GRP, NRESPWRON_DEV_GRP, CLKEN_DEV_GRP, SYSEN_DEV_GRP, 
 * HFCLKOUT_DEV_GRP, TRITON_RESET_DEV_GRP, MAINREF_DEV_GRP device 
 * group registers. (VRRTC domain) 
 */
 
#define TPS_PM_NO_DEV_GRP    (0x0 << 5)/* Belongs to no device group */
#define TPS_PM_P1_DEV_GRP    (0x1 << 5)/* Belongs to P1 device group */
#define TPS_PM_P2_DEV_GRP    (0x2 << 5)/* Belongs to P2 device group */
#define TPS_PM_P1_P2_DEV_GRP (0x3 << 5)/* Belongs to P1 and P2 device groups */
#define TPS_PM_P3_DEV_GRP    (0x4 << 5)/* Belongs to P3 device group */
#define TPS_PM_P1_P3_DEV_GRP (0x5 << 5)/* Belongs to P1 and P3 device groups */
#define TPS_PM_P2_P3_DEV_GRP (0x6 << 5)/* Belongs to P2 and P3 device groups */
#define TPS_PM_ALL_DEV_GRP   (0x7 << 5)/* Belongs to all device groups */
#define TPS_PM_WARM_CFG      (1 << 4)   


/*
 * This section is dedicated to the TPS65950
 * I2C Address group 3 (0x4A) TPS_I2C_ADDRESS_ID3 
 */

/* base addresses of the TPS modules in ADDRESS_ID3 (0x4A)*/

#define TPS_MADC_BASE        0x00000000   
#define TPS_MAIN_CHG_BASE    0x00000074
#define TPS_INT_BCI_BASE     0x000000B9  
#define TPS_KEYP_BASE        0x000000D2
#define TPS_PWM0_BASE        0X000000F8
#define TPS_PWM1_BASE        0x000000FB
#define TPS_LED_BASE         0X000000EE
#define TPS_PWMA_BASE        0x000000EF
#define TPS_PWMB_BASE        0x000000F1 

/* 
 * TPS MADC (monitoring analog-to-digital converter) 
 * module 8 bit R/W registers 
 */

#define TPS_MADC_CTRL1          0x00000000
#define TPS_MADC_CTRL2          0x00000001
#define TPS_MADC_RTSELECT_LSB   0x00000002
#define TPS_MADC_RTSELECT_MSB   0x00000003
#define TPS_MADC_RTAVERAGE_LSB  0x00000004
#define TPS_MADC_RTAVERAGE_MSB  0x00000005
#define TPS_MADC_SW1SELECT_LSB  0x00000006
#define TPS_MADC_SW1SELECT_MSB  0x00000007
#define TPS_MADC_SW1AVERAGE_LSB 0x00000008
#define TPS_MADC_SW1AVERAGE_MSB 0x00000009
#define TPS_MADC_SW2SELECT_LSB  0x0000000A
#define TPS_MADC_SW2SELECT_MSB  0x0000000B
#define TPS_MADC_SW2AVERAGE_LSB 0x0000000C
#define TPS_MADC_SW2AVERAGE_MSB 0x0000000D
#define TPS_MADC_BCI_USBAVERAGE 0x0000000E
#define TPS_MADC_ACQUISITION    0x0000000F
#define TPS_MADC_USBREF_LSB     0x00000010
#define TPS_MADC_USBREF_MSB     0x00000011
#define TPS_MADC_CTRL_SW1       0x00000012
#define TPS_MADC_CTRL_SW2       0x00000013
#define TPS_MADC_TEST           0x00000014
#define TPS_GP_MADC_TEST1       0x00000015
#define TPS_GP_MADC_TEST2       0x00000016
#define TPS_MADC_RTCH0_LSB      0x00000017
#define TPS_MADC_RTCH0_MSB      0x00000018
#define TPS_MADC_RTCH1_LSB      0x00000019
#define TPS_MADC_RTCH1_MSB      0x0000001A
#define TPS_MADC_RTCH2_LSB      0x0000001B
#define TPS_MADC_RTCH2_MSB      0x0000001C
#define TPS_MADC_RTCH3_LSB      0x0000001D
#define TPS_MADC_RTCH3_MSB      0x0000001E
#define TPS_MADC_RTCH4_LSB      0x0000001F
#define TPS_MADC_RTCH4_MSB      0x00000020
#define TPS_MADC_RTCH5_LSB      0x00000021
#define TPS_MADC_RTCH5_MSB      0x00000022
#define TPS_MADC_RTCH6_LSB      0x00000023
#define TPS_MADC_RTCH6_MSB      0x00000024
#define TPS_MADC_RTCH7_LSB      0x00000025
#define TPS_MADC_RTCH7_MSB      0x00000026
#define TPS_MADC_RTCH8_LSB      0x00000027
#define TPS_MADC_RTCH8_MSB      0x00000028
#define TPS_MADC_RTCH9_LSB      0x00000029
#define TPS_MADC_RTCH9_MSB      0x0000002A
#define TPS_MADC_RTCH10_LSB     0x0000002B
#define TPS_MADC_RTCH10_MSB     0x0000002C
#define TPS_MADC_RTCH11_LSB     0x0000002D
#define TPS_MADC_RTCH11_MSB     0x0000002E
#define TPS_MADC_RTCH12_LSB     0x0000002F
#define TPS_MADC_RTCH12_MSB     0x00000030
#define TPS_MADC_RTCH13_LSB     0x00000031
#define TPS_MADC_RTCH13_MSB     0x00000032
#define TPS_MADC_RTCH14_LSB     0x00000033
#define TPS_MADC_RTCH14_MSB     0x00000034
#define TPS_MADC_RTCH15_LSB     0x00000035
#define TPS_MADC_RTCH15_MSB     0x00000036
#define TPS_MADC_GPCH0_LSB      0x00000037
#define TPS_MADC_GPCH0_MSB      0x00000038
#define TPS_MADC_GPCH1_LSB      0x00000039
#define TPS_MADC_GPCH1_MSB      0x0000003A
#define TPS_MADC_GPCH2_LSB      0x0000003B
#define TPS_MADC_GPCH2_MSB      0x0000003C
#define TPS_MADC_GPCH3_LSB      0x0000003D
#define TPS_MADC_GPCH3_MSB      0x0000003E
#define TPS_MADC_GPCH4_LSB      0x0000003F
#define TPS_MADC_GPCH4_MSB      0x00000040
#define TPS_MADC_GPCH5_LSB      0x00000041
#define TPS_MADC_GPCH5_MSB      0x00000042
#define TPS_MADC_GPCH6_LSB      0x00000043
#define TPS_MADC_GPCH6_MSB      0x00000044
#define TPS_MADC_GPCH7_LSB      0x00000045
#define TPS_MADC_GPCH7_MSB      0x00000046
#define TPS_MADC_GPCH8_LSB      0x00000047
#define TPS_MADC_GPCH8_MSB      0x00000048
#define TPS_MADC_GPCH9_LSB      0x00000049
#define TPS_MADC_GPCH9_MSB      0x0000004A
#define TPS_MADC_GPCH10_LSB     0x0000004B
#define TPS_MADC_GPCH10_MSB     0x0000004C
#define TPS_MADC_GPCH11_LSB     0x0000004D
#define TPS_MADC_GPCH11_MSB     0x0000004E
#define TPS_MADC_GPCH12_LSB     0x0000004F
#define TPS_MADC_GPCH12_MSB     0x00000050
#define TPS_MADC_GPCH13_LSB     0x00000051
#define TPS_MADC_GPCH13_MSB     0x00000052
#define TPS_MADC_GPCH14_LSB     0x00000053
#define TPS_MADC_GPCH14_MSB     0x00000054
#define TPS_MADC_GPCH15_LSB     0x00000055
#define TPS_MADC_GPCH15_MSB     0x00000056
#define TPS_MADC_BCICH0_LSB     0x00000057
#define TPS_MADC_BCICH0_MSB     0x00000058
#define TPS_MADC_BCICH1_LSB     0x00000059
#define TPS_MADC_BCICH1_MSB     0x0000005A
#define TPS_MADC_BCICH2_LSB     0x0000005B
#define TPS_MADC_BCICH2_MSB     0x0000005C
#define TPS_MADC_BCICH3_LSB     0x0000005D
#define TPS_MADC_BCICH3_MSB     0x0000005E
#define TPS_MADC_BCICH4_LSB     0x0000005F
#define TPS_MADC_BCICH4_MSB     0x00000060

/* 
 * TPS MADC (monitoring analog-to-digital converter) module
 * 8 bit R/W interrupt registers 
 */

#define TPS_MADC_ISR1       0x00000061
#define TPS_MADC_IMR1       0x00000062
#define TPS_MADC_ISR2       0x00000063
#define TPS_MADC_IMR2       0x00000064
#define TPS_MADC_EDR        0x00000066
#define TPS_MADC_SIH_CTRL   0x00000067

/* TPS MADC module bit mask definitions X=1,2 */

#define TPS_MADC_RSVD4                     (1 << 7)
#define TPS_MADC_RSVD3                     (1 << 6)
#define TPS_MADC_RSVD2                     (1 << 5)
#define TPS_MADC_RSVD1                     (1 << 4)
#define TPS_MADC_USB_ISRX                  (1 << 3)
#define TPS_MADC_SW2_ISRX                  (1 << 2)
#define TPS_MADC_SW1_ISRX                  (1 << 1)
#define TPS_MADC_RT_ISRX                   (1 << 0)

#define TPS_MADC_USB_IMRX                  (1 << 3)
#define TPS_MADC_SW2_IMRX                  (1 << 2)
#define TPS_MADC_SW1_IMRX                  (1 << 1)
#define TPS_MADC_RT_IMRX                   (1 << 0)

#define TPS_MADC_USB_RISING           (1 << 7)
#define TPS_MADC_USB_FALLING          (1 << 6)
#define TPS_MADC_SW2_RISING           (1 << 5)
#define TPS_MADC_SW2_FALLING          (1 << 4)
#define TPS_MADC_SW1_RISING           (1 << 3)
#define TPS_MADC_SW1_FALLING          (1 << 2)
#define TPS_MADC_RT_RISING            (1 << 1)
#define TPS_MADC_RT_FALLING           (1 << 0)

#define TPS_MADC_COR                         (1 << 2)
#define TPS_MADC_PENDDIS                     (1 << 1)
#define TPS_MADC_EXCLEN                      (1 << 0)

#define TPS_USB_IDGND_RISE            (1 << 4)
#define TPS_USB_SESSEND_RISE          (1 << 3)
#define TPS_USB_SESSVALID_RISE        (1 << 2)
#define TPS_USB_VBUSVALID_RISE        (1 << 1)
#define TPS_USB_HOSTDISCONNECT_RISE   (1 << 0)

/*
 * TPS MAIN_CHARGE module 8 bit R-only registers
 * (except for BCIMDKEY which is W-only)
 */

#define TPS_MAIN_CHG_BCIMDEN       0x00000074
#define TPS_MAIN_CHG_BCIMDKEY      0x00000075  /* W-only */
#define TPS_MAIN_CHG_BCIMSTATEC    0x00000076
#define TPS_MAIN_CHG_BCIMSTATEP    0x00000077
#define TPS_MAIN_CHG_BCIVBAT1      0x00000078
#define TPS_MAIN_CHG_BCIVBAT2      0x00000079
#define TPS_MAIN_CHG_BCITBAT1      0x0000007A
#define TPS_MAIN_CHG_BCITBAT2      0x0000007B
#define TPS_MAIN_CHG_BCIICHG1      0x0000007C
#define TPS_MAIN_CHG_BCIICHG2      0x0000007D
#define TPS_MAIN_CHG_BCIVAC1       0x0000007E
#define TPS_MAIN_CHG_BCIVAC2       0x0000007F
#define TPS_MAIN_CHG_BCIVBUS1      0x00000080
#define TPS_MAIN_CHG_BCIVBUS2      0x00000081
#define TPS_MAIN_CHG_BCIMFSTS2     0x00000082
#define TPS_MAIN_CHG_BCIMFSTS3     0x00000083
#define TPS_MAIN_CHG_BCIMFSTS4     0x00000084

/* 
 * MAIN_CHARGE 8 bit R/W registers
 * (except for BCIWDKEY which is W-only)
 */

#define TPS_MAIN_CHG_BCIMFKEY      0x00000085
#define TPS_MAIN_CHG_BCIMFEN1      0x00000086
#define TPS_MAIN_CHG_BCIMFEN2      0x00000087
#define TPS_MAIN_CHG_BCIMFEN3      0x00000088
#define TPS_MAIN_CHG_BCIMFEN4      0x00000089
#define TPS_MAIN_CHG_BCIMFTH1      0x0000008A
#define TPS_MAIN_CHG_BCIMFTH2      0x0000008B
#define TPS_MAIN_CHG_BCIMFTH3      0x0000008C
#define TPS_MAIN_CHG_BCIMFTH4      0x0000008D
#define TPS_MAIN_CHG_BCIMFTH5      0x0000008E
#define TPS_MAIN_CHG_BCIMFTH6      0x0000008F
#define TPS_MAIN_CHG_BCIMFTH7      0x00000090
#define TPS_MAIN_CHG_BCIMFTH8      0x00000091
#define TPS_MAIN_CHG_BCIMFTH9      0x00000092
#define TPS_MAIN_CHG_BCITIMER1     0x00000093
#define TPS_MAIN_CHG_BCITIMER2     0x00000094
#define TPS_MAIN_CHG_BCIWDKEY      0x00000095 /* W-only */
#define TPS_MAIN_CHG_BCIWD         0x00000096
#define TPS_MAIN_CHG_BCICTL1       0x00000097
#define TPS_MAIN_CHG_BCICTL2       0x00000098
#define TPS_MAIN_CHG_BCIVREF1      0x00000099
#define TPS_MAIN_CHG_BCIVREF2      0x0000009A
#define TPS_MAIN_CHG_BCIIREF1      0x0000009B
#define TPS_MAIN_CHG_BCIIREF2      0x0000009C
#define TPS_MAIN_CHG_BCIPWM2       0x0000009D
#define TPS_MAIN_CHG_BCIPWM1       0x0000009E
#define TPS_MAIN_CHG_BCITRIM1      0x0000009F
#define TPS_MAIN_CHG_BCITRIM2      0x000000A0
#define TPS_MAIN_CHG_BCITRIM3      0x000000A1
#define TPS_MAIN_CHG_BCITRIM4      0x000000A2
#define TPS_MAIN_CHG_BCIVREFCOMB1  0x000000A3
#define TPS_MAIN_CHG_BCIVREFCOMB2  0x000000A4
#define TPS_MAIN_CHG_BCIIREFCOMB1  0x000000A5
#define TPS_MAIN_CHG_BCIIREFCOMB2  0x000000A6
                                               
/* 
 * TPS BCI module 
 * 8 bit R/W interrupt registers  
 * 
 * Controls charging of batteries. Supports regulated AC chargers with USB
 * host devices, multiple channels per carrier (MCPC) devices, USB chargers,
 * car kits of 7-V abs max. Battery monitored. Uses 10-bit ADC (from MADC
 * module) to measure battery voltage, temperature, type, charge current,
 * VBUS input voltage, AC charger input voltage. Monitors AC charger, VBUS
 * or batter over-voltage detection, battery voltage-level, charge current
 * level, temperature out-of-range, end-of-charge and over-current 
 * detection, and watchdog.
 */

#define TPS_PIH_BCIISR1A   0x000000B9
#define TPS_PIH_BCIISR2A   0x000000BA
#define TPS_PIH_BCIIMR1A   0x000000BB
#define TPS_PIH_BCIIMR2A   0x000000BC
#define TPS_PIH_BCIISR1B   0x000000BD
#define TPS_PIH_BCIISR2B   0x000000BE
#define TPS_PIH_BCIIMR1B   0x000000BF
#define TPS_PIH_BCIIMR2B   0x000000C0
#define TPS_PIH_BCIEDR1    0x000000C3
#define TPS_PIH_BCIEDR2    0x000000C4
#define TPS_PIH_BCIEDR3    0x000000C5
#define TPS_PIH_BCISIHCTRL 0x000000C6

/* 
 * bit mask definitions for TPS BCI module 
 * X=S,M  Y=A,B N=1,2 
 *
 * BCIIXRNY type registers:
 * Bit set to 1 when corresponding monitoring function interrupt
 * has triggered the PO_BCI_SIH_INT1_N request. Cannot generate
 * interrupt by setting ISR2A bit to 1. If set to 1, corresponding 
 * interrupt line is released. If set to 0, no change. Synchronous 
 * with interface OCP clock.
 *  
 * BCIIXRNY type registers: 
 * Unmask expected transition on end-of-sequence from generating
 * an interrupt request on PO_BCI_SIH_INT1_N. Interrupt mask  
 * registers programmed synchronously with the interface OCP clock.
 */ 

#define TPS_PIH_BCIIXRNX_ACCHGOV             (1 << 3)
#define TPS_PIH_BCIIXRNX_VBUSOV              (1 << 2)
#define TPS_PIH_BCIIXRNX_VBATOV              (1 << 1)
#define TPS_PIH_BCIIXRNX_VBATLVL             (1 << 0)

#define TPS_PIH_BCIIXRNY_BATSTS            (1 << 7)
#define TPS_PIH_BCIIXRNY_TBATOR1           (1 << 6)
#define TPS_PIH_BCIIXRNY_TBATOR2           (1 << 5)
#define TPS_PIH_BCIIXRNY_ICHGEOC           (1 << 4)     
#define TPS_PIH_BCIIXRNY_ICHGLOW           (1 << 3)  
#define TPS_PIH_BCIIXRNY_IICHGHIGH         (1 << 2)    
#define TPS_PIH_BCIIXRNY_TMOVF             (1 << 1)     
#define TPS_PIH_BCIIXRNY_WOVF              (1 << 0) 

#define TPS_PIH_BCIEDRX_ICHGLOW_RISING   (1 << 7)
#define TPS_PIH_BCIEDRX_ICHGLOW_FALLING  (1 << 6) 
#define TPS_PIH_BCIEDRX_ICHGHIGH_RISING  (1 << 5) 
#define TPS_PIH_BCIEDRX_ICHGHIGH_FALLING (1 << 4) 
#define TPS_PIH_BCIEDRX_TMOVF_RISING     (1 << 3)
#define TPS_PIH_BCIEDRX_TMOVF_RFALLING   (1 << 2) 
#define TPS_PIH_BCIEDRX_WOVF_RISING      (1 << 1) 
#define TPS_PIH_BCIEDRX_WOVF_FALLING     (1 << 0) 

#define TPS_PIH_BCISIHCTRL_COR                 (1 << 2) 
#define TPS_PIH_BCISIHCTRL_PENDDIS             (1 << 1)
#define TPS_PIH_BCISIHCTRL_EXCLEN              (1 << 0)      
          
/*
 * TPS Keypad module
 * 8 bit R/W registers
 */

#define TPS_KEYP_CTRL_REG       0x000000D2
#define TPS_KEYP_DEB_REG        0x000000D3
#define TPS_KEYP_LONG_KEY_REG1  0x000000D4
#define TPS_KEYP_LK_PTV_REG     0x000000D5
#define TPS_KEYP_TIME_OUT_REG1  0x000000D6
#define TPS_KEYP_TIME_OUT_REG2  0x000000D7
#define TPS_KEYP_KBC_REG        0x000000D8

/*
 * TPS Keypad module
 * 8 bit read-only registers
 */

#define TPS_KEYP_KBR_REG          0x000000D9 
#define TPS_KEYP_SMS              0x000000DA
#define TPS_KEYP_FULL_CODE_7_0    0x000000DB
#define TPS_KEYP_FULL_CODE_15_8   0x000000DC
#define TPS_KEYP_FULL_CODE_23_16  0x000000DD
#define TPS_KEYP_FULL_CODE_31_24  0x000000DE
#define TPS_KEYP_FULL_CODE_39_32  0x000000DF
#define TPS_KEYP_FULL_CODE_47_40  0x000000E0
#define TPS_KEYP_FULL_CODE_55_48  0x000000E1
#define TPS_KEYP_FULL_CODE_63_56  0x000000E2

/*
 * TPS Keypad module
 * 8 bit R/W interrupt registers
 *
 */

#define TPS_KEYP_ISR1     0x000000E3
#define TPS_KEYP_IMR1     0x000000E4
#define TPS_KEYP_ISR2     0x000000E5
#define TPS_KEYP_IMR2     0x000000E6
#define TPS_KEYP_EDR      0x000000E8
#define TPS_KEYP_SIH_CTRL 0x000000E9

/* TPS Keypad module bit mask definitions X=1,2*/

#define TPS_KEYP_ITMISRX               (1 << 3)
#define TPS_KEYP_ITTOISRX              (1 << 2)
#define TPS_KEYP_ITLKISRX              (1 << 1)
#define TPS_KEYP_ITKPISRX              (1 << 0)

#define TPS_KEYP_ITMISIMRX             (1 << 3)
#define TPS_KEYP_ITTOIMRX              (1 << 2)
#define TPS_KEYP_ITLKIMRX              (1 << 1)
#define TPS_KEYP_ITKPIMRX              (1 << 1)

#define TPS_KEYP_ITMISRISING       (1 << 7)
#define TPS_KEYP_ITMISFALLING      (1 << 6)
#define TPS_KEYP_ITTORISING        (1 << 5)
#define TPS_KEYP_ITTOFALLING       (1 << 4)
#define TPS_KEYP_ITLKRISING        (1 << 3)
#define TPS_KEYP_ITLKFALLING       (1 << 2)
#define TPS_KEYP_ITKPRISING        (1 << 1)
#define TPS_KEYP_ITKPFALLING       (1 << 0)

#define TPS_KEYP_COR                     (1 << 2)
#define TPS_KEYP_PENDDIS                 (1 << 1)
#define TPS_KEYP_EXCLEN1                 (1 << 0)
          
/* 
 * TPS LED module
 * 8 bit R/W register
 */

#define TPS_LEDEN     0x000000EE

/* 
 * TPS PWMA module
 * 8 bit R/W register
 */

#define TPS_PWMAON     0x000000F1
#define TPS_PWMAOFF    0x000000F2

/* 
 * TPS PWMB module
 * 8 bit R/W register
 */

#define TPS_PWMBON     0x000000F1
#define TPS_PWMBOFF    0x000000F2

/*
 * This section is dedicated to the TPS65950
 * I2C Address group 2 (0x49) TPS_I2C_ADDRESS_ID2 
 */

/* base addresses of the TPS modules in ADDRESS_ID2 (0x49)*/
 
#define TPS_AV_BASE         0x00000001
#define TPS_TEST_REG_BASE   0x0000004C
#define TPS_PIH_BASE        0x00000081  
#define TPS_INTBR_BASE      0x00000085
#define TPS_GPIO_BASE       0x00000098
 
/* 
 * TPS audio voice register module
 * 8 bit R/W registers
 */

#define TPS_AV_CODEC_MODE        0x00000001
#define TPS_AV_OPTION            0x00000002
#define TPS_AV_MICBIAS_CTL       0x00000004
#define TPS_AV_ANAMICL           0x00000005
#define TPS_AV_ANAMICR           0x00000006
#define TPS_AV_AVADC_CTL         0x00000007
#define TPS_AV_ADCMICSEL         0x00000008
#define TPS_AV_DIGMIXING         0x00000009
#define TPS_AV_ATXL1PGA          0x0000000A
#define TPS_AV_ATXR1PGA          0x0000000B
#define TPS_AV_AVTXL2PGA         0x0000000C
#define TPS_AV_AVTXR2PGA         0x0000000D
#define TPS_AV_AUDIO_IF          0x0000000E
#define TPS_AV_VOICE_IF          0x0000000F
#define TPS_AV_ARXR1PGA          0x00000010
#define TPS_AV_ARXL1PGA          0x00000011
#define TPS_AV_ARXR2PGA          0x00000012
#define TPS_AV_ARXL2PGA          0x00000013
#define TPS_AV_VRXPGA            0x00000014
#define TPS_AV_VSTPGA            0x00000015
#define TPS_AV_VRX2ARXPGA        0x00000016
#define TPS_AV_AVDAC_CTL         0x00000017
#define TPS_AV_ARX2VTXPGA        0x00000018
#define TPS_AV_ARXL1_APGA_CTL    0x00000019
#define TPS_AV_ARXR1_APGA_CTL    0x0000001A
#define TPS_AV_ARXL2_APGA_CTL    0x0000001B
#define TPS_AV_ARXR2_APGA_CTL    0x0000001C
#define TPS_AV_ATX2ARXPGA        0x0000001D
#define TPS_AV_BT_IF             0x0000001E
#define TPS_AV_BTPGA             0x0000001F
#define TPS_AV_BTSTPGA           0x00000020
#define TPS_AV_EAR_CTL           0x00000021
#define TPS_AV_HS_SEL            0x00000022
#define TPS_AV_HS_GAIN_SET       0x00000023
#define TPS_AV_HS_POPN_SET       0x00000024
#define TPS_AV_PREDL_CTL         0x00000025
#define TPS_AV_PREDR_CTL         0x00000026
#define TPS_AV_PRECKL_CTL        0x00000027
#define TPS_AV_PRECKR_CTL        0x00000028
#define TPS_AV_HFL_CTL           0x00000029
#define TPS_AV_HFR_CTL           0x0000002A
#define TPS_AV_ALC_CTL           0x0000002B
#define TPS_AV_ALC_SET1          0x0000002C
#define TPS_AV_ALC_SET2          0x0000002D
#define TPS_AV_BOOST_CTL         0x0000002E
#define TPS_AV_SOFTVOL_CTL       0x0000002F
#define TPS_AV_DTMF_FREQSEL      0x00000030
#define TPS_AV_DTMF_TONEXT1H     0x00000031
#define TPS_AV_DTMF_TONEXT1L     0x00000032
#define TPS_AV_DTMF_TONEXT2H     0x00000033
#define TPS_AV_DTMF_TONEXT2L     0x00000034
#define TPS_AV_DTMF_TONOFF       0x00000035
#define TPS_AV_DTMF_WANONOFF     0x00000036
#define TPS_AV_I2S_RX_SCRAMBLE_H 0x00000037
#define TPS_AV_I2S_RX_SCRAMBLE_M 0x00000038
#define TPS_AV_I2S_RX_SCRAMBLE_L 0x00000039
#define TPS_AV_APLL_CTL          0x0000003A
#define TPS_AV_DTMF_CTL          0x0000003B
#define TPS_AV_DTMF_PGA_CTL2     0x0000003C
#define TPS_AV_DTMF_PGA_CTL1     0x0000003D
#define TPS_AV_MISC_SET_1        0x0000003E
#define TPS_AV_PCMBTMUX          0x0000003F
#define TPS_AV_RX_PATH_SEL       0x00000043
#define TPS_AV_VDL_APGA_CTL      0x00000044
#define TPS_AV_VIBRA_CTL         0x00000045
#define TPS_AV_VIBRA_SET         0x00000046
#define TPS_AV_ANAMIC_GAIN       0x00000048
#define TPS_AV_MISC_SET_2        0x00000049

/* 
 * TPS Test register module
 * 8 bit R/W registers
 */

#define TPS_AUDIO_TEST_CTL   0x0000004C
#define TPS_INT_TEST_CTL     0x0000004D
#define TPS_DAC_ADC_TEST_CTL 0x0000004E
#define TPS_RXTX_TRIM_IB     0x0000004F
#define TPS_CLD_CONTROL      0x00000050
#define TPS_CLD_MODE_TIMING  0x00000051
#define TPS_CLD_TRIM_RAMP    0x00000052
#define TPS_CLD_TESTV_CTL    0x00000053
#define TPS_APLL_TEST_CTL    0x00000054
#define TPS_APLL_TEST_DIV    0x00000055
#define TPS_APLL_TEST_CTL2   0x00000056
#define TPS_APLL_TEST_CUR    0x00000057
#define TPS_DIGMIC_BIAS1_CTL 0x00000058
#define TPS_DIGMIC_BIAS2_CTL 0x00000059

/* 
 * TPS Test register module
 * 8 bit R-only registers
 */

#define TPS_RX_OFFSET_VOICE    0x0000005A
#define TPS_RX_OFFSET_AL1      0x0000005B
#define TPS_RX_OFFSET_AR1      0x0000005C
#define TPS_RX_OFFSET_AL2      0x0000005D
#define TPS_RX_OFFSET_AR2      0x0000005E
#define TPS_OFFSET1            0x0000005F
#define TPS_OFFSET2            0x00000060

/*
 * TPS PIH primary interrupt handler module 
 * 8 bit RW interrupt registers
 */

#define TPS_PIH_ISR_P1 0x00000081 
#define TPS_PIH_ISR_P2 0x00000082
#define TPS_PIH_SIR    0x00000083 

/* 
 * stores active block number of interrupt. 
 * Tells the host which subsystem SIH_ISRx register to read 
 */

/* bit fields (N = 1 or 2)*/

#define TPS_PIH_PN7                  (1 << 7)
#define TPS_PIH_PN6                  (1 << 6)
#define TPS_PIH_PN5                  (1 << 5)
#define TPS_PIH_PN4                  (1 << 4)
#define TPS_PIH_PN3                  (1 << 3)
#define TPS_PIH_PN2                  (1 << 2)
#define TPS_PIH_PN1                  (1 << 1)
#define TPS_PIH_PN0                  (1 << 0)

#define TPS_PIH_PN_USB        (1 << 4)
#define TPS_PIH_PN_MADC       (1 << 3)                                   
#define TPS_PIH_PN_BCI        (1 << 2)   
#define TPS_PIH_PN_KEYP       (1 << 1)                      
#define TPS_PIH_PN_GPIO       (1 << 0) 

#define TPS_PIH_SIR5                 (1 << 5)
#define TPS_PIH_SIR4                 (1 << 4)
#define TPS_PIH_SIR3                 (1 << 3)
#define TPS_PIH_SIR2                 (1 << 2)
#define TPS_PIH_SIR1                 (1 << 1)
#define TPS_PIH_SIR0                 (1 << 0)

/* 
 * TPS INTBR module
 * 8 bit R/W (except where indicated as R-only) registers
 */

#define TPS_INTBR_IDCODE_7_0       0x00000085 /* R-only */
#define TPS_INTBR_IDCODE_15_8      0x00000086 /* R-only */
#define TPS_INTBR_IDCODE_23_16     0x00000087 /* R-only */
#define TPS_INTBR_IDCODE_31_24     0x00000088 /* R-only */
#define TPS_INTBR_DIEID_7_0        0x00000098 /* R-only */
#define TPS_INTBR_DIEID_15_8       0x0000008A /* R-only */
#define TPS_INTBR_DIEID_23_16      0x0000008B /* R-only */
#define TPS_INTBR_DIEID_31_24      0x0000008C /* R-only */
#define TPS_INTBR_DIEID_39_32      0x0000008D /* R-only */
#define TPS_INTBR_DIEID_47_40      0x0000008E /* R-only */
#define TPS_INTBR_DIEID_55_48      0x0000008F /* R-only */
#define TPS_INTBR_DIEID_63_56      0x00000090 /* R-only */
#define TPS_INTBR_GPBR1            0x00000091
#define TPS_INTBR_PMBR1            0x00000092
#define TPS_INTBR_PMBR2            0x00000093
#define TPS_INTBR_GPPUPDCTR1       0x00000094
#define TPS_INTBR_GPPUPDCTR2       0x00000095
#define TPS_INTBR_GPPUPDCTR3       0x00000096
#define TPS_INTBR_UNLOCK_TEST_REG  0x00000097

/* 
 * TPS GPIO module
 * 8 bit R/W (except where indicated as R-only) registers
 */

#define TPS_GPIODATAIN1       0x00000098 /* R-only */
#define TPS_GPIODATAIN2       0x00000099 /* R-only */
#define TPS_GPIODATAIN3       0x0000009A /* R-only */
#define TPS_GPIODATADIR1      0x0000009B
#define TPS_GPIODATADIR2      0x0000009C
#define TPS_GPIODATADIR3      0x0000009D
#define TPS_GPIODATAOUT1      0x0000009E
#define TPS_GPIODATAOUT2      0x0000009F
#define TPS_GPIODATAOUT3      0x000000A0
#define TPS_CLEARGPIODATAOUT1 0x000000A1
#define TPS_CLEARGPIODATAOUT2 0x000000A2
#define TPS_CLEARGPIODATAOUT3 0x000000A3
#define TPS_SETGPIODATAOUT1   0x000000A4
#define TPS_SETGPIODATAOUT2   0x000000A5
#define TPS_SETGPIODATAOUT3   0x000000A6
#define TPS_GPIO_DEBEN1       0x000000A7
#define TPS_GPIO_DEBEN1       0x000000A7
#define TPS_GPIO_DEBEN3       0x000000A9
#define TPS_GPIO_CTRL         0x000000AA
#define TPS_GPIOPUPDCTR1      0x000000AB
#define TPS_GPIOPUPDCTR2      0x000000AC
#define TPS_GPIOPUPDCTR3      0x000000AD
#define TPS_GPIOPUPDCTR4      0x000000AE
#define TPS_GPIOPUPDCTR5      0x000090AF
#define TPS_GPIO_TEST         0x000000B0
#define TPS_GPIO_ISR1A        0x000000B1
#define TPS_GPIO_ISR2A        0x000000B2
#define TPS_GPIO_ISR3A        0x000000B3
#define TPS_GPIO_IMR1A        0x000000B4
#define TPS_GPIO_IMR2A        0x000000B5
#define TPS_GPIO_IMR3A        0x000000B6
#define TPS_GPIO_ISR1B        0x000000B7
#define TPS_GPIO_ISR2B        0x000000B8
#define TPS_GPIO_ISR3B        0x000000B9
#define TPS_GPIO_IMR1B        0x000000BA
#define TPS_GPIO_IMR2B        0x000000BB
#define TPS_GPIO_IMR3B        0x000000BC
#define TPS_GPIO_EDR1         0x000000C0
#define TPS_GPIO_EDR2         0x000000C1
#define TPS_GPIO_EDR3         0x000000C2
#define TPS_GPIO_EDR4         0x000000C3
#define TPS_GPIO_EDR5         0x000000C4
#define TPS_GPIO_SIH_CTRL     0x000000C5

/* GPIO register bit mask definitions */

#define TPS_GPIO7_ISRX                 (1 << 7)
#define TPS_GPIO6_ISRX                 (1 << 6)
#define TPS_GPIO5_ISRX                 (1 << 5)
#define TPS_GPIO4_ISRX                 (1 << 4)
#define TPS_GPIO3_ISRX                 (1 << 3)
#define TPS_GPIO2_ISRX                 (1 << 2)
#define TPS_GPIO1_ISRX                 (1 << 1)
#define TPS_GPIO0_ISRX                 (1 << 0)
 
#define TPS_GPIO15_ISRX             (1 << 7)  
#define TPS_GPIO14_ISRX             (1 << 6) 
#define TPS_GPIO13_ISRX             (1 << 5) 
#define TPS_GPIO12_ISRX             (1 << 4) 
#define TPS_GPIO11_ISRX             (1 << 3) 
#define TPS_GPIO10_ISRX             (1 << 2) 
#define TPS_GPIO9_ISRX              (1 << 1) 
#define TPS_GPIO8_ISRX              (1 << 0) 

#define TPS_GPIO17_ISRX             (1 << 1)
#define TPS_GPIO16_ISRX             (1 << 0)

#define TPS_GPIO7_IMRX                 (1 << 7)
#define TPS_GPIO6_IMRX                 (1 << 6)
#define TPS_GPIO5_IMRX                 (1 << 5)
#define TPS_GPIO4_IMRX                 (1 << 4)
#define TPS_GPIO3_IMRX                 (1 << 3)
#define TPS_GPIO2_IMRX                 (1 << 2)
#define TPS_GPIO1_IMRX                 (1 << 1)
#define TPS_GPIO0_IMRX                 (1 << 0)

#define TPS_GPIO15_IMRX              (1 << 7)
#define TPS_GPIO14_IMRX              (1 << 6)
#define TPS_GPIO13_IMRX              (1 << 5)
#define TPS_GPIO12_IMRX              (1 << 4)
#define TPS_GPIO11_IMRX              (1 << 3)
#define TPS_GPIO10_IMRX              (1 << 2)
#define TPS_GPIO9_IMRX               (1 << 1)
#define TPS_GPIO8_IMRX               (1 << 0)

#define TPS_GPIO17_IMRX             (1 << 1)
#define TPS_GPIO16_IMRX             (1 << 0)

#define TPS_GPIO3_RISING          (1 << 7)
#define TPS_GPIO3_FALLING         (1 << 6)
#define TPS_GPIO2_RISING          (1 << 5)
#define TPS_GPIO2_FALLING         (1 << 4)
#define TPS_GPIO_RISING           (1 << 3)
#define TPS_GPIO1_FALLING         (1 << 2) 
#define TPS_GPIO0_RISING          (1 << 1)
#define TPS_GPIO0_FALLING         (1 << 0)

#define TPS_GPIO7_RISING          (1 << 7)
#define TPS_GPIO7_FALLING         (1 << 6)
#define TPS_GPIO6_RISING          (1 << 5)
#define TPS_GPIO6_FALLING         (1 << 4)
#define TPS_GPIO5_RISING          (1 << 3)
#define TPS_GPIO5_FALLING         (1 << 2)
#define TPS_GPIO4_RISING          (1 << 1)
#define TPS_GPIO4_FALLING         (1 << 0)

#define TPS_GPIO11_RISING          (1 << 7)
#define TPS_GPIO11_FALLING         (1 << 6)
#define TPS_GPIO10_RISING          (1 << 5)
#define TPS_GPIO10_FALLING         (1 << 4)
#define TPS_GPIO9_RISING           (1 << 3)
#define TPS_GPIO9_FALLING          (1 << 2)
#define TPS_GPIO8_RISING           (1 << 1)
#define TPS_GPIO8_FALLING          (1 << 0)

#define TPS_GPIO15_RISING          (1 << 7)
#define TPS_GPIO15_FALLING         (1 << 6)
#define TPS_GPIO14_RISING          (1 << 5)
#define TPS_GPIO14_FALLING         (1 << 4)
#define TPS_GPIO13_RISING          (1 << 3)
#define TPS_GPIO13_FALLING         (1 << 2)
#define TPS_GPIO12_RISING          (1 << 1)
#define TPS_GPIO12_FALLING         (1 << 0)

#define TPS_GPIO17_RISING          (1 << 3)
#define TPS_GPIO17_FALLING         (1 << 2)
#define TPS_GPIO16_RISING          (1 << 1)
#define TPS_GPIO16_FALLING         (1 << 0)

#define TPS_GPIO_COR              (1 << 2)
#define TPS_GPIO_PENDDIS          (1 << 1)
#define TPS_GPIO_EXCLEN           (1 << 0)

/*
 * This section is dedicated to the TPS65950
 * I2C Address group 1 (0x48) TPS_I2C_ADDRESS_ID1 
 */

/* base address of the TPS module in ADDRESS_ID1 (0x48)*/

#define TPS_PM_USBPHY_BASE                 0x00000000

/* STS_HW_CONDITIONS bit masks */

#define TPS_PM_STS_HW_CONDITIONS_STS_USB    (1 << 2)
#define TPS_PM_STS_HW_CONDITIONS_STS_VBUS   (1 << 7)

/* TPS Power Resource States */

#define TPS_PM_PWR_RES_OFF                             0x00  
#define TPS_PM_PWR_RES_SLEEP                           0x08   
#define TPS_PM_PWR_RES_ACTIVE                          0x0E  
#define TPS_PM_PWR_RES_WRST                            0x0F  

/* USB PHY registers */

#define TPS_PM_USBPHY_VENDOR_ID_LO                0x00
#define TPS_PM_USBPHY_VENDOR_ID_HI                0x01
#define TPS_PM_USBPHY_PRODUCT_ID_LO               0x02
#define TPS_PM_USBPHY_PRODUCT_ID_HI               0x03
#define TPS_PM_USBPHY_FUNC_CTRL                   0x04
#define TPS_PM_USBPHY_FUNC_CTRL_SET               0x05
#define TPS_PM_USBPHY_FUNC_CTRL_CLR               0x06
#define TPS_PM_USBPHY_IFC_CTRL                    0x07
#define TPS_PM_USBPHY_IFC_CTRL_SET                0x08
#define TPS_PM_USBPHY_IFC_CTRL_CLR                0x09
#define TPS_PM_USBPHY_OTG_CTRL                    0x0A
#define TPS_PM_USBPHY_OTG_CTRL_SET                0x0B
#define TPS_PM_USBPHY_OTG_CTRL_CLR                0x0C
#define TPS_PM_USBPHY_USB_INT_EN_RISE             0x0D
#define TPS_PM_USBPHY_USB_INT_EN_RISE_SET         0x0E
#define TPS_PM_USBPHY_USB_INT_EN_RISE_CLR         0x0F
#define TPS_PM_USBPHY_USB_INT_EN_FALL             0x10
#define TPS_PM_USBPHY_USB_INT_EN_FALL_SET         0x11
#define TPS_PM_USBPHY_USB_INT_EN_FALL_CLR         0x12
#define TPS_PM_USBPHY_USB_INT_STS                 0x13
#define TPS_PM_USBPHY_USB_INT_LATCH               0x14
#define TPS_PM_USBPHY_DEBUG                       0x15
#define TPS_PM_USBPHY_SCRATCH_REG                 0x16
#define TPS_PM_USBPHY_SCRATCH_REG_SET             0x17
#define TPS_PM_USBPHY_SCRATCH_REG_CLR             0x18
#define TPS_PM_USBPHY_CARKIT_CTRL_SET             0x1A
#define TPS_PM_USBPHY_CARKIT_CTRL                 0x19
#define TPS_PM_USBPHY_CARKIT_CTRL_CLR             0x1B
#define TPS_PM_USBPHY_CARKIT_INT_DELAY            0x1C
#define TPS_PM_USBPHY_CARKIT_INT_EN               0x1D
#define TPS_PM_USBPHY_CARKIT_INT_EN_SET           0x1E
#define TPS_PM_USBPHY_CARKIT_INT_EN_CLR           0x1F
#define TPS_PM_USBPHY_CARKIT_INT_STS              0x20
#define TPS_PM_USBPHY_CARKIT_INT_LATCH            0x21
#define TPS_PM_USBPHY_CARKIT_PLS_CTRL             0x22
#define TPS_PM_USBPHY_CARKIT_PLS_CTRL_SET         0x23
#define TPS_PM_USBPHY_CARKIT_PLS_CTRL_CLR         0x24
#define TPS_PM_USBPHY_TRANS_POS_WIDTH             0x25
#define TPS_PM_USBPHY_TRANS_NEG_WIDTH             0x26
#define TPS_PM_USBPHY_RCV_PLTY_RECOVERY           0x27
#define TPS_PM_USBPHY_MCPC_CTRL                   0x30
#define TPS_PM_USBPHY_MCPC_CTRL_SET               0x31
#define TPS_PM_USBPHY_MCPC_CTRL_CLR               0x32
#define TPS_PM_USBPHY_MCPC_IO_CTRL                0x33
#define TPS_PM_USBPHY_MCPC_IO_CTRL_SET            0x34
#define TPS_PM_USBPHY_MCPC_IO_CTRL_CLR            0x35
#define TPS_PM_USBPHY_MCPC_CTRL2                  0x36
#define TPS_PM_USBPHY_MCPC_CTRL2_SET              0x37
#define TPS_PM_USBPHY_MCPC_CTRL2_CLR              0x38
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL             0x80
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL_SET         0x81
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL_CLR         0x82
#define TPS_PM_USBPHY_OTHER_IFC_CTRL              0x83
#define TPS_PM_USBPHY_OTHER_IFC_CTRL_SET          0x84
#define TPS_PM_USBPHY_OTHER_IFC_CTRL_CLR          0x85
#define TPS_PM_USBPHY_OTHER_INT_EN_RISE           0x86
#define TPS_PM_USBPHY_OTHER_INT_EN_RISE_SET       0x87
#define TPS_PM_USBPHY_OTHER_INT_EN_RISE_CLR       0x88
#define TPS_PM_USBPHY_OTHER_INT_EN_FALL           0x89
#define TPS_PM_USBPHY_OTHER_INT_EN_FALL_SET       0x8A
#define TPS_PM_USBPHY_OTHER_INT_EN_FALL_CLR       0x8B
#define TPS_PM_USBPHY_OTHER_INT_STS               0x8C
#define TPS_PM_USBPHY_OTHER_INT_LATCH             0x8D
#define TPS_PM_USBPHY_ID_INT_EN_RISE              0x8E
#define TPS_PM_USBPHY_ID_INT_EN_RISE_SET          0x8F
#define TPS_PM_USBPHY_ID_INT_EN_RISE_CLR          0x90
#define TPS_PM_USBPHY_ID_INT_EN_FALL              0x91
#define TPS_PM_USBPHY_ID_INT_EN_FALL_SET          0x92
#define TPS_PM_USBPHY_ID_INT_EN_FALL_CLR          0x93
#define TPS_PM_USBPHY_ID_INT_STS                  0x94
#define TPS_PM_USBPHY_ID_INT_LATCH                0x95
#define TPS_PM_USBPHY_ID_STATUS                   0x96
#define TPS_PM_USBPHY_CARKIT_SM_1_INT_EN          0x97
#define TPS_PM_USBPHY_CARKIT_SM_1_INT_EN_SET      0x98
#define TPS_PM_USBPHY_CARKIT_SM_1_INT_EN_CLR      0x99
#define TPS_PM_USBPHY_CARKIT_SM_1_INT_STS         0x9A
#define TPS_PM_USBPHY_CARKIT_SM_1_INT_LATCH       0x9B
#define TPS_PM_USBPHY_CARKIT_SM_2_INT_EN          0x9C
#define TPS_PM_USBPHY_CARKIT_SM_2_INT_EN_SET      0x9D
#define TPS_PM_USBPHY_CARKIT_SM_2_INT_EN_CLR      0x9E
#define TPS_PM_USBPHY_CARKIT_SM_2_INT_STS         0x9F
#define TPS_PM_USBPHY_CARKIT_SM_2_INT_LATCH       0xA0
#define TPS_PM_USBPHY_CARKIT_SM_CTRL              0xA1
#define TPS_PM_USBPHY_CARKIT_SM_CTRL_SET          0xA2
#define TPS_PM_USBPHY_CARKIT_SM_CTRL_CLR          0xA3
#define TPS_PM_USBPHY_CARKIT_SM_CMD               0xA4
#define TPS_PM_USBPHY_CARKIT_SM_CMD_SET           0xA5
#define TPS_PM_USBPHY_CARKIT_SM_CMD_CLR           0xA6
#define TPS_PM_USBPHY_CARKIT_SM_CMD_STS           0xA7
#define TPS_PM_USBPHY_CARKIT_SM_STATUS            0xA8
#define TPS_PM_USBPHY_CARKIT_SM_NEXT_STATUS       0xA9
#define TPS_PM_USBPHY_CARKIT_SM_ERR_STATUS        0xAA
#define TPS_PM_USBPHY_CARKIT_SM_CTRL_STATE        0xAB
#define TPS_PM_USBPHY_POWER_CTRL                  0xAC
#define TPS_PM_USBPHY_POWER_CTRL_SET              0xAD
#define TPS_PM_USBPHY_POWER_CTRL_CLR              0xAE
#define TPS_PM_USBPHY_OTHER_IFC_CTRL2             0xAF
#define TPS_PM_USBPHY_OTHER_IFC_CTRL2_SET         0xB0
#define TPS_PM_USBPHY_OTHER_IFC_CTRL2_CLR         0xB1
#define TPS_PM_USBPHY_REG_CTRL_EN                 0xB2
#define TPS_PM_USBPHY_REG_CTRL_EN_SET             0xB3
#define TPS_PM_USBPHY_REG_CTRL_EN_CLR             0xB4
#define TPS_PM_USBPHY_REG_CTRL_ERROR              0xB5
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL2            0xB8
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL2_SET        0xB9
#define TPS_PM_USBPHY_OTHER_FUNC_CTRL2_CLR        0xBA
#define TPS_PM_USBPHY_CARKIT_ANA_CTRL             0xBB
#define TPS_PM_USBPHY_CARKIT_ANA_CTRL_SET         0xBC
#define TPS_PM_USBPHY_CARKIT_ANA_CTRL_CLR         0xBD
#define TPS_PM_USBPHY_VBUS_DEBOUNCE               0xC0
#define TPS_PM_USBPHY_ID_DEBOUNCE                 0xC1
#define TPS_PM_USBPHY_TPH_DP_CON_MIN              0xC2
#define TPS_PM_USBPHY_TPH_DP_CON_MAX              0xC3
#define TPS_PM_USBPHY_TCR_DP_CON_MIN              0xC4
#define TPS_PM_USBPHY_TCR_DP_CON_MAX              0xC5
#define TPS_PM_USBPHY_TPH_DP_PD_SHORT             0xC6
#define TPS_PM_USBPHY_TPH_CMD_DLY                 0xC7
#define TPS_PM_USBPHY_TPH_DET_RST                 0xC8
#define TPS_PM_USBPHY_TPH_AUD_BIAS                0xC9
#define TPS_PM_USBPHY_TCR_UART_DET_MIN            0xCA
#define TPS_PM_USBPHY_TCR_UART_DET_MAX            0xCB
#define TPS_PM_USBPHY_TPH_ID_INT_PW               0xCD
#define TPS_PM_USBPHY_TACC_ID_INT_WAIT            0xCE
#define TPS_PM_USBPHY_TACC_ID_INT_PW              0xCF
#define TPS_PM_USBPHY_TPH_CMD_WAIT                0xD0
#define TPS_PM_USBPHY_TPH_ACK_WAIT                0xD1
#define TPS_PM_USBPHY_TPH_DP_DISC_DET             0xD2
#define TPS_PM_USBPHY_VBAT_TIMER                  0xD3
#define TPS_PM_USBPHY_CARKIT_4W_DEBUG             0xE0
#define TPS_PM_USBPHY_CARKIT_5W_DEBUG             0xE1
#define TPS_PM_USBPHY_TEST_CTRL_SET               0xEA
#define TPS_PM_USBPHY_TEST_CTRL_CLR               0xEB
#define TPS_PM_USBPHY_TEST_CARKIT_SET             0xEC
#define TPS_PM_USBPHY_TEST_CARKIT_CLR             0xED
#define TPS_PM_USBPHY_TEST_POWER_SET              0xEE
#define TPS_PM_USBPHY_TEST_POWER_CLR              0xEF
#define TPS_PM_USBPHY_TEST_ULPI                   0xF0
#define TPS_PM_USBPHY_TXVR_EN_TEST_SET            0xF2
#define TPS_PM_USBPHY_TXVR_EN_TEST_CLR            0xF3
#define TPS_PM_USBPHY_VBUS_EN_TEST                0xF4
#define TPS_PM_USBPHY_ID_EN_TEST                  0xF5
#define TPS_PM_USBPHY_PSM_EN_TEST_SET             0xF6
#define TPS_PM_USBPHY_PSM_EN_TEST_CLR             0xF7
#define TPS_PM_USBPHY_PHY_TRIM_CTRL               0xFC
#define TPS_PM_USBPHY_PHY_PWR_CTRL                0xFD
#define TPS_PM_USBPHY_PHY_CLK_CTRL                0xFE
#define TPS_PM_USBPHY_PHY_CLK_CTRL_STS            0xFF

/* TPS_PM_USBPHY_PHY_CLK_CTRL bit masks */

#define TPS_PM_USBPHY_PHY_CLK_CTRL_CLOCKGATING_EN             (1 << 2)
#define TPS_PM_USBPHY_PHY_CLK_CTRL_CLK32_EN                   (1 << 1)
#define TPS_PM_USBPHY_PHY_CLK_CTRL_REQ_PHY_DPLL_CLK           (1 << 0)

/* TPS_PM_USBPHY_PHY_CLK_CTRL_STS bit masks */

#define TPS_PM_USBPHY_PHY_CLK_CTRL_STS_PHY_DPLL_LOCK          (1 << 0)

/* TPS_PM_USBPHY_PHY_PWR_CTRL bit masks */

#define TPS_PM_USBPHY_PWR_CTRL_PHYPWD                         (1 << 0)

/* TPS_PM_USBPHY_POWER_CTRL bit masks */

#define TPS_PM_USBPHY_POWER_CTRL_OTG_EN                       (1 << 5)

/* VUSB_DEDICATED1 bit masks */

#define TPS_PM_VUSB_DEDICATED1_WKUPCOMP_EN                    (1 << 4)
#define TPS_PM_VUSB_DEDICATED1_SW2VBUS                        (1 << 3)
#define TPS_PM_VUSB_DEDICATED1_SW2VBAT                        (1 << 2)
#define TPS_PM_VUSB_DEDICATED1_G1                             (1 << 1)
#define TPS_PM_VUSB_DEDICATED1_G0                             (1 << 0)

/* VUSB_DEDICATED2 bit masks */

#define TPS_PM_VUSB_DEDICATED2_VUSB3V1_SLEEP                  (1 << 3)

/* TPS register access macros */

#define TPS_PM_MASTER_WRITE(uOffset, uVal)                          \
        omapTpsRegWrite8(TPS_PM_MASTER_I2C_ADDR,                    \
                        (uOffset),                                  \
                        (uVal))

#define TPS_PM_MASTER_READ(uOffset, pVal)                           \
        omapTpsRegRead8(TPS_PM_MASTER_I2C_ADDR,                     \
                        (uOffset),                                  \
                        (pVal))

#define TPS_PM_RECEIVER_WRITE(uOffset, uVal)                        \
        omapTpsRegWrite8(TPS_PM_RECEIVER_I2C_ADDR,                  \
                        (uOffset),                                  \
                        (uVal))

#define TPS_PM_RECEIVER_READ(uOffset, pVal)                         \
        omapTpsRegRead8(TPS_PM_RECEIVER_I2C_ADDR,                   \
                        (uOffset),                                  \
                        (pVal))

void tps65950EnableSR ( void );     /* enable smart reflex */
void tps65950EnableReset ( void );  /* enable the 8-second reset button */
STATUS tps65950Unprotect            /* unprotect the protected registers */
    ( 
    UINT8 action  /* lock or unlock cfg registers, tst registers or both */
    );

/* write any 8 bit TPS register */

STATUS omapTpsRegWrite8
    (
    UINT8   uModule,
    UINT8   uRegAddr,
    UINT8   uVal
    );

/* read any 8 bit TPS register */

STATUS omapTpsRegRead8
    (
    UINT8   uModule,
    UINT8   uRegAddr,
    UINT8 * pVal
    );
	
#ifdef __cplusplus
    }
#endif

#endif /* if tps65950 included */
