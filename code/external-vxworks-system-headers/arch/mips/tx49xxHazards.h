/* tx49xxHazards.h - assembler hazards definitions header file */

/* Copyright 1999-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,13sep05,rlg  Modified to handle tx49xx hazards
*/

/* These hazard macros are intended for use with MIPS architecture-
 * dependent assembly files which require handling hazards.
 * These macros support the tx4938 core
 * This file is included by the asmMips.h file when the HAZARD_FILE macro
 * is defined using
 * #define HAZARD_FILE <arch/mips/tx49xxHazards.h>
 */

#ifndef __INCtx49xxHazardsh
#define __INCtx49xxHazardsh

#define SINGLE_ISSUE 0
#define DUAL_ISSUE   1
#define CPU_CYCLES              DUAL_ISSUE

/* Using the issue mechanism definitions above, the MIPS CPU cycles
 * are defined below.
 */

#define ssnop           .word 0x00000040

/* Hazard macros */
#define HAZARD_TLB       ssnop; ssnop; ssnop; ssnop; sync
#define HAZARD_ERET      ssnop; ssnop; ssnop; ssnop
#define HAZARD_CP_READ   ssnop; ssnop
#define HAZARD_CP_WRITE  ssnop; ssnop; ssnop; ssnop
#define HAZARD_CACHE_TAG ssnop; ssnop
#define HAZARD_CACHE     ssnop; ssnop; ssnop; ssnop
#define HAZARD_INTERRUPT ssnop; ssnop; ssnop; ssnop

#endif /* __INCtx49xxHazardsh */

