/* wrhvHypercalls.h - hypervisor system calls */

/*
 * Copyright (c) 2007-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03d,02aug12,c_t  Sync with HV 2.0 Jul03rd DVD
03f,17feb12,c_t  Sync with HV 2.0 Jan27th DVD
03e,25aug11,c_t  Sync with HV 2.0
03d,18apr11,wqi  Updated for e300 guest OS.
03c,04apr11,jlv  Sync with HV 1.3 01-Apr-11(WIND00265419)
03b,08feb11,jlv  Sync with HV 1.3 04-Feb-11 DVD
03a,24may10,jl   Sync with HV 1.2 25-May-10
02z,29apr10,pad  Moved extern C statement after include statements.
02y,03mar10,rgo  sync-up with hv1.2 3/3/10
02x,21jan10,rgo  assign a HV system-call to vbiVbRemote 
02w,23oct09,jl   Sync with HV 1.1 30-Oct-09 DVD
02v,22sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
02u,12aug09,dtr  Add defines for additional arg to vbiHyIoctl.
02t,13jul09,dbt  stop using long for VTLB VBI system calls
02s,16jul09,mmi  change NO_RESET to RESET and NO_DOWNLOAD to DOWNLOAD
02r,13jul09,mmi  fix reset flag reset
02q,13jul09,mmi  add VBI_VBMGMT_RESET_DOWNLOAD
02p,06jul09,mmi  add vb managment syscall numbers
02o,02jul09,mmi  update the interrupt sending options, fix textUpdate
		 fast syscall number
02n,23jun09,mmi  add VBI_VBMGM_RESTART
02m,10jun09,mmi  add cache text update fast system call
02l,29may09,mes  Fixed VBI_CTX_STATS to match HY_CTX_STATS
02k,27apr09,mpk  Supervisor Syscall Interface for Privileged Guest OS
02j,19mar09,mes  Fixed type of VBI_ERROR_CODE
02i,02feb09,mmi  add name service system call
02h,02mar09,mmi  fix header name define
02g,24feb09,mmi  decouple vbi definitions from internal data, add vbMgmt API
02f,19jan09,mmi  update msg API prototypes
02e,12jan09,dtr  Add driver ioctl calls, remove legacy interrupt defns.
02d,12dec08,md   rename header files
02c,05dec08,mes  Removed shelf macros, added vbMgmt macros
02b,01dec08,md   add VBI_IOAPICIOCTL_SEND options
02a,21nov08,md   remove port and ED&R syscalls
01z,20nov08,mmi  adtopt new naming convention
01y,31oct08,dbt  Added vdkVtlbMmuOp hypercall.
01x,16jun08,mmi  fix vdkBspIoctl prototype
01w,19may08,gws  add vIoapicIoctl
01v,18apr08,md   add extra arg to vdkHyioctl
01u,11apr08,md   add EOI ioctl
01t,06mar08,md   add debug shell ioctl
01s,06dec07,foo  update hw ints
01r,23nov07,foo  fix prototype, use basic types
01q,25oct07,foo  updated with new vdk functions
01p,27sep07,md   added exception profiling fields
01o,26sep07,md   added profiling statistics and stats ioctl
01n,10sep07,md   re-number hypervisor system calls
01m,21aug07,md   added VDK_SYS_ctx_load_vmmu
01l,05jul07,foo  added bspIoctl calls and defines
01k,04jun07,md   added ctxctl and mmu system calls
01j,17may07,ymz  added port syscall.
01i,28may07,foo  update vdkInt prototype
01h,18may07,md   add hypervisor ioctl
01g,20apr07,md   add vmmu system calls
01f,18apr07,md   renamed to vdk
01e,10apr07,md   replace kprintf syscall with kputs and kputc
01d,19mar07,foo  fix macro
01c,17mar07,foo  modify definitions to all start with HY
01b,15mar07,md   added interrupt system calls
01a,09mar07,md   written
*/

#ifndef __INCwrhvHypercallsh
#define __INCwrhvHypercallsh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wrhv/vbiVersion.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 *
 *
 * System call number encoding:
 *
 * 31                                                                        0
 *
 *  |               |               |        |               |               |
 *  +---------------+---------------+        +---------------+---------------+
 *  | | | | | | | | | | | | | | | | | ...... | | | | | | | | | | | | | | | | |
 *  +---------------+---------------+        +---------------+---------------+
 *   ^ ^ ^         ^ ^ ^                                                    ^
 *   | | \--------/  | \----------------------------------------------------/
 *   | |      |      |                         |
 *   | |      |      |                         |
 *   | |      |      |                         +-- System call number
 *   | |      |      |
 *   | |      |      +-- Size override
 *   | |      |
 *   | |      +-- Fast hypervisor system call number
 *   | |
 *   | +--------- Hypervisor system call
 *   |
 *   +----------- Fast hypervisor system call
 *
 *
 *
 *
 */

/* fast system call numbers handled by assembler code */

#define	HY_FAST_SYSCALL_MASK	0x3f000000
#define	HY_FAST_SYSCALL_SHIFT	24
#define	HY_FAST_SYSCALL_BIT	0x80000000
#define	HY_FAST_SYSCALL(x)	\
    ((((x) << HY_FAST_SYSCALL_SHIFT) & HY_FAST_SYSCALL_MASK) | \
     HY_FAST_SYSCALL_BIT)

/* C driven system calls */

#define	HY_SYSCALL_MASK		0x007fffff
#define	HY_SYSCALL_SHIFT	0
#define	HY_SYSCALL_BIT		0x40000000
#define	HY_SYSCALL(x)	\
    ((((x) << HY_SYSCALL_SHIFT) & HY_SYSCALL_MASK) | HY_SYSCALL_BIT)

#define HY_SIZE_OVERRIDE	0x00800000

/* fast system calls */

#define	VBI_SYS_tlb_flush	HY_FAST_SYSCALL(1) /* TLB flush			*/
#define	VBI_SYS_icache_flush	HY_FAST_SYSCALL(2) /* instruction cache flush	*/
#define	VBI_SYS_dcache_flush	HY_FAST_SYSCALL(3) /* data cache flush		*/
#define	VBI_SYS_ctx_load	HY_FAST_SYSCALL(4) /* context load		*/
#define	VBI_SYS_int_enable	HY_FAST_SYSCALL(5) /* int enable		*/
#define	VBI_SYS_cache_text_update		    \
				HY_FAST_SYSCALL(6) /* cache text update	        */
#define	VBI_SYS_pic_EOI         HY_FAST_SYSCALL(7) /* mpic EOI                */
#ifdef _WRS_CONFIG_HV_VER_1_3
#define	VBI_SYS_spefscr_update		    \
				HY_FAST_SYSCALL(8) /* update spefscr         */
#else  /* HV2.0 */
#define	VBI_SYS_fp_enable       HY_FAST_SYSCALL(8) /* Enable floating point  */
#define	VBI_SYS_trace_enable    HY_FAST_SYSCALL(9) /* Enable trace  */
#endif /* _WRS_CONFIG_HV_VER_1_3 */

/* hypervisor services */

#define	VBI_SYS_hyIoctl		 HY_SYSCALL(1)	/* hypervisor ioctl	     */
#define	VBI_SYS_vmContextCreate	 HY_SYSCALL(2)	/* context create	     */
#define	VBI_SYS_send		 HY_SYSCALL(3)	/* send a messages	     */
#define	VBI_SYS_receive		 HY_SYSCALL(4)	/* receive a messages	     */
#define	VBI_SYS_reply		 HY_SYSCALL(5)	/* reply to a messages	     */
#define	VBI_SYS_panic		 HY_SYSCALL(6)	/* halt the system	     */
#define	VBI_SYS_int 		 HY_SYSCALL(7)	/* deliver an interrupt	     */
#define	VBI_SYS_int_controller_done HY_SYSCALL(8)/* done interrupt processing*/
#define	VBI_SYS_ctxctl		 HY_SYSCALL(9)	/* context control operation */

/* VMMU operations */

#define	VBI_SYS_vmmu_config 	HY_SYSCALL(10)	/* configure the virtual MMU */
#define	VBI_SYS_vmmu_enable 	HY_SYSCALL(11)	/* enable the virtual MMU    */
#define	VBI_SYS_vmmu_disable 	HY_SYSCALL(12)	/* disable the virtual MMU   */
#define	VBI_SYS_vmmu_tlbload 	HY_SYSCALL(13)	/* load a VMMU TLB entry     */
#define	VBI_SYS_vmmu_tlbflush 	HY_SYSCALL(14)	/* flush a VMMU TLB entry    */

/* MMU operations */

#define	VBI_SYS_mmu_attr_set	HY_SYSCALL(16)	/* set physical memory attr  */
#define	VBI_SYS_mmu_attr_get	HY_SYSCALL(17)	/* get physical memory attr  */

/* BSP specific interface */

#define VBI_SYS_bspIoctl	HY_SYSCALL(18)	/* BSP specific opreration   */

/* vbMgmt services */

#define VBI_SYS_vbMgmt          HY_SYSCALL(20)	/* keep back compatibility */

/* Virtual IO APIC services */

#define VBI_SYS_vIoapicIoctl	HY_SYSCALL(21)

#define VBI_SYS_vbReset         HY_SYSCALL(22)	/* reset  vcores	*/
#define VBI_SYS_vbRestart       HY_SYSCALL(23)	/* restart vcores	*/
#define VBI_SYS_vbSuspend       HY_SYSCALL(24)	/* suspend vcores	*/
#define VBI_SYS_vbResume        HY_SYSCALL(25)  /* Resume vcores	*/
#define VBI_SYS_vbRemote        HY_SYSCALL(26)  /* Get info of board    */
#define VBI_SYS_schedControl	HY_SYSCALL(27)	/* scheduler control    */
#define VBI_SYS_port            HY_SYSCALL(28)  /* port send and receive */

/* Additional VMMU calls */
#define	VBI_SYS_vmmu_create 	HY_SYSCALL(30)	/* configure the virtual MMU */
#define	VBI_SYS_vmmu_delete 	HY_SYSCALL(31)	/* configure the virtual MMU */
#define	VBI_SYS_vmmu_maxAsid	HY_SYSCALL(32)	/* get max asid available    */

#define VBI_SYS_intRedirect     HY_SYSCALL(40)  /* vcores int redirect	*/

/* debug facilities */

#define	VBI_SYS_kputs		HY_SYSCALL(50)	/* print a string to the cons*/
#define	VBI_SYS_kputc		HY_SYSCALL(51)	/* print a char to the cons  */
#ifdef  _WRS_CONFIG_HV_VER_1_3
#define VBI_SYS_ps		HY_SYSCALL(52)	/* process status display    */
#endif  /* _WRS_CONFIG_HV_VER_1_3 */
#define VBI_SYS_dbgShStart	HY_SYSCALL(53)	/* start debug shell	     */

/* VTLB MMU operations */

#define VBI_SYS_vtlb_op		HY_SYSCALL(55)	/* VTLB operation */

/* Name services */

#define VBI_SYS_ns_op		HY_SYSCALL(60)	/* Name service operation */

/* remote board memory services */

#define VBI_SYS_memWrite_op	HY_SYSCALL(70)	/* memory write service operation */
#define VBI_SYS_memRead_op	HY_SYSCALL(71)	/* memory read service operation */

/* remote board memory services */

#define VBI_SYS_RegsWrite_op	HY_SYSCALL(72)	/* regs write service operation */
#define VBI_SYS_RegsRead_op	HY_SYSCALL(73)	/* regs service operation */

#define VBI_SYS_Pstate_set	HY_SYSCALL(74)  /* set core P state */
#define VBI_SYS_Cstate_set	HY_SYSCALL(75)  /* set core C state */


/* Dynamic VB create/delete and VB Migration */

#define VBI_SYS_vbCreate	    HY_SYSCALL(80) /* create virtual board   */
#define VBI_SYS_vbDelete	    HY_SYSCALL(81) /* delete virtual board   */
#define VBI_SYS_vbBoardSimpleConfigGet					     \
				    HY_SYSCALL(82) /* get board configuration*/
#define VBI_SYS_vbBoardConfigGet    HY_SYSCALL(83) /* get board configuration*/
#define VBI_SYS_vbMove		    HY_SYSCALL(84) /* move virtual board     */
#define VBI_SYS_vbPrioSet	    HY_SYSCALL(85) /* set VB priority	     */

/* Dynamic modification of VB */

#define VBI_SYS_vbSharedMemoryAlloc HY_SYSCALL(90) /* allocate shared memory */
#define VBI_SYS_vbSharedMemoryFree  HY_SYSCALL(91) /* free shared memory     */
#define VBI_SYS_vbRamAlloc	    HY_SYSCALL(92) /* allocate extra ram     */
#define VBI_SYS_vbRamFree	    HY_SYSCALL(93) /* free extra ram	     */

/* Max number of syscalls*/
#define VBI_SYS_max 		(101 + 1)

/* hyIoctl system call supported ioctl's */

#define	VBI_HYIOCTL_GETPID	 1	/* get context's pid		*/
#define	VBI_HYIOCTL_GETPRIORITY	 2	/* get context's priority	*/
#define	VBI_HYIOCTL_PSDISPLAY	 3	/* print context list on console*/
#define	VBI_HYIOCTL_EXCBASE	 4	/* exception vector base addr	*/
#define	VBI_HYIOCTL_INTBASE	 5	/* interrupt vector base addr	*/
#define	VBI_HYIOCTL_GETSTATS	 6	/* get context statistics	*/
#define	VBI_HYIOCTL_DEBUG_SHELL	 7	/* start the debug shell	*/
#define	VBI_HYIOCTL_PADDR	 9	/* translate to physical address*/
#define	VBI_HYIOCTL_EXCOFFSETS_SET  10  /* set exc vector offsets for the VB*/
#define	VBI_HYIOCTL_EXCOFFSETS_GET  11	/* get exc vector offsets for the VB*/
#define	VBI_HYIOCTL_GETCONFIG	    12	/* get config page address          */

/* vIoapicIoctl system call supported ioctl's */

#define	VBI_IOAPICIOCTL_UNMASK	    1	/* unmask v io apic interrupt src */
#define	VBI_IOAPICIOCTL_SEND	    2	/* inject a v io apic interrupt */
#define	VBI_IOAPICIOCTL_EOI	    3	/* end of interrupt acknowledge */
#define VBI_IOAPICIOCTL_VCORE_SEND  4	/* Send an irq to a core	*/
/* remove this after vbControl is working, we don't need a hypercall for it: */
#define	VBI_IOAPICIOCTL_MASK	 10	/* mask v io apic interrupt src */

/* VBI_IOAPICIOCTL_SEND options */

#define	VBI_IOAPICSEND_ALL	 0	/* send interrupt to all incl self */
#define	VBI_IOAPICSEND_OTHERS	 1	/* send interrupt to all except self */
#define	VBI_IOAPICSEND_SELF	 2	/* send interrupt to self only */
#define	VBI_IOAPICSEND_UNICAST	 3	/* send interrupt to a only one vb*/
#define	VBI_IOAPICSEND_NONE	 4	/* ignore this call	       */

/* sent interrupt to a virtual flags */

#define VBI_IOAPICSEND_VCORE_NONE 0	/* there no option available for now */

/* hyCtxctl system call supported operations */

#define	VBI_CTXCTL_IDLE	 	1	/* make current context idle	*/

/* remote VB syscall call supported operations */

#define VBI_VBREMOTE_BOARDCONFIG    1       /* get guest addr of VBCONFIG */
#define VBI_VBREMOTE_RAMSIZE        2       /* get memory size */

/* MMU protection attributes */

/* For backwards compatibility, these are preserved: */
#define	VBI_MMU_PROT_READ	0x00000001	/* read allowed    */
#define	VBI_MMU_PROT_WRITE	0x00000002	/* write allowed   */
#define	VBI_MMU_PROT_EXECUTE	0x00000004	/* execute allowed */

/* Newer vbiMemAttrSet/Get interface: */

#define	VBI_MMU_PROT_USER_READ	    0x00000001	/* user read		*/
#define	VBI_MMU_PROT_USER_WRITE	    0x00000002	/* user write		*/
#define	VBI_MMU_PROT_USER_EXECUTE   0x00000004	/* user execute		*/
#define	VBI_MMU_PROT_SUPV_READ	    0x00000008	/* supervisor read	*/
#define	VBI_MMU_PROT_SUPV_WRITE	    0x00000010	/* supervisor write	*/
#define	VBI_MMU_PROT_SUPV_EXECUTE   0x00000020	/* supervisor execute	*/

/* attributes passed to guest besides protection                        */

#define VBI_MMU_ATTR_GUEST_MEM      0x80000000  /* accessible by guest  */

/* ETSEC MDIO supported ioctl's */
#define VBI_BSPIOCTL_DRV_MDIO 1         /* mdio messages */

/* system clock frequency query */
#define VBI_BSPIOCTL_SYS_CLK  2  /* system clock frequency query */
#define	VBI_BSPIOCTL_CLK_FREQ 2	 /* Request system clk freq */

/* return physical cpu number given virtual number 
 * - UP should always be 0 
 * - SMP any vcore in the system 
 */
#define VBI_BSPIOCTL_VIRT_TO_PHYS_CPU_NUM 3

/* Get CPU Processor Version Register content */

#define	VBI_BSPIOCTL_PVR_GET	4

/* Get CPU System Version Register content */

#define	VBI_BSPIOCTL_SVR_GET	5

#define MDIO_READ	 1
#define MDIO_WRITE	 2
#define MDIO_INT_ENABLE  3
#define MDIO_INT_DISABLE 4

/* vbiHyIoctl for PADDR */
#define VBI_HYIOCTL_PADDR_DMA        0x0 /* Default used for DMA */
#define VBI_HYIOCTL_PADDR_PHYS       0x1 /* When absolute phys addr needed */

/* vbMgmt commands */
#define VBI_VBMGMT_ATTACH       1       /* Attach to VB for control */
#define VBI_VBMGMT_DETACH       2       /* Detech from VB */
#define VBI_VBMGMT_SUSPEND      3       /* Suspend/halt VB */
#define VBI_VBMGMT_RESUME       4       /* Resume/start a VB */
#define VBI_VBMGMT_RESET        5       /* Reset VB */
#define VBI_VBMGMT_RESTART      6       /* Restart a VB */

/* vbMgmt error codes */
#define VBI_ERROR_CODE              int32_t
#define VBI_ERR_GENERAL             -101   /* General error */
#define VBI_ERR_INVALID_ARG         -102   /* General error */

/* vbMgmt reset macros */
#define VBI_VBMGMT_RESET_NON_CORE0	    0x00000000     /* APs dont clear mem */
#define VBI_VBMGMT_RESET_DOWNLOAD	    0x00000001	/* reload ELF image */
#define VBI_VBMGMT_RESET_CLEAR		    0x00000002  /* clear memory */
#define VBI_VBMGMT_RESET_AND_START_CORE0    0x00000004

/* target vb options */

#define VBI_VB_CORES_ALL	(0x80000000)
#define VBI_VB_CORES_OTHERS	(0x40000000)

/* VTLB operation command and flags (intel-vt specific) */

#define	VBI_VTLB_OP_UPDATE_PMD		 1	/* 32-bit: L1 */
#define	VBI_VTLB_OP_UPDATE_PTE		 2	/* 32-bit: L2, 64-bit: L4 */
#define	VBI_VTLB_OP_DELETE_PMD		 3	/* 32-bit: L1 */
#define VBI_VTLB_OP_SET_PTE_AT		 4
#define	VBI_VTLB_OP_SET_PTE		 5
#define	VBI_VTLB_OP_FLUSH_OPS            6
#define	VBI_VTLB_OP_INIT                 7

#define	VBI_VTLB_OP_INIT64		10
#define	VBI_VTLB_OP_UPDATE_PML4		11	/* 64-bit: L1 */
#define	VBI_VTLB_OP_UPDATE_PDP		12	/* 64-bit: L2 */
#define	VBI_VTLB_OP_UPDATE_PDE		13	/* 64-bit: L3 */
#define	VBI_VTLB_OP_UPDATE_PTE		 2	/* 64-bit: L4 */
#define	VBI_VTLB_OP_DELETE_PML4		15	/* 64-bit: L1 */
#define	VBI_VTLB_OP_DELETE_PDP		16	/* 64-bit: L2 */
#define	VBI_VTLB_OP_DELETE_PDE		17	/* 64-bit: L3 */

/* VTLB macros */

#define	VBI_VTLB_OP_MAX_OPS		100
#define	VBI_VTLB_OP_CR3_CACHE_ENTRIES	4

/* VTLB optimization supported options */

#define	VBI_VTLB_OPTIM_ENABLED			1
#define	VBI_VTLB_CR3_CACHE_ENABLED		2
#define	VBI_VTLB_OPS_CACHE_ENABLED		4
#define	VBI_VTLB_DIRTY_BIT_SUPPORT_ENABLED	8

/* vbiNsOp system call supported operations */

#define	VBI_NS_REGISTER		1	/* register service name    */
#define	VBI_NS_UNREGISTER	2	/* unregister service name  */
#define	VBI_NS_LOOKUP_OLD	3	/* look up service name		  */
#define	VBI_NS_LOOKUP	        4	/* look up service name w/options */

#ifndef	_ASMLANGUAGE

/* statistics structure returned by VBI_HYIOCTL_GETSTATS ioctl */

#ifdef _WRS_CONFIG_HV_VER_1_3
typedef struct {
    unsigned long ctx_type;          /* type of context (user, supv, etc) */
    unsigned long switchin;          /* number of times switched in       */
    unsigned long pended;            /* number of times in pend state     */
    unsigned long tsCtxSwitchOutH;   /* timestamp: context switch (high)  */
    unsigned long tsCtxSwitchOutL;   /* timestamp: context switch (low)   */
    unsigned long tsCtxSwitchInH;    /* timestamp: context switch (high)  */
    unsigned long tsCtxSwitchInL;    /* timestamp: context switch (low)   */
    unsigned long tsCtxExcInH;	   /* timestamp: exception entry (high) */
    unsigned long tsCtxExcInL;	   /* timestamp: exception entry (low)  */
    unsigned long reset;            /* number of times context reset */
} VBI_CTX_STATS;
#else /* 2.0 changed to always 32bit */
typedef struct {
    uint32_t ctx_type;          /* type of context (user, supv, etc) */
    uint32_t switchin;          /* number of times switched in       */
    uint32_t pended;            /* number of times in pend state     */
    uint32_t tsCtxSwitchOutH;   /* timestamp: context switch (high)  */
    uint32_t tsCtxSwitchOutL;   /* timestamp: context switch (low)   */
    uint32_t tsCtxSwitchInH;    /* timestamp: context switch (high)  */
    uint32_t tsCtxSwitchInL;    /* timestamp: context switch (low)   */
    uint32_t tsCtxExcInH;	   /* timestamp: exception entry (high) */
    uint32_t tsCtxExcInL;	   /* timestamp: exception entry (low)  */
    uint32_t reset;            /* number of times context reset */
} VBI_CTX_STATS;
#endif /* _WRS_CONFIG_HV_VER_1_3 */

/* VTLB operation structures (x86 specific) */

typedef struct vbi_vtlb_op		/* VTLB operation */
    {
    uint32_t		op;		/* VTLB operation id */
    uint32_t		arg1;		/* VTLB operation arg 1 */
    uint32_t		arg2;		/* VTLB operation arg 2 */
    uint32_t		arg3;		/* VTLB operation arg 3 */
    } VBI_VTLB_OP;

typedef struct vbi_vtlb_cr3_cache
    {
    uint32_t		guest_cr3;	/* Guest CR3 register */
    uint32_t		host_cr3;	/* Host CR3 register */
    } VBI_VTLB_CR3_CACHE;
    
typedef struct vbi_vtlb_control
    {
    uint32_t		size;		/* VTLB Control structure size */
    uint32_t		mode;		/* VTLB module */
    uint32_t		vtlb_ops_ix;	/* VTLB operation index */
    VBI_VTLB_OP		vtlb_ops[VBI_VTLB_OP_MAX_OPS];	/* VTLB ops array */
    uint32_t		cr3_cache_ix;	/* CR3 cache index */
    VBI_VTLB_CR3_CACHE	cr3_cache[VBI_VTLB_OP_CR3_CACHE_ENTRIES]; /* cr3 cache*/
    } VBI_VTLB_CONTROL;			/* VBI VTLB control */

/* VTLB operation structures (x86 specific, 64-bit version) */

typedef struct vbi_vtlb_op64		/* VTLB operation */
    {
    uint32_t		op;		/* VTLB operation id */
    uint64_t		arg1;		/* VTLB operation arg 1 */
    uint64_t		arg2;		/* VTLB operation arg 2 */
    uint64_t		arg3;		/* VTLB operation arg 3 */
    } VBI_VTLB_OP64;

typedef struct vbi_vtlb_cr3_cache64
    {
    uint64_t		guest_cr3;	/* Guest CR3 register */
    uint64_t		host_cr3;	/* Host CR3 register */
    } VBI_VTLB_CR3_CACHE64;
    
typedef struct vbi_vtlb_control64
    {
    uint32_t		 size;		/* VTLB Control structure size */
    uint32_t		 mode;		/* VTLB module */
    uint32_t		 vtlb_ops_ix;	/* VTLB operation index */
					/* VTLB ops array */
    VBI_VTLB_OP64	 vtlb_ops[VBI_VTLB_OP_MAX_OPS];
    uint32_t		 cr3_cache_ix;	/* CR3 cache and index */
    VBI_VTLB_CR3_CACHE64 cr3_cache[VBI_VTLB_OP_CR3_CACHE_ENTRIES];
    } VBI_VTLB_CONTROL64;		/* VBI VTLB control */

/*
 * Control structure used by vbiVbMgmt for commands memory read, memory write, 
 *  register read, and register write.
 */

typedef struct vbMgmtCtl 
    {
    union 
	{
	struct 
	    {
	    uint32_t *pBuffer;  /* address of target context */
	    uint32_t *pAddress; /* address of calling context */
	    uint32_t size;	/* number of total bytes */
	    uint32_t width;	/* bus width in bytes */
	    } vbMgmtMem;
	struct 
	    {
	    uint32_t *pBuffer;  /* address of target context */
	    uint32_t regSet;	/* register set */
	    uint32_t reg;	/* macro to specify register */
	    uint32_t size;	/* number of total bytes */
	    } vbMgmtReg;
	} data;
    } VBMGMT_CTL;

typedef uint32_t VBMGMT_HANDLE;
typedef uint32_t VBI_NS_HANDLE;

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCwrhvHypercallsh */
