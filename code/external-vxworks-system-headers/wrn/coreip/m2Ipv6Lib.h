/* m2Ipv6Lib.h - VxWorks IPv6 MIB-II interface to SNMP Agent */

/* 
 * Copyright 2002-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01q,21jun10,h_x  Fix WIND00217113
01p,29apr10,pad  Moved extern C statement after include statements.
01o,05feb10,h_x  Support 64bit
01n,27dec06,kch  Removed references to the obsolete coreip virtual stack
                 headers.
01m,19jun06,jpb  Removed I960 check.
01l,07feb05,vvv  _KERNEL cleanup
01k,19sep04,spm  updated virtual stack startup: restored use of published
                 init routine and removed packing/unpacking parameters
01j,02feb04,pas  finished Zoltan's changes for new avlLib API
01i,20nov03,niq  Remove copyright_wrs.h file inclusion
01h,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01g,04nov03,rlm  Ran batch header path update for header re-org.
01f,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01e,22oct03,zl   updated for new avlLib API
01d,15sep03,vvv  updated path for new headers
01c,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01b,14may03,vvv  included m2Lib.h
01a,16apr02,ant  written
*/

#ifndef __INCm2Ipv6Libh
#define __INCm2Ipv6Libh

#include <cfgDefs.h>
#include <sys/socket.h>        /* needed by sockaddr usage in if.h */
#include <net/if.h>
#include <avlLib.h>
#include <m2Lib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IPV6ADDRESSLEN    16

/* Convert IPv6 address from network format to host format (or vice versa).
 * All parameters in m2Ipv6xxx functions that are of Ipv6 address type
 * are expected in host format. 
 */

#define NTOHL_IPV6ADDR(in6Addr) \
    { \
    uint32_t	   * p32; \
\
    p32 = (uint32_t *)in6Addr; \
    p32[0] = ntohl(p32[0]); \
    p32[1] = ntohl(p32[1]); \
    p32[2] = ntohl(p32[2]); \
    p32[3] = ntohl(p32[3]); \
    }

#define HTONL_IPV6ADDR(in6Addr) \
    { \
    uint32_t	   * p32; \
\
    p32 = (uint32_t *)in6Addr; \
    p32[0] = htonl(p32[0]); \
    p32[1] = htonl(p32[1]); \
    p32[2] = htonl(p32[2]); \
    p32[3] = htonl(p32[3]); \
    }

/* possible values for ipv6Forwarding */

#define M2_ipv6Forwarding_forwarding            1
#define M2_ipv6Forwarding_notForwarding         2

/* possible values for ipv6IfAdminStatus */

#define M2_ipv6IfAdminStatus_up                 1
#define M2_ipv6IfAdminStatus_down               2

/* possible values for ipv6IfOperStatus */

#define M2_ipv6IfOperStatus_up                  1
#define M2_ipv6IfOperStatus_down                2
#define M2_ipv6IfOperStatus_noIfIdentifier      3
#define M2_ipv6IfOperStatus_unknown             4
#define M2_ipv6IfOperStatus_notPresent          5

/* possible values for ipv6TcpConnState */

#define M2_ipv6TcpConnState_closed          	1
#define M2_ipv6TcpConnState_listen          	2
#define M2_ipv6TcpConnState_synSent         	3
#define M2_ipv6TcpConnStatee_synReceived     	4
#define M2_ipv6TcpConnState_established     	5
#define M2_ipv6TcpConnState_finWait1        	6
#define M2_ipv6TcpConnState_finWait2        	7
#define M2_ipv6TcpConnState_closeWait       	8
#define M2_ipv6TcpConnState_lastAck         	9
#define M2_ipv6TcpConnState_closing         	10
#define M2_ipv6TcpConnState_timeWait        	11
#define M2_ipv6TcpConnState_deleteTCB       	12

/* possible values for ipv6AddrType */

#define M2_ipv6AddrType_stateless           	1
#define M2_ipv6AddrType_stateful            	2
#define M2_ipv6AddrType_unknown            	3

/* possible values for ipv6AddrStatus */

#define M2_ipv6AddrStatus_preferred           	1
#define M2_ipv6AddrStatus_deprecated           	2
#define M2_ipv6AddrStatus_invalid           	3
#define M2_ipv6AddrStatus_inaccessible          4
#define M2_ipv6AddrStatus_unknown           	5

/* possible values for ipv6RouteType */

#define M2_ipv6RouteType_other           	1
#define M2_ipv6RouteType_discard           	2
#define M2_ipv6RouteType_local           	3
#define M2_ipv6RouteType_remote           	4

/* possible values for ipv6RouteProtocol */

#define M2_ipv6RouteProtocol_other           	1
#define M2_ipv6RouteProtocol_local           	2
#define M2_ipv6RouteProtocol_netmgmt           	3
#define M2_ipv6RouteProtocol_ndisc           	4
#define M2_ipv6RouteProtocol_rip           	5
#define M2_ipv6RouteProtocol_ospf          	6
#define M2_ipv6RouteProtocol_bgp          	7
#define M2_ipv6RouteProtocol_idrp           	8
#define M2_ipv6RouteProtocol_igrp           	9

/* possible values for ipv6NetToMediaType */

#define M2_ipv6NetToMediaType_other		1
#define M2_ipv6NetToMediaType_dynamic		2
#define M2_ipv6NetToMediaType_static 		3
#define M2_ipv6NetToMediaType_local		4

/* possible values for ipv6NetToMediaState */

#define M2_ipv6NetToMediaState_reachable	1
#define M2_ipv6NetToMediaState_stale		2
#define M2_ipv6NetToMediaState_delay		3
#define M2_ipv6NetToMediaState_probe		4
#define M2_ipv6NetToMediaState_invalid		5
#define M2_ipv6NetToMediaState_unknown		6

/* IPv6 General Group objects */

typedef struct m2Ipv6General
    {
    Mib2_Integer    ipv6Forwarding;
    Mib2_Integer    ipv6DefaultHopLimit;
    Mib2_Unsigned32 ipv6Interfaces;
    Mib2_TimeStamp  ipv6IfTableLastChange;
    } M2_IPV6_GENERAL;

/* values for ipv6GeneralSetEntry varToSet */

#define M2_varId_ipv6Forwarding                 1
#define M2_varId_ipv6DefaultHopLimit            2

/* IPv6 General Group set operation structure */

typedef struct ipv6GeneralSetEntry
    {
    Mib2_Unsigned    varToSet;
    Mib2_Integer     ipv6Forwarding;
    Mib2_Integer     ipv6DefaultHopLimit;
    } IPV6_GENERAL_SETENTRY;

/* values for ipv6IfSetEntry varToSet */

#define M2_varId_ipv6IfDescr                    1
#define M2_varId_ipv6IfIdentifier               2
#define M2_varId_ipv6IfIdentifierLength         4
#define M2_varId_ipv6IfAdminStatus              8

/* IPv6 if table set operation structure */

typedef struct ipv6IfSetEntry
    {
    Mib2_Unsigned      varToSet;
    Mib2_IfIndexOrZero ipv6IfIndex;
    Mib2_OctetString   ipv6IfDescr[M2DISPLAYSTRSIZE];
                                  /* XXX Do we really want to be able to set the if identifier?? ism */
    Mib2_OctetString  ipv6IfIdentifier[8];
    Mib2_Integer      ipv6IfIdentifierLength;
    Mib2_Integer      ipv6IfAdminStatus;
    } IPV6_IF_SETENTRY;

/* IPv6 TCP Connection Table Entry, RFC 2452 */

typedef struct
    {
    Mib2_OctetString   ipv6TcpConnLocalAddress [IPV6ADDRESSLEN];
    Mib2_Integer       ipv6TcpConnLocalPort;
    Mib2_OctetString   ipv6TcpConnRemAddress [IPV6ADDRESSLEN];
    Mib2_Integer       ipv6TcpConnRemPort;
    Mib2_IfIndexOrZero ipv6TcpConnIfIndex;	
    Mib2_Integer       ipv6TcpConnState;

    } M2_IPV6TCPCONNTBL;

/* IPv6 UDP Table Entry, RFC 2454 */

typedef struct
    {
    Mib2_OctetString        ipv6UdpLocalAddress [IPV6ADDRESSLEN];
    Mib2_Integer            ipv6UdpLocalPort;
    Mib2_IfIndexOrZero      ipv6UdpIfIndex;	

    } M2_IPV6UDPTBL;

/* IPV6 Address Prefix Table Entry, RFC 2465 */

typedef struct
    {
    Mib2_OctetString ipv6AddrPrefixAddress [IPV6ADDRESSLEN];
	Mib2_Integer	 ipv6AddrPrefixLength;
	Mib2_TruthValue  ipv6AddrPrefixOnLinkFlag;
	Mib2_TruthValue  ipv6AddrPrefixAutonomousFlag;
    Mib2_Unsigned32  ipv6AddrPrefixAdvPreferredLifetime;
    Mib2_Unsigned32  ipv6AddrPrefixAdvValidLifetime;
    } M2_IPV6ADDRPFXTBL;

/* IPV6 Address Table Entry, RFC 2465 */

typedef struct
    {
    Mib2_OctetString		ipv6AddrAddress [IPV6ADDRESSLEN];
    Mib2_Integer			ipv6AddrPfxLength;
    Mib2_Integer			ipv6AddrType;
    Mib2_TruthValue		ipv6AddrAnycastFlag;
    Mib2_Integer			ipv6AddrStatus;
    } M2_IPV6ADDRTBL;

/* IPV6 Routing objects */

typedef struct
    {
    Mib2_Gauge32     	ipv6RouteNumber;
    Mib2_Counter32    	ipv6DiscardedRoutes;
    } M2_IPV6ROUTE;

/* IPV6 Routing Table Entry, RFC 2465 */

typedef struct
    {
    Mib2_OctetString   	ipv6RouteDest [IPV6ADDRESSLEN];
	Mib2_Integer		ipv6RoutePfxLength;
    Mib2_Unsigned32     ipv6RouteIndex;
    Mib2_IfIndexOrZero  ipv6RouteIfIndex;
    Mib2_OctetString   	ipv6RouteNextHop [IPV6ADDRESSLEN];
	Mib2_Integer        ipv6RouteType;
	Mib2_Integer		ipv6RouteProtocol;
    Mib2_Integer32     	ipv6RoutePolicy;
    Mib2_Unsigned32     ipv6RouteAge;
    Mib2_Unsigned32     ipv6RouteNextHopRDI;
    Mib2_Unsigned32     ipv6RouteMetric;
    Mib2_Unsigned32   	ipv6RouteWeight;
    M2_OBJECTID     	ipv6RouteInfo;
    Mib2_TruthValue     ipv6RouteValid;   
    } M2_IPV6ROUTETBL;

/* IPV6 Addres Translation Table Entry, RFC 2465 */

typedef struct
    {
    Mib2_OctetString ipv6NetToMediaNetAddress [IPV6ADDRESSLEN];
    M2_PHYADDR		 ipv6NetToMediaPhysAddress;
	Mib2_Integer     ipv6NetToMediaType;
	Mib2_Integer     ipv6NetToMediaState;
    Mib2_TimeStamp   ipv6NetToMediaLastUpdated;
    Mib2_TruthValue  ipv6NetToMediaValid; 
    } M2_IPV6ATRANSTBL;

/* IPV6 ICMPv6 statistics table, RFC 2466 */

typedef struct
    {
    Mib2_Counter32	     ipv6IfIcmpInMsgs;
    Mib2_Counter32       ipv6IfIcmpInErrors;
    Mib2_Counter32       ipv6IfIcmpInDestUnreachs;
    Mib2_Counter32       ipv6IfIcmpInAdminProhibs;
    Mib2_Counter32       ipv6IfIcmpInTimeExcds;
    Mib2_Counter32       ipv6IfIcmpInParmProblems;
    Mib2_Counter32       ipv6IfIcmpInPktTooBigs;
    Mib2_Counter32       ipv6IfIcmpInEchos;
    Mib2_Counter32       ipv6IfIcmpInEchoReplies;
    Mib2_Counter32       ipv6IfIcmpInRouterSolicits;
    Mib2_Counter32       ipv6IfIcmpInRouterAdvertisements;
    Mib2_Counter32       ipv6IfIcmpInNeighborSolicits;
    Mib2_Counter32       ipv6IfIcmpInNeighborAdvertisements;
    Mib2_Counter32       ipv6IfIcmpInRedirects;
    Mib2_Counter32       ipv6IfIcmpInGroupMembQueries;
    Mib2_Counter32       ipv6IfIcmpInGroupMembResponses;
    Mib2_Counter32       ipv6IfIcmpInGroupMembReductions;
    Mib2_Counter32       ipv6IfIcmpOutMsgs;
    Mib2_Counter32       ipv6IfIcmpOutErrors;
    Mib2_Counter32       ipv6IfIcmpOutDestUnreachs;
    Mib2_Counter32       ipv6IfIcmpOutAdminProhibs;
    Mib2_Counter32       ipv6IfIcmpOutTimeExcds;
    Mib2_Counter32       ipv6IfIcmpOutParmProblems;
    Mib2_Counter32       ipv6IfIcmpOutPktTooBigs;
    Mib2_Counter32       ipv6IfIcmpOutEchos;
    Mib2_Counter32       ipv6IfIcmpOutEchoReplies;
    Mib2_Counter32       ipv6IfIcmpOutRouterSolicits;
    Mib2_Counter32       ipv6IfIcmpOutRouterAdvertisements;
    Mib2_Counter32       ipv6IfIcmpOutNeighborSolicits;
    Mib2_Counter32       ipv6IfIcmpOutNeighborAdvertisements;
    Mib2_Counter32       ipv6IfIcmpOutRedirects;
    Mib2_Counter32       ipv6IfIcmpOutGroupMembQueries;
    Mib2_Counter32       ipv6IfIcmpOutGroupMembResponses;
    Mib2_Counter32       ipv6IfIcmpOutGroupMembReductions;
    }  M2_IPV6IFICMPTBL;
                
/* IPV6 MLD Interface Table Entry, RFC 3019 */

typedef struct
    {
    Mib2_InterfaceIndex		mldInterfaceIfIndex;		/* Host compliance */
    Mib2_Unsigned32	        mldInterfaceQueryInterval;
	Mib2_RowStatus 			mldInterfaceStatus; 	/* Host compliance */
	Mib2_Unsigned32	        mldInterfaceVersion;
    Mib2_OctetString		mldInterfaceQuerier [IPV6ADDRESSLEN];	/* Host compliance */
    Mib2_Unsigned32	        mldInterfaceQueryMaxResponseDelay;
    Mib2_Counter32	        mldInterfaceJoins;
    Mib2_Gauge32	        mldInterfaceGroups;
    Mib2_Unsigned32	        mldInterfaceRobustness;
    Mib2_Unsigned32	        mldInterfaceLastListenQueryIntvl;
    Mib2_IfIndexOrZero		mldInterfaceProxyIfIndex;
    Mib2_TimeTicks	        mldInterfaceQuerierUpTime;
    Mib2_TimeTicks	        mldInterfaceQuerierExpiryTime;
    } M2_MLDINTERFACETBL;
 
/* IPV6 MLD Cache Table Entry, RFC 3019 */

typedef struct
    {
    Mib2_OctetString		mldCacheAddress [IPV6ADDRESSLEN];	/* Host compliance */
    Mib2_InterfaceIndex		mldCacheIfIndex;	/* Host compliance */
	Mib2_TruthValue			mldCacheSelf;		/* Host compliance */
    Mib2_OctetString		mldCacheLastReporter [IPV6ADDRESSLEN];
    Mib2_TimeTicks	        mldCacheUpTime;
    Mib2_TimeTicks	        mldCacheExpiryTime;
    Mib2_RowStatus			mldCacheStatus;		/* Host compliance */
    } M2_MLDCACHETBL;

/* function declarations */
 
#if defined(__STDC__) || defined(__cplusplus)

extern STATUS m2Ipv6Init(unsigned long maxRouteTableSize); 
extern STATUS m2Ipv6Delete (void);

extern STATUS m2Ipv6TcpInit (void);
extern STATUS m2Ipv6TcpConnEntryGet (int search, M2_IPV6TCPCONNTBL * pTcpConnEntry);
extern STATUS m2Ipv6TcpConnEntrySet (M2_IPV6TCPCONNTBL * pTcpConnEntry);
extern STATUS m2Ipv6TcpDelete (void);

extern STATUS m2Ipv6UdpInit (void);
extern STATUS m2Ipv6UdpTblEntryGet (int search, M2_IPV6UDPTBL * pUdpEntry);
extern STATUS m2Ipv6UdpDelete (void);

extern STATUS m2Ipv6IfInit (unsigned long maxRouteTableSize);
extern STATUS m2Ipv6IfGeneralGet(M2_IPV6_GENERAL * pIpv6Gen);
extern STATUS m2Ipv6IfGeneralSet(void * pIpv6IfReqEntry);
extern STATUS m2Ipv6IfTblEntryGet(int search,void * pIpv6IfReqEntry);
extern STATUS m2Ipv6IfTblEntrySet(void * pIpv6IfReqEntry);
extern STATUS m2Ipv6AddrTblEntryGet (int search, int * index, 
			M2_IPV6ADDRTBL * pIpAddrTblEntry);
extern STATUS m2Ipv6AddrPfxTblEntryGet (int search, int * index, 
			M2_IPV6ADDRPFXTBL * pIpAddrPfxTblEntry);
extern STATUS m2Ipv6RouteInfoGet (M2_IPV6ROUTE * pIpv6RouteInfo);
extern STATUS m2Ipv6RouteTblEntryGet (int search, M2_IPV6ROUTETBL * pIpRouteTblEntry);
extern STATUS m2Ipv6RouteTblEntrySet (M2_IPV6ROUTETBL *	pIpRouteTblEntry);
extern STATUS m2Ipv6AtransTblEntryGet (int search, int * index, 
			M2_IPV6ATRANSTBL * pReqIpAtEntry);
extern STATUS m2Ipv6AtransTblEntrySet (int index, M2_IPV6ATRANSTBL * pReqIpAtEntry);
extern STATUS m2Ipv6IfDelete (void);

extern STATUS m2Ipv6IfIcmpInit (void);
extern STATUS m2Ipv6IfIcmpTblGet (int search, int * index, M2_IPV6IFICMPTBL * pIcmpInfo);
extern STATUS m2Ipv6IfIcmpDelete (void);

extern STATUS m2Ipv6MldInit (void);
extern STATUS m2Ipv6MldIfTblEntryGet (int search, M2_MLDINTERFACETBL * pMldIfEntry);
extern STATUS m2Ipv6MldCacheTblEntryGet (int  search, M2_MLDCACHETBL * pMldCacheEntry);
extern STATUS m2Ipv6MldCacheTblEntrySet (M2_MLDCACHETBL * pMldCacheEntry);
extern STATUS m2Ipv6MldDelete (void);

extern M2_IFINDEX * m2Ipv6AvlSearch (AVLU_TREE root, UINT key);
extern M2_IFINDEX * m2Ipv6AvlSuccessorGet (AVLU_TREE root, UINT key);

#else   /* __STDC__ */

extern STATUS m2Ipv6Init(); 
extern STATUS m2Ipv6Delete ();

extern STATUS m2Ipv6TcpInit (void);
extern STATUS m2Ipv6TcpConnEntryGet ();
extern STATUS m2Ipv6TcpConnEntrySet ();
extern STATUS m2Ipv6TcpDelete ();

extern STATUS m2Ipv6UdpInit ();
extern STATUS m2Ipv6UdpTblEntryGet ();
extern STATUS m2Ipv6UdpDelete ();

extern STATUS m2Ipv6IfInit (); 
extern STATUS m2Ipv6IfGeneralGet();
extern STATUS m2Ipv6IfGeneralSet();
extern STATUS m2Ipv6IfTblEntryGet();
extern STATUS m2Ipv6IfTblEntrySet();
extern STATUS m2Ipv6AddrTblEntryGet ();
extern STATUS m2Ipv6AddrPfxTblEntryGet ();
extern STATUS m2Ipv6RouteInfoGet ();
extern STATUS m2Ipv6RouteTblEntryGet ();
extern STATUS m2Ipv6RouteTblEntrySet ();
extern STATUS m2Ipv6AtransTblEntryGet ();
extern STATUS m2Ipv6AtransTblEntrySet ();
extern STATUS m2Ipv6IfDelete ();

extern STATUS m2Ipv6IfIcmpInit ();
extern STATUS m2Ipv6IfIcmpTblGet ();
extern STATUS m2Ipv6IfIcmpDelete ();

extern STATUS m2Ipv6MldInit ();
extern STATUS m2Ipv6MldIfTblEntryGet ();
extern STATUS m2Ipv6MldCacheTblEntryGet ();
extern STATUS m2Ipv6MldCacheTblEntrySet ();
extern STATUS m2Ipv6MldDelete ();

extern void * m2Ipv6AvlSearch ();
extern void * m2Ipv6AvlSuccessorGet (); 

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCm2Ipv6Libh */
