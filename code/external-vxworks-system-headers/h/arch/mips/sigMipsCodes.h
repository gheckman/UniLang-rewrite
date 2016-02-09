/* sigMipsCodes.h - Mips codes sent to signal handlers */

/* Copyright 1984-2001, 2010 Wind River Systems, Inc. */

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
01f,29apr10,pad  Moved extern C statement after include statements.
01e,16jul01,ros  add CofE comment
01d,18apr96,rml  add definitions for R4650 specific exception types
01c,10feb93,rdc  fixed ILL_COPROC_UNUSABLE macro.
01b,22sep92,rrr  added support for c++
01a,31aug92,rrr  written
*/

#ifndef __INCsigMipsCodesh
#define __INCsigMipsCodesh

#include "iv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUS_IBND		IV_IBND_VEC 		/* R4650: instr bound */
#define BUS_DBND		IV_DBND_VEC		/* R4650: data bound */
#define BUS_TLBMOD		IV_TLBMOD_VEC		/* tlb mod */
#define BUS_TLBL		IV_TLBL_VEC		/* tlb load */
#define BUS_TLBS		IV_TLBS_VEC		/* tlb store */
#define BUS_ADEL		IV_ADEL_VEC		/* address load */
#define BUS_ADES		IV_ADES_VEC		/* address store */
#define SEGV_IBUS		IV_IBUS_VEC		/* instr. bus error */
#define SEGV_DBUS		IV_DBUS_VEC		/* data bus error */
#define TRAP_SYSCALL		IV_SYSCALL_VEC		/* system call */
#define TRAP_BP			IV_BP_VEC		/* break point */
#define ILL_ILLINSTR_FAULT	IV_RESVDINST_VEC	/* rsvd instruction */
#define ILL_COPROC_UNUSABLE	IV_CPU_VEC		/* coproc unusable */
#define FPE_FPA_UIO		IV_FPA_UNIMP_VEC	/* unimplemented op */
#define FPE_FLTNAN_TRAP		IV_FPA_INV_VEC		/* invalid op */
#define FPE_FLTDIV_TRAP		IV_FPA_DIV0_VEC		/* FPA div by zero */
#define FPE_FLTOVF_TRAP		IV_FPA_OVF_VEC		/* FPA overflow */
#define FPE_FLTUND_TRAP		IV_FPA_UFL_VEC		/* FPA underflow */
#define FPE_FLTINEX_TRAP	IV_FPA_PREC_VEC		/* FPA inexact */

#ifdef __cplusplus
}
#endif

#endif /* __INCsigMipsCodesh */
