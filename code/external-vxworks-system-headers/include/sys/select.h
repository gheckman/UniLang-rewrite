/*      Definition module : socket.h
 
        Copyright 1999 Diab Data, USA
 
        Description :
        Berkeley socket standard header file
 
	4/14/99
*/

#ifndef	_SYS_SELECT_H
#define	_SYS_SELECT_H

#include <sys/types.h>
#include <sys/time.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields.
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= NOFILE (param.h).
 */
#ifndef	FD_SETSIZE
#define	FD_SETSIZE	1024
#endif

#ifndef NBBY		/* number of bits per byte */
#define	NBBY 8
#endif

typedef	long	fd_mask;
#define	NFDBITS	(sizeof (fd_mask) * NBBY)	/* bits per mask */
#ifndef	howmany
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#endif


typedef	struct fd_set {
	fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

#define	FD_SET(n, p)	((p)->fds_bits[(n)/NFDBITS] |= \
			    ((unsigned)1 << ((n) % NFDBITS)))

#define	FD_CLR(n, p)	((p)->fds_bits[(n)/NFDBITS] &= \
			    ~((unsigned)1 << ((n) % NFDBITS)))

#define	FD_ISSET(n, p)	((p)->fds_bits[(n)/NFDBITS] & \
			    ((unsigned)1 << ((n) % NFDBITS)))

#define	FD_ZERO(p)	memset((char *)(p), 0, sizeof (*(p)))

extern int select(int, fd_set *, fd_set *, fd_set *, struct timeval *);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SELECT_H */
