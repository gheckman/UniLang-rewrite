/* vxbPpc440gxPciBsp.h - IBM PowerPC 440GX Chip header */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,20jul07,rcs  created.
*/

#ifndef INCvxbPpc440gxPciBsph
#define INCvxbPpc440gxPciBsph

#ifdef __cplusplus
    extern "C" {
#endif

#define   BRDGOPT1_PLREQ      0x00000060
#define     BRDGOPT1_PLREQ_0  0x00000000
#define     BRDGOPT1_PLREQ_1  0x00000020
#define     BRDGOPT1_PLREQ_2  0x00000040
#define     BRDGOPT1_PLREQ_3  0x00000060



/*
 * Bit definitions for use with POM Size Attribute registers (PCIX0_POMxSA)
 */
#define POM_SIZE_MASK      0xFFF00000

#define POM_SIZE_1MB       0xFFF00000
#define POM_SIZE_2MB       0xFFE00000
#define POM_SIZE_4MB       0xFFC00000
#define POM_SIZE_8MB       0xFF800000
#define POM_SIZE_16MB      0xFF000000
#define POM_SIZE_32MB      0xFE000000
#define POM_SIZE_64MB      0xFC000000
#define POM_SIZE_128MB     0xF8000000
#define POM_SIZE_256MB     0xF0000000
#define POM_SIZE_512MB     0xE0000000
#define POM_SIZE_1GB       0xC0000000
#define POM_SIZE_2GB       0x80000000
#define POM_SIZE_4GB       0x00000000
#define POM_ENABLE         0x00000001
#define POM_UNUSED         0x00000000


/*
 * Bit definitions for use with PIM Size Attribute registers (PCIX0_PIMxSA)
 */
#define PIM_SIZE_MASK      0xFFFFFF00

#define PIM_SIZE_4KB       0xFFFFF000
#define PIM_SIZE_8KB       0xFFFFE000
#define PIM_SIZE_16KB      0xFFFFC000
#define PIM_SIZE_32KB      0xFFFF8000
#define PIM_SIZE_64KB      0xFFFF0000
#define PIM_SIZE_128KB     0xFFFE0000
#define PIM_SIZE_256KB     0xFFFC0000
#define PIM_SIZE_512KB     0xFFF80000
#define PIM_SIZE_1MB       0xFFF00000
#define PIM_SIZE_2MB       0xFFE00000
#define PIM_SIZE_4MB       0xFFC00000
#define PIM_SIZE_8MB       0xFF800000
#define PIM_SIZE_16MB      0xFF000000
#define PIM_SIZE_32MB      0xFE000000
#define PIM_SIZE_64MB      0xFC000000
#define PIM_SIZE_128MB     0xF8000000
#define PIM_SIZE_256MB     0xF0000000
#define PIM_SIZE_512MB     0xE0000000
#define PIM_SIZE_1GB       0xC0000000
#define PIM_SIZE_2GB       0x80000000
#define PIM_SIZE_4GB       0x00000000
#define PIM_PREFETCH       0x00000002
#define PIM_ENABLE         0x00000001
#define PIM_UNUSED         0x00000000



#ifdef __cplusplus
    }
#endif

#endif  /* INCvxbPpc440gxPciBsph */

