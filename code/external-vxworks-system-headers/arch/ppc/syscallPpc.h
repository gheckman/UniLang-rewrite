/* syscallPpc.h - PowerPC specific System Call Infrastructure header */

/*
 * Copyright (c) 2003-2004, 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01d,04may07,zl   updated portable library build configuration.
01c,04may04,yvp  Renamed spare1 to srTable.
01b,06apr04,yvp  SPR 95407: SYSCALL_ENTRY_FRAME_SIZE now made a multiple 
                 of _STACK_ALIGN_SIZE.
01a,15sep03,yvp  written.
*/

/*
DESCRIPTION
This header contains PowerPC-specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallPpch
#define __INCsyscallPpch

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

#define SYSCALL_ENTRY_FRAME_SIZE	96

    /* PPC doesnt need a user-SP check since all params are in registers. */

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
     * of the system call entry frame in src/arch/ppc/syscallALib.s.
     */

typedef struct syscall_entry_state
    {
    int    args[8];             /* argument list (r3-r10) */
    int    scn;			/* System Call Number (SCN) in r0 */
    void * pSdata;		/* small data pointer (r13) */
    void * pSdata2;		/* small data pointer 2 (r2) */
    void * pLR;			/* saved link register value */
    int  * pUStack;		/* user-mode stack pointer */
    int    statusReg;		/* saved Machine Status Register (SRR1) */ 
    void * pc;			/* Trap return address (SRR0) */
    int    nonVolatileRegs[4];	/* saved non-volatile registers (r28-r31) */
    int    pSrTable;		/* Ptr to Segment Reg. Table (PPC60X only) */
    int    spare1;
    int    spare2;
    } SYSCALL_ENTRY_STATE;
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallPpch */
