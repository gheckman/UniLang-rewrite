/* smpX86_64P.h - x86_64 private SMP assembler definitions header file */

/*
 * Copyright (c) 2009-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01r,09jan13,scm  WIND00229494 - SMP dedicated segment register
01q,11sep12,cwl  Correct the macro _WRS_WIND_VARS_ARCH_GET for UP.
                 (WIND00375599)
01p,21feb12,scm  WIND00326315 - live lock osm & cpc issue...
01o,14aug11,j_l  added vxCpuIdLib.h include.
01n,10aug11,zl   added _WRS_CPU_SMTSET_GET().
01m,06jan11,scm  WIND00240019: add _X86_64_PER_CPU_VALUE_SET_INT macro for SMP support...
01l,04jan11,scm  WIND00248698 adjust vxIntStackEnabled to type BOOL...
01k,27oct10,rbc  WIND00204240 - Add support for objVerifiedSafe.
01j,29jul10,pad  Moved extern C statement after include statements.
01i,22jun10,j_l  Delete _X86_64_LOC_APIC_ID.
01h,02jun10,scm  modify for smp m to n...
01g,16may10,scm  SMP 64 bit macro clean up...
01f,13may10,scm  removal of unused vars...
01e,29apr10,scm  local apic register access adjustment...
01d,22mar10,scm  update for sysCr3...
01c,18mar10,scm  add Local CR3 cache to WIND_VARS_ARCH...
01b,12feb09,jb   Tuning for 64-bit
01a,26jan09,jb   Creating 64-bit version from 32-bit version 01x
*/


#ifndef	__INCsmpX86_64Ph
#define	__INCsmpX86_64Ph

/************************************************************/

#include <vsbConfig.h>
#include <arch/i86/x86_64/archX86_64.h>
#include <regs.h>
#include <private/kernelLockLibP.h>
#include <hwif/cpu/arch/i86/vxCpuIdLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT

#define _X86_64_CPU_INDEX_SHIFT   (0x18)
#define _X86_64_CPU_INDEX_MASK    (0xFF)

#ifdef _WRS_CONFIG_SMP

/*
 * IA has been adapted to use the new object safe count feature for SMP.
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

#define _WRS_WIND_VARS_ALIGN            256
#define _WRS_WIND_VARS_ALIGN_SHIFT      8

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

/*
 * This macro is used to provide an instruction barrier.  It is in this file
 * only until the semantics are solidified, at which point it should be
 * moved to vxAtomicArchLib.h.
 *
 * The current definition is a replication of the VX_MEM_BARRIER_R() macro. It
 * should be revisited when the semantics are finalized.
 */

#define VX_INSTR_BARRIER()          _WRS_BARRIER("mfence")


/* mpCpuIndexTable is used in vxCpuArchLib.c, this gloabal avoids
 * calling through vxbus and reduces overhead, table translations
 * are done everywhere, but once up this table should never change...
 */

extern UINT8 mpCpuIndexTable[];

typedef struct wind_vars_arch
   {
   GDT     *cpu_pSysGdt;             /* 0x70: Global Descriptor Table */
   TSS     *cpu_sysTssCurrent;       /* 0x78: Task State Segmnet */
   TSS     *cpu_excOSMTssCurrent;    /* 0x80: OSM TSS */
   ULONG   *cpu_excOSMStackCurrent;  /* 0x88: OSM Stack */
   ULONG   cpu_vxIntStackPtr;        /* 0x90: Interrupt Stack Pointer */
   BOOL    cpu_vxIntStackEnabled;    /* 0x98: Interrupt Stack Enabled */
   unsigned int  cpu_cpuIndex;       /* 0x9c: logical cpu used by GS ref. */
   ULONG   cpu_sysCr3;               /* 0xa0: Local CR3 cache */
   UINT32  cpu_intNest;              /* 0xa8: Interrupt Nested Count */
   UINT32  cpu_sysOSMState;          /* 0xac: OSM State Flag */
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

static __inline__ unsigned int _vxGsBaseCpuIndexGet_inline (void)
    {
    unsigned int cpu;

    __asm__ volatile ("mov    %%gs:(0x9c), %%eax" \
                            : "=a" (cpu) : /* no input */);

    return cpu;
    }
#endif /* !_ASMLANGUAGE */

#define _WRS_CPU_INDEX_GET() _vxGsBaseCpuIndexGet_inline ()

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

/* SMP support */

#define _WRS_WIND_VARS_OFFSET_pSysGdt                   (_WRS_WIND_VARS_OFFSET_archVars+0x0)
#define _WRS_WIND_VARS_OFFSET_sysTssCurrent             (_WRS_WIND_VARS_OFFSET_archVars+0x8)
#define _WRS_WIND_VARS_OFFSET_excOSMTssCurrent          (_WRS_WIND_VARS_OFFSET_archVars+0x10)
#define _WRS_WIND_VARS_OFFSET_excOSMStackCurrent        (_WRS_WIND_VARS_OFFSET_archVars+0x18)
#define _WRS_WIND_VARS_OFFSET_vxIntStackPtr             (_WRS_WIND_VARS_OFFSET_archVars+0x20)
#define _WRS_WIND_VARS_OFFSET_vxIntStackEnabled         (_WRS_WIND_VARS_OFFSET_archVars+0x28)
#define _WRS_WIND_VARS_OFFSET_cpuIndex                  (_WRS_WIND_VARS_OFFSET_archVars+0x2c)
#define _WRS_WIND_VARS_OFFSET_sysCr3                    (_WRS_WIND_VARS_OFFSET_archVars+0x30)
#define _WRS_WIND_VARS_OFFSET_intNest                   (_WRS_WIND_VARS_OFFSET_archVars+0x38)
#define _WRS_WIND_VARS_OFFSET_sysOSMState               (_WRS_WIND_VARS_OFFSET_archVars+0x3c)

#define _WRS_LOAD_REG_WITH_VAR_BASE(label,reg) \
	lea  FUNC(vxKernelVars),reg;           \
	add  $_WRS_WIND_VARS_OFFSET_##label,reg;

#define _WRS_WIND_VARS_OFFSET(reg) \
	rol $_WRS_WIND_VARS_ALIGN_SHIFT,reg;

#define _X86_64_ASM_EXTERN_KERNEL_GLOBALS

/*
 * Obtain the address of vxKernelVars[cpuid] for the current
 * CPU in register 'reg', using 'scratch' as a scratch
 * variable.
 */

#define _X86_64_CPU_ADRS_BASE_GET(reg,scratch)    \
        _WRS_WIND_VARS_OFFSET(reg)              \
        leaq FUNC(vxKernelVars)(reg), reg;

#define _X86_64_PER_CPU_ADRS_GET(reg,scratch,label)  \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addq    reg,scratch;                       \
	leaq    0x0(scratch),reg;

#define _X86_64_PER_CPU_VALUE_GET_INT(reg,regv,scratch,label) \
	_WRS_WIND_VARS_OFFSET(regv)                \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	add     regv,scratch;                      \
	movl    0x0(scratch),reg;

#define _X86_64_PER_CPU_VALUE_GET_LONG(reg,scratch,label) \
	_WRS_WIND_VARS_OFFSET(reg)                 \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch) \
	addq    reg,scratch;                       \
	movq    0x0(scratch),reg;

#define _X86_64_PER_CPU_VALUE_SET_INT(regv,scr1,scr2,label) \
	_WRS_WIND_VARS_OFFSET(scr1)                   \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scr2)       \
	addq    scr1,scr2;                            \
	movl    regv,0x0(scr2);

#define _X86_64_PER_CPU_VALUE_SET_LONG(regv,scr1,scr2,label) \
	_WRS_WIND_VARS_OFFSET(scr1)                   \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scr2)       \
	addq    scr1,scr2;                            \
	movq    regv,0x0(scr2);

#define _X86_64_PER_CPU_VALUE_AND_ADRS_GET_LONG(regv,rega,scratch,label) \
	_WRS_WIND_VARS_OFFSET(regv)                               \
	_WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)                \
	addq    regv,scratch;                                     \
	leaq    0x0(scratch),rega;                                \
	movq    0x0(scratch),regv;

#else /* _WRS_CONFIG_SMP */

#define _WRS_X86_64_VAR_ADRS(label) FUNC(label)

#define _X86_64_ASM_EXTERN_KERNEL_GLOBALS                                   \
	.globl   FUNC(sysTssCurrent);           /* OSM Tss task info */     \
	.globl   FUNC(excOSMTssCurrent);        /* OSM Tss */               \
	.globl   FUNC(pSysGdt);                 /* Gdt */                   \
	.globl   FUNC(intNest);                 /* nested intr cnt */       \
	.globl   FUNC(vxIntStackPtr);           /* intr stk ptr */          \
	.globl   FUNC(vxIntStackEnabled);       /* intr stk enabled flag */ \
        .globl   FUNC(sysCr3);                  /* local CR3 cache */       \
        .globl   FUNC(sysOSMState);             /* OSM State Flag */     


#define _X86_64_PER_CPU_ADRS_GET(reg,scratch,label) \
	lea     _WRS_X86_64_VAR_ADRS(label),reg;  /* get address of label */

#define _X86_64_PER_CPU_VALUE_GET_INT(reg,scratch,label) \
	movl    _WRS_X86_64_VAR_ADRS(label),reg;  /* get value at label */

#define _X86_64_PER_CPU_VALUE_GET_LONG(reg,scratch,label) \
	movq    _WRS_X86_64_VAR_ADRS(label),reg;  /* get value at label */

#define _X86_64_PER_CPU_VALUE_SET_INT(regv,scr1,scr2,label) \
	movl    regv,_WRS_X86_64_VAR_ADRS(label);

#define _X86_64_PER_CPU_VALUE_SET_LONG(regv,scr1,scr2,label) \
	movq    regv,_WRS_X86_64_VAR_ADRS(label);

#define _X86_64_PER_CPU_VALUE_AND_ADRS_GET_INT(regv,rega,label) \
	leaq    _WRS_X86_64_VAR_ADRS(label),rega; /* get address of label */ \
	leal    0x0(rega),regv;                 /* get value at label */

#define _X86_64_PER_CPU_VALUE_AND_ADRS_GET_LONG(regv,rega,label) \
	leaq    _WRS_X86_64_VAR_ADRS(label),rega; /* get address of label */ \
	leaq    0x0(rega),regv;                 /* get value at label */

#define _X86_64_PER_CPU_VALUE_INC(reg,scratch,label) \
	incl    _WRS_X86_64_VAR_ADRS(label);

#define _X86_64_PER_CPU_VALUE_DEC(reg,scratch,label) \
	decl    _WRS_X86_64_VAR_ADRS(label);

#endif  /* _ASMLANGUAGE */

#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif	/* __INCsmpX86_64Ph */
