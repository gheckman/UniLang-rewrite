/* archI86.h - Intel 80X86 specific header */

/*
 * Copyright (c) 1993,1999,2001-2008,2010,2011,2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
03b,20jun13,scm  WIND00420874 - correct workQAdd indexing for more than 8
                 core...
03a,14aug11,j_l  Move _WRS_ARCH_HAS_CPU_PWR_MGMT outside of power management
                 ifdef.
02z,12aug11,rbc  WIND00238999 - Fix conditional for CPU==NEHALEM
02y,11aug11,rbc  WIND00238999 - Fix build errors
02x,09aug11,rbc  WIND00238999 - Fix build error for windPwrDown()
02w,18may11,jb   Requirement WIND00189850 - Increase VX_MAX_SMP_CPUS for HT/SMT support
02v,19jan11,jb   Fix for WIND00185635 - mmu deoptimize locks do not work
02u,05nov10,gls  modified _ALLOC_ALIGN_SIZE
02t,20oct10,zl   defined _WRS_ARCH_DEFERS_KERNEL_UNLOCK and 
                 _WRS_ARCH_HAS_TASK_MMU_CURRENT_SET.
02t,30sep10,sem  Add new IA cpus. Remove pentium2/3
02s,16sep10,gls  added VX_OBJ_ALIGN_SIZE
02r,29jul10,pad  Moved extern C statement after include statements.
02q,10oct08,rbc  WIND00132719. Add defines for _STACK_ALIGN_SIZE and
                 _ALLOC_ALIGN_SIZE.
02p,27aug08,jpb  Renamed VSB header file
02o,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
02n,13mar08,rlp  Removed obsolete _WRS_ARCH_HAS_DBG_IPI macro.
02m,24sep07,scm  WIND00105635, enable _WRS_MMU_HAS_MAP_STATE_API.
02l,15aug07,mmi  Added _WRS_ARCh_HAS_CPU_PWR_MGMT
02k,25jul07,scm  WIND00099103...
02j,13jul07,rlp  Added the _WRS_ARCH_HAS_DBG_IPI support.
02i,09jul07,tor  revert 02h
02h,02jul07,tor  temp macro for vxIpiLib and cpcLib
02g,04may07,zl   updated portable library build configuration.
02f,17apr07,kk   move VX_MAX_SMP_CPUS from smpI86P.h to here
02e,21feb07,jmg  Added include vxPortablLibP.h
02d,11dec06,kk   removed references to _WRS_BASE6_SCHEDULER and 
                 _WRS_ARCH_HAS_RESCHEDULE_STACK, no longer needed
02c,06dec06,scm  only Pentium4 is SMP safe...
02b,02nov06,scm  define _WRS_ARCH_HAS_IDLE_TASK, undef
                 _WRS_ARCH_HAS_RESCHEDULE_STACK
02a,25sep06,scm  added _WRS_ARCH_HAS_NEW_KERNEL_LOCK
01z,30aug06,scm  Add definition _WRS_VX_NO_GLOBAL_ERRNO
01y,15jun06,scm  Add definition of _WRS_ARCH_HAS_RESCHEDULE_STACK.
01y,30jun06,agf  enable optimized version of bLib (CQ:WIND00044910)
01x,28apr05,scm  scm  add _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
01w,12apr05,kk   remove _WRS_OBJLIB_SUPPORT_VERIFY_TRAP macro (SPR# 106486)
01v,04nov04,scm  add _WRS_OSM_INIT for new OSM API...
01u,01sep04,jb   Adding _WRS_OBJLIB_SUPPORT_VERIFY_TRAP for objVerify support
01t,14jul04,jb   Enable Portable for all functions
01s,17may04,jb   Switch to PORTABLE scheduler.
                 Fix debug register clear on load and go problem
01r,05may04,zmm  Fix diab compiler warnings.
01s,13may04,zl   fixed _WRS_FRAMEP_FROM_JMP_BUF().
01r,27apr04,cjj  Defined workQLib_PORTABLE
01q,27apr04,jmp  moved INSTR definition to archI86Common.h. added macros for
                 getting frame and return PC from a jmp_buf.
01p,03dec03,md   changed to use portable scheduler
01o,25nov03,pes  Move setting of _BYTE_ORDER macro into archI86Common.h.
01n,14nov03,job  Moved some blib stuff to archI86Common.h
01m,13nov03,pes  Add include of archI86Common.h
01l,27aug03,to   added defines for semLib.
01k,07may03,pes  PAL conditional compilation cleanup. Phase 2.
01j,28apr03,pes  PAL conditional compilation cleanup.
01i,12nov02,hdn  made CR4 initialization only for P5 or later (spr 83992)
01h,29oct02,hdn  assigned reserved1 to (FP_CONTEXT *) (spr 70252)
01g,07oct02,hdn  added the architecture extension of the TCB
01f,13mar01,sn   SPR 73723 - define supported toolchains
01e,04oct01,hdn  enclosed ARCH_REGS_INIT macro with _ASMLANGUAGE
01d,21aug01,hdn  added PENTIUM4's _CACHE_ALIGN_SIZE, ARCH_REGS_INIT
01c,10aug01,hdn  added PENTIUM2/3/4 support
01b,25feb99,hdn  added _CACHE_ALIGN_SIZE for Pentium and PentiumPro
01a,07jun93,hdn  written based on arch68k.h
*/

#ifndef __INCarchI86h
#define __INCarchI86h

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif
	
#if (CPU==PENTIUM) && defined(_WRS_CONFIG_SMP)
#error "PENTIUM IS NOT SMP SAFE !!!"
#endif

#define _ARCH_SUPPORTS_GCC

/* temporary macro to indicate i86 uses the idle task stack */

#define _WRS_ARCH_HAS_IDLE_TASK

/* temporary macro to indicate i86 uses the type II kernel lock */

#define _WRS_ARCH_HAS_NEW_KERNEL_LOCK

#define _WRS_VX_NO_GLOBAL_ERRNO

/* arch supports new MMU API... */

#define _WRS_MMU_HAS_MAP_STATE_API

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

/* arch needs deferred kernel unlock */

#define _WRS_ARCH_DEFERS_KERNEL_UNLOCK

/* arch provides taskMmuCurrentSet() */

#define _WRS_ARCH_HAS_TASK_MMU_CURRENT_SET

/* arch allows semaphore protection for vmStateSet */

#define _WRS_MMU_DEOPTIMIZE_LOCK_CTX_SEM

#undef VX_MAX_SMP_CPUS
#if CPU!=PENTIUM
#if CPU==_VX_ATOM
#define VX_MAX_SMP_CPUS      8   /* maximum processors in SMP configuration */
#define VX_MAX_SMP_CPU_SHIFT 3   /* allow workQ to calculate with Max CPUs  */
#elif  CPU==PENTIUM4 || CPU==_VX_CORE
#define VX_MAX_SMP_CPUS     16   /* maximum processors in SMP configuration */
#define VX_MAX_SMP_CPU_SHIFT 4   /* allow workQ to calculate with Max CPUs  */
#else
#define VX_MAX_SMP_CPUS     32   /* maximum processors in SMP configuration */
#define VX_MAX_SMP_CPU_SHIFT 5   /* allow workQ to calculate with Max CPUs  */
#endif /* CPU==_VX_ATOM */
#endif /* CPU!=PENTIUM */

#define	_DYNAMIC_BUS_SIZING	FALSE	/* required alignment for swap */

/* required stack alignment for sse and sse2 instructions is 16 bytes */

#define _STACK_ALIGN_SIZE   16

/* allocated objects require an 8 byte aligment */

#define _ALLOC_ALIGN_SIZE   8

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

#define VX_OBJ_ALIGN_SIZE   8

#if	(CPU==PENTIUM)
#define _CACHE_ALIGN_SIZE	32
#else
#define _CACHE_ALIGN_SIZE	64
#endif	/* CPU==PENTIUM */

#ifdef	_ASMLANGUAGE

/* 
 * system startup macros used by sysInit(sysALib.s) and romInit(romInnit.s).
 * - no function calls to outside of BSP is allowed.
 * - no references to the data segment is allowed.
 * the CR4 is introduced in the Pentium processor.
 */

#define ARCH_REGS_INIT							\
	xorl	%eax, %eax;		/* zero EAX */			\
	movl    %cr0, %edx;		/* get CR0 */			\
	andl    $0x7ffafff1, %edx;	/* clear PG, AM, WP, TS, EM, MP */ \
	movl    %edx, %cr0;		/* set CR0 */			\
									\
	pushl	%eax;			/* initialize EFLAGS */		\
	popfl;

#define ARCH_CR4_INIT							\
	xorl	%eax, %eax;		/* zero EAX */			\
	movl	%eax, %cr4;		/* initialize CR4 */


#else

/* architecture extension of the TCB (pTcb->reserved2) */

typedef struct x86Ext		/* architecture specific TCB extension */
    {
    unsigned int	reserved0;	/* (DS_CONFIG *) */
    unsigned int	reserved1;	/* (FP_CONTEXT *) for FPU exception */
    unsigned int	reserved2;
    unsigned int	reserved3;
    unsigned int	reserved4;
    unsigned int	reserved5;
    unsigned int	reserved6;
    unsigned int	reserved7;
    } X86_EXT;

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

#define _WRS_SR_SIZE	UINT

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
#endif /* __INCarchI86h */
