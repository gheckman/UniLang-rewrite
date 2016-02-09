/* dshmDebug.h - dSHM console debugging output */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,15jul10,gjj  deprecated the DSHM technology and added deprecation macros.
01d,29apr10,pad  Moved extern C statement after include statements.
01c,07sep06,bwa  split, added debug levels; added timestamped version.
01b,29jul06,bwa  added description;
                 moved some functionalities to a adaptation layer header file.
01a,05jul06,bwa  written.
*/

#ifndef __INCdshmDebugh
#define __INCdshmDebugh

/* Sanity #defines for cases these weren't already defined in the file including
 * this one. The way to use this file is to #define the followings to 1 if they
 * are to be turned on for the file where this file is included. Then #include
 * this file in the next line after the #define, eg. like this:
 * 
 * (in dshmSvcFoo.c)
 * [...]
 * /@ turn on debugging but no extra debugging @/
 * #define DSHM_DEBUG 1
 * #define DSHM_EXTRA_DEBUG 0
 * #include <dshm/debug/dshmDebug.h>
 * [...]
 * 
 */
 
#ifndef DSHM_DEBUG
#define DSHM_DEBUG	0
#endif
#ifndef DSHM_EXTRA_DEBUG
#define DSHM_EXTRA_DEBUG 0
#endif
#ifndef DSHM_TIMESTAMP
#define DSHM_TIMESTAMP 0
#endif

#include <dshm/dshm.h>
#include <dshm/adapt/debug.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void dshmDebugInit (const int debugLevel)
	_WRS_DEPRECATED ("DSHM will be deprecated, you can use MIPC instead");

/* Debugging levels.
 * Used as the first parameter to DSHMDBG() and IDSHMDBG(). For the output to
 * be displayed, the chosen debugging level must be of higher or equal priority
 * than the overall debugging level set in the system. The latter can be set by
 * using the DSHM_INIT_DBG_LVL configuration parameter at configuration time. It
 * can also be set programmatically and thus modified at a later time by setting
 * the global variable 'dshmDebugLevel' to the desired level of output.
 * 
 * WARNING: If the dSHM library is built with debugging support enabled and the
 * global debugging level is set to VERBOSE, *lots* of debugging output will be
 * displayed, with a high probability of disrupting system operation.
 * 
 * Three debugging levels are provided for service usage: DSHMDBG_SVC_LO,
 * DSHMDBG_SVC and DSHMDBG_SVC_HI, the latter being of the higher priority.
 * Setting the global debugging output level to any of the DSHMDBG_SVC levels
 * will also ouptut error conditions from the dSHM libraries if they were built
 * with debugging enabled. Low-importance information will not be displayed.
 * 
 * eg.
 * 
 * void dshmSvcFooInit (void)
 *     {
 *     dshmDebugLevel = DSHMDBG_SVC;
 *     }
 * 
 * int dshmSvcFooBlahVerify
 *     (
 *     const int blah
 *     )
 *     {
 *     /@ Display the value 'blah' is set to: if the level set in the Init()
 *      @ routine is not modified later on, it will not get displayed.
 *      @/
 *     DSHMDBG(DSHMDBG_SVC_LO, "Value of 'blah' = %d\n", blah);
 * 
 *     /@ Ensure user passed a 16-bit value @/
 *     if ((blah & 0xffff) != blah)
 *         {
 *         /@ Will get displayed with the level set in the Init() routine. The
 *          @ value of this debugging info was chosen to be higher than the one
 *          @ chosen to display the value of 'blah' since this is an error
 *          @ condition, and thus of higher importance for debugging.
 *          @/
 *         DSHMDBG(DSHMDBG_SVC_HI, "Value passed is too large!\n");
 *         return -1;
 *         }
 *     return 0;
 *     }
 */

#define DSHMDBG_UNUSED	0xe	/* use this for debug output that impedes
				 * correct functionality but that might be
				 * turned on by changing the debug level to a
				 * higher one */
#define DSHMDBG_MAX	0xd

#define DSHMDBG_VERBOSE 0xc	/* this is the lowest level dshmDebugLevel
				 * should be set to. */

#define DSHMDBG_INFO_LO	0xb
#define DSHMDBG_INFO	0xa

#define DSHMDBG_SVC_LO	0x9	/* use these for service debugging, to get */
#define DSHMDBG_SVC	0x8	/* service-specific debugging info and */
#define DSHMDBG_SVC_HI	0x7	/* possible important core dSHM debug info */

#define DSHMDBG_INFO_HI	0x6

#define DSHMDBG_WARNING	0x5
#define DSHMDBG_ERROR	0x4
#define DSHMDBG_CRIT	0x3
#define DSHMDBG_FATAL	0x2
#define DSHMDBG_TMP	0x1	/* debugging info that *must* be printed for
				 * current debugging, *has to* be changed to a
				 * lower debug level before getting put into
				 * codebase */

#define DSHMDBG_OFF	0x0

extern int dshmDebugLevel;
extern const char dshmDebugLevelStr[][32];

#if DSHM_DEBUG
    /* regular debugging printout */
#if 1
#if DSHM_TIMESTAMP
#if 1
    #define DSHMDBG(lvl, fmt, args...) \
	do \
	    { \
	    if (lvl <= dshmDebugLevel && lvl > DSHMDBG_OFF) \
		{ \
		DSHM_TIMESTAMP_INC(); \
		DSHM_PRINT ( \
		"[(%4.4x:%4.4x)%s@%d] " fmt, \
		    DSHM_TIMESTAMP_GET(0), \
		    DSHM_TIMESTAMP_GET(1), \
		    __FILE__, __LINE__, \
		    ##args); \
		} \
	    } \
	while (0)
#else
    #define DSHMDBG(lvl, fmt, args...) \
	do \
	    { \
	    if (lvl <= dshmDebugLevel && lvl > DSHMDBG_OFF) \
		{ \
		DSHM_TIMESTAMP_INC(); \
		DSHM_PRINT ( \
		"[<%s> %s@%d(%#x)] " fmt, \
		    dshmDebugLevelStr[lvl], __FILE__, __LINE__, \
		    DSHM_TIMESTAMP_GET(), \
		    ##args); \
		} \
	    } \
	while (0)
#endif
#else
    #define DSHMDBG(lvl, fmt, args...) \
	do \
	    { \
	    if (lvl <= dshmDebugLevel && lvl > DSHMDBG_OFF) \
		{ \
		DSHM_PRINT ( \
		"[<%s> %s@%d] " fmt, \
		    dshmDebugLevelStr[lvl], __FILE__, __LINE__, \
		    ##args); \
		} \
	    } \
	while (0)
#endif
#endif
    /* interrupt-safe debugging printout */
    #define DSHMDBGI(lvl, fmt, a, b, c) \
	do \
	    { \
	    if (lvl <= dshmDebugLevel && lvl > DSHMDBG_OFF) \
		{ \
		DSHM_IPRINT ("[<%s> %s@%d] " fmt, \
		    (int)dshmDebugLevelStr[lvl], (int)__FILE__, (int)__LINE__, \
				(int)a, (int)b, (int)c); \
		} \
	    } \
	while (0)
	
    /* support old style without level as a parameter */
    #define DPRINTF(fmt, args...) \
	DSHMDBG(DSHMDBG_VERBOSE, fmt, ##args)
    #define IDPRINTF(fmt,a,b,c) \
	DSHMDBGI(DSHMDBG_VERBOSE, fmt, a,b,c)
	
    /* screen dump of a message's contents */
    #define DSHM_MSG_DUMP(msg, align, level)	dshmMsgDump(msg, align, level)
#else
    #define DSHMDBG(lvl, fmt, args...)
    #define DSHMDBGI(lvl, fmt, args...)
    #define DPRINTF(fmt, args...)
    #define IDPRINTF(fmt,a,b,c)
    #define DSHM_MSG_DUMP(msg, align, level)
#endif

#ifdef __cplusplus
}
#endif

#endif	/* __INCdshmDebugh */

