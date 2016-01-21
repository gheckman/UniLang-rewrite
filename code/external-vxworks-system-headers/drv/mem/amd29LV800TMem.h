/* amd29LV800TMem.h - AMD 29LV800T FLASH memory header */

/* Copyright 2001 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,22jun01,g_h  remove sysNvRamGet() & sysNvRamSet() prototype
01a,22apr01,g_h  created.
*/

/*
DESCRIPTION
This file contains header information for AMD 29LV800T FLASH memory routines.
*/

#ifndef __INCamd29LV800TMemh
#define __INCamd29LV800TMemh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
#ifndef UINT64
#define	UINT64 unsigned long long
#endif

#define BLOCKS (sizeof(blocks) / sizeof(tBLOCK))

#if __PACKUNALIGNED__
typedef __packed__ struct tSOURCE
{
	UINT64 Integer;
} _PackedType tSOURCE;
#define readUnaligned(x)    ((tSOURCE *)(x))->Integer
#else
#define readUnaligned(x)	*(UINT64 *)(x)
#endif

#ifdef __LITTLE_ENDIAN__
#define	MASKSHIFTOP1	<<
#define MASKSHIFTOP2	>>
#else
#define MASKSHIFTOP1	>>
#define MASKSHIFTOP2	<<
#endif


/* typedefs */
typedef float	FLOAT;
typedef double	DOUBLE;

typedef union tFLASH
{
	UINT32 Halves[2];
	UINT64 Integer;
	DOUBLE Float;
} tFLASH;

typedef struct tBLOCK
{
	UINT16 Number;
	UINT16 Size;
} tBLOCK;

/* function declarations */

#ifndef	_ASMLANGUAGE
#if defined(__STDC__) || defined(__cplusplus)

IMPORT UINT32 amd29LV800TWrite(volatile UINT8 *pDest, UINT8 *pSource,	UINT32 Length);
IMPORT UINT32 amd29LV800TEraseBlock(volatile UINT8 *pChip, volatile UINT8 *pSector);
IMPORT UINT32 amd29LV800TEraseSector(volatile UINT8 *pSector);

#else	/* __STDC__ */

IMPORT UINT32 amd29LV800TWrite();
IMPORT UINT32 amd29LV800TEraseBlock();
IMPORT UINT32 amd29LV800TEraseSector();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCamd29LV800TMemh */
