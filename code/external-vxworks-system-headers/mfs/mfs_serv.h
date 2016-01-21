/* mfs_serv.h - header for mfs_serv.c */

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
01b,26nov10,hps  make priorities of server tasks user configurable
                 and other minor changes
01a,03sep10,hps  written
*/

#ifndef __INCmfs_serv_h
#define __INCmfs_serv_h

#ifdef __cplusplus
extern "C" {
#endif

extern int mfs_servinit(char *busname, int reqport,
                        int recvtskprio, int proctskprio, int proctsks);
extern int mfs_export(char *dirname, int options);
extern int mfs_unexport(char *dirname, int options);

#ifdef __cplusplus
}
#endif

#endif  /* __INCmfs_serv_h */
