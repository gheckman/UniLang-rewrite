/*	Definition module : elf_arm.h

	Copyright 2000 Diab Data, Inc.

	Description :
	elf_arm.h standard header file used by ld, ar, & as

	History :
	When	Who	What
	000203	sandeep	Initial
*/

/**************	Exported data, types and macros	*****************/

/*
 * Relocation types for ARM Family (ABI)
 */


#define R_ARM_FIRST		0
#define R_ARM_NONE		0
#define R_ARM_PC24		1
#define R_ARM_ABS32             2
#define R_ARM_REL32             3
#define R_ARM_PC13              4
#define R_ARM_ABS16             5
#define R_ARM_ABS12             6
#define R_ARM_THM_ABS5          7
#define R_ARM_ABS8              8
#define R_ARM_SBREL32           9
#define R_ARM_THM_PC22          10
#define R_ARM_THM_PC8           11
#define R_ARM_AMP_VCALL9        12
#define R_ARM_SWI24             13
#define R_ARM_THM_SWI8          14
#define R_ARM_XPC25             15
#define R_ARM_THM_XPC22         16
#define R_ARM_LAST		17

#define R_ARM_TFIRST		0
#define R_ARM_N			(R_ARM_LAST-R_ARM_TFIRST)


#define R_ARM_DIAB_FIRST	17
#define R_ARM_DIAB_ADDR0	17
#define R_ARM_DIAB_OVERRIDE0	18
#define R_ARM_DIAB_VTBL32	19
#define	R_ARM_COPY		20
#define	R_ARM_GLOB_DAT	21
#define	R_ARM_JUMP_SLOT	22
#define R_ARM_RELATIVE	23
#define R_ARM_GOTOFF	24
#define R_ARM_GOTPC		25
#define R_ARM_GOT32		26
#define R_ARM_PLT32			27

/* THUMB-2 relocations - Diab specific until we can move to */
/* latest ARM ABI (when VxWorks moves).                     */
/* Until then, these take up the "Reserved for ARM LINUX" space */

#define R_ARM_THM_CALL		28
#define R_ARM_THM_JUMP19	29
#define R_ARM_THM_JUMP24	30
#define R_ARM_THM_MOVW_ABS_NC   47
#define R_ARM_THM_MOVT_ABS      48

#define R_ARM_DIAB_LAST         49

#define R_ARM_DIAB_TFIRST	(R_ARM_TFIRST+R_ARM_N)
#define R_ARM_DIAB_N		(R_ARM_DIAB_LAST-R_ARM_DIAB_FIRST)

/* Thumb-2 specific Section Header Attributes */

#define SHT_ARM_ATTRIBUTES	0x70000003

