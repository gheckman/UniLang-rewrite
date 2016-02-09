/* archX86_64.h - Intel x86_64 specific header */

/* 
 * Copyright (c) 2009-2011, 2013 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01t,20jun13,scm  WIND00420874 - correct workQAdd indexing for more than 8
                 core...
01s,14aug11,j_l  Move _WRS_ARCH_HAS_CPU_PWR_MGMT outside of power management
                 ifdef.
01r,12aug11,rbc  WIND00238999 - Fix conditional for CPU==NEHALEM
01q,11aug11,rbc  WIND00238999 - Fix build errors
01p,09aug11,rbc  WIND00238999 - Fix build error for windPwrDown()
01o,18may11,jb   Requirement WIND00189850 - Increase VX_MAX_SMP_CPUS for HT/SMT support
01n,07feb11,rlp  Enabled system mode agent for LP64.
01m,24nov10,kk  Change _ALLOC_ALIGN_SIZE to 16
01l,28oct10,zl   defined _WRS_ARCH_DEFERS_KERNEL_UNLOCK and
                 _WRS_ARCH_HAS_TASK_MMU_CURRENT_SET
01k,16sep10,gls  added VX_OBJ_ALIGN_SIZE
01j,29jul10,pad  Moved extern C statement after include statements.
01i,12mar10,zl   added _WRS_ARCH_USES_DIRECT_MAP_REGION
01i,26feb10,rlp  Added _WRS_ARCH_NO_SYSTEM_MODE_AGENT macro to disable WDB
                 system mode agent.
01h,10sep09,jb   Add flag for _WRS_MMU_HAS_OPTIMIZATION_INFO_API
01g,31jul09,jb   Adding defines for 64-bit MMU
01f,09jun09,cww  Added _WRS_PAL_COPROC_LIB
01e,20may09,jb   Change to kernel model
01d,08may09,jb   Make pusha/popa interrupt safe
01c,25feb09,jb   Adding 64-bit shortcut - may be moved
01b,12feb09,jb   Fix reference to vxbConfig
01a,20jan09,jb   Derived from 32-bit version 02p
*/

#ifndef __INCarchX86_64h
#define __INCarchX86_64h

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_ARCH_KERNEL_MODEL       /* compiler uses mcmodel=kernel */

#define _ARCH_SUPPORTS_GCC

/* temporary macro to indicate i86 uses the idle task stack */

#define _WRS_ARCH_HAS_IDLE_TASK

/* temporary macro to indicate i86 uses the type II kernel lock */

#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK

#define _WRS_VX_NO_GLOBAL_ERRNO

/* arch supports new MMU APIs... */

#define _WRS_MMU_HAS_MAP_STATE_API
#define _WRS_MMU_HAS_SPL_TRANSLATE_API
#define _WRS_MMU_HAS_BLOCK_INFO_API
#define _WRS_MMU_HAS_OPTIMIZATION_INFO_API

/* arch has 64-bit mmu attributes */

#define _WRS_MMU_HAS_64BIT_ARCH_ATTR

/* this arch uses direct map region */

#define _WRS_ARCH_USES_DIRECT_MAP_REGION

/* this cpu family supports power management framework */

#define _WRS_ARCH_HAS_CPU_PWR_MGMT

#if (CPU==_VX_NEHALEM) || defined(_WRS_CONFIG_WRHV_GUEST)

#define _WRS_ARCH_HAS_WIND_PWR_DOWN
#define WIND_PWR_DOWN() windPwrDown()

/* support for device power management */

#if !defined(_WRS_CONFIG_WRHV_GUEST)
#define _WRS_ARCH_HAS_DEV_PWR_MGMT
#endif /* !defined(_WRS_CONFIG_WRHV_GUEST) */

#endif /* (CPU==_VX_NEHALEM) || defined(_WRS_CONFIG_WRHV_GUEST) */

#define _WRS_PAL_COPROC_LIB        /* enable coprocessor abstraction */ 

/* arch needs deferred kernel unlock */

#define _WRS_ARCH_DEFERS_KERNEL_UNLOCK

/* arch provides taskMmuCurrentSet() */

#define _WRS_ARCH_HAS_TASK_MMU_CURRENT_SET

/* 64-bit Virt and Physical addresses */
#define _WRS_PHYS_ADDR_IS_64_BITS
#define _TYPE_PHYS_ADDR      typedef unsigned long PHYS_ADDR
#define _TYPE_VX_PHYS_ADDR   typedef unsigned long _Vx_PHYS_ADDR

#undef VX_MAX_SMP_CPUS
#if  CPU==_VX_CORE
#define VX_MAX_SMP_CPUS     16   /* maximum processors in SMP configuration */
#define VX_MAX_SMP_CPU_SHIFT 4   /* allow workQ to calculate with Max CPUs  */
#else
#define VX_MAX_SMP_CPUS     32   /* maximum processors in SMP configuration */
#define VX_MAX_SMP_CPU_SHIFT 5   /* allow workQ to calculate with Max CPUs  */
#endif /* CPU==_VX_CORE */


#define	_DYNAMIC_BUS_SIZING	FALSE		/* require alignment for swap */

#define _STACK_ALIGN_SIZE   16 /* required stack alignment for sse and sse2 instructions */
#define _ALLOC_ALIGN_SIZE   16

/*
 * VX_OBJ_ALIGN_SIZE is the default allocation boundary for kernel objects.  
 * This is used for both statically and dynamically allocated objects.
 *
 * NOTE:
 *
 * For the INTEL architecture VxWorks objects must be aligned to a 64-bit
 * boundary for ILP32 and a 128-bit boundary for LP64.  This is to allow
 * the objVerifiedSafe() routine to be implemented using an atomic CAS of
 * the 'safe' count and 'magic' value in an object handle.
 */

#define VX_OBJ_ALIGN_SIZE   16

#define _CACHE_ALIGN_SIZE	64
#ifdef	_ASMLANGUAGE

/* 
 * system startup macros used by sysInit(sysALib.s) and romInit(romInnit.s).
 * - no function calls to outside of BSP is allowed.
 * - no references to the data segment is allowed.
 * the CR4 is introduced in the Pentium processor.
 */

#define ARCH_REGS_INIT							\
	xorq	%rax, %rax;		/* zero EAX */			\
	movq    %cr0, %rdx;		/* get CR0 */			\
	andq    $0x7ffafff1, %rdx;	/* clear PG, AM, WP, TS, EM, MP */ \
	movq    %rdx, %cr0;		/* set CR0 */			\
									\
	pushq	%rax;			/* initialize EFLAGS */		\
	popfl;

#define ARCH_CR4_INIT							\
	xor	%rax, %rax;		/* zero EAX */			\
	movq	%eax, %cr4;		/* initialize CR4 */

#define pushal \
        subq    $0x80, %rsp;          /* move stack pointer */\
        mov     %rax, REG_RAX(%rsp);  /* push rax */          \
        mov     %rcx, REG_RCX(%rsp);  /* push rcx */          \
        mov     %rdx, REG_RDX(%rsp);  /* push rdx */          \
        mov     %rbx, REG_RBX(%rsp);  /* push rbx */          \
        mov     %rbp, REG_RBP(%rsp);  /* push rbp */          \
        mov     %rsi, REG_RSI(%rsp);  /* push rsi */          \
        mov     %rdi, REG_RDI(%rsp);  /* push rdi */          \
        mov     %r8, REG_R8(%rsp);    /* push r8 */           \
        mov     %r9, REG_R9(%rsp);    /* push r9 */           \
        mov     %r10, REG_R10(%rsp);  /* push r10 */          \
        mov     %r11, REG_R11(%rsp);  /* push r11 */          \
        mov     %r12, REG_R12(%rsp);  /* push r12 */          \
        mov     %r13, REG_R13(%rsp);  /* push r13 */          \
        mov     %r14, REG_R14(%rsp);  /* push r14 */          \
        mov     %r15, REG_R15(%rsp);  /* push r15 */          \
        mov     %rsp, REG_RSP(%rsp);  /* push rsp */          \
        addq    $0x80, REG_RSP(%rsp); /* Adjust rsp */

#define popal \
        mov     REG_RAX(%rsp), %rax;  /* pop rax */           \
        mov     REG_RCX(%rsp), %rcx;  /* pop rcx */           \
        mov     REG_RDX(%rsp), %rdx;  /* pop rdx */           \
        mov     REG_RBX(%rsp), %rbx;  /* pop rbx */           \
        mov     REG_RBP(%rsp), %rbp;  /* pop rbp */           \
        mov     REG_RSI(%rsp), %rsi;  /* pop rsi */           \
        mov     REG_RDI(%rsp), %rdi;  /* pop rdi */           \
        mov     REG_R8(%rsp), %r8;    /* pop r8 */            \
        mov     REG_R9(%rsp), %r9;    /* pop r9 */            \
        mov     REG_R10(%rsp), %r10;  /* pop r10 */           \
        mov     REG_R11(%rsp), %r11;  /* pop r11 */           \
        mov     REG_R12(%rsp), %r12;  /* pop r12 */           \
        mov     REG_R13(%rsp), %r13;  /* pop r13 */           \
        mov     REG_R14(%rsp), %r14;  /* pop r14 */           \
        mov     REG_R15(%rsp), %r15;  /* pop r15 */           \
        mov     REG_RSP(%rsp), %rsp;  /* pop rsp */

#else

/* no function declarations for makeSymTlb/symTbl.c */

/* macros for getting frame and return PC from a jmp_buf */

#define _WRS_FRAMEP_FROM_JMP_BUF(env)   ((char *) (env)[0].reg.reg_fp)
#define _WRS_RET_PC_FROM_JMP_BUF(env)   ((INSTR *) (env)[0].reg.reg_pc)

#endif	/* _ASMLANGUAGE */

/* PAL additions */

/* architecture-specific overrides for fppSave and fppRestore in fppLib.c */
#define FPP_SAVE(p)	(*_func_fppSaveRtn)(p)
#define FPP_RESTORE(p)	(*_func_fppRestoreRtn)(p)

/* from h/usb/target/usbIsaLib.h */

/* DMA controller selection */

#define _WRS_DMA_I8237

/* trigger signed IO arguments in sysLib.h */

#define _WRS_SIGNED_IO_ARGS
#define _WRS_SYS_IO

/* override _WRS_SR_SIZE in taskArchLib.h */

#define _WRS_SR_SIZE	ULONG

/*
 * trigger definition of portWorkQAdd1 in trgLib.c and
 * rBuffLib.c
 */

#define _WRS_PORT_WORK_Q_ADD1

/* used in cacheLib.c:cacheFuncsSet() */

#define _WRS_EXTERN_WRITEBACK

/* used in fppLib.c to align FP_CONTEXT */

/* dummy context must be in data section for now */
#define _WRS_ALIGN_FP_CONTEXT
#define _WRS_FPP_DUMMY_CONTEXT \
_WRS_DATA_ALIGN_BYTES(_CACHE_ALIGN_SIZE) fppDummyContext = {{{0}}}


/* architecture-specific overrides for fppSave and fppRestore in dbgLib.c */
#define _WRS_SHOW_SSE_REGS
#define FPP_DBG_SAVE(p)		(*_func_fppSaveRtn)(p)
#define FPP_DBG_RESTORE(p)	(*_func_fppRestoreRtn)(p)

/* from loadElfLib.c */

#define _WRS_USE_ELF_LOAD_FORMAT

/* from xdr_float.c */

#define FLOAT_NORM

/* from vmShow.c */

#define _WRS_SHOW_WBACK_STATE
#define _WRS_SHOW_GLOBAL_STATE

/* from taskShow.c */

#define _WRS_SHOW_SSE_REGS

/* from rBuffLib.c */

#define _WRS_PORT_WORK_Q_ADD1

/* from wdbFpLib.c */

#define _WRS_ALIGN_REG_SET

/* from schedLib.c */

#define _WRS_ENABLE_IDLE_INTS {intUnlock (-1);}

/* from sysOsmLib.c */

#define _WRS_OSM_INIT

/* Interrupt stack protection, used in usrDepend.c and usrKernelStack.c */
#define _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK

/* if OSM support not available for stack protection,
 *  * then support can not be available for interrupt
 *   * stack protection.
 *    */
#if !defined(_WRS_OSM_INIT)
#undef _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
#endif

#ifdef __cplusplus
}
#endif

#include <arch/i86/archI86Common.h>

/* end of PAL additions */

#endif /* __INCarchX86_64h */
