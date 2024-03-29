/* hookLib.h - Generic hook management library header */

/*
 * Copyright (c) 2003-2005, 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,28apr10,pad  Moved extern C statement after include statements.
01k,10dec09,cww  Removed temporary variable in HOOK_INVOKE_CHECK_RETURN
01j,21aug09,jpb  Changed prototype for hookShow.
01i,17mar09,jpb  Updated for LP64 support.
01h,10jul08,mdo  remove warnings
01g,22feb08,pad  Fixed HOOK_INVOKE_CHECK_RETURN so that it does not continue
                 walking through the hook table when it finds an empty slot.
01f,09sep05,yvp  Deleted prototypes for hookLibInit & hookShowInit (SPR 106485).
01e,24jan05,aeg  added hookShow() function prototype (SPR #106381).
01d,29apr04,cjj  Added hookShowInit() prototype and added "extern" to all
		 prototype declarations.
01c,08mar04,yvp  Corrected doc error for HOOK_INVOKE_CHECK_RETURN.
01b,16feb04,yvp  Added S_hookLib_HOOK_TABLE_NULL.
01a,18nov03,yvp  written.
*/

/*
DESCRIPTION
*/

#ifndef __INChookLibh
#define __INChookLibh

/* includes */

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* generic status codes for hookLib */

#define S_hookLib_HOOK_TABLE_FULL   (M_hookLib | 1)
#define S_hookLib_HOOK_NOT_FOUND    (M_hookLib | 2)
#define S_hookLib_HOOK_TABLE_NULL   (M_hookLib | 3)

#ifndef _ASMLANGUAGE

/******************************************************************************
*
* HOOK_INVOKE_VOID_RETURN - Invoke all hooks in a table.
*
* This macro calls all hook functions added into the given hook table <tbl>
* of size <sz>. The called functions are not expected to return anything
* (return values are not checked). The <typecast> argument is a typecast
* that is applied to all function pointers in the table. This is done for
* type checking purposes. The <arglist> argument is a parenthesis-enclosed
* argument list that is passed verbatim to each hook function called.
*
* \NOMANUAL
*/

#define HOOK_INVOKE_VOID_RETURN(tbl,sz,typecast,arglist) \
    {						 	 \
    int ix;						 \
							 \
    for (ix = 0; ix < sz; ix++)				 \
	{						 \
	if ((typecast)tbl[ix] != (typecast)NULL)	 \
	    (*(typecast)tbl[ix])arglist;		 \
	else						 \
	    break;					 \
	}						 \
    }

/******************************************************************************
*
* HOOK_INVOKE_CHECK_RETURN - Invoke all hooks in a table, performing return
*                            value checking.
*
* This macro calls all hook functions added into the given hook table <tbl>
* of size <sz>. The return value from each called function is compared with
* <keepGoing>, and hook execution stops if they differ. In that case, any
* remaining hooks are not executed. The <typecast> argument is a typecast
* that is applied to all function pointers in the table. This is done for
* type checking purposes. The <arglist> must be a parenthesis-enclosed
* argument list that is passed verbatim to each hook function called.
*
* \NOMANUAL
*/

#define HOOK_INVOKE_CHECK_RETURN(tbl,sz,typecast,arglist,keepGoing,pRetval)  \
    {									     \
    int ix; 					  		             \
							  		     \
    for (ix = 0; ix < sz; ix++)				  		     \
	{						  		     \
	if ((typecast)tbl[ix] != (typecast)NULL)	  		     \
	    {								     \
	    *(pRetval) = (*(typecast)tbl[ix])arglist;			     \
	    if (*(pRetval) != keepGoing) 	     			     \
		{					  		     \
		break;					  		     \
		}					  		     \
	    }								     \
	else								     \
	    break;							     \
	}						  		     \
    }

/* function declarations */

extern STATUS hookAddToTail (void *, void * [], int);
extern STATUS hookAddToHead (void *, void * [], int);
extern STATUS hookDelete    (void *, void * [], int);
extern BOOL   hookFind      (void *, void * [], int);

#ifdef _WRS_KERNEL
extern void   hookShow      (void * [], int maxEntries);
#endif /* _WRS_KERNEL */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INChookLibh */
