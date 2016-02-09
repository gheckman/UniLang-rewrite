/* ivMips.h - interrupt vectors for MIPS architecture CPUs */

/* Copyright 1990-1993, 1996, 1999, 2001, 2004 Wind River Systems, Inc. */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01n,14oct04,pes  Correct copyright notice, add definition for Machine
                 Check vector
01m,16jul01,ros  add CofE comment
01l,10sep99,myz  added CW4000_16 support.
01k,12jul99,alp  added CW4000 support
01k,19jan99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
01j,13jul96,kkk  added R4650 CPU type definitions
01i,18apr96,rml  added definitions for R4650 specific exceptions 
01h,18oct93,cd   added R4000 support.
01g,29apr93,caf  changed INUM_TO_IVEC to return VOIDFUNCPTR * for intConnect().
01f,22sep92,rrr  added support for c++
01e,03jun92,ajm  merged 5.0.5
01d,26may92,rrr  the tree shuffle
01c,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
01b,20dec90,ajm  reordered VME interrupt definitions
01a,20apr90,ajm  defined vector defintions for MIPS R3000.
*/

#ifndef __INCivMipsh
#define __INCivMipsh

#ifdef __cplusplus
extern "C" {
#endif

/* macros to convert interrupt vectors <-> interrupt numbers */

#define IVEC_TO_INUM(intVec)	((int) (intVec) >> 2)
#define INUM_TO_IVEC(intNum)	((VOIDFUNCPTR *) ((intNum) << 2))


/* vector numbers of specific MIPS exceptions */

#define IV_LOW_VEC              0       /* lowest vector initialized    */
#define IV_TLBMOD_VEC           1       /* tlb mod vector               */
#define IV_TLBL_VEC             2       /* tlb load vector              */
#define IV_TLBS_VEC             3       /* tlb store vector             */
#define IV_ADEL_VEC             4       /* address load vector          */
#define IV_ADES_VEC             5       /* address store vector         */
#define IV_IBUS_VEC             6       /* instr. bus error vector      */
#define IV_DBUS_VEC             7       /* data bus error vector        */
#define IV_SYSCALL_VEC          8       /* system call vector           */
#define IV_BP_VEC               9       /* break point vector           */
#define IV_RESVDINST_VEC        10      /* rsvd instruction vector      */
#define IV_CPU_VEC              11      /* coprocessor unusable vector  */
#define IV_OVF_VEC              12      /* overflow vector              */
#define IV_TRAP_VEC             13      /* trap vector                  */
#define IV_VCEI_VEC             14      /* virtual coherency inst. vec  */
#define IV_FPE_VEC              15      /* floating point vector        */

#define IV_RESVD16_VEC          16      /* reserved entry               */
#define IV_RESVD17_VEC          17      /* reserved entry               */
#define IV_RESVD18_VEC          18      /* reserved entry               */
#define IV_RESVD19_VEC          19      /* reserved entry               */
#define IV_RESVD20_VEC          20      /* reserved entry               */
#define IV_RESVD21_VEC          21      /* reserved entry               */
#define IV_RESVD22_VEC          22      /* reserved entry               */
#define IV_WATCH_VEC            23      /* watchpoint vector            */
#define IV_MCHECK_VEC		24      /* machine check                */
#define IV_RESVD25_VEC          25      /* reserved entry               */
#define IV_RESVD26_VEC          26      /* reserved entry               */
#define IV_RESVD27_VEC          27      /* reserved entry               */
#define IV_RESVD28_VEC          28      /* reserved entry               */
#define IV_RESVD29_VEC          29      /* reserved entry               */
#define IV_RESVD30_VEC          30      /* reserved entry               */
#define IV_VCED_VEC             31      /* virtual coherency data vec   */
#define IV_SWTRAP0_VEC          32      /* software trap 0              */
#define IV_SWTRAP1_VEC          33      /* software trap 1              */
#define IV_FPA_UNIMP_VEC        54      /* unimplemented FPA oper       */
#define IV_FPA_INV_VEC          55      /* invalid FPA operation        */
#define IV_FPA_DIV0_VEC         56      /* FPA div by zero              */
#define IV_FPA_OVF_VEC          57      /* FPA overflow exception       */
#define IV_FPA_UFL_VEC          58      /* FPA underflow exception      */
#define IV_FPA_PREC_VEC         59      /* FPA inexact operation        */
#define IV_BUS_ERROR_VEC        60      /* bus error vector             */
#define USER_VEC_START          32      /* start of user interrupt vectors */
#define LOW_VEC                 32      /* lowest autovector initialized */
#define HIGH_VEC                255     /* highest  autovector initialized */
#define IV_FPA_BASE_VEC         IV_FPA_UNIMP_VEC


#ifdef __cplusplus
}
#endif

#endif /* __INCivMipsh */





