/*	Definition module : elftypes.h

	Copyright 1994 Diab Data AB, Sweden
	Copyright 2008 Wind River Systems Inc.

	Description :
	elftypes.h standard header file used by ld, ar, & as
	Defines standard types used by Elf headers

	History :
	When	Who	What
	941129	dalle	initial
*/

#ifndef D_elftypes
#define D_elftypes

/**************	Exported data, types and macros	*****************/

typedef signed char        __I1_T;
typedef unsigned char      __U1_T;

#if	defined(__DCC__)
#ifdef	__LP64__
typedef short              __I2_T;
typedef unsigned short     __U2_T;
typedef	int                __I4_T;
typedef unsigned int       __U4_T;
typedef long               __I8_T;
typedef unsigned long      __U8_T;
#else
typedef short              __I2_T;
typedef unsigned short     __U2_T;
typedef	long               __I4_T;
typedef unsigned long      __U4_T;
typedef long long          __I8_T;
typedef unsigned long long __U8_T;
#endif		/* __LP64__ */
#else 		/* !defined(__DCC__) */
typedef short              __I2_T;
typedef unsigned short     __U2_T;
typedef	long               __I4_T;
typedef unsigned long      __U4_T;
#if	defined(_MSC_VER)
typedef __int64          __I8_T;
typedef unsigned __int64 __U8_T;
#else
typedef long long          __I8_T;
typedef unsigned long long __U8_T;
#endif
#endif

typedef __U4_T Elf32_Addr;
typedef __U2_T Elf32_Half;
typedef __U4_T Elf32_Off;
typedef __I4_T Elf32_Sword;
typedef __U4_T Elf32_Word;

/*  Elf64 types: per this spec

Elf64_Addr 	8 	8 	Unsigned program address
Elf64_Off 	8 	8 	Unsigned file offset
Elf64_Half 	2 	2 	Unsigned medium integer
Elf64_Word 	4 	4 	Unsigned integer
Elf64_Sword 	4 	4 	Signed integer
Elf64_Xword 	8 	8 	Unsigned long integer
Elf64_Sxword 	8 	8 	Signed long integer
*/

typedef __U8_T Elf64_Addr;
typedef __U8_T Elf64_Off;
typedef __U2_T Elf64_Half;
typedef __U4_T Elf64_Word;
typedef __I4_T Elf64_Sword;
typedef __U8_T Elf64_Xword;
typedef __I8_T Elf64_Sxword;

/* Additions from MIPS_ELF64 spec
Elf64_Byte 	1	1	Unsigned tiny integer
Elf64_Section	2	2	Section index (unsigned)
*/

typedef __U1_T Elf64_Byte;
typedef __U2_T Elf64_Section;
#endif
