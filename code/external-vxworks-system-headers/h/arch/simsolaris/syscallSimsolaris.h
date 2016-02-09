/* syscallSimsolaris.h - VxSim specific System Call Infrastructure header */

/* 
 * Copyright (c) 2003-2004, 2007 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01d,04may07,zl   updated portable library build configuration.
01c,10feb04,jeg  added _func_syscallTrapHandle to fixe dependency issue
                 introduced into wdbDbgSysCallCheck() API.
01b,09feb04,jeg  added syscallTrapHandle () prototype.
01a,26dec03,jeg  written.
*/

/*
DESCRIPTION
This header contains VxSim-specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallVxSimh
#define __INCsyscallVxSimh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define	SYSCALL_ENTRY_FRAME_SIZE	48
#define	_SYSCALL_USER_SP_CHECK(sp)	/* XXX To implement */

/* typedefs */

#ifndef _ASMLANGUAGE
    /* 
     * The SYSCALL_ENTRY_STATE structure defines the saved machine state
     * when the system call trap is taken. This information is architecture
     * specific, and is used by the system call dispatcher to restart system
     * calls that have been interrupted by the occurance of signals.
     * System call restart is achieved by restoring the saved state at the
     * time of the system call trap, and re-issuing the system call.
     * Arguments to the system call are saved on the kernel stack, and 
     * the address of that array is passed as an argument to the dispatcher.
     * The layout of this structure must exactly match the ordering of members
     * of the system call entry frame in src/arch/sim<arch>/syscallALib.s.
     */

typedef struct syscall_entry_state
    {
    int		args[8];	/* argument list (user stack) */
    int		scn;		/* System Call Number (SCN) in eax */
    int *	pUStack;	/* user-mode stack pointer */
    int		statusReg;	/* saved Status Register */
    void * 	pc;		/* Trap return address */
    } SYSCALL_ENTRY_STATE;

extern FUNCPTR _func_syscallTrapHandle;

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallVxSimh */
