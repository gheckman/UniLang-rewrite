/* archI86Common.h - common I86 architecture specific header */

/*
* Copyright (c) 2003-2004, 2006-2007, 2009, 2012 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01l,22mar12,jpb  Updated for POSIX namespace isolation conformance (part of 
                 defect Defect WIND000307800).
01k,15dec09,scm  remove SYSCALL64 var...
01j,10dec09,scm  create 64bit syscall constants...
01i,04may07,zl   updated portable library build configuration.
01h,02feb06,mil  Updated for POSIX namespace conformance.
01g,13may04,zl   enabled user trcLib support.
01f,27apr04,jmp  added support for portable trcLib. moved INSTR definition
                 form archI86.h.
01e,13apr04,zmm  Add coprocessor support for Pentium.
01d,25nov03,pes  Move setting of _BYTE_ORDER macro into archI86Common.h
01c,17nov03,jb   Adding defines for syscalls
01b,12nov03,job  Moved some blib stuff from archI86.h
01a,11nov03,pes  written.
*/

#ifndef __INCarchI86Commonh
#define __INCarchI86Commonh

#ifdef __cplusplus
extern "C" {
#endif

#define	_BYTE_ORDER		_LITTLE_ENDIAN

#ifndef _ASMLANGUAGE
typedef unsigned char _Vx_INSTR;            /* char instructions */
#endif  /* !_ASMLANGUAGE */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* Common syscall defines */

#define SYSCALL_SEGMENT             8
#define SYSCALL_GATE_OFFSET         0x43    /* (SYSCALL_SEGMENT * sizeof(GDT) | (DPL3 > 13) ) */

/* from bLib.c */

#define _WRS_BLIB_ALIGNMENT     1       /* 2 byte alignment mask */

#define _WRS_PAL_COPROC_LIB             /* enable coprocessor abstraction */ 

#define _WRS_TRC_ARGS_COUNT     5       /* number of arguments to print in */
                                        /* stack trace */

#ifndef _ASMLANGUAGE
typedef _Vx_INSTR 	INSTR;	
#endif  /* !_ASMLANGUAGE */
#endif  /* !_POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCarchI86Commonh */




