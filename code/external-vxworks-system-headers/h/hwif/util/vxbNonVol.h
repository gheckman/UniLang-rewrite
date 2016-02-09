/* vxbNonVol.h - Management of non-volatile memory devices */

/*
 * Copyright (c) 2006-2009  Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
modification history
--------------------
01d,03nov09,h_k  added hwConf.h header inclusion.
01c,06may09,h_k  updated for lp64 support.
01b,26sep07,pmr  fix apigen error
01a,01Aug06,tor  created
*/

#ifndef INC_vxbNonVolH
#define INC_vxbNonVolH

#include <hwif/vxbus/hwConf.h>

/* typedefs */

typedef struct nvRamSegment NVRAM_SEGMENT;

struct nvRamSegment
    {
    char *        name;
    int           unit;
    void *        segAddr;
    size_t        segSize;
    };

/* forward declarations */

IMPORT STATUS vxbNonVolGet
    (
    char * drvName,     /* requestor's name */ 
    int    drvUnit,     /* requestor's unit number */
    char * buff,        /* buffer to copy non-volatile RAM into */ 
    off_t  offset,      /* offset from start of allocation unit */
    size_t strLen       /* maximum number of bytes to copy */ 
    );
IMPORT STATUS vxbNonVolSet
    (
    char * drvName,     /* requestor's name */
    int    drvUnit,     /* requestor's unit number */
    char * buff,        /* buffer to copy from, into non-volatile RAM */
    off_t  offset,      /* offset from start of allocation unit */
    size_t strLen       /* maximum number of bytes to copy */
    );
IMPORT STATUS nvRamSegDefGet
    (
    VXB_DEVICE_ID               pInst,
    HCF_DEVICE *                pHcf,
    NVRAM_SEGMENT **	        ppSegHd,
    int *                       pSegListCount
    );

#endif /* INC_vxbNonVolH */

