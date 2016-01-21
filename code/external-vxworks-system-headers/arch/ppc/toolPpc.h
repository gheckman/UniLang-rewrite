/* toolPpc.h - tool dependent headers */

/*
 * Copyright (c) 1984-2008, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
02k,29nov11,h_k  added FRAMEHEADERSZ and PPC_PARAM_LIST_OFFSET macros.
02j,07apr08,to   added LOADPTR_SDA macro
02i,17mar08,h_k  added STOREVAR_SDA.
02h,13feb08,to   SDA macro for assembly code
02g,13dec07,to   enforce stack alignment for RTP
02f,13jul07,pch  handle case where assembly source file is built with
		 CPU=PPC32
02e,09jul07,pch  CQ#98192: definitions of _STACK_ALIGN_SIZE and
		 _ALLOC_ALIGN_SIZE should not be qualified by _ASMLANGUAGE
02d,05jul07,pch  CQ#83952: add missing () in gnu HI/LO/HIADJ definitions
02c,17aug05,pch  Add _CPU_STACK_ALIGN_SHIFT
02b,18mar04,rec  merge PPC970 T2 changes
02a,04oct04,mdo  Documentation fixes for apigen
01z,08jul04,yvp  Added _WRS_ARCH_USER_STACK_FRAME_EXTENSION.
01y,09jun04,pch  add support for PPC440 with hard FP
01x,25feb04,pch  PPC32 vn 2:  All PPC now using 16-byte stack alignment
01w,08oct03,pch  SPR 83570: Remove references to unsupported toolchain
01v,12dec02,pch  Add generic PPC32 support
01u,08nov02,mil  Added 16-byte stack alignment for PPC85XX.
01t,12nov01,yvp  Reverted to 8-byte alignment for non-PPC604 processors.
01s,30oct01,sn   removed Diab varargs
01r,25sep01,yvp  define _WRS_TEXT_SEG_ALIGN macro.
01q,08may01,pch  Add assembler abstractions (FUNC_EXPORT, FUNC_BEGIN, etc.)
01p,06apr01,max  To make all memory allocations 16-byte aligned
01o,30mar01,pcs  ADDED Altivec Register file set.
01n,22feb00,jgn  add GTEXT & GDATA macros
01m,05may99,jgn  make FRAMEBASESZ available for C code too
01l,22apr98,tam  SPR 20438, removed #if TRUE,FALSE usage 
01k,23dec97,dat  SPR 20104, fixed LOADPTR, LOADVAR macros
01j,21may96,tpr  added underscore in front of GNU_TOOL.
01i,22apr96,ms	 made GNU_TOOL the default
01h,29feb96,tpr  removed #define _SDA2_BASE_ _SDA_BASE_
01g,22jun95,caf  updated Diab Data support.
01f,21jun95,caf  updated Green Hills support.
01e,20apr95,yao  defined _ALLOC_ALIGN_SIZE.
01d,21mar95,caf  defined _STACK_ALIGN_SIZE.
01c,03feb95,caf  cleanup.
01b,15nov94,caf  changed name of file to toolPpc.h, added Green Hills support.
01a,25oct94,yao  written.
*/

#ifndef __INCtoolPpch
#define __INCtoolPpch

#ifdef __cplusplus
extern "C" {
#endif

#define	_PPC_USE_SDA		/* define this if using SDA */

#if	!defined(_DIAB_TOOL) && !defined(_GNU_TOOL)
#define	_GNU_TOOL
#endif

/* macros for stack frame */

/*
SVR4 Stack space allocation:

    Before Dynamic stack allocation

    +----------------------------------+
    |       Back Chain                 |
    |----------------------------------|
    |  Register save areas             |
    |----------------------------------|
    |  local,non-static variables      |
    |----------------------------------|
    |  parameter lists for callees     | (overloaded parameters with #)
    |----------------------------------|
    |      LR save word                |
    |----------------------------------|
SP=>|      Back chain                  |
    +----------------------------------+

    After Dynamic stack allocation

    +----------------------------------+
    |       Back Chain                 |
    |----------------------------------|
    |  Register save areas             |
    |----------------------------------|
    |  local,non-static variables      |
    |----------------------------------|
    |  Dynamic Allocation Area         | 16 byte stack alignment
    |----------------------------------|
    |  parameter lists for callees     |
    |----------------------------------|
    |      LR save word                |
    |----------------------------------|
SP=>|      Back chain                  |
    +----------------------------------+ 16 bytes stack alignment
*/

  /* Stack and Allocation alignment */

/*
 * While it is possible to use different stack alignments for different
 * PPC processors, current compilers use 16-byte alignment for all.
 */

#define _CPU_STACK_ALIGN_SIZE	16	/* stack alignment (for all PPC) */
#define	_CPU_STACK_ALIGN_SHIFT	4

#if	((CPU == PPC604) || (CPU == PPC85XX) || (CPU == PPC970)) /* Altivec, E500 EABI */
# define _CPU_ALLOC_ALIGN_SIZE	16	/* allocation alignment */
#elif	(CPU != PPC32)			/* for others, !defined for generic */
# define _CPU_ALLOC_ALIGN_SIZE	8	/* allocation alignment */
#endif	/* PPC604|PPC85XX|PPC970 : !PPC32 */

#define FRAMEHEADERSZ		8	/* stack frame header size */

/* minimum stack frame size */

#define FRAMEBASESZ	((FRAMEHEADERSZ + (_STACK_ALIGN_SIZE - 1)) & \
			 ~(_STACK_ALIGN_SIZE - 1))

/* parameter list offset */

#define PPC_PARAM_LIST_OFFSET	FRAMEHEADERSZ

/*
*
* _WRS_ARCH_USER_STACK_FRAME_EXTENSION - creating words on the stack for the 
*                                        back chain word and the LR register.
*
* This macro is used in creating the initial stack frame for an RTP's initial 
* task. It performs the extra steps of creating words on the stack for the 
* back chain word and the LR register. Both these locations are set to 0 to 
* prevent stack traces and debuggers from looking ahead.
*
* NOMANUAL
*/

#define _WRS_ARCH_USER_STACK_FRAME_EXTENSION(sp)			     \
    do									     \
	{								     \
	(sp) = (char *) STACK_ROUND_DOWN ((sp) - 2*sizeof(int *));	     \
	*((int *)(sp)) = (int)0;					     \
	*((int *)((sp)+4)) = (int)0;					     \
	} while ((0))


#ifdef	_ASMLANGUAGE

/* register definition */

/* volatile registers that are not saved across subroutine calls */

#define p0	r3	/* argument register, volatile */
#define p1	r4	/* argument register, volatile */
#define p2	r5	/* argument register, volatile */
#define p3	r6	/* argument register, volatile */
#define p4	r7	/* argument register, volatile */
#define p5	r8	/* argument register, volatile */
#define p6	r9	/* argument register, volatile */
#define p7	r10	/* argument register, volatile */
#define glr0	r0	/* prologs(PO,EABI), epilogs, glink routines(EABI) /
			 * language specific purpose(SVR4), volatile */
#define glr1	r11	/* prologs, epilogs, as Pascal environment pointer(EABI)
			 * language specific purpose (SVR4)
			 * calls by pointer, as Pascal environment(PO), 
			 * volatile */
#define glr2	r12	/* prologs, epilogs, glink routines, calls by 
			 * pointer(EABI), language specific purpose (SVR4),
			 * glue code, exception handling (PO), volatile */
#define retval0	r3	/* return register 0, volatile */
#define retval1	r4	/* return register 1, volatile */


/* non-volatile and dedicated registers saved across subroutine calls */

#define	sp	r1	/* stack pointer, dedicated */

#define t0	r14	/* temporary registers, non-volatile */
#define t1	r15	/* temporary registers, non-volatile */
#define t2	r16	/* temporary registers, non-volatile */
#define t3	r17	/* temporary registers, non-volatile */
#define t4	r18	/* temporary registers, non-volatile */
#define t5	r19	/* temporary registers, non-volatile */
#define t6	r20	/* temporary registers, non-volatile */
#define t7	r21	/* temporary registers, non-volatile */
#define t8	r22	/* temporary registers, non-volatile */
#define t9	r23	/* temporary registers, non-volatile */
#define t10	r24	/* temporary registers, non-volatile */
#define t11	r25	/* temporary registers, non-volatile */
#define t12	r26	/* temporary registers, non-volatile */
#define t13	r27	/* temporary registers, non-volatile */
#define t14	r28	/* temporary registers, non-volatile */
#define t15	r29	/* temporary registers, non-volatile */
#define t16	r30	/* temporary registers, non-volatile */
#define t17	r31	/* temporary registers, non-volatile */

#ifdef	_GNU_TOOL

/* GP register names */

#define r0	0
#define r1	1
#define r2	2
#define r3	3
#define r4	4
#define r5	5
#define r6	6
#define r7	7
#define r8	8
#define r9	9
#define r10	10
#define r11	11
#define r12	12
#define r13	13
#define r14	14
#define r15	15
#define r16	16
#define r17	17
#define r18	18
#define r19	19
#define r20	20
#define r21	21
#define r22	22
#define r23	23
#define r24	24
#define r25	25
#define r26	26
#define r27	27
#define r28	28
#define r29	29
#define r30	30
#define r31	31

#ifdef	_PPC_MSR_FP
/* FP register names */

#define	fp0	0
#define	fr0	0
#define	f0	0
#define	fp1	1
#define	fr1	1
#define	f1	1
#define	fp2	2
#define	fr2	2
#define	f2	2
#define	fp3	3
#define	fr3	3
#define	f3	3
#define	fp4	4
#define	fr4	4
#define	f4	4
#define	fp5	5
#define	fr5	5
#define	f5	5
#define	fp6	6
#define	fr6	6
#define	f6	6
#define	fp7	7
#define	fr7	7
#define	f7	7
#define	fp8	8
#define	fr8	8
#define	f8	8
#define	fp9	9
#define	fr9	9
#define	f9	9
#define	fp10	10
#define	fr10	10
#define	f10	10
#define	fp11	11
#define	fr11	11
#define	f11	11
#define	fp12	12
#define	fr12	12
#define	f12	12
#define	fp13	13
#define	fr13	13
#define	f13	13
#define	fp14	14
#define	fr14	14
#define	f14	14
#define	fp15	15
#define	fr15	15
#define	f15	15
#define	fp16	16
#define	fr16	16
#define	f16	16
#define	fp17	17
#define	fr17	17
#define	f17	17
#define	fp18	18
#define	fr18	18
#define	f18	18
#define	fp19	19
#define	fr19	19
#define	f19	19
#define	fp20	20
#define	fr20	20
#define	f20	20
#define	fp21	21
#define	fr21	21
#define	f21	21
#define	fp22	22
#define	fr22	22
#define	f22	22
#define	fp23	23
#define	fr23	23
#define	f23	23
#define	fp24	24
#define	fr24	24
#define	f24	24
#define	fp25	25
#define	fr25	25
#define	f25	25
#define	fp26	26
#define	fr26	26
#define	f26	26
#define	fp27	27
#define	fr27	27
#define	f27	27
#define	fp28	28
#define	fr28	28
#define	f28	28
#define	fp29	29
#define	fr29	29
#define	f29	29
#define	fp30	30
#define	fr30	30
#define	f30	30
#define	fp31	31
#define	fr31	31
#define	f31	31
#endif	/* _PPC_MSR_FP */

/* Condition register names */

#define cr0	0
#define cr1	1
#define cr2	2
#define cr3	3
#define cr4	4
#define cr5	5
#define cr6	6
#define cr7	7

/* Macro for hiadjust and lo */
#define HIADJ(arg)	(arg)@ha
#define HI(arg)		(arg)@h
#define LO(arg)		(arg)@l

#define SDA21(arg)	(arg)@sda21(0)

#ifdef _PPC_MSR_VEC

/* ALTIVEC Vector register names */

#define v0      0
#define v1      1
#define v2      2
#define v3      3
#define v4      4
#define v5      5
#define v6      6
#define v7      7
#define v8      8
#define v9      9
#define v10     10
#define v11     11
#define v12     12
#define v13     13
#define v14     14
#define v15     15
#define v16     16
#define v17     17
#define v18     18
#define v19     19
#define v20     20
#define v21     21
#define v22     22
#define v23     23
#define v24     24
#define v25     25
#define v26     26
#define v27     27
#define v28     28
#define v29     29
#define v30     30
#define v31     31

#endif /* _PPC_MSR_VEC */

#endif	/* _GNU_TOOL */

#ifdef	_DIAB_TOOL

#ifdef	_PPC_MSR_FP
/* Diab Data FP register names */

#define	fp0	f0
#define	fr0	f0
#define	fp1	f1
#define	fr1	f1
#define	fp2	f2
#define	fr2	f2
#define	fp3	f3
#define	fr3	f3
#define	fp4	f4
#define	fr4	f4
#define	fp5	f5
#define	fr5	f5
#define	fp6	f6
#define	fr6	f6
#define	fp7	f7
#define	fr7	f7
#define	fp8	f8
#define	fr8	f8
#define	fp9	f9
#define	fr9	f9
#define	fp10	f10
#define	fr10	f10
#define	fp11	f11
#define	fr11	f11
#define	fp12	f12
#define	fr12	f12
#define	fp13	f13
#define	fr13	f13
#define	fp14	f14
#define	fr14	f14
#define	fp15	f15
#define	fr15	f15
#define	fp16	f16
#define	fr16	f16
#define	fp17	f17
#define	fr17	f17
#define	fp18	f18
#define	fr18	f18
#define	fp19	f19
#define	fr19	f19
#define	fp20	f20
#define	fr20	f20
#define	fp21	f21
#define	fr21	f21
#define	fp22	f22
#define	fr22	f22
#define	fp23	f23
#define	fr23	f23
#define	fp24	f24
#define	fr24	f24
#define	fp25	f25
#define	fr25	f25
#define	fp26	f26
#define	fr26	f26
#define	fp27	f27
#define	fr27	f27
#define	fp28	f28
#define	fr28	f28
#define	fp29	f29
#define	fr29	f29
#define	fp30	f30
#define	fr30	f30
#define	fp31	f31
#define	fr31	f31
#endif	/* _PPC_MSR_FP */

/* Macro for hiadjust and lo */
#define HIADJ(arg)	%hiadj(arg)
#define HI(arg)		%hi(arg)
#define LO(arg)		%lo(arg)

#define SDA21(arg)	(arg)@sdarx(r0)

#endif	/* _DIAB_TOOL */

/*
 * define r2 as VTOC/GOT(EABI), system use(SVR4)/TOC/GOT(PO),dedicated. 
 * define r13 as CTOC/GOT anchor pointer, dedicated (EABI), non-volatile
 * register (SVR4, PO) 
 */

#define FUNC(func)	    func
#define FUNC_LABEL(func)    func:

#define FUNC_DECL(range, func)
#define VAR_DECL(var)   var
#define VAR(var)        var(r0)

/*
 * These macros are used to declare assembly language symbols that need
 * to be typed properly(func or data) to be visible to the OMF tool.  
 * So that the build tool could mark them as an entry point to be linked
 * by another PD.
 */

#define GTEXT(sym) FUNC(sym) ;  .type   FUNC(sym),@function
#define GDATA(sym) VAR_DECL(sym) ;  .type   VAR_DECL(sym),@object

/* Introduced to abstract assembler idiosyncrasies */
#define	FUNC_EXPORT(func)	.globl	GTEXT(func)
#define	DATA_EXPORT(var)	.globl	GDATA(var)
#define	FUNC_IMPORT(func)	.extern	FUNC(func)
#define	DATA_IMPORT(var)	.extern	VAR_DECL(var)
#define	FUNC_BEGIN(func)	FUNC_LABEL(func)
#define	FUNC_END(func)		.size	FUNC(func), . - FUNC(func)

  /* Macro for beginning a text segment */
#define _WRS_TEXT_SEG_START \
	.text ; .balign _PPC_TEXT_SEG_ALIGN

#define	FRAMESZ(nregs)	\
    	  ROUND_UP((FRAMEBASESZ + nregs * _PPC_REG_SIZE), _STACK_ALIGN_SIZE)

#define	LOADPTR(reg,const32) \
	  addis reg,r0,HIADJ(const32); addi reg,reg,LO(const32)

#define	LOADVAR(reg,const32) \
	  addis reg,r0,HIADJ(const32); lwz reg,LO(const32)(reg)

#ifdef	_PPC_USE_SDA

#define	LOADPTR_SDA(reg,const32) \
	la	reg,SDA21(const32)

#define	LOADVAR_SDA(reg,const32) \
	lwz	reg,SDA21(const32)

#define	STOREVAR_SDA(v,sc,const32) \
	stw	v,SDA21(const32)

#else	/* _PPC_USE_SDA */

#define	LOADPTR_SDA(reg,const32)	LOADPTR(reg,const32)

#define	LOADVAR_SDA(reg,const32)	LOADVAR(reg,const32)

#define	STOREVAR_SDA(v,reg,const32) \
	addis reg,r0,HIADJ(const32); stw v,LO(const32)(reg)

#endif	/* _PPC_USE_SDA */


#else	/* _ASMLANGUAGE */

#define	FUNCREF(func)	func

#endif	/* _ASMLANGUAGE */

/*
 * Use constant sizes if known (when building for a specific CPU type)
 * else fetch from a global variable (when building for generic PPC32).
 * The latter is not supported, and should not be needed, for .s files.
 */

#ifdef	_CPU_STACK_ALIGN_SIZE
#define	_STACK_ALIGN_SIZE	_CPU_STACK_ALIGN_SIZE
#else	/* _CPU_STACK_ALIGN_SIZE */
# ifndef _ASMLANGUAGE
#define	_STACK_ALIGN_SIZE	_ppcStackAlignSize
extern	int	_ppcStackAlignSize;
# endif	/* _ASMLANGUAGE */
#endif	/* _CPU_STACK_ALIGN_SIZE */

#ifdef	_CPU_ALLOC_ALIGN_SIZE
#define	_ALLOC_ALIGN_SIZE	_CPU_ALLOC_ALIGN_SIZE
#else	/* _CPU_ALLOC_ALIGN_SIZE */
# ifndef _ASMLANGUAGE
#define	_ALLOC_ALIGN_SIZE	_ppcAllocationQuantumSize
extern	int	_ppcAllocationQuantumSize;
# endif	/* _ASMLANGUAGE */
#endif	/* _CPU_ALLOC_ALIGN_SIZE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtoolPpch */
