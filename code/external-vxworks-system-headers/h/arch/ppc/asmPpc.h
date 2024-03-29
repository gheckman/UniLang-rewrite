/* asmPpc.h - PowerPC assembler definitions header file */

/* 
 * Copyright 1984-2007, 2013 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01x,28feb13,h_k  added T4_ERRATUM_CPU6198 for e6500.
01w,05oct07,kk   added macros to support SHL GOT table access
01v,19jul06,pch  move kernel-only definitions to kernel-only archPpc.h file
01v,06jun06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU to _VX_CPU.
01u,01nov04,pch  SPR 83004: move SPRG[4-7] definitions from asmPpc.h to ppc405.h
01t,10dec03,pch  TEMPORARY HACK for msync/mbar in PPC440gnu
01s,03dec03,jtp  Add MMU_MASK operation
01r,09sep03,yvp  Removed definition of the SYSCALL_PROLOG macro.
01q,03sep03,yvp  Added system call trap stub definition.
01p,12dec02,pch  Add generic PPC32 support
01o,26mar02,pcs  Add defines for I & D BAT's 4-7.
01n,02may01,pch  Documentation cleanup
01m,25oct00,s_m  renamed PPC405 cpu types
01l,12jun00,alp  Added PPC405 Support
01k,18mar97,tam  made INT_MASK definition conditional.
01j,08apr96,tpr  move implementation specific definition in ppcXXX.h.
01i,04mar96,tam  added some SPR definitions for the PPC403.
01h,26feb96,kkk  added HID0 for PPC601.
01g,14feb96,tpr  added PPC604 support.
01f,09feb95,yao  added RFCI, MTBESR_P0 macro for PPC403.
01e,30jan95,yao  added DBCR for PPC403.  fixed mtdcr macros for PPC403.
01d,06jan95,vin  corrected HID0 (was 8, now 1008).
01c,15nov94,caf  moved register defines to toolPpc.h.
01b,04nov94,yao  changed PPC403GA to PPC403.  moved tool related macros
		 to tools.h.
01a,25may94,yao  written.
*/

#ifndef __INCasmPpch
#define __INCasmPpch

#ifdef __cplusplus
extern "C" {
#endif

/* TEMPORARY HACK for msync/mbar in PPC440gnu */
#if	(_VX_CPU == _VX_PPC440 && defined(_GNU_TOOL))
#define	msync	sync
#define	mbar	eieio
#endif

/* special purpose register encoding */

#define XER		1	/* external exception register */
#define LR		8	/* link register (return address) */
#define	CTR		9	/* counter register */

#define	BO_dCTR_NZERO_AND_NOT	0
#define BO_dCTR_ZERO_AND_NOT	2
#define BO_IF_NOT		4
#define BO_dCTR_ZERO_AND	10
#define BO_IF			12
#define BO_dCTR_NZERO		16
#define BO_dCTR_ZERO		18
#define BO_ALWAYS		20
#define CR0_LT			8

/* macros for globals via the Global Offset table for SHLs in assembly code */

#ifdef	_WRS_KERNEL

# if defined(T4_ERRATUM_CPU6198) && defined(_WRS_CONFIG_SMP)
# define _PPC_KERNEL_MTMSR(msr, scr, label)				      \
	mtspr	MCSRR1, msr;	/* put new MSR into machine check SSR */      \
	lis	scr, HI(label##_mtmsrwa);      /* get address of */	      \
	ori	scr, scr, LO(label##_mtmsrwa); /* where to rfmci to */	      \
	mtspr	MCSRR0, scr;	/* put into MCSRR0 */			      \
	rfmci;			/* perform change to MSR */		      \
label##_mtmsrwa:		/* the workaround rfmci always goes here */

# define _PPC_KERNEL_MTMSR_WITH_BLR(msr, scr)				      \
	mtspr	MCSRR1, msr;	/* put new MSR into machine check SSR */      \
	mfspr	scr, LR;	/* get address of where to rfmci to */	      \
	mtspr	MCSRR0, scr;	/* put into MCSRR0 */			      \
	rfmci;			/* perform change to MSR */		      \
				/* the workaround rfmci returns to the caller \
				 * directly, or goes to the next instruction  \
				 * if an interrupt is raised at the rfmci     \
				 */					      \
	blr
# else
# define _PPC_KERNEL_MTMSR(msr, scr, label)				      \
	mtmsr	msr

# define _PPC_KERNEL_MTMSR_WITH_BLR(msr, scr)				      \
	mtmsr	msr;							      \
	blr
# endif	/* T4_ERRATUM_CPU6198 && _WRS_CONFIG_SMP */

#else

# ifdef	__SO_PICABIRTP__
/*
 * Shared-library globals must be accessed via the Global Offset
 * Table for the current instance (attachment) of the shared library.
 * Used by vxAtomicALib.s.
 */
#define	_PPC_RTP_GLOBAL_GET(globalName, reg)				     \
	lis	reg, HIADJ(__GOTT_BASE__);				     \
	lwz	reg, LO(__GOTT_BASE__)(reg);	/* reg = &GOT[] */	     \
	lwz	reg, __GOTT_INDEX__(reg);	/* reg = &GOT[myInstance] */ \
	lwz	reg, globalName@got(reg);	/* reg = &globalName */	     \
	lwz	reg, 0(reg)			/* reg = globalName */
# else	/* __SO_PICABIRTP__ */
#define	_PPC_RTP_GLOBAL_GET(globalName, reg)	\
	lis	reg, HIADJ(globalName);		\
	lwz	reg, LO(globalName)(reg);
# endif	/* __SO_PICABIRTP__ */

#endif	/* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCasmPpch */
