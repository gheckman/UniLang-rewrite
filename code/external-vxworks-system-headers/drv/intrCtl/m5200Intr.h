/* m5200Intr.h - Motorola MPC5200 interrupt header file */

/* Copyright 1991-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,15feb05,j_b  INUM_PERIPHERAL_LAST corrected
01a,03jul03,pkr  derived from ppc860Intr.h
*/

#ifndef __INCm5200Intrh
#define __INCm5200Intrh

#ifdef __cplusplus
extern "C" {
#endif

/* interrupt number definitions */

/* Peripheral Interrupts */

#define INUM_PERIPHERAL_FIRST   0
#define INUM_BESTCOMM       0
#define INUM_PSC1       1
#define INUM_PSC2       2
#define INUM_PSC3       3
#define INUM_PSC6       4
#define INUM_ETH        5
#define INUM_USB        6
#define INUM_ATA        7
#define INUM_PCI_CTL        8
#define INUM_PCI_RX     9
#define INUM_PCI_TX     10
#define INUM_PSC4       11
#define INUM_PSC5       12
#define INUM_SPI_MODF       13
#define INUM_SPI_SPIF       14
#define INUM_I2C1       15
#define INUM_I2C2       16
#define INUM_CAN1       17
#define INUM_CAN2       18
#define INUM_IR_RX      19
#define INUM_IR_TX      20
#define INUM_XLB        21
#define INUM_BDLC       22
#define INUM_BESTCOMM_LP    23
#define INUM_PERIPHERAL_LAST     INUM_BESTCOMM_LP

/* External Interrupts to Main Controller */
#define INUM_MAIN_FIRST     32
#define INUM_SLT1       32
#define INUM_IRQ1       33
#define INUM_IRQ2       34
#define INUM_IRQ3       35
#define _INUM_LO        36 /* internal only */
#define INUM_RTC_pint       37
#define INUM_RTC_sint       38
#define INUM_GPIO_std       39
#define INUM_GPIO_wkup      40
#define INUM_TMR0       41
#define INUM_TMR1       42
#define INUM_TMR2       43
#define INUM_TMR3       44
#define INUM_TMR4       45
#define INUM_TMR5       46
#define INUM_TMR6       47
#define INUM_TMR7       48
#define INUM_MAIN_LAST      48

/* Critical Interrupts to Main Controller */
#define INUM_CRITICAL_FIRST 49
#define INUM_IRQ0       49
#define INUM_SLT0       50
#define _INUM_HI        51 /* internal only */
#define INUM_CCS        52
#define INUM_CRITICAL_LAST  52

/* Bestcomm Interrupts (to share a common table */

#define INUM_SDMA_FIRST     53
#define INUM_SDMA_TEA       53
#define INUM_SDMA_TASK0     54
#define INUM_SDMA_TASK1     55
#define INUM_SDMA_TASK2     56
#define INUM_SDMA_TASK3     57
#define INUM_SDMA_TASK4     58
#define INUM_SDMA_TASK5     59
#define INUM_SDMA_TASK6     60
#define INUM_SDMA_TASK7     61
#define INUM_SDMA_TASK8     62
#define INUM_SDMA_TASK9     63
#define INUM_SDMA_TASK10    64
#define INUM_SDMA_TASK11    65
#define INUM_SDMA_TASK12    66
#define INUM_SDMA_TASK13    67
#define INUM_SDMA_TASK14    68
#define INUM_SDMA_TASK15    69
#define INUM_SDMA_LAST      69

#define SDMA_TASKNO_TO_INUM(TASKNO) (INUM_SDMA_TASK0+TASKNO)

#define NUM_VEC_MAX     69

/* vectors */

#define IV_BESTCOMM     INUM_TO_IVEC (INUM_BESTCOMM)
#define IV_PSC1         INUM_TO_IVEC (INUM_PSC1)
#define IV_PSC2         INUM_TO_IVEC (INUM_PSC2)
#define IV_PSC3         INUM_TO_IVEC (INUM_PSC3)
#define IV_PSC6         INUM_TO_IVEC (INUM_PSC6)
#define IV_ETH          INUM_TO_IVEC (INUM_ETH)
#define IV_USB          INUM_TO_IVEC (INUM_USB)
#define IV_ATA          INUM_TO_IVEC (INUM_ATA)
#define IV_PCI_CTL      INUM_TO_IVEC (INUM_PCI_CTL)
#define IV_PCI_RX       INUM_TO_IVEC (INUM_PCI_RX)
#define IV_PCI_TX       INUM_TO_IVEC (INUM_PCI_TX)
#define IV_PSC4         INUM_TO_IVEC (INUM_PSC4)
#define IV_PSC5         INUM_TO_IVEC (INUM_PSC5)
#define IV_SPI_MODF     INUM_TO_IVEC (INUM_SPI_MODF)
#define IV_SPI_SPIF     INUM_TO_IVEC (INUM_SPI_SPIF)
#define IV_I2C1         INUM_TO_IVEC (INUM_I2C1)
#define IV_I2C2         INUM_TO_IVEC (INUM_I2C2)
#define IV_CAN1         INUM_TO_IVEC (INUM_CAN1)
#define IV_CAN2         INUM_TO_IVEC (INUM_CAN2)
#define IV_IR_RX        INUM_TO_IVEC (INUM_IR_RX)
#define IV_IR_TX        INUM_TO_IVEC (INUM_IR_TX)
#define IV_XLB          INUM_TO_IVEC (INUM_XLB)
#define IV_BDLC         INUM_TO_IVEC (INUM_BDLC)
#define IV_BESTCOMM_LP      INUM_TO_IVEC (INUM_BESTCOMM_LP)
#define IV_RESERVED24       INUM_TO_IVEC (INUM_RESERVED24)
#define IV_RESERVED25       INUM_TO_IVEC (INUM_RESERVED25)
#define IV_RESERVED26       INUM_TO_IVEC (INUM_RESERVED26)
#define IV_RESERVED27       INUM_TO_IVEC (INUM_RESERVED27)
#define IV_RESERVED28       INUM_TO_IVEC (INUM_RESERVED28)
#define IV_RESERVED29       INUM_TO_IVEC (INUM_RESERVED29)
#define IV_RESERVED30       INUM_TO_IVEC (INUM_RESERVED30)
#define IV_RESERVED31       INUM_TO_IVEC (INUM_RESERVED31)

#define IV_SLT1         INUM_TO_IVEC (INUM_SLT1)
#define IV_IRQ1         INUM_TO_IVEC (INUM_IRQ1)
#define IV_IRQ2         INUM_TO_IVEC (INUM_IRQ2)
#define IV_IRQ3         INUM_TO_IVEC (INUM_IRQ3)
#define IV_RTC_pint     INUM_TO_IVEC (INUM_RTC_pint)
#define IV_RTC_sint     INUM_TO_IVEC (INUM_RTC_sint)
#define IV_GPIO_std     INUM_TO_IVEC (INUM_GPIO_std)
#define IV_GPIO_wkup        INUM_TO_IVEC (INUM_GPIO_wkup)
#define IV_TMR0         INUM_TO_IVEC (INUM_TMR0)
#define IV_TMR1         INUM_TO_IVEC (INUM_TMR1)
#define IV_TMR2         INUM_TO_IVEC (INUM_TMR2)
#define IV_TMR3         INUM_TO_IVEC (INUM_TMR3)
#define IV_TMR4         INUM_TO_IVEC (INUM_TMR4)
#define IV_TMR5         INUM_TO_IVEC (INUM_TMR5)
#define IV_TMR6         INUM_TO_IVEC (INUM_TMR6)
#define IV_TMR7         INUM_TO_IVEC (INUM_TMR7)

#define IV_IRQ0         INUM_TO_IVEC (INUM_IRQ0)
#define IV_SLT0         INUM_TO_IVEC (INUM_SLT0)
#define IV_CCS          INUM_TO_IVEC (INUM_CCS)

#define IV_SDMA_TEA     INUM_TO_IVEC (INUM_SDMA_TEA)
#define IV_SDMA_TASK0       INUM_TO_IVEC (INUM_SDMA_TASK0)
#define IV_SDMA_TASK1       INUM_TO_IVEC (INUM_SDMA_TASK1)
#define IV_SDMA_TASK2       INUM_TO_IVEC (INUM_SDMA_TASK2)
#define IV_SDMA_TASK3       INUM_TO_IVEC (INUM_SDMA_TASK3)
#define IV_SDMA_TASK4       INUM_TO_IVEC (INUM_SDMA_TASK4)
#define IV_SDMA_TASK5       INUM_TO_IVEC (INUM_SDMA_TASK5)
#define IV_SDMA_TASK6       INUM_TO_IVEC (INUM_SDMA_TASK6)
#define IV_SDMA_TASK7       INUM_TO_IVEC (INUM_SDMA_TASK7)
#define IV_SDMA_TASK8       INUM_TO_IVEC (INUM_SDMA_TASK8)
#define IV_SDMA_TASK9       INUM_TO_IVEC (INUM_SDMA_TASK9)
#define IV_SDMA_TASK10      INUM_TO_IVEC (INUM_SDMA_TASK10)
#define IV_SDMA_TASK11      INUM_TO_IVEC (INUM_SDMA_TASK11)
#define IV_SDMA_TASK12      INUM_TO_IVEC (INUM_SDMA_TASK12)
#define IV_SDMA_TASK13      INUM_TO_IVEC (INUM_SDMA_TASK13)
#define IV_SDMA_TASK14      INUM_TO_IVEC (INUM_SDMA_TASK14)

#define SDMA_TASKNO_TO_IVEC(TASKNO) INUM_TO_IVEC(SDMA_TASKNO_TO_INUM(TASKNO))

/* other defines */

#define USE_CRITICAL_INTERRUPT  0

#define INTR_LEVEL_DEFAULT  3

/* typedefs */

/* interrupt handler */

#ifndef _ASMLANGUAGE
typedef struct intr_handler
    {
    VOIDFUNCPTR vec;    /* interrupt vector */
    int         arg;    /* interrupt handler argument */
    } INTR_HANDLER;

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT STATUS m5200IntrInit (void);
IMPORT int m5200IntrSetLevel(int, int);
IMPORT void m5200IntAck(int);

#else

IMPORT STATUS m5200IntrInit ();
IMPORT STATUS m5200IntrSetLevel();
IMPORT void m5200IntAck();

#endif  /* __STDC__ */
#endif  /* _ASMLANGUAGE */

#define _EXC_INFO_XLB   0x10000 /* mach check from XLB, info in DAR/DSISR */

#ifdef __cplusplus
}
#endif

#endif /* __INCm5200Intrh */
