/* exc440x5.h - Layout of PPC440GX Machine Check Handler Save Area */

/* Copyright 2003-2004, 2009-2010 Wind River Systems, Inc. */
 
/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,09may09,jpb  Made mch_logger fully qualified function pointer.
01f,24sep04,dtr  Add new typedef. Part of SPR 100373.
01e,27apr04,cjj  Defined _PPC_440X5_MCH_LOG_USE_POLLING
01d,17nov03,pch  move definition of MCHSA_BASE_REG from ppc440.h
		 and adjust for Diab
01c,11nov03,pch  Update for Base 6 AIM MMU
01b,09jun03,pch  log recovered 440x5 Machine Check events.
01a,29may03,pch  initial release.
*/
 
#ifndef __INCexc440x5h
#define __INCexc440x5h
 

#include "arch/ppc/mmu440Lib.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * Register for the Machine Check handler to use as a base for addressing its
 * save area.  If 0, the save area is at address 0 and no base register is
 * needed.  If non-zero, the save area can be anywhere within the address
 * space mapped by the TLB entry that covers the vector table, and the Machine
 * Check handler must save the base register before use.  See exc440x5ALib.s
 * for details.
 *
 * XXX - This definition must be an integer specifying the register number
 * XXX - (or 0).  It may not be a symbolic register name, because the symbols
 * XXX - are not known to the preprocessor when using the Diab assembler or
 * XXX - either C compiler.
 */
#define	MCHSA_BASE_REG	10	/* p7 = r10 */

/*
 * This is a dedicated memory area used to save and restore registers during
 * Machine Check handling.  Using a memory save area reduces the need to use
 * processor core registers for saving state, without impairing reliability
 * or functionality:
 *
 * 1. The TLB entry which maps the Machine Check handler is presumed to be
 *    uncorrupted:  if not, the handler would fail attempting to fetch its
 *    first instruction.  No additional vulnerability arises from using the
 *    same TLB entry to access the save area.
 *
 * 2. If configured, data cache recovery is performed before the save area
 *    is accessed.  Alternatively, when configured for maximum robustness
 *    (with a TLB entry dedicated to the Machine Check handler and refreshed
 *    periodically), the dedicated TLB entry will be set to inhibit cacheing.
 *
 * 3. Use of a dedicated memory save area does not sacrifice reenterability,
 *    because this handler cannot be reenterable anyway:  critical state
 *    saved in MCSRR0 and MCSRR1 would be lost if a second Machine Check
 *    interrupt occurred during its execution.  Additional Machine Check
 *    interrupts are disabled when the hardware takes the first one, and they
 *    remain disabled until an rfmci is executed (after recovery is complete,
 *    or the Machine Check has been identified as non-recoverable).
 *
 * Since we must establish addressability to the save area anyway, we'll also
 * arrange for initialization to store copies of the static TLB entries there
 * for use in recovery from a TLB parity error.  The timer service routine
 * will also use this to periodically refresh TLB 0.
 */

/*
 * Defining _PPC_440X5_MCH_LOG_USE_POLLING during arch build will cause the
 * TLB 0 refresh function (part of the timer ISR) to poll for Machine Check
 * events which need to be logged.  Undefining it will cause the Machine Check
 * Handler to invoke the logger via the kernel workQ instead.  Using the workQ
 * improves overall efficiency by avoiding a special-purpose polling operation
 * at each timer tick, but introduces a dependency on the workQ implementation
 * (which may change in future kernel releases).
 */

/* 
 * The kernel work queue was modified therefore polling MUST be used
 * to check for Machine Check events until exc440x5ALib.s is modified 
 * iaw the work queue mods.
 */
#define	_PPC_440X5_MCH_LOG_USE_POLLING

/*
 * Defining _PPC_440X5_MCH_SUPPORT_CB_DCACHE during arch build will include
 * support for limited recovery of a copyback data cache.  If this support
 * is included in the arch build, the system can be configured to operate
 * in writethrough mode, providing recovery from all Dcache parity errors;
 * in copyback mode, providing recovery from only those Dcache parity errors
 * which occur in unmodified lines and therefore do not lose data; or with
 * no data cache recovery.  If this support is omitted from the arch build,
 * the Machine Check handler will be smaller but only the writethrough and
 * no-recovery configurations will be available.
 */
#undef	_PPC_440X5_MCH_SUPPORT_CB_DCACHE

#ifndef	_ASMLANGUAGE
typedef struct
    {
    UINT32 count;		/* Count of Machine Checks encountered */
    UINT32 mcsr;		/* MCSR value which precipitated this event */
    } PPC440X5_MCH_LOG_DATA;

typedef struct
    {
#if (MCHSA_BASE_REG != 0)
    UINT32	mch_base;	/* save base register */
#endif /* MCHSA_BASE_REG != 0 */
    UINT32	mch_rY;		/* save rY */
    UINT32	mch_cr;		/* save CR */
    UINT32	mch_mcsr;	/* MCSR (set for every MC) */
    UINT32	mch_count;	/* counter incremented for every MC */
    UINT32	mch_fatalMcsr;	/* MCSR (set only for non-recoverable MC) */
    UINT32	mch_fatalCount;	/* counter incremented for fatal MC */
    int (*mch_logger)(char *fmt, 
               _Vx_usr_arg_t arg1,  /* function to log recovered MC, or NULL */
               _Vx_usr_arg_t arg2, 
               _Vx_usr_arg_t arg3,
               _Vx_usr_arg_t arg4, 
               _Vx_usr_arg_t arg5,
               _Vx_usr_arg_t arg6);
#ifdef	_PPC_440X5_MCH_SUPPORT_CB_DCACHE
    UINT32	mch_dcrSel;	/* selector of failed Dcache line per dcread */
    UINT32	mch_dcdbtrl;	/* DCDBTRL from failed Dcache line */
    UINT32	mch_dcdbtrh;	/* DCDBTRH from failed Dcache line */
    UINT32	mch_dcvaddr;	/* virtual addr for failed Dcache line */
    UINT32	mch_dcsrrZ;	/* work space during Dcache recovery */
    UINT32	mch_dcPmask;	/* work space during Dcache recovery */
    UINT32	mch_reserved[2];  /* reserved for future use */
#else	/* _PPC_440X5_MCH_SUPPORT_CB_DCACHE != 0 */
    UINT32	mch_reserved[8];  /* reserved for future use */
#endif	/* _PPC_440X5_MCH_SUPPORT_CB_DCACHE */
/* following entries are used for TLB recovery */
    UINT32	mch_rZ;		/* save rZ */
    UINT32	mch_ctr;	/* save CTR */
    UINT32	mch_mmucr;	/* save MMUCR */
    UINT32	mch_rX;		/* save rX */
    UINT32	mch_numStat;	/* # of static TLB entries */
    UINT32	mch_cacheEnab;	/* Cache is enabled? */
    UINT32	mch_res_tlb[2];	/* reserved for future use */
/*
 * XXX - sizeof(PPC_MCHSA) should not be believed, because the dimension
 * of mch_statTlb[] is variable, set by sysStaticTlbDescNumEnt in the BSP.
 * Using 4 here since it is difficult to envision a configuration using
 * fewer static TLB entries, but the actual value will likely be around 25.
 */
    MMU440_PTE  mch_statTlb[4];   /* Copies of static TLB entries */
    } PPC_MCHSA;
#else	/* _ASMLANGUAGE */
# if (MCHSA_BASE_REG == 0)
# define MCHSA_PFX_SIZE		_EXC_OFF_MCHSA
# else	/* MCHSA_BASE_REG == 0 */
# define MCHSA_BR_OFFSET	0		     /* save base register */
# define MCHSA_PFX_SIZE		4		     /* sizeof(UINT32) */
# endif	/* MCHSA_BASE_REG == 0 */
#define	MCHSA_RY_OFFSET		(MCHSA_PFX_SIZE+0)   /* save rY */
#define	MCHSA_CR_OFFSET		(MCHSA_PFX_SIZE+4)   /* save CR */
#define	MCHSA_MCSR_OFFSET	(MCHSA_PFX_SIZE+8)   /* MCSR (every MC) */
#define	MCHSA_COUNT_OFFSET	(MCHSA_PFX_SIZE+12)  /* count of all MC */
#define	MCHSA_FATAL_MCSR_OFFSET	(MCHSA_PFX_SIZE+16)  /* MCSR (only fatal MC) */
#define	MCHSA_FATAL_COUNT_OFFSET (MCHSA_PFX_SIZE+20) /* count of fatal MC */
#define	MCHSA_LOGGER_OFFSET	(MCHSA_PFX_SIZE+24)  /* log function */
#ifdef	_PPC_440X5_MCH_SUPPORT_CB_DCACHE
#define	MCHSA_DCRSEL_OFFSET	(MCHSA_PFX_SIZE+28)  /* Dcache line selector */
#define	MCHSA_DCDBTRL_OFFSET	(MCHSA_PFX_SIZE+32)  /* DCDBTRL value */
#define	MCHSA_DCDBTRH_OFFSET	(MCHSA_PFX_SIZE+36)  /* DCDBTRH value */
#define	MCHSA_DCVADDR_OFFSET	(MCHSA_PFX_SIZE+40)  /* v addr for bad line */
#define	MCHSA_DCSRRZ_OFFSET	(MCHSA_PFX_SIZE+44)  /* work space */
#define	MCHSA_DCPMASK_OFFSET	(MCHSA_PFX_SIZE+48)  /* work space */
#endif	/* _PPC_440X5_MCH_SUPPORT_CB_DCACHE */
/* following entries are used for TLB recovery */
#define MCHSA_RZ_OFFSET		(MCHSA_PFX_SIZE+60)  /* save rZ */
#define MCHSA_CTR_OFFSET	(MCHSA_PFX_SIZE+64)  /* save CTR */
#define MCHSA_MMUCR_OFFSET	(MCHSA_PFX_SIZE+68)  /* save MMUCR */
#define MCHSA_RX_OFFSET		(MCHSA_PFX_SIZE+72)  /* save rX */
#define MCHSA_NUMSTAT_OFFSET	(MCHSA_PFX_SIZE+76)/* # of static TLB entries */
#define MCHSA_CACHENAB_OFFSET	(MCHSA_PFX_SIZE+80)  /* Cache is enabled? */
#define	MCHSA_STAT_TLB_OFFSET	(MCHSA_PFX_SIZE+92)  /* Static TLB entries */
			/* sizeof(MMU440_PTE) == 16 not 12! */
#define	MCHSA_FIXED_SIZE	MCHSA_STAT_TLB_OFFSET

#endif	/* _ASMLANGUAGE */
 
#ifdef __cplusplus
}
#endif
 
#endif /* __INCexc440x5h */
