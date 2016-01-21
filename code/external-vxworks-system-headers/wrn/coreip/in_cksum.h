/* 
 * Copyright 1984-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,19jun06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
01e,14jan05,vvv  osdep.h cleanup
01d,23sep04,kc   Added coldfire arch support.
01c,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/2)
01b,08dec03,dat  fix CPU_FAMILY names
01a,04dec03,xli  creation
*/

/*
DESCRIPTION
This file is a wrapper of in_cksum.h which include specific in_cksum.h  
depend on the CPU_FAMILY
*/

#ifndef _IN_CKSUM_H_
#define _IN_CKSUM_H_

#include <vxWorks.h>

/* The following includes are from target/h/arch */

#if(_VX_CPU_FAMILY==_VX_ARM)
#include <arch/arm/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_MIPS) 
#include <arch/mips/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_I80X86)
#include <arch/i86/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_PPC)
#include <arch/ppc/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_SH)
#include <arch/sh/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_COLDFIRE)
#include <arch/coldfire/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_SIMNT)
#include <arch/simnt/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_SIMLINUX)
#include <arch/simlinux/in_cksum.h>

#elif (_VX_CPU_FAMILY==_VX_SIMSPARCSOLARIS)
#include <arch/simsolaris/in_cksum.h>

#endif

#endif
