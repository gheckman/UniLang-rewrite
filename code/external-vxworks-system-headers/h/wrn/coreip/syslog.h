/* syslog.h - the system message logger header file */

/* Copyright 2001-2005 Wind River Systems, Inc. */

/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)syslog.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD: src/sys/sys/syslog.h,v 1.19.2.2 2001/05/29 13:15:08 dwmalone Exp $
 */

/*
modification history
--------------------
01j,25oct06,kch  Removed unused defines that were previously commented out.
01i,07feb05,vvv  _KERNEL cleanup
01h,03sep04,dlk  Reimplement in terms of applUtilLib.
01g,20nov03,niq  Remove copyright_wrs.h file inclusion
01f,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01e,04nov03,rlm  Ran batch header path update for header re-org.
01d,29apr03,syy  Added #ifdef for __cplusplus
01c,12oct01,ppp  undef'd log temporarily for board bringup
01b,05sep01,ham  renamed printf to PRINTF.
01a,05sep01,ham  created from FreeBSD4.3-RELEASE(July-17-01).
*/

#ifndef _SYS_SYSLOG_H_
#define _SYS_SYSLOG_H_

#include <applUtilLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Note, Base 6 presently does not support syslog() or the
 * related posix functions openlog(), closelog(), and setlogmask().
 * applUtilLib is the closest present match.
 */

#define	_PATH_LOG	"/var/run/log"
#define	_PATH_OLDLOG	"/dev/log"	/* backward compatibility */


#define	LOG_PRIMASK	0x07	/* mask to extract priority part (internal) */
				/* extract priority */
#define	LOG_PRI(p)	((p) & LOG_PRIMASK)
#define	LOG_MAKEPRI(fac, pri)	((fac) | (pri))

/* For now, we map all the unimplemented Posix facilities to GENERAL_LOG */

/* facility codes */
#define	LOG_KERN	KERN_LOG	/* kernel messages */
#define	LOG_USER	GENERAL_LOG	/* random user-level messages */
#define	LOG_MAIL	GENERAL_LOG	/* mail system */
#define	LOG_DAEMON	GENERAL_LOG	/* system daemons */
#define	LOG_AUTH	GENERAL_LOG	/* authorization messages */
#define	LOG_SYSLOG	GENERAL_LOG     /* generated internally by syslogd */
#define	LOG_LPR		GENERAL_LOG	/* line printer subsystem */
#define	LOG_NEWS	GENERAL_LOG	/* network news subsystem */
#define	LOG_UUCP	GENERAL_LOG	/* UUCP subsystem */
#define	LOG_CRON	GENERAL_LOG	/* clock daemon */
#define	LOG_AUTHPRIV	GENERAL_LOG	/* authorization messages (private) */
				/* Facility #10 clashes in DEC UNIX, where */
				/* it's defined as LOG_MEGASAFE for AdvFS  */
				/* event logging.                          */
#define	LOG_FTP		FTPD_LOG	/* ftp daemon */
#define	LOG_NTP		GENERAL_LOG	/* NTP subsystem */
#define	LOG_SECURITY	GENERAL_LOG     /* security subsystems (firewalling,
					   etc.) */
#define	LOG_CONSOLE	GENERAL_LOG	/* /dev/console output */

/* other codes through 15 reserved for system use */
#define	LOG_LOCAL0	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL1	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL2	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL3	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL4	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL5	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL6	GENERAL_LOG	/* reserved for local use */
#define	LOG_LOCAL7	GENERAL_LOG	/* reserved for local use */

/* current number of facilities */
#define	LOG_NFACILITIES	LOG_NUMCATS
#define	LOG_FACMASK	CAT_MASK	/* mask to extract facility part */
					/* facility of pri */
#define	LOG_FAC(p)	(((p) & LOG_FACMASK) >> CAT_SHIFT)

/*
 * arguments to setlogmask.
 */
#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */
/* LOG_UPTO() defined in applUtilLib.h */


/*
 * Option flags for openlog.
 *
 * LOG_ODELAY no longer does anything.
 * LOG_NDELAY is the inverse of what it used to be.
 */
#define	LOG_PID		0x01	/* log the pid with each message */
#define	LOG_CONS	0x02	/* log on the console if errors in sending */
#define	LOG_ODELAY	0x04	/* delay open until first syslog() (default) */
#define	LOG_NDELAY	0x08	/* don't delay open */
#define	LOG_NOWAIT	0x10	/* don't wait for console forks: DEPRECATED */
#define	LOG_PERROR	0x20	/* log to stderr as well */

#ifdef C99_VARIADIC_MACROS

#if (LOG_ENABLE_MASK & LOG_KERNEL_BIT)
#if LOG_ARGS
#define LOG(pri, ...)						\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION,		\
	      __VA_ARGS__);					\
	} while (FALSE)

#define log(pri, ...)						\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION,		\
	      __VA_ARGS__);					\
	} while (FALSE)
#else
#define LOG(pri, ...)						\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION,		\
	      "");						\
	} while (FALSE)

#define log(pri, ...)						\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION,		\
	      "");						\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define LOG(pri, ...) do {} while (FALSE)
#define log(pri, ...) do {} while (FALSE)
#endif

#else   /* !defined (C99_VARIADIC_MACROS) -> assume old GNU variadic syntax */

#if  (LOG_ENABLE_MASK & LOG_KERNEL_BIT)
#if LOG_ARGS
#define LOG(pri, fmt...)					\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION, fmt);	\
	} while (FALSE)

#define log(pri, fmt...)					\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define LOG(pri, fmt...)					\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION, "");	\
	} while (FALSE)

#define log(pri, fmt...)					\
    do  {							\
	_applLog (((pri) | LOG_KERN), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define LOG(pri, fmt...) do {} while (FALSE)
#define log(pri, fmt...) do {} while (FALSE)
#endif

#endif /* ! C99_VARIADIC_MACROS */

#ifdef __cplusplus
}
#endif

#endif /* _SYS_SYSLOG_H_ */
