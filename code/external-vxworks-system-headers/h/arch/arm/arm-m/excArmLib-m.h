/* excArmLib-m.h - ARMv7-M exception library header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01d,05sep12,rec  add excClearFault prototype
01c,24may12,j_b  add fault status to EXC_INFO
01b,22may12,jdw  Add exception vector offset mapping for scopetools
01a,14may12,m_h  create from target/h/arch/arm/excArmLib.h version 01f
*/

#ifndef	__INCexcArmLib_mh
#define	__INCexcArmLib_mh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/*
 * NOTE: if this structure changes, the TCB offsets in h/private/taskLibP.h
 *	 must be updated. See also taskLib.h.
 */

typedef struct
    {
    UINT32	valid;          /* flags indicate following fields are valid */
    UINT32	vecNum;         /* exception number */
    INSTR *	pc;	        /* PC */
    UINT32	psr;            /* combined A/I/E PSR */
    UINT32	primask;        /* PRIMASK */
    UINT32	faultmask;      /* FAULTMASK */
    UINT32	basepri;        /* BASEPRI */
    UINT32	control;        /* Control Register */
    UINT32	sysHandlrStat;  /* System Handler Control and State Register */
    UINT32	hardFltStat;    /* Hard Fault Status Register */
    UINT32	configFltStat;  /* Configurable Fault Status Register */
    UINT32	memFltAddr;     /* Memory Manage Fault Address Register */
    UINT32	busFltAddr;     /* Bus Fault Address Register */
    } EXC_INFO;

extern FUNCPTR excExcepHook;    /* add'l rtn to call when exceptions occur */
extern VOIDFUNCPTR _func_excBreakpoint; /* called to handle breakpoints */

extern void excVecBaseSet (UINT32 base); /* non-zero exception base address */

extern STATUS  	excIntConnect (VOIDFUNCPTR * vector, VOIDFUNCPTR routine);

extern void	excVecSet (FUNCPTR * vector, FUNCPTR function);
extern FUNCPTR	excVecGet (FUNCPTR * vector);

extern STATUS	excVecPrioSet (VOIDFUNCPTR * vector, UINT8 priority);
extern STATUS	excVecPrioGet (VOIDFUNCPTR * vector, UINT8 * pPriority);
extern void	excClearFault (void);

#endif	/* ASMLANGUAGE */

/* exception information valid bits */

#define EXC_INFO_VECNUM         0x01    /* vector is valid */
#define EXC_INFO_PC             0x02    /* PC is valid */
#define EXC_INFO_XPSR           0x04    /* xPSR is valid */
#define EXC_INFO_PRIMASK        0x08    /* PRIMASK is valid */
#define EXC_INFO_FAULTMASK      0x10    /* FAULTMASK is valid */
#define EXC_INFO_BASEPRI        0x20    /* BASEPRI is valid */
#define EXC_INFO_CONTROL        0x40    /* Control Register is valid */
#define EXC_INFO_SYSHDLRSTAT    0x80    /* System Handler Ctrl/State is valid */
#define EXC_INFO_HRDFLTSTAT     0x100   /* Hard Fault Status is valid */
#define EXC_INFO_CFGFLTSTAT     0x200   /* Configurable Fault Status is valid */
#define EXC_INFO_MEMFLTADDR     0x400   /* Mem Manage Fault Address is valid */
#define EXC_INFO_BUSFLTADDR     0x800   /* Bus Fault Address is valid */

#define EXC_INFO_ALL_VALID      0xFFF   /* all EXC_INFO fields are valid */

/*
 * Exception Numbers
 *
 * Note there is no Exception number 0.  If the IPSR contains zero then we are
 * in thread mode and therefore not servicing an exception or interrupt.
 */

#define EXC_NUM_THREAD_MODE     0    /* IPSR is 0 when in thread mode */

#define EXC_NUM_RESET           1    /* Reset */
#define EXC_NUM_NMI             2    /* Nonmaskable Interrupt */
#define EXC_NUM_HARD_FAULT      3    /* unimplemented fault handler */
#define EXC_NUM_MEM_MANAGE      4    /* MPU Violation */
#define EXC_NUM_BUS_FAULT       5    /* Bus Error */
#define EXC_NUM_USAGE_FAULT     6    /* Program error or coprocessor */
#define EXC_NUM_SVCALL         11    /* Supervisor Call */
#define EXC_NUM_DEBUG_MONITOR  12    /* Debug Monitor */
#define EXC_NUM_PENDSV         14    /* PendSV */
#define EXC_NUM_SYSTICK        15    /* System Tick Timer */
#define EXC_NUM_IRQ_BASE       16    /* First External Interrupt */

#define EXC_NUM_IRQ(num)       (EXC_NUM_IRQ_BASE + (num))

#define EXC_NUM_LAST_IRQ       511

/* Exception Vectors
 *
 * The values at these offsets are 32-bit addresses of exception handlers.
 * This is different from traditional arm architectures (such as ARMv7) which
 * expect branch instructions or some other executable instructions.
 *
 * Note: the first entry (entry 0) in the exception vector table is the
 * initial value of the stack pointer after reset, and not an exception vector
 * address.  Although not actually an exception vector, it is included here
 * for completeness.
 */

#define EXC_OFF_INITIAL_SP      0x00

#define EXC_OFF_RESET           (EXC_NUM_RESET * 4)
#define EXC_OFF_NMI             (EXC_NUM_NMI * 4)
#define EXC_OFF_HARD_FAULT      (EXC_NUM_HARD_FAULT * 4)
#define EXC_OFF_MEM_MANAGE      (EXC_NUM_MEM_MANAGE * 4)
#define EXC_OFF_BUS_FAULT       (EXC_NUM_BUS_FAULT * 4)
#define EXC_OFF_USAGE_FAULT     (EXC_NUM_USAGE_FAULT * 4)
#define EXC_OFF_SVCALL          (EXC_NUM_SVCALL * 4)
#define EXC_OFF_DEBUG_MONITOR   (EXC_NUM_DEBUG_MONITOR * 4)
#define EXC_OFF_PENDSV          (EXC_NUM_PENDSV * 4)
#define EXC_OFF_SYSTICK         (EXC_NUM_SYSTICK * 4)
#define EXC_OFF_IRQ_BASE        (EXC_NUM_IRQ_BASE * 4)

#define EXC_OFF_IRQ(num)        (EXC_OFF_IRQ_BASE + ((num)*4))

#define EXC_OFF_LAST_IRQ        EXC_OFF_IRQ(EXC_NUM_LAST_IRQ)

/* Exception Vector Base */
#define ARM_EXC_VEC_BASE        0x00

/*
 * Map the traditional ARM definition to the ARM-M exception offset.
 */

/* Scope tools needs to know which vector handles undefined instructions. */
#define EXC_OFF_UNDEF           (EXC_NUM_USAGE_FAULT)

/* ObjVerify needs to know which vector handles Page Faults */
#define EXC_OFF_DATA            (EXC_NUM_MEM_MANAGE)

#ifdef __cplusplus
}
#endif

#endif	/* __INCexcArmLib_mh */



