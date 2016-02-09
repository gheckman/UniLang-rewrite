/* asmI86.h - i80x86 assembler definitions header file */

/*
 * Copyright (c) 1992,1993.1998,2001,2003,2006,2008
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,26mar08,dbt  Added FUNC_BEGIN & FUNC_END macros (Defect WIND00066731)
01n,21jul06,scm  Move SMP macros to private header.
01m,13jul06,scm  correct for UNI mode RTP/OSM support...
01l,07jul06,scm  update macros for smp/uni...
01k,28jun06,scm  SMP GDT support macros added.
01j,06jun06,scm  Add SMP support.
01i,17nov05,zmm  Use .type directive to declare assembly language symbols that
                 weren't typed properly by GNU assembler. SPR 114490.
01h,04may04,dbt  Added ARG8-12 and SP_ARG8-12.
01g,17nov03,jb   Adding additional ARG defines
01f,01nov01,hdn  added ARG8 and SP_ARG8
01e,01oct01,pad  Turn off the underscore prepending to assembly routines.
01d,14aug01,hdn  imported FUNC/FUNC_LABEL GTEXT/GDATA macros from T31 ver 01i
01c,28aug98,hdn  added INT_CONNECT_CODE29 for intEnt().
01b,07jun93,hdn  added support for c++
01a,28feb92,hdn  written based on TRON, 68k version.
*/

#ifndef	__INCasmI86h
#define	__INCasmI86h

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

/* fp offsets to arguments */

#define ARG1	8
#define ARG1W	10
#define ARG2	12
#define ARG2W	14
#define ARG3	16
#define ARG3W	18
#define ARG4	20
#define ARG5	24
#define ARG6	28
#define ARG7	32
#define ARG8	36
#define ARG9	40
#define ARG10	44
#define ARG11	48
#define ARG12	52

#define DARG1	8		/* double arguments */
#define	DARG1L	12
#define DARG2	16
#define DARG2L	20
#define DARG3	24
#define DARG3L	28
#define DARG4	32
#define DARG4L	36

/* sp offsets to arguments */

#define SP_ARG0		0
#define SP_ARG1		4
#define SP_ARG1W	6
#define SP_ARG2		8
#define SP_ARG2W	10
#define SP_ARG3		12
#define SP_ARG3W	14
#define SP_ARG4		16
#define SP_ARG5		20
#define SP_ARG6		24
#define SP_ARG7		28
#define SP_ARG8		32
#define SP_ARG9		36
#define SP_ARG10	40
#define SP_ARG11	44
#define SP_ARG12	48

/* offset to the IRQ number in the intConnectCode[] */

#define INT_CONNECT_CODE29    24 /* from the return address of intEnt() */

#ifdef __cplusplus
}
#endif

#endif	/* __INCasmI86h */
