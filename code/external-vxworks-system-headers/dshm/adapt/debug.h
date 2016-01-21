/* debug.h - dSHM adaptation layer-specifics debugging */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,03nov10,mze  IA CPU tag work
01d,21sep10,sem  Add new IA cpus. Remove pentium2/3
01c,29apr10,pad  Moved extern C statement after include statements.
01b,21dec06,bwa  added timestamps.
01a,29jul06,bwa  written.
*/

#ifndef __INCdshmAdaptDebugh
#define __INCdshmAdaptDebugh

#include <stdio.h>
#include <logLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if DSHM_DEBUG
    #if DSHM_EXTRA_DEBUG
        /* VxBus iteration options */
	#define ITERATE_I_OPTIONS (VXB_ITERATE_INSTANCES|VXB_ITERATE_VERBOSE)
	#define ITERATE_O_OPTIONS (VXB_ITERATE_ORPHANS|VXB_ITERATE_VERBOSE)
	extern int usrBusDebugLevel;
    #else
	#define ITERATE_I_OPTIONS (VXB_ITERATE_INSTANCES)
	#define ITERATE_O_OPTIONS (VXB_ITERATE_ORPHANS)
    #endif
    /* turning local symbols into global symbols */
    #ifdef LOCAL
	#undef LOCAL
	#define LOCAL
    #endif
#else
    #define ITERATE_OPTIONS	(VXB_ITERATE_ORPHANS)
#endif
    
#if DSHM_TIMESTAMP
    #if (CPU==MIPS32 || CPU==MIPS64)
    #if 0
	extern int sysCountGet (void);
        #define DSHM_TIMESTAMP_GET()	sysCountGet()
    #else
    extern int sysProcNum;
	#define DSHM_TIMESTAMP_GET(n)	\
		n ? (*((uint16_t*)(0x8000061a))) : (*((uint16_t*)(0x80000618)))
	#define DSHM_TIMESTAMP_INC() \
	    do { \
		(*((uint16_t*)(sysProcNum ? 0x8000061a: 0x80000618)))++; \
		DSHM_MEM_BARRIER(); \
	    } while ((0))
    #endif
    #elif (CPU==SIMNT || CPU==SIMSPARCSOLARIS || CPU==SIMLINUX)
        #define DSHM_TIMESTAMP_GET(n)	tickGet()
	#define DSHM_TIMESTAMP_INC()
    #elif (CPU==PPC32)
        #define DSHM_TIMESTAMP_GET(n)	tickGet()
	#define DSHM_TIMESTAMP_INC()
    #elif (CPU==PENTIUM || CPU==PENTIUM4 || CPU==_VX_ATOM || CPU==_VX_CORE || CPU==_VX_NEHALEM)
        #define DSHM_TIMESTAMP_GET(n)	tickGet()
	#define DSHM_TIMESTAMP_INC()
    #else
        #error "Unknown CPU type"
    #endif
#else /* DSHM_TIMESTAMP */
    #define DSHM_TIMESTAMP_GET()	0
#endif /* DSHM_TIMESTAMP */

#ifdef __cplusplus
}
#endif

#endif /* __INCdshmAdaptDebugh */

