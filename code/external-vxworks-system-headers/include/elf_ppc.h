/*	Definition module : elf_ppc.h

	Copyright 1994 Diab Data AB, Sweden

	Description :
	elf_ppc.h standard header file used by ld, ar, & as
	Defines flags used by PowerPC EABI.

	History :
	When	Who	What
	941129	dalle	initial
*/

/**************	Exported data, types and macros	*****************/

/*
 * e_flags
 */
#define EF_PPC_EMB	0x80000000

/*
 * Relocation types
 */
#define R_PPC_FIRST		0
#define R_PPC_NONE		0
#define R_PPC_ADDR32		1
#define R_PPC_ADDR24		2
#define R_PPC_ADDR16		3
#define R_PPC_ADDR16_LO		4
#define R_PPC_ADDR16_HI		5
#define R_PPC_ADDR16_HA		6
#define R_PPC_ADDR14		7
#define R_PPC_ADDR14_BRTAKEN	8
#define R_PPC_ADDR14_BRNTAKEN	9
#define R_PPC_REL24		10
#define R_PPC_REL14		11
#define R_PPC_REL14_BRTAKEN	12
#define R_PPC_REL14_BRNTAKEN	13
#define R_PPC_GOT16		14
#define R_PPC_GOT16_LO		15
#define R_PPC_GOT16_HI		16
#define R_PPC_GOT16_HA		17
#define R_PPC_PLTREL24		18
#define R_PPC_COPY		19
#define R_PPC_GLOB_DAT		20
#define R_PPC_JMP_SLOT		21
#define R_PPC_RELATIVE		22
#define R_PPC_LOCAL24PC		23
#define R_PPC_UADDR32		24
#define R_PPC_UADDR16		25
#define R_PPC_REL32		26
#define R_PPC_PLT32		27
#define R_PPC_PLTREL32		28
#define R_PPC_PLT16_LO		29
#define R_PPC_PLT16_HI		30
#define R_PPC_PLT16_HA		31
#define R_PPC_SDAREL16		32
#define R_PPC_SECTOFF		33
#define R_PPC_SECTOFF_LO	34
#define R_PPC_SECTOFF_HI	35
#define R_PPC_SECTOFF_HA	36
#define R_PPC_LAST		37

#define R_PPC_TFIRST		0
#define R_PPC_N			(R_PPC_LAST-R_PPC_FIRST)

/* These relocations were introduced in VLE 0.9 */

#define R_PPC_VLE09_FIRST	 46
#define R_PPC_VLE_ADDR20	 46
#define R_PPC_VLE_EMB_SDA27	 47
#define R_PPC_VLE_ADDR16_L	 48
#define	R_PPC_VLE_ADDR16_L_LO	 49
#define	R_PPC_VLE_ADDR16_L_HI	 50
#define	R_PPC_VLE_ADDR16_L_HA	 51
#define	R_PPC_VLE_ADDR16_A	 52
#define	R_PPC_VLE_ADDR16_A_LO	 53
#define	R_PPC_VLE_ADDR16_A_HI	 54
#define	R_PPC_VLE_ADDR16_A_HA	 55
#define R_PPC_VLE_FAR_SDA21_A_HI 56
#define R_PPC_VLE_FAR_SDA21_A_HA 57
#define R_PPC_VLE_MR_SDA_REG	 58
#define R_PPC_VLE09_LAST	 59

#define R_PPC_VLE09_TFIRST	(R_PPC_TFIRST+R_PPC_N)
#define R_PPC_VLE09_N		(R_PPC_VLE09_LAST-R_PPC_VLE09_FIRST)

#define R_PPC_EMB_FIRST		101
#define R_PPC_EMB_NADDR32	101
#define R_PPC_EMB_NADDR16	102
#define R_PPC_EMB_NADDR16_LO	103
#define R_PPC_EMB_NADDR16_HI	104
#define R_PPC_EMB_NADDR16_HA	105
#define R_PPC_EMB_SDAI16	106
#define R_PPC_EMB_SDA2I16	107
#define R_PPC_EMB_SDA2REL	108
#define R_PPC_EMB_SDA21		109
#define R_PPC_EMB_MRKREF	110
#define R_PPC_EMB_RELSEC16	111
#define R_PPC_EMB_RELST_LO	112
#define R_PPC_EMB_RELST_HI	113
#define R_PPC_EMB_RELST_HA	114
#define R_PPC_EMB_BIT_FLD	115
#define R_PPC_EMB_RELSDA	116
#define R_PPC_EMB_LAST		117

#define R_PPC_EMB_TFIRST	(R_PPC_VLE09_TFIRST+R_PPC_VLE09_N)
#define R_PPC_EMB_N		(R_PPC_EMB_LAST-R_PPC_EMB_FIRST)

/* The R_PPC_DIAB_SDA21_xx relocation modes work like the R_PPC_EMB_SDA21 mode
 * and the R_PPC_DIAB_RELSDA_xx relocation modes work like the R_PPC_EMB_RELSDA mode
 * with the following exceptions:
 * If the symbol is in .data, .sdata, .bss, .sbss the symbol is DATA relative
	(r13 base pointer/_SDA_BASE_ base address)
 * If the symbol is in .text, .sdata2, .sbss2 the symbol is CODE relative
	(r2 base pointer/_SDA_BASE2_ base address)
 * Otherwise the symbol is absolute (r0 base pointer/0 base address)
 */
#define R_PPC_DIAB_FIRST	180
#define R_PPC_DIAB_SDA21_LO	180
#define R_PPC_DIAB_SDA21_HI	181
#define R_PPC_DIAB_SDA21_HA	182
#define R_PPC_DIAB_RELSDA_LO	183
#define R_PPC_DIAB_RELSDA_HI	184
#define R_PPC_DIAB_RELSDA_HA	185
#define R_PPC_DIAB_IMTO		186
#define R_PPC_DIAB_IMT		187
#define R_PPC_DIAB_ADDR0	188

#define R_PPC_DIAB_OVERRIDE0	189
#define R_PPC_DIAB_VTBL32	190
#define R_PPC_DIAB_LAST		191

#define R_PPC_DIAB_TFIRST	(R_PPC_EMB_TFIRST+R_PPC_EMB_N)
#define R_PPC_DIAB_N		(R_PPC_DIAB_LAST-R_PPC_DIAB_FIRST)

/* The R_PPC_VLE_xx relocation modes were introduced for PPC VLE.
   The reference document is PowerPC(tm) VLE, PIM, Version 0.4 */
#define R_PPC_VLE_FIRST		216
#define R_PPC_VLE_REL8		216
#define R_PPC_VLE_REL15		217
#define R_PPC_VLE_REL24		218
#define R_PPC_VLE_LO16A		219
#define R_PPC_VLE_LO16D		220
#define R_PPC_VLE_HI16A		221
#define R_PPC_VLE_HI16D		222
#define R_PPC_VLE_HA16A		223
#define R_PPC_VLE_HA16D		224
#define R_PPC_VLE_HA16D		224
#define R_PPC_VLE_SDA21		225   /* Special semantics */
#define R_PPC_VLE_SDA21_LO     	226   /* Special semantics */
#define R_PPC_VLE_SDAREL_LO16A  227
#define R_PPC_VLE_SDAREL_LO16D  228
#define R_PPC_VLE_SDAREL_HI16A  229
#define R_PPC_VLE_SDAREL_HI16D  230
#define R_PPC_VLE_SDAREL_HA16A  231
#define R_PPC_VLE_SDAREL_HA16D  232
#define R_PPC_VLE_LAST  	233

#define R_PPC_VLE_TFIRST	(R_PPC_DIAB_TFIRST+R_PPC_DIAB_N)
#define R_PPC_VLE_N		(R_PPC_VLE_LAST-R_PPC_VLE_FIRST)

/* 
 * Processor specific sh_type 
 */
#define	SHT_ORDERED		(SHT_HIPROC)

/* 
 * Processor specific sh_flags 
 */
#define SHF_PPC_VLE     	0x10000000
#define	SHF_CMP_EXECINSTR	0x20000000
#define	SHF_PCMP_EXECINSTR	0x40000000
#define	SHF_EXCLUDE		0x80000000

/*
 * EB622/D
 * Rev. 1, 5/2003
 * Motorola Book E
 * Implementation Standards:
 * APU ID Reference
 *
 *	0x0000..0x003E	Reserved for legacy use
 *	0x0044..0x00FF	Reserved
 */
#define PPC_APUINFO_ALTIVEC		0x003f 	/* Motorola AltiVec APU	*/
#define PPC_APUINFO_ISEL		0x0040	/* Book E integer select (isel) APU	*/
#define PPC_APUINFO_PERFORMANCE_MONITOR	0x0041	/* Motorola Book E Performance monitor APU	*/
#define PPC_APUINFO_MACHINE_CHECK	0x0042	/* Motorola Book E machine check APU	*/
#define PPC_APUINFO_CACHE_LOCKING	0x0043	/* Motorola Book E cache locking APU	*/
#define PPC_APUINFO_SPE			0x0100	/* Motorola Book E SPE APU	*/
#define PPC_APUINFO_SPEFP		0x0101	/* Motorola Book E SPFP APU	*/
#define PPC_APUINFO_BRANCH_LOCKING	0x0102	/* e500 branch-locking APU (also called the BTB locking APU)	*/
#define PPC_APUINFO_VLE			0x0104	/* Variable length encoding	*/
