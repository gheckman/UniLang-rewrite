/* pciIntLib.h - PCI Interrupt support public constants header file */

/*
 * Copyright (c) 1984-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01d,28apr09,h_k  updated for LP64 support.
01c,19jun00,dat  added pciIntDisconnect2, SPR 31194
01b,04mar98, tm  moved pciIntRtn structure to private header file
01a,24feb98, tm  derived from pciIomapLib.h v01a from ebsa285 BSP
*/

#ifndef __INCpciIntLibh
#define __INCpciIntLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PCI_IRQ_LINES
#define PCI_IRQ_LINES   32
#endif /* PCI_IRQ_LINES */

#ifndef _ASMLANGUAGE

STATUS pciIntLibInit	(void);
STATUS pciIntConnect	(VOIDFUNCPTR * vec, VOIDFUNCPTR rtn, _Vx_usr_arg_t arg);
STATUS pciIntDisconnect	(VOIDFUNCPTR * vec, VOIDFUNCPTR rtn);
STATUS pciIntDisconnect2(VOIDFUNCPTR * vec, VOIDFUNCPTR rtn, _Vx_usr_arg_t arg);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpciIntLibh */
