/* vrfsLib.h - header file for the Virtual Root File System component */

/* 
* Copyright (c) 2005 Wind River Systems, Inc. 
* 
* The right to copy, distribute, modify or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
01a,21dec05,rfr  written
*/

#ifndef __INCvrfsLibh
#define __INCvrfsLibh

#include <vxWorks.h>


#ifdef __cplusplus
extern "C" {
#endif

STATUS vrfsInit(void);
STATUS vrfsDevCreate(void);

#ifdef __cplusplus
}
#endif

#endif
