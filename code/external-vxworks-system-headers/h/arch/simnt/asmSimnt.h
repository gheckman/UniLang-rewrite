/* asmSimpentium.h - i86 simulator assembler definitions header file */

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

#ifndef	__INCasmSimpentiumh
#define	__INCasmSimpentiumh

#include <vsbConfig.h>

#ifdef _WRS_CONFIG_LP64

#ifdef _WRS_KERNEL
#if CPU==SIMNT
#include <arch/simnt/asmSimpentium64.h>
#elif CPU==SIMLINUX
#include <arch/simlinux/asmSimpentium64.h>
#endif
#else /* _WRS_KERNEL */
#include <arch/simpentium/asmSimpentium64.h>
#endif /* _WRS_KERNEL */

#else /* __WRS_CONFIG_LP64 */

#ifdef _WRS_KERNEL
#if CPU==SIMNT
#include <arch/simnt/asmSimpentium32.h>
#elif CPU==SIMLINUX
#include <arch/simlinux/asmSimpentium32.h>
#endif
#else /* _WRS_KERNEL */
#include <arch/simpentium/asmSimpentium32.h>
#endif /* _WRS_KERNEL */

#endif /* _WRS_CONFIG_LP64 */

#endif	/* __INCasmSimpentiumh */
