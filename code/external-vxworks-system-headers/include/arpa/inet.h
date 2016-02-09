/*      Definition module : inet.h
 
        Copyright 1999 Diab Data, USA
 
        Description :
        inet services
 
	11/25/1999
*/

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned long inet_addr(const char *cp);
extern unsigned long inet_lnaof(struct in_addr in);
extern struct in_addr inet_makeaddr(int net, int lna);
extern unsigned long inet_netof(struct in_addr in);
extern unsigned long inet_network(const char *cp);
extern char *inet_ntoa(struct in_addr in);
extern int inet_ntoa_r(struct in_addr in, char *buf, int buflen);

#ifdef __cplusplus
}
#endif

#endif /* _ARPA_INET_H */
