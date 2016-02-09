#ifndef __Itypes
#define __Itypes

#include <xmacros.h>

_C_LIB_DECL

typedef	unsigned short	ushort;
typedef	unsigned int	uint;
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

#ifdef	__mot68
typedef unsigned short	use_t;
#else
typedef unsigned char	use_t;
#endif

typedef short		cnt_t;

#ifndef __size_t
#define	__size_t
_TYPE_size_t;
#endif

#if !defined(__time_t) && !defined(_TIME_T)
#define __time_t 
typedef	size_t		time_t;
#endif 

typedef	long		off_t;
typedef	long		paddr_t;
typedef	long		key_t;

#if !defined(__clock_t) && !defined(_CLOCK_T)
#define __clock_t 
typedef size_t		clock_t;
#endif

typedef	char *		caddr_t;
typedef	char *		laddr_t;

typedef	struct { int r[1]; } *	physadr;

#if defined(m88k) || defined(__m88k)
typedef	unsigned long	ino_t;
typedef	unsigned long	mode_t;
typedef long		pid_t;
typedef	unsigned long	dev_t;
typedef	unsigned long	uid_t;
typedef	unsigned long	gid_t;
typedef unsigned long	nlink_t;
typedef	long		daddr_t;
#else
typedef	unsigned short	ino_t;
typedef	int		mode_t;
typedef short		pid_t;
typedef	short		dev_t;
#ifdef  __mot68
typedef	unsigned short	uid_t;
typedef	unsigned short	gid_t;
#else
typedef	int		uid_t;
typedef	int		gid_t;
#endif
typedef short		nlink_t;
typedef	unsigned long	daddr_t;
#endif

_END_C_LIB_DECL

#endif
