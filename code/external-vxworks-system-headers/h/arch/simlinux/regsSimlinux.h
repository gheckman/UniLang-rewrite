/* regsSimnt.h - simnt registers header */

/*
 * Copyright (c) 1997-1998,2003-2004,2006-2008,2010,2011
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01w,05sep11,elp  added CPUID type and definitions (CQID: WIND00286339).
01v,24jun11,elp  added fsBase to regset for tools (CQ:WIND00278823).
01u,04jan11,elp  added simulator specific TCB for fsBase (CQ:WINd00247541).
01t,29jul10,elp  fixed VXSIM_SIMSTATUS_VALUE_GET()
01s,18jun10,elp  added address register in VXSIM_SIMSTATUS_VALUE_GET().
01r,13apr10,elp  added ELFAGS_BRANDNEW define, replaced ULONG by VXSIM_ULONG.
01q,29apr10,pad  Moved extern C statement after include statements.
01p,01mar10,elp  64bits support.
01o,27may08,elp  fixed warnings.
01n,05jan07,elp  added pSimStatus and pSimIntPendingLvl declarations,
		 added interrupt level macros.
01m,17oct06,elp  added WIND_CPU_STATE.
01l,31aug04,jmp  made SIMLINUX REG_SET indentical to SIMNT.
01k,01dec03,jmp  added mmuTransTbl (current MMU translation table) to REG_SET.
01j,24nov03,jeg  added macros to manage supervisor bit
01i,14nov03,jmp  added SIM_STATUS_USR.
01h,18sep03,jeg  removed SIM_STATUS_INIT macro.
01g,12sep03,jeg  updated REG_SET structure to split intLockKey by a status bit
                 field. Removed the WIND_TCB_* macros.
01f,27may03,jmp  added Register offsets in TCB.
01e,26mar03,jmp  replaced INSTR by UCHAR to use this file from host side.
01d,17mar03,jmp  renamed macros REG_* in REG_SET_*.
01c,16jan03,elp  added REGS defines (SPR #84278).
01b,29apr98,cym  added intLockKey
01a,27aug97,cym  written
*/

#ifndef __INCregsSimnth
#define __INCregsSimnth

#ifndef HOST
#include <vsbConfig.h>
#include <types/vxArch.h>
#endif /* HOST */

#ifdef __cplusplus
extern "C" {
#endif

#define EFLAGS_BRANDNEW		0x10202

#ifdef _WRS_CONFIG_LP64

#ifndef _ASMLANGUAGE

#define GREG_NUM	16	/* has 64-bit general registers */

typedef struct		/* REG_SET - simnt register set (based on x86_64) */
    {
    UINT32	reg_status;	/* status bit field */
    UINT32	unused;		
    VXSIM_ULONG	mmuTransTbl; 	/* current MMU translation table */
    VXSIM_ULONG	r15;	/* general register */
    VXSIM_ULONG	r14;	/* general register */
    VXSIM_ULONG	r13;	/* general register */
    VXSIM_ULONG	r12;	/* general register */
    VXSIM_ULONG	r11;	/* general register */
    VXSIM_ULONG	r10;	/* general register */
    VXSIM_ULONG	r9;	/* general register */
    VXSIM_ULONG	r8;	/* general register */
    VXSIM_ULONG	rdi;	/* general register */
    VXSIM_ULONG	rsi;	/* general register */
    VXSIM_ULONG	rbp;	/* frame pointer register */
    VXSIM_ULONG	rsp;	/* stack pointer register */
    VXSIM_ULONG	rbx;	/* general register */
    VXSIM_ULONG	rdx;	/* general register */
    VXSIM_ULONG	rcx;	/* general register */
    VXSIM_ULONG	rax;	/* general register */
    VXSIM_ULONG	rflags;	/* status register */
    UCHAR *	pc;	/* program counter */
    VXSIM_ULONG	fsBase;	/* fsBase for tool easy access,
    			 * synchronized with extraRegs value when saving, 
			 * never used when loading */
    } REG_SET;

typedef struct		/* SIM_REG_SET - simulator specific part of TCB */
    {
    VXSIM_ULONG		fsBase;
    } SIM_REG_SET;

/* some common names for registers */

#undef spReg
#undef pc
#define	fpReg	rbp	/* frame pointer */
#define spReg	rsp	/* stack pointer */
#define flReg	rflags	/* flags register */
#define eflags	rflags

#define reg_pc			pc
#define reg_sp			spReg
#define reg_fp			fpReg

#define G_REG_BASE		0x10	/* data reg's base offset to REG_SET */
#define G_REG_OFFSET(n)		(G_REG_BASE + (n) * sizeof(VXSIM_ULONG))
#define SR_OFFSET		G_REG_OFFSET(GREG_NUM)
#define PC_OFFSET		(SR_OFFSET + sizeof(VXSIM_ULONG))

#else /* _ASMLANGUAGE */

#define VXSIM_SIMSTATUS_ADDR_GET(reg)	\
	movabsq	$VAR(pSimStatus),reg;	\
	mov (reg),reg

#define VXSIM_SIMSTATUS_VALUE_GET(addrRegSuffix,valRegSuffix)	\
	movabsq	$VAR(pSimStatus),%r##addrRegSuffix;	\
	mov	(%r##addrRegSuffix), %r##addrRegSuffix;	\
	movl	0x0(%r##addrRegSuffix),%e##valRegSuffix;

#endif /* _ASMLANGUAGE */

/* Register offsets */

#define REG_SET_SIMSTATUS	0x00
#define REG_SET_MMU_TRANS_TBL	0x08
#define REG_SET_R15		0x10
#define REG_SET_R14		0x18
#define REG_SET_R13		0x20
#define REG_SET_R12		0x28
#define REG_SET_R11		0x30
#define REG_SET_R10		0x38
#define REG_SET_R9		0x40
#define REG_SET_R8		0x48
#define REG_SET_RDI		0x50
#define REG_SET_RSI		0x58
#define REG_SET_RBP		0x60
#define REG_SET_RSP		0x68
#define REG_SET_RBX		0x70
#define REG_SET_RDX		0x78
#define REG_SET_RCX		0x80
#define REG_SET_RAX		0x88
#define REG_SET_RFLAGS		0x90
#define REG_SET_RIP		0x98
#define REG_SET_PC		0x98

#else /* _WRS_CONFIG_LP64 */

#ifndef _ASMLANGUAGE

#define GREG_NUM	8

typedef struct		/* REG_SET - simnt register set (based on x86)	*/
    {
    VXSIM_ULONG	edi;		/* general register			*/
    VXSIM_ULONG	esi;		/* general register			*/
    VXSIM_ULONG	ebp;		/* general register			*/
    VXSIM_ULONG	esp;		/* general register			*/
    VXSIM_ULONG	ebx;		/* general register			*/
    VXSIM_ULONG	edx;		/* general register			*/
    VXSIM_ULONG	ecx;		/* frame pointer register		*/
    VXSIM_ULONG	eax;		/* stack pointer register		*/
    VXSIM_ULONG	eflags;		/* status register			*/
    UCHAR *	pc;		/* program counter			*/
    VXSIM_ULONG	reg_status;	/* status bit field			*/
    UINT32 	mmuTransTbl;	/* current MMU translation table	*/
    char	unused[0xc8];	/* unused - keep for SIMNT backward	*/
				/* compatibility with T2.x releases	*/
    } REG_SET;

#undef spReg
#undef pc
#define spReg			esp
#define fpReg			ebp
#define flReg			eflags

#define reg_pc			pc
#define reg_sp			spReg
#define reg_fp			fpReg

#define G_REG_BASE		0x00	/* data reg's base offset to REG_SET */
#define G_REG_OFFSET(n)		(G_REG_BASE + (n) * sizeof(VXSIM_ULONG))
#define SR_OFFSET		G_REG_OFFSET(GREG_NUM)
#define PC_OFFSET		(SR_OFFSET + sizeof(VXSIM_ULONG))

#else /* _ASMLANGUAGE */

#define VXSIM_SIMSTATUS_ADDR_GET(reg)	\
	movl 	VAR(pSimStatus),reg;	\

#define VXSIM_SIMSTATUS_VALUE_GET(addrRegSuffix,valRegSuffix)	\
	movl 	VAR(pSimStatus),%e##addrRegSuffix;	\
	movl	0x0(%e##addrRegSuffix),%e##valRegSuffix;

#endif /* _ASMLANGUAGE */

/* Register offsets */

#define REG_SET_EDI		0x00
#define REG_SET_ESI		0x04
#define REG_SET_EBP		0x08
#define REG_SET_ESP		0x0c
#define REG_SET_EBX		0x10
#define REG_SET_EDX		0x14
#define REG_SET_ECX		0x18
#define REG_SET_EAX		0x1c
#define REG_SET_EFLAGS		0x20
#define REG_SET_PC		0x24
#define REG_SET_SIMSTATUS	0x28
#define REG_SET_MMU_TRANS_TBL	0x2c

#endif /* _WRS_CONFIG_LP64 */

#ifndef _ASMLANGUAGE

typedef struct wind_cpu_state	/* CPU initial state */ 
    {
    REG_SET	regs;		/* initial register set */
    } WIND_CPU_STATE;

typedef struct cpuid		/* CPUID - 80x86 cpuid version/feature */
    {
    int highestValue;		/* EAX=0: highest integer value */
    int vendorId[3];		/* EAX=0: vendor identification string */
    int signature;		/* EAX=1: processor signature */
    int featuresEbx;		/* EAX=1: feature flags EBX */
    int featuresEcx;		/* EAX=1: feature flags ECX */
    int featuresEdx;		/* EAX=1: feature flags EDX */
    int cacheEax;		/* EAX=2: config parameters EAX */
    int cacheEbx;		/* EAX=2: config parameters EBX */
    int cacheEcx;		/* EAX=2: config parameters ECX */
    int cacheEdx;		/* EAX=2: config parameters EDX */
    int serialNo64[2];		/* EAX=3: lower 64 of 96 bit serial no */
    int brandString[12];	/* EAX=0x8000000[234]: brand strings */
    } CPUID;

extern volatile UINT32 * pSimStatus;
extern volatile UINT32 * pSimIntPendingLvl;

#define VXSIM_PENDING_INT_CHECK(minLvl)	\
    ((*pSimIntPendingLvl) > (minLvl))

#endif  /* _ASMLANGUAGE */

/* status bit fields */

#define SIM_STATUS_INTLOCK	0x0001	/* interrupt locked	*/
#define SIM_STATUS_INTUNLOCK	0x0000	/* interrupt unlocked	*/
#define SIM_STATUS_SUP		0x0002	/* supervisor mode	*/
#define SIM_STATUS_USR		0x0000	/* user mode		*/
#define SIM_STATUS_INTLVL_MASK	0x0f00	/* interrupt level mask */	
#define SIM_STATUS_INTLVL_SHIFT	8	

/* macros to access interrupt status field */

#define VXSIM_INT_MASK_SET(vxsimStatus) \
    (vxsimStatus |= SIM_STATUS_INTLOCK)

#define VXSIM_INT_MASK_CLEAR(vxsimStatus) \
    (vxsimStatus &= ~(SIM_STATUS_INTLOCK))
    
#define VXSIM_INT_MASK_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_INTLOCK) == 0) ? FALSE : TRUE)

#define VXSIM_SUP_MODE_SET(vxsimStatus) \
    (vxsimStatus |= SIM_STATUS_SUP)

#define VXSIM_USR_MODE_SET(vxsimStatus) \
    (vxsimStatus &= ~(SIM_STATUS_SUP))
    
#define VXSIM_SUP_MODE_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_SUP) == 0) ? FALSE : TRUE)

#define VXSIM_INT_LVL_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_INTLVL_MASK) >> SIM_STATUS_INTLVL_SHIFT))

#define VXSIM_INT_LVL_SET(vxsimStatus,intLvl) 			\
    (vxsimStatus = (vxsimStatus & ~SIM_STATUS_INTLVL_MASK) |	\
		    ((intLvl << SIM_STATUS_INTLVL_SHIFT) &	\
		     SIM_STATUS_INTLVL_MASK))

#define VX_CPUID_HIGHVALUE         0    /* offset to highestValue          */
#define VX_CPUID_VENDORID          4    /* offset to vendorId              */
#define VX_CPUID_SIGNATURE         16   /* offset to signature             */
#define VX_CPUID_FEATURES_EBX      20   /* offset to featuresEbx           */
#define VX_CPUID_FEATURES_ECX      24   /* offset to featuresEcx           */
#define VX_CPUID_FEATURES_EDX      28   /* offset to featuresEdx           */
#define VX_CPUID_CACHE_EAX         32   /* offset to cacheEax              */
#define VX_CPUID_CACHE_EBX         36   /* offset to cacheEbx              */
#define VX_CPUID_CACHE_ECX         40   /* offset to cacheEcx              */
#define VX_CPUID_CACHE_EDX         44   /* offset to cacheEdx              */
#define VX_CPUID_SERIALNO          48   /* offset to serialNo64            */
#define VX_CPUID_BRAND_STR         56   /* offset to brandString[0]        */
#define VX_CPUID_HIGHVALUE_EXT     104  /* offset to highestValue Extended */
#define VX_CPUID_EXT_FEATURES_EDX  108  /* offset to featuresEdx Extended  */
#define VX_CPUID_EXT_FEATURES_ECX  112  /* offset to featuresEcx Extended  */
#define VX_CPUID_CACHE_COUNT       116  /* offset to cache count           */
#define VX_CPUID_CACHE_PARAMS      120  /* offset to cache parameters      */
#define VX_CPUID_MONITOR_EAX       216  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_EBX       220  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_ECX       224  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_EDX       228  /* offset to montor/mwait parameters */
#define VX_CPUID_DTSPM_EAX         232  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_EBX         236  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_ECX         240  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_EDX         244  /* offset to DTSPM parameters */
#define VX_CPUID_DCA_EAX           248  /* offset to DCA parameters */
#define VX_CPUID_PMON_EAX          252  /* offset to PMON parameters */
#define VX_CPUID_PMON_EBX          256  /* offset to PMON parameters */
#define VX_CPUID_PMON_ECX          260  /* offset to PMON parameters */
#define VX_CPUID_PMON_EDX          264  /* offset to PMON parameters */
#define VX_CPUID_PTOP_COUNT        268  /* offset to PTOP count      */
#define VX_CPUID_PTOP_PARAMS       272  /* offset to PTOP parameters */
#define VX_CPUID_XSAVE_EAX         336  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_EBX         340  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_ECX         344  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_EDX         348  /* offset to XSAVE parameters */
#define VX_CPUID_L2CACHE_EAX       352  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_EBX       356  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_ECX       360  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_EDX       364  /* offset to L2 Cache parameters */
#define VX_CPUID_APM_EAX           368  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_EBX           372  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_ECX           376  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_EDX           380  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_VPADRS_EAX        384  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_EBX        388  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_ECX        392  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_EDX        396  /* offset to Virt/Phys Adr Size parameters */

/* bit mask in VX_CPUID_FEATURES structure */

#define VX_CPUID_FPU         0x00000001
#define VX_CPUID_MMX         0x00800000
#define VX_CPUID_FXSR        0x01000000
#define VX_CPUID_SSE         0x02000000
#define VX_CPUID_SSE2        0x04000000

/* bit mask in VX_CPUID_FEATURES_EXT structure */

#define VX_CPUID_SSE3        0x00000001
#define VX_CPUID_SSE42       0x00100000
#define VX_CPUID_XSAVE       0x04000000
#define VX_CPUID_OSXSAVE     0x08000000
#define VX_CPUID_AVX         0x10000000

#ifdef __cplusplus
}
#endif

#endif /* __INCregsSimnth */
