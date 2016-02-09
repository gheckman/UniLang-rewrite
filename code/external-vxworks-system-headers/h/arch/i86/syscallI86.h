/* syscallI86.h - I86 specific System Call Infrastructure header */

/*
 * Copyright (c) 2003-2005, 2007-2008, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01g,16oct12,scm  WIND00376020 - fast system call support...
01f,14mar08,scm  modify saved regs to reflect code changes...
01e,04may07,zl   updated portable library build configuration.
01d,05may05,zmm  Fix SYSCALL_ENTRY_FRAME_SIZE. SPR 108825
01c,02feb04,jb  Fix SPR 93500
01b,04jan04,jb  Adding context to syscall_entry_state
01a,18sep03,jb   written.
*/

/*
DESCRIPTION
This header contains I86-specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallI86h
#define __INCsyscallI86h

#ifndef _ASMLANGUAGE
#include <taskLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

#if (CPU != PENTIUM)
/*
 * SYSENTER/SYSEXIT...
 *
 * When SYSENTER called, made from USR Mode (PL3) :
 *
 * IA32_SYSENTER_CS - sysCsSuper
 * IA32_SYSENTER_EIP - address of syscallHandle routine
 * IA32_SYSENTER_ESP - pTcbCurrent->pExcStackBase
 *
 * CS <--- loaded from IA32_SYSENTER_CS (target code segment)
 * RIP <--- loaded from IA32_SYSENTER_EIP (target instruction)
 * SS <--- Computed by adding 8 to IA32_SYSENTER_CS (stack segment)
 * RSP <--- loaded from IA32_SYSENTER_ESP (stack pointer)
 *
 * When SYSEXIT called, made from Kernel Mode (PL0):
 *
 * IA32_SYSENTER_CS - sysCsSuper
 * EDX - return address
 * ECX - user stack
 *
 * CS <--- Computed by adding 16 to IA32_SYSENTER_CS (code segment)
 * RIP <--- loaded from EDX (target instruction)
 * SS <--- Computed by adding 24 to IA32_SYSENTER_CS (stack segment)
 * RSP <--- loaded from ECX (stack pointer)
 *
 * NOTE: When using SYSENTER/SYSEXIT to implement system calls, any 
 * additional state that needs to be saved to allow a return to the 
 * calling procedure must be saved explicitly by the calling procedure 
 * or be predefined through programming conventions.
 *
 */

#define SYSCALL_ENTRY_FRAME_SIZE    72   /* size of 'syscall' frame */
#define INSTR_SYSENTER_SIZE          2   /* size of 'sysenter' instruction */
#define SYSCALL_STACK_ARGS           8   /* number of arguments passed */
#else
#define SYSCALL_ENTRY_FRAME_SIZE    68
#define SYSCALL_STACK_ARGS           8
#endif /* (CPU != PENTIUM) */

#ifndef _ASMLANGUAGE


/* The call gate/Tss mechanism does the copy for us, this is not needed */

#define _SYSCALL_USER_SP_CHECK(sp)

    /* typedefs */

    /*
     * The SYSCALL_ENTRY_STATE structure defines the saved machine state
     * when the system call trap is taken. This information is architecture
     * specific, and is used by the system call dispatcher to restart system
     * calls that have been interrupted by the occurance of signals.
     * System call restart is achieved by restoring the saved state at the
     * time of the system call trap, and re-issuing the system call.
     *
     * All arguments to the system call are saved on the kernel stack, and 
     * the address of that array is passed as an argument to the dispatcher.
     * The layout of this structure must exactly match the ordering of members
     * of the system call entry frame in src/arch/I86/syscallALib.s.
     *
     */

typedef struct syscall_entry_state
    {
#if (CPU != PENTIUM)
    long    esi;            /* Saved reg on entry to syscallHandle */
    long    edi;            /* Saved reg on entry to syscallHandle */
    long    ebx;            /* Saved reg on entry to syscallHandle */

    void *  pc;             /* return to stub PC (edx) */
    long *  pUStack;        /* usr stack pointer (ecx) */

    long    cs;             /* return address code segment */

    long    upc;            /* return to caller pc */
    long    args[8];        /* argument list */
    long    scn;            /* System Call Number - Also temp error storage */

    long    errNo;          /* errno status */
    long    eflags;         /* EFLAGS */
#else
    int     esi;            /* Save reg */
    int     edi;            /* Save reg */
    int     ebx;            /* Save reg */
    void *  pc;             /* return address instruction pointer */
    int     cs;             /* return address code segment */
    int     scn;            /* System Call Number - Also temp error storage */
    int     upc;            /* return to caller pc */
    int     args[8];        /* argument list  */
    int  *  pUStack;        /* user-mode stack pointer */
    int     ss;             /* user stack segment */
#endif /* (CPU != PENTIUM) */
    } SYSCALL_ENTRY_STATE;


/* Prototype */
UINT32 sysModGdt (UINT32 offset, UINT32 limit, UINT32 base, UINT32 priority);


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallI86h */
