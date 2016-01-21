/* vbiPpcArch.h - PowerPC architecture specific definitions */

/*
 * Copyright (c) 2008-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01v,06jun12,kk   added back the use of VBI_PPC_E500MC (WIND00420036)
01u,04dec12,jpb  Added VSB option for PISA_EHV
01t,04apr11,jlv  Sync with HV 1.3 01-Apr-11(WIND00265419)
01s,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01r,12jun10,rab  save and restore r3-r7 in VBI_INT_VCORE_PEND_CHECK
01q, 3mar10,rgo  Sync with HV1.2 view on 3/3/10
01p,24feb10,rgo  Introduce guestOS inline wrhvAmpCpuHreg32Set.
01o,25jan09,to   add VIRT_TO_PHYS_CPU_NUM to mdio messages
01n,02nov09,to   e500mc support
01m,07oct09,d_c  Defect WIND00185185 Fix WIND00185188 - Fix apigen errors
01l,21sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
01k,12aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD, HV 1.1 version 01r
01j,16jul09,d_c  Fix bug in VBI_INT_VCORE_UNLOCK
01i,13jul09,to   fix comment of int locking macro
01h,01jul09,to   import vbiPpcArch.h, v01l from HV 1.1
01g,26may09,md   adapted for VxWorks 6.7
01f,14may09,pmr  WIND00166320 - fix MSR macro
01e,21apr09,rec  WIND00160134 - documentation updates
01d,09apr09,pmr  CQ144306: GuestOS MSR
01c,28jan09,dtr  Use new structures.
01b,23jan09,mmi  add debug registers
01a,21jan09,mmi  created
*/

#ifndef __INCvbiPpcArchh
#define __INCvbiPpcArchh


#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WRS_CONFIG_VBI_PPC_E500MC) || defined(_WRS_CONFIG_PISA_EHV)
/* VB supports PowerISA, category Embedded.Hypervisor */
#define _VB_PISA_EHV
#endif

/* PPC uses big endian byte ordering */

#define __VBI_BYTE_ORDER __VBI_BIG_ENDIAN

/* VIOAPIC number of entries */

#define VB_VIOAPIC_ENTRIES_SIZE		    64 

#define _WRHV_ARCH_HAS_STATUS_REGS	    1
#define _WRHV_ARCH_HAS_CTRL_REGS	    1

#define VB_STATUS_REGS_OFFSET_BASE	 0
#define VB_STATUS_SRR0			(4 * (VB_STATUS_REGS_OFFSET_BASE +0))
#define VB_STATUS_SRR1			(4 * (VB_STATUS_REGS_OFFSET_BASE +1))
#define VB_STATUS_CR			(4 * (VB_STATUS_REGS_OFFSET_BASE +2))
#define VB_STATUS_LR			(4 * (VB_STATUS_REGS_OFFSET_BASE +3))
#define VB_STATUS_R3			(4 * (VB_STATUS_REGS_OFFSET_BASE +4))
#define VB_STATUS_R4			(4 * (VB_STATUS_REGS_OFFSET_BASE +5))
#define VB_STATUS_MCSRR0		(4 * (VB_STATUS_REGS_OFFSET_BASE +6))
#define VB_STATUS_MCSRR1		(4 * (VB_STATUS_REGS_OFFSET_BASE +7))
#define VB_STATUS_ESR			(4 * (VB_STATUS_REGS_OFFSET_BASE +8))
#define VB_STATUS_MCSR			(4 * (VB_STATUS_REGS_OFFSET_BASE +9))
#define VB_STATUS_MCAR			(4 * (VB_STATUS_REGS_OFFSET_BASE +10))
#define VB_STATUS_DEAR			(4 * (VB_STATUS_REGS_OFFSET_BASE +11))
#define VB_STATUS_EMSR			(4 * (VB_STATUS_REGS_OFFSET_BASE +12))
#define VB_STATUS_ESRR0			(4 * (VB_STATUS_REGS_OFFSET_BASE +13))
#define VB_STATUS_ESRR1			(4 * (VB_STATUS_REGS_OFFSET_BASE +14))
#define VB_STATUS_SPEFSCR               (4 * (VB_STATUS_REGS_OFFSET_BASE +15)) 
#define VB_STATUS_ASID                  (4 * (VB_STATUS_REGS_OFFSET_BASE +16)) 
#define VB_STATUS_VMMU_HANDLE           (4 * (VB_STATUS_REGS_OFFSET_BASE +17)) 
#define VB_STATUS_RESERVED1_0           (4 * (VB_STATUS_REGS_OFFSET_BASE +15)) 
#define VB_STATUS_RESERVED1_1           (4 * (VB_STATUS_REGS_OFFSET_BASE +16)) 
#define VB_STATUS_RESERVED1_2           (4 * (VB_STATUS_REGS_OFFSET_BASE +17)) 
#define VB_STATUS_RESERVED1_3           (4 * (VB_STATUS_REGS_OFFSET_BASE +18)) 
#define VB_STATUS_RESERVED1_4           (4 * (VB_STATUS_REGS_OFFSET_BASE +19)) 
#define VB_STATUS_RESERVED1_5           (4 * (VB_STATUS_REGS_OFFSET_BASE +20)) 
#define VB_STATUS_RESERVED1_6           (4 * (VB_STATUS_REGS_OFFSET_BASE +21)) 
#define VB_STATUS_RESERVED1_7           (4 * (VB_STATUS_REGS_OFFSET_BASE +22)) 
#define VB_STATUS_SVR			(4 * (VB_STATUS_REGS_OFFSET_BASE +23)) 
#define VB_STATUS_PIR			(4 * (VB_STATUS_REGS_OFFSET_BASE +24)) 
#define VB_STATUS_PVR			(4 * (VB_STATUS_REGS_OFFSET_BASE +25)) 
#define VB_STATUS_HID0			(4 * (VB_STATUS_REGS_OFFSET_BASE +26)) 
#define VB_STATUS_HID1			(4 * (VB_STATUS_REGS_OFFSET_BASE +27)) 
#define VB_STATUS_BUSCR			(4 * (VB_STATUS_REGS_OFFSET_BASE +28)) 
#define VB_STATUS_L1CSR0		(4 * (VB_STATUS_REGS_OFFSET_BASE +29)) 
#define VB_STATUS_L1CSR1		(4 * (VB_STATUS_REGS_OFFSET_BASE +30)) 
#define VB_STATUS_RESERVED2_0           (4 * (VB_STATUS_REGS_OFFSET_BASE +31)) 
#define VB_STATUS_RESERVED2_1           (4 * (VB_STATUS_REGS_OFFSET_BASE +32)) 
#define VB_STATUS_RESERVED2_2           (4 * (VB_STATUS_REGS_OFFSET_BASE +33)) 
#define VB_STATUS_RESERVED2_3           (4 * (VB_STATUS_REGS_OFFSET_BASE +34)) 
#define VB_STATUS_RESERVED2_4           (4 * (VB_STATUS_REGS_OFFSET_BASE +35)) 
#define VB_STATUS_RESERVED2_5           (4 * (VB_STATUS_REGS_OFFSET_BASE +36)) 
#define VB_STATUS_RESERVED2_6           (4 * (VB_STATUS_REGS_OFFSET_BASE +37)) 
#define VB_STATUS_RESERVED2_7           (4 * (VB_STATUS_REGS_OFFSET_BASE +38)) 
#define VB_STATUS_RESERVED2_8           (4 * (VB_STATUS_REGS_OFFSET_BASE +39)) 


#define VB_STATUS_REG_STRUCT_END	(4 * (VB_STATUS_REGS_OFFSET_BASE +40))

/* Bit Mask definitions for VB_STATUS_INT_PENDING */

#define VB_STATUS_INT_PENDING_INT        1	/* Interrupt controller */
#define VB_STATUS_INT_PENDING_TICK       2	/* Tick interrupt */


#define VB_CONTROL_REGS_OFFSET_BASE	 0
#define VB_CONTROL_SRR0			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 0))
#define VB_CONTROL_SRR1			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 1))
#define VB_CONTROL_CR			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 2))
#define VB_CONTROL_R0			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 3))
#define VB_CONTROL_R1			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 4))
#define VB_CONTROL_SP			VB_CONTROL_R1
#define VB_CONTROL_R2			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 5))
#define VB_CONTROL_R3			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 6))
#define VB_CONTROL_R4			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 7))
#define VB_CONTROL_R5			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 8))
#define VB_CONTROL_R6			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 9))
#define VB_CONTROL_R7			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 10))
#define VB_CONTROL_R8			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 11))
#define VB_CONTROL_R9			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 12))
#define VB_CONTROL_R10			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 13))
#define VB_CONTROL_R11			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 14))
#define VB_CONTROL_R12			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 15))
#define VB_CONTROL_R13			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 16))
#define VB_CONTROL_EMSR			(4 * (VB_CONTROL_REGS_OFFSET_BASE + 17))
#define VB_CONTROL_DBSR		        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 18))
#define VB_CONTROL_DBCR0	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 19))
#define VB_CONTROL_DBCR1       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 20))
#define VB_CONTROL_DBCR2       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 21))
#define VB_CONTROL_IAC1       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 22))
#define VB_CONTROL_IAC2       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 23))
#define VB_CONTROL_DAC1       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 24))
#define VB_CONTROL_DAC2       	        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 25))
#define VB_CONTROL_SPEFSCR		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 26))
#define VB_CONTROL_ASID		        (4 * (VB_CONTROL_REGS_OFFSET_BASE + 27))
#define VB_CONTROL_VMMU_HANDLE		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 28))
#define VB_CONTROL_RESERVED0		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 26))
#define VB_CONTROL_RESERVED1		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 27))
#define VB_CONTROL_RESERVED2		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 28))
#define VB_CONTROL_RESERVED3		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 29))
#define VB_CONTROL_RESERVED4		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 30))
#define VB_CONTROL_RESERVED5		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 31))
#define VB_CONTROL_RESERVED6		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 32))
#define VB_CONTROL_RESERVED7		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 33))
#define VB_CONTROL_RESERVED8		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 34))
#define VB_CONTROL_RESERVED9		(4 * (VB_CONTROL_REGS_OFFSET_BASE + 35))

/* status register size for ppc */

#define VB_CONTROL_REG_STRUCT_END	(4 * (VB_CONTROL_REGS_OFFSET_BASE + 36))

/* mdio messages */
#define MDIO_READ	    1
#define MDIO_WRITE	    2
#define MDIO_INT_ENABLE	    3
#define MDIO_INT_DISABLE    4
#define BSP_CLK_FREQ	    5
#define VIRT_TO_PHYS_CPU_NUM	6
#define BSP_CORE_FREQ       7

#ifndef _ASMLANGUAGE

#define VB_STATUS_REGS_ACCESS(base, field)	\
	base->vbStatusRegs.field		

#define VB_CONTROL_REGS_ACCESS(base, field)	\
	base->vbControlRegs.field		

/*******************************************************************************
*
* VB_ARCH_CONTROL_REGS - Virtual core PPC control structure
*
* Virtual board emulated control registers. These registers are used
* by a guest running on hypervisor to configure the virtual CPU register.
*
* SYNOPSIS
*
* PPC Control structure graphical illustration
*\cs
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
*    } VB_ARCH_CONTROL_REGS;
*
*\ce
*
* SEE ALSO: VB_ARCH_CONTROL_REGS, architecture supplement document 
*\COMMAND
*\NOMANUAL
*/

typedef struct vbArchControlRegs
    {

    /* Registers to be restored by the VDK_SYS_ctx_load fast system call */

    uint32_t srr0;		/*  0: PC */
    uint32_t srr1;		/*  1: MSR */
    uint32_t cr;		/*  2: condition registers */
    uint32_t r0;		/*  3: General register R0 */
    uint32_t sp;		/*  4: General register R1 (stack pointer) */
    uint32_t r2;		/*  5: General register R2 */
    uint32_t r3;		/*  6: General register R3 */
    uint32_t r4;		/*  7: General register R4 */
    uint32_t r5;		/*  8: General register R5 */
    uint32_t r6;		/*  9: General register R6 */
    uint32_t r7;		/* 10: General register R7 */
    uint32_t r8;		/* 11: General register R8 */
    uint32_t r9;		/* 12: General register R9 */
    uint32_t r10;		/* 13: General register R10 */
    uint32_t r11;		/* 14: General register R11 */
    uint32_t r12;		/* 15: General register R12 */
    uint32_t r13;		/* 16: General register R13 */

    /* emulated registers used by the VDK_SYS_ctx_load_vmmu system call */

    uint32_t emsr;		/* 17: emulated MSR register */

    /* Debug control registers */
    
    uint32_t     dbsr; /* 18 - debug status register */

    /* Debug control registers */
    
    uint32_t     dbcr0; /* 19 - debug control register 0 */
    uint32_t     dbcr1; /* 20 - debug control register 1 */
    uint32_t     dbcr2; /* 21 - debug control register 2 */

    /* instruction address compare registers IAC1-IAC2 */

    uint32_t     iac1; /* 22 - instructions access control 1 */
    uint32_t     iac2; /* 23 - instructions access control 2 */

    /* data address compare registers DAC1-DAC2. */

    uint32_t     dac1; /* 24 - instructions access control 3 */
    uint32_t     dac2; /* 25 - instructions access control 4 */
#if (CPU==PPC85XX)
    uint32_t     spefscr; /* 26 - SPE float status control */
#else
    uint32_t     reserved1;       /* 26: Reserved */
#endif
    uint32_t     asid;    /* 27 - Emulated ASID */
    uint32_t     vmmuHandle;    /* 28 - vmmuHandle */
    /* reserved fields for future use */

    uint32_t reserved[7];       /* 29: Reserved */
    } VB_ARCH_CONTROL_REGS;

/*******************************************************************************
*
* VB_ARCH_STATUS_REGS - Virtual core PPC emulated status registers
*
* Virtual board emulated CPU status registers
*
* SYNOPSIS
*
* PPC Status structure graphical illustration
*\cs
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
*       |---------------|  Registers saved during exception handling
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
*       | reserved[8]   |      8 x 32bits for future enhancements
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
*
*    } VB_ARCH_STATUS_REGS; 
*
*
*\ce
*
* SEE ALSO: VB_STATUS 
*\COMMAND
*\NOMANUAL
*/

typedef struct archStatusRegs
    {

    /* 
     * registers saved by WRHV for all interrupts exceptions
     * before setting the PC in the virtual board to the exception/interrupt
     * vector address
     */

    uint32_t srr0; /* 0: PC at time of the interrupt */
    uint32_t srr1; /* 1: MSR at time of the interrupt */
    uint32_t cr;   /* 2: Condition registers at time of the interrupt */
    uint32_t lr;   /* 3: Link register at time of the interrupt */
    uint32_t r3;   /* 4: R3 at time of the interrupt */
    uint32_t r4;   /* 5: R4 at time of the interrupt */

    /* Registers saved by WRHV during exception processing only */

    uint32_t mcsrr0; /*  6: */
    uint32_t mcsrr1; /*  7: */
    uint32_t esr;    /*  8: */
    uint32_t mcsr;   /*  9: */
    uint32_t mcar;   /* 10  */
    uint32_t dear;   /* 11: */
    uint32_t emsr;   /* 12: */
    uint32_t esrr0;  /* 13: */
    uint32_t esrr1;  /* 14: */
#if (CPU==PPC85XX)
    uint32_t spefscr;  /* 15: */
#else
    uint32_t reserved1; /* 15  */
#endif
    uint32_t asid;     /* 16: */
    uint32_t vmmuHandle; /* 17 */
/* 
 * keep this part in a separate structure in order to keep the offsets
 * to remain the same as in VB_STATUS
 */

    /* reserved fields for future use */

    uint32_t reserved2[5]; /* 18 - 22  */

    /* Configuration registers (only updated upon board creation */

    uint32_t svr;     /* 23 */     
    uint32_t pir;     /* 24 */
    uint32_t pvr;     /* 25 */  
    uint32_t hid0;    /* 26 */
    uint32_t hid1;    /* 27 */
    uint32_t bucsr;   /* 28 */
    uint32_t l1csr0;  /* 29 */
    uint32_t l1csr1;  /* 30 */
    
    /* reserved fields for future use */

    uint32_t reserved3[9]; /* 31 - 39 */

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
*     uint32_t gpr[GREG_NUM];	/@ general purpose registers @/
*     uint32_t msr;		/@ machine state register @/
*     uint32_t lr;		/@ link register @/
*     uint32_t ctr;		/@ count register @/
*     uint32_t pc;		/@ program counter @/
*     uint32_t cr;		/@ condition register @/
*     uint32_t xer;		/@ fixed-point exception register @/
*     uint32_t spefscr;		/@ SPE floating-point status & ctrl reg @/
*     uint32_t casid;		/@ PPC405, Book E PID and PPC860 M_CASID @/
*     } VBI_HREG_SET;
* 
*
*\ce
* SEE ALSO: NONE
* 
*\NOMANUAL
* 
*/

#define GREG_NUM	32	/* has 32 32/64-bit data registers */

typedef struct
    {
    uint32_t gpr[GREG_NUM];	/* general purpose registers */
    uint32_t msr;		/* machine state register */
    uint32_t lr;		/* link register */
    uint32_t ctr;		/* count register */
    uint32_t pc;		/* program counter */
    uint32_t cr;		/* condition register */
    uint32_t xer;		/* fixed-point exception register */
    uint32_t spefscr;		/* SPE floating-point status & ctrl reg */
    uint32_t casid;		/* PPC405, Book E PID and PPC860 M_CASID */
    } HREG_SET;

/* VBI_HREG_SET is same as HREG_SET in ppc */
typedef HREG_SET VBI_HREG_SET;


/*******************************************************************************
*
* VBI_HREG_SET_64 - hardware register set, for read/write
*
* Used by vbiVbRegisterComplexRead/vbiVbRegisterComplexWrite to read/write
* registers in another VB
* 
* SYNOPSIS
*
* VB hardware register set C data structure type definition
*
*\cs
*
* typedef struct
*     {
*     uint64_t gpr[GREG_NUM];	/@ general purpose registers @/
*     uint64_t msr;		/@ machine state register @/
*     uint64_t lr;		/@ link register @/
*     uint64_t ctr;		/@ count register @/
*     uint64_t pc;		/@ program counter @/
*     uint64_t cr;		/@ condition register @/
*     uint64_t xer;		/@ fixed-point exception register @/
*     uint64_t spefscr;		/@ SPE floating-point status & ctrl reg @/
*     uint64_t casid;		/@ PPC405, Book E PID and PPC860 M_CASID @/
*     } VBI_HREG_SET_64;
* 
*
*\ce
* SEE ALSO: NONE
* 
*/

typedef struct
    {
    uint64_t gpr[GREG_NUM];	/* general purpose registers */
    uint64_t msr;		/* machine state register */
    uint64_t lr;		/* link register */
    uint64_t ctr;		/* count register */
    uint64_t pc;		/* program counter */
    uint64_t cr;		/* condition register */
    uint64_t xer;		/* fixed-point exception register */
    uint64_t spefscr;		/* SPE floating-point status & ctrl reg */
    uint64_t casid;		/* PPC405, Book E PID and PPC860 M_CASID */
    } HREG_SET_64;

/* VBI_HREG_SET_64 is same as HREG_SET_64 in ppc */
typedef HREG_SET_64 VBI_HREG_SET_64;


/* complex register set definition */

typedef union
    {
    VBI_HREG_SET    hreg32;	/* 32 bit register set */
    VBI_HREG_SET_64 hreg64;     /* 64 bit register set */
    } VBI_HREG_SET_CMPLX;


typedef struct
    {
    vbiRegSet_t        vbiRegType;
    VBI_HREG_SET_CMPLX vbiRegSet;
    } VBI_HREG_SET_CMPLX_QUALIFIED;

/* mdio messages */

#define VBI_MDIO_READ           MDIO_READ
#define VBI_MDIO_WRITE          MDIO_WRITE
#define VBI_BSP_CLK_FREQ        BSP_CLK_FREQ
#define VBI_BSP_CORE_FREQ       BSP_CORE_FREQ

/* This should exceed the number of IVOR registers defined in the hardware 
* It also defined the size of the excVectorTable size 
* VBI_ARCH_MAX_EXC_OFFSETS * 256 == 0x4000 */
#define VBI_ARCH_MAX_EXC_OFFSETS	64	

typedef struct
    {
    uint32_t excOffset[VBI_ARCH_MAX_EXC_OFFSETS];
    } VBI_EXC_OFFSETS_TABLE;

extern status_t vbiExcOffsetsSet(VBI_EXC_OFFSETS_TABLE *excOffsetsTable);
extern status_t vbiExcOffsetsGet(VBI_EXC_OFFSETS_TABLE *excOffsetsTable);

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

    union 
	{
    	struct 
	    {
	    uint32_t vcore;
	    } v2pCpuNum;
    	struct 
	    {
	    uint32_t bus;		
	    uint32_t phyAddr;
	    uint32_t regNum;
	    uint32_t page;
	    } mdioRead;
    	struct 
	    {
	    uint32_t bus;		
	    uint32_t phyAddr;
	    uint32_t regNum;
	    uint32_t page;
	    uint32_t dataVal;
	    } mdioWrite;
#if 0 /* not supported for now */
    	struct 
	    {
	    uint32_t bus;		
	    uint32_t vbIntNum;
	    HY_CTX *pCtx;
	    } mdioIntEnable;
    	struct 
	    {
	    uint32_t bus;	
	    uint32_t vbIntNum;
	    HY_CTX *pCtx;
	    } mdioIntDisable;
#endif
	} arg;				
    
    } VBI_BSP_MSG;

typedef struct 
    {
    VBI_MSG_HEADER hdr;			/* message header */
    uint32_t   status;			/* request completion status */
    uint32_t   dataVal;
    } VBI_BSP_MSG_REPLY;

extern void vbiCtxLoad();

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
    /* Set PC, MSR and Arguments in target VB hardware register set */

    pRegSet->vbiRegSet.hreg32.pc       = (uint32_t)entryPt;
    pRegSet->vbiRegSet.hreg32.gpr[3]   = (uint32_t) cfgAddr;
    #ifdef _WRS_CONFIG_VBI_PPC_E500MC
    pRegSet->vbiRegSet.hreg32.msr      = 0x10000000;
    #else /* E500 */
    pRegSet->vbiRegSet.hreg32.msr      = 0x0202d030;
    #endif
    }
#else /*_ASMLANGUAGE */

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

#define VBI_CONFIG_ADDR_GET(reg)		 \
	lis	reg, HIADJ(wrhvVbConfig)	;\
	lwz	reg, LO(wrhvVbConfig)(reg)

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

#define VBI_CNTRL_ADDR_GET(reg)			\
	lis	reg, HIADJ(wrhvVbControl);	\
	lwz	reg, LO(wrhvVbControl)(reg)

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

#define VBI_STATUS_ADDR_GET(reg)		\
	lis	reg, HIADJ(wrhvVbStatus);	\
	lwz	reg, LO(wrhvVbStatus)(reg)


#ifdef	_VB_PISA_EHV

/* w/ PowerISA Embedded.Hypervisor */

#define	HCALL			sc	1
#define	VB_SET_EE		wrteei	1
#define	VB_CLEAR_EE		wrteei	0

#define TLBWE_CODE		0x7c0007a4
#define TLBRE_CODE		0x7c000764
#define TLBIVAX_OPCODE		0x7c000e24

#define LD_TLBWE_IN_P0				 \
	lis	p0, HIADJ(TLBWE_CODE)		;\
	addi	p0, p0, LO(TLBWE_CODE)

#else	/* !_VB_PISA_EHV */

#define _VB_NO_MSR
#define	HCALL			sc

#endif	/* !_VB_PISA_EHV */

#define VBI_INT_VCORE_PEND_CHECK(reg)				 \
	stwu	sp, -20(sp); \
	stw	r3, 0x0(sp) ; \
	stw	r4, 0x4(sp) ; \
	stw	r5, 0x8(sp) ; \
	stw	r6, 0x0C(sp) ; \
	stw	r7, 0x10(sp) ; \
1:								 \
	VBI_STATUS_ADDR_GET(reg)				;\
	lwz	reg, VB_STATUS_INT_PENDING(reg)			;\
	cmplwi	reg, 0	/* may need to make a hypercall*/	;\
	beq	2f						;\
	lis	r0, HI(VBI_SYS_int_enable)			;\
	ori	r0, r0, LO(VBI_SYS_int_enable)			;\
	HCALL							;\
	b	1b						;\
2: \
	lwz	r3, 0x0(sp) ; \
	lwz	r4, 0x4(sp) ; \
	lwz	r5, 0x8(sp) ; \
	lwz	r6, 0xC(sp) ; \
	lwz	r7, 0x10(sp) ; \
	addi	sp, sp, 20 



/*******************************************************************************
*
* VBI_CTX_LOAD - Load a guest context
*
* This routine is implemented as an assembly MACRO since it's callers can't
* reference C functions. This MACRO makes a hypercall to load a context for a
* guest OS. The guest OS running on the core is expected to store a set of
* registers that represent the new context to load in the it's control structure
* then call VBI_CTX_LOAD() MACRO to switch to the new context. The Following are
* the registers loaded from the control structure:
*
*\ms
*\m 1 -
* VB_CONTROL_SRR0	     ------->  SRR0
*\m 2 -
* VB_CONTROL_SRR1	     -------> SRR1 
*\m 3 -
* VB_CONTROL_CR		     -------> CR
*\m 4 -
* VB_CONTROL_R0		     -------> R0
*\m 5 -
* VB_CONTROL_EMSR	     -------> MSR 
*\m 6 -
* VB_CONTROL_DBCR0	     -------> DBCR0 
*\m 7 -
* VB_CONTROL_NEW_INT_DISABLE -------> VB_CONTROL_INT_DISABLE 
* If interrupts are being reenabled then we ensure that any pending interrupts
* are delivered before the new context is activated.
*
* Note that registers that are not saved by Hypervisor must be loaded by the
* guest OS.
*
* SYNOPSIS
*\cs
* 
* VBI PPC Architecture Supplements
*
* void  VBI_CTX_LOAD () 
*
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO: VBI_INT_VCORE_LOCK(), VBI_INT_VCORE_UNLOCK(), 
*           VBI_INT_VCORE_STATE_GET()
*/

#ifndef	_VB_PISA_EHV
#define VBI_CTX_LOAD(reg)				    \
	lis	reg, HI(VBI_SYS_ctx_load);		    \
	ori	reg, reg, LO(VBI_SYS_ctx_load);		    \
	sc
#endif	/* !_VB_PISA_EHV */

/******************************************************************************
*
* VBI_INT_VCORE_LOCK - lock a core's interrupts macro
*
* This MACRO disables the currently running core interrupts and returns the
* previous interrupts state. The interrupt status field in wrhvVbControl
* structure at offset VB_CONTROL_INT_DISABLE is set to -1 and the previous
* interrupts state is loaded to the register passed in as the first argument to
* this MACRO. 
* A hypercall is not needed to perform this operation. 
*
* SYNOPSIS
*\cs
* 
* VBI PPC Architecture Supplements
*
* VBI_INT_VCORE_LOCK (reg0, reg1, reg2)	\
*	{
*	load -1 to reg1
*	load wrhvVbControl address to reg2
*       read the previous value and store in reg0
*	Disable interrupts by loading reg1 to VB_CONTROL_INT_DISABLE(reg2)
*	}
*\ce
*
* RETURNS: TRUE is interrupts were locked otherwise FALSE
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_UNLOCK(), VBI_INT_VCORE_STATE_GET()  
*/

#ifdef	_VB_PISA_EHV

#define VBI_INT_VCORE_LOCK(reg0, reg1, reg2)		 \
	mfmsr	reg0					;\
	VB_CLEAR_EE

#else	/* !_VB_PISA_EHV */

#define VBI_INT_VCORE_LOCK(reg0, reg1, reg2)		\
	li	reg1, -1;				\
	VBI_CNTRL_ADDR_GET(reg2)			;\
        lwz     reg0, VB_CONTROL_INT_DISABLE(reg2);	\
        stw     reg1, VB_CONTROL_INT_DISABLE(reg2)		

#endif	/* !_VB_PISA_EHV */

/*******************************************************************************
*
* VBI_INT_VCORE_UNLOCK - unlock a core's interrupts
*
* This MACRO is implemented in assembly to enable a core's interrupts. It
* enables the interrupts by clearing to zero the value in the core's control
* structure and and makes a fast hypercall if need be. A hypercall is made only
* if found that interrupts are pending. The pending interrupts are checked by
* reading the wrhvVbStatus structure at offset VB_STATUS_INT_PENDING. A
* positive integer greater than zero indicates that interrupts are pending
* which causes this macro to make a hypercall in order to drain the pending
* interrupts. This MACRO expects two general purpose registers. The first 
* register is used to load the value to store and the second is used for
* holding the destination address of the control or status structure.
*
* SYNOPSIS
*\cs
* 
* VBI PPC Architecture Supplements
*
* VBI_INT_VCORE_UNLOCK (reg0, reg1) 
*	{
*	load "0" to reg1
*	load address of wrhvVbControl in reg0 
*	store reg1 to VB_CONTROL_INT_DISABLE(reg0)
*
* checkStatus:
*	load address of wrhvVbStatus in reg0
*       load VB_STATUS_INT_PENDING(reg0) in reg1
*       check if reg1 is equal to zero
*       if true return
*	otherwise send an hypercall 
*       go to checkStatus
*	}
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_LOCK(), VBI_INT_VCORE_STATE_GET()  
*/

#ifdef	_VB_PISA_EHV

#define VBI_INT_VCORE_UNLOCK(reg0, reg1)			 \
	VB_SET_EE						;\
	VBI_INT_VCORE_PEND_CHECK(reg0)

#else	/* !_VB_PISA_EHV */

#define VBI_INT_VCORE_UNLOCK(reg0, reg1)			 \
	VBI_CNTRL_ADDR_GET(reg0)				;\
	li	reg1, 0;					\
	stw	reg1, VB_CONTROL_INT_DISABLE(reg0);		\
	VBI_INT_VCORE_PEND_CHECK(reg0)

#endif	/* !_VB_PISA_EHV */

#ifdef	_VB_PISA_EHV

#define _PPC_MSR_EE 0x8000
#define _PPC_MSR_BIT_EE 16

#define VBI_INT_VCORE_UNLOCK_WITH_ORIG(reg0, reg1, orig)	 \
	rlwinm. reg0, orig, 0, _PPC_MSR_BIT_EE, _PPC_MSR_BIT_EE	;\
	beq-	0f						;\
	VBI_INT_VCORE_UNLOCK(reg0, reg1)			;\
0:

#else	/* !_VB_PISA_EHV */

#define VBI_INT_VCORE_UNLOCK_WITH_ORIG(reg0, reg1, orig)	 \
	cmplwi  orig, 0						;\
	bne-    0f						;\
	VBI_INT_VCORE_UNLOCK(reg0, reg1)			;\
0:

#endif	/* !_VB_PISA_EHV */

/*******************************************************************************
*
* VBI_INT_VCORE_STATE_GET - Get interrupts state
*
* This MACRO is implemented in assembly to read the interrupt state of the
* currently running core. It relies on a passed in general purpose register
* to store the current state of interrupts. The status is -1 if locked
* otherwise 0.
*
* SYNOPSIS
*\cs
* 
* VBI PPC Architecture Supplements
*
* VBI_INT_VCORE_STATE_GET (reg0)
*	{
*       Load the interrupt status from wrhvVbControl to reg0
*	}
*\ce
*
* RETURNS: TRUE if interrupts are locked otherwise FALSE
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIntVCoreLock(), vbiIntVCoreUnlock(), vbiIntVCoreStateGet(),
*	    VBI_INT_VCORE_LOCK(), VBI_INT_VCORE_UNLOCK()  
*/

#ifndef	_VB_PISA_EHV
#define VBI_INT_VCORE_STATE_GET(reg0)				\
	VBI_CNTRL_ADDR_GET(reg0);				\
       lwz     reg0, VB_CONTROL_INT_DISABLE(reg0)
#endif	/* !_VB_PISA_EHV */


/* vxWorks GuestOS specific definitions */

#ifndef	_VB_PISA_EHV

#define _PPC_MSR_EE 0x8000
#define _PPC_MSR_BIT_EE 16

/*
 * Interrupt disable load / store macros
 *
 * These macros come in two types: one which operates with a REG_SET, and
 * one with a TCB.  The latter is identified by the _TCB suffix.
 *
 * These are needed because the hypervisor uses the values 0 and -1 to mean
 * interrupts are enabled or disabled, respectively.  We store this value
 * here as the MSR[EE] bit, so that the meaning of the MSR field is consistent.
 *
 * The store macros do the following:
 * 1.  Decide whether interrupts are being enabled or disabled
 * 2a. If being enabled, load MSR value from REG_SET or TCB and set MSR[EE]
 * 2b. If being disabled, load MSR value from REG_SET or TCB and clear MSR[EE]
 * 3.  Store new MSR value to REG_SET or TCB
 * 4.  Restore the register which originally contained 0 or -1
 *
 * The load macros do the following:
 * 1.  Load the MSR value from REG_SET or TCB
 * 2.  Translate this value to 0 or -1 based on value of MSR[EE]
 *
 */

/* reg1 contains pointer to REG_SET / TCB
 * reg2 contains value to store / load
 */
#define STORE_WRHV_INT_DISABLE(reg1, reg2)	\
	cmpwi   reg2, 0 ; \
	beq	1f ; \
	lwz	reg2, REG_SET_MSR(reg1) ;		\
	rlwinm	reg2, reg2, 0, (_PPC_MSR_BIT_EE + 1), (_PPC_MSR_BIT_EE - 1) ; \
	b	2f ; \
1:	lwz	reg2, REG_SET_MSR(reg1) ;		\
	ori	reg2, reg2, _PPC_MSR_EE ; \
2:	stw	reg2, REG_SET_MSR(reg1) ; \
	rlwinm	reg2, reg2, (_PPC_MSR_BIT_EE + 1), 31, 31;	\
	addi	reg2, reg2, -1

#define LOAD_WRHV_INT_DISABLE(reg1, reg2)		\
	lwz	reg2, REG_SET_MSR(reg1)  ;		\
	rlwinm	reg2, reg2, (_PPC_MSR_BIT_EE + 1), 31, 31;	\
	addi	reg2, reg2, -1

#define STORE_WRHV_INT_DISABLE_TCB(reg1, reg2)	\
	cmpwi   reg2, 0 ; \
	beq	1f ; \
	lwz	reg2, WIND_TCB_MSR(reg1) ;		\
	rlwinm	reg2, reg2, 0, (_PPC_MSR_BIT_EE + 1), (_PPC_MSR_BIT_EE - 1) ; \
	b	2f ; \
1:	lwz	reg2, WIND_TCB_MSR(reg1) ;		\
	ori	reg2, reg2, _PPC_MSR_EE ; \
2:	stw	reg2, WIND_TCB_MSR(reg1) ; \
	rlwinm	reg2, reg2, (_PPC_MSR_BIT_EE + 1), 31, 31;	\
	addi	reg2, reg2, -1

#define LOAD_WRHV_INT_DISABLE_TCB(reg1, reg2)		\
	lwz	reg2, WIND_TCB_MSR(reg1)  ;		\
	rlwinm	reg2, reg2, (_PPC_MSR_BIT_EE + 1), 31, 31;	\
	addi	reg2, reg2, -1

#endif	/* !_VB_PISA_EHV */

#endif /*_ASMLANGUAGE */
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvbiPpcArchh */
