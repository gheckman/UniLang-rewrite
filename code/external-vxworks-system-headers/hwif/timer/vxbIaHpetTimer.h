/* vxbIaHpetTimer.h - header for the Intel High Precision Event Timer (HPET) */

/*
 * Copyright (c) 2011, 2013, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,31jan14,jb   VXW6-1845 - Error in HPET reading
01h,28jan14,jb   VXW6-25700 - patch for WIND00406770 does not fix the problem
                 in aux timer
01g,25apr13,rbc  WIND00414401 - Changes to support Unified BSP.
01f,18mar13,jb   WIND00406770 - iaHpetTimerInt() -> wrong calculation of next
                 timeout
01e,07oct11,sem  WIND00310639 - Remove timer drift. Revise oneshot API.
01d,02aug11,sem  Fix HPET interrupts - WIND00287725
01c,22jul11,sem  Update timestamp name define
01b,14jul11,sem  Update 64-bit counter read
01a,05may11,sem  initial version
*/

#ifndef __INCvxbIaHpetTimerh
#define __INCvxbIaHpetTimerh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IA HPET - High Precision Event Timers
 *
 * On IA platforms this gives us a
 * 64-bit free running up-counter for Time Stamping Applications.
 *
 * This provides a time-base that is insensitive to clock frequency
 * drifts on individual CPU's on an N-way MP system.
 */

#define  IA_TIMESTAMP_NAME          "iaTimestamp"

#ifndef  IA_HPET_TIMER_NAME
#define  IA_HPET_TIMER_NAME         "iaHpetTimerDev"
#endif   /* IA_HPET_TIMER_NAME */

#define IA_HPET_TIMER_CLK_FREQ       14318179

/* HPET timer IDs */

#define IA_HPET_TIMER0               0x0 /* Timer 0 Id */
#define IA_HPET_TIMER1               0x1 /* Timer 1 Id */
#define IA_HPET_TIMER2               0x2 /* Timer 2 Id */
#define IA_HPET_TIMER3               0x3 /* Timer 3 Id */
#define IA_HPET_TIMER4               0x4 /* Timer 4 Id */
#define IA_HPET_TIMER5               0x5 /* Timer 5 Id */
#define IA_HPET_TIMER6               0x6 /* Timer 6 Id */
#define IA_HPET_TIMER7               0x7 /* Timer 7 Id */
#define IA_HPET_TIMER_MAX            0x8 /* Max timer Ids */

/* HPET timer operational modes */

#ifdef _WRS_CONFIG_PWR_MGMT

/* Maintain Power Mgmt functionality */

#define IA_HPET_TIMER_MODE_PERIODIC      0x00 /* Periodic timer    */
#define IA_HPET_TIMER_MODE_ONESHOT32     0x01 /* 32-bit one-shot timer */
#define IA_HPET_TIMER_MODE_ONESHOT64     0x02 /* 64-bit one-shot timer */

#else

#define IA_HPET_TIMER_MODE_PERIODIC      0x01 /* Periodic timer    */
#define IA_HPET_TIMER_MODE_HW_PERIODIC   0x03 /* Timer supports H/W periodic */
                                              /* mode */
#define IA_HPET_TIMER_MODE_ONESHOT32     0x04 /* 32-bit one-shot timer */
#define IA_HPET_TIMER_MODE_ONESHOT64     0x08 /* 64-bit one-shot timer */

#endif /* _WRS_CONFIG_PWR_MGMT */

/* interrupt routing for HPET comparators */

#define INT_NUM_IA_HPET_TIMER0    0x14 /* Timer 0 interrupt    */
#define INT_NUM_IA_HPET_TIMER1    0x15 /* Timer 1 interrupt    */
#define INT_NUM_IA_HPET_TIMER2    0x16 /* Timer 2 interrupt    */
#define INT_NUM_IA_HPET_TIMER3    0x17 /* Timer 3 interrupt    */
#define INT_NUM_IA_HPET_TIMER4    0x18 /* Timer 4 interrupt    */
#define INT_NUM_IA_HPET_TIMER5    0x19 /* Timer 5 interrupt    */
#define INT_NUM_IA_HPET_TIMER6    0x1A /* Timer 6 interrupt    */
#define INT_NUM_IA_HPET_TIMER7    0x1B /* Timer 7 interrupt    */

/* The HPET LPC Bridge function resides in PCI Device:31, Function:0 */

#define LPC_BUSNO                  0x00
#define LPC_DEVNO                  0x1F
#define LPC_FUNCNO                 0x00
#define LPC_DID_6300ESB            0x25A1
#define LPC_DID_ICH5               0x24D0
#define LPC_GEN_CNTRL              0xD0       /* 6300ESB ICH General Control */
                                              /* Reg */

#define LPC_RCBA_REG               0xF0       /* ICH7 Root Complex Base Addr */
                                              /* Reg */

#define RCBA_REG_BASE              1
#define RCBA_ADDR_MSK              0xFFFFC000 /* ICH7 RCBA Address Mask */
#define RCBA_ADDR_ENBL             0x00000001 /* ICH7 RCBA Enable Bit */
#define RCBA_MEM_ADDR_RNG          0x4000     /* ICH7 RCBA Address Block */

#define IA_HPETTC_REG_OFFSET       0x00003404 /* ICH7 HPTC Register Offset */
#define IA_HPETTC_REG_MSK          0xFFFFFFFE /* ICH7 HPTC Register Mask */
#define IA_HPETTC_ADDR_ENBL        0x00000080 /* ICH7 HPTC Address Enable Bit */

/*
 * This bit enables the ICH to decode the High Performance Event Timer
 * memory Address Range...
 *
 * The registers associated with these timers are mapped to memory space
 * much like the I/O APIC. The timer register space is 1024 bytes.
 */

#define IA_HPET_ADDR_ENABLE        0x00020000

/*
 * 1 of 4 possible memory address ranges for the High Performance
 * Event Timer functionality...
 */

#define IA_HPET_ADDR_SEL_MASK      0x00018000

#define IA_HPET_ADDR_SEL_00        0xFED00000
#define IA_HPET_ADDR_SEL_01        0xFED01000
#define IA_HPET_ADDR_SEL_02        0xFED02000
#define IA_HPET_ADDR_SEL_03        0xFED03000

#define IA_HPET_MEM_ADDR_RNG       0x4000

/* HPET Memory-mapped Register Offsets */

/*
 * General Capabilities and ID Register
 * Offset: 000-007h, RO, 64-bit
 */

#define IA_HPET_GEN_CAP_OFF        0x0000

#define IA_HPET_CNTR_PER_CAP_MSK   0xffffffff00000000
#define IA_HPET_VNDR_ID_CAP_MSK    0x00000000ffff0000
#define IA_HPET_LEG_RT_CAP_MSK     0x0000000000008000
#define IA_HPET_CNT_SZ_CAP_MSK     0x0000000000002000
#define IA_HPET_NUM_TIM_CAP_MSK    0x0000000000001f00
#define IA_HPET_REV_ID_CAP_MSK     0x00000000000000ff

/*
 * General Configuration Register
 * Offset: 010-017h, RW, 64-bit
 */

#define IA_HPET_GEN_CON_OFF        0x0010

#define IA_HPET_LEG_RT_CNF_MSK     0x0000000000000002
#define IA_HPET_EN_CNF_MSK         0x0000000000000001

/*
 * General Interrupt Status Register
 * Offset: 020-027h, RW, 64-bit
 */

#define IA_HPET_INT_STS_OFF        0x0020

#define IA_HPET_T00_INT_STS_MSK    0x0000000000000001
#define IA_HPET_T01_INT_STS_MSK    0x0000000000000002
#define IA_HPET_T02_INT_STS_MSK    0x0000000000000004

/*
 * Main counter Value Register
 * Offset: 0F0-0F7h, RW, 64-bit
 */

#define IA_HPET_MN_CNTR_OFF        0x00F0

/*
 * Timer Config/Capabilities Registers
 * Offset: 20h, relative to each register
 */

#define IA_HPET_TIMER_CONF_OFF     0x0020

/*
 * Timer Comparator Registers
 * Offset: 20h, relative to each comparator
 */

#define IA_HPET_TIMER_COMP_OFF     0x0020

/*
 * Timer MSI Configuration Registers
 * Offset: 20h, relative to each comparator
 */

#define IA_HPET_TIMER_MSI_OFF      0x0020

/*
 * Timer Config/Capabilities Register
 * Offset: 100-107h, RW, 64-bit
 *
 * Timer Comparator Value Register
 * Offset: 108-10Fh, RW, 64-bit
 *
 * Timer MSI Config Value Register
 * Offset: 110-10Fh, RW, 64-bit
 */

#define IA_HPET_T0_CONF_OFF        0x0100
#define IA_HPET_T0_COMP_OFF        0x0108
#define IA_HPET_T0_MSI_OFF         0x0110

#define IA_HPET_T1_CONF_OFF        0x0120
#define IA_HPET_T1_COMP_OFF        0x0128
#define IA_HPET_T1_MSI_OFF         0x0130

#define IA_HPET_T2_CONF_OFF        0x0140
#define IA_HPET_T2_COMP_OFF        0x0148
#define IA_HPET_T2_MSI_OFF         0x0150

#define IA_HPET_T3_CONF_OFF        0x0160
#define IA_HPET_T3_COMP_OFF        0x0168
#define IA_HPET_T3_MSI_OFF         0x0170

#define IA_HPET_T4_CONF_OFF        0x0180
#define IA_HPET_T4_COMP_OFF        0x0188
#define IA_HPET_T4_MSI_OFF         0x0180

#define IA_HPET_T5_CONF_OFF        0x01a0
#define IA_HPET_T5_COMP_OFF        0x01a8
#define IA_HPET_T5_MSI_OFF         0x01b0

#define IA_HPET_T6_CONF_OFF        0x01c0
#define IA_HPET_T6_COMP_OFF        0x01c8
#define IA_HPET_T6_MSI_OFF         0x01d0

#define IA_HPET_T7_CONF_OFF        0x01e0
#define IA_HPET_T7_COMP_OFF        0x01e8
#define IA_HPET_T7_MSI_OFF         0x01f0

/* Timer Config/Capabilities Masks */

#define IA_HPET_TIMERn_INT_ROUT_CAP_MSK    0xffffffff00000000
#define IA_HPET_TIMERn_MSI_INT_DEL_CAP_MSK 0x0000000000008000
#define IA_HPET_TIMERn_MSI_EN_CNF_MSK      0x0000000000004000
#define IA_HPET_TIMERn_INT_ROUT_CNF_MSK    0x0000000000003e00
#define IA_HPET_TIMERn_32MODE_CNF_MSK      0x0000000000000100
#define IA_HPET_TIMERn_VAL_SET_CNF_MSK     0x0000000000000040
#define IA_HPET_TIMERn_SIZE_CAP_MSK        0x0000000000000020
#define IA_HPET_TIMERn_PER_INT_CAP_MSK     0x0000000000000010
#define IA_HPET_TIMERn_TYPE_CNF_MSK        0x0000000000000008
#define IA_HPET_TIMERn_INT_ENB_CNF_MSK     0x0000000000000004
#define IA_HPET_TIMERn_INT_TYPE_CNF_MSK    0x0000000000000002

/*
 * IA Timestamp based off of a 64-bit free running counter
 * using default address range HPET_ADDR_SEL_00 (0xFED00000).
 * This address should be obtained from ACPI tables, however
 * the associated ACPI tables are initialized after the HPET timer
 * driver is instantiated by VxBus.
 */

#define IA_HPET_BASE_ADDR         (IA_HPET_ADDR_SEL_00)
#define IA_HPET_REG_BASE          (IA_HPET_GEN_CAP_OFF)

#ifndef  _WRS_CONFIG_LP64
IMPORT  UINT                       vxbIaHpetBaseAddr;

/* HPET register definitions */

#define IA_HPET_GEN_CAP           (IA_HPET_BASE_ADDR + IA_HPET_GEN_CAP_OFF)
#define IA_HPET_GEN_CON           (IA_HPET_BASE_ADDR + IA_HPET_GEN_CON_OFF)
#define IA_HPET_INT_STS           (IA_HPET_BASE_ADDR + IA_HPET_INT_STS_OFF)
#define IA_HPET_MN_CNTR           (IA_HPET_BASE_ADDR + IA_HPET_MN_CNTR_OFF)

#define IA_HPET_T0_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T0_CONF_OFF)
#define IA_HPET_T0_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T0_COMP_OFF)
#define IA_HPET_T0_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T0_MSI_OFF)

#define IA_HPET_T1_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T1_CONF_OFF)
#define IA_HPET_T1_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T1_COMP_OFF)
#define IA_HPET_T1_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T1_MSI_OFF)

#define IA_HPET_T2_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T2_CONF_OFF)
#define IA_HPET_T2_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T2_COMP_OFF)
#define IA_HPET_T2_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T2_MSI_OFF)

#define IA_HPET_T3_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T3_CONF_OFF)
#define IA_HPET_T3_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T3_COMP_OFF)
#define IA_HPET_T3_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T3_MSI_OFF)

#define IA_HPET_T4_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T4_CONF_OFF)
#define IA_HPET_T4_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T4_COMP_OFF)
#define IA_HPET_T4_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T4_MSI_OFF)

#define IA_HPET_T5_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T5_CONF_OFF)
#define IA_HPET_T5_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T5_COMP_OFF)
#define IA_HPET_T5_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T5_MSI_OFF)

#define IA_HPET_T6_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T6_CONF_OFF)
#define IA_HPET_T6_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T6_COMP_OFF)
#define IA_HPET_T6_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T6_MSI_OFF)

#define IA_HPET_T7_CONF           (IA_HPET_BASE_ADDR + IA_HPET_T7_CONF_OFF)
#define IA_HPET_T7_COMP           (IA_HPET_BASE_ADDR + IA_HPET_T7_COMP_OFF)
#define IA_HPET_T7_MSI            (IA_HPET_BASE_ADDR + IA_HPET_T7_MSI_OFF)

#else

IMPORT  ULONG                      vxbIaHpetBaseAddr;

#define IA_HPET_GEN_CAP           (vxbIaHpetBaseAddr + IA_HPET_GEN_CAP_OFF)
#define IA_HPET_GEN_CON           (vxbIaHpetBaseAddr + IA_HPET_GEN_CON_OFF)
#define IA_HPET_INT_STS           (vxbIaHpetBaseAddr + IA_HPET_INT_STS_OFF)
#define IA_HPET_MN_CNTR           (vxbIaHpetBaseAddr + IA_HPET_MN_CNTR_OFF)

#define IA_HPET_T0_CONF           (vxbIaHpetBaseAddr + IA_HPET_T0_CONF_OFF)
#define IA_HPET_T0_COMP           (vxbIaHpetBaseAddr + IA_HPET_T0_COMP_OFF)
#define IA_HPET_T0_MSI            (vxbIaHpetBaseAddr + IA_HPET_T0_MSI_OFF)

#define IA_HPET_T1_CONF           (vxbIaHpetBaseAddr + IA_HPET_T1_CONF_OFF)
#define IA_HPET_T1_COMP           (vxbIaHpetBaseAddr + IA_HPET_T1_COMP_OFF)
#define IA_HPET_T1_MSI            (vxbIaHpetBaseAddr + IA_HPET_T1_MSI_OFF)

#define IA_HPET_T2_CONF           (vxbIaHpetBaseAddr + IA_HPET_T2_CONF_OFF)
#define IA_HPET_T2_COMP           (vxbIaHpetBaseAddr + IA_HPET_T2_COMP_OFF)
#define IA_HPET_T2_MSI            (vxbIaHpetBaseAddr + IA_HPET_T2_MSI_OFF)

#define IA_HPET_T3_CONF           (vxbIaHpetBaseAddr + IA_HPET_T3_CONF_OFF)
#define IA_HPET_T3_COMP           (vxbIaHpetBaseAddr + IA_HPET_T3_COMP_OFF)
#define IA_HPET_T3_MSI            (vxbIaHpetBaseAddr + IA_HPET_T3_MSI_OFF)

#define IA_HPET_T4_CONF           (vxbIaHpetBaseAddr + IA_HPET_T4_CONF_OFF)
#define IA_HPET_T4_COMP           (vxbIaHpetBaseAddr + IA_HPET_T4_COMP_OFF)
#define IA_HPET_T4_MSI            (vxbIaHpetBaseAddr + IA_HPET_T4_MSI_OFF)

#define IA_HPET_T5_CONF           (vxbIaHpetBaseAddr + IA_HPET_T5_CONF_OFF)
#define IA_HPET_T5_COMP           (vxbIaHpetBaseAddr + IA_HPET_T5_COMP_OFF)
#define IA_HPET_T5_MSI            (vxbIaHpetBaseAddr + IA_HPET_T5_MSI_OFF)

#define IA_HPET_T6_CONF           (vxbIaHpetBaseAddr + IA_HPET_T6_CONF_OFF)
#define IA_HPET_T6_COMP           (vxbIaHpetBaseAddr + IA_HPET_T6_COMP_OFF)
#define IA_HPET_T6_MSI            (vxbIaHpetBaseAddr + IA_HPET_T6_MSI_OFF)

#define IA_HPET_T7_CONF           (vxbIaHpetBaseAddr + IA_HPET_T7_CONF_OFF)
#define IA_HPET_T7_COMP           (vxbIaHpetBaseAddr + IA_HPET_T7_COMP_OFF)
#define IA_HPET_T7_MSI            (vxbIaHpetBaseAddr + IA_HPET_T7_MSI_OFF)

#endif  /* !_WRS_CONFIG_LP64 */

#ifndef _ASMLANGUAGE

#define IA_HPET_GEN_READ64(addr, value)  (value = (*(volatile UINT64 *)addr))
#define IA_HPET_GEN_WRITE64(addr, value) ((*(volatile UINT64 *)addr) = value)
#define IA_HPET_GEN_READ32(addr, value)  (value = (*(volatile UINT32 *)addr))
#define IA_HPET_GEN_WRITE32(addr, value) ((*(volatile UINT32 *)addr) = value)

#define IA_HPET_TIMERn_READ64(base, id, value) (value = *(volatile UINT64 *)\
                                                (base + id * 0x20))
#define IA_HPET_TIMERn_WRITE64(base, id, value) (*(volatile UINT64 *)\
                                                (base + id * 0x20) = value)
#define IA_HPET_TIMERn_READ32(base, id, value)  (value = *(volatile UINT32 *)\
                                                (base + id * 0x20))
#define IA_HPET_TIMERn_WRITE32(base, id, value) (*(volatile UINT32 *)\
                                                (base + id * 0x20) = value)

LOCAL __inline__ UINT64 iaHpetRead64 (void)
    {
    UINT64 value;

    value = *(volatile UINT64 *)IA_HPET_MN_CNTR;

#ifndef  _WRS_CONFIG_LP64
    if (((*(volatile UINT64 *)IA_HPET_MN_CNTR) & 0x00000000ffffffffULL) <
                                       (value & 0x00000000ffffffffULL))
        value = *(volatile UINT64 *)IA_HPET_MN_CNTR;
#endif

    return value;
    }

/* macros */

#define IA_HPET_READ32(value)      value = *(volatile UINT32 *)IA_HPET_MN_CNTR
#define IA_HPET_READ64(value)      value = iaHpetRead64()

#undef HPET_DEBUG

#if defined (HPET_DEBUG)
IMPORT void earlyPrint (char * outString);
#endif /* HPET_DEBUG */

IMPORT BOOL vxbDelayTimerFreeRunning;

IMPORT STATUS sysMmuMapAdd();

IMPORT UINT8  *sysInumTbl;      /* IRQ vs intNum table */

IMPORT unsigned int vxCpuLoApicId (void);

/* prototypes */

IMPORT void vxbIaHpetTimerDrvRegister (void);

IMPORT STATUS iaHpetOneShotEnable (VXB_DEVICE_ID pInst,
                                   UINT32 timerId,
                                   UINT64 timeoutTs,
                                   void *pIsr,
                                   UINT32 arg);
IMPORT UINT64 iaHpetOneShotDisable (VXB_DEVICE_ID pInst, UINT32 timerId);
IMPORT UINT64 iaHpetTimerBaseGet (VXB_DEVICE_ID pInst, UINT32 timerId);
IMPORT UINT64 iaHpetTimerPeriodGet (VXB_DEVICE_ID pInst, UINT32 timerId);
IMPORT UINT32 iaHpetTimerFreqGet (VXB_DEVICE_ID pInst, UINT32 timerId);
IMPORT void   iaHpetTimerCfgShow (void);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __INCvxbIaHpetTimerh */
