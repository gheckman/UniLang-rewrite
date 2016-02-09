/* vxSimsolarisLib.h - header for board dependent routines for Solaris VxSim */

/* Copyright 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,01dec03,dbt  Fixed vxPowerDown prototype.
01a,25mar03,dbt	 written.
*/

#ifndef __INCvxSimsolarisLibh
#define __INCvxSimsolarisLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

IMPORT void	vxPowerDown (void);
IMPORT STATUS	vxWindowsFlush (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxSimsolarisLibh */
