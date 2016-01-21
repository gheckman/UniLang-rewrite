/* smpMipsP.h - private assembler definitions header file for SMP */

/*
 * Copyright (c) 2006-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02n,08mar12,h_k  removed _WRS_ARCH_REQUIRES_TLB_SYNC_CPC. (WIND00320752)
02m,23dec11,l_z  Move _WRS_MIPS_SMP_VARIANT to Makefile for XLR/XLP CPU
02l,17may11,slk  Add 64bit register read and set interface
02k,19nov10,rlg  find WIND00242201 - compiler warnings
02j,27may10,d_c  Rename CAVIUM_CNMIPS_* to _WRS_CAVIUM_CNMIPS_* and define in
                 arch Makefile
02l,09jun10,kab  Add _WRS_ARCH_HAS_OBJ_SAFE
02k,29apr10,pad  Moved extern C statement after include statements.
02i,31mar10,d_c  Add cav_cn5xxx and cav_cn6xxx variants
02j,11jan10,slk  add cavium to variants that support index on -1 page
02i,13nov09,slk  update and add macros for SMP M-N support
02h,23sep09,s_s  changed INT_CPU_LOCK() and INT_CPU_UNLOCK() to
                 INT_CPU_MICRO_LOCK() and INT_CPU_MICRO_UNLOCK()
		 (WIND00181479)
02g,15may09,gls  moved VX_INSTR_BARRIER() to vxAtomicArchLibCommon.h
02f,24feb09,slk  fix zero register references
02e,14feb09,slk  move archVars to -1 page
02d,18sep08,gls  added _WRS_KERNEL_LOCK_VAR_ALIGN
02c,27aug08,jpb  Renamed VSB header file
02b,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02a,20jun08,zl   replaced _WRS_ASM() with _WRS_BARRIER()
01z,03apr08,slk  add global var access macros that don't call
                 _MIPS_CPU_INDEX_GET (cpuindex supplied)
01z,27may08,slk  define _WRS_MIPS_SMP_VARIANT if _mti24kx variant
01y,10jan08,gls  added VX_INSTR_BARRIER()
01x,05dec07,d_c  add _MIPS_CPU_ID_GET() macro for Raza. Continue to default
                 to _MIPS_CPU_INDEX_GET() for other variants.
01w,25sep07,d_c  Add extended interrupts for RMI _xlr variant (rebased on 02nov07)
01x,07may08,slk  add _mipsIpiMailbox and WRS ARCH macros
01w,12oct07,pes  Remove reference to _mipsEsfTailTbl.
01v,09aug07,rlg  Changes for the MIPS Library restructuring
01u,01aug07,pes  Disable cache lock for SMP
01u,01aug07,l_z  add limitation when define _MIPS_CPU_INDEX_GET
01t,17jul07,pes  Rename .kseg0data to .kseg0bss.
01s,22jun07,slk  add zero return to _MIPS_CPU_INDEX_GET for UP arch builds
01r,18jun07,pes  Move references to _WRS_VX_SMP out of public header file.
01q,05jun07,agf  remove octeon5xxx reference
01q,30may07,pes  Add defines for Raza CPU variant.
01p,17apr07,kk   move VX_MAX_SMP_CPUS to archMips.h
01p,30mar07,pes  Add CPU index get code for MIPS64R2 cores.
01o,11dec06,kk   removed references to VX_KERNEL_VARS define, no longer needed
01n,30nov06,pes  Complete changes from 01m.
01m,29nov06,pes  Remove local definition of _WRS_WIND_VARS_OFFSET_archVars.
01l,05oct06,pes  Remove padding from windArchVars structure. Removed
                 obsolete macro definitions. Change _MIPS_CPU_INDEX_GET
		 macro to return core number instead of word index. 
01k,29sep06,pes  Add _MIPS_KERNEL_LOCK_OWNER_AND_INDEX_GET.
01j,20sep06,pes  Provide default macros if _WRS_MIPS_SMP_VARIANT is not
                 defined. Add definitions used in kernelCpuEnable. Define
		 VX_KERNEL_VARS.
01i,06sep06,gls  added definition of MIPS specific vxKernelVars[] offsets
01h,12sep06,pes  Move _WRS_CPU_INDEX_GET macro out of assembly portion of the
                 file.
01g,12sep06,pes  Add macro definition for _WRS_CPU_INDEX_GET().
01f,22aug06,pes  Correct use of WRS_KERNEL_VARS to VX_KERNEL_VARS.
01e,16aug06,pes  Change #if FALSE to #ifdef VX_KERNEL_VARS.
01d,13aug06,pes  Correct definition of _WRS_WIND_VARS_ARCH.
01c,12aug06,pes  Provide MIPS-specific definition of VX_MAX_SMP_CPUS.
01b,26jul06,pes  Include archMips.h. Add _WRS_WIND_VARS* definitions.
		 Change name of CPU_INDEX macro to _MIPS_CPU_INDEX_GET.
		 Replace individual global access macros with generic
		 ones that automatically handle new globals as needed.
01a,20jul06,pes  written.
*/

#ifndef __INCsmpMipsPh
#define __INCsmpMipsPh

#include <vsbConfig.h>
#include <arch/mips/archMips.h>
#include <arch/mips/regsMips.h>
#include <arch/mips/mipsExcPage.h>
#include <private/kernelLockLibP.h>
#ifdef _WRS_CONFIG_SMP
#include <private/intMicroLibP.h>
#endif
#ifdef _ASMLANGUAGE
#include <private/windLibP.h>
#endif /* _ASMLANGUAGE */


#ifdef __cplusplus
extern "C" {
#endif

/* SMP support */

#ifdef _WRS_CONFIG_SMP

/*
 * MIPS has been adapted to use the new object safe count feature for SMP.
 * When all architectures have been adapted this can be removed from
 * the code.
 */

#define _WRS_ARCH_HAS_OBJ_SAFE

/* Trigger software cacheTextUpdate CPC */

#define _WRS_ARCH_REQUIRES_CACHE_TEXT_UPDATE_CPC

/* Disable cache locking */
#undef _WRS_SUPPORT_CACHE_LOCK			/* cache lock feature */

#endif /* _WRS_CONFIG_SMP */

#define _WRS_VX_KERNEL_VARS_SECTION_ATTR \
__attribute__ ((__section__ (".kseg0bss")))

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
 *	(rule 1). 
 * if WIND_VARS is 72 bytes, _WRS_WIND_VARS_ALIGN must be no less than 128
 *	(rules 2 and 3). 
 */
#define _WRS_WIND_VARS_ALIGN		128
#define _WRS_WIND_VARS_ALIGN_SHIFT	7

/*
 * Much like the _WRS_WIND_VARS_ALIGN the _WRS_KERNEL_LOCK_VAR_ALIGN macro
 * must be defined for the common CPU build variants (e.g. PPC32, MIPS32, 
 * XSCALE, etc), representing the maximum cache line size of the variants of 
 * the respective arch. 
 *
 * For MIPS this is 128 bytes.
 */

#define _WRS_KERNEL_LOCK_VAR_ALIGN		128

/* add logical CPU index saved to -1 page support.  the 
 * _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED define is temporary and will
 * be removed before 6.8.1 is released
 * SLK -  TO DO remove _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
 */

#if defined (_WRS_MIPS_NETLOGIC_CPU) \
    || defined(_WRS_CAVIUM_CNMIPS_CORE) \
    || defined(_WRS_CAVIUM_CNMIPS_II_CORE) 
#define _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#else  /* defined (_WRS_MIPS_NETLOGIC_CPU) || defined (_WRS_CAVIUM_CNMIPS[_II]_CORE) */
#undef _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#endif /* defined (_WRS_MIPS_NETLOGIC_CPU) || defined (_WRS_CAVIUM_CNMIPS[_II]_CORE) */

#if defined(_WRS_MIPS_NETLOGIC_CPU)
/* 
 * Note: The format of mipsSrImask variable changes for _xlr varient and
 * possibly others.  Rather than representing SR[15:8],it represents 
 * a full 32-bit interrupt mask MR[31:0]. The mapping of SR[15:8]
 * to MR is variant-dependent. In _xlr, SR[15:8] == EIMR[7:0].
 */
#endif  /* _WRS_MIPS_NETLOGIC_CPU */
#ifndef _ASMLANGUAGE

/* MIPS has no arch vxKernelVars */
#undef _WRS_WIND_VARS_ARCH

#if defined (_WRS_CONFIG_SMP)

/* macro to access the arch-specific fields of the vxKernelVars struct */
#define _WRS_WIND_VARS_ARCH_ACCESS(glob)				\
                      *(int *)(EXCPAGE_ARCHVARS##glob)

#define _WRS_WIND_VARS_ARCH_SET(cpuid,glob,var)  \
                      *(int *)(EXCPAGE_ARCHVARS##glob)=var

#define _WRS_WIND_VARS_ARCH_GET(cpuid,glob)      \
                      *(int *)(EXCPAGE_ARCHVARS##glob)

#define _WRS_ARCH_LOCKED_GLOBAL_SET(glob, var)   \
                   do                                       \
                      {                                     \
                      int key=INT_CPU_MICRO_LOCK();         \
                      *(int *)(EXCPAGE_ARCHVARS##glob)=var; \
                      INT_CPU_MICRO_UNLOCK(key);            \
                      } while ((0))

#define _WRS_ARCH_LOCKED_GLOBAL_GET(glob, var)   \
                   do                                       \
                      {                                     \
                      var=*(int *)(EXCPAGE_ARCHVARS##glob); \
                      } while ((0))

#define _WRS_WIND_VARS_INLINE_ASM_ARCH_ACCESS(reg,glob)		\
                      lw   reg, %lo(EXCPAGE_ARCHVARS##glob)(zero)

/* macro to access the arch-specific fields of the vxKernelVars struct
 * for 64 bit width
 */
#define _WRS_WIND_VARS_ARCH_64_ACCESS(glob)				\
                      *(UINT64 *)(EXCPAGE_ARCHVARS##glob)

#define _WRS_WIND_VARS_ARCH_64_SET(cpuid,glob,var)  \
                      *(UINT64 *)(EXCPAGE_ARCHVARS##glob)=var

#define _WRS_WIND_VARS_ARCH_64_GET(cpuid,glob)      \
                      *(UINT64 *)(EXCPAGE_ARCHVARS##glob)

#define _WRS_ARCH_LOCKED_GLOBAL_64_SET(glob, var)   \
                   do                                          \
                      {                                        \
                      int key=INT_CPU_MICRO_LOCK();            \
                      *(UINT64 *)(EXCPAGE_ARCHVARS##glob)=var; \
                      INT_CPU_MICRO_UNLOCK(key);               \
                      } while ((0))

#define _WRS_ARCH_LOCKED_GLOBAL_64_GET(glob, var)   \
                   do                                          \
                      {                                        \
                      var=*(UINT64 *)(EXCPAGE_ARCHVARS##glob); \
                      } while ((0))

#define _WRS_WIND_VARS_INLINE_ASM_ARCH_64_ACCESS(reg,glob)	\
                      ld   reg, %lo(EXCPAGE_ARCHVARS##glob)(zero)
/*
 * _WRS_CPU_INDEX_GET():
 *
 * Just call the (assembly) function for now, but to optimize
 * performance this should eventually become a C-callable
 * _WRS_ASM construct (whose syntax varies depending on TOOL).
 */

#define _WRS_CPU_INDEX_GET()    vxCpuIndexGet()
#else /* !_WRS_CONFIG_SMP */
#define _WRS_WIND_VARS_ARCH_ACCESS(glob) glob
#define _WRS_WIND_VARS_INLINE_ASM_ARCH_ACCESS(reg,glob)		\
                      lw   reg, glob
#define _WRS_WIND_VARS_ARCH_64_ACCESS(glob) glob
#define _WRS_WIND_VARS_INLINE_ASM_ARCH_64_ACCESS(reg,glob)		\
                      ld   reg, glob
#define _WRS_CPU_INDEX_GET()    0
#endif /* _WRS_CONFIG_SMP */

#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT

#endif /* ! _ASMLANGUAGE */

#ifdef _ASMLANGUAGE

#undef _MIPS_CPU_ID_GET_DEFD 

/* read logical CPU index from -1 page if configured */

#ifdef _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#define _MIPS_CPU_INDEX_GET(reg) \
	lw	reg, %lo(EXCPAGE_CPU_LOGICAL_INDEX)(zero);
#endif /* _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED */

#if defined (MIPSXX_sb1) \
    || defined(_WRS_CAVIUM_CNMIPS_CORE) \
    || defined(_WRS_CAVIUM_CNMIPS_II_CORE) \
    || defined(MIPSXX_mti24kx) \
    || defined(_WRS_MIPS_NETLOGIC_CPU)
#ifndef _WRS_MIPS_SMP_VARIANT
#define _WRS_MIPS_SMP_VARIANT
#endif /* _WRS_MIPS_SMP_VARIANT */
#endif /* MIPSXX_sb1 || _WRS_CAVIUM_CNMIPS[_II]_CORE || MIPSXX_mti24kx ||
          _WRS_MIPS_NETLOGIC_CPU */

#if defined (_WRS_MIPS_NETLOGIC_CPU)
/*
 * the Raza XLR core implements 8 per-core scratch registers. We will use the
 * last of these scratch registers to hold a CPU identification. This makes it
 * a very simple matter to quickly determine what core we're running on.
 */
#define C0_CPUNUM	$22,7
#ifndef _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#define _MIPS_CPU_INDEX_GET(reg) \
	mfc0	reg,C0_CPUNUM;			/* CPUNum register */
#endif /* _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED */
#define C0_CPUID    $15,1
#define CPUID_MASK  0x1f
#define _MIPS_CPU_ID_GET_DEFD 1
#define _MIPS_CPU_ID_GET(reg) \
    mfc0    reg, C0_CPUID; \
    and     reg, CPUID_MASK

#endif /* _WRS_MIPS_NETLOGIC_CPU */

#ifdef _WRS_MIPS_ENABLE_R2_ISA

/*
 * the MIPS32/MIPS64 Release 2 instruction set includes the ability to
 * determine core by reading the CPUIndex register.
 */

#ifndef _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#define _MIPS_CPU_INDEX_GET(reg) \
	rdhwr	reg, cpunum;			/* CPUNum register */
#endif /* _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED */
/* add _MIPS_CPU_ID_GET for R2 CPUs */
#define _MIPS_CPU_ID_GET_DEFD 1
#define _MIPS_CPU_ID_GET(reg) \
	rdhwr	reg, cpunum;			/* CPUNum register */

#elif defined(_WRS_MIPS_SMP_VARIANT)
#ifndef _MIPS_CPU_INDEX_GET

/*
 * provide the register, shift and mask defines for the default
 * standard MIPS case
 */

#if !defined(_MIPS_CPU_INDEX_GET_REG)
#define _MIPS_CPU_INDEX_GET_REG		C0_PRID
#endif
#if !defined(_MIPS_CPU_INDEX_GET_SHIFT)
#define _MIPS_CPU_INDEX_GET_SHIFT	(25)
#endif
#if !defined(_MIPS_CPU_INDEX_GET_MASK)
#define _MIPS_CPU_INDEX_GET_MASK	(7)
#endif

#ifndef _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED
#define _MIPS_CPU_INDEX_GET(reg) \
        mfc0    reg, _MIPS_CPU_INDEX_GET_REG;	/* get processor ID */    \
        srl     reg, _MIPS_CPU_INDEX_GET_SHIFT;	/* shift CPU into word */ \
						/*   index position */    \
        and     reg, _MIPS_CPU_INDEX_GET_MASK;	/* apply mask */
#endif /* _MIPS_CPU_INDEX_GET */
#define _MIPS_CPU_ID_GET_DEFD 1
#define _MIPS_CPU_ID_GET(reg) \
        mfc0    reg, _MIPS_CPU_INDEX_GET_REG;	/* get processor ID */    \
        srl     reg, _MIPS_CPU_INDEX_GET_SHIFT;	/* shift CPU into word */ \
						/*   index position */    \
        and     reg, _MIPS_CPU_INDEX_GET_MASK;	/* apply mask */
#endif /* _WRS_MIPS_EXCPAGE_CPU_INDEX_SUPPORTED */
#else /* UP variant */

#define _MIPS_CPU_INDEX_GET(reg) \
        move    reg, zero;	/* processor ID always zero */

#endif /* _WRS_MIPS_ENABLE_R2_ISA */

#ifndef _MIPS_CPU_ID_GET_DEFD
#define _MIPS_CPU_ID_GET(reg) _MIPS_CPU_INDEX_GET(reg)
#endif

#ifdef  _WRS_CONFIG_SMP
/*
 * N.B.: The macros which follow may ONLY be used in sections of code in
 *       which use of the AT register as a scratch register is permitted.
 *       When using them in interrupt/exception entry/exit, make sure
 *       that AT is properly saved/restored.
 *
 * N.B.: Access to the kernel globals structure assumes two things. First,
 *       that they are in an address space in which there is identity mapping
 *       between kseg2 and kseg0. This is currently required for kernel data
 *       so we should be ok there. The other requirement is that kernel data
 *       must be in either kseg2 or kseg0 (for mapped or unmapped kernels,
 *       respectively). This is so that we can force addresses to kseg0
 *       by clearing bit 30. (i.e., 0xcxxxxxxx & 0xbfffffff = 0x8xxxxxxx).
 */

#define _WRS_LOAD_AT_WITH_VAR_BASE(label) \
	la  AT,vxKernelVars; \
        add AT,_WRS_WIND_VARS_OFFSET_##label;
#define _WRS_MIPS_VAR_ADRS(label)	vxKernelVars+_WRS_WIND_VARS_OFFSET_##label
#define _WRS_WIND_VARS_OFFSET(reg)	sll reg,_WRS_WIND_VARS_ALIGN_SHIFT;

#define _MIPS_PER_CPU_ADRS_GET(reg,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_MIPS_CPU_INDEX_GET(reg)	\
	_WRS_WIND_VARS_OFFSET(reg)	\
	addu	reg, AT			;/* add word index */ \
	.set	at

#define _MIPS_PER_CPU_ARCH_ADRS_GET(reg,label) \
	la	reg, EXCPAGE_ARCHVARS##label

/* _MIPS_PER_CPU_INDEX_ADRS_GET is the same as _MIPS_PER_CPU_ADRS_GET 
 * but cpuindex is supplied (and overwritten by return value)
 */

#define _MIPS_PER_CPU_INDEX_ADRS_GET(cpuindex,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_WRS_WIND_VARS_OFFSET(cpuindex)	\
	addu	cpuindex, AT		;/* add word index */ \
	.set	at

#define _MIPS_PER_CPU_REG_VALUE_GET(reg,label) \
        _MIPS_PER_CPU_VALUE_GET(reg,label)

#define _MIPS_PER_CPU_ARCH_REG_VALUE_GET(reg,label) \
        _MIPS_PER_CPU_ARCH_VALUE_GET(reg,label)

#define _MIPS_PER_CPU_REG64_VALUE_GET(reg,label) \
        .set    noat                    ;/* forbid assembler use of AT */ \
        _WRS_LOAD_AT_WITH_VAR_BASE(label) \
        _MIPS_CPU_INDEX_GET(reg)        \
        _WRS_WIND_VARS_OFFSET(reg)      \
        addu    AT, reg                 ;/* add word index */ \
        ld      reg, 0(AT)              ;/* fetch value from array */ \
        .set    at

#define _MIPS_PER_CPU_ARCH_REG64_VALUE_GET(reg,label) \
        ld      reg, %lo(EXCPAGE_ARCHVARS##label)(zero)

#define _MIPS_PER_CPU_VALUE_GET(reg,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_MIPS_CPU_INDEX_GET(reg)	\
	_WRS_WIND_VARS_OFFSET(reg)	\
	addu	AT, reg			;/* add word index */ \
	lw	reg, 0(AT)		;/* fetch value from array */ \
	.set	at

#define _MIPS_PER_CPU_ARCH_VALUE_GET(reg,label) \
	lw	reg, %lo(EXCPAGE_ARCHVARS##label)(zero)

/* _MIPS_PER_CPU_INDEX_VALUE_GET is the same as _MIPS_PER_CPU_VALUE_GET 
 * but cpuindex is supplied (and overwritten by return value)
 */

#define _MIPS_PER_CPU_INDEX_VALUE_GET(cpuindex,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_WRS_WIND_VARS_OFFSET(cpuindex)	\
	addu	AT, cpuindex		;/* add word index */ \
	lw	cpuindex, 0(AT)		;/* fetch value from array */ \
	.set	at

#if defined(_WRS_MIPS_NETLOGIC_CPU)
#define _MIPS_PER_CPU_REG_VALUE_AND_ADRS_GET(regv,rega,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_MIPS_CPU_INDEX_GET(rega)	\
	_WRS_WIND_VARS_OFFSET(rega)	\
	addu	rega, AT		;/* add word index */ \
	lwu	regv, 0(rega)		;/* fetch value from array */ \
	.set	at

#define _MIPS_PER_CPU_ARCH_REG_VALUE_AND_ADRS_GET(regv,rega,label) \
	la	rega, EXCPAGE_ARCHVARS##label ;	\
	lwu	regv, 0(rega)

#else /* ! _WRS_MIPS_NETLOGIC_CPU */
#define _MIPS_PER_CPU_REG_VALUE_AND_ADRS_GET(regv,rega,label) \
        _MIPS_PER_CPU_VALUE_AND_ADRS_GET(regv,rega,label)

#define _MIPS_PER_CPU_ARCH_REG_VALUE_AND_ADRS_GET(regv,rega,label) \
        _MIPS_PER_CPU_ARCH_VALUE_AND_ADRS_GET(regv,rega,label)

#endif  /* _WRS_MIPS_NETLOGIC_CPU */

#define _MIPS_PER_CPU_REG64_VALUE_AND_ADRS_GET(regv,rega,label) \
        .set    noat                    ;/* forbid assembler use of AT */ \
        _WRS_LOAD_AT_WITH_VAR_BASE(label) \
        _MIPS_CPU_INDEX_GET(rega)       \
        _WRS_WIND_VARS_OFFSET(rega)     \
        addu    rega, AT                ;/* add word index */ \
        ld      regv, 0(rega)           ;/* fetch value from array */ \
        .set    at

#define _MIPS_PER_CPU_ARCH_REG64_VALUE_AND_ADRS_GET(regv,rega,label) \
        la      rega, EXCPAGE_ARCHVARS##label ; \
        ld      regv, 0(rega)

#define _MIPS_PER_CPU_VALUE_AND_ADRS_GET(regv,rega,label) \
	.set	noat			;/* forbid assembler use of AT */ \
	_WRS_LOAD_AT_WITH_VAR_BASE(label) \
	_MIPS_CPU_INDEX_GET(rega)	\
	_WRS_WIND_VARS_OFFSET(rega)	\
	addu	rega, AT		;/* add word index */ \
	lw	regv, 0(rega)		;/* fetch value from array */ \
	.set	at

#define _MIPS_PER_CPU_ARCH_VALUE_AND_ADRS_GET(regv,rega,label)  \
	la	rega, EXCPAGE_ARCHVARS##label ;			\
	lw	regv, 0(rega)

#ifndef _MIPS_ASM_EXTERN_KERNEL_GLOBALS
#define _MIPS_ASM_EXTERN_KERNEL_GLOBALS
#endif /* _MIPS_ASM_EXTERN_KERNEL_GLOBALS */

/*
 * _MIPS_KERNEL_LOCK_OWNER_AND_INDEX_GET(ro,ri)
 *
 * ro = register to store kernel lock owner
 * ri = register to store cpu index
 *
 * typedef struct smpLock
 * {
 * volatile int state;	/@ state of lock (free/taken) @/
 * volatile int owner;	/@ CPU which owns the lock @/
 * int count;		/@ recursive ownership nesting count @/
 * int options;		/@ options applicable to this lock @/
 */

#define _MIPS_KERNEL_LOCK_OWNER_AND_INDEX_GET(ro,ri) \
	la	ro,kernelStateLock	/* point to lock */; \
	lw	ro,_WRS_KERNEL_LOCK_OFFSET_cpuIndex(ro) /* get CPU index */; \
      _MIPS_CPU_INDEX_GET(ri)

#else /* _WRS_CONFIG_SMP */

#define _WRS_MIPS_VAR_ADRS(label) label

#define _MIPS_PER_CPU_ADRS_GET(r,label) \
	la	r, _WRS_MIPS_VAR_ADRS(label) /* get address of label */\

#define _MIPS_PER_CPU_ARCH_ADRS_GET(r,label) \
		_MIPS_PER_CPU_ADRS_GET(r,label)

#define _MIPS_PER_CPU_INDEX_ADRS_GET(r,label) \
	la	r, _WRS_MIPS_VAR_ADRS(label) /* get address of label */\

#define _MIPS_PER_CPU_ARCH_INDEX_ADRS_GET(r,label) \
		_MIPS_PER_CPU_INDEX_ADRS_GET(r,label)

/* On Raza we need a macro to load a 32-bit per-cpu value into a
 * 64-bit register without sign-extending. We use this macro to retrieve
 * the lower 32-bits of the EIMR, then write the full 64-bit register
 * to the EIMR. We want the upper 32 bits to always be zero.
 */
#if defined(_WRS_MIPS_NETLOGIC_CPU)
#define _MIPS_PER_CPU_REG_VALUE_GET(r,label) \
	lwu	r, _WRS_MIPS_VAR_ADRS(label) /* get value at label */

#define _MIPS_PER_CPU_ARCH_REG_VALUE_GET(r,label) \
		_MIPS_PER_CPU_REG_VALUE_GET(r,label)

#else /* ! _WRS_MIPS_NETLOGIC_CPU */
#define _MIPS_PER_CPU_REG_VALUE_GET(r,label) \
        _MIPS_PER_CPU_VALUE_GET(r,label)

#define _MIPS_PER_CPU_ARCH_REG_VALUE_GET(r,label) \
                             _MIPS_PER_CPU_VALUE_GET(r,label)
#endif  /* _WRS_MIPS_NETLOGIC_CPU */

#define _MIPS_PER_CPU_REG64_VALUE_GET(r,label) \
        ld      r, _WRS_MIPS_VAR_ADRS(label) /* get value at label */

#define _MIPS_PER_CPU_ARCH_REG64_VALUE_GET(r,label) \
                _MIPS_PER_CPU_REG64_VALUE_GET(r,label)

#define _MIPS_PER_CPU_VALUE_GET(r,label) \
	lw	r, _WRS_MIPS_VAR_ADRS(label) /* get value at label */

#define _MIPS_PER_CPU_ARCH_VALUE_GET(r,label)  \
		_MIPS_PER_CPU_VALUE_GET(r,label)

#define _MIPS_PER_CPU_INDEX_VALUE_GET(r,label) \
	lw	r, _WRS_MIPS_VAR_ADRS(label) /* get value at label */

#define _MIPS_PER_CPU_ARCH_INDEX_VALUE_GET(r,label) \
		_MIPS_PER_CPU_INDEX_VALUE_GET(r,label)

#if defined(_WRS_MIPS_NETLOGIC_CPU)
#define _MIPS_PER_CPU_REG_VALUE_AND_ADRS_GET(rv,ra,label) \
	la	ra, _WRS_MIPS_VAR_ADRS(label); /* get address of label */ \
	lwu	rv, 0(ra)		;/* load value through pointer */

#define _MIPS_PER_CPU_ARCH_REG_VALUE_AND_ADRS_GET(rv,ra,label)   \
		_MIPS_PER_CPU_REG_VALUE_AND_ADRS_GET(rv,ra,label)

#else /* ! _WRS_MIPS_NETLOGIC_CPU */
#define _MIPS_PER_CPU_REG_VALUE_AND_ADRS_GET(rv,ra,label) \
        _MIPS_PER_CPU_VALUE_AND_ADRS_GET(rv,ra,label)

#define _MIPS_PER_CPU_ARCH_REG_VALUE_AND_ADRS_GET(rv,ra,label)        \
                            _MIPS_PER_CPU_VALUE_AND_ADRS_GET(rv,ra,label)

#endif  /* _WRS_MIPS_NETLOGIC_CPU */

#define _MIPS_PER_CPU_REG64_VALUE_AND_ADRS_GET(rv,ra,label) \
        la      ra, _WRS_MIPS_VAR_ADRS(label); /* get address of label */ \
        ld      rv, 0(ra)               ;/* load value through pointer */

#define _MIPS_PER_CPU_ARCH_REG64_VALUE_AND_ADRS_GET(rv,ra,label)   \
                _MIPS_PER_CPU_REG64_VALUE_AND_ADRS_GET(rv,ra,label)

#define _MIPS_PER_CPU_VALUE_AND_ADRS_GET(rv,ra,label) \
	la	ra, _WRS_MIPS_VAR_ADRS(label); /* get address of label */ \
	lw	rv, 0(ra)		;/* load value through pointer */

#define _MIPS_PER_CPU_ARCH_VALUE_AND_ADRS_GET(rv,ra,label)              \
		_MIPS_PER_CPU_VALUE_AND_ADRS_GET(rv,ra,label)

#ifndef _MIPS_ASM_EXTERN_KERNEL_GLOBALS
#define _MIPS_ASM_EXTERN_KERNEL_GLOBALS \
	.extern _mipsEsfTail
#endif /* _MIPS_ASM_EXTERN_KERNEL_GLOBALS */

#endif /* _WRS_CONFIG_SMP */
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsmpMipsPh */
