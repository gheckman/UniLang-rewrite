#ifndef __Ireloc
#define __Ireloc

#if defined(m88k) || defined(__m88k) || defined(__ppc)

struct reloc {				/* modified COFF	*/
	long		r_vaddr;	/* address of reference	*/
	long		r_symndx;	/* index into symtab	*/
	unsigned short	r_type;		/* relocation type	*/
	unsigned short	r_offset;	/* hi word of rel addr	*/
};

#define	RELOC	struct reloc
#define	RELSZ	sizeof(RELOC)

#else

struct reloc {			/* standard COFF	*/
	long	r_vaddr;	/* address of reference	*/
	long	r_symndx;	/* index into symtab	*/
	unsigned short	r_type;	/* relocation type	*/
};

#define	RELOC	struct reloc
#define	RELSZ	10	/* sizeof(RELOC) */

#endif

/*	Relocation types	*/

#define  R_ABS		0

/*	68k relocations	*/
#define R_RELBYTE	017	/* byte virtual	*/
#define R_RELWORD	020	/* word virtual	*/
#define R_RELLONG	021	/* long virtual	*/
#define R_PCRBYTE	022	/* byte pcrel	*/
#define R_PCRWORD	023	/* word pcrel	*/
#define R_PCRLONG	024	/* long pcrel	*/

/*	88k relocations	*/
#define R_PCR16L	128	/* 16bit>>2 pcr	*/
#define R_PCR26L	129	/* 26bit>>2 pcr	*/
#define R_VRT16		130	/* word virtual	*/
#define R_HVRT16	131	/* hi16 virtual	*/
#define R_LVRT16	132	/* lo16 virtual	*/
#define R_VRT32		133	/* long virtual	*/

/*	PowerPC COFF relocations */
#define R_HAVRT16	136	/* hi16 adjusted virtual		*/
#define R_PCR16S2	137	/* PC Relative 16bit 2lsb not changed	*/
#define R_PCR26S2	138	/* PC Relative 26bit 2lsb not changed	*/
#define R_REL16S2	139	/* Absolute 16bit 2lsb not changed	*/
#define R_REL26S2	140	/* Absolute 26bit 2lsb not changed	*/

#endif
