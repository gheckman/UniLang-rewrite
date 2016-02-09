/* esfX86_64.h - x86_64 exception stack frames */

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
01e,24feb09,jb   Update to 64-bits
01d,21jan09,jb   64-bit version from 32-bit version 01c
*/

#ifndef	__INCesfX86_64h
#define	__INCesfX86_64h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* Override eflags references */
#define eflags  rflags

/* Exception stack frames.  Most of these can happen only for one
   CPU or another, but they are all defined for all CPU's */

/* Format-0 - no privilege change, no error code */

typedef struct
    {
    INSTR * pc;				/* 0x00 : PC */
    unsigned long cs;			/* 0x08 : code segment */
    unsigned long rflags;		/* 0x10 : EFLAGS */
    } ESF0;				/* sizeof(ESF0) -> 0x18 */

/* Format-1 - no privilege change, error code */

typedef struct
    {
    unsigned long errCode;		/* 0x00 : error code */
    INSTR * pc;				/* 0x08 : PC */
    unsigned long cs;			/* 0x10 : code segment */
    unsigned long rflags;		/* 0x18 : EFLAGS */
    } ESF1;				/* sizeof(ESF1) -> 0x20 */

/* Format-2 - privilege change, no error code */

typedef struct
    {
    INSTR * pc;				/* 0x00 : PC */
    unsigned long cs;			/* 0x08 : code segment */
    unsigned long rflags;		/* 0x10 : EFLAGS */
    unsigned long esp;			/* 0x18 : ESP */
    unsigned long ss;			/* 0x20 : SS */
    } ESF2;				/* sizeof(ESF2) -> 0x28 */

/* Format-3 - privilege change, error code */

typedef struct
    {
    unsigned long errCode;		/* 0x00 : error code */
    INSTR * pc;				/* 0x08 : PC */
    unsigned long cs;			/* 0x10 : code segment */
    unsigned long rflags;		/* 0x18 : EFLAGS */
    unsigned long esp;			/* 0x20 : ESP */
    unsigned long ss;			/* 0x28 : SS */
    } ESF3;				/* sizeof(ESF3) -> 0x30 */

#endif	/* _ASMLANGUAGE */


#define	ESF0_EIP	0x00		/* 0x00 : PC */
#define	ESF0_CS		0x08		/* 0x08 : CS */
#define	ESF0_EFLAGS	0x10		/* 0x10 : EFLAGS */

#define	ESF1_ERROR	0x00		/* 0x00 : ERROR */
#define	ESF1_EIP	0x08		/* 0x08 : PC */
#define	ESF1_CS		0x10		/* 0x10 : CS */
#define	ESF1_EFLAGS	0x18		/* 0x18 : EFLAGS */

#define	ESF2_EIP	0x00		/* 0x00 : PC */
#define	ESF2_CS		0x08		/* 0x08 : CS */
#define	ESF2_EFLAGS	0x10		/* 0x10 : EFLAGS */
#define	ESF2_ESP	0x18		/* 0x18 : ESP */
#define	ESF2_SS		0x20		/* 0x20 : SS */

#define	ESF3_ERROR	0x00		/* 0x00 : ERROR */
#define	ESF3_EIP	0x08		/* 0x08 : PC */
#define	ESF3_CS		0x10		/* 0x10 : CS */
#define	ESF3_EFLAGS	0x18		/* 0x18 : EFLAGS */
#define	ESF3_ESP	0x20		/* 0x20 : ESP */
#define	ESF3_SS		0x28		/* 0x28 : SS */

#define	ESF0_NBYTES	0x18		/* sizeof(ESF0) */
#define	ESF1_NBYTES	0x20		/* sizeof(ESF1) */
#define	ESF2_NBYTES	0x28		/* sizeof(ESF2) */
#define	ESF3_NBYTES	0x30		/* sizeof(ESF3) */

#define	ESF0_NLONGS	0x03		/* sizeof(ESF0) / sizeof(long) */
#define	ESF1_NLONGS	0x04		/* sizeof(ESF1) / sizeof(long) */
#define	ESF2_NLONGS	0x05		/* sizeof(ESF2) / sizeof(long) */
#define	ESF3_NLONGS	0x06		/* sizeof(ESF3) / sizeof(long) */

#ifdef __cplusplus
}
#endif

#endif	/* __INCesfX86_64h */
