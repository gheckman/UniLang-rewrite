/* palMipsLib.h - PAL sundry definitions for MIPS */

/*
 * Copyright 2004,2006,2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,02apr09,pch  add mmuType, hasCP2, hasWatch, & hasFPU to palDesc
01e,19jan06,pes  Change _mipsTlbSizeGet to mipsTlbSizeGet
01d,10jan06,pes  Fix compiler warning.
01c,20sep04,pes  Added prototype for palInit().
01b,16aug04,sru  Added prototype for _mipsTlbSizeGet.
01a,26may04,agf  Created.
*/

/*
DESCRIPTION:

This file contains the various strutures and macros required for the PAL
processor description for MIPS.

*/

#ifndef __INCpalMipsLibh
#define __INCpalMipsLibh

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ASMLANGUAGE

/* typedefs */

typedef struct
    {
    VIRT_ADDR * vectorAddr;	/* typically [T,X,C,E]_Vec */
    VIRT_ADDR * excHandler;	/* typically exc[Tlb,Xtlb,Cache,Norm]Vec */
    UINT      excSize;		/* size of handler copied to vectorAddr */
    } MIPS_EXC_VECTOR;

typedef struct
    {
    UINT	nEntries;	/* number of rows in the TLB hardware */
    int		supportedPageSizes;
    int		mmuCacheable;
    int		mmuUncacheable;
    int		mmuCacheCopyback;
    int		mmuCacheWritethrough;
    int		mmuCacheCoherency;
  } MIPS_MMU_INFO;

typedef struct
    {
    BOOL	present;
    UINT	lineSize;	/* line size in bytes */
    UINT	ways;		/* Number of ways */
    UINT	wayStep;	/* Steps between ways */
    UINT	sets;		/* Number of sets/way */
    UINT	modes;		/* Supported modes */
    } MIPS_CACHE_INFO;

typedef struct
    {
    char		*version;	/* PAL version string */
    int			coreNum;	/* processor number */
    MIPS_EXC_VECTOR	tVec;
    MIPS_EXC_VECTOR	xVec;
    MIPS_EXC_VECTOR	cVec;
    MIPS_EXC_VECTOR	eVec;
    MIPS_MMU_INFO	tlb;  
    MIPS_CACHE_INFO	iCache;
    MIPS_CACHE_INFO	dCache;
    MIPS_CACHE_INFO	l2Cache;
    MIPS_CACHE_INFO	l3Cache;
    int			mmuType;	/* CR bits 9:7 */
    BOOL		hasCP2;
    BOOL		hasWatch;
    BOOL		hasFPU;
    } MIPS_PAL_DESC;

/* externals */

IMPORT MIPS_PAL_DESC palDesc;

/* function declarations */

IMPORT UINT32 mipsTlbSizeGet (void);
IMPORT UINT32 _mipsConfigGet (void);
IMPORT void palInit (void);

#endif  /* ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCpalMipsLibh */
