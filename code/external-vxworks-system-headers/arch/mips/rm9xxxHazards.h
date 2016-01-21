/* rm9xxxHazards.h - assembler hazards definitions header file */

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
01a,14nov02,jmt  Modified to handle RM9xxx hazards
*/

/* These hazard macros are intended for use with MIPS architecture-
 * dependent assembly files which require handling hazards.
 * These macros support the PMC-Sierra RM9000 core
 * This file is included by the asmMips.h file when the HAZARD_FILE macro
 * is defined using
 * #define HAZARD_FILE <arch/mips/rm9xxxHazards.h>
 */

#ifndef __INCrm9xxxHazardsh
#define __INCrm9xxxHazardsh

/* Hazard macros */

#define CPU_CYCLES_FOUR         ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop
#define CPU_CYCLES_SEVEN        ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop; ssnop; ssnop; \
                                ssnop; ssnop

#define HAZARD_TLB       CPU_CYCLES_SEVEN
#define HAZARD_ERET      CPU_CYCLES_TWO
#define HAZARD_CP_READ   CPU_CYCLES_ONE
#define HAZARD_CP_WRITE  CPU_CYCLES_FOUR
#define HAZARD_CACHE_TAG CPU_CYCLES_ONE
#define HAZARD_CACHE     CPU_CYCLES_TWO
#define HAZARD_INTERRUPT CPU_CYCLES_TWO

#endif /* __INCrm9xxxHazardsh */

