/* mpApic.h - Intel MP APIC/xAPIC (Advanced PIC) */

/* Copyright 2006, 2008, 2010 Wind River Systems, Inc. */ 

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,27aug08,jpb  Renamed VSB header file
01e,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01d,30oct06,scm  rename mpApicNcpu to vxCpuCount...
01c,31aug06,scm  add support for CPU ID translation table...
01b,26jul06,scm  update for pentium/xeon support...
01a,26jul06,hdn  written...
*/

#ifndef __INCmpApich
#define __INCmpApich

	
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUILT_IN_APIC    0

/* Maximum Number of IOAPICs in the system */
#ifndef MAX_IOAPICS
#define MAX_IOAPICS	16
#endif

#ifndef _ASMLANGUAGE

/* variable declarations */
IMPORT MP_FPS *mpApicFps;

#ifdef _WRS_CONFIG_SMP
IMPORT unsigned int vxCpuCount; /* number of CPUs (MP Table) */
#endif /* _WRS_CONFIG_SMP */

IMPORT UINT32 mpApicNioApic;  /* number of IO APICs (MP Table) */
IMPORT UINT32 mpApicNbus;     /* number of buses (MP Table) */
IMPORT UINT32 mpApicNioint;   /* number of io interrupts (MP Table) */
IMPORT UINT32 mpApicNloint;   /* number of local interrupts (MP Table) */

IMPORT UINT32 *mpApicAddrTable[]; /* logical apic id to address mapping */

#ifdef _WRS_CONFIG_SMP
IMPORT UINT8 mpCpuIndexTable[];    /* cpu Id translation */
IMPORT UINT8 mploApicIndexTable[]; /* loApic Id translation */
#endif /* _WRS_CONFIG_SMP */

IMPORT UINT8 mpApicLogicalTable[]; /* recorded id mapping */
IMPORT UINT8 mpApicRedEntries[];
IMPORT UINT8 mpApicBaseIrq[];

IMPORT MP_INTERRUPT *mpApicInterruptTable;

IMPORT MP_BUS *mpApicBusTable;

#if defined(__STDC__) || defined(__cplusplus)

STATUS mpApicMpConfigTableInit(void);

INT8 *mpApicScan(INT8* match, INT8 * start, INT8 * end);

UINT32 mpApicIrqToBusIrq(UINT32 ioApicId, UINT32 irq);

#else

IMPORT STATUS mpApicMpConfigTableInit();

IMPORT INT8 *mpApicScan();

IMPORT UINT32 mpApicIrqToBusIrq(UINT32 ioApicId, UINT32 irq);

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmpApich */
