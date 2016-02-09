/* vbiVersion.h - vbi version information */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,07sep11,m_h  Sync with HV 1.3.1.1 02-Sept-11 DVD
01b,29apr10,pad  Moved extern C statement after include statements.
01a,29jun09,to   created from vbiVersion.h, v01b for HV 1.1
*/

#ifndef __INCvbiVersionh
#define __INCvbiVersionh

#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_VBI_VER_2_0

#define VBI_VERSION_MAJOR 2

/*
 * Release identification, major, minor, and maintenance numbers.
 *
 * Current vbi release number
 */

#define VBI_RUNTIME_NAME     "Wind River Hypervisor Virtual board interface"
#define VBI_RUNTIME_VERSION  "2.2.1"

/* textual description of this product version */

#define VBI_VERSION VBI_RUNTIME_NAME " " VBI_RUNTIME_VERSION

#ifndef _ASMLANGUAGE
extern const char *vbiCreationDate;
extern const char *vbiRuntimeVersion;
extern const char *vbiRuntimeName;
extern const char *vbiVersion;

extern const uint32_t vbiVersionMajor;
extern const uint32_t vbiVersionMinor;
extern const uint32_t vbiVersionMaint;
#endif

#else /* _WRS_CONFIG_VBI_VER_1_0 */

#define VBI_VERSION_MAJOR 1

#endif /* _WRS_CONFIG_VBI_VER_ */

#ifdef __cplusplus
}
#endif

#endif /* __INCvbiVersionh */
