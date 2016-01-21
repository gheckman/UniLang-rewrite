/* cavFpa.h - FPA functions, interface data types, macros and addresses */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01d,09nov10,d_c  Get FPA pool constants from SDK configuration
                 with cavFpaPoolInfoGet(FPA_POOL_INFO_T *);
01c,20oct10,d_c  Include SDK data types directly from SDK
01b,05oct10,d_c  Change ull to ULL to be Diab compatible
01a,06aug10,d_c  written
*/

#ifndef __INCcavFpah
#define __INCcavFpah

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-fpa-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_FPA_CTL_STATUS                     0x8001180028000050ULL

/* typedefs */

typedef cvmx_fpa_ctl_status_t   CAV_FPA_CTL_STATUS_T;

typedef struct
    {
    int packet_pool;
    int wqe_pool;
    int output_buffer_pool;
    int packet_pool_size;
    int wqe_pool_size;
    int output_buffer_pool_size;
    int output_buffer_pool_entries;
    } FPA_POOL_INFO_T;
    

/* functions */

IMPORT void cavFpaEnable(void);
IMPORT void cavFpaPoolInfoGet(FPA_POOL_INFO_T *);
IMPORT void *cavFpaAlloc
    (
    uint64_t pool
    );
IMPORT void cavFpaFree
    (
    void *ptr,
    uint64_t pool,
    uint64_t num_cache_lines
    );


#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavFpah */
