/* vxbHpetLib.h - vxbus high performance event timer interfaces header file */

/*
 * Copyright (c) 2007,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,30oct10,j_l  Fix LP64 HPET register mapping (Fix for WIND00236223).
01a,07aug07,scm  written.
*/

/*
DESCRIPTION

This library provides the high performance event timer (HPET) specific 
definitiions.

*/

#ifndef _INC_vxbHpetLibH
#define _INC_vxbHpetLibH

#ifdef __cplusplus
extern "C" {
#endif

/* IA-PC HPET - High Precision Event Timers
 *
 * On-Multiprocessing IA-32 platforms this gives us a
 * 64-bit free running up-counter for Time Stamping Applications.
 *
 * This provides a time-base that is insensitive to clock frequency
 * drifts on individual CPU's on an N-way MP system.
 */

#define IA_TIMESTAMP_NAME       "iaTimestamp"

/* The HPET LPC Bridge function resides in PCI Device:31, Function:0 */

#define LPC_BUSNO               0x00
#define LPC_DEVNO               0x1F
#define LPC_FUNCNO              0x00

#define LPC_GEN_CNTRL           0xD0       /* 6300ESB ICH General Control Reg */

#define LPC_RCBA_REG            0xF0       /* ICH7 Root Complex Base Addr Reg */

#define RCBA_ADDR_MSK           0xFFFFC000 /* ICH7 RCBA Address Mask */
#define RCBA_ADDR_ENBL          0x00000001 /* ICH7 RCBA Enable Bit */
#define RCBA_MEM_ADDR_RNG       0x4000     /* ICH7 RCBA Address Block */

#define HPTC_REG_OFFSET         0x00003404 /* ICH7 HPTC Register Offset */
#define HPTC_REG_MSK            0xFFFFFFFE /* ICH7 HPTC Register Mask */
#define HPTC_ADDR_ENBL          0x00000080 /* ICH7 HPTC Address Enable Bit */
	
/* This bit enables the ICH to decode the High Performance Event Timer
 * memory Address Range...
 *
 * The registers associated with these timers sre mapped to memory space
 * much like the I/O APIC. The timer register space is 1024 bytes.
 */

#define HPET_ADDR_ENABLE        0x00020000

/* 1 of 4 possible memory address ranges for the High Performance
 * Event Timer functionality...
 */

#define HPET_ADDR_SEL_MASK      0x00018000

#define HPET_ADDR_SEL_00        0xFED00000
#define HPET_ADDR_SEL_01        0xFED01000
#define HPET_ADDR_SEL_02        0xFED02000
#define HPET_ADDR_SEL_03        0xFED03000

#define HPET_MEM_ADDR_RNG       0x4000

/* HPET Memory-mapped Register Offsets */

/* General Capabilities and ID Register
 * Offset: 000-007h, RO, 64-bit
 */

#define HPET_GEN_CAP_OFF        0x0000

#define HPET_CNTR_PER_CAP_MSK   0xffffffff00000000
#define HPET_VNDR_ID_CAP_MSK    0x00000000ffff0000
#define HPET_LEG_RT_CAP_MSK     0x0000000000008000
#define HPET_CNT_SZ_CAP_MSK     0x0000000000002000
#define HPET_NUM_TIM_CAP_MSK    0x0000000000001f00
#define HPET_REV_ID_CAP_MSK     0x00000000000000ff

/* General Configuration Register
 * Offset: 010-017h, RW, 64-bit
 */

#define HPET_GEN_CON_OFF        0x0010

#define HPET_LEG_RT_CNF_MSK     0x0000000000000002
#define HPET_EN_CNF_MSK         0x0000000000000001

/* General Interrupt Status Register
 * Offset: 020-027h, RW, 64-bit
 */

#define HPET_GEN_INT_STS_OFF    0x0020

#define HPET_T02_INT_STS_MSK    0x0000000000000004
#define HPET_T01_INT_STS_MSK    0x0000000000000002
#define HPET_T00_INT_STS_MSK    0x0000000000000001
                                                                                
/* Main counter Value Register
 * Offset: 0F0-0F7h, RW, 64-bit
 */

#define HPET_MN_CNTR_OFF        0x00F0

/* Timer 0 Config/Capabilities Register
 * Offset: 100-107h, RW, 64-bit
 *
 * Timer 0 Comparator Value Register
 * Offset: 108-10Fh, RW, 64-bit
 */

#define HPET_T0_CONF_OFF        0x0100
#define HPET_T0_COMP_OFF        0x0108

/* Timer 1 Config/Capabilities Register
 * Offset: 120-127h, RW, 64-bit
 *
 * Timer 1 Comparator Value Register
 * Offset: 128-12Fh, RW, 64-bit
 */

#define HPET_T1_CONF_OFF        0x0120
#define HPET_T1_COMP_OFF        0x0128

/* Timer 2 Config/Capabilities Register
 * Offset: 140-147h, RW, 64-bit
 *
 * Timer 2 Comparator Value Register
 * Offset: 148-14Fh, RW, 64-bit
 */

#define HPET_T2_CONF_OFF        0x0140
#define HPET_T2_COMP_OFF        0x0148
                                                                                
/* Timer Config/Capabilities Masks */

#define HPET_TIMERn_INT_ROUT_CAP_MSK    0xffffffff00000000
#define HPET_TIMERn_FSB_INT_DEL_CAP_MSK 0x0000000000008000
#define HPET_TIMERn_FSB_EN_CNF_MSK      0x0000000000004000
#define HPET_TIMERn_INT_ROUT_CNF_MSK    0x0000000000003e00
#define HPET_TIMERn_32MODE_CNF_MSK      0x0000000000000100
#define HPET_TIMERn_VAL_SET_CNF_MSK     0x0000000000000040
#define HPET_TIMERn_SIZE_CAP_MSK        0x0000000000000020
#define HPET_TIMERn_PER_INT_CAP_MSK     0x0000000000000010
#define HPET_TIMERn_TYPE_CNF_MSK        0x0000000000000008
#define HPET_TIMERn_INT_ENB_CNF_MSK     0x0000000000000004
#define HPET_TIMERn_INT_TYPE_CNF_MSK    0x0000000000000002

/* IA-32 dedicated SMP Timestamp defines used in vxbIntelTimestamp.c,
 * and elsewhere...
 */

/* IA-32 SMP Timestamp based off of a 64-bit free running counter.
 * IA-32 will be using HPET Timer #0, using default address range
 * HPET_ADDR_SEL_00 (0xFED00000)...
 */

#define HPET_TIMESTAMP          (HPET_ADDR_SEL_00)

#ifdef  _WRS_CONFIG_LP64
IMPORT  ULONG                    hpetTimestampAddr;
#define HP_TS_GEN_CAP           (hpetTimestampAddr + HPET_GEN_CAP_OFF)
#define HP_TS_GEN_CON           (hpetTimestampAddr + HPET_GEN_CON_OFF)
#define HP_TS_GEN_INT_STS       (hpetTimestampAddr + HPET_GEN_INT_STS_OFF)
#define HP_TS_MN_CNTR           (hpetTimestampAddr + HPET_MN_CNTR_OFF)
#define HP_TS_T0_CONF           (hpetTimestampAddr + HPET_T0_CONF_OFF)
#define HP_TS_T0_COMP           (hpetTimestampAddr + HPET_T0_COMP_OFF)
#else
#define HP_TS_GEN_CAP           (HPET_TIMESTAMP + HPET_GEN_CAP_OFF)
#define HP_TS_GEN_CON           (HPET_TIMESTAMP + HPET_GEN_CON_OFF)
#define HP_TS_GEN_INT_STS       (HPET_TIMESTAMP + HPET_GEN_INT_STS_OFF)
#define HP_TS_MN_CNTR           (HPET_TIMESTAMP + HPET_MN_CNTR_OFF)
#define HP_TS_T0_CONF           (HPET_TIMESTAMP + HPET_T0_CONF_OFF)
#define HP_TS_T0_COMP           (HPET_TIMESTAMP + HPET_T0_COMP_OFF)
#endif  /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbHpetLibH */

