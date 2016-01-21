/* archArm.h - ARM specific header */

/*
 * Copyright (c) 1996, 1998, 1999, 2001, 2003-2011, 2013 
 *                   Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02t,01jun13,yjw  update for ARMARCH7M
02s,12aug11,jb   WIND00238999 Limit Device Power Mgmt to ARMARCH7
02r,17nov10,dbr  define _WRS_ARCH_HAS_DEV_PWR_MGMT for device power management
02q,16sep10,gls  added VX_OBJ_ALIGN_SIZE
02p,29jul10,pad  Moved extern C statement after include statements.
02o,27aug10,rlp  Added _WRS_ARCH_HAS_VXDBG_BP_ADDR_CHECK macro.
02n,24aug10,jdw  Fix _WRS_REV_INSN_SET_CHANGE for Thumb2
02m,09jun10,m_h  Thumb-2 Support
02l,10mar10,j_b  define _WRS_PHYS_ADDR_IS_64_BITS for XScale, ARMv6+
                 (WIND00129408)
02k,20oct09,z_l  add SMP support for ARMARCH7
02j,25feb09,j_b  merge ARM SMP support, incl adding VSB header file:
                 22feb08,j_b  replace intUnlock with intCpuUnlock
                 12nov07,jmp  Define _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT
                 02nov07,jb   Add coherency flag for SMP and build exclusions
                 10oct07,j_b  define _WRS_ARCH_HAS_DBG_IPI
02i,27feb09,m_h  ARMARCH7 Support
02h,31jul08,tcr  change macro for compatibility
02g,19may08,tcr  update SV instrumentation
02f,16aug07,j_b  added _WRS_MMU_HAS_MAP_STATE_API
02e,08jun07,j_b  Add definition for _WRS_VX_NO_GLOBAL_ERRNO
02d,21may07,j_b  define _WRS_ARCH_HAS_IDLE_TASK, VX_MAX_SMP_CPUS
02c,04may07,zl   updated portable library build configuration,
                 added _WRS_CPU_HAS_CLZ_INSTR.
02b,21feb07,jmg  Added include vxPortableP.h
02a,11dec06,kk   removed references to _WRS_BASE6_SCHEDULER, no longer needed
01z,21jun06,jb   Re-enable fast ffs for arch5, make ARMARCH6 64 bit PHYS_ADDR
01y,02mar06,jb   Fix for SPR 118321 - vfp references in 920t
01x,01feb06,jb   Adding VFP Support
01w,12jan06,jb   Enabling 920t variant support
01v,10jan06,hya  Add ARM CPU variant code for FFS(x) (WRN)
01u,19dec05,jb   Changing XSCALE to 64 bit PHYS_ADDR
01t,24aug05,h_k  Added _WRS_SUPPORT_CACHE_XLATE.
01s,12apr05,kk   remove _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
01r,28mar05,scm  add _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
01q,18feb05,dbt  Moved some loader specific macros to elfArm.h.
01p,17feb05,scm  add _WRS_OSM_INIT definition, and clarify
                 PORTABLE/NON-PORTABLE inclussion
01o,17jan05,jb   Adding architecture specific objVerify support
01n,08sep04,scm  move INSTR to archArmCommon.h
01m,10aug04,scm  undef "OPTIMIZE", define "PORTABLE"...
01l,27apr04,cjj  Defined workQLib_PORTABLE
01k,01dec03,scm  clean up, SPR #90358... remove obnoxious warning...
01j,25nov03,pes  Move setting of _BYTE_ORDER macro into archArmCommon.h
01i,14nov03,job  Moved some blib stuff to archArmCommon.h
01h,13nov03,pes  Add include of archArmCommon.h
01h,29oct03,sn   gcc 3.3.2 does not currently support arm or sh
01g,27aug03,to   added defines for semLib.
01f,07may03,pes  PAL conditional compilation cleanup. Phase 2.
01e,29apr03,pes  PAL conditional compilation cleanup.
01d,13mar01,sn   SPR 73723 - define supported toolchains
01c,20jan99,cdp  removed support for old ARM libraries.
01b,17aug98,cdp  added big-endian and multiple cachelib support.
01a,08may96,cdp  written based on archI86.h
*/

#ifndef __INCarchArmh
#define __INCarchArmh

#include <vsbConfig.h>

/* In the cases where vxWorks.h is not defined first... */

#if !defined (TRUE)
#define TRUE 1
#endif

#if !defined (FALSE)
#define FALSE 0
#endif

#undef  _ARCH_SUPPORTS_GCC
#define _ARCH_SUPPORTS_DCC

/* define to indicate ARM supports device power management */

#if (CPU==ARMARCH7) || (CPU==ARMARCH7_T2)
#define _WRS_ARCH_HAS_DEV_PWR_MGMT
#endif /* (CPU==ARMARCH7) || (CPU==ARMARCH7_T2) */

/* temporary macro to indicate ARM uses the idle task stack */

#define _WRS_ARCH_HAS_IDLE_TASK

/* temporary define to indicate ARM uses task-specific errnos */

#define _WRS_VX_NO_GLOBAL_ERRNO

/* temporary define to indicate ARM supports MMU state info with map request */

#define _WRS_MMU_HAS_MAP_STATE_API

/* temporary macro to indicate ARM has Debug IPI */

#define _WRS_ARCH_HAS_DBG_IPI

/* indicates that ARM has VxDBG CPU control support */

#define _WRS_ARCH_HAS_VXDBG_CPU_CTRL_SUPPORT

/*
 * Indicate that the ARM architecture has the VxDBG support to check the
 * alignment of the breakpoint address.
 */

#define	_WRS_ARCH_HAS_VXDBG_BP_ADDR_CHECK

#undef VX_MAX_SMP_CPUS
#define VX_MAX_SMP_CPUS 4  /* maximum processors in SMP configuration */

/*
 * For SMP, any shared data region that is created from the RAM need
 * to be memory coherent. 
 * So we need to set the page attribute to MMU_ATTR_CACHE_COHERENCY.
 * The arches, need to specify this via the macro 
 * VM_DEFAULT_CACHE_COHERENCY_ATTR
 */

#ifdef _WRS_CONFIG_SMP

    /* Limit SMP build to ARMARCH6 and ARMARCH7 little endian */

#if ((CPU == ARMARCH6) || (CPU == ARMARCH7)) && !defined(ARMEB) && !defined(__ARMEB__)
#define VM_DEFAULT_CACHE_COHERENCY_ATTR MMU_ATTR_CACHE_COHERENCY
#else
#error SMP build is NOT supported by this architecture/tool combination
#endif /* (CPU == ARMARCH6) && !defined(ARMEB) && !defined(__ARMEB__) */

#endif /* _WRS_CONFIG_SMP */

#define _DYNAMIC_BUS_SIZING FALSE  /* require alignment for swap */

#define _ARCH_MULTIPLE_CACHELIB TRUE  /* multiple cache libraries */

/* macros for AIM Cache */

#define _WRS_SUPPORT_CACHE_XLATE  /* cache virt-phys translate */

#if !defined(ARMCPU920T)

/* Say VFP is Supported */

#define _WRS_HW_VFP_SUPPORT

#endif /* !defined(ARMCPU920T) */

#ifdef __cplusplus
extern "C" {
#endif

#if ((CPU == XSCALE) || (CPU == ARMARCH6) || (CPU == ARMARCH7) \
     || (CPU == ARMARCH7_T2))

/* physical addresses are represented with 64 bits for these CPUs */

#define _TYPE_PHYS_ADDR           typedef UINT64 PHYS_ADDR
#define _WRS_PHYS_ADDR_IS_64_BITS
#endif /* ((CPU == XSCALE, ARMARCH6, ARMARCH7,  ARMARCH7_T2)) */

#ifdef __cplusplus
}
#endif

#include "arm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PAL additions */

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 */

#define VX_OBJ_ALIGN_SIZE       8               /* 8-byte alignment */

/* moved here from h/private/eventP.h */

/*
 * (Borrowed from PPC.)
 *
 * Macro for event logging of intEnt events for ARM architectures.
 * The ARM architecture is different in that there is only one external
 * interrupt line coming into the CPU. At the time of the intEnt, the
 * external interrupt number is unknown, meaning that logging cannot
 * take place at this time. In this architecture, the logging of an
 * intEnt event is deferred until the interrupt controller driver
 * is executed.
 * Since the logging has to take place in drivers and/or BSP world files,
 * the details of how the logging to be done has been deferred to a macro 
 * which is defined here.
 *
 * Note: This replaces the previous technique of saving the timestamp
 * during the intEnt code to be used later, when the logging was done.
 * SPR 21868 refers to a problem in which this can give rise to out-of-order
 * timestamps in the event log.
 */

#define WV_EVT_INT_ENT(intNum)	    EVT_CTX_1(EVENT_INT_ENTER, intNum);

/* moved here from h/private/classLibP.h */

#define OBJ_CLASS_initRtn	0x24	/* Offsets into OBJ_CLASS */

/* status codes */

#define S_vmLib_NO_FREE_REGIONS			(M_vmLib | 6)
#define S_vmLib_ADDRS_NOT_EQUAL			(M_vmLib | 7)

/* from dbgLib.c */

#define _WRS_FRAME_PRINT_STRING	"                   : "

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from periodHost.c, repeatHost.c, shell.c, and taskLib.c */

#if (ARM_THUMB) || (ARM_THUMB2)
#define _WRS_CHANGE_INSN_SET_ENABLE
#define _WRS_CHANGE_INSN_SET(p)	(p) = ((FUNCPTR)(((UINT32)(p))|1))
#define _WRS_CHANGE_INSN_SET_PTR(p)	((FUNCPTR)(((UINT32)(p))|1))
#define _WRS_REV_INSN_SET_CHANGE(p)	((FUNCPTR)(((UINT32)(p)) & ~1))
#endif /* ARM_THUMB || (ARM_THUMB2) */

/* OSM support for stack protection, used in sysOsmLib.c */

#define _WRS_OSM_INIT

/* Interrupt stack protection, used in usrDepend.c and usrKernelStack.c */

#define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK

/* 
 * if OSM support not available for stack protection,
 * then support can not be available for interrupt
 * stack protection.
 */

#if !defined(_WRS_OSM_INIT)
#undef _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
#endif

#if defined(_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK)
#undef _WRS_SVC_INT_STACK
#undef _WRS_IRQ_INT_STACK
#undef _WRS_DUAL_INT_STACK
#undef _WRS_SPLIT_STACKS
#else

/*
 * Old split interrupt stack method...,
 * not used when OSM stack protection is
 * enabled...
 */

/* from usrLib.c */
                                                                                    
#define _WRS_SVC_INT_STACK
#define _WRS_IRQ_INT_STACK
#define _WRS_DUAL_INT_STACK
                                                                                    
/* from kernelLib.c */

    /*
     * The ARM family uses 3 interrupt stacks. The ratio of the sizes of
     * these stacks is dependent on the interrupt structure of the board
     * and so is handled in the BSP code. Note that FIQ is now external to
     * VxWorks.
     */

#define _WRS_SPLIT_STACKS    {if (_func_armIntStackSplit != NULL) \
	        (_func_armIntStackSplit)(vxIntStackBase, intStackSize);}
#endif  /* _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

/* from xdr_float.c */

#define FLOAT_NORM

/* Set to force the use of the big-endian call to XDR_GETLONG() */

#define _WRS_XDR_FORCE_BE

#define _WRS_ENABLE_IDLE_INTS	{intCpuUnlock(0);}

/* macros for getting frame and return PC from a jmp_buf */

#define _WRS_FRAMEP_FROM_JMP_BUF(env)   ((char *) (env)[0].reg.reg_sp)
#define _WRS_RET_PC_FROM_JMP_BUF(env)   ((INSTR *) (env)[0].reg.reg_pc)

#ifdef __cplusplus
}
#endif

#include <arch/arm/archArmCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* variants that support the clz instruction, "count leading zeroes" */

#if ((CPU == XSCALE) || (CPU == ARMARCH6) || (CPU == ARMARCH5) \
       || (CPU == ARMARCH7) || (CPU == ARMARCH7_T2) || (CPU == ARMARCH7M))
#define _WRS_CPU_HAS_CLZ_INSTR
#endif /* CPU = XSCALE ... ARMARCH7_T2 */

#ifndef _ASMLANGUAGE

#ifdef _WRS_CPU_HAS_CLZ_INSTR

/* optimize FFS(x) in network code for CPUs supporting clz instruction */

#undef FFS
#define FFS(x) (31 - _countLeadingZeroes(x))

#if defined (__GNUC__)

/*
 * Return the number of zero bits in bit positions more significant
 * than the first set bit.
 * We don't have to handle the x=0 case, this is only called
 * when x != 0. Returns a value y in the range 31 >= y >= 0.
 * 0 indicates the most significant bit.
 */

static __inline__ unsigned int _countLeadingZeroes
    (
    unsigned int x
    )
    {
    unsigned int y;

    __asm__ ("clz %0, %1"
	     : "=r" (y)
	     : "r" (x)
	    );

    return y;
    }
#elif defined (_DIAB_TOOL)

#pragma pure_function _countLeadingZeroes

__asm unsigned int _countLeadingZeroes
    (
    unsigned int x
    )
{
% reg x
! "r0"
	clz  r0, x
}

#else  /* !_DIAB_TOOL */

/* Unknown compiler, use default */

#undef FFS
#define FFS(x) (ffsMsb(x) - 1)

#endif /* _DIAB_TOOL */

#else /* _WRS_CPU_HAS_CLZ_INSTR */

/* use default */

#undef FFS
#define FFS(x) (ffsMsb(x) - 1)

#endif /* _WRS_CPU_HAS_CLZ_INSTR */
#endif /* ! _ASMLANGUAGE */

/* End PAL */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchArmh */
