/* vbi.h - virtual board support definitions */

/*
 * Copyright (c) 2007-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02b,24jun13,slk  add VBI_MEM_SIZE64_GET
02a,18dec12,jjk  WIND00393674 - Adapt VBI_CORE_PRIVMEM_BASE_GET for 64-bit
01z,17feb12,c_t  sync with HV 2.0 27-jan-12 DVD
01y,01feb12,c_t  fix C++ compile problem (WIND00299011)
01x,22sep11,wqi  VBI subset for CERT hypervisor.
01w,07sep11,m_h  Sync with HV 1.3.1.1 02-Sept-11 DVD
01v,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
01u,27jan11,jlv  Fix apigen issues
01t,23dec10,jlv  Add get macros to access memory base addresses
01s,29jul10,pad  Moved extern C statement after include statements.
01r,24may10,jl   Sync with HV 1.2 25-May-10
01q,20jan10,rgo  Add prototype for vbiVbBoardConfigFind. 
01p,30nov09,jl   Sync with HV 1.1 04-Dec-09 DVD
01o,23oct09,jl   Sync with HV 1.1 30-Oct-09 DVD
01n,12aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD
                 HV DVD vbi.h version 01y,12aug09,dtr
                 Add standard address translation functions.
                 Add missing prototyp for vbiVioapicIntAck()
01m,16jul09,to   add VBI 2.0 compatibility macros to VBI 1.0
01l,14jul09,mmi  VBI_OLD_INT_DISABLE_GET() renamed to
                 VB_INT_CORE_PREVSTATE_GET()
01k,13jul09,to   changes from v01t for HV 1.1
		         correct macro name typos
01j,29jun09,to   VBI 2.0 definitions from vbi.h, v01s for HV 1.1
01i,25mar09,to   add vbiPciIntLineRead()
01h,30jan09,rec  add vbi show prototypes
01g,16dec08,to   modified for vxWorks
01f,12dec08,mmi  rename RAZOR to WRHV
01e,11dec08,mmi  replace razor with wrhv prefix, add access macros, moved
		         razorvxworks.h contents to this file
01d,10dec08,mmi  add VIOAPIC API prototypes
01c,05dec08,mmi  add ctypes header file
01b,20nov08,mmi  adopt new naming convention
01a,20nov07,foo  written
*/

#ifndef __INCvbih
#define __INCvbih

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>

/* #include <stdlib.h> */
#include <wrhv/vbiErrors.h>
#include <wrhv/vbiTypes.h>
#include <wrhv/vbiArch.h>
#include <wrhv/vbInterface.h>
#include <wrhv/vbiSyscall.h>
#include <wrhv/vbiInterrupt.h>
#include <wrhv/vbiShmem.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/*
DESCRIPTION
This module contains the vbi methods prototypes and access macros to access the
various data structures.
*/

/* Access macros for VB control structure */

/*******************************************************************************
*
* VBI_CNTRL_ADDR_GET - Get virtual core control structure base address
*
* This macro returns the base address of the running virtual core's control
* structure.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_CONTROL * VBI_CNTRL_ADDR_GET (void)
*
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_CNTRL_ADDR_GET()		wrhvVbControl


#define VBI_INT_STATE_GET()		\
	(VBI_CNTRL_ADDR_GET()->intDisable == -1 ? TRUE: FALSE)

#define VBI_INT_STATE_SET(value)	\
	(VBI_CNTRL_ADDR_GET()->intDisable = value)

#define VBI_INT_PENDING_SET(value)	\
	(VBI_CNTRL_ADDR_GET()->intPending = value)


/*******************************************************************************
*
* VBI_VIOAPIC_BASE_GET - Get the virtual I/O APIC base address
*
* This macro returns the virtual I/O APIC base address in the configuration
* structure. This is a table that controls the state of individual IRQ
* connected to a virtual board. If the underlying hardware supports an IRQ can
* be redirected to a specific vector number. The redirection capability is not
* used for PPC platforms since all interrupts are funneled via vector 0x500.
* The VIOAPIC is comprised of a description header and a redirection table. Each
* entry in the redirection table is 64 bits wide. The size of the redirection
* table is architecture specific. See the VBI user's guide for more detailed
* information.
*
* API's for controlling the VIOAPIC:
*\ms
*\m -
* vbiVioapicIntSend()
*\m -
* vbiVioapicVectorSet()
*\m -
* vbiVioapicVectorGet()
*\m -
* vbiVioapicIntAck()
*\m -
* vbiVioapicIntMask()
*\m -
* vbiVioapicIntUnmask()
*\me
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* void * VBI_VIOAPIC_BASE_GET (void)
*
*\ce
*
* RETURNS: N/A
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiIoapicIntUnmask(), vbiVioapicVectorGet(), vbiIoapicIntMask(),
*           vbiIoapicIntSend(), vbiIoapicIntRedirect(), vbiIoapicIntAck(),
*	    VBI User's Guide
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_VIOAPIC_BASE_GET()		\
        (WRHV_MEM_PHYS_TO_VIRT(VBI_CNTRL_ADDR_GET()->vIoapic))
#else
#define VBI_VIOAPIC_BASE_GET()		\
	(VBI_CNTRL_ADDR_GET()->vIoapic)
#endif

/* VMMU0 and VMMU1 tables for context switch access macro's */

#define VBI_VMMU0_GET()			\
	(VBI_CNTRL_ADDR_GET()->vmmu0)

#define VBI_VMMU0_SET(value)		\
	(VBI_CNTRL_VMMU0_GET() = value)

/*******************************************************************************
*
* VBI_STATUS_ADDR_GET - Get virtual core status structure address
*
* This macro returns the base address of the status structure of currently
* running core. This structure is read-only and contains a description of
* the running virtual core. Hypervisor uses this data to inform the
* virtual board time variant data that may be updated during hypervisor context
* Switch. Typical that are available in the status structure are:
*
*\ms
*\m -
*Timer tick counter
*\m -
*Pending interrupt state
*\m -
*The interrupt state before this core was schedule
*\m -
*VMMU configuration
*\m -
*Virtual core registers state
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_STATUS * VBI_STATUS_ADDR_GET(void)
*
*\ce
*
* RETURNS: virtual core configuration structure base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_STATUS_ADDR_GET()		wrhvVbStatus

/*******************************************************************************
*
* VBI_INT_VCORE_PENDING - Get the pending interrupt 
*
* This returns the pending interrupts vector number for the running core. 
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiVector_t VBI_INT_VCORE_PENDING (void)
*
*\ce
*
* RETURNS: VB Interrupt Vector or 0xffff (PowerPC) Not applicable for X86
*
* ERROR CODES: N/A
*
* SEE ALSO: VBI_INT_VCORE_STATE_GET(), VBI_INT_VCORE_LOCK(),
*              VBI_INT_VCORE_UNLOCK(), VBI_INT_VCORE_PREVSTATE_GET()
*/

#define VBI_INT_VCORE_PENDING()                             \
        (VBI_CNTRL_ADDR_GET()->intPending)

/*******************************************************************************
*
* VBI_INT_VCORE_PENDING_TYPE_GET - Get the pending interrupts
*
* This returns the type of pending interrupts for the running core. This API
* are not use by hardware with virtualization support.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiVector_t VBI_INT_VCORE_PENDING_TYPE_GET(void)
*
*\ce
*
* RETURNS: 2 for timer interrupt, 1 for other external interrupts or
*           0 if none is pending
*
* ERROR CODES: N/A
*
* SEE ALSO: VBI_INT_VCORE_STATE_GET(), VBI_INT_VCORE_LOCK(),
*              VBI_INT_VCORE_UNLOCK(), VBI_INT_VCORE_PREVSTATE_GET()
*/


#define VBI_INT_VCORE_PENDING_TYPE_GET()            \
        (VBI_STATUS_ADDR_GET()->intPendingType)

/*******************************************************************************
*
* VBI_INT_VCORE_PREVSTATE_GET - Get the core's previous interrupt status
*
* This returns the previous interrupt state of the currently running core. This
* flag reflects the state of interrupts before Hypervisor injected an
* interrupt. The guest OS must restore this flag in the control structure
* before returning from the interrupt service routine.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* bool VBI_INT_VCORE_PREVSTATE_GET (void)
*
*\ce
*
* RETURNS: TRUE if locked otherwise FALSE
*
* ERROR CODES:
*
* SEE ALSO: VBI_INT_VCORE_STATE_GET(), VBI_INT_VCORE_LOCK(),
*              VBI_INT_VCORE_UNLOCK()
*/

#define VBI_INT_VCORE_PREVSTATE_GET()		\
	(VBI_STATUS_ADDR_GET()->oldIntDisable == -1 ? TRUE : FALSE)

/* timeStamp field  */

#define VBI_TIMESTAMP_GET()		\
	(VBI_STATUS_ADDR_GET()->timeStamp)

/* vmm[0,1] access macro */


/*******************************************************************************
*
* VBI_VMMU_CONFIG_GET - Get a core's VMMU configuration addr
*
* This macro gets the core's VMMU configuration structure address. The VMMU
* structure is a descriptor of the VMMU context with the following info:
*
*\ms
*\m -
* The VMMU page table base address
*\m -
* The VMMU pages
*\m -
* The page size granularity
*\me
*
* VMMU_CONFIG definition:
*
* typedef struct vmmuConfig
*    {
*    VMMU_LEVEL_1_DESC *addr;
*    size_t         pageSize;
*    uint32_t       reserved;
*    uint32_t       vmmu_num;
*    } VMMU_CONFIG;
*
* The vmmu virtual address space is restricted to 32 bits and is decoded using
* a level-1/level-2 page table.  The virtual address is decoded as follows:
*\cs
*
*
*
*
*
*
*
*
*                          32-bit Virtual Address
*        +---------------------------------------------------------+
*        |      L1 offset       | L2 offset |    Page offset       |
*        +---------------------------------------------------------+
*                11 bits           9 bits           12 bits
*                  |                 |
*                  |                 |
*    +-------------+                 |
*    |                               |
*    |                               |
*    |           L1 Table            |            L2 Table
*    |    2047 +----------+          |      511 +----------+
*    |         |          |          |          |          |
*    |         |          |          |          |          |
*    |         |          |          |          |----------|
*    |         |          |          |   +----->|    PTE   | 8 byte PTE
*    |         |          |          |   |      |----------|
*    |         |          |          |   |      |          |
*    |         |----------| 20 bits  |   |      |          |
*    +-------->|  L2 ptr  |----------+---+      |          |
*              |----------|                     |          |
*              |          |                     |          |
*              |          |                     |          |
*            0 +----------+                   0 +----------+
*               2 page (8KB)                    1 page (4KB)
*             2048 L2 pointers                 512 PTE entries
*
* Each page table entry is 8 bytes (2 words) and uses the following format:
*
* word 0 (32-bits):
*          0 1            7 8           15 1 1 1 1 2 2 2 2 24   26 27  31
*                                          6 7 8 9 0 1 2 3
*         +-+--------------+--------------+-+-+-+-+-+-+-+-+-------+------+
*         |V|  Hypervisor  |   Reserved   |U|U|U|U|U|U|U|U| ERPN  | ATTR |
*         | |   Reserved   |              |0|1|2|3|4|5|6|7|       |      |
*         +-+--------------+--------------+-+-+-+-+-+-+-+-+-------+------+
*
*                V          - valid bit
*                Hypervisor - reserved for use by hypervisor
*                U0-U7      - user defined attributes
*                ERPN       - extended real page number bits
*                ATTR       - page attributes
*
* word 1 (32-bits):
*
*          0                                19 20      23 2 2 2 2 2 2 3 3
*                                                         4 5 6 7 8 9 0 1
*         +-----------------------------------+----------+-+-+-+-+-+-+-+-+
*         |                RPN                | Reserved |R|C|U|S|U|S|U|S|
*         |                                   |          | | |X|X|W|W|R|R|
*         +-----------------------------------+----------+-+-+-+-+-+-+-+-+
*
*                RPN        - real page number
*                R          - page referenced bit
*                C          - page changed bit
*                SX,SW,SR   - supervisor mode protection bits
*                UX,UW,UR   - user mode protection bits
*\ce
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VMMU_CONFIG * VBI_VMMU_CONFIG_GET (void)
*
*\ce
*
* RETURNS: A pointer to the cores VMMU_CONFIG structure
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiVmmuConfig(), vbiVmmuEnable(), vbiVmmuDisable(),
*           vbiVmmuTlbFlush(), vbiVmmuTlbLoad()
*/


#define VBI_VMMU0_CONFIG_GET()          \
        (VBI_STATUS_ADDR_GET()->vmmu0)

#define VBI_VMMU1_CONFIG_GET()          \
        (VBI_STATUS_ADDR_GET()->vmmu1)

/*******************************************************************************
*
* VBI_TICK_COUNT_GET - Get the elapsed ticks count
*
* This returns the number timer ticks elapsed since the board has started.
* The frequency of the counter is based on the virtual board configuration XML
* file "TimerTicksFrequency" flag.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiTicks_t VBI_TICK_COUNT_GET (void)
*
*\ce
*
* RETURNS: count number of elapsed ticks for a VB
*
* ERROR CODES:
*
* SEE ALSO:
*/

#define VBI_TICK_COUNT_GET()             \
        ((vbiTicks_t)(VBI_STATUS_ADDR_GET()->tickCount))

/*******************************************************************************
*
* VBI_CONFIG_ADDR_GET - Get virtual core configuration structure base address
*
* This macro returns the base address of the configuration structure of the
* running core.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_CONFIG * VBI_CONFIG_ADDR_GET (void)
*
*\ce
*
* RETURNS: virtual core configuration structure base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_CONFIG_ADDR_GET()		wrhvVbConfig

/*******************************************************************************
*
* VBI_SHMEM_REGION_CONFIG_ADDR_GET - Get the shared memory regions base address
*
* This macro returns the address to the shared memory regions information
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_SM_INFO * VBI_SHMEM_REGION_CONFIG_ADDR_GET(void)
*
*\ce
*
* RETURNS: shared memory regions map base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_SHMEM_REGION_CONFIG_ADDR_GET()              wrhvVbSmInfo	
#else
#define VBI_SHMEM_REGION_CONFIG_ADDR_GET()		\
        (VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsConfigAddress)
#endif

/*******************************************************************************
*
* VBI_SHMEM_REGION_STATE_ADDR_GET - Get the shared memory state address
*
* This macro returns the address to the shared memory state information
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* void * VBI_SHMEM_REGION_STATE_ADDR_GET (void)
*
*\ce
*
* RETURNS: shared memory regions state address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_SHMEM_REGION_STATE_ADDR_GET()               \
        (WRHV_MEM_PHYS_TO_VIRT(VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsStateAddress))
#else
#define VBI_SHMEM_REGION_STATE_ADDR_GET()               \
        (VBI_CONFIG_ADDR_GET()->sharedMemoryRegionsStateAddress)
#endif

/*******************************************************************************
*
* VBI_MEM_REGION_CONFIG_ADDR_GET - Get memory regions map base address
*
* This macro returns address to the memory regions information.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_MEM_INFO * VBI_MEM_REGION_CONFIG_ADDR_GET (void)
*
*\ce
*
* RETURNS: memory regions map base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_MEM_REGION_CONFIG_ADDR_GET() \
(WRHV_MEM_PHYS_TO_VIRT(VBI_CONFIG_ADDR_GET()->memoryRegionsConfigAddress))
#else
#define VBI_MEM_REGION_CONFIG_ADDR_GET()		\
        (VBI_CONFIG_ADDR_GET()->memoryRegionsConfigAddress)
#endif

/*******************************************************************************
*
* VBI_INT_CONFIG_ADDR_GET - Get the address of the interrupt configuration
*
* This macro returns the address to information about incoming and outgoing 
* interrupt connections 
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_INT_INFO * VBI_INT_CONFIG_ADDR_GET (void)
*
*\ce
*
* RETURNS: interupt configuration base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_INT_CONFIG_ADDR_GET()		\
        (WRHV_MEM_PHYS_TO_VIRT(VBI_CONFIG_ADDR_GET()->interruptConfiguration))
#else
#define VBI_INT_CONFIG_ADDR_GET()		\
        (VBI_CONFIG_ADDR_GET()->interruptConfiguration)
#endif

/*******************************************************************************
*
* VBI_DEVICE_CONFIG_ADDR_GET - Get the address of the device configuration
*
* This macro returns the address to device configuration information
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* VB_DEV_INFO * VBI_DEVICE_CONFIG_ADDR_GET (void)
*
*\ce
*
* RETURNS: device configuration base address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_DEVICE_CONFIG_ADDR_GET()		\
        (WRHV_MEM_PHYS_TO_VIRT(VBI_CONFIG_ADDR_GET()->deviceConfiguration))
#else
#define VBI_DEVICE_CONFIG_ADDR_GET()		\
        (VBI_CONFIG_ADDR_GET()->deviceConfiguration)
#endif

/*******************************************************************************
*
* VBI_CONTEXT_ID_GET - Get virtual core context Id
*
* This macro returns the virtual core context id.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiCtx_t VBI_CONTEXT_ID_GET (void)
*
*\ce
*
* RETURNS: virtual core context id
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_CONTEXT_ID_GET()		\
	(VBI_CONFIG_ADDR_GET()->pid)

/*******************************************************************************
*
* VBI_BOARD_ID_GET - Get virtual Id
*
* This macro returns the virtual board id that the running core is attached.
* This is positive integer in the range [1, N]. Where N is the total number of
* boards in the system.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiVb_t VBI_BOARD_ID_GET (void)
*
*\ce
*
* RETURNS: virtual board id;
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_BOARD_ID_GET()		\
	(VBI_CONFIG_ADDR_GET()->boardID)

/*******************************************************************************
*
* VBI_VCORES_COUNT_GET - Get the number of cores in a VB.
*
* This macro returns the number of virtual cores in the VB that the calling
* core is attached. This is a positive integer in the range of [1:N]. Where N
* the total number of cores in the virtual board.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* uint32_t VBI_VCORES_COUNT_GET (void)
*
*\ce
*
* RETURNS: number of cores in a virtual board
*
* ERROR CODES: N/A
*
* SEE ALSO: VBI_VCORE_ID_GET()
*/

#define VBI_VCORES_COUNT_GET()		\
	(VBI_CONFIG_ADDR_GET()->numCores)

/*******************************************************************************
*
* VBI_VCORE_ID_GET - Get a core's id
*
* This macro returns the running core id. This is a positive integer in the
* range of [0:N-1]; Where N is the total number of cores in the system.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* vbiCore_t VBI_CORE_ID_GET (void)
*
*\ce
*
* RETURNS: the running core id
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_VCORE_ID_GET()		\
	(VBI_CONFIG_ADDR_GET()->coreId)

/*******************************************************************************
*
* VBI_VCORE_PRIVMEM_SIZE_GET - Get core's private memory size
*
* This macro returns the size in bytes of the running core's private memory
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* size_t VBI_VCORE_PRIVMEM_SIZE_GET (void)
*
*\ce
*
* RETURNS: size in bytes of the core's private memory
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiCorePrvMemFind
*/

#define VBI_VCORE_PRIVMEM_SIZE_GET()		\
	(VBI_CONFIG_ADDR_GET()->corePrivateSize)

/*******************************************************************************
*
* VBI_VCORE_PRIVMEM_BASE_GET - Get core's private memory base address
*
* This macro returns the base of the private memory associated to the running
* core's private memory
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* void * VBI_VCORE_PRIVMEM_BASE_GET (void)
*
*\ce
*
* RETURNS: a pointer to the core's private memory
*
* ERROR CODES: N/A
*
* SEE ALSO: vbiCorePrvMemFind
*/

#if defined(_WRS_CONFIG_LP64)
#define VBI_VCORE_PRIVMEM_BASE_GET()		\
	(WRHV_MEM_PHYS_TO_VIRT(VBI_CONFIG_ADDR_GET()->corePrivate))
#else
#define VBI_VCORE_PRIVMEM_BASE_GET()		\
	(VBI_CONFIG_ADDR_GET()->corePrivate)
#endif /* _WRS_CONFIG_LP64 */

/*******************************************************************************
*
* VBI_PRV_MODE_GET - Get virtual core privilege mode
*
* This macro returns the virtual core privilege mode. A privileged core has
* has full privilege access to hardware. If a core is configured to run in
* privilege mode then care must be taken to prevent negative impact to the
* rest of the system.
*
* SYNOPSIS
*
*\cs
*
*  C Preprocessor Macro
*
* uint32_t VBI_PRV_MODE_GET (void)
*
*\ce
*
* RETURNS: 1 if core has supervisor privilege otherwise 0
*
* ERROR CODES: N/A
*
* SEE ALSO:
*\NOMANUAL
*/

#define VBI_PRIV_MODE_GET()			\
	(VBI_CONFIG_ADDR_GET()->supervisorMode)

/*******************************************************************************
*
* VBI_BOARD_NAME - Get a VB name
*
* This macro returns the name of the virtual board that the running core is
* attached. This is a NULL terminated string of a maximum length of 64 bytes.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* char * VBI_BOARD_NAME (void)
*
*\ce
*
* RETURNS: a string representing the board name
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_BOARD_NAME_GET()		\
	(VBI_CONFIG_ADDR_GET()->boardName)

#define VBI_BOARD_TYPE_GET()		\
	(VBI_CONFIG_ADDR_GET()->boardType)

/*******************************************************************************
*
* VBI_BOOT_COUNT_GET - Get the number of times this board has booted
*
* This macro returns the number of times a board has booted. This may used to
* determine if the .bss data region needs to clear after a reset. This is a
* zero value since the board has booted at least one time to call this API.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* uint32_t VBI_BOOT_COUNT (void)
*
*\ce
*
* RETURNS: a positive number greater than 0
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_BOOT_COUNT_GET()		\
	(VBI_STATUS_ADDR_GET()->bootCount)

/*******************************************************************************
*
* VBI_MEM_SIZE_GET - Get the virtual board ram size
*
* This macro returns the size of ram memory in bytes that a virtual board
* has been assigned. If a virtual board has more than one core then it's memory
* is shared among all cores. Hypervisor maps the size of memory provided in the
* board's XML configuration file "RamSize" flag.
* This is a virtual memory region from Hypervisor perspective but serves as the
* phyisical memory for the virtual board.
*
* The size returned by this macro does not include the following:
*
*\ms
*\m -
* Private memory of each core attached to this virtual board
*\m -
* The regions that contain the configuration, status and control structures
*\m -
* The shared memory with other boards
*\me
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* size_t VBI_MEM_SIZE_GET (void)
*
*\ce
*
* RETURNS: The size of memory in bytes for virtual board
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_MEM_SIZE_GET()			\
	(VBI_CONFIG_ADDR_GET()->physicalMemorySize)

/*******************************************************************************
*
* VBI_MEM_SIZE64_GET - Get the virtual board 64bit ram size
*
* This macro returns the size of ram memory in bytes that a virtual board
* has been assigned. If a virtual board has more than one core then it's memory
* is shared among all cores. Hypervisor maps the size of memory provided in the
* board's XML configuration file "RamSize" flag.
* This is a virtual memory region from Hypervisor perspective but serves as the
* phyisical memory for the virtual board.
*
* The size returned by this macro does not include the following:
*
*\ms
*\m -
* Private memory of each core attached to this virtual board
*\m -
* The regions that contain the configuration, status and control structures
*\m -
* The shared memory with other boards
*\me
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* uint64_t VBI_MEM_SIZE64_GET (void)
*
*\ce
*
* RETURNS: The size of memory in bytes for virtual board
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_MEM_SIZE64_GET()                    \
        (VBI_CONFIG_ADDR_GET()->physicalMemorySize64)

/*******************************************************************************
*
* VBI_MEM_ALIAS_SIZE_GET - Get the size of aliased ram
*
* This macro returns a virtual board's aliased memory size.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* size_t VBI_MEM_ALIAS_SIZE_GET (void)
*
*\ce
*
* RETURNS: The aliased memory size.
*
* ERROR CODES: N/A
*
* SEE ALSO:
*\NOMANUAL
*/

#define VBI_MEM_ALIAS_SIZE_GET()		\
	(VBI_CONFIG_ADDR_GET()->memoryAliasSize)

/*******************************************************************************
*
* VBI_MEM_ALIAS_ADDR_GET - Get the virtual board ram alias address
*
* This macro returns a virtual board's ram alias base address. This is a
* physical address from the board's perspective but a virtual address mapped
* to the board's ram address from Hypervisor's perspective.
* Hypervisor maps this address based on "RamAliasAddr" value in the board's XML
* configuration file. The virtual board's ram and this address point to the
* same physical address. This is convenient mechanism for a virtual board that
* needs to remap it's physical address to a different address.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* void * VBI_MEM_ALIAS_ADDR_GET (void)
*
*\ce
*
* RETURNS: The base address of ram alias address
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_MEM_ALIAS_ADDR_GET()		\
	(VBI_CONFIG_ADDR_GET()->memoryAliasAddress)

/*******************************************************************************
*
* VBI_MEM_ENTRY_RTN - Get a core entry point function
*
* This macro returns the address of the entry point function of a particular
* core. This address is derived from the guest OS binary image a compile time
* while creating the hypervisor system.elf image. Hypervisor calls this
* function and passes it to the configuration address and the boot flag when
* launching a virtual core.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* void * VBI_MEM_ENTRY_RTN(void)
*
*\ce
*
* RETURNS: The entry point function of a virtual core
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_ENTRY_RTN_GET()		\
	(VBI_CONFIG_ADDR_GET()->resetPC)

/*******************************************************************************
*
* VBI_TICK_TIMER_FREQ_GET - Get a core timer tick frequency
*
* This macro returns a core's timer clock frequency. It is the number of timer
* ticks per second. It is based on the "TickTimerFrequency" flag specified in
* the board's XML configuration file.
* The timer tick interrupt is delivered to only the running core of a VB. If a
* core is not running the counter in the status page is incremented.
* If "TickTimerFrequency" is set to a value of 0 for a board it  disables the
* timer tick.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* vbiTicks_t VBI_TICK_TIMER_FREQ_GET (void)
*
*\ce
*
* RETURNS: The number of ticks per second
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_TICK_TIMER_FREQ_GET()			\
	(VBI_CONFIG_ADDR_GET()->tickTimerFrequency)

#define VBI_TIMESTAMP_FREQ_GET()			\
	(VBI_CONFIG_ADDR_GET()->timeStampFrequency)

/*******************************************************************************
*
* VBI_BOOTLINE_ADDR_GET - Get a virtual board bootline parameters address
*
* The bootline parameters is a string that contains configuration data that a
* user may specify in the virtual XML configuration "BootLine" flag. A guest
* OS running on Hypervisor must use this bootline instead of it's native
* bootline parameters. For example VxWorks bootline parameters are not passed
* to the VB running VxWorks. The size of the bootline parameters string is
* determined by VB_MAX_BOOTLINE_LENGTH at compile time flag. The bootline is
* NULL terminated string.
*
* SYNOPSIS
*
*\cs
*
* C Preprocessor Macro
*
* const char * VBI_BOOTLINE_ADDR_GET (void)
*
*\ce
*
* RETURNS: The address of the bootline parameters.
*
* ERROR CODES: N/A
*
* SEE ALSO:
*/

#define VBI_BOOTLINE_ADDR_GET()				\
	(VBI_CONFIG_ADDR_GET()->bootLine)

#define VBI_PANIC(vector, halt)				\
    {							\
    VB_PRINTF ("core%d: unhandled exception: 0x%x\n",   \
		wrhvVbConfig->coreId, vector);		\
    if (halt)						\
        {						\
        vbiPanic ("unhandled exception");		\
	}						\
    }

#ifndef ERROR
#define ERROR	(-1)
#endif
#ifndef OK
#define OK	0
#endif
#ifndef NULL
#define NULL	0
#endif

/* typedefs */

typedef struct vbiClkHook
    {
    void (*rtn)(void *pArg);
    void * pArg;
    } VBI_CLK_HOOK_INFO, * VBI_CLK_HOOK_INFO_PTR;

/* externs */
#ifdef _WRS_CONFIG_LP64
extern VB_SM_INFO * wrhvVbSmInfo;
extern VB_MEM_INFO *wrhvVbMemInfo;
#endif
extern VB_CONFIG  * wrhvVbConfig;
extern VB_STATUS  * wrhvVbStatus;
extern VB_CONTROL * wrhvVbControl;
extern int32_t      wrhvVbIntNested;
extern void vbiInit (VB_CONFIG * config);
extern void vbiExcStub (void);
extern void ASSERT_FN (const char *, const char *, int);
extern void vbiIdle (uint64_t);
extern void * vbiVioapicAddrGet (void);
extern vbiStatus_t vbiVioapicVectorSet (vbiIrq_t irq, vbiVector_t vector);
extern vbiVector_t vbiVioapicVectorGet (vbiIrq_t irq);
extern vbiStatus_t vbiVioapicIntUnmask (vbiIrq_t irq);
extern vbiStatus_t vbiVioapicIntMask (vbiIrq_t irq);
extern vbiStatus_t vbiVioapicIntAck (vbiIrq_t irq);
extern vbiStatus_t vbiVioapicIntSend (vbiIrq_t irq, uint32_t filter,
				      vbiVb_t vb);
#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
extern vbiStatus_t vbiVioapicIntRedirect (vbiIrq_t irq, vbiCore_t tCore);
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

extern vbiStatus_t vbiVioapicVcoreIntSend (vbiIrq_t irq, vbiCoreSet_t vcoreSet, 
					  uint32_t options);
extern vbiIrq_t    vbiVioapicIntPending (void);
extern void        vbiVioapicDisplay (void);

extern vbiStatus_t vbiGuestDmaAddrGet
    (
    vbiGuestPhysAddr_t gaddr,   /* guest physical address to translate */
    vbiPhysAddr_t  *paddr       /* translated physical address */
    );
extern vbiStatus_t vbiGuestPhysToPhysAddr
    (
    vbiGuestPhysAddr_t gaddr,   /* guest physical address to translate */
    vbiPhysAddr_t  *paddr       /* translated physical address */
    );
#ifndef _WRS_CONFIG_WRHV_GUEST_CERT
extern void vbiSharedMemoryShow (void);
extern void vbiStatusShow (void);
extern void vbiControlShow (void);
extern void vbiConfigShow (void);
extern void vbiConfigPageMapShow (void);
extern void vbiMemoryShow  (void);
extern void vbiStsRegsDisplay (void);
extern void vbiCtrlRegsDisplay (void);
extern void vbiShow (void);
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT */ 
extern STATUS vbiPciIntLineRead (uint32_t pciClass, uint32_t pciSubclass,
                                 uint32_t pciBus, uint32_t pciDev, 
                                 uint32_t pciFunc, uint8_t * pIntLine);
#if !defined(_WRS_CONFIG_WRHV_GUEST_CERT) && !defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
extern vbiStatus_t vbiVbBoardConfigFind 
    ( 
    vbiVb_t			boardID,
    vbiCore_t			coreId,
    vbiGuestPhysAddr_t * 	pAddress
    );
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */
#if defined(_WRS_CONFIG_WRHV_GUEST_CERT) || defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
vbiStatus_t vbiSchedTransition
    (
    char * 	name,		/* name of schedule to transition to */
    uint32_t	transitionType,	/* transition type */
    vbiCore_t	coreId		/* CPU core to do transition in */
    );                                 
#endif /* !_WRS_CONFIG_WRHV_GUEST_CERT && !_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvbih */
