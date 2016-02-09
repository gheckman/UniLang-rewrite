/* setjmp.h - setjmp/longjmp header */

/*
 * Copyright (c) 1984-2004, 2006, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
02o,14feb12,zl   jmp_buf to use fully qualified types (WIND00311945)
02n,29apr10,pad  Moved extern C statement after include statements.
02m,21dec06,aeg  added _WRS_FUNC_NORETURN attribute to longjmp/siglongjmp.
02l,12jan06,gls  updated to support 64 bit sigset_t
02k,16feb04,m_s  added excCnt to jump buffer
02j,09jul96,ms   fixed prototype of sigsetjmp (SPR 7002).
02i,27dec95,mem  removed macros for VxSim hppa
02h,27mar95,kkk  fixed multiple definition of jmp_buf & sigjmp_buf (SPR 4051)
02g,31mar94,cd   modified jmp_buf and sigjmp_buf structures for use
		 with 32/64 bit processors.
02g,12may94,ms   added macros for VxSim hppa
02f,22sep92,rrr  added support for c++
02e,31aug92,rrr  added setjmp
02d,10jul92,rrr  set it up to use the new signal code. One more pass is needed
                 to make it ANSI.
02c,09jul92,jwt  removed structure version of jmp_buf for SPARC - merge error.
02b,09jul92,rrr  fixed sparc from having two typedefs for jmp_buf
02a,04jul92,jcf  cleaned up.
01l,26may92,rrr  the tree shuffle
01k,09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
01j,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01i,20jul91,jwt  modified jmp_buf for SPARC; added #ifndef _ASMLANGUAGE.
01h,02aug91,ajm  added defines and macros for MIPS architecture.
01g,29apr91,hdn  added defines and macros for TRON architecture.
01f,20apr91,del  added I960 specifics.
01e,19oct90,shl  changed IMPORT to extern for ANSI compatibility,
		 fixed wrong type definition for longjmp().
01d,05oct90,shl  added ANSI function prototypes.
		 added copyright notice.
                 made #endif ANSI style.
01c,25aug88,ecs  added SPARC version of jmp_buf.
01b,01jul88,rdc  changed order of stuff in jmp_buf.
01a,22jun88,dnw  written
*/

#ifndef __INCsetjmph
#define __INCsetjmph

#include <regs.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _jmp_buf
    {
    REG_SET          reg;		/* saved task register set */
    int              excCnt;		/* saved tasks exception count */
    BOOL             sigmaskIsValid;	/* TRUE when sigmask is saved */
    sigset_t         sigmask;		/* saved task signal mask */
    struct windTcb * pTcb;		/* task identifier for verification */
    } jmp_buf[1];

/*
 * sigjmp_buf is identical in content to jmp_buf. The distinct structure
 * definition is maintained for legacy reasons; Also note that this structure 
 * uses "regs" instead of "reg".
 */

typedef struct _sigjmp_buf
    {
    REG_SET          regs;		/* saved task register set */
    int              excCnt;		/* saved tasks exception count */
    BOOL             sigmaskIsValid;	/* TRUE when sigmask is saved */
    sigset_t         sigmask;		/* saved task signal mask */
    struct windTcb * pTcb;		/* task identifier for verification */
    } sigjmp_buf[1];

/* function declarations */

extern int	setjmp 		(jmp_buf __env);
extern int	sigsetjmp 	(sigjmp_buf __env, int __savemask);

extern _WRS_FUNC_NORETURN
	void 	longjmp 	(jmp_buf __env, int __val);

extern _WRS_FUNC_NORETURN
	void 	siglongjmp 	(sigjmp_buf __env, int __val);

#ifdef __cplusplus
}
#endif

#endif /* __INCsetjmph */
