/* flbuffer.h - True Flash File System */

/*
 * Copyright (c) 1984-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,29jul04,alr  modified file header, restarted history
*/

#ifndef FLBUFFER_H
#define FLBUFFER_H

#include "flbase.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  unsigned char data[SECTOR_SIZE];	/* sector buffer */
  SectorNo	sectorNo;		/* current sector in buffer */
  void		*owner;			/* owner of buffer */
  FLBoolean	dirty;			/* sector in buffer was changed */
  FLBoolean	checkPoint;		/* sector in buffer must be flushed */
} FLBuffer;

#ifdef __cplusplus
}
#endif

#endif /* FLBUFFER_H */
