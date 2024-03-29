/* vxWindCommon.h - Common WIND object types header file */

/* Copyright 2004-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01d,08may06,tcr  add POSIX Trace Wind objects
01c,20jan06,mil  Updated for POSIX namespace conformance (P2).
01b,29jul04,dcc  removed windOmsClass from windObjClassType enum.
01a,29mar04,dcc  created from vxWind.h 01v, kernel version.
*/

/*
DESCRIPTION
This file typedefs the opaque types for WIND kernel objects.  They
are typedef-ed here so that other header files can declare functions
containing more than one of these types as parameters without having
to include each other - which could cause circular header file
inclusion problems.

The Wind object type and handle type enumerations are also defined here.
*/

#ifndef __INCvxWindCommonh
#define __INCvxWindCommonh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/*
 * The values for Wind object types and handle types are defined in
 * the enumerated types windObjClassType and handleType, respectively.
 * The values for Wind objects begin at 0, and the value for handle
 * based structs begin at 1000.   The non-overlapping range of values
 * allows tools to easily distinguish between Wind objects, which contain
 * a HANDLE struct as the first field, and handle based structures by
 * examining the type field of the HANDLE struct.
 *
 * Do not shuffle or delete any types without updating the various host
 * tools that depend on these definitions, e.g. XML and TOM.
 *
 * The _Vx_ version is always defined.  This is to make possible
 * gradual migration.  Any update should be performed on both
 * versions of the enumerations.  
 */

enum _Vx_windObjClassType
    {
    _Vx_windInvalidClass = 0,   /* invalid class type class		*/
    _Vx_windSemClass,		/* Wind native semaphore		*/
    _Vx_windSemPxClass,		/* POSIX semaphore			*/
    _Vx_windMsgQClass,		/* Wind native message queue		*/
    _Vx_windMqPxClass,		/* POSIX message queue			*/
    _Vx_windRtpClass,		/* real time process			*/
    _Vx_windTaskClass,		/* task					*/
    _Vx_windWdClass,		/* watchdog				*/
    _Vx_windFdClass,		/* file descriptor			*/
    _Vx_windPgPoolClass,	/* page pool				*/
    _Vx_windPgMgrClass,		/* page manager				*/
    _Vx_windGrpClass,		/* group				*/
    _Vx_windVmContextClass,	/* virtual memory context		*/
    _Vx_windTrgClass,		/* trigger				*/
    _Vx_windMemPartClass,	/* memory partition			*/
    _Vx_windI2oClass,		/* I2O					*/
    _Vx_windDmsClass,		/* device management system		*/
    _Vx_windSetClass,		/* Set                                  */
    _Vx_windIsrClass,           /* ISR object                           */
    _Vx_windTimerClass,         /* Timer services                       */
    _Vx_windSdClass,            /* Shared data region 			*/

    /* 
     * The value of 'windNumObjClass' represents the number of VxWorks kernel
     * object classes.  Add new object classes above 'windNumObjClass'. 
     * IMPORTANT: When a handle is initialized, this value is stored in the 
     * type member of the HANDLE structure, which is declared as an INT8.  
     * Therefore, windNumObjClass must be less than handleTypeStart, and 
     * the last handleType must be less than 256. 
     */

    _Vx_windNumObjClass
    };

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
enum windObjClassType
    {
    windInvalidClass	= 0,    /* invalid class type class		*/
    windSemClass,		/* Wind native semaphore		*/
    windSemPxClass,		/* POSIX semaphore			*/
    windMsgQClass,		/* Wind native message queue		*/
    windMqPxClass,		/* POSIX message queue			*/
    windRtpClass,		/* real time process			*/
    windTaskClass,		/* task					*/
    windWdClass,		/* watchdog				*/
    windFdClass,		/* file descriptor			*/
    windPgPoolClass,		/* page pool				*/
    windPgMgrClass,		/* page manager				*/
    windGrpClass,		/* group				*/
    windVmContextClass,		/* virtual memory context		*/
    windTrgClass,		/* trigger				*/
    windMemPartClass,		/* memory partition			*/
    windI2oClass,		/* I2O					*/
    windDmsClass,		/* device management system		*/
    windSetClass,		/* Set                                  */
    windIsrClass,               /* ISR object                           */
    windTimerClass,             /* Timer services                       */
    windSdClass,                /* Shared data region 			*/
    windPxTraceClass,           /* POSIX trace                          */

   /* see comments in posix section on windNumObjClass */
    windNumObjClass
    };
#endif  /* _POSIX_xxx_SOURCE */


enum _Vx_handleType
    {
    _Vx_handleTypeUnknown = -1,	/* bad handle				*/
    _Vx_handleTypeStart	= 100,	/* starting value for handle types	*/
    _Vx_handleTypeHashTbl = 100,/* hashLib HASH_TBL			*/
    _Vx_handleTypeSymTbl,	/* symLib SYMTAB			*/
    _Vx_handleTypeFile,		/* stdioLib FILE			*/
    _Vx_handleTypeRbuff,	/* rbuffLib RBUFF			*/
    _Vx_handleTypeModuleDesc,	/* moduleLib MODULE_DESC		*/
    _Vx_handleTypeClass,	/* classLib OBJ_CLASS			*/
    _Vx_handleTypeModuleListDesc,/* moduleLib MODLIST_DESC		*/
    _Vx_handleTypeModuleHdl,	/* malLib MODULE_HDL			*/
    _Vx_handleTypeSectionDesc,	/* moduleLib SECTION_DESC		*/
    _Vx_handleTypeEnvironment,	/* envLib ENV_TBL			*/
    _Vx_handleTypeCbioHdl,	/* cbioLib CBIO_DEV handle		*/
    _Vx_handleTypeHamChannel,	/* hamLib (Foundation HA) HAM_ID	*/

    /* The value of 'handleNumType' represents the number of handle
     * types.  Add new object classes above 'handleNumType' and
     * update the definition of 'handleNumType'.
     */

    _Vx_handleNumType	= _Vx_handleTypeHamChannel - _Vx_handleTypeStart + 1
    };

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
enum handleType
    {
    handleTypeUnknown	= -1,	/* bad handle				*/
    handleTypeStart	= 100,	/* starting value for handle types	*/
    handleTypeHashTbl	= 100,	/* hashLib HASH_TBL			*/
    handleTypeSymTbl,		/* symLib SYMTAB			*/
    handleTypeFile,		/* stdioLib FILE			*/
    handleTypeRbuff,		/* rbuffLib RBUFF			*/
    handleTypeModuleDesc,	/* moduleLib MODULE_DESC		*/
    handleTypeClass,		/* classLib OBJ_CLASS			*/
    handleTypeModuleListDesc,	/* moduleLib MODLIST_DESC		*/
    handleTypeModuleHdl,	/* malLib MODULE_HDL			*/
    handleTypeSectionDesc,	/* moduleLib SECTION_DESC		*/
    handleTypeEnvironment,	/* envLib ENV_TBL			*/
    handleTypeCbioHdl,		/* cbioLib CBIO_DEV handle		*/
    handleTypeHamChannel,	/* hamLib (Foundation HA) HAM_ID	*/

   /* see comments in posix section on windNumObjClass */
    handleNumType	= handleTypeHamChannel - handleTypeStart + 1
    };
#endif  /* _POSIX_xxx_SOURCE */


#endif /* #ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxWindCommonh */
