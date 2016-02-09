/* archSimsolarisCommon.h - common Simsolaris architecture specific header */

/*
* Copyright (c) 2003-2004, 2006-2007, 2012 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01i,23mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 defect Defect WIND000307800).
01h,04may07,zl   updated portable library build configuration.
01g,02feb06,mil  Updated for POSIX namespace conformance.
01f,13may04,zl   enabled user-side trace.
01e,22apr04,jmp  added support for portable trcLib.
		 Moved INSTR definitions from archSimsolaris.h.
01d,25feb04,aeg  added _WRS_PAL_COPROC_LIB
01c,24dec03,jeg  added SYSCALL_TRAP_HANDLE_INIT and SYSCALL_SF macros.
01b,12nov03,job  Moved blib stuff from archSimsolaris.h
01a,11nov03,pes  written.
*/

#ifndef __INCarchSimsolarisCommonh
#define __INCarchSimsolarisCommonh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
typedef unsigned long _Vx_INSTR;          /* 32 bit word-aligned instructions */
#endif  /* !_ASMLANGUAGE */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* from bLib.c */

#define _WRS_BLIB_ALIGNMENT     3       /* quad byte alignment mask */

/*
 * SYSCALL_TRAP_HANDLE_INIT - system call trap magic number
 *
 * On VxSim, the system call infrastucture is based on a mechanism to directly
 * call kernel services from RTP via the syscallTrapHandle() routine.
 * Since the RTP does not have access to syscallTrapHandle() routine, each RTP
 * contains a function pointer _func_syscallTrapHandle which is initialized to
 * an invalid address: SYSCALL_TRAP_HANDLE_INIT. On the first system call
 * performed by the RTP, an exception will be generated, the exception
 * handling will invoke syscallTrapHandlerInit() if installed, and
 * syscallTrapHandlerInit() will fix _func_syscallTrapHandle to point to
 * syscallTrapHandle().
 */

#define SYSCALL_TRAP_HANDLE_INIT	0x1234

/* 
 * stack frame size used for syscall routines. The size is bigger than the
 * STACK_FRAME_SIZE usually used since we have 8 parameters to manage. So it 
 * requires additional space into stack frame to store parameters 7 and 8.
 */

#define SYSCALL_SF	0x80

/*
 * Parameters 1 to 6 are located into %i0 to %i5 registers, the
 * others are located into stack. Define offset of paameters 7 
 * 8 into the stack. 
 */

#define PARAM7	0x5c
#define PARAM8	0x60
#define PARAM9	0x64

/* Enable Coprocessor Abstraction */

#define _WRS_PAL_COPROC_LIB

#define _WRS_TRC_ARGS_COUNT	6	/* number of arguments to print in */

#ifndef _ASMLANGUAGE
typedef _Vx_INSTR	 INSTR;
#endif	/* !_ASMLANGUAGE */

#endif  /* !_POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchSimsolarisCommonh */

