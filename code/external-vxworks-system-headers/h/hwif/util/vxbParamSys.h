/* vxbParamSys.h - vxBus parameter system */

/* 
 * Copyright (c) 2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
02b,29apr10,pad  Moved extern C statement after include statements.
02a,29mar10,cwl  add the function vxbInstUsrOptionGet. (WIND00204365)
01a,07Nov05,tor  created
*/

#ifndef _INC_vxbParamSysH
#define _INC_vxbParamSysH

/* includes */

#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* define parameter types */

#define VXB_PARAM_END_OF_LIST	0x0000
#define VXB_PARAM_INT32		0x0001
#define VXB_PARAM_INT64		0x0002
#define VXB_PARAM_STRING	0x0003
#define VXB_PARAM_POINTER	0x0004
#define VXB_PARAM_FUNCPTR	0x0005

/* typedefs */

/* BSP-resident table containing parameter override values */

typedef union vxbInstParamValue VXB_INST_PARAM_VALUE;
union vxbInstParamValue
    {
    void *			pValue;
    UINT32			int32Val;
    UINT64			int64Val;
    char *			stringVal;
    FUNCPTR			funcVal;
    };

typedef struct vxbInstParamOverride	VXB_INST_PARAM_OVERRIDE;
struct vxbInstParamOverride
    {
    char *			instName;
    int				unit;
    char *			paramName;
    UINT32			paramType;
    union vxbInstParamValue	value;
    };

/* driver default parameter values */

typedef struct vxbParams VXB_PARAMETERS;
struct vxbParams
    {
    char *			paramName;
    UINT32			paramType;
    union vxbInstParamValue	value;
    };

/* globals */

/* locals */

/* forward declarations */

IMPORT STATUS vxbInstParamSet
    (
    VXB_DEVICE_ID		pInst,
    char *			paramName,
    UINT32			paramType,
    VXB_INST_PARAM_VALUE *      value
    );
IMPORT VXB_DEVICE_ID vxbInstByNameFind
    (
    char *			instName,
    int				unit
    );
IMPORT STATUS vxbInstParamByNameGet
    (
    VXB_DEVICE_ID		pInst,
    char *			paramName,
    UINT32			paramType,
    union vxbInstParamValue *	pValue
    );
IMPORT STATUS vxbInstParamByIndexGet
    (
    VXB_DEVICE_ID		pInst,
    int				paramIndex,
    union vxbInstParamValue *	pValue
    );
IMPORT STATUS vxbInstUsrOptionGet
    (
    char *          paramName,
    UINT32          paramType,
    VOID **         ppValue
    );

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbParamSysH */
