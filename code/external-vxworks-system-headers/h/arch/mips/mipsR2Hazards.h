/* mipsR2Hazards.h - assembler definitions header file */

/* Copyright  2005-2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,12jan06,pes  R2 ISA support completed, remove EHB macro from HAZARD
                 macros. (EHB macro definition retained for backward
                 compatibility.)
01c,11apr05,d_c  rename mti24kxHazards.h to mipsR2Hazards.h
01b,24feb05,pes  Modified to use the 'ehb' instruction, either by
		 macro or actual instruction (if supported by assembler)
01a,16feb05,pes  Created from mti5kxHazards.h
*/

/* These hazard macros are intended for use with MIPS architecture-
 * dependent assembly files which require handling hazards.
 * These macros support release 2 ISA cores
 * This file is included by the asmMips.h file when the HAZARD_FILE macro
 * is defined using
 * #define HAZARD_FILE <mipsR2Hazards.h>
 */

#ifndef __INCmipsR2Hazardsh
#define __INCmipsR2Hazardsh

/* Hazard macros */
/* Keep macro definition for backward compatability */
#define EHB	ehb

#define HAZARD_TLB		ehb
#define HAZARD_ERET		ehb
#define HAZARD_CP_READ		ehb
#define HAZARD_CP_WRITE		ehb
#define HAZARD_CACHE_TAG	ehb
#define HAZARD_CACHE		ehb
#define HAZARD_INTERRUPT	ehb

#endif /* __INCmipsR2Hazardsh */

