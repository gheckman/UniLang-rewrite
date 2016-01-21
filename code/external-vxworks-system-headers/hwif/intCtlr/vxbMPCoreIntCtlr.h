/* vxbMPCoreIntCtlr.h - MPCore interrupt ctrl driver  */

/*
 * Copyright (c) 2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29jul10,pad  Moved extern C statement after include statements.
01b,16apr09,j_b  change core reset and start IPI #s
01a,23aug07,jb   Created from top of vxbEbGenIntrCtl.c rev 01c
*/

#ifndef __INCvxbMPCoreIntCtlrh
#define __INCvxbMPCoreIntCtlrh

#include <vxBusLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*  MPCore GIC Interrupt levels */
#define INT_LVL_MPCORE_IPI00         0 /* This is vxWorks CPC IPI */
#define INT_LVL_MPCORE_CPC           INT_LVL_MPCORE_IPI00

#define INT_LVL_MPCORE_IPI01         1 /* This is vxWorks Debug IPI */
#define INT_LVL_MPCORE_DEBUG         INT_LVL_MPCORE_IPI01

#define INT_LVL_MPCORE_IPI02         2 /* This is vxWorks Reschedule IPI */
#define INT_LVL_MPCORE_SCHED         INT_LVL_MPCORE_IPI02

#define INT_LVL_MPCORE_IPI03         3 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI04         4 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI05         5 /* IPI -> use SWI register in GIC */

#define INT_LVL_MPCORE_IPI06         6 /* This is vxWorks Core Reset IPI */
#define INT_LVL_MPCORE_RESET         INT_LVL_MPCORE_IPI06

#define INT_LVL_MPCORE_IPI07         7 /* This is vxWorks Core Start IPI */
#define INT_LVL_MPCORE_START         INT_LVL_MPCORE_IPI07

#define INT_LVL_MPCORE_IPI08         8 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI09         9 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI10        10 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI11        11 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI12        12 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI13        13 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI14        14 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_IPI15        15 /* IPI -> use SWI register in GIC */
#define INT_LVL_MPCORE_SPARE00      16 /* not used */
#define INT_LVL_MPCORE_SPARE01      17 /* not used */
#define INT_LVL_MPCORE_SPARE02      18 /* not used */
#define INT_LVL_MPCORE_SPARE03      19 /* not used */
#define INT_LVL_MPCORE_SPARE04      20 /* not used */
#define INT_LVL_MPCORE_SPARE05      21 /* not used */
#define INT_LVL_MPCORE_SPARE06      22 /* not used */
#define INT_LVL_MPCORE_SPARE07      23 /* not used */
#define INT_LVL_MPCORE_SPARE08      24 /* not used */
#define INT_LVL_MPCORE_SPARE09      25 /* not used */
#define INT_LVL_MPCORE_SPARE10      26 /* not used */
#define INT_LVL_MPCORE_SPARE11      27 /* not used */
#define INT_LVL_MPCORE_SPARE12      28 /* not used */
#define INT_LVL_MPCORE_PVT_TMR      29 /* Private Timer */
#define INT_LVL_MPCORE_PVT_WDG      30 /* Private WatchDog */
#define INT_LVL_MPCORE_PVT_IRQ      31 /* nIRQ */
#define INT_LVL_MPCORE_TST_INT00    32 /* AACIINTR */
#define INT_LVL_MPCORE_TST_INT01    33 /* TIMERINT01 */
#define INT_LVL_MPCORE_TST_INT02    34 /* TIMERINT23 */
#define INT_LVL_MPCORE_TST_INT03    35 /* USBnINT */
#define INT_LVL_MPCORE_TST_INT04    36 /* UARTINT0 */
#define INT_LVL_MPCORE_TST_INT05    37 /* UARTINT1 */
#define INT_LVL_MPCORE_TST_INT06    38 /* RTCINT */
#define INT_LVL_MPCORE_TST_INT07    39 /* KMIINT0 */
#define INT_LVL_MPCORE_TST_INT08    40 /* KMIINT1*/
#define INT_LVL_MPCORE_TST_INT09    41 /* ETHINTR */
#define INT_LVL_MPCORE_TST_INT10    42 /* GIC1 on EB */
#define INT_LVL_MPCORE_TST_INT11    43 /* GIC2 on EB */
#define INT_LVL_MPCORE_TST_INT12    44 /* GIC3 on EB */
#define INT_LVL_MPCORE_TST_INT13    45 /* GIC4 on EB */
#define INT_LVL_MPCORE_TST_INT14    46 /* MCIINTR0 */
#define INT_LVL_MPCORE_TST_INT15    47 /* MCIINTR1*/
#define INT_LVL_MPCORE_NOT_USED     48 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ00     49 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ01     50 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ02     51 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ03     52 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ04     53 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ05     54 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ06     55 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ07     56 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ08     57 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ09     58 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ10     59 /* PMU interrupts */
#define INT_LVL_MPCORE_PMUIRQ11     60 /* PMU interrupts */
#define INT_LVL_MPCORE_L220_EVENT   61
#define INT_LVL_MPCORE_L220_SLV_ERR 62
#define INT_LVL_MPCORE_L220_DEC_ERR 63

#define INT_LVL_MPCORE_GIC1         INT_LVL_MPCORE_TST_INT10

#define MPCORE_GIC_INT_LEVELS_MAX   64

#define MPCORE_GIC_BINP_DEFAULT     0x03
#define MPCORE_GIC_CONTROL_ENABLE   0x1
#define MPCORE_GIC_INT_ALL_ENABLED  0xF0  /* priority 0-E can run */
#define MPCORE_GIC_INT_ALL_DISABLED 0x00  /* nothing higher than 0*/
#define MPCORE_GIC_INT_SPURIOUS     0x3FF /* No interrupt currently */
#define MPCORE_GIC_ONEMINUS_HIGH    0xAAAAAAAA /* Intrpt config to 1-N, High */
#define MPCORE_GIC_SWINTRMASK       0X0000FFFF /* Mask for enabling S/W intr */

/* Generic Controller Defines */
#ifndef CONFIGS_PER_WORD
#define CONFIGS_PER_WORD        16
#endif
#ifndef PRIOS_PER_WORD
#define PRIOS_PER_WORD          4
#endif
#ifndef TARGETS_PER_WORD
#define TARGETS_PER_WORD        4
#endif
#ifndef NWORD
#define NWORD(bitnum)           (bitnum / 32)
#endif
#ifndef BIT
#define BIT(bitnum)             (1 << (bitnum % BITS_PER_WORD))
#endif

#ifndef      _ASMLANGUAGE

    /* MPCore Distributor and Controller defines */

/* TO DO - Add code to grab and use base from arm11MPCorePeriphBaseAddr */

#define MPCORE_SYS_BASE  0x1F000000

#define MPCORE_GIC_DIST  (MPCORE_SYS_BASE + 0x1000)

    /* MPCORE_GIC_Config used in code */

#define MPCORE_GIC_Config(Periph) ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + 0xC00 + \
                                           (0x4 * (Periph / CONFIGS_PER_WORD))))

    /* MPCORE_GIC_Prio used in code */

#define MPCORE_GIC_Prio(Periph)   ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + 0x400 + \
                                           (0x4 * (Periph / PRIOS_PER_WORD))))

    /* These three used in code */

#define MPCORE_GIC_Control   ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + 0x000))

    /* MPCORE_GIC_CPUTarg used in code */

#define MPCORE_GIC_CPUTarg(Periph)   ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + \
                                            0x800 + \
                                            (0x4 * (Periph/TARGETS_PER_WORD))))

    /* MPCORE_GIC_IntEnable used in code */

#define MPCORE_GIC_IntEnable(Periph) ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + \
                                            0x100 + (0x4 * NWORD(Periph))))

    /* MPCORE_GIC_IntEnClr used in code */

#define MPCORE_GIC_IntEnClr(Periph)   ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + 0x180 + \
                                            (0x4 * NWORD(Periph))))

    /* MPCORE_GIC_IntPendClr used in code */

#define MPCORE_GIC_IntPendClr(Periph)   ((volatile unsigned int *)\
                                           (MPCORE_GIC_DIST + 0x280 + \
                                            (0x4 * NWORD(Periph))))

    /* MPCORE_GIC Software Interrupt Register */

#define MPCORE_GIC_SWInterrupt          ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x1F00))

    /* Per Cpu Private space */
#define MPCORE_CPU_Control   ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x100))

    /* MPCORE_CPU_PrioMask used in code */

#define MPCORE_CPU_PrioMask   ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x104))

#define MPCORE_CPU_BinPoint   ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x108))

    /* MPCORE_CPU_IntAck used in code */

#define MPCORE_CPU_IntAck   ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x10C))

    /* MPCORE_CPU_EOInt used in code */

#define MPCORE_CPU_EOInt   ((volatile unsigned int *)\
                                           (MPCORE_SYS_BASE + 0x110))

    /* Aliased address space */

    /* Per Cpu Aliased space */
#define MPCORE_CPU_A_Control(CPU)   ((volatile unsigned int *)\
                                   ((MPCORE_SYS_BASE + 0x200) + ((CPU) * 100)))

    /* MPCORE_CPU_PrioMask used in code */

#define MPCORE_A_CPU_PrioMask(CPU)   ((volatile unsigned int *)\
                                       (MPCORE_SYS_BASE + 0x204) + ((CPU) * 100))

#define MPCORE_A_CPU_BinPoint(CPU)   ((volatile unsigned int *)\
                                       (MPCORE_SYS_BASE + 0x208) + ((CPU) * 100))

    /* MPCORE_A_CPU_IntAck used in code */

#define MPCORE_A_CPU_IntAck(CPU)   ((volatile unsigned int *)\
                                       (MPCORE_SYS_BASE + 0x20C) + ((CPU) * 100))

    /* MPCORE_A_CPU_EOInt used in code */

#define MPCORE_A_CPU_EOInt(CPU)   ((volatile unsigned int *)\
                                       (MPCORE_SYS_BASE + 0x210) + ((CPU) * 100))

IMPORT STATUS vxbSysMPCoreIpiConnect (VOIDFUNCPTR * vector, \
                                      VOIDFUNCPTR routine, INT32 parameter);
IMPORT STATUS vxbSysMPCoreIpiEnable (INT32 vector);
IMPORT STATUS vxbSysMPCoreIpiDisable (INT32 vector);
IMPORT STATUS sysEbMPCoreIpiGen(INT32 level, cpuset_t processor);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCvxbMPCoreIntCtlrh */

