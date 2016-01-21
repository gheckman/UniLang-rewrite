/* mti5kxHazards.h - assembler definitions header file */

/* Copyright 1999-2005, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,08feb09,pch  add HAZARD_NULL
01c,14sep05,rlg  SPR 110832 - fix the hazards
01b,25feb05,pes  Added copyright notice.
01a,07apr04,mem  Modified to handle mti5kx hazards
*/

/* These hazard macros are intended for use with MIPS architecture-
 * dependent assembly files which require handling hazards.
 * These macros support the MTI 5kx cores
 * This file is included by the asmMips.h file when the HAZARD_FILE macro
 * is defined using
 * #define HAZARD_FILE "mti5kxHazards.h"
 */

#ifndef __INCmti5kxHazardsh
#define __INCmti5kxHazardsh

/* Hazard macros */

#define HAZARD_TLB		ssnop; ssnop; ssnop
#define HAZARD_ERET		ssnop; ssnop
#define HAZARD_CP_READ		HAZARD_NULL	/* Fully interlocked on read */
#define HAZARD_CP_WRITE		ssnop; ssnop; ssnop
#define HAZARD_CACHE_TAG	ssnop
#define HAZARD_CACHE		ssnop; ssnop
#define HAZARD_INTERRUPT	ssnop; ssnop; ssnop

#endif /* __INCmti5kxHazardsh */
