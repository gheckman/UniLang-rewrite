/*	Definition module : elf_x86_64.h	*/

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
	Description :
	elf_x86_64.h standard header file used by ld, ar & as

	History :
	When	        Who	  What
	03-Dec-2008     mmadhava  written
*/

/**************	Exported data, types and macros	*****************/

/*
 * Relocation types for AMD x86_64
 */

#define R_X86_64_FIRST			0 
#define R_X86_64_NONE 			0 
#define R_X86_64_64 			1 
#define R_X86_64_PC32 			2 
#define R_X86_64_GOT32 			3 
#define R_X86_64_PLT32 			4 
#define R_X86_64_COPY 			5	 
#define R_X86_64_GLOB_DAT 		6 
#define R_X86_64_JUMP_SLOT 		7 
#define R_X86_64_RELATIVE 		8 
#define R_X86_64_GOTPCREL 		9 
#define R_X86_64_32 			10 
#define R_X86_64_32S 			11 
#define R_X86_64_16 			12 
#define R_X86_64_PC16 			13 
#define R_X86_64_8 			14 
#define R_X86_64_PC8 			15 
#define R_X86_64_DTPMOD64 		16 
#define R_X86_64_DTPOFF64 		17 
#define R_X86_64_TPOFF64 		18 
#define R_X86_64_TLSGD 			19 
#define R_X86_64_TLSLD 			20 
#define R_X86_64_DTPOFF32 		21 
#define R_X86_64_GOTTPOFF 		22 
#define R_X86_64_TPOFF32 		23 
#define R_X86_64_PC64 			24 
#define R_X86_64_GOTOFF64 		25 
#define R_X86_64_GOTPC32 		26 
#define R_X86_64_SIZE32 		32 
#define R_X86_64_SIZE64 		33 
#define R_X86_64_GOTPC32_TLSDESC 	34 
#define R_X86_64_TLSDESC_CALL 		35 
#define R_X86_64_TLSDESC 		36 
#define R_X86_64_LAST 			37

#define R_X86_64_TFIRST			0
#define R_X86_64_N			(R_X86_64_LAST-R_X86_64_TFIRST)

#define R_X86_64_DIAB_FIRST		37
#define R_X86_64_DIAB_ADDR0		37
#define R_X86_64_DIAB_OVERRIDE0		38
#define R_X86_64_DIAB_VTBL64		39
#define R_X86_64_DIAB_LAST		40

#define R_X86_64_DIAB_TFIRST		(R_X86_64_TFIRST+R_X86_64_N)
#define R_X86_64_DIAB_N			(R_X86_64_DIAB_LAST-R_X86_64_DIAB_FIRST)

/* 
 * Processor specific sh_type 
 */
#define SHT_X86_64_UNWIND     0x70000001

/* 
 * Processor specific sh_flags 
 */
#define SHF_X86_64_LARGE		0x10000000
