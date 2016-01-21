/* vbiArmArch.h - ARM architecture specific definitions */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,20jan12,m_h  WIND00290890 Fix Warnings
01e,26apr11,m_h  Support for wrload
01d,04apr11,jlv  Sync with HV 1.3 01-Apr-11(WIND00265419)
01c,11mar11,rab  add VBI_INT_VCORE_LOCK/UNLOCK/STATE_GET macros
01b,11feb11,rab  sync with latest hv-1.3
01a,28sep10,rab  created
*/

#ifndef __INCvbiArmArchh
#define __INCvbiArmArchh

#ifdef __cplusplus
extern "C" {
#endif

#include <vxWorks.h>
#include <vsbConfig.h>

/* For now restrict operation to little endian. */
/* Later this should come from the build system. */

#define __VBI_BYTE_ORDER __VBI_LITTLE_ENDIAN

#define WRHV_13_LATEST      /* RAB - undef to build for HV-1.3 EAR DVD */

/* VIOAPIC number of entries */

#define VB_VIOAPIC_ENTRIES_SIZE		    64 

#define _WRHV_ARCH_HAS_STATUS_REGS	    1
#define _WRHV_ARCH_HAS_CTRL_REGS	    1

#define VB_STATUS_REGS_OFFSET_BASE	 0
#define VB_STATUS_MODE			(4 * (VB_STATUS_REGS_OFFSET_BASE + 0))
#define VB_STATUS_DFSR			(4 * (VB_STATUS_REGS_OFFSET_BASE + 1))
#define VB_STATUS_IFSR			(4 * (VB_STATUS_REGS_OFFSET_BASE + 2))
#define VB_STATUS_DFAR			(4 * (VB_STATUS_REGS_OFFSET_BASE + 3))
#define VB_STATUS_IFAR			(4 * (VB_STATUS_REGS_OFFSET_BASE + 4))
#define VB_STATUS_INTVECTOR		(4 * (VB_STATUS_REGS_OFFSET_BASE + 5))
#define VB_STATUS_COPROC_RIGHTS		(4 * (VB_STATUS_REGS_OFFSET_BASE + 6))
#define VB_STATUS_COPROC_GRANTS		(4 * (VB_STATUS_REGS_OFFSET_BASE + 7))
#define VB_STATUS_BANKED_REGS		(4 * (VB_STATUS_REGS_OFFSET_BASE + 8))
/* (SPSR, SP, LR) * 16 = 48 */

#define VB_STATUS_REG_STRUCT_END	(4 * (VB_STATUS_REGS_OFFSET_BASE + 56))

#if 0
/* Bit Mask definitions for VB_STATUS_INT_PENDING */

#define VB_STATUS_INT_PENDING_INT        1	/* Interrupt controller */
#define VB_STATUS_INT_PENDING_TICK       2	/* Tick interrupt */
#endif

#define VB_CONTROL_REGS_OFFSET_BASE	 0

#define VB_CONTROL_CPSR		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 0))
#define VB_CONTROL_SPSR		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 1))
#define VB_CONTROL_R0		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 2))
#define VB_CONTROL_R1		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 3))
#define VB_CONTROL_R2		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 4))
#define VB_CONTROL_R3		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 5))
#define VB_CONTROL_R4		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 6))
#define VB_CONTROL_R5		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 7))
#define VB_CONTROL_R6		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 8))
#define VB_CONTROL_R7		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 9))
#define VB_CONTROL_R8		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 10))
#define VB_CONTROL_R9		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 11))
#define VB_CONTROL_R10		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 12))
#define VB_CONTROL_R11		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 13))
#define VB_CONTROL_R12		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 14))
#define VB_CONTROL_R13		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 15))
#define VB_CONTROL_R14		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 16))
#define VB_CONTROL_R15		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 17))
#define VB_CONTROL_SP		VB_CONTROL_R13
#define VB_CONTROL_LR		VB_CONTROL_R14
#define VB_CONTROL_PC		VB_CONTROL_R15

#define VB_CONTROL_REG_STRUCT_END	(4 * (VB_CONTROL_REGS_OFFSET_BASE + 18))

/* status register size for arm */

#ifndef _ASMLANGUAGE

#define VB_STATUS_REGS_ACCESS(base, field)	\
	base->vbStatusRegs.field		

#define VB_CONTROL_REGS_ACCESS(base, field)	\
	base->vbControlRegs.field		


/*******************************************************************************
*
* VB_ARCH_CONTROL_REGS - Virtual core ARM control structure
*
* Virtual board emulated control registers. These registers are used
* by a guest running on hypervisor to configure the virtual CPU register.
*
* SYNOPSIS
*
* ARM Control structure graphical illustration
*\cs
#if 0
*        _______________   
*       |       PC      |   
*       |---------------|
*       |       MSR     |	    
*       |---------------|
*       |       CR      |
*       |---------------|
*       |		|
*       |general purpose|
*       |     r[0:13]   | 
*       |		|
*       |---------------|
*       |emulated MSR   |
*       |---------------|
*       |       dbsr    |
*       |---------------|
*       | dbcr[0:2]     |
*       |---------------|
*       |IAC[1:2]       |
*       |---------------|
*       |DAC[1:2]       |
*       |---------------|
*       |reserved[0:9]  |
*       |---------------|
#endif
*
*\ce
*
* Virtual core's control C data structure type definition
*
*\cs
* VB_STATUS structure definition
*
* typedef struct vbArchControlRegs
*    {
*
*    /@ Registers to be restored by the VDK_SYS_ctx_load fast system call   @/
*
#if 0
*    uint32_t srr0;	/@  0: PC		    @/
*    uint32_t srr1;	/@  1: MSR		    @/
*    uint32_t cr;	/@  2: condition registers	    @/
*    uint32_t r0;	/@  3: General register R0	    @/
*    uint32_t sp;	/@  4: General register R1 (stack pointer)  @/
*    uint32_t r2;	/@  5: General register R2	    @/
*    uint32_t r3;	/@  6: General register R3	    @/
*    uint32_t r4;	/@  7: General register R4	    @/
*    uint32_t r5;	/@  8: General register R5	    @/
*    uint32_t r6;	/@  9: General register R6	    @/
*    uint32_t r7;	/@ 10: General register R7	    @/
*    uint32_t r8;	/@ 11: General register R8	    @/
*    uint32_t r9;	/@ 12: General register R9	    @/
*    uint32_t r10;	/@ 13: General register R10	    @/
*    uint32_t r11;	/@ 14: General register R11	    @/
*    uint32_t r12;	/@ 15: General register R12	    @/
*    uint32_t r13;	/@ 16: General register R13	    @/
*
*    /@ emulated registers used by the VDK_SYS_ctx_load_vmmu system call    @/
*
*    uint32_t emsr;	/@ 17: emulated MSR register	        @/
*
*    /@ Debug control registers			        @/
*    
*    uint32_t     dbsr; /@ 18 - debug status register		    @/
*
*    /@ Debug control registers			        @/
*    
*    uint32_t     dbcr0; /@ 19 - debug control register 0	    @/
*    uint32_t     dbcr1; /@ 20 - debug control register 1	    @/
*    uint32_t     dbcr2; /@ 21 - debug control register 2	    @/
*
*    /@ instruction address compare registers IAC1-IAC2		    @/
*
*    uint32_t     iac1; /@ 22 - instructions access control 1	        @/
*    uint32_t     iac2; /@ 23 - instructions access control 2	        @/
*
*    /@ data address compare registers DAC1-DAC2.	        @/
*
*    uint32_t     dac1;	    /@ 24 - instructions access control 3       @/
*    uint32_t     dac2;	    /@ 25 - instructions access control 4       @/
*
*    /@ reserved fields for future use			    @/
*
*    uint32_t reserved[10]; /@ 26: Reserved		    @/ 
#endif
*    } VB_ARCH_CONTROL_REGS;
*
*\ce
*
* SEE ALSO: VB_ARCH_CONTROL_REGS, architecture supplement document 
*\COMMAND
*/

typedef struct vbArchControlRegs
    {
    unsigned long cpsr;		/* saved CPSR */
    unsigned long spsr;		/* saved SPSR */

    /* registers that can be restored by a sys_ret fast system call */

    unsigned long r0;		/* general purpose register R0  */
    unsigned long r1;		/* general purpose register R1  */
    unsigned long r2;		/* general purpose register R2  */
    unsigned long r3;		/* general purpose register R3  */
    unsigned long r4;		/* general purpose register R4  */
    unsigned long r5;		/* general purpose register R5  */
    unsigned long r6;		/* general purpose register R6  */
    unsigned long r7;		/* general purpose register R7  */
    unsigned long r8;		/* general purpose register R8  */
    unsigned long r9;		/* general purpose register R9  */
    unsigned long r10;		/* general purpose register R10 */
    unsigned long r11;		/* general purpose register R11 */
    unsigned long r12;		/* general purpose register R12 */
    unsigned long sp;		/* r13 */
    unsigned long lr;		/* r14 */
    unsigned long pc;		/* r15 */

#ifdef WRHV_13_LATEST
    unsigned long asid;		/* Virtual ASID */
    unsigned long vmmuHandle;	/* VMMU Handle returned from vbiVmmuCreate */
#endif /* WRHV_13_LATEST */

    } VB_ARCH_CONTROL_REGS;

/*******************************************************************************
*
* VB_ARCH_STATUS_REGS - Virtual core emulated status registers
*
* Virtual board emulated CPU status registers
*
* SYNOPSIS
*
* PPC Status structure graphical illustration
*\cs
#if 0
*        _______________   ---------------------------
*       |    SRR0       |   
*       |---------------|
*       |    SRR1       |   Registers save by WRHV	
*       |---------------|   before injecting an exception/interrupt
*       |    CR		|
*       |---------------|
*       |    LR		|
*       |---------------|
*       |    r3		| 
*       |---------------|
*       |    r4         |
*       |---------------|   ---------------------------
*	|    mcsrr0	|	
*       |---------------|  Registers saved duing exception handling
*       |    mcssr1     |
*       |---------------|
*       |    esr        |
*       |---------------|
*       |    mcsr       |
*       |---------------|
*       |    mcar       |
*       |---------------|
*       |    dear       |
*       |---------------|
*       |    emsr       |
*       |---------------|
*       |    esrr0      |
*       |---------------|
*       |    esrr1      |
*       |---------------|    -------------------------
*       | reserved[8]   |      8 x 32bits for future enhencements
*       |---------------|    -------------------------
*       |    svr        |
*       |---------------|
*       |    pir        |
*       |---------------|
*       |    pvr        |    Configuration registers updated
*       |---------------|    upon board creation    
*       |    hid0       |  
*       |---------------|
*       |    hid1       |
*       |---------------|
*       |    buscr      |
*       |---------------|       
*       |    l1csr0     |
*       |---------------|
*       |    l1csr1     |
*       |---------------|   --------------------------
*       | reserved[0:8] | 9x 32bit
*       |---------------|
#endif
*
*\ce
*
* Virtual core's status C data structure type definition
*
*\cs
* VB_ARCH_STATUS_REGS structure definition
*
* typedef struct archStatusRegs
*    {
*
*    /@ 
*     @ registers saved by WRHV for all interrupts exceptions
*     @ before setting the PC in the virtual board to the exception/interrupt
*     @ vector address
*     @/
*
#if 0
*    uint32_t srr0; /@ 0: PC at time of the interrupt		@/
*    uint32_t srr1; /@ 1: MSR at time of the interrupt		@/
*    uint32_t cr;   /@ 2: Condition registers at time of the interrupt	@/
*    uint32_t lr;   /@ 3: Link register at time of the interrupt    @/
*    uint32_t r3;   /@ 4: R3 at time of the interrupt		@/
*    uint32_t r4;   /@ 5: R4 at time of the interrupt		@/
*
*    /@ Registers saved by WRHV during exception processing only    @/
*
*    uint32_t mcsrr0; /@  6:			    @/
*    uint32_t mcsrr1; /@  7:			    @/
*    uint32_t esr;    /@  8:			    @/
*    uint32_t mcsr;   /@  9:			    @/
*    uint32_t mcar;   /@ 10			@/
*    uint32_t dear;   /@ 11:			    @/
*    uint32_t emsr;   /@ 12:			    @/
*    uint32_t esrr0;  /@ 13:			    @/
*    uint32_t esrr1;  /@ 14:			    @/
*
*    /@ reserved fields for future use			@/
*
*    uint32_t reserved1[8]; /@ 15 - 22			@/
*
*    /@ Configuration registers (only updated upon board creation   @/
*
*    uint32_t svr;     /@ 23			    @/     
*    uint32_t pir;     /@ 24			    @/
*    uint32_t pvr;     /@ 25			    @/  
*    uint32_t hid0;    /@ 26			    @/
*    uint32_t hid1;    /@ 27			    @/
*    uint32_t bucsr;   /@ 28			    @/
*    uint32_t l1csr0;  /@ 29			    @/
*    uint32_t l1csr1;  /@ 30			    @/
*    
*    /@ reserved fields for future use			@/
*
*    uint32_t reserved2[9]; /@ 31 - 39			@/
#endif
*
*    } VB_ARCH_STATUS_REGS; 
*
*
*\ce
*
* SEE ALSO: VB_STATUS 
*\COMMAND
*/

typedef struct archStatusRegs
    {
    /* 
     * registers saved by Razor for all interrupts exceptions
     * before setting the PC in the virtual board to the exception/interrupt
     * vector address
     */

    unsigned long mode;

    unsigned long dfsr;		/* cp15 c5, Data Fault Status Register */
    unsigned long ifsr;		/* cp15 c5, Instruction Fault Status Register */
    unsigned long dfar;		/* like cp15 c6, Fault Address Register */
    unsigned long ifar;		/* like cp15 c6, Fault Address Register */
    unsigned long intVector;	/* vector index indicating highest pri pending */

    /* bit0 = cp0, ..., bit13 = cp13; 1 = grant, 0 = deny */
    unsigned long coprocRights;	/* CP access rights for this VB [13:0] */

    /* CPs that have been granted user-mode access by the VB [13:0] */
    /* coprocGrants is changed in sync with regs->coprocAccess */
    unsigned long coprocGrants;

    struct
	{
	unsigned long spsr;	/* mode specific SPSR */
	unsigned long sp;	/* mode specific r13 (stack pointer) */
	unsigned long lr;	/* mode specific r14 (link register) */
	} modeSpecificReg[16];

    } VB_ARCH_STATUS_REGS; 


/*******************************************************************************
*
* VBI_HREG_SET - hardware register set, for read/write
*
* Used by vbiVbRegisterRead/vbiVbRegisterWrite to read/write registers in 
* another VB
* 
* SYNOPSIS
*
* VB hardware register set C data structure type definition
*
*\cs
*
* typedef struct
*     {
#if 0
*     uint32_t gpr[GREG_NUM];	/@ general purpose registers @/
*     uint32_t msr;		/@ machine state register @/
*     uint32_t lr;		/@ link register @/
*     uint32_t ctr;		/@ count register @/
*     uint32_t pc;		/@ program counter @/
*     uint32_t cr;		/@ condition register @/
*     uint32_t xer;		/@ fixed-point exception register @/
*     uint32_t spefscr;		/@ SPE floating-point status & ctrl reg @/
*     uint32_t casid;		/@ PPC405, Book E PID and PPC860 M_CASID @/
#endif
*     } VBI_HREG_SET;
* 
*
*\ce
* SEE ALSO: NONE
* 
*/

#define VBI_GREG_NUM	13	/* has 32 32/64-bit data registers */

typedef struct
    {
    uint32_t r[VBI_GREG_NUM];	/* general purpose registers 0-12 */

    INSTR * pc;			/* program counter. aka r[15] */

    uint32_t cpsr;

    uint32_t sp_usr;		/* or sys mode. aka r[13] */
    uint32_t lr_usr;		/* or sys mode. aka r[14] */

    } VBI_HREG_SET;


/* complex register set definition */

typedef union
    {
    VBI_HREG_SET    hreg32;	/* 32 bit register set */
    } VBI_HREG_SET_CMPLX;


typedef struct
    {
    vbiRegSet_t        vbiRegType;
    VBI_HREG_SET_CMPLX vbiRegSet;
    } VBI_HREG_SET_CMPLX_QUALIFIED;

/* common system wide message header structure */

typedef struct vbi_msg_header {
    uint32_t msgId;	/* message type identification */
    uint32_t msgArg;	/* argument associated with message type */
} VBI_MSG_HEADER;

/* request message */

typedef struct 
    {
    VBI_MSG_HEADER hdr;			/* message header */
    uint32_t   request;			/* request type */

    } VBI_BSP_MSG;

typedef struct 
    {
    VBI_MSG_HEADER hdr;			/* message header */
    uint32_t   status;			/* request completion status */
    uint32_t   dataVal;
    } VBI_BSP_MSG_REPLY;

/******************************************************************************
*
* wrhvAmpCpuHreg32Set - Init the guestOS of VBI_HREG_SET_CMPLX_QUALIFIED data
* structure.
*
* This function sets the specific parameters which are CPU/Arch dependent
* and it will be called by wrhvAmpCpuEnable before resuming the Virtual Board
* during the GuestOS wrload operation. Note that the register-width is assumed
* to be 32bits.
*
* ERRNO: - N/A
* RETURNS:None
* \NOMANUAL
*
*/

_WRS_INLINE void wrhvAmpCpuHreg32Set
    (
    VBI_HREG_SET_CMPLX_QUALIFIED *	pRegSet,
    FUNCPTR             		entryPt,
    vbiGuestPhysAddr_t  		cfgAddr
    )
    {
    /* Set PC and Arguments in target VB hardware register set */

    pRegSet->vbiRegSet.hreg32.pc       = (INSTR *) entryPt;
    pRegSet->vbiRegSet.hreg32.r[0]     = (uint32_t) cfgAddr;
    }

#else /*_ASMLANGUAGE */

#define ARM_IMM	#

/******************************************************************************
*
* VBI_INT_VCORE_LOCK - lock a core's interrupts macro
*
* This macro disables the currently running core interrupts and returns the
* previous state.
*
* A hypercall is not needed to perform this operation. 
*
* SYNOPSIS
*\cs
* 
* VBI ARM Architecture Supplements
*
* VBI_INT_VCORE_LOCK (REG0);
*
*\ce
*
* RETURNS: nonzero if interrupts were locked, otherwise zero
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_UNLOCK(), VBI_INT_VCORE_STATE_GET()  
*/

#define VBI_INT_VCORE_LOCK(reg0, reg1, reg2)		\
        mrs     reg0, cpsr;				\
	and     reg0, reg0, ARM_IMM (I_BIT | F_BIT);		\
	cpsid	if

/*******************************************************************************
*
* VBI_INT_VCORE_UNLOCK - unlock a core's interrupts
*
* This macro enables a core's interrupts.
*
* SYNOPSIS
*\cs
* 
* VBI ARM Architecture Supplements
*
* VBI_INT_VCORE_UNLOCK (REG0);
*
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_LOCK(), VBI_INT_VCORE_STATE_GET()  
*/

#define VBI_INT_VCORE_UNLOCK(reg0, reg1);			\
        cpsie   if

/*******************************************************************************
*
* VBI_INT_VCORE_STATE_GET - Get interrupts state
*
* This macro reads the interrupt state of the currently running core. It uses
* a passed in general purpose register to store the current state of interrupts.
* The status is nonzero if locked or 0 if not locked.
*
* SYNOPSIS
*\cs
* 
* VBI ARM Architecture Supplements
*
* VBI_INT_VCORE_STATE_GET (REG0);
*
*\ce
*
* RETURNS: nonzero if interrupts are locked otherwise zero
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_LOCK(), VBI_INT_VCORE_UNLOCK()  
*/

#define VBI_INT_VCORE_STATE_GET(reg0)			\
        mrs     reg0, cpsr;				\
	and     reg0, reg0, ARM_IMM (I_BIT | F_BIT)

/*******************************************************************************
*
* VBI_CONFIG_ADDR_GET - Get virtual core configuration structure base address
*
* This macro returns the base address of the configuration structure of the 
* running core. 
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro for PPC assembly code
*
* VB_CONFIG * VBI_CONFIG_ADDR_GET (void)
*
*\ce
*
* RETURNS: virtual core configuration structure base address
*
* ERROR CODES: N/A
*
* SEE ALSO: 
*/

#define VBI_CONFIG_ADDR_GET(reg)		    \
	ldr	reg, =wrhvVbConfig;                 \
	ldr     reg, [reg]

/*******************************************************************************
*
* VBI_CNTRL_ADDR_GET - Get virtual core control structure base address
*
* This macro returns the base address of the running virtual core's control
* structure.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_CONTROL * VBI_CNTRL_ADDR_GET (void)
*
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO: 
*/

#define VBI_CNTRL_ADDR_GET(reg)			    \
	ldr	reg, =wrhvVbControl;                \
	ldr     reg, [reg]

/*******************************************************************************
*
* VBI_STATUS_ADDR_GET - Get virtual core status structure address
*
* This macro returns the base address of the status structure of currently
* running core. This structure is read-only and contains a description of
* the running virtual core. Hypervisor uses this data to inform the
* virtual board time variant data that may be updated during hypervisor context
* Switch. Typical that are available in the status structure are:
*
*\ms
*\m - 
*Timer tick counter
*\m -
*Pending interrupt state
*\m -
*The interrupt state before this core was schedule
*\m -
*VMMU configuration
*\m -
*Virtual core registers state
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_STATUS * VBI_STATUS_ADDR_GET(void)
*
*\ce
*
* RETURNS: virtual core configuration structure base address
*
* ERROR CODES: N/A
*
* SEE ALSO: 
*/

#define VBI_STATUS_ADDR_GET(reg)		    \
	ldr	reg, =wrhvVbStatus;                 \
	ldr     reg, [reg]

#endif /*_ASMLANGUAGE */
    
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __INCvbiPpcArchh */
