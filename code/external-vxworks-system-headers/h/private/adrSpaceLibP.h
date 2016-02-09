/* adrSpaceLibP.h - Address Space Library header */

/* 
 * Copyright (c) 2004-2005,2007-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01p,08sep10,pcs  Add an entry to represent the global virtual memory region
                 size to struct adrSpaceInitParams.
01o,02jun10,elp  added SIMNT/SIMLINUX 64 bits support.
01n,29apr10,pad  Moved extern C statement after include statements.
01m,14apr10,jpb  Added function pointer declarations.
01l,09mar10,pad  Reorganized ADR_SPACE_INIT_PARAMS structure so that only the
		 localMemLocalAdrs field is defined for VxWorks 64-bit.
01k,27oct09,pcs  Rearranged struct adrSpaceInitParams entries while adding
                 support for RTP's in LP64.
01j,12oct09,zl   added adrSpaceOptimizedSizeGet()and RAM pool allocation option
01i,17sep09,zl   added directMapRAMSize.
01h,24aug09,zl   updated map and alloc options; added 64-bit arch header
01g,22jun09,zl   updated for LP64 build
01f,18apr08,pcs  Add prototypes for adrSpaceOverlapPageAlloc and
                 adrSpaceOverlapNodesRemove.
01e,24apr07,pcs  Add prototype for adrSpacePageVirtPhysFree.
01d,09sep05,zl   removed ADR_SPACE_RGN_CTL structure.
01c,27jun05,zl   added new alloc, free, map, unmap APIs and options.
01b,22sep04,zl   post-inspection fixes.
01a,31aug04,zl   created.
*/

#ifndef __INCadrSpaceLibPh
#define __INCadrSpaceLibPh

/* includes */

#include <vxWorks.h>
#include <vmLib.h>
#include <private/vmLibP.h>		/* VIRT_SEG_INFO */

#ifdef _WRS_CONFIG_LP64

#if (CPU_FAMILY==I80X86)
#include <arch/i86/x86_64/private/adrSpaceArchLibP.h>
#elif (CPU_FAMILY==SIMNT)
#include <arch/simnt/private/adrSpaceArchLibP.h>
#elif (CPU_FAMILY==SIMLINUX)
#include <arch/simlinux/private/adrSpaceArchLibP.h>
#endif

#endif /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
extern "C" {
#endif

/* address space types */

#define ADR_SPACE_TYPE_KERNEL		0x00000001
#define ADR_SPACE_TYPE_RTP		0x00000000
#define ADR_SPACE_TYPE_MASK		0x00000001

/* 
 * the alloc and map options are defined so that they don't 
 * overlap with the MMU attributes and VM mapping options, since they
 * can be OR-ed together. MMU attributes use 0x000fffff. VM
 * map options use 0x00f00000.
 */

#define ADR_SPACE_OPT_CONTIG		0x80000000
#define ADR_SPACE_OPT_NONCONTIG		0x00000000
#define ADR_SPACE_OPT_CONTIG_MASK	0x80000000

#define ADR_SPACE_OPT_MAPPED		0x40000000
#define ADR_SPACE_OPT_UNMAPPED		0x00000000
#define ADR_SPACE_OPT_MAPPED_MASK	0x40000000

#define ADR_SPACE_OPT_OPTIMIZED		0x20000000
#define ADR_SPACE_OPT_UNOPTIMIZED	0x00000000
#define ADR_SPACE_OPT_OPTIMIZE_MASK	0x20000000

#define ADR_SPACE_OPT_NOPHYSALLOC	0x10000000
#define ADR_SPACE_OPT_PHYSALLOC		0x00000000
#define ADR_SPACE_OPT_PHYSALLOC_MASK	0x10000000

#define ADR_SPACE_OPT_RGN_KERNEL	0x08000000
#define ADR_SPACE_OPT_RGN_DIRECT	0x04000000
#define ADR_SPACE_OPT_RGN_SHM		0x02000000
#define ADR_SPACE_OPT_RGN_MASK		0x0e000000

/*
 * the address space map attributes are a combination of the MMU attributes,
 * the VM mapping options, the contiguous and optimized mapping options.
 * 
 * The address space allocation attributes are a combination of all of 
 * the above, plus the region and the mapped options.
 */

#define ADR_SPACE_OPT_MAP_MASK		(ADR_SPACE_OPT_CONTIG_MASK   | \
					 ADR_SPACE_OPT_OPTIMIZE_MASK | \
					 ADR_SPACE_OPT_PHYSALLOC_MASK| \
					 VM_MAP_OPTIONS_MASK	     | \
					 VM_ATTR_ALL)

#define ADR_SPACE_OPT_ALLOC_MASK	(ADR_SPACE_OPT_MAP_MASK      | \
					 ADR_SPACE_OPT_MAPPED_MASK   | \
					 ADR_SPACE_OPT_RGN_MASK)

/* unmap and free attributes */

#define ADR_SPACE_OPT_PHYS_NOFREE	0x00000001
#define ADR_SPACE_OPT_PHYS_FREE		0x00000000
#define ADR_SPACE_OPT_PHYS_FREE_MASK	0x00000001

/* address space model configuration values */

#define ADR_SPACE_MODEL_FLAT            1
#define ADR_SPACE_MODEL_OVERLAPPED      2

#ifndef _ASMLANGUAGE

/* typedefs */

typedef struct adrSpaceInitParams
    {
#ifdef _WRS_CONFIG_USE_MEMDESC
    VIRT_ADDR   	localMemLocalAdrs;	/* where memory begins */
#else /* _WRS_CONFIG_USE_MEMDESC */
    PHYS_MEM_DESC *	pPhysMemDesc;		/* physMemDesc pointer */
    int 		physMemDescNumEnt;	/* number of elements */
    VIRT_ADDR   	localMemLocalAdrs;	/* where memory begins */
    VIRT_ADDR   	kernelMemTop;		/* top of kernel mem (heap) */
    VIRT_ADDR   	rtpRgnBase;		/* RTP overlapped rgn base */
    size_t        	rtpRgnSize;		/* RTP overlapped rgn size */
    size_t        	globalVirtMemRgnSize;	/* global virt mem rgn size */
    BOOL		rtpRgnIsOverlapped;     /* is RTP space overlapped? */
#endif /* _WRS_CONFIG_USE_MEMDESC */
    } ADR_SPACE_INIT_PARAMS;

/* globals */

extern UINT		adrSpaceModel;		/* flat or overlapped  */
extern PAGE_POOL_ID	globalRAMPgPoolId;
extern PAGE_POOL_ID	kernelVirtPgPoolId;
#ifdef _WRS_CONFIG_LP64
extern PAGE_POOL_ID	shmRgnPgPoolId;
extern size_t		directMapRAMSize;
#else
extern PAGE_POOL_ID	userRgnPoolId;
extern PAGE_POOL_ID	kernelRgnPoolId;
#endif
extern size_t		rtpCodeSize;
extern VIRT_ADDR	rtpCodeStart;

extern ADR_SPACE_INIT_PARAMS * pAsInitParams;

/* base level function prototypes */

extern STATUS 	adrSpaceLibInit (ADR_SPACE_INIT_PARAMS * pInitParams);
extern STATUS 	adrSpaceShowInit (void);

extern VIRT_ADDR adrSpacePageAlloc (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAddr,
				    PHYS_ADDR physAddr, size_t numPages,
				    UINT options);
extern STATUS	adrSpacePageFree (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAddr,
				  size_t numPages, UINT options);
extern STATUS	adrSpacePageMap (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAdr, 
				 PHYS_ADDR physAdr, size_t numPages, 
				 UINT options);
extern STATUS	adrSpacePageUnmap (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAdr, 
				   size_t numPages, UINT options);

extern STATUS	adrSpacePageVirtPhysFree (VM_CONTEXT_ID vmContext, 
                                  VIRT_ADDR virtAddr, PHYS_ADDR physAddr,
                                  size_t numPages, UINT options);
extern STATUS	adrSpaceOptimizedSizeGet (ULONG addr, size_t numPages,
					  size_t * pAlignSize, 
					  size_t * pNumPages);

#ifdef _WRS_CONFIG_LP64
extern VIRT_ADDR adrSpaceDirectBaseGet (void);
#endif

/* function pointer prototypes */

extern VIRT_SEG_INFO *       (*_func_virtSegInfoGet)(UINT * pNumElems);
extern VIRT_EXTRA_MAP_INFO * (*_func_virtExtraMapInfoGet)(int descNum);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceLibPh */
