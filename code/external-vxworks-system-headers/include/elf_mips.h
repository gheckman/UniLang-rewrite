/*	Definition module : elf_mips.h

	Copyright 1996 Diab Data, USA

	Description :
	elf_mips.h standard header file used by ld, ar, & as
	Defines flags used by 

	History :
	When	Who	What
	960411	paulb	initial
*/

/**************	Exported data, types and macros	*****************/

/*
 * Relocation types
 */
/* ABI/DIAB reloc modes */

#define R_MIPS_NONE		0
#define R_MIPS_16		1	/* .short var */
#define R_MIPS_32		2	/* .long var */
#define R_MIPS_26		4	/* jal func */
#define R_MIPS_HI16		5	/* %hi(var) */
#define R_MIPS_LO16		6	/* %lo(var) */
#define R_MIPS_GPREL16		7	/* %sdaoff(var) */
#define R_MIPS_GOT16		9	/* %got(var) */
#define R_MIPS_PC16		10	/* bal func */
#define R_MIPS_CALL16		11	/* %plt(func) % */

/*
 * From the MIPS64 ABI - "64-bit ELF Object File Specification" 
 * Draft Version 2.5" MIPS Technologies & Silicon Graphics Computer Systems 
 */
#define R_MIPS_LITERAL		8
#define R_MIPS_GPREL32		12	/* Same as R_MIPS_DIAB_ADDR16_HI */
#define R_MIPS_SHIFT5		16
#define R_MIPS_SHIFT6		17
#define R_MIPS_64		18
#define R_MIPS_GOT_DISP		19
#define R_MIPS_GOT_PAGE		20
#define R_MIPS_GOT_OFST		21
#define R_MIPS_GOT_HI16		22
#define R_MIPS_GOT_LO16		23
#define R_MIPS_SUB		24
#define R_MIPS_INSERT_A		25
#define R_MIPS_INSERT_B		26
#define R_MIPS_DELETE		27
#define R_MIPS_HIGHER		28
#define R_MIPS_HIGHEST		29
#define R_MIPS_CALL_HI16m	30
#define R_MIPS_CALL_LO16m	31
#define R_MIPS_SCN_DISP		32
#define R_MIPS_REL16		33
#define R_MIPS_ADD_IMMEDIATE	34
#define R_MIPS_PJUMP		35
#define R_MIPS_RELGOT		36
#define R_MIPS_JALR		37

/* Diab reloc modes is a superset */
#define R_MIPS_DIAB_FIRST	0
#define R_MIPS_DIAB_ADDR16	1	/* .short var */
#define R_MIPS_DIAB_ADDR32	2	/* .long var */
#define R_MIPS_DIAB_ADDR26	4	/* jal func */
#define R_MIPS_DIAB_ADDR16_HA	5	/* %hi(var) */
#define R_MIPS_DIAB_ADDR16_LO	6	/* %lo(var) */
#define R_MIPS_DIAB_GOT16	9	/* %got(x) */
#define R_MIPS_DIAB_PC16	10	/* bal func */
#define R_MIPS_DIAB_CALL16	11	/* %plt(func) */
#define R_MIPS_DIAB_ADDR16_HI	12
#define R_MIPS_DIAB_ADDR0	13
#define R_MIPS_DIAB_OVERRIDE0	14
#define R_MIPS_DIAB_VTBL32	15
#define R_MIPS_DIAB_SHIFT5	16
#define R_MIPS_DIAB_SHIFT6	17
#define R_MIPS_DIAB_64		18
#define R_MIPS_DIAB_GOT_DISP	19
#define R_MIPS_DIAB_GOT_PAGE	20
#define R_MIPS_DIAB_GOT_OFST	21
#define R_MIPS_DIAB_GOT_HI16	22
#define R_MIPS_DIAB_GOT_LO16	23
#define R_MIPS_DIAB_SUB		24
#define R_MIPS_DIAB_INSERT_A	25
#define R_MIPS_DIAB_INSERT_B	26
#define R_MIPS_DIAB_DELETE	27
#define R_MIPS_DIAB_HIGHER	28
#define R_MIPS_DIAB_HIGHEST	29
#define R_MIPS_DIAB_CALL_HI16m	30
#define R_MIPS_DIAB_CALL_LO16m	31
#define R_MIPS_DIAB_SCN_DISP	32
#define R_MIPS_DIAB_REL16	33
#define R_MIPS_DIAB_ADD_IMMEDIATE	34
#define R_MIPS_DIAB_PJUMP	35
#define R_MIPS_DIAB_RELGOT	36
#define R_MIPS_DIAB_JALR	37
#define R_MIPS_DIAB_LAST	38

#define R_MIPS_DIAB_TFIRST	0
#define R_MIPS_DIAB_N		(R_MIPS_DIAB_LAST-R_MIPS_DIAB_FIRST)

#define R_MIPS_SDA_FIRST	245
#define R_MIPS_SCA_16		245	/* %picoff(var) */
#define R_MIPS_SCA_16_HA	246	/* %pichi(var) */
#define R_MIPS_SCA_16_HI	247
#define R_MIPS_SCA_16_LO	248	/* %piclo(var) */
#define R_MIPS_SDA_16		251	/* %sdaoff(var) */
#define R_MIPS_SDA_16_HA	252	/* %pidhi(var) */
#define R_MIPS_SDA_16_HI	253
#define R_MIPS_SDA_16_LO	254	/* %pidlo(var) */
#define R_MIPS_SDA_LAST		255

#define R_MIPS_SDA_TFIRST	(R_MIPS_DIAB_TFIRST+R_MIPS_DIAB_N)
#define R_MIPS_SDA_N		(R_MIPS_SDA_LAST-R_MIPS_SDA_FIRST)

/* mips16 relocations */

#define	R_MIPS16_FIRST		100 
#define	R_MIPS16_26		100  	/* mips16 jal */
#define	R_MIPS16_SDA		101  	/* %sdaoff(var) */
#define	R_MIPS16_LAST		102 

#define R_MIPS16_TFIRST		(R_MIPS_SDA_TFIRST+R_MIPS_SDA_N)
#define R_MIPS16_N		(R_MIPS16_LAST-R_MIPS16_FIRST)

#define	R_MIPS_DIAB_DYNREL_FIRST	126
#define	R_MIPS_DIAB_COPY	126
#define	R_MIPS_DIAB_JMP_SLOT	127
#define	R_MIPS_DIAB_DYNREL_LAST	128

#define R_MIPS_DIAB_DYNREL_TFIRST	(R_MIPS16_TFIRST+R_MIPS16_N)
#define	R_MIPS_DIAB_DYNREL_N	(R_MIPS_DIAB_DYNREL_LAST-R_MIPS_DIAB_DYNREL_FIRST)

#define STO_MIPS16_SYM		240

/* st_other field masks */
#define STO_EXPORT		3
#define STO_DEFAULT		0
#define STO_INTERNAL		1
#define STO_HIDDEN		2
#define STO_PROTECTED		3

/*
  SGI relocation modes. Not supported
*/
#if 0
#define R_MIPS_FIRST		0
#define R_MIPS_NONE		0
#define R_MIPS_REFHALF       1
#define R_MIPS_REFWORD       2
#define R_MIPS_JMPADDR       3
#define R_MIPS_REFHI         4
#define R_MIPS_REFLO         5
#define R_MIPS_GPREL         6
#define R_MIPS_LITERAL       7
#define R_MIPS_REL32         8
#define R_MIPS_REFGOT        R_MIPS_REL32     /* alias for compatibility */
#define R_MIPS_REFHI_64      9
#define R_MIPS_REFLO_64      10
#define R_MIPS_REFWORD_64    11
#define R_MIPS_PC16          12
#define R_MIPS_RELHI         13
#define R_MIPS_RELLO         14
#define R_MIPS_REFSHFT       15
#define R_MIPS_REFHI_ADDEND  16          /* lo value is in immed of inst */
#define R_MIPS_SHFTCNT       17
#define R_MIPS_MULTRELHI     18
#define R_MIPS_MULTRELLO     19
#define R_MIPS_DATA16        20
#define R_MIPS_LAST	21
#endif

/*
 * Processor specific section header types
 */
#define SHT_MIPS_LIBLIST	0x70000000
#define SHT_MIPS_MSYM		0x70000001
#define SHT_MIPS_CONFLICT	0x70000002
#define SHT_MIPS_GPTAB		0x70000003
#define SHT_MIPS_UCODE		0x70000004
#define SHT_MIPS_DEBUG		0x70000005
#define SHT_MIPS_REGINFO	0x70000006
#define SHT_MIPS_PACKAGE	0x70000007
#define SHT_MIPS_PACKSYM	0x70000008
#define SHT_MIPS_RELD		0x70000009
#define SHT_MIPS_IFACE		0x7000000b
#define SHT_MIPS_CONTENT	0x7000000c
#define SHT_MIPS_OPTIONS	0x7000000d
#define SHT_MIPS_DELTASYM	0x7000001b
#define SHT_MIPS_DELTAINST	0x7000001c
#define SHT_MIPS_DELTACLASS	0x7000001d
#define SHT_MIPS_DWARF		0x7000001e
#define SHT_MIPS_DELTADECL	0x7000001f
#define SHT_MIPS_SYMBOL_LIB	0x70000020
#define SHT_MIPS_EVENTS		0x70000021
#define SHT_MIPS_TRANSLATE	0x70000022
#define SHT_MIPS_PIXIE		0x70000023
#define SHT_MIPS_XLATE		0x70000024
#define SHT_MIPS_XLATE_DEBUG	0x70000025
#define SHT_MIPS_WHIRL		0x70000026
#define SHT_MIPS_EH_REGION	0x70000027
#define SHT_MIPS_XLATE_OLD	0x70000028
#define SHT_MIPS_PDR_EXCEPTION	0x70000029

/*
 * Processor specific section attribute flags
 */
#define SHF_MIPS_GPREL		0x10000000
#define SHF_MIPS_MERGE		0x20000000
#define SHF_MIPS_ADDR		0x40000000
#define SHF_MIPS_STRING		0x80000000
#define SHF_MIPS_NOSTRIP	0x08000000
#define SHF_MIPS_LOCAL		0x04000000
#define SHF_MIPS_NAMES		0x02000000
#define SHF_MIPS_NODUPE		0x01000000

/*
 * Processor specific section index field values
 */
#define SHN_MIPS_ACOMMON	0xff00
#define SHN_MIPS_TEXT		0xff01
#define SHN_MIPS_DATA		0xff02
#define SHN_MIPS_SCOMMON	0xff03
#define SHN_MIPS_SUNDEFINED	0xff04
#define SHN_MIPS_LCOMMON	0xff05
#define SHN_MIPS_LUNDEFINED	0xff06

/*
 * Relocation
 */

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Word	r_sym;		/* These 5 fields r_sym - r_type   */
	Elf64_Byte	r_ssym;		/* map to r_info in the generic    */
	Elf64_Byte	r_type3;	/* Elf64_Rel struct                */
	Elf64_Byte	r_type2;
	Elf64_Byte	r_type;
} Elf64_Mips_Rel;

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Word	r_sym;		/* These 5 fields r_sym - r_type  */
	Elf64_Byte	r_ssym;		/* map to r_info in the generic   */
	Elf64_Byte	r_type3;	/* Elf64_Rela struct              */
	Elf64_Byte	r_type2;
	Elf64_Byte	r_type;
	Elf64_Sxword	r_addend;
} Elf64_Mips_Rela;
