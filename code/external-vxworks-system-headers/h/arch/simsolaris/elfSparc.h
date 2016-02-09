/* elfSparc.h - SPARC ABI header file used by ld, ar, as & loaders */

/* 
 * Copyright (c) 2003-2005,2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
01f,14dec09,pgh  Add EM_ARCH_MACHINE_x macro definition.
01e,25jul05,v_r  Updated copyright.
01d,18sep04,jn   Move towards shared code for host and target loaders
01c,20jun03,nwd  Deliver of Tornado 2.2 Cumulative Patch 1
01a,30apr03,jn   Derived from Diab version of elf_sparc.h. 
                 /vobs/rome_diab_lib/dlib/include/include.unx/
		 elf_sparc.h@@/main/1
		 and /.wind_vxw_h/river/target/h/vxWorks.h@@/main/tor2/1 
		 (for elements of Wind River coding standards).
		 Moved definitions of N_* macros here.  
*/

#ifndef __INCelfSparch
#define __INCelfSparch

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * The following macro defines the ELF machine type value that can be loaded
 * into a SPARC CPU.
 */

#define EM_ARCH_MACHINE_1   EM_SPARC


#define EM_ARCH_MACHINE		EM_SPARC     

#ifndef EM_ARCH_MACH_ALT                     /* defaults to EM_ARCH_MACHINE */
#define EM_ARCH_MACH_ALT	EM_ARCH_MACHINE
#endif 


/*
 *	Note entry header
 */

typedef struct
    {
    Elf32_Word	n_namesz;	/* length of note's name */
    Elf32_Word	n_descsz;	/* length of note's "desc" */
    Elf32_Word	n_type;		/* type of note */
    } Elf32_Nhdr;

/*
 *	Known values for note entry types (e_type == ET_CORE)
 */

#define	NT_PRSTATUS	1
#define	NT_PRFPREG	2
#define	NT_PRPSINFO	3

/**************	Exported data, types and macros	*****************/

/*
 * Relocation types
 */

#define R_SPARC_FIRST		0

#define	R_SPARC_NONE		0	/* relocation type */
#define	R_SPARC_8		1
#define	R_SPARC_16		2
#define	R_SPARC_32		3
#define	R_SPARC_DISP8		4
#define	R_SPARC_DISP16		5
#define	R_SPARC_DISP32		6
#define	R_SPARC_WDISP30		7
#define	R_SPARC_WDISP22		8
#define	R_SPARC_HI22		9
#define	R_SPARC_22		10
#define	R_SPARC_13		11
#define	R_SPARC_LO10		12
#define	R_SPARC_GOT10		13
#define	R_SPARC_GOT13		14
#define	R_SPARC_GOT22		15
#define	R_SPARC_PC10		16
#define	R_SPARC_PC22		17
#define	R_SPARC_WPLT30		18
#define	R_SPARC_COPY		19
#define	R_SPARC_GLOB_DAT	20
#define	R_SPARC_JMP_SLOT	21
#define	R_SPARC_RELATIVE	22
#define	R_SPARC_UA32		23
#define	R_SPARC_NUM		24	/* must be >last */

typedef enum    /* RTYPE_SPARC - sparc relocation types */
    {
    RELOC_8,        RELOC_16,        RELOC_32,          /* simplest relocs */
    RELOC_DISP8,    RELOC_DISP16,    RELOC_DISP32,      /* Disp's (pc-rel) */
    RELOC_WDISP30,  RELOC_WDISP22,                      /* SR word disp's */
    RELOC_HI22,     RELOC_22,                           /* SR 22-bit relocs */
    RELOC_13,       RELOC_LO10,                         /* SR 13&10-bit relocs*/
    RELOC_SFA_BASE, RELOC_SFA_OFF13,                    /* SR S.F.A. relocs */
    RELOC_BASE10,   RELOC_BASE13,    RELOC_BASE22,      /* base_relative pic */
    RELOC_PC10,     RELOC_PC22,                         /* special pc-rel pic */
    RELOC_JMP_TBL,                                      /* jmp_tbl_rel in pic */
    RELOC_SEGOFF16,                                     /* ShLib offset-in-seg*/
    RELOC_GLOB_DAT, RELOC_JMP_SLOT,  RELOC_RELATIVE     /* rtld relocs */
    } RTYPE_SPARC;

#ifdef __cplusplus
}
#endif

#endif /* __INCelfSparch */

