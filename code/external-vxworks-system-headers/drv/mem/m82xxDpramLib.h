/* m82xxDpramLib.h - 82xx DPRAM memory allocation driver */

/* Copyright 1984-2001, 2010 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,26nov01,rcs   renamed m82xxDpramLib.h and moved to target/h/drv/mem
01b,17jul01,g_h   cleaning and renaming to sys82xxDpramLib.h
01a,16jul01,p_h   created
*/

/*
DESCRIPTION
This module contains m82xx DPRAM memory allocation driver.
*/

#ifndef __INCm82xxDpramh
#define __INCm82xxDpramh

#include "vxWorks.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Define part */
#define ALLOCTABLESIZE 64

typedef struct ADDR_RESOURCE
    {
    UINT32                 start;
    UINT32                 size;
    struct ADDR_RESOURCE * pNext;
    } ADDR_RESOURCE;

typedef struct
    {
    UINT32          start;
    UINT32          limit;
    ADDR_RESOURCE * pHead;
    } POOL;

/* Prototypes */

void  m82xxDpramLibInit (void);
void* m82xxDpramMalloc (size_t Length);
void* m82xxDpramAlignedMalloc (size_t Length, size_t Alignment);
void  m82xxDpramFree (void* Addr);
void* m82xxDpramFccMalloc (size_t Length, size_t Alignment);
void  m82xxDpramFccFree (void* Addr);

#ifdef __cplusplus
}
#endif
	  
#endif /* __INCm82xxDpramh */
