/* syscallX86_64.h - x86_64 specific System Call Infrastructure header */

/*
 * Copyright (c) 2003-2005, 2007-2009, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01h,24jul12,scm  WIND00225976 - syscall/sysret support...
01g,01dec09,scm  make 64 bit compliant...
01f,14mar08,scm  modify saved regs to reflect code changes...
01e,04may07,zl   updated portable library build configuration.
01d,05may05,zmm  Fix SYSCALL_ENTRY_FRAME_SIZE. SPR 108825
01c,02feb04,jb   Fix SPR 93500
01b,04jan04,jb   Adding context to syscall_entry_state
01a,18sep03,jb   written.
*/

/*
DESCRIPTION
This header contains x86_64-specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallX86_64h
#define __INCsyscallX86_64h

#ifndef _ASMLANGUAGE
#include <taskLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

#define SYSCALL_ENTRY_FRAME_SIZE    144  /* size of 'syscall' frame */

#define INSTR_SYSCALL_SIZE          2    /* size of 'syscall' instruction */

#define SYSCALL_STACK_ARGS          8    /* number of arguments passed */

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
     * of the system call entry frame in src/arch/X86_64/x86_64/syscallALib.s.
     *
     */

typedef struct syscall_entry_state
    {
    long    rax;            /* Saved reg on entry to syscallHandle */
    long    rbx;            /* Saved reg on entry to syscallHandle */

    long    scn;            /* System Call Number - Also temp error storage */
    long    upc;            /* return to caller pc */
    long    args[8];        /* argument list  */

    long    rcx;            /* save off SYSCALL/SYSRET use for RIP */
    long    r11;            /* save off SYSCALL/SYSRET use for EFLAGS */

    void *  pc;             /* return address instruction pointer */
    long    cs;             /* return address code segment */
    
    long *  pUStack;        /* user-mode stack pointer */
    long    ss;             /* user stack segment */
    } SYSCALL_ENTRY_STATE;


/* Prototype */

UINT32 sysModGdt (UINT32 offset, UINT32 limit, UINT32 base, UINT32 priority);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallX86_64h */
