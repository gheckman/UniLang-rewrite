/* asmX86_64.h - x86_64 assembler definitions header file */

/*
 * Copyright (c) 2009
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,17mar09,jb   Update INT_CONNECT_CODE29
01a,20jan09,jb   Derived from 32-bit version 01o
*/

#ifndef	__INCasmX86_64h
#define	__INCasmX86_64h

/************************************************************/

/*
 * The following definitions are used for symbol name compatibility.
 * 
 * When #if 1, sources are assembled assuming the compiler
 * you are using does not generate global symbols prefixed by "_".
 * (e.g. elf/dwarf)
 * 
 * When #if 0, sources are assembled assuming the compiler
 * you are using generates global symbols prefixed by "_".
 * (e.g. coff/stabs)
 */

#if	TRUE
#define FUNC(sym)		sym
#define FUNC_LABEL(sym)		sym:
#else
#define FUNC(sym)		_##sym
#define FUNC_LABEL(sym)		_##sym:
#endif

#define VAR(sym)		FUNC(sym)

/*
 * These macros are used to declare assembly language symbols that need
 * to be typed properly(func or data) to be visible to the OMF tool.  
 * So that the build tool could mark them as an entry point to be linked
 * correctly.  This is an elfism. Use #if 0 for a.out.
 */

#if	TRUE
#define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@function
#define GDATA(sym) FUNC(sym) ;  .type   FUNC(sym),@object
#else
#define GTEXT(sym) FUNC(sym)
#define GDATA(sym) FUNC(sym)
#endif

/* Introduced to abstract assembler idiosyncrasies */

#define	FUNC_BEGIN(func)	FUNC_LABEL(func)
#define	FUNC_END(func)		.size	FUNC(func), . - FUNC(func)

/************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
 * fp offsets to arguments
 *
 * In 64-bits the first six arguments are in registers,
 * the rest are on the stack. ARG0 - ARG6 should not
 * be used.
 */

#define ARG7	16
#define ARG8	24
#define ARG9	32
#define ARG10	40
#define ARG11	48
#define ARG12	56

/* Should not be any double args. Will be in registers? */
#if 0
#define DARG1	8		/* double arguments */
#define	DARG1L	12
#define DARG2	16
#define DARG2L	20
#define DARG3	24
#define DARG3L	28
#define DARG4	32
#define DARG4L	36
#endif

/*
 * sp offsets to arguments
 *
 * In 64-bits the first six arguments are in registers,
 * the rest are on the stack. SP_ARG0 - SP_ARG6 should
 * not be used.
 */

#define SP_ARG7		0
#define SP_ARG8		8
#define SP_ARG9		16
#define SP_ARG10	24
#define SP_ARG11	32
#define SP_ARG12	40

/* offset to the IRQ number in the intConnectCode[] */

#define INT_CONNECT_CODE29    26 /* from the return address of intEnt() */

#ifdef __cplusplus
}
#endif

#endif	/* __INCasmX86_64h */
