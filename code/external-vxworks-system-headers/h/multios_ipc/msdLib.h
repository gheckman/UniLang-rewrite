/* msdLib.h - VxWorks centric MSD header file */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,18oct08,jlk  WIND00136113 - Configure multiple MSDs
01b,08aug08,jlk  Updated as per HLD review.
01a,17jul08,jlk  written.
*/

/*
DESCRIPTION

Definitions for the VxWorks version of the MSD component.
*/

#ifndef _MSD_LIB_H_
#define _MSD_LIB_H_

#include <sioLib.h>
#include <multios_ipc/msd.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS usrMsdInit(int, int, int, int, int, int, char *);

extern SIO_CHAN * msdCreate(void);
extern STATUS msdDestroy(SIO_CHAN *);
extern STATUS msdLibInit(int, int, int, int);

#ifdef __cplusplus
}
#endif

#endif /* _MSD_LIB_H_ */
