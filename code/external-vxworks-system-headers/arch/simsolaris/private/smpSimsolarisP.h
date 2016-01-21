/* smpSimsolarisP.h - simsolaris private SMP assembler definitions hdr file */

/*
 * Copyright (c) 2006-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01s,24feb11,elp  added vxsimHostCpuDelay() vxsimHostCpuWakeup()
                 CQ:WIND00151275.
01r,29jul10,pad  Moved extern C statement after include statements.
01q,15may09,gls  moved VX_INSTR_BARRIER() to vxAtomicArchLibCommon.h
01p,26sep08,gls  added _WRS_KERNEL_LOCK_VAR_ALIGN
01o,27aug08,jpb  Renamed VSB header file
01n,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01m,20jun08,zl   replaced _WRS_ASM() with _WRS_BARRIER()
01l,18jan08,gls  added VX_INSTR_BARRIER()
01k,23jul07,elp  include vxsimHostLibP.h to remove extern vxsimHostSleep().
01j,19jul07,rlp  Declared vxsimHostSleep() as extern, this is a temporary fix
                 to be able to build the aim directory.
01i,16jul07,elp  added _WRS_ARCH_CPU_DELAY() macro.
01h,17apr07,kk   move VX_MAX_SMP_CPUS to archSolaris.h
01g,16mar07,elp  fixed cplus build
01f,08mar07,dbt  Removed inclusion of mmuArchLib.h
01e,19dec06,elp  moved simStatus and simPendingIntLvl to host,
		 added macros to get WIND_VARS locked, added intNest.
01d,11dec06,kk   removed references to VX_KERNEL_VARS define, no longer needed
01c,30nov06,dbt  Increased maximum number of CPUs to 32.
01b,24nov06,dbt  Added missing macros.
01a,07sep06,elp  created
*/

#ifndef	__INCsmpSimsolarisPh
#define	__INCsmpSimsolarisPh

/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Any compilation using definitions from this file will not *
 * be binary-compatible between the UP and SMP environments. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#include <vsbConfig.h>

#ifdef  _WRS_CONFIG_SMP

/*
 * Much like the _WRS_WIND_VARS_ALIGN the _WRS_KERNEL_LOCK_VAR_ALIGN macro
 * must be defined for the common CPU build variants (e.g. PPC32, MIPS32, 
 * XSCALE, etc), representing the maximum cache line size of the variants of 
 * the respective arch. 
 *
 * For the SIMSPARCSOLARIS this is 128 bytes.
 */

#define _WRS_KERNEL_LOCK_VAR_ALIGN		128

#ifndef _ASMLANGUAGE

#include <private/vxsimHostLibP.h>

#ifdef __cplusplus
extern "C" {
#endif
	
#define _WRS_ARCH_CPU_DELAY()		(vxsimHostCpuDelay (0))
#define _WRS_ARCH_CPU_DELAY_MS(ms)	(vxsimHostCpuDelay (ms))
#define _WRS_ARCH_CPU_WAKEUP(cpuIx)	(vxsimHostCpuWakeup (cpuIx))

extern UINT32 *	pVxCpuIndex;

/* optimized access without function call */

#define _WRS_CPU_INDEX_GET()	(*pVxCpuIndex)

#ifdef __cplusplus
}
#endif

#endif /* ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif
	
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

#ifndef _ASMLANGUAGE

typedef struct wind_vars_arch
    {
    UINT32	cpu_intNest;		/* 0x0: interrupt nested count */
    struct mmuTransTblStruct * cpu_pMmuCurrentTransTbl;
    					/* 0x04: current MMU trans table */
    UINT32	cpu_ctxLoadIntLock;	/* 0x8: context load intlock */
    } WIND_VARS_ARCH;

#define _WRS_WIND_VARS_ARCH WIND_VARS_ARCH cpu_archVars

/* macros to access the arch-specific fields of the vxKernelVars struct */

#define _WRS_WIND_VARS_ARCH_ACCESS(glob)		\
    _WRS_KERNEL_GLOBAL_ACCESS (archVars.cpu_##glob)

#define _WRS_WIND_VARS_ARCH_SET(cpuid,glob,var)		\
    _WRS_KERNEL_CPU_GLOBAL_SET(cpuid,archVars.cpu_##glob,var)

#define _WRS_WIND_VARS_ARCH_LOCKED_GET(glob, var)		\
    _WRS_KERNEL_LOCKED_GLOBAL_GET (archVars.cpu_##glob, var)

#else /* _ASMLANGUAGE */

#define _WRS_WIND_VARS_OFFSET_intNest	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x0)
#define _WRS_WIND_VARS_OFFSET_pMmuCurrentTransTbl	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x4)
#define _WRS_WIND_VARS_OFFSET_ctxLoadIntLock	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x8)

#define _WRS_SIMSPARC_VAR_ADRS(label)	FUNC(vxKernelVars+OFFSET_##label)
#define _WRS_WIND_VARS_OFFSET(reg)      sll reg,_WRS_WIND_VARS_ALIGN_SHIFT,reg;

/*
 * take the value at *pVxCpuIndex and shift to get the vxKernelVar index
 * 0,128,256 ...
 */

#define _SIMSPARC_CPU_INDEX_GET(reg,scratch)		\
    sethi	%hi(FUNC(pVxCpuIndex)),reg;		\
    ld		[reg + %lo(FUNC(pVxCpuIndex))],reg;	\
    ld		[reg], reg;				\
    _WRS_WIND_VARS_OFFSET(reg)

#define _WRS_LOAD_REG_WITH_VAR_BASE(label,reg)          \
    set		FUNC(vxKernelVars),reg;			\
    add		reg,_WRS_WIND_VARS_OFFSET_##label,reg;

#define _SIMSPARC_PER_CPU_ADRS_GET(reg,scratch,label)	\
    _SIMSPARC_CPU_INDEX_GET(reg,scratch)		\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)		\
    add		reg,scratch,reg;

#define _SIMSPARC_PER_CPU_VALUE_GET(reg,scratch,label)	\
    _SIMSPARC_CPU_INDEX_GET(reg,scratch)		\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)		\
    ld		[reg + scratch], reg;

#define _SIMSPARC_PER_CPU_VALUE_CLEAR(reg,scratch,label)\
    _SIMSPARC_CPU_INDEX_GET(reg,scratch)		\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)		\
    st		%g0, [reg + scratch];

#define _SIMSPARC_PER_CPU_VALUE_INC(reg,scratch,label)	\
    _SIMSPARC_CPU_INDEX_GET(reg,scratch)		\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)		\
    add		scratch,reg,scratch;			\
    ld		[scratch], reg;				\
    add		reg,1,reg;				\
    st		reg,[scratch]


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#else /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif
	
#define _WRS_CPU_INDEX_GET()	0

/* macro to access the arch-specific fields */

#define _WRS_WIND_VARS_ARCH_ACCESS(glob)		\
    _WRS_KERNEL_GLOBAL_ACCESS (glob)

#define _WRS_WIND_VARS_ARCH_SET(ignored,glob,var)	\
    _WRS_KERNEL_CPU_GLOBAL_SET(ignored,glob,var)

#define _WRS_WIND_VARS_ARCH_LOCKED_GET(glob,var)	\
    _WRS_KERNEL_LOCKED_GLOBAL_GET (glob,var)

#ifdef _ASMLANGUAGE

#define _SIMSPARC_PER_CPU_ADRS_GET(reg,scratch,label)	\
    set		FUNC(label),reg;

#define _SIMSPARC_PER_CPU_VALUE_GET(reg,scratch,label)	\
    sethi	%hi(FUNC(label)),reg;			\
    ld		[reg + %lo(FUNC(label))],reg;

#define _SIMSPARC_PER_CPU_VALUE_CLEAR(reg,scratch,label)\
    sethi	%hi(FUNC(label)),reg;			\
    st		%g0, [reg + %lo(FUNC(label))]

#define _SIMSPARC_PER_CPU_VALUE_INC(reg,scratch,label)	\
    sethi	%hi(FUNC(label)),reg;			\
    ld		[reg + %lo(FUNC(label))],reg;		\
    add		reg, 1, reg;				\
    sethi	%hi(FUNC(label)),scratch;		\
    st		reg, [scratch + %lo(FUNC(label))]

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* _WRS_CONFIG_SMP */

#endif	/* __INCsmpSimsolarisPh */
