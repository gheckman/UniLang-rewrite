/* cavPko.h - Packet Output Processing Unit data types, macros and addresses */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,11may12,l_z  enable OCT_MAX_PORTS_PER_IFACE for all boards
01f,09dec11,x_f  add defines for OcteonII CN68xx
01e,07jul11,rlg  Setup for SDK TYPEDEFS only
01d,10jun11,d_c  Restore Cavium headers to original form, before splitting
                 struct defs to separate headers
01c,20oct10,d_c  Include SDK data types directly from SDK
01b,05oct10,d_c  Change ull to ULL to be Diab compatible
01a,06aug10,d_c  written
*/

#ifndef __INCcavPkoh
#define __INCcavPkoh

#include <arch/mips/private/cavSdkDrvInclude.h>
#define CAV_INCLUDE_TYPEDEFS_ONLY
#include CAV_SDK_DRV_INCLUDE(cvmx-utils.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-pko.h)
#include CAV_SDK_DRV_INCLUDE(cvmx-pko-defs.h)

#ifdef	__cplusplus
extern "C" {
#endif

/* defines */

#define CAV_PKO_REG_FLAGS               0x8001180050000000ULL
#define CAV_PKO_REG_CMD_BUF             0x8001180050000010ULL
#define CAV_PKO_REG_GMX_PORT_MODE       0x8001180050000018ULL
#define CAV_PKO_MEM_IPORT_PTRS          0x8001180050001030ULL
#define CAV_PKO_MEM_IQUEUE_PTRS         0x8001180050001040ULL

#define CAV_PKO_INDEX_BITS              12
#define CAV_PKO_INVALID_EID             31
#define CAV_CN68XX_PKO_MAX_PORT         128
#define CAV_PKO_PADDING_60              1

#define OCT_MAX_PORTS_PER_IFACE         16

#define OCT_MAX_IFACE_NUM               5

#define OCT_MAX_INDEX_NUM               4

/* typedefs */

typedef cvmx_pko_reg_gmx_port_mode_t    CAV_PKO_REG_GMX_PORT_MODE_T;
typedef cvmx_pko_reg_cmd_buf_t          CAV_PKO_REG_CMD_BUF_T;
typedef cvmx_pko_reg_flags_t            CAV_PKO_REG_FLAGS_T;
typedef cvmx_pko_command_word0_t        CAV_PKO_COMMAND_WORD0_T;
#if (OCTEON_MODEL == OCTEON_CN68XX)
typedef cvmx_pko_mem_iport_ptrs_t       CAV_PKO_MEM_IPORT_PTRS_T;
typedef cvmx_pko_mem_iqueue_ptrs_t      CAV_PKO_MEM_IQUEUE_PTRS_T;
#endif /* (OCTEON_MODEL == OCTEON_CN68XX) */

typedef enum
{
    CAV_PKO_SUCCESS               = CVMX_PKO_SUCCESS,
    CAV_PKO_INVALID_PORT          = CVMX_PKO_INVALID_PORT,
    CAV_PKO_INVALID_QUEUE         = CVMX_PKO_INVALID_QUEUE,
    CAV_PKO_INVALID_PRIORITY      = CVMX_PKO_INVALID_PRIORITY,
    CAV_PKO_NO_MEMORY             = CVMX_PKO_NO_MEMORY
    
} CAV_PKO_STATUS_T;

/* functions */

IMPORT void cavPkoShutdown(void);
IMPORT void cavPkoEnable(void);
IMPORT int cavPkoBaseQueueGet
    (
    int port
    );
IMPORT int cavPkoNumQueuesGet
    (
    int port
    );

CAV_PKO_STATUS_T cavPkoPortConfig
    (
    uint64_t port,
    uint64_t base_queue,
    uint64_t num_queues,
    const uint64_t priority[]
    );
  
void cavPkoDoorbell
    (
    uint64_t port,
    uint64_t queue,
    uint64_t len
    );


#ifdef	__cplusplus
}
#endif
  
#endif /* __INCcavPkoh */
