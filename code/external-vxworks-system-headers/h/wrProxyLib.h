/* wrProxyLib.h - Wind River proxy interface header */

/*
 * Copyright (c) 2005-2006,2008,2011,2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01g,12jan12,elp  added wrProxySerialRegister(),wrProxyAmioProtRegister().
01f,24may11,rlp  Defined wrProxyTcpSockRegister prototype for runtime as well.
01f,22apr11,rlp  Moved wrProxySslCertGen prototype to wrProxyLibP.h.
01e,22mar11,rlp  Added SSL support.
01d,23jul08,dbt  Updated wrProxyLibInit() prototype. Added MIPC support
01c,21jun06,dbt  Updated wrProxyLibInit() prototype
		 Moved proxy version macro from wrProxyLib.c file.
01b,22aug05,dbt  Added TIPC support for host proxy.
01a,15apr05,dbt  written
*/

#ifndef __INCwrProxyLibh
#define __INCwrProxyLibh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define	WRPROXY_VERSION		"1.2"	/* proxy version */

/* function declarations */

extern STATUS	wrProxyAmioProtRegister (void);
extern void	wrProxyUdpSockRegister (void);
extern void	wrProxyTipcSockRegister (void);
extern void	wrProxyMipcSockRegister (void);
extern void	wrProxyTcpSockRegister (void);
extern void	wrProxySerialRegister (void);
#ifdef	_WRS_CONFIG_SSL
extern STATUS	wrProxySslLibInit (char * certRepo);
#endif	/* _WRS_CONFIG_SSL */
#ifdef	HOST
extern STATUS	wrProxyLibInit (unsigned short portNumber, char * initString,
				BOOL hasControlPort);
#else	/* HOST */
extern STATUS	wrProxyLibInit (UINT16 portNumber, char * initString,
				    BOOL useSsl,
				    BOOL hasControlPort, UINT32 priority,
				    UINT32 stackSize, UINT32 options);
#endif	/* HOST */

#ifdef __cplusplus
}
#endif

#endif	/* __INCwrProxyLibh */
