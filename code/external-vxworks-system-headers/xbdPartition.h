/* xbdPartition.h - XBD partition manager */

/* 
* Copyright (c) 2005-2006, 2009-2010, 2013 Wind River Systems, Inc. 
* 
* The right to copy, distribute, modify or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Wind River license agreement. 
*/

/*
modification history
-------------------- 
01g,11sep13,m_y  move partition type defination in header file
01f,09apr13,xwu  fix WIND00405596 Bootable disk creation failure 
01e,29apr10,pad  Moved extern C statement after include statements.
01d,17jul09,lyc  added partLibcreate for LP64 support
01d,16jul09,yjl  modify for Defect:  WIND00142601,add a funtion to create part
                 according to part size (M bytes)
01c,12apr06,dee  SPR 119990, WIND00037359 - add cplusplus constructs
01b,15sep05,pcm  added xbdCreatePartition()
01a,05may05,rfr  written
*/

#ifndef __INCxbdPartitionh
#define __INCxbdPartitionh

#include <drv/xbd/xbd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PART_DOS_EXTENDED    0x05
#define PART_WIN95_EXTENDED  0x0f
#define PART_PMBR            0xEE


extern device_t xbdPartitionDevCreate (device_t subDev);
extern STATUS   xbdCreatePartition    (char * pathName, int nPart,
                                       int size1, int size2, int size3);
extern STATUS   partLibCreate         (int fd,int nPart,int size1,
                                       int size2,int size3);
extern STATUS   xbdCreatePartitionSz    (char * pathName, int nPart,
                                         int size1, int size2, int size3);
extern int      getHiddenSectorsFromDPT (device_t subDev, UINT32 *pHiddenSectors);
extern device_t xbdGptPartDevCreate (device_t subDev);
#ifdef __cplusplus
}
#endif

#endif /* __INCxbdPartitionh */
