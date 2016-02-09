/*	Definition module : elf_tricore.h
 *
 *	Copyright 2004 Wind RIver, Inc.
 *
 *	Description :
 *	elf_tricore.h standard header file used by ld, ar, & as
 *
 *	History :
 *	When	        Who	What
 *	03-24-2004	swalk	Initial
 */

/**************	Exported data, types and macros	*****************/

#if 0
/*
 *	e_flags
 */

#define EF_TRICORE_V1_1		0x80000000
#define EF_TRICORE_V1_2		0x40000000
#define EF_TRICORE_V1_3		0x20000000
#define	EF_TRICORE_V1_3_1	0x00800000
#define EF_TRICORE_V1_6		0x00400000  /* V2_0 changed to V1_6 */
#define EF_TRICORE_PCP 		0x01000000
#define EF_TRICORE_PCP2		0x02000000
#endif


/*
 *	sh_flags
 */

#define SHF_TRICORE_ABS		0x400
#define SHF_TRICORE_NOREAD	0x800


/*
 * 	Relocation types for Infineon Tricore processor
 */

#define R_TRICORE_FIRST		0
#define R_TRICORE_NONE		0
#define R_TRICORE_32REL		1
#define R_TRICORE_32ABS         2
#define R_TRICORE_24REL         3
#define R_TRICORE_24ABS         4
#define R_TRICORE_16SM          5
#define R_TRICORE_HI         	6
#define R_TRICORE_LO		7
#define R_TRICORE_LO2		8
#define R_TRICORE_18ABS		9
#define R_TRICORE_10SM		10
#define R_TRICORE_15REL		11
#define R_TRICORE_10LI		12
#define R_TRICORE_16LI		13
#define R_TRICORE_10A8		14
#define R_TRICORE_16A8		15
#define R_TRICORE_10A9		16
#define R_TRICORE_16A9		17
#define R_TRICORE_PCPHI		25
#define R_TRICORE_PCPLO		26
#define R_TRICORE_PCPPAGE	27
#define R_TRICORE_PCPOFF	28
#define R_TRICORE_PCPTEXT	29
#define R_TRICORE_LAST		30

#define R_TRICORE_TFIRST	0
#define R_TRICORE_N		(R_TRICORE_LAST-R_TRICORE_TFIRST)


/* 
 * 	DIAB specific relocation types
 */

#define R_TRICORE_DIAB_FIRST	 30
#define R_TRICORE_DIAB_ADDR0     30
#define R_TRICORE_DIAB_OVERRIDE0 31
#define R_TRICORE_DIAB_VTBL32    32
#define R_TRICORE_DIAB_LAST	 33

#define R_TRICORE_DIAB_TFIRST   (R_TRICORE_FIRST+R_TRICORE_N)
#define R_TRICORE_DIAB_N        (R_TRICORE_DIAB_LAST-R_TRICORE_DIAB_FIRST)




