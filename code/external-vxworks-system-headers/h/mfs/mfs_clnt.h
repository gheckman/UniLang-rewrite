/* mfs_clnt.h - header for mfs_clnt.c */

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
01a,03sep10,hps  written
*/

#ifndef __INCmfs_clnt_h
#define __INCmfs_clnt_h

#include <multios_ipc/mipc.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int mfs_clntinit(char *busname, int servpt, int numsos);
extern int mfs_exportshow(UINT16 srvnode);
#if     0
extern int mfs_exportshowall(void);
#endif
extern int mfs_mount(UINT16 srvnode, char *exportname,
                     char *localname, int flags);
extern int mfs_unmount(char *localname);
extern int mfs_getmtusize(void);
extern int mfs_zalloc(int fd, int size, UINT8 **zbuf,
                      MIPC_ZBUFFER *zhdl, int flags);
extern int mfs_zfree(int fd, MIPC_ZBUFFER zhdl);
extern int mfs_zread(int fd, UINT8 **zbuf, MIPC_ZBUFFER *zhdl, int size);
extern int mfs_zwrite(int fd, UINT8 *zbuf, MIPC_ZBUFFER zhdl, int size);

#ifdef __cplusplus
}
#endif

#endif  /* __INCmfs_clnt_h */
