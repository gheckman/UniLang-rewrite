/* smpI86P.h - i80x86 private SMP assembler definitions header file */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02m,16may13,scm  WIND00417700 SMP diab macro correction...
02l,09jan13,scm  WIND00229494 - SMP dedicated segment register
02k,20dec12,yjw  clear warning when load symbol table.(WIND00380360)
02j,11sep12,cwl  Correct the macro _WRS_WIND_VARS_ARCH_GET for UP.
                 (WIND00375599)
02i,27jan12,scm  WIND00326315 - live lock osm & cpc issue...
02h,10aug11,zl   added _WRS_CPU_SMTSET_GET()
02g,04jan11,scm  WIND00248698 adjust vxIntStackEnabled to type BOOL...
02f,12nov10,pch  CQ240922: exclude refs to OSM when small footprint selected
02e,25oct10,rbc  WIND00204240 - Add support for objVerifiedSafe.
02d,29jul10,pad  Moved extern C statement after include statements.
02c,24may10,jb   Mods for SMP M-N support
02b,05may10,jl   add support for SMP GuestOS
02a,07may09,pee  using generated offsets. Removing hardcoded offsets.
01z,15may09,gls  moved VX_INSTR_BARRIER() to vxAtomicArchLibCommon.h
01y,12feb09,sem  Added sysCr3 to the WIND_VARS_ARCH struct
		 Added sysCr3 access macros
01x,18sep08,gls  added _WRS_KERNEL_LOCK_VAR_ALIGN
01w,27aug08,jpb  Renamed VSB header file
01v,30jul08,rbc  Fix undefines for _IA32_LOC_APIC_ID...
01u,24jun08,jpb  Added include path for kernel configurations options set in
		 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01t,20jun08,zl   replaced _WRS_ASM() with _WRS_BARRIER()
01s,22apr08,zl   ensure 32-bit _IA32_LOC_APIC_ID register access.
01r,10jan08,gls  added VX_INSTR_BARRIER()
01q,01aug07,scm  optimize _WRS_CPU_INDEX_GET()...
01p,31may07,scm  add _IA32_CPU_ADRS_BASE_GET macro...
01o,04may07,scm  correct _IA32_PER_CPU_VALUE_SET macro...
01m,17apr07,kk   move VX_MAX_SMP_CPUS to archI86.h
01l,11dec06,kk   removed references to VX_KERNEL_VARS define, no longer needed
01k,06dec06,scm  correct macro for GNU compiler support...
01j,28nov06,scm  remove def for _WRS_WIND_VARS_OFFSET_archVars...
01i,02nov06,scm  rename pSysGdtCurrent for backward comp with P2/3/4...
01h,26oct06,scm  add per Cpu OSM Scratch memory space for GDT data manipulation
01g,05oct06,scm  add translation to _IA32_CPU_INDEX_GET...
01f,03oct06,scm  additional macro work...
01e,15sep06,scm  add specific vxKernelVars[] support...
01d,30aug06,scm  expand _WRS_WIND_VARS_ARCH...
01c,21aug06,jb   Combining smpI86P.h and vxCpuLibP.h
01b,01aug06,scm  more SMP work...
01a,21jul06,scm  created, added SMP Support Macros...
*/

#ifndef	__INCasmI86Ph
#define	__INCasmI86Ph

/************************************************************/

#include <vsbConfig.h>
#include <arch/i86/archI86.h>
#include <arch/i86/regsI86.h>
#include <private/kernelLockLibP.h>
#include <hwif/cpu/arch/i86/vxCpuIdLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT

/*
 * 0xFEE00020 is the address of the local APIC ID Register.
 */
#define _IA32_LOC_APIC_ID       0xFEE00020

#define _IA32_CPU_INDEX_SHIFT   (0x18)
#define _IA32_CPU_INDEX_MASK    (0xFF)

#ifdef _WRS_CONFIG_SMP

/*
 * IA32 has been adapted to use the new object safe count feature for SMP.
 * When all architectures have been adapted this can be removed from
 * the code.
 */

#define _WRS_ARCH_HAS_OBJ_SAFE

/*
 * This macro defines the alignment requirement for the WIND_VARS structure.
 *
 * There are 3 factors involved in selection of this value.
 *
 * 1. It's definition is no LESS than the maximum value of
 *    _CPU_CACHE_ALIGN_SIZE, and may be larger to provide for future
 *    cache line length growth.
 * 2. It must be at least as large as the WIND_VARS structure.
 * 3. It must be a power of 2.
 *
 * For example:
 * If WIND_VARS is 56 bytes, _WRS_WIND_VARS_ALIGN must be no less than 64
 *      (rule 1).
 * if WIND_VARS is 72 bytes, _WRS_WIND_VARS_ALIGN must be no less than 128
 *      (rules 2 and 3).
 */

#define _WRS_WIND_VARS_ALIGN            128
#define _WRS_WIND_VARS_ALIGN_SHIFT      7

/*
 * Much like the _WRS_WIND_VARS_ALIGN the _WRS_KERNEL_LOCK_VAR_ALIGN macro
 * must be defined for the common CPU build variants (e.g. PPC32, MIPS32,
 * XSCALE, etc), representing the maximum cache line size of the variants of
 * the respective arch.
 *
 * For x86 this is 128 bytes.
 */

#define _WRS_KERNEL_LOCK_VAR_ALIGN		128

#ifndef _ASMLANGUAGE

#ifdef _WRS_CONFIG_WRHV_GUEST
/*
 * wrhvVbCpuId is used to store the address of the virtual-core's cpuId.
 * This global contains the virtual address for the core configuration
 * and avoids making a VBI function call to get the wrhvVbConfig address
 * and calculate the offset to the core id..
 */

extern UINT32 *wrhvVbCpuId;
#endif /* WRS_CONFIG_WRHV_GUEST */

/* mpCpuIndexTable is used in vxCpuArchLib.c, this gloabal avoids
 * calling through vxbus and reduces overhead, table translations
 * are done everywhere, but once up this table should never change...
 */

extern UINT8 mpCpuIndexTable[];

typedef struct wind_vars_arch
   {
   GDT         *cpu_pSysGdt;                 /* 0x4c: Global Descriptor Table */
   TSS         *cpu_sysTssCurrent;           /* 0x50: Task State Segmnet */
   TSS         *cpu_excOSMTssCurrent;        /* 0x54: OSM TSS */
   SEGDESC     *cpu_sysOSMLdtCurrent;        /* 0x58: Local Descriptor Table */
   UINT32      *cpu_excOSMStackCurrent;      /* 0x5c: OSM Stack */
   UINT32      *cpu_sysOSMGdtScratchCurrent; /* 0x60: OSM Scratch memory */
   UINT32       cpu_vxIntStackPtr;           /* 0x64: Interrupt Stack Pointer */
   BOOL         cpu_vxIntStackEnabled;       /* 0x68: Interrupt Stack Enabled */
   unsigned int cpu_cpuIndex;                /* 0x6c: logical cpu used by GS */
   UINT32       cpu_cpuGsBaseCurrent;        /* 0x70: &vxKernelVars in gsbase */
   UINT32       cpu_intNest;                 /* 0x74: Interrupt Nested Count */
   UINT32       cpu_sysCr3;                  /* 0x78: Local CR3 cache */
   UINT32       cpu_sysOSMState;             /* 0x7c: OSM State Flag */
   } WIND_VARS_ARCH;

#define _WRS_WIND_VARS_ARCH WIND_VARS_ARCH cpu_archVars

/* macro to access the arch-specific fields of the vxKernelVars struct */
#define _WRS_WIND_VARS_ARCH_ACCESS(glob)         \
		      _WRS_KERNEL_GLOBAL_ACCESS (archVars.cpu_##glob)

#define _WRS_WIND_VARS_ARCH_SET(cpuid,glob,var)  \
		      _WRS_KERNEL_CPU_GLOBAL_SET(cpuid,archVars.cpu_##glob,var)

#define _WRS_WIND_VARS_ARCH_GET(cpuid,glob)      \
		      _WRS_KERNEL_CPU_GLOBAL_GET(cpuid,archVars.cpu_##glob)

#define _WRS_ARCH_LOCKED_GLOBAL_SET(glob, var)   \
		      _WRS_KERNEL_LOCKED_GLOBAL_SET(archVars.cpu_##glob,var)

#define _WRS_ARCH_LOCKED_GLOBAL_GET(glob, var)   \
		      _WRS_KERNEL_LOCKED_GLOBAL_GET(archVars.cpu_##glob,var)

/*
 * _WRS_CPU_SMTSET_GET() is used by the SMP scheduler for Hyper-Threading 
 * support.
 */

#define _WRS_CPU_SMTSET_GET(smtSet, cpuIx)		\
	     smtSet = sysCpuIdTopology.__smtSet[cpuIx]

/* Fast retrieve of cpuIndex using GS Base register offset */

#if defined (__DCC__)

__asm volatile unsigned int _vxGsBaseCpuIndexGet_inline (void)
{
! "ax"                                          /* ax is clobbered */

	mov    %gs:(0x6c), %eax
}

#else /* if defined (__GNUC__) */

static __inline__ unsigned int _vxGsBaseCpuIndexGet_inline (void)
    {
    unsigned int cpu;

    __asm__ volatile ("mov    %%gs:(0x6c), %%eax" \
                            : "=a" (cpu) : /* no input */);

    return cpu;
    }

#endif /* __DCC__ */
#endif /* !_ASMLANGUAGE */

#ifdef _WRS_CONFIG_WRHV_GUEST
#define _WRS_CPU_INDEX_GET() \
	(*(volatile UINT32 *)wrhvVbCpuId)
#else	/* _WRS_CONFIG_WRHV_GUEST */

#define _WRS_CPU_INDEX_GET() _vxGsBaseCpuIndexGet_inline ()

#endif	/* _WRS_CONFIG_WRHV_GUEST */

#else   /* _WRS_CONFIG_SMP */

#define _WRS_CPU_INDEX_GET()    0

/* macro to access the arch-specific fields */
#define _WRS_WIND_VARS_ARCH_ACCESS(glob)          \
		      _WRS_KERNEL_GLOBAL_ACCESS (glob)

#define _WRS_WIND_VARS_ARCH_SET(ignored,glob,var) \
		      _WRS_KERNEL_CPU_GLOBAL_SET(ignored,glob,var)

#define _WRS_WIND_VARS_ARCH_GET(ignored,glob)      \
		      _WRS_KERNEL_CPU_GLOBAL_GET(ignored,glob)

#define _WRS_ARCH_LOCKED_GLOBAL_SET(glob, var)   \
		      _WRS_KERNEL_LOCKED_GLOBAL_SET(glob,var)

#define _WRS_ARCH_LOCKED_GLOBAL_GET(glob, var)   \
		      _WRS_KERNEL_LOCKED_GLOBAL_GET(glob,var)

#endif  /* _WRS_CONFIG_SMP */

#ifdef _ASMLANGUAGE

#include <private/windLibP.h>

#if defined(_WRS_CONFIG_SMP)

/* generated macro values required by assembly macros below */
#include <private/offsetMacrosP.h>

/* SMP support */
		
#define _WRS_LOAD_REG_WITH_VAR_BASE(label,reg) \
	leal FUNC(vxKernelVars),reg;           \
	addl $_WIND_VARS_cpu_##label##_OFFSET,reg;

#define _WRS_WIND_VARS_OFFSET(reg) \
	rol $_WRS_WIND_VARS_ALIGN_SHIFT,reg;

#define _IA32_ASM_EXTERN_KERNEL_GLOBALS

#ifdef _WRS_CONFIG_WRHV_GUEST
#define _IA32_CPU_INDEX_GET(reg,scratch)            \
	movl    wrhvVbCpuId,reg;                    \
	movl    0x0(reg),reg;
#else	/* _WRS_CONFIG_WRHV_GUEST */
#define _IA32_CPU_INDEX_GET(reg,scratch)            \
	movl    $_IA32_LOC_APIC_ID,reg;             \
	movl    0x0(reg),reg;                       \
	ror     $_IA32_CPU_INDEX_SHIFT,reg;         \
	andl    $_IA32_CPU_INDEX_MASK,reg;          \
	leal    FUNC(mpCpuIndexTable)(reg),scratch; \
	mov     0x0(scratch),reg;                   \
	andl    $_IA32_CPU_INDEX_MASK,reg;          \
	subl    FUNC(vxBaseCpuPhysIndex), reg;
#endif	/* _WRS_CONFIG_WRHV_GUEST */

/*
 * Obtain the address of vxKernelVars[cpuid] for the current
 * CPU in register 'reg', using 'scratch' as a scratch
 * variable.
 */

#define _IA32_CPU_ADRS_BASE_GET(reg,scratch)    \
	_IA32_CPU_INDEX_GET(reg,scratch)        \
	_WRS_WIND_VARS_OFFSET(reg)              \
	leal FUNC(vxKernelVars)(reg), reg;

#define _IA32_PER_CPU_ADRS_GET(reg,scratch,label)  \
	_IA32_CPU_INDEX_GET(reg,scratch)           \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addl    reg,scratch;                       \
	leal    0x0(scratch),reg;

#define _IA32_PER_CPU_VALUE_GET(reg,scratch,label) \
	_IA32_CPU_INDEX_GET(reg,scratch)           \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addl    reg,scratch;                       \
	movl    0x0(scratch),reg;

#define _IA32_PER_CPU_VALUE_SET(regv,scr1,scr2,label) \
	_IA32_CPU_INDEX_GET(scr1,scr2)                \
	_WRS_WIND_VARS_OFFSET(scr1)                   \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scr2)       \
	addl    scr1,scr2;                            \
	movl    regv,0x0(scr2);

#define _IA32_PER_CPU_VALUE_AND_ADRS_GET(regv,rega,scratch,label) \
	_IA32_CPU_INDEX_GET(regv,scratch)                         \
	_WRS_WIND_VARS_OFFSET(regv)                               \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)                \
	addl    regv,scratch;                                     \
	leal    0x0(scratch),rega;                                \
	movl    0x0(scratch),regv;

#define _IA32_PER_CPU_VALUE_INC(reg,scratch,label) \
	_IA32_CPU_INDEX_GET(reg,scratch)           \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addl    reg,scratch;                       \
	movl    0x0(scratch),reg;                  \
	incl    reg;                               \
	movl    reg,0x0(scratch);

#define _IA32_PER_CPU_VALUE_DEC(reg,scratch,label) \
	_IA32_CPU_INDEX_GET(reg,scratch)           \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addl    reg,scratch;                       \
	movl    0x0(scratch),reg;                  \
	decl    reg;                               \
	movl    reg,0x0(scratch);

/*
 * rega = register to store kernel lock owner
 * regb = register to store cpu index
 *
 * typedef struct smpLock
 * {
 * volatile int state;         /@ state of lock (free/taken) @/
 * volatile int owner;         /@ CPU which owns the lock @/
 * int          count;         /@ recursive ownership nesting count @/
 * int          options;       /@ options applicable to this lock @/
 */
#define _IA32_KERNEL_LOCK_OWNER_AND_INDEX_GET(rega, regb)     \
	_IA32_CPU_INDEX_GET(regb,rega)                        \
	leal    FUNC(kernelStateLock),rega;                   \
	movl    VX_KERNEL_LOCK_cpuIndex_OFFSET(rega),rega;
			      /* kernel spin lock owner */

#else /* _WRS_CONFIG_SMP */

#define _WRS_IA32_VAR_ADRS(label) FUNC(label)

#ifdef	_WRS_CONFIG_MEM_ALLOT

/* exclude OSM references, because OSM requires malloc() */

#define _IA32_ASM_EXTERN_KERNEL_GLOBALS                                 \
	.globl  FUNC(pSysGdt);                 /* Gdt */                \
	.globl  FUNC(intNest);                 /* nested intr cnt */    \
	.globl  FUNC(vxIntStackPtr);           /* intr stk ptr */       \
	.globl  FUNC(vxIntStackEnabled);       /* intr stk enabled flag */ \
	.globl  FUNC(sysCr3);                  /* local CR3 cache */

#else	/* _WRS_CONFIG_MEM_ALLOT */

#define _IA32_ASM_EXTERN_KERNEL_GLOBALS                                 \
	.globl  FUNC(sysTssCurrent);           /* OSM Tss task info */  \
	.globl  FUNC(excOSMTssCurrent);        /* OSM Tss */            \
	.globl  FUNC(sysOSMGdtScratchCurrent); /* OSM Scratch memory */ \
	.globl  FUNC(sysOSMState);             /* OSM State Flag */     \
	.globl  FUNC(pSysGdt);                 /* Gdt */                \
	.globl  FUNC(intNest);                 /* nested intr cnt */    \
	.globl  FUNC(vxIntStackPtr);           /* intr stk ptr */       \
	.globl  FUNC(vxIntStackEnabled);       /* intr stk enabled flag */ \
	.globl  FUNC(sysCr3);                  /* local CR3 cache */

#endif	/* _WRS_CONFIG_MEM_ALLOT */

#define _IA32_PER_CPU_ADRS_GET(reg,scratch,label) \
	leal    _WRS_IA32_VAR_ADRS(label),reg;  /* get address of label */

#define _IA32_PER_CPU_VALUE_GET(reg,scratch,label) \
	movl    _WRS_IA32_VAR_ADRS(label),reg;  /* get value at label */

#define _IA32_PER_CPU_VALUE_SET(regv,scr1,scr2,label) \
	movl    regv,_WRS_IA32_VAR_ADRS(label);

#define _IA32_PER_CPU_VALUE_AND_ADRS_GET(regv,rega,label) \
	leal    _WRS_IA32_VAR_ADRS(label),rega; /* get address of label */ \
	leal    0x0(rega),regv;                 /* get value at label */

#define _IA32_PER_CPU_VALUE_INC(reg,scratch,label) \
	incl    _WRS_IA32_VAR_ADRS(label);

#define _IA32_PER_CPU_VALUE_DEC(reg,scratch,label) \
	decl    _WRS_IA32_VAR_ADRS(label);

#endif  /* _ASMLANGUAGE */

#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCasmI86Ph */
