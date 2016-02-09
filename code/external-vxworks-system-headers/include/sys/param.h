/*
 * Since DNIX is not UNIX it would be nice if things that are
 * very deep in then implementation could stay out.
 * Note that this file is for inclusion by applications only.
 * Things that are visible only within the kernel should be kept out.
 */
/*
 * fundamental variables
 * don't change too often
 */

#ifdef	__mot68
#define	NOFILE	100		/* max open files per process */
#define	MAXPID	30000		/* max process id */

#define	BSIZE	512		/* Don't change this since dd(1) uses it as
				 * default buffer size which is
				 * DOCUMENTED to be 512 by ATT (sic) */
#define BSHIFT	9		/* This is 2LOG(BSIZE) and used tail (sic too) */
#define	MAXUID	60000		/* max user id */
#define	MAXLINK	1000		/* max links */

#define HZ	60

#define DHZ	HZ		/* Same as HZ */
#define	NCARGS	8192		/* # characters in exec arglist */

#define SCHMAX	127
#else
#define	NOFILE	72		/* max open files per process */
#define	MAXPID	30000		/* max process id */

#define	BSIZE	512		/* Don't change this since dd(1) uses it as
				 * default buffer size which is
				 * DOCUMENTED to be 512 by ATT (sic) */
#define BSHIFT	9		/* This is 2LOG(BSIZE) and used tail (sic too) */
#define	MAXUID	60000		/* max user id */
#define	MAXLINK	1000		/* max links */

#if defined( __LINUX_TARGET) || defined (__IRIX_TARGET) || defined(__SOLARIS_TARGET)
#define HZ	100
#else
#define HZ	(sysconf(3))
#endif

#define DHZ	HZ		/* Same as HZ */
#define	NCARGS	5120		/* # characters in exec arglist */

#define SCHMAX	127
#endif
/*
 * fundamental constants of the implementation--
 * cannot be changed easily
 */

#define	NBPW	sizeof(int)	/* number of bytes in an integer */
#define	NBPP	8192
#define	BPPSHIFT 13
#define	NBPC	2048
#define	BPCSHIFT	11
#define	NCPS	16
#define	NBPS	(NCPS*NBPC)

#ifndef	NULL
#define	NULL	0
#endif

#define	CMASK	0		/* default mask for file creation */
#define	CDLIMIT	(0x7fffffff)	/* default max write address */
#define	NODEV	(dev_t)(-1)
#define	ROOTINO	((ino_t)2)	/* i number of all roots */
#define	DIRSIZ	14		/* max characters per directory */

#define	lobyte(X)	(((unsigned char *)&X)[1])
#define	hibyte(X)	(((unsigned char *)&X)[0])
#define	loword(X)	(((ushort *)&X)[1])
#define	hiword(X)	(((ushort *)&X)[0])

