/* smpSimntP.h - simnt/simlinux private SMP assembler definitions header file */

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
01v,24feb11,elp  added vxsimHostCpuDelay() vxsimHostCpuWakeup()
		 (CQ:WIND00151275).
01u,29dec10,dbt  Fixed _SIMIA_PER_CPU_VALUE32_INC macro in 64-bit mode to
                 correct return value.
01t,18oct10,elp  implement LP64 SMP macros.
01s,03aug10,elp  fixed _SIMIA_PER_CPU_ADRS_GET(64 bits).
01r,29jul10,pad  Moved extern C statement after include statements.
01q,02jun10,elp  64 bits support.
01p,15may09,gls  moved VX_INSTR_BARRIER() to vxAtomicArchLibCommon.h
01o,26sep08,gls  added _WRS_KERNEL_LOCK_VAR_ALIGN
01n,27aug08,jpb  Renamed VSB header file
01m,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01l,18jan08,gls  added VX_INSTR_BARRIER()
01k,09jan08,elp  removed previous temporary fix.
01j,19jul07,rlp  Declared vxsimHostSleep() as extern, this is a temporary fix
                 to be able to build the aim directory.
01i,16jul07,elp  added _WRS_ARCH_CPU_DELAY() macro.
01h,17apr07,kk   move VX_MAX_SMP_CPUS to archSimnt.h
01g,16mar07,elp  fixed cplus build
01f,08mar07,dbt  Removed inclusion of mmuArchLib.h
01e,19dec06,elp  added macros to get WIND_VARS locked, moved simStatus and
		 simPendingIntLvl to host variables.
01d,11dec06,kk   removed references to VX_KERNEL_VARS define, no longer needed
01c,30nov06,dbt  Increased maximum number of CPUs to 32.
01b,23nov06,dbt  Fixed syntax for GNU compiler.
		 Removed _WRS_WIND_VARS_OFFSET_archVars definition
		 Increased maximum CPU number to 16
01a,07sep07,elp  created
*/

#ifndef	__INCsmpSimntPh
#define	__INCsmpSimntPh

/************************************************************/

#include <vsbConfig.h>


#ifndef _ASMLANGUAGE
#include <private/vxsimHostLibP.h>
#endif /* ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif
	
#define REG32_rax		eax
#define REG32_rbx		ebx
#define REG32_rcx		ecx
#define REG32_rdx		edx
#define REG32_r10		r10d
#define REG32_r11		r11d
    
#ifdef  _WRS_CONFIG_SMP

#ifndef _ASMLANGUAGE
#define _WRS_ARCH_CPU_DELAY()		(vxsimHostCpuDelay(0))
#define _WRS_ARCH_CPU_DELAY_MS(ms)	(vxsimHostCpuDelay(ms))
#define _WRS_ARCH_CPU_WAKEUP(cpuIx)	(vxsimHostCpuWakeup(cpuIx))

/* optimized access without function call */

#define _WRS_CPU_INDEX_GET()	(*pVxCpuIndex)
#endif /* ASMLANGUAGE */

/*
 * Much like the _WRS_WIND_VARS_ALIGN the _WRS_KERNEL_LOCK_VAR_ALIGN macro
 * must be defined for the common CPU build variants (e.g. PPC32, MIPS32, 
 * XSCALE, etc), representing the maximum cache line size of the variants of 
 * the respective arch. 
 *
 * For SIMNT/SIMLINUX this is 128 bytes.
 */

#define _WRS_KERNEL_LOCK_VAR_ALIGN		128

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

#ifdef _WRS_CONFIG_LP64

/* WIND_VARS size is 0x70+0x58=0xc8(200) */

#define _WRS_WIND_VARS_ALIGN		256
#define _WRS_WIND_VARS_ALIGN_SHIFT	8

#else /* _WRS_CONFIG_LP64 */

/* WIND_VARS size is 0x4c+0x28=0x74(116) */

#define _WRS_WIND_VARS_ALIGN            128
#define _WRS_WIND_VARS_ALIGN_SHIFT      7
#endif /* _WRS_CONFIG_LP64 */

#ifndef _ASMLANGUAGE

typedef struct wind_vars_arch
    {
    struct mmuTransTblStruct * cpu_pMmuCurrentTransTbl;
    					/* 0x00|0x00: current MMU table */
#ifdef _WRS_CONFIG_LP64
    ULONG	cpu_ctxLoadTmpRegs[8];	/* 0x08:
    					 * ss,rsp,rflags,cs,rip,rax,rcx,rdx */
#else
    ULONG	cpu_ctxLoadPc;		/* 0x04 context load pc */
    ULONG	cpu_ctxLoadEax;		/* 0x08 context load eax */
    ULONG	cpu_ctxLoadEcx;		/* 0x0c context load ebx */
    ULONG	cpu_ctxLoadEflags;	/* 0x10 context load eflags */
#endif /* _WRS_CONFIG_LP64 */
    UINT32	cpu_ctxLoadIntLock;	/* 0x14|0x48: context load intlock */
    BOOL	cpu_windSchedDefer;	/* 0x18|0x4c: defer rescheduling */
    BOOL	cpu_windSchedIsLocked;	/* 0x1c|0x50: scheduler locked */
    UINT32	cpu_intNest;		/* 0x20|0x54: interrupt mask and mode */
    } WIND_VARS_ARCH;

#define _WRS_WIND_VARS_ARCH WIND_VARS_ARCH cpu_archVars

/* macros to access the arch-specific fields of the vxKernelVars struct */

#define _WRS_WIND_VARS_ARCH_ACCESS(glob)		\
    _WRS_KERNEL_GLOBAL_ACCESS (archVars.cpu_##glob)

#define _WRS_WIND_VARS_ARCH_LOCKED_GET(glob,var)		\
    _WRS_KERNEL_LOCKED_GLOBAL_GET (archVars.cpu_##glob,var)

#define _WRS_WIND_VARS_ARCH_SET(cpuid,glob,var)		\
    _WRS_KERNEL_CPU_GLOBAL_SET(cpuid,archVars.cpu_##glob,var)

extern UINT32 *	pVxCpuIndex;
	
#else /* _ASMLANGUAGE */

#ifdef _WRS_CONFIG_LP64

#define _WRS_WIND_VARS_OFFSET_pMmuCurrentTransTbl	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x0)

#define _WRS_WIND_VARS_OFFSET_ctxLoadTmpRegs		\
    (_WRS_WIND_VARS_OFFSET_archVars+0x08)
#define _WRS_WIND_VARS_OFFSET_intNest		\
    (_WRS_WIND_VARS_OFFSET_archVars+0x54)

#define _WRS_WIND_VARS_OFFSET(reg)	rol $_WRS_WIND_VARS_ALIGN_SHIFT,reg;
#define _WRS_SIMIA_VAR_ADRS(label)	FUNC(vxKernelVars+OFFSET_##label)

/*
 * take the value at *pVxCpuIndex and shift to get the vxKernelVar index
 * 0,128,256 ...
 */

#define _SIMIA_CPU_INDEX_GET(regSuffix)			\
    movabsq	$VAR(pVxCpuIndex),%r##regSuffix;	\
    movq	(%r##regSuffix),%r##regSuffix;		\
    movl	(%r##regSuffix),%REG32_r##regSuffix;	\
    rol		$_WRS_WIND_VARS_ALIGN_SHIFT,%REG32_r##regSuffix;

/* put windVars->label address in reg */

#define _WRS_LOAD_REG_WITH_VAR_BASE(label,regSuffix)		\
    movabsq	$FUNC(vxKernelVars),%r##regSuffix;		\
    add		$_WRS_WIND_VARS_OFFSET_##label,%r##regSuffix;

/* put windvar->label address in r<regSuffix> */

#define _SIMIA_PER_CPU_ADRS_GET(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    add		%r##scratch,%r##regSuffix;

/* put windVars->label field 32 bits value in e<regSuffix> */

#define _SIMIA_PER_CPU_VALUE32_GET(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    add		%r##regSuffix,%r##scratch;			\
    movl	0x0(%r##scratch),%REG32_r##regSuffix;

/* put windVars->label field 64 bits value in r<regSuffix> */

#define _SIMIA_PER_CPU_VALUE64_GET(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    add		%r##regSuffix,%r##scratch;			\
    movq	0x0(%r##scratch),%r##regSuffix;

/* increment windVars->label field (int) */

#define _SIMIA_PER_CPU_VALUE32_INC(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    add		%r##regSuffix,%r##scratch;			\
    movl	0x0(%r##scratch),%REG32_r##regSuffix;		\
    incl	%REG32_r##regSuffix;				\
    movl	%REG32_r##regSuffix,0x0(%r##scratch);

#else /* _WRS_CONFIG_LP64 */

#define _WRS_WIND_VARS_OFFSET_pMmuCurrentTransTbl	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x0)
#define _WRS_WIND_VARS_OFFSET_ctxLoadPc		\
    (_WRS_WIND_VARS_OFFSET_archVars+0x04)
#define _WRS_WIND_VARS_OFFSET_ctxLoadEax	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x08)
#define _WRS_WIND_VARS_OFFSET_ctxLoadEbx	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x0c)
#define _WRS_WIND_VARS_OFFSET_ctxLoadEflags	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x10)
#define _WRS_WIND_VARS_OFFSET_ctxLoadIntLock	\
    (_WRS_WIND_VARS_OFFSET_archVars+0x14)
#define _WRS_WIND_VARS_OFFSET_intNest		\
    (_WRS_WIND_VARS_OFFSET_archVars+0x20)

#define _WRS_WIND_VARS_OFFSET(reg)      rol $_WRS_WIND_VARS_ALIGN_SHIFT,reg;
#define _WRS_SIMIA_VAR_ADRS(label)    FUNC(vxKernelVars+OFFSET_##label)

/*
 * take the value at *pVxCpuIndex and shift to get the vxKernelVar index
 * 0,128,256 ...
 */

#define _SIMIA_CPU_INDEX_GET(regSuffix)				\
    movl	VAR(pVxCpuIndex),%REG32_r##regSuffix;	\
    movl	(%REG32_r##regSuffix),%REG32_r##regSuffix;\
    rol		$_WRS_WIND_VARS_ALIGN_SHIFT,%REG32_r##regSuffix;

#define _WRS_LOAD_REG_WITH_VAR_BASE(label,reg)         		\
    leal	FUNC(vxKernelVars),%REG32_r##reg;		\
    addl	$_WRS_WIND_VARS_OFFSET_##label,%REG32_r##reg;

#define _SIMIA_PER_CPU_ADRS_GET(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    addl	%REG32_r##scratch,%REG32_r##regSuffix;

#define _SIMIA_PER_CPU_VALUE32_GET(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    addl	%REG32_r##regSuffix,%REG32_r##scratch;		\
    movl	0x0(%REG32_r##scratch),%REG32_r##regSuffix;

#define _SIMIA_PER_CPU_VALUE32_INC(regSuffix,scratch,label)	\
    _SIMIA_CPU_INDEX_GET(regSuffix)				\
    _WRS_LOAD_REG_WITH_VAR_BASE(label,scratch)			\
    addl	%REG32_r##regSuffix,%REG32_r##scratch;		\
    movl	0x0(%REG32_r##scratch),%REG32_r##regSuffix;	\
    incl	%REG32_r##regSuffix;				\
    movl	%REG32_r##regSuffix,0x0(%REG32_r##scratch);
#endif /* _WRS_CONFIG_LP64 */

#endif /* _ASMLANGUAGE */

#else /* _WRS_CONFIG_SMP */
	
#define _WRS_CPU_INDEX_GET()	0

/* macro to access the arch-specific fields */

#define _WRS_WIND_VARS_ARCH_ACCESS(glob)		\
    _WRS_KERNEL_GLOBAL_ACCESS (glob)

#define _WRS_WIND_VARS_ARCH_SET(ignored,glob,var)	\
    _WRS_KERNEL_CPU_GLOBAL_SET(ignored,glob,var)

#define _WRS_WIND_VARS_ARCH_LOCKED_GET(glob,var)	\
    _WRS_KERNEL_LOCKED_GLOBAL_GET (glob,var)

#ifdef _ASMLANGUAGE

#ifdef _WRS_CONFIG_LP64
#define _SIMIA_PER_CPU_ADRS_GET(regSuffix,scratch,label)	\
    movabsq	$FUNC(label),%r##regSuffix;

#define _SIMIA_PER_CPU_VALUE32_GET(regSuffix,scratch,label)	\
    movabsq	$FUNC(label),%r##regSuffix;			\
    movl	(%r##regSuffix),%REG32_r##regSuffix;

#define _SIMIA_PER_CPU_VALUE64_GET(regSuffix,scratch,label)	\
    movabsq	$FUNC(label),%r##regSuffix;			\
    mov		(%r##regSuffix),%r##regSuffix

#define _SIMIA_PER_CPU_VALUE32_INC(regSuffix,scratch,label)	\
    movabsq	$FUNC(label),%r##scratch;			\
    movl	(%r##scratch),%REG32_r##regSuffix;		\
    incl	%REG32_r##regSuffix;				\
    movl	%REG32_r##regSuffix,(%r##scratch);
#else /* _WRS_CONFIG_LP64 */

#define _SIMIA_PER_CPU_ADRS_GET(regSuffix,scratch,label)	\
    leal FUNC(label),%REG32_r##regSuffix;

#define _SIMIA_PER_CPU_VALUE32_GET(regSuffix,scratch,label)	\
    movl FUNC(label),%REG32_r##regSuffix;

#define _SIMIA_PER_CPU_VALUE32_INC(regSuffix,scratch,label)	\
    incl FUNC(label);				\
    movl FUNC(label),%REG32_r##regSuffix;
#endif /* _WRS_CONFIG_LP64 */

#endif /* _ASMLANGUAGE */

#endif  /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif


#endif	/* __INCsmpSimntPh */
