/* vxSimntLib.h - header for board dependent routines for Windows VxSim */

/* Copyright 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,01dec03,dbt  Fixed vxPowerDown prototype.
01a,01apr03,jmp	 written.
*/

#ifndef __INCvxSimntLibh
#define __INCvxSimntLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

IMPORT void	vxPowerDown (void);

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxSimntLibh */
