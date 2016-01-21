/* cavMix.h - MIX interface data types, macros and addresses */

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
01b,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01a,15oct10,d_c  written
*/

#ifndef __INCcavMixh
#define __INCcavMixh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-mixx-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_MIXX_ADDR(addr, offset) (addr + (offset & 1) * 2048)

#define CAV_MIXX_BIST(offset) \
  CAV_MIXX_ADDR(0x8001070000100078ULL, offset)

#define CAV_MIXX_CTL(offset) \
  CAV_MIXX_ADDR(0x8001070000100020ULL, offset)

#define CAV_MIXX_INTENA(offset) \
  CAV_MIXX_ADDR(0x8001070000100050ULL, offset)

#define CAV_MIXX_ORCNT(offset) \
  CAV_MIXX_ADDR(0x8001070000100040ULL, offset)

#define CAV_MIXX_ORING1(offset) \
  CAV_MIXX_ADDR(0x8001070000100000ULL, offset)

#define CAV_MIXX_ORING2(offset) \
  CAV_MIXX_ADDR(0x8001070000100008ULL, offset)

#define CAV_MIXX_ORHWM(offset) \
  CAV_MIXX_ADDR(0x8001070000100038ULL, offset)

#define CAV_MIXX_IRING1(offset) \
  CAV_MIXX_ADDR(0x8001070000100010ULL, offset)

#define CAV_MIXX_IRING2(offset) \
  CAV_MIXX_ADDR(0x8001070000100018ULL, offset)

#define CAV_MIXX_ISR(offset) \
  CAV_MIXX_ADDR(0x8001070000100048ULL, offset)

#define CAV_MIXX_IRCNT(offset) \
  CAV_MIXX_ADDR(0x8001070000100030ULL, offset)

#define CAV_MIXX_IRHWM(offset) \
  CAV_MIXX_ADDR(0x8001070000100028ULL, offset)

/* typedefs */

typedef cvmx_mixx_bist_t   CAV_MIXX_BIST_T;
typedef cvmx_mixx_ctl_t    CAV_MIXX_CTL_T;
typedef cvmx_mixx_intena_t CAV_MIXX_INTENA_T;
typedef cvmx_mixx_ircnt_t  CAV_MIXX_IRCNT_T;
typedef cvmx_mixx_irhwm_t  CAV_MIXX_IRHWM_T;
typedef cvmx_mixx_iring1_t CAV_MIXX_IRING1_T;
typedef cvmx_mixx_isr_t    CAV_MIXX_ISR_T;
typedef cvmx_mixx_orcnt_t  CAV_MIXX_ORCNT_T;
typedef cvmx_mixx_orhwm_t  CAV_MIXX_ORHWM_T;
typedef cvmx_mixx_oring1_t CAV_MIXX_ORING1_T;
typedef cvmx_mixx_oring2_t CAV_MIXX_ORING2_T;
typedef cvmx_mixx_oring2_t CAV_MIXX_ORING2_T;

#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavMixh */
