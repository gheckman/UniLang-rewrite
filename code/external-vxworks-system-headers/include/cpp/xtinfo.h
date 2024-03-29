/* xtinfo.h internal header */
#ifndef _XTINFO
#define _XTINFO
#include <time.h>
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN

		/* type definitions */
typedef struct
	{	/* format strings for date and time */
	const char *_Am_pm;
	const char *_Days;
		const char *_Abday;
		const char *_Day;
	const char *_Months;
		const char *_Abmon;
		const char *_Mon;
	const char *_Formats;
		const char *_D_t_fmt;
		const char *_D_fmt;
		const char *_T_fmt;
		const char *_T_fmt_ampm;
	const char *_Era_Formats;
		const char *_Era_D_t_fmt;
		const char *_Era_D_fmt;
		const char *_Era_T_fmt;
		const char *_Era_T_fmt_ampm;
	const char *_Era;
	const char *_Alt_digits;
	const char *_Isdst;
	const char *_Tzone;
	} _Tinfo;

		/* declarations */
_C_LIB_DECL
size_t _CStrftime(char *, size_t, const char *,
	const struct tm *, const _Tinfo *);
_Tinfo *_Getptimes(void);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XTINFO */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.01:1278 */
