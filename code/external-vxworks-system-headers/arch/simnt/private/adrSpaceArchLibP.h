/* adrSpaceArchLibP.h - address space header file for x86_64 */

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
01a,01feb10,elp   created from x86_64 with 64-bit region definitions.
*/

#ifndef __INCadrSpaceArchLibPh
#define __INCadrSpaceArchLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* virtual memory region definitions */

#define KERNEL_SYS_MEM_RGN_BASE		\
    (adrSpaceArchRgnBaseGet(ADR_SPACE_ARCH_KERNEL_SYS_MEM_RGN))
#define KERNEL_SYS_MEM_RGN_SIZE		\
    (adrSpaceArchRgnSizeGet(ADR_SPACE_ARCH_KERNEL_SYS_MEM_RGN))

#define KERNEL_VIRT_POOL_RGN_BASE 	\
    (adrSpaceArchRgnBaseGet(ADR_SPACE_ARCH_KERNEL_VIRT_POOL_RGN))
#define KERNEL_VIRT_POOL_RGN_SIZE	\
    (adrSpaceArchRgnSizeGet(ADR_SPACE_ARCH_KERNEL_VIRT_POOL_RGN))

#define KERNEL_DIRECT_MAP_RGN_BASE	\
    (adrSpaceArchRgnBaseGet(ADR_SPACE_ARCH_KERNEL_DIRECT_MAP_RGN))
#define KERNEL_DIRECT_MAP_RGN_SIZE 	\
    (adrSpaceArchRgnSizeGet(ADR_SPACE_ARCH_KERNEL_DIRECT_MAP_RGN))

#define SHARED_RGN_BASE		\
    (adrSpaceArchRgnBaseGet(ADR_SPACE_ARCH_SHARED_RGN))
#define SHARED_RGN_SIZE		\
    (adrSpaceArchRgnSizeGet(ADR_SPACE_ARCH_SHARED_RGN))

#define RTP_PRIVATE_RGN_BASE	\
    (adrSpaceArchRgnBaseGet(ADR_SPACE_ARCH_RTP_PRIV_RGN))
#define RTP_PRIVATE_RGN_SIZE	\
    (adrSpaceArchRgnSizeGet(ADR_SPACE_ARCH_RTP_PRIV_RGN))

#define ADR_SPACE_ARCH_RGN_NUM	5	/* number of regions */

/* typedefs */

typedef enum 
    {
    ADR_SPACE_ARCH_KERNEL_SYS_MEM_RGN = 0, 
    ADR_SPACE_ARCH_KERNEL_VIRT_POOL_RGN = 1,
    ADR_SPACE_ARCH_KERNEL_DIRECT_MAP_RGN = 2,
    ADR_SPACE_ARCH_SHARED_RGN = 3,
    ADR_SPACE_ARCH_RTP_PRIV_RGN = 4
    } ADR_SPACE_ARCH_RGN_TYPE;

/* BSP configured values */

extern VIRT_ADDR sysKernelSysMemRgnBase;
extern size_t sysKernelSysMemRgnSize;
extern VIRT_ADDR sysRtpPrivMemRgnBase;
extern size_t sysRtpPrivMemRgnSize;
extern VIRT_ADDR sysSharedMemRgnBase;
extern size_t sysSharedMemRgnSize;
extern VIRT_ADDR sysKernelVirtPoolMemRgnBase;
extern size_t sysKernelVirtPoolMemRgnSize;

extern VIRT_ADDR adrSpaceArchRgnBaseGet (ADR_SPACE_ARCH_RGN_TYPE rgnType);
extern size_t adrSpaceArchRgnSizeGet (ADR_SPACE_ARCH_RGN_TYPE rgnType);
#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceArchLibPh */
