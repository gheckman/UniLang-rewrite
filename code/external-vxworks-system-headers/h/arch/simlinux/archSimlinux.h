/* archSimnt.h - i86 VxSim specific header */

/* 
 * Copyright (c) 1997-2008,2010-2011 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02q,07feb11,rlp  Enabled system mode agent for LP64.
02p,27oct10,zl   defined _WRS_ARCH_DEFERS_KERNEL_UNLOCK (WIND00227404 
                 and WIND00232955).
02o,16sep10,gls  added VX_OBJ_ALIGN_SIZE
02n,13sep10,elp  fixed STACK_ALIGN_SIZE.
02m,29jul10,pad  Moved extern C statement after include statements.
02m,26may10,dbt  Fixed idle mode if no power management is enabled.
02l,01feb10,elp  64 bits support: added _WRS_MMU_HAS_BLOCK_INFO_API.
02k,27aug08,jpb  Renamed VSB header file
02j,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02i,13mar08,rlp  Removed obsolete _WRS_ARCH_HAS_DBG_IPI macro.
02h,15aug07,mmi  add _WRS_ARCH_HAS_CPU_PWR_MGMT
02g,14may07,elp  added _WRS_MMU_HAS_MAP_STATE_API
02f,04may07,zl   updated portable library build configuration.
02e,25apr07,kk   move VX_MAX_SMP_CPUS to here
02d,05apr07,rlp  Added _WRS_ARCH_HAS_DBG_IPI macro.
02c,07mar07,jmg  Added include for vxPortableP.h
02b,14feb07,elp  added SIMNT SMP support.
02a,13dec06,kk   removed references to _WRS_BASE6_SCHEDULER and
                 _WRS_ARCH_HAS_RESCHEDULE_STACK, no longer needed
01z,08dec06,elp  removed _WRS_HAS_RESCHEDULE_STACK.
01y,27jul06,elp  Added WRS_ARCH_HAS_RESCHEDULE_STACK, _WRS_VX_NO_GLOBAL_ERRNO.
01x,12apr05,kk   removed _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
01w,31mar05,elp  added _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK macro
01v,27aug04,dbt  Added _WRS_OBJLIB_SUPPORT_VERIFY_TRAP.
01u,18may04,tam  removed _WRS_KERNEL_TEXT_START_ADRS definition
01t,18may04,jmp  fixed _WRS_FRAMEP_FROM_JMP_BUF macro.
01s,15may04,zl   fixed _WRS_FRAMEP_FROM_JMP_BUF()
01r,14may04,jmp  removed obsolete stuff.
01q,23mar04,jmp  added support for portable trcLib.
		 added macros for getting frame and return PC from a jmp_buf.
01p,09feb04,aeg  moved _WRS_PAL_COPROC_LIB to archSimntCommon.h
01o,04dec03,dbt  Added support for DIAB compiler.
01n,02dec03,dbt  Updated power management support.
01m,25nov03,pes  Move definition of _BYTE_ORDER to arch<Arch>Common.h.
01l,14nov03,job  Moved blib stuff to archSimntCommon.h
01k,13nov03,pes  Add include of common header
01j,23sep03,dbt  Use new B6 scheduler.
01i,18aug03,dbt  Added PAL support for VxSim.
01h,22jul03,kam  removed define of WV_INSTRUMENTATION
01g,28may03,jmp  removed X86_EXT structure.
01f,22apr03,dbt  Added _WRS_ARCH_IS_SIMULATOR definition.
01e,27mar03,jmp  added X86_EXT. no longer include ntcontext.h
01d,13mar01,sn   SPR 73723 - define supported toolchains
01c,21sep01,jmp  only include ntcontext.h if _ASMLANGUAGE not defined
		 (SPR# 34669).
01b,29jul98,ms   added WV_INSTRUMENTATION
01a,03sep97,cym  written
*/

#ifndef __INCarchSimnth
#define __INCarchSimnth

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif
	
/* Begin PAL */

#define	_ALLOC_ALIGN_SIZE	8		/* 8-byte alignment */
#ifdef _WRS_CONFIG_LP64
/* 16-bytes alignment for sse and sse2 instructions */

#define _STACK_ALIGN_SIZE   	16		
#else
#define _STACK_ALIGN_SIZE	8		/* 8-byte alignment */
#endif /* _WRS_CONFIG_LP64 */

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 */

#define VX_OBJ_ALIGN_SIZE	8		/* 8-byte alignment */

#define _DYNAMIC_BUS_SIZING	FALSE		/* no dynamic bus sizing */

#ifdef _WRS_CONFIG_LP64
/* 64-bit Virt and Physical addresses */

#define _WRS_PHYS_ADDR_IS_64_BITS
#define _TYPE_PHYS_ADDR			typedef unsigned long PHYS_ADDR
#define _TYPE_VX_PHYS_ADDR		typedef unsigned long _Vx_PHYS_ADDR

#endif /* _WRS_CONFIG_LP64 */

#define _WRS_ARCH_IS_SIMULATOR		/* This is a simulator */
#define _WRS_VX_NO_GLOBAL_ERRNO		/* no longer save errno on ctx switch */

#define _WRS_ARCH_HAS_IDLE_TASK		
#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK 
#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT

/* defer kernel unlock to windLoadContext() */

#define _WRS_ARCH_DEFERS_KERNEL_UNLOCK

/* specify that arch supports cpu power management framework */

#define _WRS_ARCH_HAS_CPU_PWR_MGMT

#define _ARCH_SUPPORTS_GCC	/* GCC compiler is supported on this arch. */
#define _ARCH_SUPPORTS_DCC	/* DCC compiler is supported on this arch. */

/* Used in usrDepend.c and usrKernelStack.c */

#define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK

/* moved here from h/private/javaLibP.h */

#define JAVA_C_SYM_PREFIX	""

#ifndef _ASMLANGUAGE
/* macros for getting frame and return PC from a jmp_buf */

#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *) (env)[0].reg.reg_fp)
#define _WRS_RET_PC_FROM_JMP_BUF(env)	((INSTR *) (env)[0].reg.reg_pc)
#endif 	/* _ASMLANGUAGE */

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from xdr_float.c */

#define FLOAT_NORM

/* from schedLib.c */

#define _WRS_VXLIB_SUPPORT

#ifdef _WRS_CONFIG_SMP 
#define _WRS_ENABLE_IDLE_INTS	intCpuUnlock (0)
#else
/*
 * There is no need to unlock interrupts in UP VxSim in order to enter
 * idle mode unless power management is not enabled.
 */

#define _WRS_ENABLE_IDLE_INTS	\
	if (_func_cpuPwrIdleEnter == NULL) intCpuUnlock (0)
#endif /* _WRS_CONFIG_SMP */

#undef VX_MAX_SMP_CPUS
#define VX_MAX_SMP_CPUS 32       /* maximum processors in SMP configuration */

/* from spyLib.c */

#define _WRS_SPY_TASK_SIZE      10000

/* arch support new MMU APIs */

#define _WRS_MMU_HAS_MAP_STATE_API
#define _WRS_MMU_HAS_SPL_TRANSLATE_API
#define _WRS_MMU_HAS_BLOCK_INFO_API

/* End PAL */

#ifdef __cplusplus
}
#endif

#if (CPU==SIMLINUX)
#include "arch/simlinux/archSimlinuxCommon.h"
#elif (CPU==SIMNT)
#include "arch/simnt/archSimntCommon.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Since on host side ULONG is always a 32 bits on Windows, we use VXSIM_ULONG
 * instead. VXSIM_ULONG follows ILP32 and LP64 models
 */

#ifndef _ASMLANGUAGE
typedef unsigned long 	VXSIM_ULONG;
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchSimnth */
