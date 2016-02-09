/* adrSpaceArchLibP.h - address space header file for x86_64 */

/* 
 * Copyright (c) 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01c,14apr10,zl   changed RTP private region base to 2M
01b,23dec09,zl   fixed shared region base address.
01a,24aug09,zl   created with 64-bit region definitions.
*/

#ifndef __INCadrSpaceArchLibPh
#define __INCadrSpaceArchLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* virtual memory region definitions */

#define RTP_PRIVATE_RGN_BASE		0x0000000000200000UL
#define RTP_PRIVATE_RGN_SIZE		0x000007ffffe00000UL

#define SHARED_RGN_BASE			0x0000780000000000UL
#define SHARED_RGN_SIZE			0x0000080000000000UL

#define KERNEL_VIRT_POOL_RGN_BASE	0xffff800000000000UL
#define KERNEL_VIRT_POOL_RGN_SIZE	0x0000080000000000UL

#define KERNEL_DIRECT_MAP_RGN_BASE	0xfffff00000000000UL
#define KERNEL_DIRECT_MAP_RGN_SIZE	0x0000080000000000UL

#define KERNEL_SYS_MEM_RGN_BASE		0xffffffff80000000UL
#define KERNEL_SYS_MEM_RGN_SIZE		0x0000000080000000UL


#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceArchLibPh */
