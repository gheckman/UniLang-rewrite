#ifndef __Isdirent
#define __Isdirent

#ifdef	__cplusplus
extern "C" {
#endif

struct dirent {				/* directory entries	*/
#if defined(m88k) || defined(__m88k)
	ino_t		d_ino;		/* inode number		*/
#else
	long		d_ino;		/* inode number		*/
#endif
	off_t		d_off;		/* offset of entry	*/
	unsigned short	d_reclen;	/* length of entry	*/
	char		d_name[1];	/* filename		*/
};

#define DIRENTBASESIZ	offsetof(struct dirent,d_name)
#define DIRENTSIZ(len)	((DIRENTBASESIZ + sizeof(long) + (len))/sizeof(long)*sizeof(long))

#define	MAXNAMLEN	512		/* max filename length	*/

#ifndef NAME_MAX
#define	NAME_MAX	(MAXNAMLEN - 1)
#endif

extern int getdents(int, char *, unsigned);

#ifdef	__cplusplus
}
#endif
#endif
