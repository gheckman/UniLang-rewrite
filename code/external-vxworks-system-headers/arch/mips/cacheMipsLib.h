/* cacheMipsLib.h - MIPS cache library header file */

/* Copyright (C) 1992-1993,1996,1999,2001-2003,2006-2008, 2010 Wind River Systems, Inc. */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01q,29apr10,pad  Moved extern C statement after include statements.
01p,22may08,slk  add CFG_CCA_COHERENT for malta34k variant
01o,09aug07,rlg  Changes for the MIPS Library restructuring
01n,23apr07,rlg  fix for defect 87754
01m,10jan06,pes  Fix compiler warning.
01l,27may03,jmt  Modify after cache library review
01k,07may03,jmt  Add mti20kx family support
01j,01oct02,jmt  added tx79xx support and made mods for comments from
                 design review
01i,17may02,zmm  Global au1000 name changes. SPR 77333.
01i,14may02,jmt  Added Tx49xx cache library support
01h,13dec01,sru  add prototype for Vr4131 cache lib
01g,16jul01,ros  add CofE comment
01f,09jul01,mem  Added generic MIPS cache op prototypes.
01e,19jan99,dra  added CW4000, CW4011, VR4100, VR5000 and VR5400 support.
01d,15jul96,kkk  added R4650 support
01c,15oct93,cd   added R4000 supoort.
01b,22sep92,rrr  added support for c++
01a,07jul92,ajm  created.
*/

#ifndef __INCcacheMipsLibh
#define __INCcacheMipsLibh

#include <vxWorks.h>
#include <cacheLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* function declarations */

IMPORT void * cacheMipsMalloc (size_t bytes);
IMPORT STATUS cacheMipsFree (void * pBuf);
IMPORT void * cacheMipsVirtToPhys (void * address);
IMPORT void * cacheMipsPhysToVirt (void * address);
IMPORT STATUS cacheMipsPipeFlush (void);

IMPORT STATUS cacheMipsLibInit(CACHE_MODE instMode, CACHE_MODE dataMode);

IMPORT STATUS cache4kcLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			       UINT32 iCacheSize, UINT32 iCacheLineSize,
			       UINT32 dCacheSize, UINT32 dCacheLineSize);

IMPORT STATUS cache20kxLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			        UINT32 iCacheSize, UINT32 iCacheLineSize,
			        UINT32 dCacheSize, UINT32 dCacheLineSize,
				UINT32 sCacheSize, UINT32 sCacheLineSize,
			        UINT32 tCacheSize, UINT32 tCacheLineSize);

IMPORT STATUS cacheAuLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
				  UINT32 iCacheSize, UINT32 iCacheLineSize,
				  UINT32 dCacheSize, UINT32 dCacheLineSize);

IMPORT STATUS cacheCW400xLibInit (CACHE_MODE instMode, CACHE_MODE dataMode);

IMPORT STATUS cacheCW4011LibInit (CACHE_MODE instMode, CACHE_MODE dataMode);

IMPORT STATUS cacheR32kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode);

IMPORT STATUS cacheR33kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
				UINT32 iCacheSize, UINT32 iCacheLineSize,
				UINT32 dCacheSize, UINT32 dCacheLineSize);

IMPORT STATUS cacheR3kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode);

IMPORT STATUS cacheR4kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			       UINT32 iCacheSize, UINT32 iCacheLineSize,
			       UINT32 dCacheSize, UINT32 dCacheLineSize,
			       UINT32 sCacheSize, UINT32 sCacheLineSize);

IMPORT STATUS cacheR5kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			       UINT32 iCacheSize, UINT32 iCacheLineSize,
			       UINT32 dCacheSize, UINT32 dCacheLineSize,
			       UINT32 sCacheSize, UINT32 sCacheLineSize);

IMPORT STATUS cacheR7kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			       UINT32 iCacheSize, UINT32 iCacheLineSize,
			       UINT32 dCacheSize, UINT32 dCacheLineSize,
			       UINT32 sCacheSize, UINT32 sCacheLineSize,
			       UINT32 tCacheSize, UINT32 tCacheLineSize);

IMPORT STATUS cacheR10kLibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
				UINT32 iCacheSize, UINT32 iCacheLineSize,
				UINT32 dCacheSize, UINT32 dCacheLineSize,
				UINT32 sCacheSize, UINT32 sCacheLineSize);

IMPORT STATUS cacheTx49LibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			        UINT32 iCacheSize, UINT32 iCacheLineSize,
			        UINT32 dCacheSize, UINT32 dCacheLineSize);

IMPORT STATUS cacheTx79LibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			        UINT32 iCacheSize, UINT32 iCacheLineSize,
			        UINT32 dCacheSize, UINT32 dCacheLineSize);

IMPORT STATUS cacheVr4131LibInit (CACHE_MODE instMode, CACHE_MODE dataMode,
			          UINT32 iCacheSize, UINT32 iCacheLineSize,
			          UINT32 dCacheSize, UINT32 dCacheLineSize,
			          UINT32 sCacheSize, UINT32 sCacheLineSize);

#endif	/* _ASMLANGUAGE */

#if defined (MIPSXX_sb1)
/* cache configuration attributes  */
#define CFG_K0_MASK			0x07
#define CFG_K0_EXCL_NOL2   0
#define CFG_K0_SHARED_NOL2 1
#define CFG_K0_UNCACHED    2
#define CFG_K0_CACHEABLE   3
#define CFG_K0_EXCL_COH    4
#define CFG_K0_COHERENT    5
#define CFG_K0_UNUSED      6
#define CFG_K0_ACCEL       7

#elif defined (MIPSXX_vr55xx)
/* cache configuration attributes */
#define CFG_CCA_RESERVED                0
#define CFG_CCA_WRTTHRU_ALLOC           1
#define CFG_CCA_UNCACHED                2
#define CFG_CCA_WRITEBACK               3
#define CFG_CCA_WRITETHRU               4
#define CFG_CCA_WRITEBACK_UNGUARDED     5
#define CFG_CCA_RESERVED2               6
#define CFG_CCA_UNCACHED_ACCELERATED    7

#elif  defined (MIPSXX_rm9xxx)
/* cache control config attributes  */
#define CFG_CCA_WRITETHRU               0
#define CFG_CCA_WRTTHRU_ALLOC           1
#define CFG_CCA_UNCACHED_BLK            2
#define CFG_CCA_WRITEBACK               3
#define CFG_CCA_COHERE_WRTBK_EXCL       4
#define CFG_CCA_COHERE_WRTBK            5
#define CFG_CCA_UNCACHED_NOBLK          6
#define CFG_CCA_FAST_PACKET_CACHE       7

#elif defined (MIPSXX_rm52xx)
/* cache control config attributes  */
#define CFG_CCA_WRITETHRU               0
#define CFG_CCA_WRTTHRU_ALLOC           1
#define CFG_CCA_UNCACHED                2
#define CFG_CCA_WRITEBACK               3
#define CFG_CCA_RESERVED1               4
#define CFG_CCA_RESERVED2               5
#define CFG_CCA_RESERVED3               6
#define CFG_CCA_RESERVED4               7
#endif /* MIPSXX_sb1 */

/* cache control attributes for pal */
#define CFG_CCA_ALIAS_CACHEABLE		 1
#define CFG_CCA_UNCACHED        	 2
#define CFG_CCA_CACHEABLE       	 3
#define CFG_CCA_COHERENT                 4
#define CFG_CCA_MASK                     7

#ifdef __cplusplus
}
#endif

#endif /* __INCcacheMipsLibh */
