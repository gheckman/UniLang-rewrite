#ifndef __Iioctl
#define __Iioctl

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef __dcc_linux

#define _IOC_NRBITS	8
#define _IOC_TYPEBITS	8
#define _IOC_SIZEBITS	13
#define _IOC_DIRBITS	3

#define _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#define _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#define _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#define _IOC_DIRMASK	((1 << _IOC_DIRBITS)-1)

#define _IOC_NRSHIFT	0
#define _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#define _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#define _IOC_DIRSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Direction bits _IOC_NONE could be 0, but OSF/1 gives it a bit.
 * And this turns out useful to catch old ioctl numbers in header
 * files for us.
 */
#define _IOC_NONE	1U
#define _IOC_READ	2U
#define _IOC_WRITE	4U

#define _IOC(dir,type,nr,size) \
	(((dir)  << _IOC_DIRSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))

/* used to create numbers */
#define _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
#define _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),sizeof(size))
#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),sizeof(size))
#define _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

/* used to decode them.. */
#define _IOC_DIR(nr)		(((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
#define _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#define _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#define _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

extern int ioctl(int, int, ...);

#else
#define IOCPARM_MASK	0x7f
#define IOC_VOID	0x20000000
#define IOC_OUT		0x40000000
#define IOC_IN		0x80000000
#define IOC_INOUT	(IOC_IN|IOC_OUT)
#define _IO(x,y)	(IOC_VOID|('x'<<8)|y)
#define _IOR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#define _IOW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
#define _IOWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|('x'<<8)|y)
/* if ansi the above doesn't work! */
#define _IO_(x,y)	(IOC_VOID|(x<<8)|y)
#define _IOR_(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define _IOW_(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define _IOWR_(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)

extern int ioctl(int, int, ...);

#endif /* __dcc_linux */

#ifdef	__cplusplus
}
#endif
#endif
