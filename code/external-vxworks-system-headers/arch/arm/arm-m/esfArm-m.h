/* esfArm-m.h - ARM exception stack frames */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,10may12,j_b  fix tabs/spacing
01b,03may12,j_b  replace "-" in filename include macro
01a,03apr12,j_b  created from target/h/arch/arm/esfArm.f version 01b
*/

#ifndef __INCesfArm_mh
#define __INCesfArm_mh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* 
 * The Exception Stack Frame
 * On ARMv7-M, this is faked by a stub and the pointer
 * passed back points to the PC and PSR at the end of the
 * register structure. If that changes, so must this.
 *
 * I.E., REG_SET struct & ESF struct 'overlap' on last 4
 * elements of REG_SET (pc, psr, primask and basepri).
 */

typedef struct
    {
    INSTR *pc;		/* program counter */
    ULONG psr;		/* combined A/I/E PSR */
    ULONG basepri;	/* BASEPRI */
    ULONG demcr;	/* MON_STEP in DEMCR */
    ULONG primask;	/* PRIMASK */
    ULONG faultmask;	/* FAULTMASK */
    ULONG control;	/* CONTROL */
    UINT32 vecNum;	/* exception number */
    } ESF;

#endif /* _ASMLANGUAGE */


#ifdef __cplusplus
}
#endif

#endif /* __INCesfArm_mh */
