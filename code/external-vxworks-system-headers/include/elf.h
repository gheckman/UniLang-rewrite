/*	Definition module : elf.h

	Copyright 1994 Diab Data AB, Sweden
	Copyright 2008 Wind River Systems Inc

	Description :
	elf.h standard header file used by ld, ar, & as

	History :
	When	Who	What
	941129	dalle	initial
*/

#ifndef D_elf
#define D_elf

/**************	Exported data, types and macros	*****************/

#include <elftypes.h>

/* 
 * Elf header
 */
#define EI_NIDENT	16

typedef struct {
	unsigned char	e_ident[EI_NIDENT];
	Elf32_Half	e_type;			/* ET_XXX */
	Elf32_Half	e_machine;		/* EM_XXX */
	Elf32_Word	e_version;		/* EV_XXX */
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;		/* EF_XXX */
	Elf32_Half	e_ehsize;
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
} Elf32_Ehdr;

typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf64_Half      e_type;
        Elf64_Half      e_machine;
        Elf64_Word      e_version;
        Elf64_Addr      e_entry;
        Elf64_Off       e_phoff;
        Elf64_Off       e_shoff;
        Elf64_Word      e_flags;
        Elf64_Half      e_ehsize;
        Elf64_Half      e_phentsize;
        Elf64_Half      e_phnum;
        Elf64_Half      e_shentsize;
        Elf64_Half      e_shnum;
        Elf64_Half      e_shstrndx;
} Elf64_Ehdr;

#define EHDRSZ sizeof(Elf32_Ehdr)

/* 
 * e_ident[] values
 */
#define EI_MAG0		0
#define EI_MAG1		1
#define EI_MAG2		2
#define EI_MAG3		3
#define EI_CLASS	4
#define EI_DATA		5
#define EI_VERSION	6
#define	EI_OSABI 	7
#define	EI_ABIVERSION 	8
#define EI_PAD		9

/* Values for EI_OSABI. 64-255 is the "Architecture-specific value range" */
#define	ELFOSABI_NONE		0 	/* No extensions or unspecified */
#define	ELFOSABI_HPUX		1 	/* Hewlett-Packard HP-UX */
#define	ELFOSABI_NETBSD		2 	/* NetBSD */
#define	ELFOSABI_SOLARIS	6 	/* Sun Solaris */
#define	ELFOSABI_AIX		7 	/* AIX */
#define	ELFOSABI_IRIX		8 	/* IRIX */
#define	ELFOSABI_FREEBSD	9 	/* FreeBSD */
#define	ELFOSABI_TRU64		10 	/* Compaq TRU64 UNIX */
#define	ELFOSABI_MODESTO	11 	/* Novell Modesto */
#define	ELFOSABI_OPENBSD	12 	/* Open BSD */
#define	ELFOSABI_OPENVMS	13 	/* Open VMS */
#define	ELFOSABI_NSK		14 	/* Hewlett-Packard Non-Stop Kernel */
#define	ELFOSABI_AROS		15 	/* Amiga Research OS */

#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'
#define ELFMAG		"\177ELF"
#define SELFMAG		4

/* 
 * EI_CLASS 
 */
#define ELFCLASSNONE	0
#define ELFCLASS32	1
#define ELFCLASS64	2

/* 
 * EI_DATA 
 */
#define ELFDATANONE	0
#define ELFDATA2LSB	1
#define ELFDATA2MSB	2

/* 
 * e_type 
 */
#define ET_NONE		0
#define ET_REL		1
#define ET_EXEC		2
#define ET_DYN		3
#define ET_CORE		4
#define	ET_LOOS		0xfe00
#define	ET_HIOS		0xfeff
#define ET_LOPROC	0xff00
#define ET_HIPROC	0xffff

/* 
 * e_machine
 */
#define EM_NONE		0		/* No machine */
#define EM_M32		1		/* AT&T WE 32100 */
#define EM_SPARC	2		/* SPARC */
#define EM_386		3		/* Intel 80386 */
#define EM_68K		4		/* Motorola 68000 */
#define EM_88K		5		/* Motorola 88000 */
#define EM_860		7		/* Intel 80860 */
#define EM_MIPS		8		/* MIPS RS3000 Big-Endian */
#define EM_MIPS_RS4_BE	10		/* MIPS RS4000 Big-Endian */
#define EM_PPC_OLD	17		/* PowerPC - old */
#define EM_PPC		20		/* PowerPC */
#define EM_RCE_OLD	25		/* RCE - old */
#define EM_RCE		39		/* RCE */
#define EM_MCORE	39		/* MCORE */
#define EM_SH		42		/* SH */
#define EM_M32R		36929		/* M32R */
#define EM_NEC		36992		/* NEC 850 series */
#define EM_NEC_830	36		/* NEC 830 series */
#define EM_SC		58		/* SC */
#define EM_ARM          40              /* ARM  */
#define EM_TRICORE      44              /* TRICORE */
#define EM_X86_64	62		/* X86_64 */

/* 
 * e_flags
 */
#define EF_PPC_EMB		0x80000000

#define EF_MIPS_NOREORDER	0x00000001
#define EF_MIPS_PIC		0x00000002
#define EF_MIPS_CPIC		0x00000004
#define EF_MIPS_UCODE		0x00000010
#define	EF_MIPS_ABI2		0x00000020
#define EF_MIPS_OPTIONS_FIRST	0x00000080
#define	EF_MIPS_ARCH_ASE	0x0f000000
#define	EF_MIPS_ARCH_ASE_MDMX	0x08000000
#define	EF_MIPS_ARCH_ASE_M16	0x04000000
#define EF_MIPS_ARCH		0xf0000000
#define EF_MIPS_ARCH_MIPS_2	0x10000000
#define	EF_MIPS_ARCH_MIPS_3	0x20000000
#define	EF_MIPS_ARCH_MIPS_4	0x30000000

#define EF_TRICORE		0xf0000000
#define EF_TRICORE_V1_1		0x80000000
#define EF_TRICORE_V1_2		0x40000000
#define EF_TRICORE_V1_3		0x20000000
#define	EF_TRICORE_V1_3_1	0x00800000
#define EF_TRICORE_V1_6		0x00400000  /* V2_0 changed to V1_6 */
#define EF_TRICORE_PCP 		0x01000000
#define EF_TRICORE_PCP2		0x02000000

/* 0x10000000 is not a valid TRICORE_EFLAG according to the ABI however Diab 
has been using that bit to mark ISA V1.6. Uses of this are fixed up in the 
linker so we can continue linking with older objects and still o produce 
reasonable output e_flags; at least as long as the TriCore EABI does not 
repurpose 0x10000000. If that happens, fix the code in dld/src/elf/etc.c 
that handles ISA and PCP versions */

#define EF_TRICORE_V1_6_DIAB_OLD		0x10000000

/*
 * ARM-specific e_flags: referred from "ARM IHI 0036B, current through ABI release 2.07" 
 * released on Date 10th October 2008
 */
#define	EF_ARM_BE8			0x00800000

/* 
 * e_version and EI_VERSION 
 */
#define EV_NONE		0
#define EV_CURRENT	1





/* 
 * Special section indexes
 */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define	SHN_LOOS	0xff20
#define	SHN_HIOS	0xff3f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff
#define SHN_XINDEX	0xffff

#define SHN_GHCOMMON	0xff00
/* 
 * Section header
 */
typedef struct {
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;	/* SHT_... */
	Elf32_Word	sh_flags;	/* SHF_... */
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
} Elf32_Shdr;

typedef struct {
	Elf64_Word	sh_name;
	Elf64_Word	sh_type;
	Elf64_Xword	sh_flags;
	Elf64_Addr	sh_addr;
	Elf64_Off	sh_offset;
	Elf64_Xword	sh_size;
	Elf64_Word	sh_link;
	Elf64_Word	sh_info;
	Elf64_Xword	sh_addralign;
	Elf64_Xword	sh_entsize;
} Elf64_Shdr;

#define SHDRSZ sizeof(Elf32_Shdr)

/* 
 * sh_type 
 */
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_COMDAT	12
#define	SHT_INIT_ARRAY	14
#define	SHT_FINI_ARRAY	15
#define	SHT_PREINIT_ARRAY	16
#define	SHT_GROUP	17
#define	SHT_SYMTAB_SHNDX	18
#define	SHT_LOOS	0x60000000
#define	SHT_HIOS	0x6fffffff
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000
#define SHT_HIUSER	0xffffffff

/* 
 * sh_flags 
 */
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define	SHF_MERGE	0x10
#define	SHF_STRINGS	0x20
#define	SHF_INFO_LINK	0x40
#define	SHF_LINK_ORDER	0x80
#define	SHF_OS_NONCONFORMING	0x100
#define	SHF_GROUP	0x200
#define	SHF_TLS	0x400
#define	SHF_MASKOS	0x0ff00000
#define SHF_MASKPROC	0xf0000000





/* Section Group Flags */
#define GRP_COMDAT	0x1
#define GRP_MASKOS	0x0ff00000
#define GRP_MASKPROC	0xf0000000
/* 
 * Symbol table
 */
typedef struct {
	Elf32_Word	st_name;
	Elf32_Addr	st_value;
	Elf32_Word	st_size;
	unsigned char	st_info;	/* ELF_32_ST_XXX */
	unsigned char	st_other;
	Elf32_Half	st_shndx;	/* SHN_XXX */
} Elf32_Sym;

typedef struct {
	Elf64_Word	st_name;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf64_Half	st_shndx;
	Elf64_Addr	st_value;
	Elf64_Xword	st_size;
} Elf64_Sym;

#define STN_UNDEF	0

#define STB_LOCAL	0
#define STB_GLOBAL	1
#define STB_WEAK	2
#define STB_LOOS	10
#define STB_HIOS	12
#define STB_LOPROC	13
#define STB_SPLIT_COMMON 13
#define STB_HIPROC	15

#define STT_NOTYPE	0
#define STT_OBJECT	1
#define STT_FUNC	2
#define STT_SECTION	3
#define STT_FILE	4
#define	STT_COMMON	5
#define	STT_TLS		6
#define	STT_LOOS	10
#define	STT_HIOS	12
#define STT_LOPROC	13
#define STT_HIPROC	15
#define STT_ARM_TFUNC   0xd          /* GNU THUMB Function */

/* Symbol Visibility */
#define STV_DEFAULT		0
#define STV_INTERNAL	1
#define STV_HIDDEN		2
#define STV_PROTECTED	3

#define ELF32_ST_BIND(info)		((info) >> 4)
#define ELF32_ST_TYPE(info)		((info) & 0xf)
#define ELF32_ST_INFO(bind,type)	(((bind)<<4)+((type)&0xf))

#define ELF64_ST_BIND(i)	((i)>>4)
#define ELF64_ST_TYPE(i)	((i)&0xf)
#define ELF64_ST_INFO(b,t)	(((b)<<4)+((t)&0xf))

#define ELF32_ST_VISIBILITY(o)	((o)&0x3)
#define ELF64_ST_VISIBILITY(o)	((o)&0x3)




/*
 * Relocation
 */
typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;		/* ELF32_R_XXX */
} Elf32_Rel;

typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;		/* ELF32_R_XXX */
	Elf32_Sword	r_addend;
} Elf32_Rela;

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Xword	r_info;
} Elf64_Rel;

typedef struct {
	Elf64_Addr	r_offset;
	Elf64_Xword	r_info;
	Elf64_Sxword	r_addend;
} Elf64_Rela;
#define ELF32_R_SYM(info)	((info)>>8)
#define ELF32_R_TYPE(info)	((unsigned char)(info))
#define ELF32_R_INFO(sym,type)	(((sym)<<8)+(unsigned char)(type))
#define ELF64_R_SYM(i)	((i)>>32)
#define ELF64_R_TYPE(i)	((i)&0xffffffffL)
#define ELF64_R_INFO(s,t)	(((s)<<32)+((t)&0xffffffffL))





/*
 * Program header
 */
typedef struct {
	Elf32_Word	p_type;		/* PT_XXX */
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;	/* PF_XXX */
	Elf32_Word	p_align;
} Elf32_Phdr;

typedef struct {
	Elf64_Word	p_type;
	Elf64_Word	p_flags;
	Elf64_Off	p_offset;
	Elf64_Addr	p_vaddr;
	Elf64_Addr	p_paddr;
	Elf64_Xword	p_filesz;
	Elf64_Xword	p_memsz;
	Elf64_Xword	p_align;
} Elf64_Phdr;

#define PHDRSZ sizeof(Elf32_Phdr)

/* 
 * p_type 
 */
#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_TLS		7
#define PT_LOOS		0x60000000
#define PT_HIOS		0x6fffffff
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0x7fffffff

/* 
 * p_flags 
 */
#define PF_X		0x1
#define PF_W		0x2
#define PF_R		0x4
#define PF_MASKOS	0x0ff00000 	
#define PF_MASKPROC	0xf0000000	/* Processor-specific flags mask */
#define PF_PPC_VLE	0x10000000	/* PPC VLE code attribute */

typedef struct {
	Elf32_Sword	d_tag;
	union {
		Elf32_Word  d_val;
		Elf32_Addr  d_ptr;
	} d_un;
} Elf32_Dyn;

typedef struct {
	Elf64_Sxword	d_tag;
   	union {
   		Elf64_Xword	d_val;
   		Elf64_Addr	d_ptr;
	} d_un;
} Elf64_Dyn;

#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH	15
#define DT_SYMBOLIC	16
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_BIND_NOW     24
#define DT_INIT_ARRAY   25
#define DT_FINI_ARRAY   26
#define DT_INIT_ARRAYSZ 27
#define DT_FINI_ARRAYSZ 28
#define DT_RUNPATH      29
#define DT_FLAGS        30
#define DT_ENCODING 	32 
#define DT_PREINIT_ARRAY 	32
#define DT_PREINIT_ARRAYSZ 	33

#define DT_LOPROC   0x70000000
#define DT_HIPROC   0x7fffffff

#define	DT_LOOS		0x6000000D
#define	DT_HIOS		0x6ffff000

/* DT_FLAGS Values */
#define DF_ORIGIN	0x1
#define DF_SYMBOLIC	0x2
#define DF_TEXTREL	0x4
#define DF_BIND_NOW	0x8
#define DF_STATIC_TLS	0x10

/* VxWorks specific tags */

#define	DT_VX_WRS_TLS_DATA_START	0x60000010
#define	DT_VX_WRS_TLS_DATA_SIZE		0x60000011
#define	DT_VX_WRS_TLS_VARS_START	0x60000012
#define	DT_VX_WRS_TLS_VARS_SIZE		0x60000013
#define	DT_VX_WRS_TLS_DATA_ALIGN	0x60000015

#endif
