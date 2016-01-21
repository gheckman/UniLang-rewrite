/* archSimsolaris.h - simsparc specific header */

/* 
 * Copyright (c) 1995-2008,2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02p,27oct10,zl   defined _WRS_ARCH_DEFERS_KERNEL_UNLOCK (WIND00227404 
                 and WIND00232955).
02o,16sep10,gls  added VX_OBJ_ALIGN_SIZE
02n,28may10,elp  replaced ULONG by VXSIM_ULONG.
02m,26may10,dbt  Fixed idle mode if no power management is enabled.
02l,29apr10,pad  Moved extern C statement after include statements.
02k,01apr10,elp  added new MMU support macros.
02j,13mar08,rlp  Removed obsolete _WRS_ARCH_HAS_DBG_IPI macro.
02i,09jul07,mmi  added _WRS_ARCH_HAS_CPU_PWR_MGMT
02h,14may07,elp  added _WRS_MMU_HAS_MAP_STATE_API
02g,04may07,zl   updated portable library build configuration.
02f,25apr07,kk   move VX_MAX_SMP_CPUS to here
02e,05apr07,rlp  Added _WRS_ARCH_HAS_DBG_IPI macro.
02d,21feb07,jmg  Added include vxPortableP.h
02c,13dec06,kk   removed references to _WRS_BASE6_SCHEDULER and
                 _WRS_ARCH_HAS_RESCHEDULE_STACK, no longer needed
02b,05dec06,elp  removed _WRS_HAS_RESCHEDULE_STACK.
02a,25nov06,dbt  Added _WRS_ARCH_HAS_IDLE_TASK, _WRS_VX_NO_GLOBAL_ERRNO &
		 _WRS_ARCH_HAS_IDLE_TASK.
01z,08nov06,elp  added _WRS_HAS_RESCHEDULE_STACK, _WRS_VX_NO_GLOBAL_ERRNO.
01y,12apr05,kk   remove _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
01x,31mar05,elp  added _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK macro
01w,27aug04,dbt  Added _WRS_OBJLIB_SUPPORT_VERIFY_TRAP.
01v,17may04,tam  removed _WRS_KERNEL_TEXT_START_ADRS definition
01u,14may04,jmp  removed upsolete stuff.
01t,22apr04,jmp  added macros for getting frame and return PC from a jmp_buf.
01s,25feb04,aeg  moved _WRS_PAL_COPROC_LIB to archSimsolarisCommon.h
01r,22jan04,dbt  Added support for GNU compiler.
01q,02dec03,dbt  Updated power management support.
01p,14nov03,job  Moved blib stuff to archSimsolarisCommon.h
01o,13nov03,pes  Add include of common header file.
01n,23sep03,dbt  Use new B6 scheduler.
01m,18aug03,dbt  Added PAL spuport for VxSim.
01l,22jul03,kam  removed define of WV_INSTRUMENTATION
01k,19jun03,dbt  Added support for DCC.
01j,31may01,jmp  removed _WRS_NO_EXC_STACK_USED definition.
		 Added _WRS_ARCH_IS_SIMULATOR.
		 Added define for PAL-ified cache library.
01i,12feb01,hbh  Removed _WRS_NO_OVERLAPPING_MODEL and NO_SL_DATA_SUPPORT
                 flags definition (SPR 64073)
01h,26may00,rlp  added _WRS_NO_EXC_STACK_USED macro.
01g,19apr00,hbh  Added _WRS_NO_OVERLAPPING_MODEL macro.
01f,17apr00,cjj  defined NO_SL_DATA_SUPPORT
01e,13apr00,hbh  added WV_INSTRUMENTATION
01d,23dec99,cjj  removed WV_INSTRUMENTATION for T3 development.
01c,29jul98,ms   added WV_INSTRUMENTATION
01b,16dec96,yp   va_start now passes LASTARG to builtin_next_arg
01a,07jun95,ism  derived from simsparc
*/

#ifndef __INCarchSimsolarish
#define __INCarchSimsolarish

#define	_ALLOC_ALIGN_SIZE	8		/* 8-byte alignment */
#define _STACK_ALIGN_SIZE	8		/* 8-byte alignment */

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 */

#define VX_OBJ_ALIGN_SIZE	8		/* 8-byte alignment */

#define _DYNAMIC_BUS_SIZING	FALSE		/* no dynamic bus sizing */

#define _WRS_ARCH_IS_SIMULATOR	/* This is a simulator */
#define _WRS_VX_NO_GLOBAL_ERRNO	/* no longer save errno on ctx switch */

#define _ARCH_SUPPORTS_DCC	/* DCC compiler is supported on this arch. */
#define _ARCH_SUPPORTS_GCC	/* GCC compiler is supported on this arch. */

/* XXX SMP step macros */

#define _WRS_ARCH_HAS_IDLE_TASK		
#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK 
#define _WRS_ARCH_SUPPORTS_VX_CPU_STATE_INIT
#define _WRS_MMU_HAS_MAP_STATE_API

/* specify that arch supports cpu power management framework */

#define _WRS_ARCH_HAS_CPU_PWR_MGMT

/* Used in usrDepend.c and usrKernelStack.c */

#define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK

/* moved here from h/private/javaLibP.h */

#define JAVA_C_SYM_PREFIX	""

#ifndef _ASMLANGUAGE
/* macros for getting frame and return PC from a jmp_buf */

#define _WRS_FRAMEP_FROM_JMP_BUF(env)	((char *)  (env)[0].reg.reg_sp)
#define _WRS_RET_PC_FROM_JMP_BUF(env)	((INSTR *) (env)[0].reg.reg_pc)

#endif 	/* _ASMLANGUAGE */

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from xdr_float.c */

#define FLOAT_NORM

/* from schedLib.c */

#define _WRS_VXLIB_SUPPORT

/* defer kernel unlock to windLoadContext() */

#define _WRS_ARCH_DEFERS_KERNEL_UNLOCK

/*
 * There is no need to unlock interrupts in Solaris VxSim in order to enter
 * idle mode unless power management is not enabled.
 */

#define _WRS_ENABLE_IDLE_INTS \
	if (_func_cpuPwrIdleEnter == NULL) intCpuUnlock (0)

#undef  VX_MAX_SMP_CPUS
#define VX_MAX_SMP_CPUS 32       /* maximum processors in SMP configuration */

/* from spyLib.c */

#define _WRS_SPY_TASK_SIZE      10000

/* arch support new MMU APIs */

#define _WRS_MMU_HAS_MAP_STATE_API
#define _WRS_MMU_HAS_SPL_TRANSLATE_API
#define _WRS_MMU_HAS_BLOCK_INFO_API

/* End PAL */

#ifndef _ASMLANGUAGE
typedef unsigned long   VXSIM_ULONG;
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#include <arch/simsolaris/archSimsolarisCommon.h>

#endif /* __INCarchSimsolarish */
