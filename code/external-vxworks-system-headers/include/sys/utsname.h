#ifndef __Iutsname
#define __Iutsname

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(m88k) || defined(__m88k)
#define	SYS_NMLN	256
#elif defined(__dcc_linux)
#define	SYS_NMLN	65
#else
#define SYS_NMLN	9
#endif

struct utsname {
	char	sysname[SYS_NMLN];
	char	nodename[SYS_NMLN];
	char	release[SYS_NMLN];
	char	version[SYS_NMLN];
	char	machine[SYS_NMLN];
#ifdef __dcc_linux
	char	domainname[SYS_NMLN];
#endif
};

extern int uname(struct utsname *);

#ifdef	__cplusplus
}
#endif
#endif
