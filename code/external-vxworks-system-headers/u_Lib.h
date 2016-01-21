/* u_Lib.h - simulator UNIX/VxSim interface header */

/*
 * Copyright (c) 1992-1994, 1996, 2001, 2002, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
02k,12jun13,elp  cleanup obsolete declarations (WIND00409444).
02j,23dec02,jmp  added unix_statvfs (SPR #29024).
02i,08nov01,jmp  moved some structures from solaris/sysLib.c.
02h,24oct01,hbh  Added u_usleep, u_getppid, u_signal.
02g,19may98,dbt  added u_lockf prototype.
02f,20nov96,dvs  took out redundant u_sigprocmask entry during merge.
02e,23jul96,ism  added SIMSPARCSOLARIS support
02d,19jan94,gae  alphabetized.
02c,14dec93,gae  added setsid, system, execlp, fork.
02b,10jul93,gae  fixed dirent's.
02a,09jan93,gae  renamed from sysULib.h; discarded major portions.
01c,05aug92,gae  added non-ANSI forward declarations.
01b,29jul92,gae  added more prototypes; ANSIfied.
01a,04jun92,gae  written.
*/

/*
This header contains the prototype declarations for all UNIX
calls made by VxSim.
*/

#ifndef	INCu_Libh
#define	INCu_Libh

extern int u_open (char *name, int flags, int mode);

#endif	/* INCu_Libh */
