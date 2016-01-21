/* simNetEndDrv.h - END style Simulator Ethernet driver header */

/*
 * Copyright (c) 2003-2004,2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01b,08feb08,elp  opacified simnet_pkt type.
01a,15apr04,elp  added defines to get/set parameters.
01a30jul03,elp written.
*/

#ifndef __INCsimEndh
#define __INCsimEndh

#ifdef __cplusplus
extern "C" {
#endif

/* SIMNET defines */

/* macros to get SUBNET information from vxsimnetd */
#define SIMNET_SUBNET_MTU		1	/* get subnet mtu */
#define SIMNET_SUBNET_PHYS_ADDRLEN	2	/* get MAC address length */
#define SIMNET_SUBNET_BROAD_ADDRESS	3	/* get subnet bcast address */
#define SIMNET_SUBNET_ADDRESS		4	/* get subnet address */
#define SIMNET_SUBNET_MASK		5	/* get subnet mask */
#define SIMNET_SUBNET_ADDRESSV6		6	/* get subnet IPv6 prefix */
#define SIMNET_SUBNET_ADDRESSV6_LEN	7	/* get subnet IPv6 prefix len */
#define SIMNET_SUBNET_BROADCAST		8 	/* broadcast support ? */
#define SIMNET_SUBNET_MULTICAST		9	/* multicast support ? */

/* macro to get/set NODE information */
#define SIMNET_NODE_PHYS_ADDRESS	10	/* node MAC address */
#define SIMNET_NODE_INTERRUPT		11	/* node interrupt enabled */
#define SIMNET_NODE_PROMISCUOUS		12	/* node promiscuous */
#define SIMNET_NODE_MULTICAST		13	/* node multicasting */
#define SIMNET_NODE_ADDRESS		14	/* node address */
#define SIMNET_NODE_ADDRESSV6		15	/* IPv6 node address */

#ifdef __cplusplus
}
#endif

#endif /* __INCsimNetEndDrvh */

