/* vbiShmem.h - Virtual Interface memory utility functions */

/* 
 * Copyright (c) 2007-2012 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01o,16aug12,c_t  delete vbiVbRamSizeFind for safety profile.WIND00369921
01n,07may12,c_t  Add support for 64bit MIPC 3.0.
01m,28mar11,jlv  Add new prototype for WIND00262654
01l,24may10,jl   Sync with HV 1.2 25-May-10
01k,29apr10,pad  Moved extern C statement after include statements.
01j,03mar10,rgo  sync with hv1.2 3/3/10
01i,18aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD
                 HV 01g,14jul09,mmi  update with vbiStatus_t return type
01h,17jul09,to   change return type for VBI 2.0 (from v01g for HV 1.1)
01g,13jul09,to   add private memory function (from v01f for HV 1.1)
01f,16dec08,to   modified for vxWorks
01e,12dec08,mmi  replace razor with wrhv
01d,11dec08,mmi  use typedef's instead natives
01c,20nov08,mmi  adopt new naming convention
01b,26nov07,foo  update prototype
01a,25may07,foo  written
*/

/*
DESCRIPTION

This header file declares the vbi API for managing memory regions

*/

#ifndef __INCvbiShmemh
#define __INCvbiShmemh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* type defines */

typedef struct vbiShmemMapInfo
    {
    void*                  gpa;            /* guest physical address */
    void*                  gva;            /* guest virtual address */
    uint64_t               length;         /* memory region length */
    } VBI_SHMEM_MAP_INFO; 

/* externs */

extern void vbiShmemInfoInit (void);

extern vbiStatus_t vbiShmemInfoRec
    (
    void *    gpa,       /* start guest physical address */
    void *    gva,       /* start guest virtual address */
    uint32_t  length     /* region length */
    );

extern vbiStatus_t vbiShmemFindGVAByGPA
    (
    void *    gpa,       /* guest physical address */
    void **   gva       /* guest virtual address,output */
    );

extern vbiStatus_t vbiShmemRegionFind
    (
    int8_t *    smName,      /* String name of the region */
    void * *    addr,        /* Location - OUT */
    uint32_t *  length,      /* Length - OUT */
    uint32_t *  attr         /* MMU Attributes - OUT */
    );

extern vbiStatus_t vbiMemRegionFind
    (
    int8_t *    name,        /* String name of the region */
    void * *    addr,        /* Location - OUT */
    uint32_t *  length,      /* Length - OUT */
    uint32_t *  attr         /* MMU Attributes - OUT */
    );

/* find the base address and length of a core's private memory */

extern vbiStatus_t vbiCorePrvMemFind (void * * addr, size_t *  length);

#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && \
    !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
extern vbiStatus_t vbiVbRamSizeFind
    (
    vbiVb_t  boardID,
    size_t * physicalMemorySize
    );
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

/* convert WRHV MMU attributes to vmLib vxWorks attributes */

extern UINT vbiWrhvMmuAttrToVmLibAttr (uint32_t attr);


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvbiShmemh */
