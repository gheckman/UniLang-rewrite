/* private/smpPpcP.h - PowerPC-specific definitions for SMP support */

/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Any compilation using definitions from this file will not *
 * be binary-compatible between the UP and SMP environments. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

/*
modification history
--------------------
02i,08mar13,pcs  Fix a type from the previous checkin.
02h,07mar13,pcs  Fix the offset for _WRS_WIND_VARS_OFFSET_intCrtSaveArea for
                 PPC_e6500.
02g,04feb13,pcs  cleanup for code review.
02f,08nov12,zl   added _WRS_CPU_SMTSET_GET() definition
02e,31oct12,pcs  Add struct tlb1EntrySelect to struct wind_vars_arch
02d,08mar12,h_k  removed _WRS_ARCH_REQUIRES_TLB_ALL_SYNC_CPC and
                 _WRS_ARCH_REQUIRES_TLB_SYNC_CPC. (WIND00320752)
02c,22nov11,x_s  Define _WRS_ARCH_REQUIRES_TLB_SYNC_CPC for PPC465
02b,18nov10,x_z  Add support for PPC476
02a,12jun10,rab  update _PPC_CPU_INDEX_GET for guest smp 
02b,29apr10,pad  Moved extern C statement after include statements.
02a,15mar10,gls  added _WRS_ARCH_HAS_OBJ_SAFE
01z,02feb10,liu  clear up compile warnings and avoid macro redefined.
                 (WIND00146270)
01z,05jan10,pmr  remove e500mc PIR shift
01y,15may09,gls  moved VX_INSTR_BARRIER() to vxAtomicArchLibCommon.h
01x,18sep08,gls  made _WRS_KERNEL_LOCK_VAR_ALIGN available to assembly files
01w,31aug08,pch  change _PPC_CACHE_MODE_IS_CONSISTENT to
                 _WRS_CONFIG_PPC_CACHE_MODE_IS_CONSISTENT for VSB
01v,27aug08,jpb  Renamed VSB header file
01u,25jun08,jpb  Added include path for kernel configurations options set in
		 vsb.
01t,20jun08,zl   replaced _WRS_ASM() with _WRS_BARRIER()
01s,18may08,pch  CQ118100: Add intCrtSaveArea definition in wind_vars_arch{}
01r,08may08,jpb  Modifications for source build.  Renamed
		 INCLUDE_VM_RTP to _WRS_CONFIG_VM_MULTIPLE_CONTEXT, 
		 _WRS_VX_SMP to _WRS_CONFIG_SMP.
01q,05may08,to   revised _PPC_PER_CPU_ macros
01p,07apr08,to   added attribute macros for kernelStateLock and vxKernelVars
01o,18mar08,h_k  added more _PPC_PER_CPU_ macros.
01n,24apr08,pmr  shift PIR for e500mc
01m,06mar08,pch  Define _PPC_CACHE_MODE_IS_CONSISTENT in SMP build
		 Move other SMP-dependent settings from archPpc.h
01l,10jan08,gls  added VX_INSTR_BARRIER()
01k,27nov07,dtr  Add _WRS_ARCH_REQUIRES_TLB_ALL_SYNC_CPC for 85XX SMP AIM MMU.
01j,08jun07,kk   added _WRS_MMU_HAS_MAP_STATE_API
01i,17apr07,kk   move VX_MAX_SMP_CPUS to archPpc.h
01h,11dec06,kk   removed references to VX_KERNEL_VARS define, no longer needed
01g,26oct06,to   define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT
		 simplify _PPC_PER_CPU macros
01f,20oct06,mmi  changed WIND_VARS_ARCH fields as void * to remove dependency
		 on mmuPpcLib.h
01e,11oct06,mmi  Enable VX_KERNEL_VARS
01d,12sep06,lei  added _PPC_KERNEL_LOCK_OWNER_AND_INDEX_GET
01c,24aug06,to   added _PPC_MINIMAL_TRY_LOCK macro
		 added _PPC_PER_CPU_VALUE_SET_ADRS_GET macro
01b,23aug06,mmi  added macro's to access WIND_VARS macro's
01a,19jul06,pch  written.
*/

#ifndef __INCsmpPpcPh
#define __INCsmpPpcPh

#include <vsbConfig.h>
#include <private/kernelLockLibP.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef	_WRS_CONFIG_SMP

/*
 * PPC has been adapted to use the new object safe count feature for SMP.
 * When all architectures have been adapted this can be removed from
 * the code.
 */

#define _WRS_ARCH_HAS_OBJ_SAFE

/*
 * WIND_VARS_ARCH must be the same size and alignment for all PPC because
 * code using WIND_VARS is built for PPC32 rather than for specific CPUs
 * and variants, but as long as its contents are used only by the PPC arch
 * code there is no particular reason why the space must be used in the
 * same way by all PPC.
 *
 * Because there are currently no supported (or known) PPC whose MMUs
 * incorporate segment registers and which also implement critical
 * interrupts, we reuse the currentSrTbl and currentPgTbl pointers in
 * WIND_VARS_ARCH as the save area for the critical interrupt handler.
 * There is no need for this reuse to be visible to C code, since the
 * save area is referenced only within intCrtEnt().
 *
 * This is purely a matter of saving space:  if we ever need to support
 * such a processor we can simply enlarge WIND_VARS_ARCH to 4 words
 * and adjust the definition of _WRS_WIND_VARS_OFFSET_intCrtSaveArea
 * accordingly.  The following #if ... #error is provided to ensure
 * that, if such a processor is encountered, the need to change the
 * definitions here will not be overlooked.
 */

#if	defined (_WRS_MMU_CLASS_SR_REGS) && defined (_PPC_MSR_CE_U)
#error	WIND_VARS_ARCH does not currently support processors having both segment regs and critical ints
#endif

/*
 * Much like the _WRS_WIND_VARS_ALIGN the _WRS_KERNEL_LOCK_VAR_ALIGN macro
 * must be defined for the common CPU build variants (e.g. PPC32, MIPS32, 
 * XSCALE, etc), representing the maximum cache line size of the variants of 
 * the respective arch. 
 *
 * For PPC this is 128 bytes.
 */

#define _WRS_KERNEL_LOCK_VAR_ALIGN		128

/* PPC specific extension fields to the WIND_VARS struct */

#ifndef _ASMLANGUAGE

/*
 * 8-byte alignment needed when used as intCrtSaveArea,
 * to ensure that both words are in the same cache line
 */

typedef struct wind_vars_arch
    {
#if defined (PPC_e6500)
    struct tlb1EntrySelect * cpu_tlb1EselPtr;
    struct tlb1EntrySelect cpu_tlb1Esel;
#else
    union sr		* cpu_currentSrTbl;
    union level_1_desc	* cpu_currentPgTbl;
#endif
    } WIND_VARS_ARCH _WRS_DATA_ALIGN_BYTES(8);

#define _WRS_WIND_VARS_ARCH WIND_VARS_ARCH cpu_archVars

#define _WRS_WIND_VARS_ARCH_ACCESS(glob) \
	_WRS_KERNEL_GLOBAL_ACCESS(archVars.cpu_##glob)

#if 0
/* XXX putting vxKernelVars[] into SDA degrades performance for some cases. */
#define _WRS_VX_KERNEL_VARS_SECTION_ATTR	_WRS_SDA_BSS
#endif /* 0 */

#define _WRS_KERNEL_STATE_LOCK_SECTION_ATTR	_WRS_SDA_DATA

#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT

extern cpuset_t __vxSmtSet[];
#define _WRS_CPU_SMTSET_GET(smtSet, cpuIx)	smtSet = __vxSmtSet[cpuIx]

#else /* !_ASMLANGUAGE */

/*
 * offsets required for assembly macros, allowing for above 8-byte alignment
 * We can't use ROUND_UP here because its expansion includes a typecast that
 * is valid only in C, not in assembly.
 */

#define WIND_VARS_ARCH_BASE	(((_WRS_WIND_VARS_OFFSET_archVars) + 7) & ~7)

/*
 * It is OK for these definitions to be based on CPU feature set since
 * they are used only in assembly code that is built per-variant.
 */
#if defined (PPC_e6500)
#define _WRS_WIND_VARS_OFFSET_tlb1EselPtr       (WIND_VARS_ARCH_BASE + 0)
#endif
# if	defined (_WRS_MMU_CLASS_SR_REGS)
#define _WRS_WIND_VARS_OFFSET_currentSrTbl	(WIND_VARS_ARCH_BASE + 0)
#define _WRS_WIND_VARS_OFFSET_currentPgTbl	(WIND_VARS_ARCH_BASE + 4)
# elif	defined (_PPC_MSR_CE_U)
#if defined(PPC_e6500)
#define _WRS_WIND_VARS_OFFSET_intCrtSaveArea	(WIND_VARS_ARCH_BASE + 8)	
#else
#define _WRS_WIND_VARS_OFFSET_intCrtSaveArea	(WIND_VARS_ARCH_BASE + 0)	
#endif
# endif	/* _WRS_MMU_CLASS_SR_REGS, _PPC_MSR_CE_U */

#endif /* _ASMLANGUAGE */

#define _WRS_MMU_HAS_MAP_STATE_API

#define	_ARCH_SUPPORTS_PROTECT_IDLE_TASK_STACK

/*
 * Defining _WRS_CONFIG_PPC_CACHE_MODE_IS_CONSISTENT removes cache management
 * around enabling and disabling the MMU.  It is always defined in SMP builds,
 * where the cache is required to always be enabled, coherent, and in
 * copyback mode (matching the default 60x no-MMU WIMG of 0011).  It can
 * potentially also be defined in source builds for UP systems, but only
 * if the accompanying constraints on cache configuration are met; this
 * cannot safely be assumed for UP systems in general due to legacy
 * considerations.
 */
#ifndef _WRS_CONFIG_PPC_CACHE_MODE_IS_CONSISTENT
#define	_WRS_CONFIG_PPC_CACHE_MODE_IS_CONSISTENT
#endif

/*
 * Some PowerPC will fault if an atomic operation (lwarx/stwcx.) is attempted
 * before the data cache has been enabled.  This flag causes edrBufLock(),
 * edrBufUnlock(), and perhaps other places, to consult spinLockApiAvailable()
 * before attempting to take a spinlock.  It is also used in windALib.s to
 * determine whether the spinLockApiAvailable() function should be defined.
 */
#define _WRS_ARCH_HAS_SPINLOCK_API_AVAILABLE
# ifndef  _ASMLANGUAGE
/*
 * spinLockApiAvailable actually returns BOOL, but neither that name nor
 * IMPORT has necessarily been defined by the time this file is included.
 */
extern int spinLockApiAvailable(void);
# endif   /* _ASMLANGUAGE */

/*
 * _WRS_WIND_VARS_ALIGN sets the alignment constraint for vxKernelVars.
 * The value must be:
 *   a power of two no smaller than sizeof(vxKernelVars), and
 *   a multiple of the cache line size on every PPC variant that supports SMP.
 */
#define	_WRS_WIND_VARS_ALIGN		128
#define	_WRS_WIND_VARS_ALIGN_SHIFT	7

/*
 * _PPC_ATOMIC_OPS_SEPARATION defines the minimum desirable separation
 * between words on which SMP-atomic operations (including spinlock)
 * will be performed, and should be set to the largest lwarx/stwcx.
 * granularity on any PPC variant that supports SMP (disregarding any
 * where the granularity is too large to honor, e.g. the entire address
 * space).  This turns out to be the cache line size on several SMP PPC.
 */
#define	_PPC_ATOMIC_OPS_SEPARATION	128

# ifdef	_CPU_CACHE_ALIGN_SIZE
/*
 * Validate _WRS_WIND_VARS_ALIGN vs current build's _CPU_CACHE_ALIGN_SIZE
 *
 * If any SMP-enabled variant fails this test, _WRS_WIND_VARS_ALIGN must be
 * increased.  Since this limit also applies to any subsequent arch-only
 * release against the same generic binary release, it may be desirable to
 * allow for growth.
 */

#  if (_CPU_CACHE_ALIGN_SIZE > _WRS_WIND_VARS_ALIGN)
#error Must increase "_WRS_WIND_VARS_ALIGN" to at least _CPU_CACHE_ALIGN_SIZE
#  endif  /* _CPU_CACHE_ALIGN_SIZE > _WRS_WIND_VARS_ALIGN */

/*
 * Sanity check on _PPC_ATOMIC_OPS_SEPARATION
 *
 * A miss here generates a warning instead of an error, since it is merely
 * likely (not inevitable) that the lwarx/stwcx. granularity matches the
 * cache line size; also the performance penalty is less.  (Two instances of
 * vxKernelVars within the same cache line will cause continual interference,
 * but two atoms within the same reservation granule will only occasionally
 * cause additional trips around the lwarx/stwcx. loop due to loss of the
 * reservation to an unrelated store.)
 */
#  if (_CPU_CACHE_ALIGN_SIZE > _PPC_ATOMIC_OPS_SEPARATION)
#warning Check "_PPC_ATOMIC_OPS_SEPARATION" setting; it likely should be at least _CPU_CACHE_ALIGN_SIZE
#  endif  /* _CPU_CACHE_ALIGN_SIZE > _PPC_ATOMIC_OPS_SEPARATION */
# endif	/* _CPU_CACHE_ALIGN_SIZE */

/*
 * Just call the (assembly) function for now, but to optimize
 * performance this should eventually become a C-callable
 * _WRS_ASM construct (whose syntax varies depending on TOOL).
 */
#define	_WRS_CPU_INDEX_GET()	vxCpuIndexGet()
#else	/* _WRS_CONFIG_SMP */
#define	_WRS_CPU_INDEX_GET()	0
#endif	/* _WRS_CONFIG_SMP */

#ifdef _ASMLANGUAGE

# ifdef	_WRS_CONFIG_SMP
DATA_IMPORT(vxKernelVars);

/* NOTE: PCV stands for per-cpu variable */

/* get the index of current cpu */
#ifdef _WRS_CONFIG_WRHV_GUEST
#define VB_VCORE_ID_OFFSET	0x98
#define	_PPC_CPU_INDEX_GET(r)   lis	r, HIADJ(wrhvVbConfig) ; \
				lwz  	r, LO(wrhvVbConfig)(r) ; \
				lwz 	r, VB_VCORE_ID_OFFSET(r) 
#else  /* _WRS_CONFIG_WRHV_GUEST */
#   if (CPU == PPC476)
#define	_PPC_CPU_INDEX_GET(r)	mfspr	r, SPRG8
#   else /* !PPC476 */
#define	_PPC_CPU_INDEX_GET(r)	mfspr	r, PIR
#   endif /* PPC476 */
#endif /* _WRS_CONFIG_WRHV_GUEST */ 

/* offset into "label" from the start of the windVars structure */
#define _WRS_WIND_VARS_OFFSET(label)	(_WRS_WIND_VARS_OFFSET_##label)

/* offset into "label" from "bLabel" */
#define _WRS_WIND_VARS_OFFSET_FROM_BASE(label, bLabel)	  \
	(_WRS_WIND_VARS_OFFSET(label) - _WRS_WIND_VARS_OFFSET(bLabel))

/* address of the "label" per-cpu variable for cpu0 */
#define _WRS_CPU0_VAR_ADRS(label)    (vxKernelVars+_WRS_WIND_VARS_OFFSET(label))

/* get the offset into the per-cpu variables for "cpuIx" */
#define _PPC_PER_CPU_VARS_CPU_OFFSET_GET_WITH_INDEX(offset, cpuIx) \
	slwi   offset, cpuIx, _WRS_WIND_VARS_ALIGN_SHIFT

/* get the offset into the per-cpu variables for current cpu */
#define _PPC_PER_CPU_VARS_CPU_OFFSET_GET(r)		  \
	_PPC_CPU_INDEX_GET(r)				; \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET_WITH_INDEX(r, r)

/*
 * _CPU_OFFSET macros are mainly used to construct other _PPC_PER_CPU_ macros.
 * Please be careful when using them in assembly code as they don't have
 * the UP counterparts.
 */

/* get the address of the "label" variable with cpu offset */
#define _PPC_PER_CPU_ADRS_GET_WITH_CPU_OFFSET(ra, label, offset)	  \
	addis	ra, offset, HIADJ(_WRS_CPU0_VAR_ADRS(label))		; \
	addi	ra, ra, LO(_WRS_CPU0_VAR_ADRS(label))

/* get the value of the "label" variable with cpu offset */
#define _PPC_PER_CPU_VALUE_GET_WITH_CPU_OFFSET(rv, label, offset)	  \
	addis	rv, offset, HIADJ(_WRS_CPU0_VAR_ADRS(label))		; \
	lwz	rv, LO(_WRS_CPU0_VAR_ADRS(label))(rv)

/* set the value of the "label" variable with cpu offset */
#define _PPC_PER_CPU_VALUE_SET_WITH_CPU_OFFSET(v, sc, label, offset)	  \
	addis	sc, offset, HIADJ(_WRS_CPU0_VAR_ADRS(label))		; \
	stw	v, LO(_WRS_CPU0_VAR_ADRS(label))(sc)

/* get the value and the address of the "label" variable with cpu offset */
#define _PPC_PER_CPU_VALUE_AND_ADRS_GET_WITH_CPU_OFFSET(rv, ra, label, offset) \
	addis	ra, offset, HIADJ(_WRS_CPU0_VAR_ADRS(label))		; \
	lwzu	rv, LO(_WRS_CPU0_VAR_ADRS(label))(ra)

/* set the value and get the address of the "label" variable with cpu offset */
#define _PPC_PER_CPU_VALUE_SET_ADRS_GET_WITH_CPU_OFFSET(v, ra, label, offset) \
	addis	ra, offset, HIADJ(_WRS_CPU0_VAR_ADRS(label))		; \
	stwu	v, LO(_WRS_CPU0_VAR_ADRS(label))(ra)

/*
 * simple _GET/_SET macros should be used when only one PCV needs to be
 * accessed or there's no register available to save base address.
 */ 

/* get the address of the "label" variable for current cpu */
#define	_PPC_PER_CPU_ADRS_GET(r, label)			  \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET(r)		; \
	_PPC_PER_CPU_ADRS_GET_WITH_CPU_OFFSET(r, label, r)

/* get the value of the "label" variable for current cpu */
#define	_PPC_PER_CPU_VALUE_GET(r, label)		  \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET(r)		; \
	_PPC_PER_CPU_VALUE_GET_WITH_CPU_OFFSET(r, label, r)

/* set the value of the "label" variable for current cpu */
#define _PPC_PER_CPU_VALUE_SET(v, sc, label)		  \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET(sc)		; \
	_PPC_PER_CPU_VALUE_SET_WITH_CPU_OFFSET(v, sc, label, sc)

/* get the value and the address of the "label" variable for current cpu */
#define	_PPC_PER_CPU_VALUE_AND_ADRS_GET(rv, ra, label)	  \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET(ra)		; \
	_PPC_PER_CPU_VALUE_AND_ADRS_GET_WITH_CPU_OFFSET(rv, ra, label, ra)

/* set the value and get the address of the "label" variable for current cpu */
#define	_PPC_PER_CPU_VALUE_SET_ADRS_GET(v, ra, label)	  \
	_PPC_PER_CPU_VARS_CPU_OFFSET_GET(ra)		; \
	_PPC_PER_CPU_VALUE_SET_ADRS_GET_WITH_CPU_OFFSET(v, ra, label, ra)

/*
 * _VARS_BASE_GET/_WITH_BASE macros should be used when multiple PCVs need
 * to be accessed and it is guaranteed that the current CPU will not change
 * while accessing multiple PCVs (i.e. interrupt locked or kernel lock taken).
 */ 

/*
 * get the address of the "label" variable as the base address of PCVs
 * for current cpu
 */
#define _PPC_PER_CPU_VARS_BASE_GET(rb, label)				  \
	_PPC_PER_CPU_ADRS_GET(rb, label)

/*
 * get the address of the "label" variable as the base address of PCVs
 * with cpu offset
 */
#define _PPC_PER_CPU_VARS_BASE_GET_WITH_CPU_OFFSET(rb, label, offset)	  \
	_PPC_PER_CPU_ADRS_GET_WITH_CPU_OFFSET(rb, label, offset)	

/*
 * get the value and the address of the "label" variable
 * and use the address as the base address of PCVs
 * for current cpu
 */
#define _PPC_PER_CPU_VALUE_AND_VARS_BASE_GET(rv, rb, label)		  \
	_PPC_PER_CPU_VALUE_AND_ADRS_GET(rv, rb, label)

/*
 * set the value and get the address of the "label" variable
 * and use the address as the base address of PCVs
 * for current cpu
 */
#define _PPC_PER_CPU_VALUE_SET_VARS_BASE_GET(v, rb, label)		  \
	_PPC_PER_CPU_VALUE_SET_ADRS_GET(v, rb, label)

/* get the address of the "label" variable with the base address of "bLabel" */
#define _PPC_PER_CPU_ADRS_GET_WITH_BASE(ra, label, b, bLabel)		  \
	addi	ra, b, _WRS_WIND_VARS_OFFSET_FROM_BASE(label, bLabel)

/* get the value of the "label" variable with the base address of "bLabel" */
#define _PPC_PER_CPU_VALUE_GET_WITH_BASE(rv, label, b, bLabel)		  \
	lwz	rv, _WRS_WIND_VARS_OFFSET_FROM_BASE(label, bLabel)(b)

/* set the value of the "label" variable with the base address of "bLabel" */
#define _PPC_PER_CPU_VALUE_SET_WITH_BASE(v, sc, label, b, bLabel)	  \
	stw	v, _WRS_WIND_VARS_OFFSET_FROM_BASE(label, bLabel)(b)

/*
 * get the value and the address of the "label" variable
 * with the base address of "bLabel"
 */
#define _PPC_PER_CPU_VALUE_AND_ADRS_GET_WITH_BASE(rv, ra, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_GET_WITH_BASE(rv, label, b, bLabel)		; \
	_PPC_PER_CPU_ADRS_GET_WITH_BASE(ra, label, b, bLabel)

/*
 * set the value and get the address of the "label" variable
 * with the base address of "bLabel"
 */
#define _PPC_PER_CPU_VALUE_SET_ADRS_GET_WITH_BASE(v, ra, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_SET_WITH_BASE(v, label, b, bLabel)		; \
	_PPC_PER_CPU_ADRS_GET_WITH_BASE(ra, label, b, bLabel)

/* _SDA is equivalent to non _SDA in SMP as vxKernelVars[] are not in SDA */

/* get the value of the "label" variable for current cpu (SDA base valid) */
#define _PPC_PER_CPU_VALUE_GET_SDA(rv, label)				  \
	_PPC_PER_CPU_VALUE_GET(rv, label)

/* set the value of the "label" variable for current cpu (SDA base valid) */
#define _PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)			  \
	_PPC_PER_CPU_VALUE_SET(v, sc, label)

/*
 * get the value and the address of the "label" variable
 * and use the address as the base address of PCVs
 * for current cpu (SDA base valid)
 */
#define _PPC_PER_CPU_VALUE_AND_VARS_BASE_GET_SDA(rv, rb, label)		  \
	_PPC_PER_CPU_VALUE_AND_ADRS_GET(rv, rb, label)

/*
 * set the value and get the address of the "label" variable
 * and use the address as the base address of PCVs
 * for current cpu (SDA base valid)
 */
#define _PPC_PER_CPU_VALUE_SET_VARS_BASE_GET_SDA(v, rb, label)		  \
	_PPC_PER_CPU_VALUE_SET_ADRS_GET(v, rb, label)

/*
 * get the value of the "label" variable with the base address of "bLabel"
 * (SDA base valid)
 */
#define _PPC_PER_CPU_VALUE_GET_SDA_WITH_BASE(rv, label, b, bLabel)	  \
	_PPC_PER_CPU_VALUE_GET_WITH_BASE(rv, label, b, bLabel)

/*
 * set the value of the "label" variable with the base address of "bLabel"
 * (SDA base valid)
 */
#define _PPC_PER_CPU_VALUE_SET_SDA_WITH_BASE(v, sc, label, b, bLabel)	  \
	_PPC_PER_CPU_VALUE_SET_WITH_BASE(v, sc, label, b, bLabel)

/*
 * Macros to support a minimal locking operation, using CR0 and one scratch
 * register.  A base register must also be provided unless the lock word is
 * located within 32KB of address 0.  The base register will not be altered,
 * and unless using 0 (=> base address == 0) it must be preset.  This is
 * generalized from code originally written for mmu600ALib.s vn. 01v,10may06,to
 *
 * reg is a scratch register number in [1,31]
 * offset is a 16-bit non-zero signed constant
 * base is a base register number in [0,31]
 * The lock word is located at offset(base), and is set to 0
 * when the lock is not held, or offset when it is held.
 */

#define	_PPC_MINIMAL_LOCK(reg, offset, base)				\
10:	lwz	reg, offset(base)	/* reg = key */ ;		\
	cmpwi	reg, 0 ;						\
	bne-	10b			/* spin until (lock == 0) */ ;	\
	li	reg, offset ;						\
	lwarx	reg, base, reg		/* reg = lock (reserving) */ ;	\
	cmpwi	reg, 0 ;						\
	bne-	10b		/* spin until (reserved lock == 0) */ ;	\
	li	reg, offset ;						\
	stwcx.	reg, base, reg		/* try store lock = offset */ ;	\
	bne-	10b			/* retry if store failed */ ;	\
	isync

#define	_PPC_MINIMAL_TRY_LOCK(reg, offset, base, label)			\
	li	reg, offset ;						\
	lwarx	reg, base, reg		/* reg = lock (reserving) */ ;	\
	cmpwi	reg, 0 ;						\
	bne	label			/* if (lock != 0) goto label */ ; \
	li	reg, offset ;						\
	stwcx.	reg, base, reg		/* try store lock = offset */ ;	\
	bne	label			/* goto label if failed */ ;	\
	isync

#define	_PPC_MINIMAL_UNLOCK(reg, offset, base)	\
	sync ;					\
	li	reg, 0 ;			\
	stw	reg, offset(base)

/*
 * ro = register to store kernel lock owner
 * ri = register to store cpu index
 *
 * typedef struct vxKernelLock
 *     {
 *     atomic_t    tkt_ctr;        /@ ticket counter                       @/
 *     char        pad[];          /@ force tkt_ctr to consume cache line  @/
 *     int         cpuIndex;       /@ Owner cpu identifier                 @/
 *     atomic_t    svc_ctr;        /@ ticket currently being serviced      @/
 *     int         flags;          /@ Reserved for system use              @/
 */

#define _PPC_KERNEL_LOCK_OWNER_GET(ro)				  \
	lis	ro, HIADJ(kernelStateLock + _WRS_KERNEL_LOCK_OFFSET_cpuIndex); \
	lwz	ro, LO(kernelStateLock + _WRS_KERNEL_LOCK_OFFSET_cpuIndex)(ro)

#define _PPC_KERNEL_LOCK_OWNER_GET_SDA(ro)			  \
	lwz	ro, SDA21(kernelStateLock + _WRS_KERNEL_LOCK_OFFSET_cpuIndex)

#define _PPC_KERNEL_LOCK_OWNER_AND_INDEX_GET(ro, ri)		  \
	_PPC_KERNEL_LOCK_OWNER_GET(ro)				; \
	_PPC_CPU_INDEX_GET(ri)

# else	/* _WRS_CONFIG_SMP */

/* Macro unconditionally returns 0 when built for UP */
#define	_PPC_CPU_INDEX_GET(r)	li	r, 0

#define	_PPC_PER_CPU_ADRS_GET(r, label)   \
	lis	r, HIADJ(label)		; \
	addi	r, r, LO(label)

/*
 * r2 and r13 could have the _SDA2_BASE_ and _SDA_BASE_ for RTP and it's not
 * able to access through SDA. If it's certain it's not the case, it's
 * recommended to use _PPC_PER_CPU_VALUE_GET_SDA()/_PPC_PER_CPU_VALUE_SET_SDA()
 * to reduce the number of the instructions.
 */

#if	(defined(_WRS_CONFIG_VM_MULTIPLE_CONTEXT) || !defined(_PPC_USE_SDA))
#define	_PPC_PER_CPU_VALUE_GET(r, label)		  \
	lis	r, HIADJ(label)				; \
	lwz	r, LO(label)(r)
#else	/* (_WRS_CONFIG_VM_MULTIPLE_CONTEXT || !_PPC_USE_SDA */
#define	_PPC_PER_CPU_VALUE_GET(r, label)		  \
	/* If RTP is not supported, use SDA any time. */  \
	_PPC_PER_CPU_VALUE_GET_SDA(r, label)
#endif	/* (_WRS_CONFIG_VM_MULTIPLE_CONTEXT || !_PPC_USE_SDA */

#if	(defined(_WRS_CONFIG_VM_MULTIPLE_CONTEXT) || !defined(_PPC_USE_SDA))
#define	_PPC_PER_CPU_VALUE_SET(v, sc, label)		  \
	lis	sc, HIADJ(label)			; \
	stw	v, LO(label)(sc)
#else	/* (_WRS_CONFIG_VM_MULTIPLE_CONTEXT || !_PPC_USE_SDA */
#define	_PPC_PER_CPU_VALUE_SET(v, sc, label)		  \
	/* If RTP is not supported, use SDA any time. */  \
	_PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)
#endif	/* (_WRS_CONFIG_VM_MULTIPLE_CONTEXT || !_PPC_USE_SDA */

#define	_PPC_PER_CPU_VALUE_AND_ADRS_GET(rv, ra, label)	  \
	lis	ra, HIADJ(label)			; \
	lwzu	rv, LO(label)(ra)

#define	_PPC_PER_CPU_VALUE_SET_ADRS_GET(v, ra, label)	  \
	lis	ra, HIADJ(label)			; \
	stwu	v, LO(label)(ra)

/* _VARS_BASE is ignored in UP */

#define _PPC_PER_CPU_VARS_BASE_GET(rb, label)

#define _PPC_PER_CPU_VALUE_AND_VARS_BASE_GET(rv, rb, label) \
	_PPC_PER_CPU_VALUE_GET(rv, label)

#define _PPC_PER_CPU_VALUE_SET_VARS_BASE_GET(v, sc, label)  \
	_PPC_PER_CPU_VALUE_SET(v, sc, label)

#define _PPC_PER_CPU_ADRS_GET_WITH_BASE(ra, label, b, bLabel) \
	_PPC_PER_CPU_ADRS_GET(ra, label)

#define _PPC_PER_CPU_VALUE_GET_WITH_BASE(rv, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_GET(rv, label)

#define _PPC_PER_CPU_VALUE_SET_WITH_BASE(v, sc, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_SET(v, sc, label)

#define _PPC_PER_CPU_VALUE_AND_ADRS_GET_WITH_BASE(rv, ra, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_AND_ADRS_GET(rv, ra, label)

#define _PPC_PER_CPU_VALUE_SET_ADRS_GET_WITH_BASE(v, ra, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_SET_ADRS_GET(v, ra, label)

#ifdef	_PPC_USE_SDA

#define	_PPC_PER_CPU_VALUE_GET_SDA(r, label)		  \
	LOADVAR_SDA(r, label)

#define	_PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)	  \
	STOREVAR_SDA(v, sc, label)

#else	/* _PPC_USE_SDA */

#define	_PPC_PER_CPU_VALUE_GET_SDA(r, label)		  \
	_PPC_PER_CPU_VALUE_GET(r, label)

#define	_PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)	  \
	_PPC_PER_CPU_VALUE_SET(v, sc, label)

#endif	/* _PPC_USE_SDA */

#define _PPC_PER_CPU_VALUE_AND_VARS_BASE_GET_SDA(rv, rb, label) \
	_PPC_PER_CPU_VALUE_GET_SDA(rv, label)

#define _PPC_PER_CPU_VALUE_SET_VARS_BASE_GET_SDA(v, sc, label) \
	_PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)

#define _PPC_PER_CPU_VALUE_GET_SDA_WITH_BASE(rv, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_GET_SDA(rv, label)

#define _PPC_PER_CPU_VALUE_SET_SDA_WITH_BASE(v, sc, label, b, bLabel) \
	_PPC_PER_CPU_VALUE_SET_SDA(v, sc, label)

# endif /* _WRS_CONFIG_SMP */
#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsmpPpcPh */
