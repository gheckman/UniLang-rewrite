/* syscallArm.h - ARM specific System Call Infrastructure header */

/*
 * Copyright (c) 2003, 2005, 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01g,03dec09,cww  Moved ARM specific macros from syscallLibP.h
01f,04may07,zl   updated portable library build configuration.
01e,04mar05,scm  _SYSCALL_USER_SP_CHECK break signals alt stack option...
01d,23feb05,scm  re-assign "spare" to user link reg...
01c,19nov03,cjj  replaced pStackLimit by pStackEnd in _SYSCALL_USER_SP_CHECK
01b,14oct03,scm  enhanced, flushed out, and debugging.
01a,03oct03,jb   written.
*/

/*
DESCRIPTION
This header contains ARM specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallArmh
#define __INCsyscallArmh

#ifndef _ASMLANGUAGE
#include <taskLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


    /* defines */

#define SYSCALL_ENTRY_FRAME_SIZE	52

#define _SYSCALL_USER_SP_CHECK(sp)

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
     * of the system call entry frame in src/arch/arm/syscallALib.s.
     */

typedef struct syscall_entry_state
    {
    ULONG    args[8];   /* argument list (r0-r3 and sp[0]-sp[3]) */
    ULONG    scn;	/* System Call Number (SCN) in r12 */
    ULONG    statusReg;	/* saved Status Register (spsr) */ 
    INSTR    *pc;	/* Trap return address (lr) */
    ULONG    *pUStack;  /* user-mode stack pointer */
    ULONG    usrLnk;	/* user-mode link register */
    } SYSCALL_ENTRY_STATE;


#define ARM_RTP_STACK_OFFSET     12  /* ARM pushes r2, SCn, and lr onto */ 
                                     /* stack prior to signal handling */
#define SYSCALL_USER_SP_GET(tid) (char *) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
		   (sizeof(SYSCALL_ENTRY_STATE)+ARM_RTP_STACK_OFFSET)))->pUStack)

#define SYSCALL_USER_PC_GET(tid) (void *) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
		   (sizeof(SYSCALL_ENTRY_STATE)+ARM_RTP_STACK_OFFSET)))->pc)

#define SYSCALL_USER_SCN_GET(tid) (int) \
	(((SYSCALL_ENTRY_STATE *) ((((WIND_TCB *)(tid))->pExcStackBase) - \
		   (sizeof(SYSCALL_ENTRY_STATE)+ARM_RTP_STACK_OFFSET)))->scn)

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallArmh */
