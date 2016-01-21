/* syscallMips.h - MIPS specific System Call Infrastructure header */

/*
 * Copyright (c) 2003-2004, 2007-2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01l,10jun08,slk  add offset defines for ASM access to SYSCALL_ENTRY_STATE
                 struct
01k,04nov07,pes  Ensure that SYSCALL_ENTRY_FRAME_SIZE is aligned to
                 _STACK_ALIGN_SIZE
01j,24may07,pes  Update for n32.
01i,04may07,zl   updated portable library build configuration.
01h,19aug04,pes  Remove stack pointer range checking until another validation
                 strategy can be identified.
01g,10mar04,pes  *Really* finish implementation of 01e.
01f,10mar04,pes  Finish implementation of 01e.
01e,10mar04,pes  _STACK_ALIGN_SIZE has been re-defined to 8, so we no longer
                 need a custom vlue for the stack alignment test.
01d,12jan04,pes  Modify stack alignment test. _STACK_ALIGN_SIZE is 16 bytes,
                 but in practice only 64-bit (8 byte) alignment is enforced.
01c,30oct03,pcm  implemented changes from code review
01b,21oct03,pcm  changed pStackLimit to pStackEnd
01a,18sep03,pes  written.
*/

/*
DESCRIPTION
This header contains MIPS-specific definitions and constants used by
the System Call Infrastructure library.

*/

#ifndef __INCsyscallMipsh
#define __INCsyscallMipsh

#ifndef _ASMLANGUAGE
#include "taskLib.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

    /* defines */

#if (_WRS_INT_REGISTER_SIZE == 4)
#define SYSCALL_ENTRY_FRAME_SIZE	56
#elif (_WRS_INT_REGISTER_SIZE == 8)
#ifdef _WRS_MIPS_N32_ABI
#define SYSCALL_ENTRY_FRAME_SIZE	96
#else /* _WRS_MIPS_N32_ABI */
#define SYSCALL_ENTRY_FRAME_SIZE	88
#endif /* _WRS_MIPS_N32_ABI */
#else
#error "_WRS_INT_REGISTER_SIZE not defined."
#endif

#ifndef _ASMLANGUAGE


/*
 * this macro is used to validate the stack pointer and copy necessary
 * arguments from the user stack to the kernel stack only after such
 * validation has been successfully completed. XXX This needs _WRS. PES
 */


#ifdef _WRS_MIPS_N32_ABI
/*
 * For n32, all 8 arguments are passed in registers, and inserted
 * into the SYSCALL_ENTRY_STATE structure in syscallTrapHandle.
 */
#if defined (_WRS_USER_SP_RANGE_CHECK)
#define _SYSCALL_USER_SP_CHECK(sp) \
  { \
  if (((UINT32)(sp) < (UINT32)(taskIdCurrent->pStackEnd)) || \
      ((UINT32)(sp) > (UINT32)(taskIdCurrent->pStackBase)) || \
      ((UINT32)(sp) & (_STACK_ALIGN_SIZE - 1))) \
      { \
      errnoSet (S_syscallLib_INVALID_USER_SP); \
      return (ERROR); \
      } \
  }
#else /* _WRS_USER_SP_RANGE_CHECK */
#define _SYSCALL_USER_SP_CHECK(sp) \
  { \
  if (((UINT32)(sp) & (_STACK_ALIGN_SIZE - 1))) \
      { \
      errnoSet (S_syscallLib_INVALID_USER_SP); \
      return (ERROR); \
      } \
  }
#endif /* _WRS_USER_SP_RANGE_CHECK */
#else /* _WRS_MIPS_N32_ABI */

typedef struct sycall_mips_stack_args
    {
    _RType args[4];
    } SYSCALL_MIPS_STACK_ARGS;

/*
 * For o32/o64, the last 4 arguments to a system call are passed on
 * the user-mode stack. These arguments must be copied into the
 * SYSCALL_ENTRY_STATE structure on the exception stack in this macro.
 */
#if defined (_WRS_USER_SP_RANGE_CHECK)
#define _SYSCALL_USER_SP_CHECK(sp) \
  { \
  register SYSCALL_MIPS_STACK_ARGS *src; \
  register SYSCALL_MIPS_STACK_ARGS *dst; \
  if (((UINT32)(sp) < (UINT32)(taskIdCurrent->pStackEnd)) || \
      ((UINT32)(sp) > (UINT32)(taskIdCurrent->pStackBase)) || \
      ((UINT32)(sp) & (_STACK_ALIGN_SIZE - 1))) \
      { \
      errnoSet (S_syscallLib_INVALID_USER_SP); \
      return (ERROR); \
      } \
  src = (SYSCALL_MIPS_STACK_ARGS *)&(((SYSCALL_ENTRY_STATE *)(sp))->args[4]); \
  dst = (SYSCALL_MIPS_STACK_ARGS *)&(pState->args[4]); \
  *dst = *src; \
  }
#else /* _WRS_USER_SP_RANGE_CHECK */
#define _SYSCALL_USER_SP_CHECK(sp) \
  { \
  register SYSCALL_MIPS_STACK_ARGS *src; \
  register SYSCALL_MIPS_STACK_ARGS *dst; \
  if (((UINT32)(sp) & (_STACK_ALIGN_SIZE - 1))) \
      { \
      errnoSet (S_syscallLib_INVALID_USER_SP); \
      return (ERROR); \
      } \
  src = (SYSCALL_MIPS_STACK_ARGS *)&(((SYSCALL_ENTRY_STATE *)(sp))->args[4]); \
  dst = (SYSCALL_MIPS_STACK_ARGS *)&(pState->args[4]); \
  *dst = *src; \
  }
#endif /* _WRS_USER_SP_RANGE_CHECK */
#endif /* _WRS_MIPS_N32_ABI */
		    
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
     * of the system call entry frame in src/arch/Mips/syscallALib.s.
     *
     * Note that sizeof(SYSCALL_ENTRY_STATE) must maintain proper stack
     * alignment. For n32, this means adding 8 bytes (two 'int's) at the
     * end of the structure.
     */

typedef struct syscall_entry_state 
    {
    _RType	args[8];        /* argument list (a0-a3, user stack) */
    int		scn;		/* System Call Number (SCN) in v0 */
    int  *	pUStack;	/* user-mode stack pointer */
    void *	pSdata;		/* small data pointer (gp) */
    void *	pc;		/* Trap return address (EPC) */
    void *	ra;		/* saved return address register */
    int		statusReg;	/* saved Status Register (SR) */ 
#ifdef _WRS_MIPS_N32_ABI
    int		pad[2];		/* padding to maintain n32 stack alignment */
#endif
    } SYSCALL_ENTRY_STATE;

#else /* _ASMLANGUAGE */

/* offsets into the SYSCALL_ENTRY_STATE structure */
#define SYSCALL_ENTRY_STATE_ARGS	(0)
#define SYSCALL_ENTRY_STATE_ARG_4	(_RTypeSize * 4)
#define SYSCALL_ENTRY_STATE_SCM		(_RTypeSize * 8)
#define SYSCALL_ENTRY_STATE_PUSTACK	(SYSCALL_ENTRY_STATE_SCM + 4)
#define SYSCALL_ENTRY_STATE_PSDATA	(SYSCALL_ENTRY_STATE_PUSTACK + 4)
#define SYSCALL_ENTRY_STATE_PC		(SYSCALL_ENTRY_STATE_PSDATA + 4)
#define SYSCALL_ENTRY_STATE_RA		(SYSCALL_ENTRY_STATE_PC + 4)
#define SYSCALL_ENTRY_STATE_STATUS_REG	(SYSCALL_ENTRY_STATE_RA + 4)

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsyscallMipsh */
