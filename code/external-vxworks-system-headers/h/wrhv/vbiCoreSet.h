/* vbiCoreSet.h - macros to manipulate vbiCoreSet_t type */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01a,09jun09,mmi  written
*/

#ifndef __INCvbivbiCoreSeth
#define __INCvbivbiCoreSeth

#include <ctype.h>

#ifdef __cplusplus
extern "C" {
# /* __cplusplus */

#ifndef _ASMLANGUAGE

/* set of macros to manipulate the coreset_t type */

#define CORESET_COPY(coreSetDst, coreSetSrc)  (coreSetDst = coreSetSrc)
#define CORESET_ISZERO(coreset)         (coreset == 0 ? TRUE : FALSE)
#define CORESET_SET(coreset, n)         (coreset |= (1 << n))
#define CORESET_ISSET(coreset, n)       (coreset & (1 << n))
#define CORESET_CLR(coreset, n)         (coreset &= ~(1 << n))
#define CORESET_ZERO(coreset)           (coreset = 0)

#define CORESET_FIRST_SET(coreset)                ((int)coreset & (int)-coreset)
#define CORESET_FIRST_INDEX(coreset)              (FFS_LSB (coreset) - 1)
#define CORESET_ADD(coresetAugend,coresetAddend)   (coresetAugend |= coresetAddend)
#define CORESET_SUB(coresetMinuend,coresetSubtrahend)      \
        (coresetMinuend &= ~coresetSubtrahend)


































#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbivbiCoreSeth */
