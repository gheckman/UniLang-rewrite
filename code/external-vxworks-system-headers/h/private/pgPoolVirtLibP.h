/* pgPoolVirtLibP.h - virtual page pool object library header file */

/* 
 * Copyright (c) 2003-2006, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,18sep09,zl   use fully qualified function pointer for pgPoolVirtRangeEach().
01g,17jun09,zl   updated for LP64 build
01f,20may09,pad  Reinstated previous prototype for pgPoolVirtNextFreeGet().
                 Fixed C code instead.
01e,20may09,pad  Fixed incorrect prototype for pgPoolVirtNextFreeGet().
01d,07jul06,zl   updated the pgPoolVirtAvailAlloc() arguments.
01c,21jul05,zl   updated pgPoolLib API
01b,13sep04,zl   converted to private header file.
01a,08jul03,yp   written.
*/

#ifndef __INCpgPoolVirtLibPh
#define __INCpgPoolVirtLibPh

/* includes */

#include <vxWorks.h>
#include <private/pgPoolLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef	_ASMLANGUAGE

/* function declarations */

extern STATUS	 pgPoolVirtLibInit (void);
extern STATUS	 pgPoolVirtAddToPool (PAGE_POOL_ID poolId, VIRT_ADDR addr,
				      size_t numPages, UINT state);
extern STATUS	 pgPoolVirtRemoveFromPool (PAGE_POOL_ID poolId, VIRT_ADDR addr,
					   size_t numPages);
extern VIRT_ADDR pgPoolVirtAlloc (PAGE_POOL_ID poolId, size_t numPages);
extern VIRT_ADDR pgPoolVirtAlignedAlloc (PAGE_POOL_ID poolId, size_t numPages,
					 size_t alignment);
extern VIRT_ADDR pgPoolVirtAllocAt (PAGE_POOL_ID poolId, VIRT_ADDR startAddr,
				    size_t numPages);
extern VIRT_ADDR pgPoolVirtAvailAlloc (PAGE_POOL_ID poolId, size_t numPagesReq,
				       size_t * pNumPagesGot);
extern STATUS	 pgPoolVirtFree (PAGE_POOL_ID poolId, VIRT_ADDR startAddr,
				 size_t numPages);
extern BOOL	 pgPoolVirtRangeIsFree (PAGE_POOL_ID poolId, VIRT_ADDR startAddr,
					size_t numPages);
extern BOOL	 pgPoolVirtRangeIsAllocated (PAGE_POOL_ID poolId,
					     VIRT_ADDR startAddr, 
					     size_t numPages);
extern BOOL	 pgPoolVirtRangeVerify (PAGE_POOL_ID poolId,
					VIRT_ADDR startAddr, size_t numPages);
extern STATUS	 pgPoolVirtNextFreeGet (PAGE_POOL_ID poolId, VIRT_ADDR addr, 
					VIRT_ADDR * pFreeAddr,
					size_t * pNumPages);
extern STATUS	 pgPoolVirtRangeEach (PAGE_POOL_ID poolId, UINT state,
				      STATUS (*usrRtn)
					(
					VIRT_ADDR virtAddr, 
					size_t numPages, 
					UINT state, 
					void * pArg
					), 
				      void * pArg);
#ifdef _WRS_CONFIG_LP64
extern void	 pgPoolVirtBaseSet (PAGE_POOL_ID poolId, VIRT_ADDR baseAddr);
#endif

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpgPoolVirtLibPh */
