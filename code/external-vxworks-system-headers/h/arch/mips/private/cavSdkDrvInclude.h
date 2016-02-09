/* cavSdkDrvInclude.h - Define path to SDK for Wind River Cavium interface */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,14jun11,d_c  Rename latest SDK directory in clearcase to OCTEON-SDK
01a,20oct10,d_c  written

DESCRIPTION

This header defines a macro to be used by the Wind River Cavium hardware
interface API defined in h/arch/mips/cav*.h. In many cases, the API
defines it's data types as aliases for native Cavium SDK data types.
In these cases, the native SDK type is pulled in by including a header
from the SDK.

WARNING: The files included by the Wind River Cavium API have been
reviewed and tested to be compatible with both the Diab and Gnu
compilers, and verified to be backwards compatible to prior SDK
versions. Many of the files in the Cavium SDK will not compile with
Diab and are not suitable for directly including in our driver or BSP
code. Do not use this macro directly in any driver or BSP module, or
to include some other file that has not been verified.

*/

#ifndef __INCcavSdkDrvIncludeh
#define __INCcavSdkDrvIncludeh

#define CAV_SDK_STRINGIFY(x)    #x

/* Modules in target/src/vendor/octeon include .c and .h files direcly
 * from the SDK. They also include cav interface files
 * (arch/mips/cav*.h) for cav interface definitions. To avoid
 * including SDK files twice, these modules set CAV_INCLUDED_SDK to
 * indicate that the SDK has already been included. In that case, we
 * simply include this file, which essentially include nothing.
 */

#ifndef CAV_INCLUDED_SDK

/* Here we define the path into the SDK directory. This is where the
 * selection of the SDK version to be used by drivers is selected.  In
 * general, we always use the latest SDK we have tested and rely on it
 * to be backwards compatible with previous SDK versions.
 */
   
#define CAV_SDK_DRV_INCLUDE(incF) \
    CAV_SDK_STRINGIFY(../src/hwif/fw/cavium_sdk/OCTEON-SDK/executive/incF)

#else /* CAV_INCLUDED_SDK */

#define CAV_SDK_DRV_INCLUDE(incF) \
    CAV_SDK_STRINGIFY(arch/mips/private/cavSdkDrvInclude.h)

#endif /* CAV_INCLUDED_SDK */
#endif /* cavSdkDrvIncludeh */
