/* vbiTypes.h - virtual board interfaces types definitions */

/*
 * Copyright (c) 2009-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,01feb12,c_t  fix C++ compile problem(WIND00311202)
01l,25aug11,c_t  Sync with HV 2.0
01k,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01j,24may10,jl   Sync with HV 1.2 25-May-10
01i,29apr10,pad  Moved extern C statement after include statements.
01h,20may10,rgo  fix unresolved _RType
01g,03mar10,rgo  sync-up with hv1.2 view on 3/3/10
01f,23oct09,jl   Sync with HV 1.1 30-Oct-09 DVD
01e,22sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
01d,13aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD
                 HV vbiTypes.h 01d 12aug09,dtr  ADd vbiGuestPhysAddr type.
		 Add definition of MSG_HEADER type from HV sys/wrhvMsg.h
		 Add definition of vb_t type from HV sys/types.h
01c,02jul09,mmi  fixe vbiIrq_t and vbiVector_t types
01b,11jun09,mmi  add vbiIntState_t, vbiMemAttr_t, etc..
01a,09jun09,mmi  written
*/

#ifndef __INCvbiTypesh
#define __INCvbiTypesh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ASMLANGUAGE

#include <ctype.h>

typedef uint32_t		vbiVb_t;
typedef int32_t			vbiCore_t;
typedef uint32_t		vbiCtx_t;
typedef uint64_t    		vbiPhysAddr_t;
typedef void *       		vbiGuestPhysAddr_t;
typedef int32_t			vbiStatus_t;		
typedef int32_t			vbiIntState_t;		
typedef int32_t			vbiMemAttr_t;		
typedef int32_t			vbiVector_t;		
typedef int32_t         vbiIrq_t;
typedef uint32_t		vbiCoreSet_t;		
typedef uint32_t		vbiRegSet_t;		
typedef int32_t                 status_t;
typedef uint64_t                vbiRType64_t;
typedef uint32_t                vbiRType32_t;
typedef uint16_t                vbiRType16_t;
typedef uint64_t                vbiTimeout_t;
typedef uint64_t                vbiTicks_t;
typedef union vbiRegisterType
    {
    vbiRType64_t    reg64;
    vbiRType32_t    reg32;
    vbiRType16_t    reg16;
    } vbiRType_t;  

#define NAME_LENGTH 64
#define BOOTLINE_LENGTH 256

typedef char vbiName_t[NAME_LENGTH];
typedef char vbiBootline_t[BOOTLINE_LENGTH];

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCvbiTypesh */
