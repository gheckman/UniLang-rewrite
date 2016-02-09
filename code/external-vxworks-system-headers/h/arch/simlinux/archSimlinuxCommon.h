/* archSimpentiumCommon.h - common PENTIUM VxSim architecture specific header */

/*
 * Copyright 2003-2004, 2006-2007, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,23mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 defect Defect WIND000307800).
01j,04may07,zl   updated portable library build configuration.
01i,14feb06,pes  Updated for POSIX namespace conformance
01h,13may04,zl   enabled user-mode trcLib
01g,22apr04,jmp  added support for portable trcLib.
01f,23mar04,dbt  Updated comments.
01e,09feb04,aeg  added _WRS_PAL_COPROC_LIB
01d,25nov03,pes  Move definition of _BYTE_ORDER to arch<Arch>Common.h.
01c,17nov03,jmp  added SYSCALL_TRAP_HANDLE_INIT.
01b,12nov03,job  Moved some blib stuff from archSimnt.h
01a,11nov03,pes  written.
*/

#ifndef __INCarchSimpentiumCommonh
#define __INCarchSimpentiumCommonh

#ifdef __cplusplus
extern "C" {
#endif

#define _BYTE_ORDER		_LITTLE_ENDIAN

#ifndef _ASMLANGUAGE
typedef unsigned char _Vx_INSTR;            /* char instructions */
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

#define	SYSCALL_TRAP_HANDLE_INIT	0x1234

/* Enable Coprocessor Abstraction */

#define _WRS_PAL_COPROC_LIB

#define _WRS_TRC_ARGS_COUNT	5	/* number of arguments to print in */
					/* stack trace */

#ifndef _ASMLANGUAGE
typedef _Vx_INSTR	 INSTR;
#endif	/* !_ASMLANGUAGE */

#endif  /* !_POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchSimpentiumCommonh */
