#ifndef __Itermios
#define __Itermios

#include <sys/ioctl.h>

#ifdef __dcc_linux

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

struct sgttyb {
	char	sg_ispeed;
	char	sg_ospeed;
	char	sg_erase;
	char	sg_kill;
	short	sg_flags;
};

struct tchars {
	char	t_intrc;
	char	t_quitc;
	char	t_startc;
	char	t_stopc;
	char	t_eofc;
	char	t_brkc;
};

struct ltchars {
	char	t_suspc;
	char	t_dsuspc;
	char	t_rprntc;
	char	t_flushc;
	char	t_werasc;
	char	t_lnextc;
};

#define FIOCLEX		_IO('f', 1)
#define FIONCLEX	_IO('f', 2)
#define FIOASYNC	_IOW('f', 125, int)
#define FIONBIO		_IOW('f', 126, int)
#define FIONREAD	_IOR('f', 127, int)
#define TIOCINQ		FIONREAD

#define TIOCGETP	_IOR('t', 8, struct sgttyb)
#define TIOCSETP	_IOW('t', 9, struct sgttyb)
#define TIOCSETN	_IOW('t', 10, struct sgttyb)	/* TIOCSETP wo flush */

#define TIOCSETC	_IOW('t', 17, struct tchars)
#define TIOCGETC	_IOR('t', 18, struct tchars)
#define TCGETS		_IOR('t', 19, struct termios)
#define TCSETS		_IOW('t', 20, struct termios)
#define TCSETSW		_IOW('t', 21, struct termios)
#define TCSETSF		_IOW('t', 22, struct termios)

#define TCGETA		_IOR('t', 23, struct termio)
#define TCSETA		_IOW('t', 24, struct termio)
#define TCSETAW		_IOW('t', 25, struct termio)
#define TCSETAF		_IOW('t', 28, struct termio)

#define TCSBRK		_IO('t', 29)
#define TCXONC		_IO('t', 30)
#define TCFLSH		_IO('t', 31)

#define TIOCSWINSZ	_IOW('t', 103, struct winsize)
#define TIOCGWINSZ	_IOR('t', 104, struct winsize)
#define	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#define	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#define TIOCOUTQ        _IOR('t', 115, int)     /* output queue size */

#define TIOCGLTC	_IOR('t', 116, struct ltchars)
#define TIOCSLTC	_IOW('t', 117, struct ltchars)
#define TIOCSPGRP	_IOW('t', 118, int)
#define TIOCGPGRP	_IOR('t', 119, int)

#define TIOCEXCL	0x540C
#define TIOCNXCL	0x540D
#define TIOCSCTTY	0x540E

#define TIOCSTI		0x5412
#define TIOCMGET	0x5415
#define TIOCMBIS	0x5416
#define TIOCMBIC	0x5417
#define TIOCMSET	0x5418
#define TIOCGSOFTCAR	0x5419
#define TIOCSSOFTCAR	0x541A
#define TIOCLINUX	0x541C
#define TIOCCONS	0x541D
#define TIOCGSERIAL	0x541E
#define TIOCSSERIAL	0x541F
#define TIOCPKT		0x5420

#define TIOCNOTTY	0x5422
#define TIOCSETD	0x5423
#define TIOCGETD	0x5424
#define TCSBRKP		0x5425	/* Needed for POSIX tcsendbreak() */
#define TIOCTTYGSTRUCT	0x5426  /* For debugging only */

#define TIOCSERCONFIG	0x5453
#define TIOCSERGWILD	0x5454
#define TIOCSERSWILD	0x5455
#define TIOCGLCKTRMIOS	0x5456
#define TIOCSLCKTRMIOS	0x5457
#define TIOCSERGSTRUCT	0x5458 /* For debugging only */
#define TIOCSERGETLSR   0x5459 /* Get line status register */
#define TIOCSERGETMULTI 0x545A /* Get multiport config  */
#define TIOCSERSETMULTI 0x545B /* Set multiport config */

#define TIOCMIWAIT	0x545C	/* wait for a change on serial input line(s) */
#define TIOCGICOUNT	0x545D	/* read serial port inline interrupt counts */

/* Used for packet mode */
#define TIOCPKT_DATA		 0
#define TIOCPKT_FLUSHREAD	 1
#define TIOCPKT_FLUSHWRITE	 2
#define TIOCPKT_STOP		 4
#define TIOCPKT_START		 8
#define TIOCPKT_NOSTOP		16
#define TIOCPKT_DOSTOP		32

struct winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

#define NCC 10
struct termio {
	unsigned short c_iflag;		/* input mode flags */
	unsigned short c_oflag;		/* output mode flags */
	unsigned short c_cflag;		/* control mode flags */
	unsigned short c_lflag;		/* local mode flags */
	unsigned char c_line;		/* line discipline */
	unsigned char c_cc[NCC];	/* control characters */
};

#define NCCS 19
struct termios {
	tcflag_t c_iflag;		/* input mode flags */
	tcflag_t c_oflag;		/* output mode flags */
	tcflag_t c_cflag;		/* control mode flags */
	tcflag_t c_lflag;		/* local mode flags */
	cc_t c_cc[NCCS];		/* control characters */
	cc_t c_line;			/* line discipline (== c_cc[19]) */
	int c_ispeed;			/* input speed */
	int c_ospeed;			/* output speed */
};

/* c_cc characters */
#define _VINTR	0
#define _VQUIT	1
#define _VERASE	2
#define _VKILL	3
#define _VEOF	4
#define _VMIN	5
#define _VEOL	6
#define _VTIME	7
#define _VEOL2	8
#define _VSWTC	9

#define VINTR 	0
#define VQUIT 	1
#define VERASE 	2
#define VKILL	3
#define VEOF	4
#define VMIN	5
#define VEOL	6
#define VTIME	7
#define VEOL2	8
#define VSWTC	9

#define VWERASE 	10
#define VREPRINT	11
#define VSUSP 		12
#define VSTART		13
#define VSTOP		14
#define VLNEXT		15
#define VDISCARD	16


#ifdef __KERNEL__
/*	eof=^D		eol=\0		eol2=\0		erase=del
	werase=^W	kill=^U		reprint=^R	sxtc=\0
	intr=^C		quit=^\		susp=^Z		<OSF/1 VDSUSP>
	start=^Q	stop=^S		lnext=^V	discard=^U
	vmin=\1		vtime=\0
#define INIT_C_CC "\004\000\000\177\027\025\022\000\003\034\032\000\021\023\026\025\001\000"
*/

/*                   ^C  ^\ del  ^U  ^D   1   0   0   0   0  ^W  ^R  ^Z  ^Q  ^S  ^V  ^U  */
#define INIT_C_CC "\003\034\177\025\004\001\000\000\000\000\027\022\032\021\023\026\025" 
#endif

/* c_iflag bits */
#define IGNBRK	0000001
#define BRKINT	0000002
#define IGNPAR	0000004
#define PARMRK	0000010
#define INPCK	0000020
#define ISTRIP	0000040
#define INLCR	0000100
#define IGNCR	0000200
#define ICRNL	0000400
#define IXON	0001000
#define IXOFF	0002000
#define IXANY	0004000
#define IUCLC	0010000
#define IMAXBEL	0020000

/* c_oflag bits */
#define OPOST	0000001
#define ONLCR	0000002
#define OLCUC	0000004

#define OCRNL	0000010
#define ONOCR	0000020
#define ONLRET	0000040

#define OFILL	00000100
#define OFDEL	00000200
#define NLDLY	00001400
#define   NL0	00000000
#define   NL1	00000400
#define   NL2	00001000
#define   NL3	00001400
#define TABDLY	00006000
#define   TAB0	00000000
#define   TAB1	00002000
#define   TAB2	00004000
#define   TAB3	00006000
#define CRDLY	00030000
#define   CR0	00000000
#define   CR1	00010000
#define   CR2	00020000
#define   CR3	00030000
#define FFDLY	00040000
#define   FF0	00000000
#define   FF1	00040000
#define BSDLY	00100000
#define   BS0	00000000
#define   BS1	00100000
#define VTDLY	00200000
#define   VT0	00000000
#define   VT1	00200000
#define XTABS	01000000 /* Hmm.. Linux/i386 considers this part of TABDLY.. */

/* c_cflag bit meaning */
#define CBAUD	0000377
#define  B0	0000000		/* hang up */
#define  B50	0000001
#define  B75	0000002
#define  B110	0000003
#define  B134	0000004
#define  B150	0000005
#define  B200	0000006
#define  B300	0000007
#define  B600	0000010
#define  B1200	0000011
#define  B1800	0000012
#define  B2400	0000013
#define  B4800	0000014
#define  B9600	0000015
#define  B19200	0000016
#define  B38400	0000017
#define EXTA B19200
#define EXTB B38400
#define CBAUDEX 0000020
#define  B57600   00020
#define  B115200  00021
#define  B230400  00022

#define CSIZE	00001400
#define   CS5	00000000
#define   CS6	00000400
#define   CS7	00001000
#define   CS8	00001400

#define CSTOPB	00002000
#define CREAD	00004000
#define PARENB	00010000
#define PARODD	00020000
#define HUPCL	00040000

#define CLOCAL	00100000
#define CRTSCTS	  020000000000		/* flow control */

/* c_lflag bits */
#define ISIG	0x00000080
#define ICANON	0x00000100
#define XCASE	0x00004000
#define ECHO	0x00000008
#define ECHOE	0x00000002
#define ECHOK	0x00000004
#define ECHONL	0x00000010
#define NOFLSH	0x80000000
#define TOSTOP	0x00400000
#define ECHOCTL	0x00000040
#define ECHOPRT	0x00000020
#define ECHOKE	0x00000001
#define FLUSHO	0x00800000
#define PENDIN	0x20000000
#define IEXTEN	0x00000400

/* modem lines */
#define TIOCM_LE	0x001
#define TIOCM_DTR	0x002
#define TIOCM_RTS	0x004
#define TIOCM_ST	0x008
#define TIOCM_SR	0x010
#define TIOCM_CTS	0x020
#define TIOCM_CAR	0x040
#define TIOCM_RNG	0x080
#define TIOCM_DSR	0x100
#define TIOCM_CD	TIOCM_CAR
#define TIOCM_RI	TIOCM_RNG

/* ioctl (fd, TIOCSERGETLSR, &result) where result may be as below */
#define TIOCSER_TEMT    0x01	/* Transmitter physically empty */


/* tcflow() and TCXONC use these */
#define	TCOOFF		0
#define	TCOON		1
#define	TCIOFF		2
#define	TCION		3

/* tcflush() and TCFLSH use these */
#define	TCIFLUSH	0
#define	TCOFLUSH	1
#define	TCIOFLUSH	2

/* tcsetattr uses these */
#define	TCSANOW		0
#define	TCSADRAIN	1
#define	TCSAFLUSH	2

/* line disciplines */
#define N_TTY		0
#define N_SLIP		1
#define N_MOUSE		2
#define N_PPP		3

#else 

#define	NCCS	19

#define	VINTR	0
#define	VQUIT	1
#define	VERASE	2
#define	VKILL	3
#define	VEOF	4
#define	VEOL	5
#define	VEOL2	6
#define	VMIN	4
#define	VTIME	5
#define	VSWTCH	7
#define	VSTART	8
#define	VSTOP	9
#define	VSUSP	10

#define	CNUL	0
#define	CDEL	0377

#define	CESC	'\\'
#define	CINTR	0177
#define	CQUIT	034
#define	CERASE	'#'
#define	CKILL	'@'
#define	CEOF	04
#define	CSTART	021
#define	CSTOP	023
#define	CSWTCH	032
#define	CNSWTCH	0
#define	CSUSP	032

#define	IGNBRK	0000001
#define	BRKINT	0000002
#define	IGNPAR	0000004
#define	PARMRK	0000010
#define	INPCK	0000020
#define	ISTRIP	0000040
#define	INLCR	0000100
#define	IGNCR	0000200
#define	ICRNL	0000400
#define	IUCLC	0001000
#define	IXON	0002000
#define	IXANY	0004000
#define	IXOFF	0010000

#define	OPOST	0000001
#define	OLCUC	0000002
#define	ONLCR	0000004
#define	OCRNL	0000010
#define	ONOCR	0000020
#define	ONLRET	0000040
#define	OFILL	0000100
#define	OFDEL	0000200
#define	NLDLY	0000400
#define	NL0	0
#define	NL1	0000400
#define	CRDLY	0003000
#define	CR0	0
#define	CR1	0001000
#define	CR2	0002000
#define	CR3	0003000
#define	TABDLY	0014000
#define	TAB0	0
#define	TAB1	0004000
#define	TAB2	0010000
#define	TAB3	0014000
#define	BSDLY	0020000
#define	BS0	0
#define	BS1	0020000
#define	VTDLY	0040000
#define	VT0	0
#define	VT1	0040000
#define	FFDLY	0100000
#define	FF0	0
#define	FF1	0100000

#if defined(m88k) || defined(__m88k)
#define	B0	0
#define	B50	000000200000
#define	B75	000000400000
#define	B110	000000600000
#define	B134	000001000000
#define	B150	000001200000
#define	B200	000001400000
#define	B300	000001600000
#define	B600	000002000000
#define	B1200	000002200000
#define	B1800	000002400000
#define	B2400	000002600000
#define	B4800	000003000000
#define	B9600	000003200000
#define	B19200	000003400000
#define EXTA	000003400000
#define	B38400	000003600000
#define EXTB	000003600000

#define	CBAUD	000077600000
#define	CIBAUD	037700000000

#define	COUTBAUD	CBAUD
#define	CINBAUD		CIBAUD

#define TCSANOW		0
#define TCSADRAIN	1
#define TCSAFLUSH	2

#else

#define	CBAUD		0x00ff
#define	B0		0x0000
#define	B50		0x0001
#define	B75		0x0002
#define	B110		0x0003
#define	B134		0x0004
#define	B150		0x0005
#define	B200		0x0006
#define	B300		0x0007
#define	B600		0x0008
#define	B1200		0x0009
#define	B1800		0x000a
#define	B2400		0x000b
#define	B4800		0x000c
#define	B9600		0x000d
#define	B19200		0x000e
#define	B38400		0x000f

#define	_OUTBAUD(X)	((X)<<16)
#define	COUTBAUD	_OUTBAUD(CBAUD)
#define	OB0		_OUTBAUD(B0)
#define	OB50		_OUTBAUD(B50)
#define	OB75		_OUTBAUD(B75)
#define	OB110		_OUTBAUD(B110)
#define	OB134		_OUTBAUD(B134)
#define	OB150		_OUTBAUD(B150)
#define	OB200		_OUTBAUD(B200)
#define	OB300		_OUTBAUD(B300)
#define	OB600		_OUTBAUD(B600)
#define	OB1200		_OUTBAUD(B1200)
#define	OB1800		_OUTBAUD(B1800)
#define	OB2400		_OUTBAUD(B2400)
#define	OB4800		_OUTBAUD(B4800)
#define	OB9600		_OUTBAUD(B9600)
#define	OB19200		_OUTBAUD(B19200)
#define	OB38400		_OUTBAUD(B38400)
#define	_INBAUD(X)	((X)<<24)
#define	CINBAUD		_INBAUD(CBAUD)
#define	IB0		_INBAUD(B0)
#define	IB50		_INBAUD(B50)
#define	IB75		_INBAUD(B75)
#define	IB110		_INBAUD(B110)
#define	IB134		_INBAUD(B134)
#define	IB150		_INBAUD(B150)
#define	IB200		_INBAUD(B200)
#define	IB300		_INBAUD(B300)
#define	IB600		_INBAUD(B600)
#define	IB1200		_INBAUD(B1200)
#define	IB1800		_INBAUD(B1800)
#define	IB2400		_INBAUD(B2400)
#define	IB4800		_INBAUD(B4800)
#define	IB9600		_INBAUD(B9600)
#define	IB19200		_INBAUD(B19200)
#define	IB38400		_INBAUD(B38400)

#define TCSANOW		TC_PX_SETATTR
#define TCSADRAIN	TC_PX_SETATTRD
#define TCSAFLUSH	TC_PX_SETATTRF

#endif

#define	CSIZE	0000060
#define	CS5	0
#define	CS6	0000020
#define	CS7	0000040
#define	CS8	0000060
#define	CSTOPB	0000100
#define	CREAD	0000200
#define	PARENB	0000400
#define	PARODD	0001000
#define	HUPCL	0002000
#define	CLOCAL	0004000
#define	LOBLK	0010000

#define	ISIG	0000001
#define	ICANON	0000002
#define	XCASE	0000004
#define	ECHO	0000010
#define	ECHOE	0000020
#define	ECHOK	0000040
#define	ECHONL	0000100
#define	NOFLSH	0000200
#define	TOSTOP	0000400
#define	IEXTEN	0001000

#define	IOCTYPE	0xff00

#define TC_PX_GETATTR	_IOR_('t',0xc0, struct termios)
#define TC_PX_SETATTR	_IOW_('t',0xc1, struct termios)
#define TC_PX_SETATTRD	_IOW_('t',0xc2, struct termios)
#define TC_PX_SETATTRF	_IOW_('t',0xc3, struct termios)
#define TC_PX_DRAIN	_IO_('t',0xc4)
#define TC_PX_FLUSH	_IO_('t',0xc5)
#define TC_PX_BREAK	_IO_('t',0xc6)
#define TC_PX_GETPGRP	_IO_('t',0xc7)
#define TC_PX_SETPGRP	_IO_('t',0xc8)
#define TC_PX_FLOW	_IO_('t',0xc9)
#define TIOCSWINSZ	_IOW_('t',0x67,struct winsize)
#define TIOCGWINSZ	_IOR_('t',0x68,struct winsize)

#define TCIFLUSH	0
#define TCOFLUSH	1
#define TCIOFLUSH	2

#define TCOOFF		0
#define TCOON		1
#define TCIOFF		2
#define TCION		3

typedef	unsigned long	tcflag_t;
typedef	unsigned char	cc_t;

struct termios {
	tcflag_t	c_iflag;
	tcflag_t	c_oflag;
	tcflag_t	c_cflag;
	tcflag_t	c_lflag;
	unsigned char	c_line;
	cc_t		c_cc[NCCS];
};

struct winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

#define SSPEED		B9600

typedef unsigned long speed_t;

#define	LDIOC	('D'<<8)
#define	LDOPEN	(LDIOC|0)
#define	LDCLOSE	(LDIOC|1)
#define	LDCHG	(LDIOC|2)
#define	LDGETT	(LDIOC|8)
#define	LDSETT	(LDIOC|9)

#define	TERM_NONE	0	/* tty */
#define	TERM_TEC	1	/* TEC Scope */
#define	TERM_V61	2	/* DEC VT61 */
#define	TERM_V10	3	/* DEC VT100 */
#define	TERM_TEX	4	/* Tektronix 4023 */
#define	TERM_D40	5	/* TTY Mod 40/1 */
#define	TERM_H45	6	/* Hewlitt-Packard 45 */
#define	TERM_D42	7	/* TTY Mod 40/2B */

#define TM_NONE		0000	/* use default flags */
#define TM_SNL		0001	/* special newline flag */
#define TM_ANL		0002	/* auto newline on column 80 */
#define TM_LCF		0004	/* last col of last row special */
#define TM_CECHO	0010	/* echo terminal cursor control */
#define TM_CINVIS	0020	/* do not send esc seq to user */
#define TM_SET		0200	/* must be on to set/res flags */

#endif /* __dcc_linux */
#endif
