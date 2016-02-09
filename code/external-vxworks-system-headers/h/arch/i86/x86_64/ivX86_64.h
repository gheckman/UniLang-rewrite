/* ivX86_64.h - x86_64 interrupt vectors */

/*
 * Copyright 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,23feb09,jb   Convert to 64-bit
01a,20jan09,jb   Adding 64-bit support
*/

#ifndef __INCivX86_64h
#define __INCivX86_64h

#ifdef __cplusplus
extern "C" {
#endif


/* 0 - 19	exception vector number */

#define IN_DIVIDE_ERROR			0
#define IN_DEBUG			1
#define IN_NON_MASKABLE			2
#define IN_BREAKPOINT			3
#define IN_OVERFLOW			4
#define IN_BOUND			5
#define IN_INVALID_OPCODE		6
#define IN_NO_DEVICE			7
#define IN_DOUBLE_FAULT			8
#define IN_CP_OVERRUN			9
#define IN_INVALID_TSS			10
#define IN_NO_SEGMENT			11
#define IN_STACK_FAULT			12
#define IN_PROTECTION_FAULT		13
#define IN_PAGE_FAULT			14
#define IN_RESERVED			15
#define IN_CP_ERROR			16
#define IN_ALIGNMENT			17
#define IN_MACHINE_CHECK		18
#define IN_SIMD				19

/* 20 - 31	unassigned, Intel reserved exceptions */

/* 32 - 255	user defined interrupt vectors */


#ifndef	_ASMLANGUAGE

/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)	( (long)(intVec) >> 4)
#define INUM_TO_IVEC(intNum)	((VOIDFUNCPTR *) ((intNum) << 4))

/* exception vector address/offset */

#define IV_DIVIDE_ERROR			INUM_TO_IVEC (IN_DIVIDE_ERROR)
#define IV_DEBUG			INUM_TO_IVEC (IN_DEBUG)
#define IV_NON_MASKABLE			INUM_TO_IVEC (IN_NON_MASKABLE)
#define IV_BREAKPOINT			INUM_TO_IVEC (IN_BREAKPOINT)
#define IV_OVERFLOW			INUM_TO_IVEC (IN_OVERFLOW)
#define IV_BOUND			INUM_TO_IVEC (IN_BOUND)
#define IV_INVALID_OPCODE		INUM_TO_IVEC (IN_INVALID_OPCODE)
#define IV_NO_DEVICE			INUM_TO_IVEC (IN_NO_DEVICE)
#define IV_DOUBLE_FAULT			INUM_TO_IVEC (IN_DOUBLE_FAULT)
#define IV_CP_OVERRUN			INUM_TO_IVEC (IN_CP_OVERRUN)
#define IV_INVALID_TSS			INUM_TO_IVEC (IN_INVALID_TSS)
#define IV_NO_SEGMENT			INUM_TO_IVEC (IN_NO_SEGMENT)
#define IV_STACK_FAULT			INUM_TO_IVEC (IN_STACK_FAULT)
#define IV_PROTECTION_FAULT		INUM_TO_IVEC (IN_PROTECTION_FAULT)
#define IV_PAGE_FAULT			INUM_TO_IVEC (IN_PAGE_FAULT)
#define IV_RESERVED			INUM_TO_IVEC (IN_RESERVED)
#define IV_CP_ERROR			INUM_TO_IVEC (IN_CP_ERROR)
#define IV_ALIGNMENT			INUM_TO_IVEC (IN_ALIGNMENT)
#define IV_MACHINE_CHECK		INUM_TO_IVEC (IN_MACHINE_CHECK)
#define IV_SIMD				INUM_TO_IVEC (IN_SIMD)

#endif	/* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif	/* __INCivX86_64h */
