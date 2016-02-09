/* elfMips.h - Mips specific Extended Load Format header */

/*
 * Copyright (c) 1993, 1995, 1999, 2001, 2003, 2004-2005, 2008, 2009 Wind River
 * Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
 * This file has been developed or significantly modified by the MIPS Center of
 * Excellence Dedicated Engineering Staff. This notice is as per the MIPS
 * Center of Excellence Master Partner Agreement, do not remove this notice
 * without checking first with WR/Platforms MIPS Center of Excellence
 * engineering management.
 */

/*
modification history
--------------------
01k,14dec09,pgh  Add EM_ARCH_MACHINE_x macro definition.
01j,24jun08,v_r  ABI/ISA checking macros: no more erroring out for unsupported 
		 MIPS variants.
01i,11mar08,v_r  Added ABI/ISA handling macros (req CQ:WIND00090099).
		 Moved HI16_RELOC_INFO back into elfMips.c
01h,26jul05,v_r  Linked target/h/arch/mips to this one (as for all other shared
		 ELF headers).
01g,03oct04,jn   Skip relocations used by shared library
01f,04nov03,jn   Temporarily expose some internals of elf mips for RTP loader
01e,11dec01,pad  Removed all unnecessary types and definitions.
01d,16jul01,ros  Add CofE comment
01c,14sep99,myz  Added a new relocation type R_MIPS16_26 for mips16
01b,17nov95,kkk  Added two new special section numbers
01a,28sep93,cd   Derived from elfSparc.h.
*/

#ifndef __INCelfMipsh
#define __INCelfMipsh

#ifdef	__cplusplus
extern "C" {
#endif

/* MIPS ABI relocation types */

#define R_MIPS_NONE		0
#define R_MIPS_16		1	/* unsupported in VxWorks */
#define R_MIPS_32		2
#define R_MIPS_REL32		3	/* unsupported in VxWorks */
#define R_MIPS_26		4
#define R_MIPS_HI16		5
#define R_MIPS_LO16		6
#define R_MIPS_GPREL16		7	/* unsupported in VxWorks */
#define R_MIPS_LITERAL		8	/* unsupported in VxWorks */
#define R_MIPS_GOT16		9	/* unsupported in VxWorks */
#define R_MIPS_PC16		10	/* unsupported in VxWorks */
#define R_MIPS_CALL16		11	/* unsupported in VxWorks */
#define R_MIPS_GPREL32		12	/* unsupported in VxWorks */

/* 
 * These relocation types are not ABI defined. They are required for
 * our compilers' shared library implementation (as per the VxWorks
 * Shared Library EABI). 
 */

#define	R_MIPS_COPY		126
#define	R_MIPS_JMP_SLOT		127

/* 
 * The following macros define the ELF machine type values that can be loaded
 * into a MIPS CPU.
 */

#define EM_ARCH_MACHINE_1   EM_MIPS
#define EM_ARCH_MACHINE_2   EM_MIPS_RS4_BE

#define EM_ARCH_MACHINE		EM_MIPS
#define EI_ARCH_CLASS		ELFCLASS32
#define EI_ARCH_DATA		ELFDATE2MSB

/*
 * MIPS-specific ABI and ISA definitions which are filled into the ELF header of
 * object files by the toolchains. These defines are based on the
 * GNU binutils ones since most of them are GNU extensions (unless indicated).
 * CQ:WIND00119327 has been filed so that Diab makes use of the GNU flags.
 *
 * Note that EF_MIPS_ABI1 does not really exist (ABI1 is defined by EF_MIPS_ABI2
 * not being set). The same goes for the EF_MIPS_ABI mask. Fortunately, nothing
 * uses that field except deprecated GNU stuff not used within VxWorks
 * (EF_MIPS_UCODE and EF_MIPS_OPTIONS_FIRST).
 */

#define EF_MIPS_ABI             0x000000f0
#define EF_MIPS_ABI1            0x00000000
#define EF_MIPS_ABI2            0x00000020  /* common with Diab */

#define EF_MIPS_EXT_ABI         0x0000f000  /* extended GNU information mask */
#define E_MIPS_ABI_O32          0x00001000  /* GNU extension */
#define E_MIPS_ABI_O64          0x00002000  /* GNU extension */
#define E_MIPS_ABI_EABI32       0x00003000  /* GNU extension */
#define E_MIPS_ABI_EABI64       0x00004000  /* GNU extension */

#define EF_MIPS_ARCH            0xf0000000  /* architecture mask */
#define E_MIPS_ARCH_1           0x00000000
#define E_MIPS_ARCH_2           0x10000000  /* common with Diab */
#define E_MIPS_ARCH_3           0x20000000  /* common with Diab */
#define E_MIPS_ARCH_4           0x30000000  /* GNU extension */
#define E_MIPS_ARCH_5           0x40000000  /* GNU extension */
#define E_MIPS_ARCH_32          0x50000000  /* GNU extension */
#define E_MIPS_ARCH_64          0x60000000  /* GNU extension */
#define E_MIPS_ARCH_32R2        0x70000000  /* GNU extension */
#define E_MIPS_ARCH_64R2        0x80000000  /* GNU extension */

/* 
 * Macros which associate ISA and ABI defines above with our build specs.
 */

#ifndef HOST
#if (CPU==MIPSI2)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI1
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_2
#elif (CPU==MIPSI32)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI1
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_32
#elif (CPU==MIPSI32R2)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI1
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_32R2
#elif (CPU==MIPSI3)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI2
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_3
#elif (CPU==MIPSI64)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI2
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_64
#elif (CPU==MIPSI64R2)
#define _WRS_KERNEL_ABI        EF_MIPS_ABI2
#define _WRS_KERNEL_ISA        E_MIPS_ARCH_64R2
#else
#define _WRS_NO_ABI_OR_ISA_INFO
#endif /* MIPS CPU definitions */
#endif /* !HOST */

/*
 * Macro to retrieve the ABI and ISA from the ELF header flags. The extended
 * ABI information does not give additional precision (only o32 is set instead
 * of abi1) so we discard it.
 */

#define _WRS_ABI_FROM_HEADER_GET(flgs) ((flgs & ~EF_MIPS_EXT_ABI) & EF_MIPS_ABI)

#define _WRS_ISA_FROM_HEADER_GET(flgs) (flgs & EF_MIPS_ARCH)

/*
 * Macros to check ISA and ABI compatibility between the kernel and a module.
 *
 * Since MIPS ISAs are backward compatible (i.e it is possible to load a MIPSI32
 * module into a MIPSI32R2 kernel -- the opposite is not true), and thanks to
 * the abovementioned defines increasing across ISA revisions, numerical
 * matching can simply be performed with the 'greater than' operator.
 *
 * This comparison is incorrect across the 32/64 bits boundary but this will be
 * trapped by the ABI checks.
 *
 * XXX: need to assess whether numerical comparison is correct for ARCH_4 and ARCH_5
 * (currently unsupported by VxWorks).
 */

#define _WRS_ISA_IS_COMPATIBLE(kernelIsa, moduleIsa)		\
			      (moduleIsa != E_MIPS_ARCH_4 &&	\
                               moduleIsa != E_MIPS_ARCH_5 &&	\
                               kernelIsa >= moduleIsa)

#define _WRS_ABI_IS_COMPATIBLE(kernelAbi, moduleAbi) (moduleAbi == kernelAbi)

#ifdef	__cplusplus
}
#endif

#endif	/* __INCelfMipsh */
