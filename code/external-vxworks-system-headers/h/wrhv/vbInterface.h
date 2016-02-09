/* vbInterface.h - virtual board interface header file */

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
02r,24jun13,slk  add physicalMemorySize64 for > 4GB support
02q,17feb12,c_t  sync with HV 2.0 27-jan-12 DVD
02p,11nov11,c_t  sync with HV 2.0 23-sept-11 DVD
02o,07sep11,m_h  Sync with HV 1.3.1.1 02-Sept-11 DVD
02n,23may11,c_t  Sync with HV 2.0
02m,18apr11,wqi  Sync with CERT HV DVD.
02l,04apr11,jlv  Sync with HV 1.3 01-Apr-11 (WIND00265419)
02k,08feb11,jlv  Sync with HV 1.3 04-Feb-11
02j,27jan11,jlv  Fix apigen issues
02i,23dec10,jlv  Add 64-bit guestPhys-to-virt translation macro
02h,02dec10,rab  Update for WRHV-1.3
02g,03nov10,rab  workaround 6.9 compiler alignment issue
02f,12jun10,rab  Add VB_CONFIG_VCORE_ID offset definition for guest smp
02e,30jul10,jl   Update to support LP64
02d,24may10,jl   Sync with HV 1.2 25-May-10
02c,02mar10,rgo  Sync with HV1.2 on 3/3/10.
02b,26oct09,jl   Sync with HV 1.1 30-Oct-09 
02a,07oct09,d_c  Defect WIND00185185 Fix WIND00185188 - Fix apigen errors
01z,12aug09,d_c  Sync with HV 1.1 14-Aug-09 DVD, v02o from HV 1.1
01y,30jun09,to   VBI 2.0 definitions from vbInterface, v02m for HV 1.1
01x,30jan09,rec  merge updated vbControl structures layout from vxw6.6
01w,22jan09,amf  add vbiShow routine
01v,16dec08,to   modified for vxWorks
01u,13dec08,mmi  update it for pentium only
01t,19nov08,dtr  Remove interrupt controller.
01s,03oct08,dbt  Added tickCount to VB_STATUS.
01r,01aug08,md   add tracking of region data type
01q,19may08,gws  add virtual IO APIC
01p,23nov07,foo  add boot defines
01o,08nov07,md   add bootline support
01n,09nov07,foo  remove includes
01m,25oct07,foo  updated for hardware interrupts
01l,09oct07,md   add emulated srr1 register
01k,04oct07,md   include sys/cpu_types.h
01j,11sep07,md   added emulated MSR register for PPC
01i,23aug07,md   added vmmu and PPC volatile regs to control page
01h,25jul07,md   added memory aliasing information
01g,29may07,ymz  added port support.
01f,25may07,foo  updated for inter-board interrupts
01e,17may07,foo  updated for improved interrupt delivery
01d,23apr07,foo  added fields for user mode virtual boards and interrupts
01c,16mar07,foo  renamed RAZOR_CPU to CPU
01b,16mar07,foo  update for generalized interface and interrupt delivery
01a,15feb07,foo  written
*/

/*
DESCRIPTION
This module defines the data structures used for information flow between
wind river Hypervisor and a Virtual Board. There are three structures employed
for this purpose:
\ms
\m -
 configuration
\m -
 status
\m -
 control
\me

The configuration structure is the first data exchanged between a given virtual
board and Hypervisor kernel. The pointers to the status and control structures are
derived from the configuration structure. It contains pointers to the status,
control and other information about resources assigned to a virtual board.
The configuration data is shared accross the cores in the same virtual board unlike
the data in the control and status structure which may be different for each core.
The information in the configuration structure is static in the sense that the data
it contains remain unmodified at least during the life of a boot cycle.

The status structure is used to inform a virtual core at runtime about the state it
is excecuting (interrupts, vmmu, elapsed time etc...).

The control structure is put in place as a fast method to pass information from
the VB to Hypervisor or vis-versa. For examples during a virtual board context
switch the control structure allows to store the incoming virtual board context
setting before the virtual board sends a Hypercall using VBI_CTX_LOAD().

Hypervisor passes (as parameter) a pointer of the configuration structure to the
entry function of the virtual core and a boot option flag.

The VBI library provides a initialization function vbiInit() to ensures that
Hypervisor version number is compatible with the VBI library in use. If the versions
match then the configuration, status and control pointers are stored respectively to
wrhvVbConfig, wrhvStatus and wrhvVbControl.

Therefore a virtual board must always call vbiInit() before accessing any data
provided by Hypervisor nor send a hypercall to it. Refer to to vbiInit() description 
in the VBI API description document for more information.

Once the VBI library is initialized the virtual board should employ the provided
macros in order to access the fieds in wrhVbConfig, wrhvVbStatus and wrhvVbControl
data structures. Accessing these structures via the VBI function guaranties source
level compatibily between VBI versions.

A guest OS should port vbiInit(), the access macros along with the necessary header
files where the data structrures layout is defined.
 To be aware:
\ms
\m -
 Changing the order of the field this structure may have serious impact on the
 integrity of the system. It exists hand crafted macros to match the C
 structures offset. Therefore any change should be reflected in the macros

\m -
 When a virtual core boots the VMMU is not enbled but a programmer may choose
 to turn-on the VMMU. In that scenario proper care must be taken to ensure that
 the address where the control, status or configureation structure is reflected
 in the VMMU mapping. Technically these area should be treated as I/O region
 therefore it is encouraged that they are identity mapped.
\me

*/

#ifndef __INCvbInterfaceh
#define __INCvbInterfaceh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>
#include <wrhv/vbiArch.h>

#ifdef __cplusplus
extern "C" {
#endif


/* macro to align guest fields for a 64-bit hypervisor */

#if defined(_WRS_CONFIG_LP64)
# define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			   __attribute__(( aligned(8) )) \
			   decl_var
#else
# if (__VBI_BYTE_ORDER == __VBI_LITTLE_ENDIAN)
#  define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			    __attribute__(( aligned(8) )) \
			    decl_var; \
			    uint32_t pad_var
# else
#  define VB_ALIGN_FIELD_64(decl_var, pad_var)	\
			    __attribute__(( aligned(8) )) \
			    uint32_t pad_var; \
			    decl_var
# endif
#endif

# define VB_PRINTF(fmt, args...)    printf(fmt, ##args)

#undef VB_DEBUG  /* define it to turn on debugging */
#ifdef VB_DEBUG
# define VB_DEBUG_MSG(fmt, args...)    VB_PRINTF(fmt, ##args)
#else
# define VB_DEBUG_MSG(fmt, args...)
#endif

/* For 64-bit, translate guest physical address to guest virtual address */

#if defined(_WRS_CONFIG_LP64)
#define WRHV_MEM_PHYS_TO_VIRT(addr)               \
   (addr ? (void *)((0xffffffff80000000UL) | (ULONG)addr) : (void *)NULL)
#endif

/* Configuration Filename for the hypervisor this must not change */

#define VB_WRHV_CONFIGURATION_FILE "wrhvConfig.xml"

/* Hard limits for now */

#define VB_MAX_VIRTUAL_BOARDS    1024
#define VB_MAX_BUSES             1024

#define VB_MAX_CORES		 64

/* Type definitions for all name identifer strings in the hypervisor */

#define VB_MAX_WRHV_NAME_LENGTH 64

#ifndef	_ASMLANGUAGE
typedef void * VOID_PTR;

typedef int8_t VB_WRHV_NAME[VB_MAX_WRHV_NAME_LENGTH];

#define VB_MAX_BOOTLINE_LENGTH   256

/* Virtual board timestamp is 64 bits */

typedef uint64_t VB_TIMESTAMP;
#endif

/* Virtual Interrupt Controller definitions --------------------------- */

/* The maximum number of interrupt sources allowed is defined by
 * VB_MAX_INTERRUPTS.  Care must be taken if this is changed, since some
 * algorithms and data structures will require modifications and become
 * more complex
 */

#define VB_MAX_INTERRUPTS     256

/* The maximum number of associated data stored with each interrupt.
 * This can be modified without any impacts, tho it should not be
 * set to 0
 */

#define VB_MAX_INTERRUPT_DATA 16

/* Macros to disable/enable interrupts */

#define VB_INTERRUPT_DISABLE	-1
#define VB_INTERRUPT_ENABLE	0

#define VB_INTERRUPT_PENDING_NONE 0xffff

/* Structure offsets for assembler */

#if !defined(_WRHV_ARCH_HAS_CTRL_REGS)
# define VB_CONTROL_REG_STRUCT_END 0
#endif

# define VB_CONTROL_INT_DISABLE		((4*0) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_NEW_INT_DISABLE	((4*1) + VB_CONTROL_REG_STRUCT_END)
#if (__VBI_BYTE_ORDER == __VBI_BIG_ENDIAN)
# define VB_CONTROL_VMMU0_HIGH		((4*2) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU0		((4*3) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU1_HIGH		((4*4) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU1		((4*5) + VB_CONTROL_REG_STRUCT_END)
#else
# define VB_CONTROL_VMMU0		((4*2) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU0_HIGH		((4*3) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU1		((4*4) + VB_CONTROL_REG_STRUCT_END)
# define VB_CONTROL_VMMU1_HIGH		((4*5) + VB_CONTROL_REG_STRUCT_END)
#endif /* __VBI_BYTE_ORDER */

/* Bit Mask definitions for VB_STATUS_INT_PENDING */

#define VB_STATUS_INT_PENDING_INT		1	/* Virtual Interrupt */
#define VB_STATUS_INT_PENDING_TICK		2	/* Tick interrupt */
#define VB_STATUS_INT_PENDING_DIRECT_INT	4       /* Direct Interrupt */

/* Assembler offsets for VB_STATUS */

#if !defined(_WRHV_ARCH_HAS_STATUS_REGS)
# define VB_STATUS_REG_STRUCT_END	0
#endif

#define VB_STATUS_INT_PENDING		((4*0) + VB_STATUS_REG_STRUCT_END)
#define VB_STATUS_RESERVED1		((4*1) + VB_STATUS_REG_STRUCT_END)
#define VB_STATUS_TIMESTAMP_HIGH	((4*2) + VB_STATUS_REG_STRUCT_END)
#define VB_STATUS_TIMESTAMP_LOW		((4*3) + VB_STATUS_REG_STRUCT_END)
#define VB_STATUS_OLD_INT_DISABLE	((4*4) + VB_STATUS_REG_STRUCT_END)
#define VB_STATUS_RESERVED2     	((4*5) + VB_STATUS_REG_STRUCT_END)
#if (__VBI_BYTE_ORDER == __VBI_BIG_ENDIAN)
# define VB_STATUS_VMMU0_HIGH		((4*6) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU0		((4*7) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU1_HIGH		((4*8) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU1		((4*9) + VB_STATUS_REG_STRUCT_END)
#else
# define VB_STATUS_VMMU0		((4*6) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU0_HIGH		((4*7) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU1		((4*8) + VB_STATUS_REG_STRUCT_END)
# define VB_STATUS_VMMU1_HIGH		((4*9) + VB_STATUS_REG_STRUCT_END)
#endif /* __VBI_BYTE_ORDER */

/* Assembler offsets for VB_CONFIG */

#if (__VBI_BYTE_ORDER == __VBI_BIG_ENDIAN)
# define VB_CONFIG_VBSTATUS		(((2+0) * 8) + 4)
# define VB_CONFIG_VBCONTROL		(((2+1) * 8) + 4)
# define VB_CONFIG_SMINFO		(((2+2) * 8) + 4)
# define VB_CONFIG_MEMINFO		(((2+3) * 8) + 4)
# define VB_CONFIG_INTINFO		(((2+4) * 8) + 4)
#else
# define VB_CONFIG_VBSTATUS		((2+0) * 8)
# define VB_CONFIG_VBCONTROL		((2+1) * 8)
# define VB_CONFIG_SMINFO		((2+2) * 8)
# define VB_CONFIG_MEMINFO		((2+3) * 8)
# define VB_CONFIG_INTINFO		((2+4) * 8)
#endif /* __VBI_BYTE_ORDER */

# define VB_CONFIG_SUPERVISORYMODE      (0x10 * 4)   /* supervisoryMode */

# define VB_CONFIG_VCORE_ID		(4*38)
/* Defines for vbIntInfo intDirection field */

#define VB_INPUT_INT  1
#define VB_OUTPUT_INT 2

/*
 * Defines for the second parameter passed to the startup program
 * in a virtual board by WRHV
 */

#define VB_BOOT_COLD	1
#define VB_BOOT_WARM	2
#define VB_BOOT_RESTART	3

/* define 128 entries for all platforms */

#define VIOAPIC_MAX_REDTABLE_ENTRIES	(VB_MAX_INTERRUPTS)

/* define valid guest to guest register operations */

#define VBI_REG_SET_32BIT	0
#define VBI_REG_SET_64BIT	1

#if defined(_WRS_CONFIG_WRHV_GUEST_CERT) || defined(_WRS_CONFIG_WRHV_GUEST_CERT_DEBUG)
/*
 * define schedule control commands that is the
 * first parameter in syscall vbiSchedControlOp() which
 * decides the action of control.
 */

/* do frame scdeduler frame transition */
#define SCHED_CONTROL_TRANSITION	1

/* define frame scheduler transition definitions */


#define SCHEDULER_TRANSITION_MAJOR 1
#define SCHEDULER_TRANSITION_MINOR 2
#define SCHEDULER_TRANSITION_TICK  3

#endif /* _WRS_CONFIG_WRHV_GUEST_CERT || _WRS_CONFIG_WRHV_GUEST_CERT_DEBUG */

#ifndef	_ASMLANGUAGE

/*******************************************************************************
*
* VB_CONTROL - Virtual board cores control structure
*
* VB_CONTROL is a data type that defines a virtual core's control structure.
* This is called the control structure because a core uses to modify it's
* state. The code running in the context of a virtual core puts the desired
* setting in this control and passes to Hypervisor via the Hypercall mechanism.
* It is suggested to use the provided APIs for manipulating the virtual core
* control structure instead of directly accessing it's members.
* Typically use cases for this structure are for following:
*\ms
*\m -
* During context switch for setting the incoming context's register state.
* For more information about this refer to VBI_CTX_LOAD() description in the
* architecture supplement API documentation.
*\m -
* Locking/unlocking the virtual core interrupts.
*\m -
* Loading the VMMU configuration data.
*\m -
* VIOAPIC configuration registers.
*
*\me
* The control structure definition is generic accross the various architecture
* flavours supported by Hypervisor with the exception of the emulated registers.
* There is an architecture specific extention available via a pointer of type
* VB_ARCH_STATUS_REGS to accomodate the registers unique for a given hardware
* platform.
* However that does imply that other fields defined in this structure are used
* in every architecture. A field is considered generic if it is usefull at least to
* two CPU families but not necessary to all CPUs.
* The VIOAPIC is the only field that is meaning full accross all architectures.
* Note that some architectures like Intel with VT technology don't require emulated
* registers. The pointer of emulated registers is included only if
*_WRHV_ARCH_HAS_CTRL_REGS flag is defined. The control structure is mapped
* with read/write access attribute for the purpose of serving as duplex
* communication channel between Hypervisor and a virtual core. This mechanism
* is fall back when it is not possible to use registers for transmitting data
* from the virtual core to Hypervisor or vis-versa. More information about
* VB_ARCH_CONTROL_REGS may be found in the architecture supplement document.
*
*
* Control structure graphical illustration
*\cs
*    ______________
*   |              |
*   |              |<------- 64bits - pointer to arch specific registers
*   |              |          (See architecture supplement documentation)
*   |--------------|
*   |              |<------- 32bits -  interrupt state flag
*   |--------------|
*   |              |<------- 32bits - virtual core to be loaded context's
*   |--------------|                  interrupt state
*   |              |
*   |              |<------- 64bits - pointer to VMMU configuration
*   |--------------|
*   |              |<------- 64bits - pointer to additional VMMU
*   |              |                  configuration (reserved for enhancement)
*   |--------------|
*   |              |<------- 64bits - VIOAPIC information header (internal use only)
*   |              |
*   |--------------|<------- 32bits - Pending interrupt vector number
*   |______________|
*\ce
*
* SYNOPSIS
*
* Virtual core's control C data structure type definition
*\cs
* typedef struct vbControl {
*
*    /@
*     @ Some architecture like Intel with hardware virtualization support don't
*     @ make use vbControlRegs.
*     @/
*
*#ifdef  _WRHV_ARCH_HAS_CTRL_REGS
*    VB_ALIGN_FIELD_64 (VB_ARCH_CONTROL_REGS  * vbControlRegs, pad1);
*#endif
*
*   /@  0: -1 => Disable all interrupts					@/
*
*    uint32_t	intDisable;
*
*   /@
*    @ future interrupt state of a context to be loaded in
*    @ vbControl->intDisable after a context switch
*    @/
*
*    uint32_t	newIntDisable;
*
*   /@  2: VMMU 0 table for context switch				@/
*
*    VB_ALIGN_FIELD_64 (void *vmmu0, pad2);
*
*   /@  3: VMMU 1 table for context switch				@/
*
*    VB_ALIGN_FIELD_64 (void *vmmu1, pad3);
*
*   /@ Virtual I/O APIC							@/
*
*    VB_ALIGN_FIELD_64 (uint32_t    vIoapicRegisters[VB_VIOAPIC_SIZE], pad4);
*
*   /@ actual virtual interrupt pending					@/
*
*    uint32_t	intPending;
*
*   } VB_CONTROL;
*\ce
*
* RETURNS: N/A
*
* SEE ALSO: VB_ARCH_CONTROL_REGS, architecture supplement document
*
* INTERNAL
* warning!!!!!!!
* 1. Any modification of this structure field should be reflected in the
* description.
* 2. Make sure the vbControlRegs, vIoapicRegisters are changed to pointers in
*     the code
*\COMMAND
*\NOMANUAL
*/

typedef struct vbControl {

#ifdef  _WRHV_ARCH_HAS_CTRL_REGS
    VB_ARCH_CONTROL_REGS  vbControlRegs;
#endif

    uint32_t	intDisable;	/*  0: -1 => Disable all interrupts */
    uint32_t	newIntDisable;	/*  1: New value for vbControl->intDisable */

				/*  2: VMMU 0 table for context switch */
    VB_ALIGN_FIELD_64 (VOID_PTR vmmu0, pad1);

				/*  3: VMMU 1 table for context switch */
    VB_ALIGN_FIELD_64 (VOID_PTR vmmu1, pad2);

    uint32_t	intLevelDisable;/* interrupt level enabling */

    /* Virtual I/O APIC */

    VB_ALIGN_FIELD_64 (VOID_PTR vIoapic, pad3);

    /* actual virtual interrupt pending */

    uint32_t	intPending;

} VB_CONTROL;


/*******************************************************************************
*
* VB_STATUS - Virtual board's core status structure
*
* VB_STATUS is a C data type structure that provides the definition of an area
* where the state of a given core is posted by Hypervisor before a virtual core is
* scheduled to run. The fields of this structure are architecture agnostic.
* A pointer is provided to accomodate anything that is specific to the underlying
* hardware. The architecture specific structure is included only if
* _WRHV_ARCH_HAS_STATUS_REGS flag is defined. The data type  VB_STATUS_ARCH_REGS
* holding the architecture dependent registers is defined by a file pulled
* vbi/vbiArch.h at compile type according to CPU value.
* The definition of VB_ARCH_STATUS_REGS can be found in the architecture
* supplement documentation.
* The purpose of this structure is to inform a virtual core at runtime the
* status of a core's time variant data such as:
*\ms
*\m -
* Interrupts state
*\ms
*\m *
* current interrupt state
*\m *
* previous interrupt state if the core is in an ISR context
*\m *
* The pending vector number if any
*\me
*\m -
* A free running clock timestamp
*\m -
* Virtual core elapsed timer ticks
*\m -
* Current VMMU configuration
*\me
*
* SYNOPSIS
*
* Control structure graphical illustration
*\cs
*        _______________
*       |		|
*       |		|<-------64bits - VB_ARCH_STATUS_REGS; arch dependent
*       |		|		structure pointer
*       |---------------|
*       |		|<-------32bits - intPending; pending vector number
*       |---------------|
*       |///////////////|<-------32bits - Reserved for future enhencements
*       |---------------|
*       |		|<-------64bits - timeStamp; free running clock ticks
*       |		|
*       |---------------|
*       |		|<-------32bits - oldIntDisable; interrupt state before
*       |---------------|		   an interrupt was injected
*       |		|<-------32bits -
*       |---------------|
*       |		|
*       |		|<-------64bits - vmmu0; current VMMU configuration
*       |---------------|
*       |		|<-------64bits - vmmu1; reserved for future use
*       |		|
*       |---------------|
*       |		|<-------64bits - tickCount; elapsed virtual core ticks
*       |---------------|
*
*\ce
*
* Virtual core's status C data structure type definition
*
*\cs
* VB_STATUS structure definition
*
* typedef struct vbStatus {
*    /@
*     @ Some architecture like Intel with hardware virtualization support don't
*     @ make use vbStatusRegs
*     @/
*
* #ifdef _WRHV_ARCH_HAS_STATUS_REGS
*    VB_ALIGN_FIELD_64 (VB_ARCH_STATUS_REGS  vbStatusRegs, pad1);
* #endif
*
*    /@ Bits indicating which interrupts are pending			    @/
*
*    uint64_t	intPendingType;
*
*    /@ reserved field for future use, required for timeStamp alignment	    @/
*
*    uint32_t	reserved1;
*
*    /@ Timestamp when last interrupt was delivered			    @/
*
*    VB_TIMESTAMP timeStamp;
*
*    /@
*     @ Interrupt registers when the hypervisor interrupts a virtual board,
*     @ it saves the following information here for use by the virtual board.
*     @/
*
*    /@ value of control->intDisable at time of the interrupt.
*     @ control->intDisable is set to -1 by WRHV at the time of delivery of
*     @ the interrupt
*     @/
*
*    uint32_t	oldIntDisable;
*
*    /@ VMMU tables which were active when an MMU exception occurred	    @/
*
*    VB_ALIGN_FIELD_64 (void *vmmu0, pad2);
*    VB_ALIGN_FIELD_64 (void *vmmu1, pad3);
*
*    /@ VB wall clock time expressed in the VB clock frequency  @/
*
*    uint64_t tickCount;
*
* } VB_STATUS;
*\ce
*
* RETURNS: N/A
*
* SEE ALSO: VB_ARCH_CONTROL_REGS, architecture supplement document
* INTERNAL
* Make sure that intPendingType modification is reflected in the code
*
*\COMMAND
*\NOMANUAL
*/

typedef struct vbStatus {

#ifdef _WRHV_ARCH_HAS_STATUS_REGS
    VB_ARCH_STATUS_REGS  vbStatusRegs;
#endif

    /* Bits indicating which interrupts are pending */

    uint32_t	intPendingType;

    /* reserved field for future use, required for timeStamp alignment */

    uint32_t	reserved1;

    /* Timestamp when last interrupt was delivered */

    VB_TIMESTAMP timeStamp;

    /* Interrupt registers
     *
     * When the hypervisor interrupts a virtual board, it saves the following
     * information here for use by the virtual board.
     */

    /* value of control->intDisable at time of the interrupt.
     * control->intDisable is set to -1 by WRHV at the time of delivery of
     * the interrupt
     */

    uint32_t	oldIntDisable;

    /* Padding to naturally align the following pointer fields */

    uint32_t	reserved2;

    /* VMMU tables which were active when an MMU exception occurred */

    VB_ALIGN_FIELD_64 (VOID_PTR vmmu0, pad1);
    VB_ALIGN_FIELD_64 (VOID_PTR vmmu1, pad2);

    /* Virtual Board clock tick count */

    uint64_t tickCount;

    /* number of times this core has booted */

    uint32_t	 bootCount;

    /* initial program load flag */

    uint32_t	 ipl;

    /* The simulatror flag  */

    uint32_t	 sim;

} VB_STATUS;

/*
 * ----------------------- Virtual BOARD STATUS PAGE -----------------------
 *
 * Read only page used to provide static configuration to the Virtual Board
 *
 */

#define ALIGN_DEV_INFO_SIZE	8 	/* vbDevInfo, vbDevIntInfo, 
                                         * vbDevRegSetInfo, etc, will
                                         * all start at an 8-byte 
                                         * alignment */

/* Configuration information for devices */

typedef struct vbDevInfo
{
    VB_WRHV_NAME deviceName;		/* the name of the GI Thread */
    VB_WRHV_NAME deviceTemplate;	/* the name of template */
    uint16_t     deviceClass;		/* class: serial, network, block */
    uint16_t     pad;		        /* pad to pack */
    uint32_t     deviceType;    	/* ADD or Emulated or Passthrough */
    uint32_t     numInterrupts; 	/* Number of Interrupts */
    uint32_t     numRegSets;    	/* Number of Register Sets */
    uint32_t     numDeviceTreeSources;	/* Number of DeviceTreeSources */
    uint32_t	 intInfoOffset; 	/* offset to Interrupt Info */
    uint32_t	 regSetInfoOffset; 	/* offset to Register Set Info */
    uint32_t	 deviceTreeSourceInfoOffset; /* offset to Device Tree Source Info */
} VB_DEV_INFO;

/* Configuration information for devices - Interrupts */

typedef struct vbDevIntInfo 
{
    uint32_t 		indexDevice;	/* which device does this belong to */
    VB_WRHV_NAME   	intName;   	/* Interrupt Name */
    VB_WRHV_NAME   	intType;   	/* Interrupt Name */
    vbiVector_t 	intNum;    	/* Interrupt Number */
    uint32_t 		intSense;  	/* level or edge */
    uint32_t 		intPolarity;  	/* active high or low */
} VB_DEV_INT_INFO;     

/* Configuration information for devices - Register Sets */

typedef struct vbDevRegSetInfo
{
    uint32_t 		indexDevice;	/* which device does this belong to */
    VB_WRHV_NAME   	regSetName;   	/* RegSet Name */
    uint32_t 		pad;	        /* pad to pack */
    uint64_t 		regSetAddress;	/* Guest Physical Address */
    uint64_t 		regSetLength;	/* Length */
    uint64_t 		regSetAlignment;/* Alignment of Physical Address */
    uint64_t 		regSetType;	/* IO, MEM, PCI memory */
} VB_DEV_REGSET_INFO;     

/* Configuration information for devices - DeviceTreeSource */

typedef struct vbDevDeviceTreeSourceInfo 
{
    uint32_t 		indexDevice;	/* which device does this belong to */
    VB_WRHV_NAME   	deviceTreeSourceName;  	/* DTS Name */
} VB_DEV_DEVICETREESOURCE_INFO;     
    
/* Configuration information for interrupts */

typedef struct vbIntInfo {
    VB_WRHV_NAME intName;	/* the name of this interrupt */
    uint16_t	 intDirection;	/* interrupt direction: INPUT_INT, OUTPUT_INT */
    uint16_t	 intNumber;	/* the local VB interrupt number */
    uint32_t	 intCore;	/* the receiving core for this incomming int */
} VB_INT_INFO;

/* Information about a shared memory region */

typedef struct vbSmInfo {
    VB_WRHV_NAME name;		/* the name of the shared memory region */
				/* the vbphysical address of the region */
    VB_ALIGN_FIELD_64 (VOID_PTR addr, pad1);
    uint32_t	 length;	/* the length in bytes of the region */
    uint32_t	 attr;		/* the MMU attributes of the region */
    uint32_t	 type;		/* shared memory type field */
				/* id's of connected boards */
    VB_ALIGN_FIELD_64 (VOID_PTR boardIds, pad2);
} VB_SM_INFO;

/* Information for the memory map info */

typedef struct vbMemInfo {
    VB_WRHV_NAME name;		/* the name of the memory region */
				/* the vbphysical address of the region */
    VB_ALIGN_FIELD_64 (VOID_PTR addr, pad1);
    uint32_t	 length;	/* the length in bytes of the region */
    uint32_t	 attr;		/* the MMU attributes of the region */
    VB_WRHV_NAME type;		/* the type of the region */
} VB_MEM_INFO;


/*
 * Fixed information about the configuration of a Virtual Board as seen by
 * the Virtual Board itself.  The address of this structure is passed as the
 * first parameter to the virtual board when it is started at its entry point.
 */
#define ACCESS_PRIV_READ_ONLY  0
#define ACCESS_PRIV_READ_WRITE 1
#define MAX_VB_CONFIG_REGIONS 16

typedef struct
    {
    uint32_t address;
    uint32_t size;
    uint32_t accessPriv;
    } CONFIG_PAGE_MAP;

typedef struct vbConfig {

    /*
     *  structure versioning information
     *  --------------------------------
     */

    uint32_t major;	/* major revision number */
    uint32_t minor;	/* minor revision number */
    uint32_t maint;	/* maintenance revision number */
    uint32_t pad;

    /*
     *  pointers to secondary configuration structures
     *  ----------------------------------------------
     */

    /* read-only status information */

    VB_ALIGN_FIELD_64 (VB_STATUS * vbStatus, pad1);

    /* read-write control information */

    VB_ALIGN_FIELD_64 (VB_CONTROL * vbControl, pad2);

    /* shared memory information (memory map) */

    VB_ALIGN_FIELD_64 (VB_SM_INFO * sharedMemoryRegionsConfigAddress, pad3);

    /* memory regions information (memory map) */

    VB_ALIGN_FIELD_64 (VB_MEM_INFO * memoryRegionsConfigAddress, pad4);

    /* information about incoming and outgoing interrupt connections */

    VB_ALIGN_FIELD_64 (VB_INT_INFO * interruptConfiguration, pad5);

    /*
     *  general board specific configuration information
     *  ------------------------------------------------
     */

    uint32_t	 pid;		 /* hypervisor context id */
    vbiVb_t	 boardID;	 /* board ID from the XML configuration */

    int32_t	 supervisoryMode;/* board is running in privileged mode */

    VB_WRHV_NAME boardName;	 /* the name of this board */
    uint32_t	 boardType;	 /* the type of this board */
    uint32_t	 bootCount;	 /* number of times this core has booted */

				 /* entry point for this VB */
    VB_ALIGN_FIELD_64 (VOID_PTR resetPC, pad6);

    /*
     *  virtual core specific information
     *  ---------------------------------
     */

    uint32_t  coreId;		  /* virtual core cpu id */
    uint32_t  numCores;		  /* number of virtual cores */
    uint32_t  corePrivateSize;	  /* size of core private memory */
				  /* pointer to core private memory */
    VB_ALIGN_FIELD_64 (VOID_PTR corePrivate, pad8);

    /*
     *  main memory configuration settings
     *  ----------------------------------
     */

    uint32_t  physicalMemorySize; /* the vbPhysical size of RAM */
    uint32_t  memoryAliasAddress; /* address to which memory is aliased */
    uint32_t  memoryAliasSize;	  /* size of aliases memory */
    uint32_t  numMem;		  /* number of memory regions */

    /*
     *  shared memory configuration settings
     *  ------------------------------------
     */

    /* number of shared memory regions */

    uint32_t  numSm;

    /* shared memory state information */

    VB_ALIGN_FIELD_64 (VOID_PTR sharedMemoryRegionsStateAddress, pad7);

    /*
     *  clock and interrupt configuration
     *  ---------------------------------
     */

    /* the frequency of the periodic tick interrupt */

    uint32_t  tickTimerFrequency;	/* ticks per second */

    /* the frequency of the timestamp */

    uint32_t  timeStampFrequency;	/* ticks per second */

    /* number of interrupts connected to this board */

    uint32_t  numInts;

    /*
     *  misc settings
     *  -------------
     */

    /* OS specific boot line */

    char      bootLine[VB_MAX_BOOTLINE_LENGTH];

    /*
     * spare 32-bit fields for future use
     * must keep the 64 bit fields after aligned
     */

    uint32_t	spare32[17];

    /* spare 64-bit fields for future use */

    uint64_t	spare64[15];

    uint32_t	pad12;

    /* direct function call interface table */

#if defined (_WRHV_ARCH_HAS_VB_SYSTBL)
    VB_ALIGN_FIELD_64 (VB_SYSCALL *vbSyscallTable, pad9);
    VB_ALIGN_FIELD_64 (VB_SYSCALL_STUB2 *vbSyscallStub2, pad10);
#endif

    /* information about devices */

    VB_ALIGN_FIELD_64 (VB_DEV_INFO * deviceConfiguration, pad11);

    /* number of devices connected to this board */

    uint32_t  numDevices;

    /* provide mappings for all configuration pages */

    CONFIG_PAGE_MAP   configPageMap[MAX_VB_CONFIG_REGIONS];
    uint32_t  configPageNum;

    /* guest type */

    uint32_t	guestOS;

    uint64_t    physicalMemorySize64;   /* physical size of RAM 64 bit */
} VB_CONFIG;

#ifndef __INCvxWorksh
extern int kprintf (const char *, ...);
#else
extern int printf (const char *, ...);
#endif

typedef struct {
     VB_WRHV_NAME       Name;			       /*  64 bytes */
     uint32_t	        Bus;			       /*   4 bytes */
     uint32_t	        Device;			       /*   4 bytes */
     uint32_t	        Function;		       /*   4 bytes */
     uint32_t	        WriteEnable;		       /*   4 bytes */
} vbPciDevice_t;

typedef struct {
    uint64_t	        RamAliasSize;			/*   8 bytes */
    uint64_t	        RamAliasAddr;		        /*   8 bytes */
    uint64_t	        RamSize;			/*   8 bytes */
    uint64_t	        SystemRamSize;		        /*   8 bytes */
    uint64_t	        BackgroundModeStartAddr;	/*   8 bytes */
    uint32_t	        EnableVmmuOnException;	        /*   4 bytes */
    uint32_t	        TickTimerFrequency;		/*   4 bytes */
    uint32_t	        BoardConfig;			/*   4 bytes */
    VB_WRHV_NAME        Name;				/*  64 bytes */
    char                BootLine[VB_MAX_BOOTLINE_LENGTH];/* 256 bytes*/
    int32_t             PassFaults;			/*   4 bytes */
    int32_t             TrapIoFault;			/*   4 bytes */
    int32_t             TraceIoFault;			/*   4 bytes */
    uint32_t            Cpu;				/*   4 bytes */
    int32_t             Preload;			/*   4 bytes */
    int32_t             Priority;			/*   4 bytes */
    uint32_t            SystemCallAccessRights;	        /*   4 bytes */
    VB_WRHV_NAME        BoardType;			/*  64 bytes */
    int32_t             SupervisoryMode;		/*   4 bytes */
    uint32_t            Cores;				/*   4 bytes */
    uint32_t            GuestOS;			/*   4 bytes */
    uint32_t            VMSize;			        /*   4 bytes */
    uint32_t            BackgroundModeEnabled;	        /*   4 bytes */
    uint32_t            NumOfGuestDevices;              /*   4 bytes */
    uint32_t            NumPciDevices;			/*   4 bytes*/
    uint32_t            Reserved[32];  /* reserved for later use - 128 bytes */
} vbSimpleInformation_t;
    
    
typedef struct
    {
    vbSimpleInformation_t vbSimpleInformation;
    VB_ALIGN_FIELD_64(uint32_t * pCpuList, pad1);           /* already aligned - 8 bytes*/
    VB_ALIGN_FIELD_64(uint32_t * pCpuPriorityList, pad2);   /* 8 bytes */
    VB_ALIGN_FIELD_64(VB_WRHV_NAME * pDeviceList, pad3);    /* 8 bytes */
    VB_ALIGN_FIELD_64(vbPciDevice_t * pPciDevices, pad4);   /* 8 bytes */
    uint32_t    Reserved[32];    /* reserved for later use - 128 bytes */
    } vbInformation_t;	


#endif /*_ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif  /* __INCvbInterfaceh */
