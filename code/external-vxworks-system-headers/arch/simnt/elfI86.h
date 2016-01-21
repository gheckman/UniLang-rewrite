/* elfI86.h - i86-specific ELF loader header */

/* 
 * Copyright (c) 2001, 2004-2005, 2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
01e,14dec09,pgh  Add EM_ARCH_MACHINE_x macro definition.
01d,05jun09,v_r  Added ELF64 support (from Professional Services EMT64 Data
                 Access project).
01c,25jul05,v_r  Updated copyright.
01b,27feb04,pad  Renamed relocation type R_386_JUMP_SLOT as R_386_JMP_SLOT as
		 per ABI.
01a,12sep01,pad  Backported from TAE 3.1 to T2.2 with necessary adaptations
                 (base version: elfI86.h@@/main/tor3_x/1).
*/

#ifndef __INCelfI86h
#define __INCelfI86h

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * The following macros define the ELF machine type values that can be loaded
 * into an i86 CPU.
 */

#define EM_ARCH_MACHINE_1   EM_386
#define EM_ARCH_MACHINE_2   EM_486
#define EM_ARCH_MACHINE_3   EM_X86_64

#ifdef _WRS_CONFIG_LP64
#define EM_ARCH_MACHINE         EM_X86_64
#else /* _WRS_CONFIG_LP64 */
#define EM_ARCH_MACHINE		EM_386
#define EM_ARCH_MACH_ALT	EM_486    	/* not used */
#endif /* !_WRS_CONFIG_LP64 */

/*
 * Relocation Type Definitions 
 *   The only ones that appear in vxWorks archives are "1" and "2"
 */

#define	R_386_NONE       0  /* No reloc */
#define R_386_32         1  /* Direct 32 bit  */
#define R_386_PC32       2  /* PC relative 32 bit */
#define R_386_GOT32      3  /* 32 bit GOT entry */
#define R_386_PLT32      4  /* 32 bit PLT address */
#define R_386_COPY       5  /* Copy symbol at runtime */
#define R_386_GLOB_DAT   6  /* Create GOT entry */
#define R_386_JMP_SLOT   7  /* Create PLT entry */
#define R_386_RELATIVE   8  /* Adjust by program base */
#define R_386_GOTOFF     9  /* 32 bit offset to GOT */
#define R_386_GOTPC     10  /* 32 bit PC relative offset to GOT */

/* These 16-bit and 8-bit relocs should never show up */

#define R_386_16        20
#define R_386_PC16      21
#define R_386_8         22
#define R_386_PC8       23
#define R_386_max       24

/* These are GNU extensions to enable C++ vtable garbage collection.  */

#define R_386_GNU_VTINHERIT 250
#define R_386_GNU_VTENTRY 251

/* AMD x86-64 relocations.  */

#define R_X86_64_NONE           0       /* No reloc */
#define R_X86_64_64             1       /* Direct 64 bit  */
#define R_X86_64_PC32           2       /* PC relative 32 bit signed */
#define R_X86_64_GOT32          3       /* 32 bit GOT entry */
#define R_X86_64_PLT32          4       /* 32 bit PLT address */
#define R_X86_64_COPY           5       /* Copy symbol at runtime */
#define R_X86_64_GLOB_DAT       6       /* Create GOT entry */
#define R_X86_64_JUMP_SLOT      7       /* Create PLT entry */
#define R_X86_64_RELATIVE       8       /* Adjust by program base */
#define R_X86_64_GOTPCREL       9       /* 32 bit signed PC relative
                                           offset to GOT */
#define R_X86_64_32             10      /* Direct 32 bit zero extended */
#define R_X86_64_32S            11      /* Direct 32 bit sign extended */
#define R_X86_64_16             12      /* Direct 16 bit zero extended */
#define R_X86_64_PC16           13      /* 16 bit sign extended pc relative */
#define R_X86_64_8              14      /* Direct 8 bit sign extended  */
#define R_X86_64_PC8            15      /* 8 bit sign extended pc relative */
#define R_X86_64_DTPMOD64       16      /* ID of module containing symbol */
#define R_X86_64_DTPOFF64       17      /* Offset in module's TLS block */
#define R_X86_64_TPOFF64        18      /* Offset in initial TLS block */
#define R_X86_64_TLSGD          19      /* 32 bit signed PC relative offset
                                           to two GOT entries for GD symbol */
#define R_X86_64_TLSLD          20      /* 32 bit signed PC relative offset
                                           to two GOT entries for LD symbol */
#define R_X86_64_DTPOFF32       21      /* Offset in TLS block */
#define R_X86_64_GOTTPOFF       22      /* 32 bit signed PC relative offset
                                           to GOT entry for IE symbol */
#define R_X86_64_TPOFF32        23      /* Offset in initial TLS block */
#define R_X86_64_PC64           24	/* PC-relative 64 bits */
#define R_X86_64_GOTOFF64       25
#define R_X86_64_GOTPC32	26
#define R_X86_64_SIZE32		32
#define R_X86_64_SIZE64		33
#define R_X86_64_GOTPC32_TLSDESC 34
#define R_X86_64_TLSDESC_CALL	35
#define R_X86_64_TLSDESC	36

#ifdef __cplusplus
}
#endif

#endif /* __INCelfI86h */
