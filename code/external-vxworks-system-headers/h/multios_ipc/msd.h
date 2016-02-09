/* msd.h - MIPC Serial Device Header File */

/********************************************************************
The following file is dual licensed and is available under either 
the GPL version 2 or a Wind River commercial license.

*********************************************************************
Copyright (c) 2008-2009,2011 Wind River Systems, Inc.

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
Copyright (c) 2008-2009,2011 Wind River Systems, Inc.

The right to copy, distribute, modify, or otherwise make use
of this software may be licensed pursuant to the terms
of an applicable Wind River license agreement.

*********************************************************************/

/*
modification history
--------------------
01l,07jan11,jlk  Update license header
01k,18nov09,als  Revise MSD single threading to work with Linux (WIND00190478)
01j,05nov09,ebh  Add socket locks to single thread access to MIPC
01i,23jun09,jlk  Code inspection changes
01h,02mar09,jlk  Linux work
01g,23apr09,ebh  Add in MIPC_AF family type
01f,25aug08,jlk  Updated as per code review.
01e,08aug08,jlk  Updated as per HLD review.
01d,07jul08,jlk  TTY adaptation
01c,26jun08,jlk  Conversion from mpipe to mio
01b,07may08,jlk  Bug fixes.
01a,11apr08,jlk  Written.
*/
#ifndef __INCmsdh
#define __INCmsdh

/* This header file is shared with VxWorks */
#ifdef _WRS_KERNEL
#define __KERNEL__
#endif

#ifdef __KERNEL__
/* Includes */
/* 
 * These are needed for kernel (VxWorks or Linux) apps and the MSD kernel code 
 * itself 
 */
#include <multios_ipc/mipc.h>
#include <multios_ipc/multios_adapt.h>

#endif	/* __KERNEL__ */

#ifdef __cplusplus
extern "C" {
#endif

/* Shared between kernel and user */

#ifdef MIPC_BUS_NAME_MAX_LEN
#define MSD_BUS_NAME_LEN  MIPC_BUS_NAME_MAX_LEN
#else
#define MSD_BUS_NAME_LEN 20
#endif


/* typedefs */
struct msd_endpoint_set {
	unsigned short node;
	unsigned char  instance;
	char bus_name[MSD_BUS_NAME_LEN];
};

struct msd_endpoint_get {
	unsigned short node;
	unsigned char  instance;
	unsigned char  up;
	char bus_name[MSD_BUS_NAME_LEN];
};

/* ioctls */
#if (defined (_WRS_KERNEL) || defined (_VX_CPU))
/* 
 * The VxWorks way.
 * _WRS_KERNEL for VxWorks kernel apps. _VX_CPU for VxWorks RTP apps
 */
#define MSD_SET_ENDPOINT ((int)0x80000001)
#define MSD_GET_ENDPOINT ((int)0x80000002)
#else
/* The Linux way */
#include <linux/ioctl.h>
#define MSD_SET_ENDPOINT	_IOW('$', 1, struct msd_endpoint_set)
#define MSD_GET_ENDPOINT	_IOR('$', 1, struct msd_endpoint_get)
#endif

#ifdef __KERNEL__

	#ifndef MSD_DEBUG_LEVEL
	#define MSD_DEBUG_LEVEL 0
	#endif

	/* Debug macros */
	#define MSD_DBG1(x)
	#define MSD_DBG2(x)
	#define MSD_DBG3(x)
	#define MSD_DBG4(x)
	#define MSD_DBG5(x)
	#define MSD_DBG6(x)
	#define MSD_DBG7(x)
	#define MSD_DBG8(x)

	#if MSD_DEBUG_LEVEL > 0
	#undef  MSD_DBG1
	#define MSD_DBG1(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 1
	#undef  MSD_DBG2
	#define MSD_DBG2(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 2
	#undef  MSD_DBG3
	#define MSD_DBG3(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 3
	#undef  MSD_DBG4
	#define MSD_DBG4(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 4
	#undef  MSD_DBG5
	#define MSD_DBG5(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 5
	#undef  MSD_DBG6
	#define MSD_DBG6(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 6
	#undef  MSD_DBG7
	#define MSD_DBG7(x) x
	#endif
	#if MSD_DEBUG_LEVEL > 7
	#undef  MSD_DBG8
	#define MSD_DBG8(x) x
	#endif
#else
	/* Non-kernel code */
	#ifdef MSD_DEBUG_LEVEL
	#undef MSD_DEBUG_LEVEL
#endif

#endif /* __KERNEL__ */

/* defines */
/* Defines the MSD product version */
#define MSD_MAJOR_VERSION MIPC_VERSION_MAJOR
#define MSD_MINOR_VERSION MIPC_MINOR_VERSION

/* Defines the MSD protocol version */
#define MSD_PROTO_MAJOR_VER 0x01
#define MSD_PROTO_MINOR_VER 0x00

#define MSD_BASE_NAME "msd"

#define MSD_PORT_NUM 1

/* This can't be more than 254 */
#define MSD_MAX_DEVS 128

#define MSD_DOMAIN   MIPC_AF
#define MSD_PROTOCOL 0

#ifdef __KERNEL__
/* Command op codes */
#define MSD_OP_NOP  0
#define MSD_OP_SEND 1

/* private macros */

#define MSD_FREE_DEV(m) ((m)->in_use = 0)

#define MSD_HDR_DATA_SZ 4
struct msd_hdr {
	uint8_t  op;	  /* op code */
	uint8_t  dev_id;  /* identifier */
	uint8_t  ver_maj; /* major version number */
	uint8_t  ver_min; /* minor version number */
	char     data[MSD_HDR_DATA_SZ]; /* payload. */
};

struct msd_addr {
	struct mipc_sockaddr mipc_addr;
	uint8_t instance;
};

struct msd_device {
	int mipc_socket;
	struct msd_addr local_addr;
	struct msd_addr remote_addr;
	int in_use;
	int up;
	int bound;
	int tx_start;
	int mtu;
	int tx_bufs;
	void *os_data;
	char bus_name[MSD_BUS_NAME_LEN];
};

struct msd_socket_lock {
	int in_use;		/* this lock entry is active (or not) */
	MULTIOS_SEM sem;	/* the lock */
};

typedef void (*msd_handle_rx_data_func)(struct msd_device *, struct msd_hdr *, int);
typedef void (*msd_tx_start_func)(struct msd_device *);

void msd_close_socket (struct msd_device *);
int msd_connect_endpoint (struct msd_device *, struct msd_endpoint_set *);
struct msd_device * msd_find_free_dev (uint8_t *);
void msd_send (struct msd_device *, struct msd_hdr *, MIPC_ZBUFFER, int,
	uint8_t);
struct msd_device * msd_init (msd_handle_rx_data_func, msd_tx_start_func);
#endif /* __KERNEL__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCmsdh */
