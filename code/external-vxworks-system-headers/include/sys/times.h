#ifndef __Itimes
#define __Itimes

#include <xmacros.h>

_C_LIB_DECL

#ifndef __size_t
#define	__size_t
_TYPE_size_t;
#endif

#ifndef __clock_t
#define	__clock_t
typedef size_t clock_t;
#endif

struct tms {
	clock_t	tms_utime;
	clock_t	tms_stime;
	clock_t	tms_cutime;
	clock_t	tms_cstime;
};

extern clock_t times(struct tms *);

_END_C_LIB_DECL

#endif
