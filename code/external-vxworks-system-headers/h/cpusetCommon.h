/* cpusetCommon.h - common cpuset_t and phys_cpuset_t access macros */
/*
 * Copyright (c) 2006-2007, 2009-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,14feb12,zl   use paranthesis around macro arguments (WIND00332849)
                 moved phys_cpuset access macros to cpuset.h
01f,28apr10,pad  Moved extern C statement after include statements.
01e,25jan10,d_c  SMP M-N updates: Add phys_cpu_t access macros. Add
                 CPUSET_LAST_INDEX macro.
01d,28apr09,cww  Use fixed sized atomic operators
01d,02feb09,cww  Add support for dynamic CPU reservation
01c,17oct07,kk   add comment to indicate updates here should also be done in
                 cpuset.c
01b,18jun07,mmi  Added CPUSET_ATOMICCOPY()
01a,13jun07,jmg  Created from cpuset.h.
*/

#ifndef __INCcpusetCommonh
#define __INCcpusetCommonh

#include <base/b_cpuset_t.h>
#include <vxAtomicLib.h>
#include <ffsLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* 
 * WARNING: Any updates made here should also be
 * review for doc updates in src/os/cpuset.c file
 * for both kernel and user side.
 */

/* set of macros to manipulate the cpuset_t type */

#define CPUSET_ATOMICCOPY(cpusetDst, cpusetSrc)				\
	vxAtomic32Set ((atomic32_t *) &(cpusetDst), (atomic32Val_t) (cpusetSrc))
#define CPUSET_ATOMICSET(cpuset, n)					\
	vxAtomic32Or ((atomic32_t *) &(cpuset), 1 << (n))
#define CPUSET_ATOMICCLR(cpuset, n)					\
	vxAtomic32And ((atomic32_t *) &(cpuset), ~(1 << (n)))

#define CPUSET_SET(cpuset, n)               ((cpuset) |= (1 << (n)))
#define CPUSET_ISSET(cpuset, n)             ((cpuset) & (1 << (n)))
#define CPUSET_CLR(cpuset, n)               ((cpuset) &= ~(1 << (n)))
#define CPUSET_ZERO(cpuset)                 ((cpuset) = 0)
#define CPUSET_ISZERO(cpuset)	            ((cpuset) == 0)

#define CPUSET_FIRST_SET(cpuset) 					\
	((int)(cpuset) & (int)-(cpuset))
#define CPUSET_FIRST_INDEX(cpuset) 					\
	(FFS_LSB (cpuset) - 1)
#define CPUSET_LAST_INDEX(cpuset) 					\
	(FFS_MSB (cpuset) - 1)
#define CPUSET_ADD(cpusetAugend,cpusetAddend)				\
	((cpusetAugend) |= (cpusetAddend))
#define CPUSET_SUB(cpusetMinuend,cpusetSubtrahend)			\
	((cpusetMinuend) &= ~(cpusetSubtrahend))

#ifdef __cplusplus
}
#endif

#endif /* __INCcpuseCommonth */
