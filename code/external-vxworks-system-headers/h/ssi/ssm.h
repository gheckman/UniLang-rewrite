/* ssm.h - Contains definitions used by ssm.c */

/* Copyright 2004-2005 Wind River Systems, Inc. */

/* 
Modification History
--------------------
01d,19jan06,xli  Added ssiDbInit to this header
01c,10jan06,tkf  Add 'pArgs' field to ssiCompRegInfo_t and ssmCompInfo_t.
01b,09jan06,tkf  Fix DIAB compiler warnings.
01a,21aug05,tkf  Header file for ssm.c
*/

/*
DESCRIPTION

This file contains the public definitions for CSM.

*/

#ifndef __INCssmh
#define __INCssmh
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

/* enums */

/* defines */

#define SSM_COMP_NAME_LEN    16

/* Component option defines */
#define SSI_OPT_COMPLIANT   0x1
#define SSI_OPT_NONEWTASK   (SSI_OPT_COMPLIANT << 1)
#define SSI_OPT_MULTI_INST  (SSI_OPT_COMPLIANT << 2)

/* typedefs */

/*
 * 'SSM_COMP_LAUNCH_FUNCPTR' defines a type of a pointer to component
 * initialization/launch function.
 */
typedef STATUS (* SSM_COMP_LAUNCH_FUNCPTR)(long * pState, char * pArgs);

/*
 * 'ssiCompRegInfo_t' contains component registration info.
 *
 */
typedef struct
{
    char *                  pName;      /* name of component */
    char *                  pDependOn;  /* list of names of to depend on */
    SSM_COMP_LAUNCH_FUNCPTR launchFunc; /* Initilize/launch routine */
    char *                  pArgs;      /* launch routine arguments */
    char *                  pOpts;      /* options */
} ssiCompRegInfo_t;

/*
 * 'ssiCompRegInfo_t' contains component info.
 *
 */
typedef struct
{
    char *                  pName;
    long                    groupId;
    SSM_COMP_LAUNCH_FUNCPTR launchFunc;   /* Initilize/launch routine */
    char *                  pArgs;
    LIST                    dependOnList;
    long                    state;
    long                    opts;
} ssmCompInfo_t;

/* forward declarations */
STATUS ssmCompLaunchAll (void);

STATUS ssmSysDependencyReady(char *  pName);

STATUS ssiDbInit(ssiCompRegInfo_t *  pComps);

STATUS ssmCompWait(char *  pName);

IMPORT STATUS ssmCompInfoGet
    (char * pName, ssmCompInfo_t ** pInfo);
IMPORT STATUS ssmCompReady
    (char * pName);
IMPORT STATUS ssmCompCreated
    (char * pName, BOOL * pCanBeInieted);
IMPORT STATUS ssmCompLaunch
    (char * pName, char * pDependency, SSM_COMP_LAUNCH_FUNCPTR launchFunc,
     char * pArgs, char * pOpts);
STATUS ssmCompRegister
    (char * pName, char * pDependencyList, SSM_COMP_LAUNCH_FUNCPTR launchFunc,
     char * pArgs, char * pOpts, ssmCompInfo_t ** ppComp);

#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* __INCssmh */
