/* mipc_sm_adapt.h - MIPC-SM OS adaptation layer API */

/********************************************************************
The following file is dual licensed and is available under either 
the GPL version 2 or a Wind River commercial license.

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*********************************************************************
Copyright (c) 2008-2011 Wind River Systems, Inc.

The right to copy, distribute, modify, or otherwise make use
of this software may be licensed pursuant to the terms
of an applicable Wind River license agreement.

*********************************************************************/

/*
modification history
--------------------
02b,07jan11,jlk  Update license header
02a,04jan11,ste  validate MIPC settings, check timer as MACRO
01z,26oct10,ste  Add functions to allocate various structures
01y,26aug10,jlk  Make sure #ifdef __cplusplus starts after #includes
01x,01apr10,als  Initial changes in support of 64-bit memory addressing
01w,17sep09,als  Obsolete MIPC_DEBUG symbol
01v,09sep09,als  Correct minor statistics collection issues
01u,25aug09,bwa  Add mipc_sm_adapt_get_node_id() prototype.
01t,25aug09,jlk  WIND00178668 - MIPC flow control changes.
01s,12aug09,als  Fix MIPC_STATS_ADD to avoid risk of mismatching else clauses
01r,07aug09,als  Make socket descriptors simple positive integers
01q,05aug09,ebh  Testing
01p,04aug09,als  Convert shared memory offsets to use MIPC_OFFSET type
01o,02aug09,als  Add support for selective stats collection
01n,29jul09,als  Add support for per-bus statistics collection
01m,27jul09,als  Event queue rework
01l,24jul09,jlk  Event Q re-work.
01k,22jul09,als  Allow adaptation code to handle fatal errors detected by
                 common code
01j,02jul09,als  Renamed from mipc_sm_init.h
01i,16jun09,als  Enhance error path code during initialization
01h,02jun09,als  Rework system configuration/initialization as per HLD and CI
01g,28may09,als  Revise configuration based on MIPC 2.0 HLD feedback
01f,25may09,ebh  Code Inspection Modifications
01e,13may09,ebh  Add in max sockets macro
01d,18mar09,ebh  Add information storage in local memory about node on buses
01c,25feb09,ebh  Remove POLL macro as it is no longer supported
01b,19feb09,ebh  Collapse 3 packet pools into a single pool per bus
01a,15dec08,apa  Initial version.
*/

#ifndef __INC_mipc_sm_adapt_h
#define __INC_mipc_sm_adapt_h

#include <multios_ipc/mipc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MIPC compile options */

#undef  MIPC_CHECK_ARGS

#define MIPC_STATS_MODE 0
	/* 0 = no statistics; 1 = stats in local memory */
	/* (in future, may support: 2 = stats in shared memory) */
#define MIPC_STATS_FIELDS (0x000FFFFF)
	/* bitfield indicating which statistics fields are to be recorded */
	/* (only meaningful if MIPC_STATS_MODE > 0) */

/* MIPC shared memory size */

typedef MIPC_OFFSET MIPC_MEMSIZE;

/* MIPC configuration settings specified for this node */

struct mipc_sm_config
{
	char *busList;				/* ptr to bus info */
	uint32_t nodeBuffers;			/* default # of buffers per bus */
	uint32_t nodeMtu;			/* default buffer size per bus */
	uint32_t nodeMaxNodes;			/* default max # nodes per bus */
	uint32_t nodeMaxPorts;			/* default num ports per bus */
	 int32_t nodeEvents;			/* default # of events per bus */
	 int32_t nodeQos;			/* default quality of service */
	 int32_t nodeSockets;			/* number of sockets on node */
	uint32_t nodeInitMode;			/* SM initialization mode used by node */
	uint32_t nodeHeartbeatPeriod;		/* heartbeat period (ms) */
	void *systemPoolBaseAddr;		/* location of the SM region */
	MIPC_MEMSIZE systemPoolSize;		/* size of the SM region */
	uint32_t nodeIntId;			/* interrupt num of this node */
};

/* MIPC atomic statistics - must match struct mipc_stats & MIPC_STATS_FIELDS */

#define MIPC_STATS_BUFS_SENT		0
#define MIPC_STATS_BUFS_RCVD		1
#define MIPC_STATS_BYTES_SENT		2
#define MIPC_STATS_BYTES_RCVD		3
#define MIPC_STATS_BUFS_ALLOCATED	4
#define MIPC_STATS_BUFS_FREED		5
#define MIPC_STATS_BUF_CONG_WAIT 	6
#define MIPC_STATS_BUF_CONG_NO_WAIT	7
#define MIPC_STATS_BUF_AVAIL_SENT	8
#define MIPC_STATS_BUF_AVAIL_RCVD	9
#define MIPC_STATS_EXPRESS_MSGS_SENT	10
#define MIPC_STATS_EXPRESS_MSGS_RCVD	11
#define MIPC_STATS_BUFFER_NOT_AVAIL	12
#define MIPC_STATS_EVENT_NOT_AVAIL	13
#define MIPC_STATS_INTERRUPTS_SENT	14
#define MIPC_STATS_INTERRUPTS_RCVD	15
#define MIPC_STATS_INTERRUPTS_DEFERRED	16
#define MIPC_STATS_SOCKETS_BOUND	17
#define MIPC_STATS_SOCKETS_CLOSED	18
#define MIPC_STATS_SOCKET_RX_QUEUE_ERR	19

#define MIPC_NUM_STATS (sizeof(struct mipc_stats) / sizeof(uint32_t))

/* MIPC routines that OS adaptation code must call */

int mipc_sm_init(struct mipc_sm_config *config);
void mipc_sm_api_process_rx_events(uint16_t busId);

#if (MIPC_STATS_MODE > 0)
#define MIPC_STATS_ADD(stats, statId, value) \
	do { if (MIPC_STATS_FIELDS & (1 << statId)) \
		MULTIOS_ATOMIC_ADD(stats + statId, value); } while (0)
#else
#define MIPC_STATS_ADD(busId, statId, value) \
	do { } while (0)
#endif

struct mipc_sm_sys_config;
struct mipc_sm_node_config;
struct mipc_sm_bus_config;

/* OS adaptation routines that MIPC calls */

int mipc_sm_adapt_get_cpu_id(void);
int mipc_sm_adapt_get_node_id(void);
int mipc_sm_adapt_config_init(uint32_t maxBuses);
int mipc_sm_adapt_config_bus(uint16_t busId, uint16_t nodeId, int qos,
			     uint16_t intId, MULTIOS_ATOMIC *stats);
int mipc_sm_adapt_config_done(uint32_t maxBuses);
void mipc_sm_adapt_config_abort(void);
int mipc_sm_adapt_notify_node(uint16_t busId, uint16_t nodeId, uint16_t intId);
void mipc_sm_adapt_fatal_error(char *reason);

int mipc_sm_adapt_validate_settings(uint16_t num_buses,
                                    struct mipc_sm_sys_config *sys,
                                    struct mipc_sm_node_config *nodes,
                                    struct mipc_sm_bus_config *buses);

/* Functions use to allocate/free different type of data */

unsigned long *mipc_alloc_sock_user_handle(uint32_t number);
void mipc_free_sock_user_handle(unsigned long *ptr);

struct mipc_sm_socket *mipc_alloc_socket(uint32_t number);
void mipc_free_socket(struct mipc_sm_socket *ptr);

struct mipc_sm_rx_buffer *mipc_alloc_rx_buffer(int sd, uint32_t number);
void mipc_free_rx_buffer(int sd, struct mipc_sm_rx_buffer* ptr);

struct mipc_sm_conn_request *mipc_alloc_conn_request(int sd, uint32_t number);
void mipc_free_conn_request(int sd, struct mipc_sm_conn_request *ptr);

struct mipc_sm_local_port_info *mipc_alloc_local_port_info(int busId, uint32_t number);
void mipc_free_local_port_info(struct mipc_sm_local_port_info *ptr);

struct mipc_sm_local_peer_info *mipc_alloc_local_peer_info(int busId, uint32_t number);
void mipc_free_local_peer_info(struct mipc_sm_local_peer_info *ptr);

struct mipc_sm_local_bus_info *mipc_alloc_local_bus_info(uint32_t number);
void mipc_free_local_bus_info(struct mipc_sm_local_bus_info *ptr);

struct mipc_sm_bus_config *mipc_alloc_bus_config(uint32_t number);
void mipc_free_bus_config(struct mipc_sm_bus_config *ptr);

struct mipc_sm_node_config *mipc_alloc_node_config(uint32_t number);
void mipc_free_node_config(struct mipc_sm_node_config* ptr);

struct mipc_sm_sys_config *mipc_alloc_sys_config(void);
void mipc_free_sys_config(struct mipc_sm_sys_config *ptr);

static MULTIOS_INLINE void mipc_sm_adapt_check_timer(MULTIOS_TIMER_ID timer)
{
	MIPC_SM_ADAPT_CHECK_TIMER(timer);
}

#ifdef __cplusplus
}
#endif

#endif /* __INC_mipc_sm_adapt_h */

