/* ethernet.h - ethernet header file */

/* Copyright 2001-2005 Wind River Systems, Inc. */

/*
 * Fundamental constants relating to ethernet.
 *
 * $FreeBSD: src/sys/net/ethernet.h,v 1.12.2.5 2000/07/19 21:43:52 archie Exp $
 *
 */

/*
modification history
--------------------
01m,09jan12,h_x  Move extern "C" after last header file include.
01l,12sep06,kch  Removed reference to struct ifnet.
01k,09sep06,kch  Cleanup for IPNet integration.
01j,07feb05,vvv  _KERNEL cleanup
01i,20nov03,niq  Remove copyright_wrs.h file inclusion
01h,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01g,04nov03,rlm  Ran batch header path update for header re-org.
01f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01e,20aug03,niq  Include cdefs.h for __BEGIN_DECLS definition (to correct
                 compilation issues
01d,10jun03,vvv  include netVersion.h
01c,09sep02,hsh  add c++ protection
01b,12sep01,ann  adding a definition for ETHERSMALL
01a,07aug01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
 */

#ifndef _NET_ETHERNET_H_
#define _NET_ETHERNET_H_

#ifdef _WRS_KERNEL

#include <netVersion.h>    

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The number of bytes in an ethernet (MAC) address.
 */
#define	ETHER_ADDR_LEN		6

/*
 * The number of bytes in the type field.
 */
#define	ETHER_TYPE_LEN		2

/*
 * The number of bytes in the trailing CRC field.
 */
#define	ETHER_CRC_LEN		4

/*
 * The length of the combined header.
 */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)

/*
 * The minimum packet length.
 */
#define	ETHER_MIN_LEN		64

/*
 * The maximum packet length.
 */
#define	ETHER_MAX_LEN		1518

/*
 * A macro to validate a length with
 */
#define	ETHER_IS_VALID_LEN(foo)	\
	((foo) >= ETHER_MIN_LEN && (foo) <= ETHER_MAX_LEN)

/*
 * Structure of a 10Mb/s Ethernet header.
 */
struct	ether_header {
	u_char	ether_dhost[ETHER_ADDR_LEN];
	u_char	ether_shost[ETHER_ADDR_LEN];
	u_short	ether_type;
};

/*
 * Structure of a 48-bit Ethernet address.
 */
struct	ether_addr {
	u_char octet[ETHER_ADDR_LEN];
};

#define	ETHERTYPE_PUP		0x0200	/* PUP protocol */
#define	ETHERTYPE_IP		0x0800	/* IP protocol */
#define	ETHERTYPE_ARP		0x0806	/* Addr. resolution protocol */
#define	ETHERTYPE_REVARP	0x8035	/* reverse Addr. resolution protocol */
#define	ETHERTYPE_VLAN		0x8100	/* IEEE 802.1Q VLAN tagging */
#define	ETHERTYPE_IPV6		0x86dd	/* IPv6 */
#define	ETHERTYPE_LOOPBACK	0x9000	/* used to test interfaces */
/* XXX - add more useful types here */

/*
 * The ETHERTYPE_NTRAILER packet types starting at ETHERTYPE_TRAIL have
 * (type-ETHERTYPE_TRAIL)*512 bytes of data followed
 * by an ETHER type (as given above) and then the (variable-length) header.
 */
#define	ETHERTYPE_TRAIL		0x1000		/* Trailer packet */
#define	ETHERTYPE_NTRAILER	16

#define	ETHERMTU	(ETHER_MAX_LEN-ETHER_HDR_LEN-ETHER_CRC_LEN)
#define	ETHERMIN	(ETHER_MIN_LEN-ETHER_HDR_LEN-ETHER_CRC_LEN)

/* Clarinet */
#define ETHERSMALL              60

/*
 * For device drivers to specify whether they support BPF or not
 */
#define ETHER_BPF_UNSUPPORTED	0
#define ETHER_BPF_SUPPORTED	1

#ifdef __cplusplus
}
#endif
#endif /* _WRS_KERNEL */    
#endif /* !_NET_ETHERNET_H_ */
