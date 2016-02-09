/* ioctl.h - socket ioctl header file */

/*
 * Copyright (c) 1984-2007, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02q,28apr10,pad  Moved extern C statement after include statements.
02p,04sep07,h_k  fixed an apigen error.
02o,15jan07,jlk  Defect WIND00064397 - macro _IOC now has type int
02q,12dec06,kch  Added <ipnet/ioctl.h> include.
02p,30nov06,kch  Removed all network stack ioctl commands.
02o,26sep06,kch  Added SIOCGIFLLADDR to retrieve interface MAC Address.
02n,22jul05,kch  Added SIOCMUXL2PASSTHRU for Layer 2 support.
02m,24feb05,dlk  Added SIOCMUXPASSTHRU support. Increase maximum
                 ioctl argument size to 4095 bytes. Added IOCPARM_MAX
		 and IOCPARM_LEN macros, and other items from ioccom.h.
02l,12oct01,rae  merge from truestack (SIOCGMTU)
02k,29apr99,pul  Upgraded NPT phase3 code to tor2.0.0
02j,18mar99,sj   added SIOCSIFASYNCFLAGS
02i,11aug93,jmm  Changed ioctl.h and socket.h to sys/ioctl.h and sys/socket.h
02h,22sep92,rrr  added support for c++
02g,04jul92,jcf  cleaned up.
02f,26may92,rrr  the tree shuffle
02e,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
02d,19aug91,rrr  changed to work with ansi compiler
02c,24mar91,del  changes to work with gnu960 compiler for i960 port.
02b,05oct90,shl  fixed copyright notice.
02a,29apr87,dnw  removed unnecessary junk.
		 added header and copyright.
*/

#ifndef __INCioctlh
#define __INCioctlh

/* socket i/o controls */

/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 4095 bytes, reserving
 * the 0x10000000 bit for other use.
 */
#define	IOCPARM_MASK	0xfff		/* parameters must be < 4096 bytes */
#define IOCPARM_MAX	0xfff		/* absolute maximum param size */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */

#define IOCPARM_LEN(x)  ((((u_long)(x)) >> 16) & IOCPARM_MAX)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << 16))
#define	IOCGROUP(x)	(((x) >> 8) & 0xff)

#define	_IOC(inout,group,num,len) \
	((int)(inout | ((len & IOCPARM_MASK) << 16) | \
			 ((group) << 8) | (num)))
#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))
/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

/*
 * These definitions are primarily to support SIOCMUXPASSTHRU.
 * It's assumed that tunnellable IOCTLs will have IOC_USER set.
 * Note that IOC_USER overlaps the high bit of the type (x) byte.
 * When this byte is an ASCII character, its high bit will be 0;
 * but if the high bit of the type byte x is set, _IOR(x,y,t)
 * and _IORU(x,y,t) (for instance) will be indistinguishable.
 */

#define IOC_USER        0x8000 /* tunnellable from RTP space */
#define	_IOU(g,n)	(IOC_USER|_IO(g,n))
#define	_IORU(g,n,t)	(IOC_USER|_IOR(g,n,t))
#define	_IOWU(g,n,t)	(IOC_USER|_IOW(g,n,t))
#define	_IOWRU(g,n,t)	(IOC_USER|_IOWR(g,n,t))

#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, int)		/* get process group */

/* tunnel ioctl to mux layer */
#define SIOCMUXPASSTHRU	 _IOW('e', 122, MUX_PASSTHRU)

/* tunnel layer 2 ioctl to mux layer */
#define SIOCMUXL2PASSTHRU _IOW('e', 123, MUX_PASSTHRU)

/* Duplicate of END ioctl to prevent include file dependencies. */

#define SIOCGMTU _IOR('e', 26, MTU_QUERY *)  /* get mtu for PMP case */

/*
 * network stack ioctl commands are now defined in ipioctl.h which can be
 * found in $WIND_BASE/target/h/wrn/coreip/ipnet.
 */   
#include <ipnet/ipioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCioctlh */
