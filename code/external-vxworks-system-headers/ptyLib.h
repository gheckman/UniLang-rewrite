/* ptyLib.h - UNIX library for allocating pseudo-terminal devices */

/* Copyright 1992-2002, 2014 Wind River Systems, Inc. */

/* modification history
-----------------------
06jan14,p_x  remove the obsolete codes; include ptyDrv.h (WIND00447946)
02b,08may02,dat  cplusplus protection SPR 74987
02a,14dec93,gae  tweaked for the simulator.
01h,19aug93,c_s  Added ptySetNonBlocking (); mod history corrected.
01g,18aug93,c_s  Adjusted Ultrix port.
01f,17aug93,c_s  Added ptySetCanonical ().
01e,02aug93,c_s  Added #include of <sys/stropts.h> in the svr4 streams case.
01d,18sep92,c_s  Ported to Ultrix.
01c,16sep92,c_s  Ported to IRIX.  Adjusted port to HP-UX.
01b,10sep92,maf  conditionally include <sys/ioctl.h> or <sys/filio.h> based
		   on presence of HP-UX predefined macro "hpux."
01a,09jul92,c_s  Adapted from PtyConnection.h (in C++).
*/

/* use ptyDrv.h to replace obsolete ptyLib.h */

#ifndef	INCptyLibh
#define	INCptyLibh

#include <ptyDrv.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif	/* INCptyLibh */
