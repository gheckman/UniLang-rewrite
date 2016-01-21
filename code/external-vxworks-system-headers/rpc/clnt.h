/* clnt.h - Client side remote procedure call interface. */

/* Copyright 1984-2005, 2006-2011 Wind River Systems, Inc. */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
/*	@(#)clnt.h 1.1 86/02/03 SMI      */

/*
 * clnt.h - Client side remote procedure call interface.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

/*
modification history
--------------------
01o,21jun11,sjz  Improve NFS performance for the requirement WIND00236547.
01n,29apr10,pad  Moved extern C statement after include statements.
01m,15jan10,y_t Add LP64 support.
01l,21jul05,vvv  fixed C++ build problem (SPR #99889)
01k,22sep92,rrr  added support for c++
01j,07sep92,smb  added includes of sys/times.h, rpc/xdr.h, rpc/auth.h
01i,26may92,rrr  the tree shuffle
		  -changed includes to have absolute path from h/
01h,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01g,01may01,elh	 removed clnt_tcpInit.
01f,10jan91,shl  fixed prototype of callrpc(), included in.h.
01e,25oct90,dnw  changed clnt_tcpInit from int to void.
01d,24oct90,shl  commented out redundant function declarations.
01c,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
01b,26oct89,hjb  upgraded to release 4.0
*/

#ifndef __INCclnth
#define __INCclnth

#include "netinet/in.h"
#include "sys/times.h"
#include "rpc/xdr.h"
#include "rpc/auth.h"
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Rpc calls return an enum clnt_stat.  This should be looked at more,
 * since each implementation is required to live with this (implementation
 * independent) list of errors.
 */
enum clnt_stat {
	RPC_SUCCESS=0,			/* call succeeded */
	/*
	 * local errors
	 */
	RPC_CANTENCODEARGS=1,		/* can't encode arguments */
	RPC_CANTDECODERES=2,		/* can't decode results */
	RPC_CANTSEND=3,			/* failure in sending call */
	RPC_CANTRECV=4,			/* failure in receiving result */
	RPC_TIMEDOUT=5,			/* call timed out */
	/*
	 * remote errors
	 */
	RPC_VERSMISMATCH=6,		/* rpc versions not compatible */
	RPC_AUTHERROR=7,		/* authentication error */
	RPC_PROGUNAVAIL=8,		/* program not available */
	RPC_PROGVERSMISMATCH=9,		/* program version mismatched */
	RPC_PROCUNAVAIL=10,		/* procedure unavailable */
	RPC_CANTDECODEARGS=11,		/* decode arguments error */
	RPC_SYSTEMERROR=12,		/* generic "other problem" */

	/*
	 * callrpc errors
	 */
	RPC_UNKNOWNHOST=13,		/* unknown host name */
	RPC_UNKNOWNPROTO=17,		/* unknown protocol -- 4.0 */

	/*
	 * _ create errors
	 */
	RPC_PMAPFAILURE=14,		/* the pmapper failed in its call */
	RPC_PROGNOTREGISTERED=15,	/* remote program is not registered */
	/*
	 * unspecified error
	 */
	RPC_FAILED=16
};

/*
 * Error info.
 */
struct rpc_err {
	enum clnt_stat re_status;
	union {
		int RE_errno;		/* realated system error */
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			u_int  low;	/* lowest verion supported */
			u_int  high;	/* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			int s1;
			int s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
};

/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */

typedef struct {
	AUTH	*cl_auth;			/* authenticator */
	struct clnt_ops *cl_ops;
	caddr_t          cl_private;     /* private stuff */
} CLIENT;

struct clnt_ops {
#if defined(__STDC__) || defined(__cplusplus)
	enum clnt_stat	(*cl_call)(CLIENT *, u_int, xdrproc_t, caddr_t,
				   xdrproc_t, caddr_t,
				   struct timeval timeout); /* call remote procedure */
	void		(*cl_abort)(CLIENT *);	/* abort a call */
	void		(*cl_geterr)(CLIENT *, struct rpc_err *); /* get specific error code */
	bool_t		(*cl_freeres)(CLIENT *, xdrproc_t xres,
	                              caddr_t resp); /* frees results */
	void		(*cl_destroy)(CLIENT *); /* destroy this structure */
	bool_t		(*cl_control)(CLIENT *, u_int, char *); /* the ioctl() of rpc -- 4.0 */
#else
	enum clnt_stat	(*cl_call)();    /* call remote procedure */
	void		(*cl_abort)();	 /* abort a call */
	void		(*cl_geterr)();  /* get specific error code */
	bool_t		(*cl_freeres)(); /* frees results */
	void		(*cl_destroy)(); /* destroy this structure */
	bool_t		(*cl_control)(); /* the ioctl() of rpc -- 4.0 */
#endif
};

/*
 * client side rpc interface ops
 *
 * Parameter types are:
 *
 */

/*
 * enum clnt_stat
 * CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)
 * 	CLIENT *rh;
 *	u_long proc;
 *	xdrproc_t xargs;
 *	caddr_t argsp;
 *	xdrproc_t xres;
 *	caddr_t resp;
 *	struct timeval timeout;
 */
#define	CLNT_CALL(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))
#define	clnt_call(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))

/*
 * void
 * CLNT_ABORT(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_ABORT(rh)	((*(rh)->cl_ops->cl_abort)(rh))
#define	clnt_abort(rh)	((*(rh)->cl_ops->cl_abort)(rh))

/*
 * struct rpc_err
 * CLNT_GETERR(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_GETERR(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))
#define	clnt_geterr(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))

/*
 * bool_t
 * CLNT_FREERES(rh, xres, resp);
 * 	CLIENT *rh;
 *	xdrproc_t xres;
 *	caddr_t resp;
 */
#define	CLNT_FREERES(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))
#define	clnt_freeres(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *      CLIENT *cl;
 *      u_int request;
 *      char *info;
 */
#define	CLNT_CONTROL(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in)) /* 4.0 */
#define	clnt_control(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in)) /* 4.0 */

/*
 * control operations that apply to both udp and tcp transports
 */
#define CLSET_TIMEOUT       1   /* set timeout (timeval) */
#define CLGET_TIMEOUT       2   /* get timeout (timeval) */
#define CLGET_SERVER_ADDR   3   /* get server's address (sockaddr) */
/*
 * udp only control operations
 */
#define CLSET_RETRY_TIMEOUT 4   /* set retry timeout (timeval) */
#define CLGET_RETRY_TIMEOUT 5   /* get retry timeout (timeval) */

/*
 * void
 * CLNT_DESTROY(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))

/*
 * RPCTEST is a test program which is accessable on every rpc
 * transport/port.  It is used for testing, performance evaluation,
 * and network administration.
 */

#define RPCTEST_PROGRAM		((u_int)1)
#define RPCTEST_VERSION		((u_int)1)
#define RPCTEST_NULL_PROC	((u_int)2)
#define RPCTEST_NULL_BATCH_PROC	((u_int)3)

/*
 * By convention, procedure 0 takes null arguments and returns them
 */

#define NULLPROC ((u_int)0)

/*
 * Below are the client handle creation routines for the various
 * implementations of client side rpc.  They can return NULL if a
 * creation failure occurs.
 */

/*
 * Memory based rpc (for speed check and testing)
 * CLIENT *
 * clntraw_create(prog, vers)
 *	u_long prog;
 *	u_long vers;
 */

/* extern CLIENT *clntraw_create(); */

/*
 * Generic client creation routine. Supported protocols are "udp" and "tcp"
 */

/* extern CLIENT * clnt_create(host, prog, vers, prot); */	/* 4.0 */

/*
	char *host;		-- hostname
	u_long prog;		-- program number
	u_long vers;		-- version number
	char *prot;		-- protocol
*/

/*
 * TCP based rpc
 * CLIENT *
 * clnttcp_create(raddr, prog, vers, sockp, sendsz, recvsz)
 *	struct sockaddr_in *raddr;
 *	u_long prog;
 *	u_long version;
 *	register int *sockp;
 *	u_int sendsz;
 *	u_int recvsz;
 */

/* extern CLIENT *clnttcp_create(); */

/*
 * UDP based rpc.
 * CLIENT *
 * clntudp_create(raddr, program, version, wait, sockp)
 *	struct sockaddr_in *raddr;
 *	u_long program;
 *	u_long version;
 *	struct timeval wait;
 *	int *sockp;
 *
 * Same as above, but you specify max packet sizes.
 * CLIENT *
 * clntudp_bufcreate(raddr, program, version, wait, sockp, sendsz, recvsz)
 *	struct sockaddr_in *raddr;
 *	u_long program;
 *	u_long version;
 *	struct timeval wait;
 *	int *sockp;
 *	u_int sendsz;
 *	u_int recvsz;
 */

/* extern CLIENT *clntudp_create();	*/
/* extern CLIENT *clntudp_bufcreate();	*/

/*
 * Print why creation failed
 */

/* void clnt_pcreateerror(char *msg); */	/* stderr -- 4.0 */
/* char *clnt_spcreateerror(char *msg); */	/* string -- 4.0 */

/*
 * Like clnt_perror () but is more verbose in its output
 */

/* void clnt_perrno(enum clnt_stat num); */		/* stderr -- 4.0 */

/*
 * Print an english error message, given the client error code
 */

/* void clnt_perror(CLIENT *clnt, char *msg); */	/* stderr -- 4.0 */
/* char *clnt_sperror(CLIENT *clnt, char *msg);*/	/* string -- 4.0 */

/*
 * If a creation fails, the following allows the user to figure out why.
 */

struct rpc_createerr {
 	enum clnt_stat cf_stat;
 	struct rpc_err cf_error; /* useful when cf_stat == RPC_PMAPFAILURE */
};

/* XXX this is now in the taskModuleList */
/* XXX extern struct rpc_createerr rpc_createerr; */

/*
 * copy error message to buffer.
 */

/* char *clnt_sperrno(enum clnt_stat num); */	/* string -- 4.0 */

#ifdef _WRS_CONFIG_NFS3_BLKSIZE_FACTOR
#define UDPMSGSIZE	(_WRS_CONFIG_NFS3_BLKSIZE_FACTOR * 8800)  	/* rpc imposed limit on udp msg size */
#else
#define UDPMSGSIZE	8800	/* rpc imposed limit on udp msg size */
#endif
#define RPCSMALLMSGSIZE	400	/* a more reasonable packet size */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern	  CLIENT *    clnt_create (char *hostname, unsigned prog,
				   unsigned vers, char *proto);
extern	  char *      clnt_sperror (CLIENT *rpch, char *s);
extern	  void	      clnt_perror (CLIENT *rpch, char *s);
extern	  char *      clnt_sperrno (enum clnt_stat stat);
extern	  void	      clnt_perrno (enum clnt_stat num);
extern	  char *      clnt_spcreateerror (char *s);
extern	  void	      clnt_pcreateerror (char *s);
extern	  CLIENT *    clntraw_create (u_int prog, u_int vers);
extern	  int	      callrpc (char *host, int prognum, int versnum,
			       int procnum, xdrproc_t inproc, char* in,
			       xdrproc_t outproc, char *out);
extern	  CLIENT *    clnttcp_create (struct sockaddr_in *raddr, u_int prog,
				      u_int vers, int *sockp, u_int sendsz,
				      u_int recvsz);
extern	  CLIENT *    clntudp_bufcreate (struct sockaddr_in *raddr,
					 u_int program, u_int version,
					 struct timeval wait, int *sockp,
					 u_int sendsz, u_int recvsz);
extern	  CLIENT *    clntudp_create (struct sockaddr_in *raddr, u_int program,
				      u_int version, struct timeval wait,
				      int *sockp);
extern	  bool_t      clntudp_freeres (CLIENT *cl, xdrproc_t xdr_res,
				       caddr_t res_ptr);

#else

extern	  CLIENT *    clnt_create ();
extern	  char *      clnt_sperror ();
extern	  void	      clnt_perror ();
extern	  char *      clnt_sperrno ();
extern	  void	      clnt_perrno ();
extern	  char *      clnt_spcreateerror ();
extern	  void	      clnt_pcreateerror ();
extern	  CLIENT *    clntraw_create ();
extern	  int	      callrpc ();
extern	  CLIENT *    clnttcp_create ();
extern	  CLIENT *    clntudp_bufcreate ();
extern	  CLIENT *    clntudp_create ();
extern	  bool_t      clntudp_freeres ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCclnth */