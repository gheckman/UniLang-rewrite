/* instrSimpentium.h - i86 simulator assembler definitions header file */

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
01a,12feb10,elp  written to select 32 or 64bits version
*/

#ifndef	__INCinstrSimpentiumh
#define	__INCinstrSimpentiumh

#include <vsbConfig.h>

#ifdef _WRS_CONFIG_LP64

#ifdef _WRS_KERNEL
#if CPU==SIMNT
#include <arch/simnt/instrSimpentium64.h>
#elif CPU==SIMLINUX
#include <arch/simlinux/instrSimpentium64.h>
#endif
#else /* _WRS_KERNEL */
#include <arch/simpentium/instrSimpentium64.h>
#endif /* _WRS_KERNEL */

#else /* __WRS_CONFIG_LP64 */

#ifdef _WRS_KERNEL
#if CPU==SIMNT
#include <arch/simnt/instrSimpentium32.h>
#elif CPU==SIMLINUX
#include <arch/simlinux/instrSimpentium32.h>
#endif
#else /* _WRS_KERNEL */
#include <arch/simpentium/instrSimpentium32.h>
#endif /* _WRS_KERNEL */

#endif /* _WRS_CONFIG_LP64 */

#endif	/* __INCinstrSimpentiumh */
