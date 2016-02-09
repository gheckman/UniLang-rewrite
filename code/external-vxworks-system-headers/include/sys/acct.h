/*
 *	RCS Information:
 *		$Source: /crystalsprings7/fburton/diabcvs/dlib/include/include.unx/sys/acct.h,v $
 *		$Revision: 1.1 $
 *		$Date: 1994/03/29 00:42:23 $
 *		$Author: fb $
 *		$State: Exp $
 *		$Locker:  $
 *		$Log: acct.h,v $
 *		Revision 1.1  1994/03/29 00:42:23  fb
 *		Initial version
 *		
 * Revision 1.2  89/03/30  10:39:19  ks
 * Added more RCS info
 * 
 */
/*
 *	84/10/29 Copyright (c) Dataindustrier DIAB AB, 1984
 */

/*
 *	Structure written on accounting file
 */

#ifndef __Iacct
#define __Iacct
typedef	ushort	comp_t;		/* Floating point - 13bit frac., 3bit exp */

#define AFORK	01		/* Has executed fork, but no exec */
#define ASU	02		/* Used super-user privileges */
#define ACCTF	0300		/* Record type: 00 = acct */

struct acct {
	char	ac_flag;	/* Accounting flag */
	char	ac_stat;	/* Exit status */
#if defined(m88k) || defined(__m88k)
	uid_t	ac_uid;		/* Accounting user id */
	gid_t	ac_gid;		/* Accounting group id */
#else
	ushort	ac_uid;		/* Accounting user id */
	ushort	ac_gid;		/* Accounting group id */
#endif
	dev_t	ac_tty;		/* Control typewriter */
	time_t	ac_btime;	/* Beginning time */
	comp_t	ac_utime;	/* User time in clock ticks */
	comp_t	ac_stime;	/* System time in clock ticks */
	comp_t	ac_etime;	/* elapsed time in clock ticks */
	comp_t	ac_mem;		/* Memory usage */
	comp_t	ac_io;		/* Chars transferred */
	comp_t	ac_rw;		/* Blocks read or written */
	char	ac_comm[8];	/* Command name */
};
#endif
