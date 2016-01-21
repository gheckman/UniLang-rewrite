/* dbgPpcLib.h - header file for arch dependent portion of debugger */

/*
 * Copyright (c) 1995,1997-2002,2004,2005,2008,2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01w,02dec11,h_k  added pc member to DBG_REGS for PPC60x. (WIND00191292)
01v,03may11,syt  Added support for PPC465.
01u,15nov10,x_z  Added support for PPC476.
01t,29apr10,pad  Moved extern C statement after include statements.
01s,31mar09,dbt  Disable hardware breakpoint support for Hypervisor
		 Guest OS (WIND00161733).
01r,28mar05,dtr  Add support for 83xx and g2le
01q,25feb05,pch  handle PPC970 hardware breakpoints
01p,11feb04,elg  Add syscall instruction size macro.
01o,09feb04,elg  Remove DBG_SYSCALL_CHECK() definition.
01n,13jan04,elg  Add system call check support.
01o,02dec02,mil  Updated support for PPC85XX.
01n,02aug02,pcs  Add support for PPC85XX and make it the same as PPC603 for
                 the present.
01m,14mar02,pch  SPR 74270:  make 440 bh types consistent with 5xx/604/860
01l,23aug01,pch  Separate PPC440 from PPC405, cleanup.
01k,16aug01,pch  Add PPC440 support
01j,30oct00,s_m  separated PPC405 support from PPC403
01i,27oct00,s_m  updated for CPU == PPC405F
01h,25oct00,s_m  renamed PPC405 cpu types
01g,13jun00,alp  Added PPC405 Support
01f,19apr99,zl   added support for PPC509 and PPC555
01e,14oct98,elg  added hardware breakpoints for PPC603 and PPC604
01d,27jul98,elg  added hardware breakpoints
01c,24dec97,dbt  modified for new breakpoint scheme.
01b,24oct95,kdl	 added DBG_TRACE=FALSE for PPC403; added mod hist.
01a,14feb95,yao	 created.
*/

#ifndef __INCdbgPpcLibh
#define __INCdbgPpcLibh

#include "esf.h"
#include "reg.h"
#ifndef _ASMLANGUAGE
#include "dsmLib.h"
#endif	/* _ASMLANGUAGE */
#include "iv.h"
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	BREAK_ESF		ESFPPC		/* XXX */

#define DBG_BREAK_INST		0x7fe00008	/* trap 31, 0, 0 */
#define	DBG_SYSCALL_SIZE	(sizeof (INSTR) / sizeof (INSTR))

#ifndef	_PPC_MSR_SE
/*
 * Tell generic code it must simulate single-step using breakpoints.
 * This setting causes wdbDbgArchLib.c to export wdbDbgGetNpc(),
 * and to call wdbDbgTrap() instead of wdbDbgBreakpoint().
 *
 * XXX - PPC4xx have no SE bit in MSR, but do provide an "instruction
 * XXX - completion" debug event which has a similar effect and could
 * XXX - perhaps be used instead of doing this.
 */
#define DBG_NO_SINGLE_STEP	1	/* no trace support */
#endif 	/* _PPC_MSR_SE */

/* definition for HID1 register for 601 */
#define HID1_RUN_MODE(x)	(((x)&0x70000000)>>28)
#define HID1_RUN_NORM
#define HID1_RUN_UNDEF
#define HID1_RUN_UNDEF

/*
 * Set DBG_HARDWARE_BP for CPUs which support hardware breakpoints, and
 * define the breakpoint types.
 *
 * If defined, BRK_INST will be handled by generic code in wdb/wdbBpLib.c
 * and ostool/dbgTaskLib.c.  Other breakpoint types are CPU-specific, and
 * are used primarily in wdbDbgArchLib.c.  The help text and type-display
 * code in dbgArchLib.c should also match the definitions here.
 *
 * BRK_HARDMASK is used to extract the type from bp_flags.  It must be
 * at least large enough to cover all defined types, and must not overlap
 * with BRK_HARDWARE, nor with the flag bits (BP_INSTALLED, BP_HOST, BP_SO,
 * BP_STEP, BP_EVENT) defined in wdb/wdbDbgLib.h.
 */

#if 	(CPU == PPC509)   || (CPU == PPC555) || (CPU == PPC603) || \
        (CPU == PPCEC603) || (CPU == PPC604) || (CPU == PPC860)

#define DBG_HARDWARE_BP	1

#define BRK_INST	0x0	/* hardware instruction breakpoint */
#define BRK_RW		0x1	/* hardware data breakpoint for read or write */
#define BRK_READ	0x2	/* hardware data breakpoint for read */
#define BRK_WRITE	0x3	/* hardware data breakpoint for write */

#define DEFAULT_HW_BP	BRK_RW	/* default hardware breakpoint */

#define BRK_HARDWARE	0x10	/* hardware breakpoint bit */
#define BRK_HARDMASK	0x0f	/* hardware breakpoint mask */

#elif	(CPU == PPC403)

#define DBG_HARDWARE_BP	1

#define BRK_INST	0x0	/* hardware instruction breakpoint */
#define BRK_DATAW1	0x1	/* data breakpoint for write one byte */
#define BRK_DATAR1	0x2	/* data breakpoint for read one byte */
#define BRK_DATARW1	0x3	/* data breakpoint for read/write one byte */
#define BRK_DATAW2	0x5	/* data breakpoint for write 2 bytes */
#define BRK_DATAR2	0x6	/* data breakpoint for read 2 bytes */
#define BRK_DATARW2	0x7	/* data breakpoint for read/write 2 bytes */
#define BRK_DATAW4	0x9	/* data breakpoint for write 4 bytes */
#define BRK_DATAR4	0xA	/* data breakpoint for read 4 bytes */
#define BRK_DATARW4	0xB	/* data breakpoint for read/write 4 bytes */
#define BRK_DATAW16	0xD	/* data breakpoint for write 16 bytes */
#define BRK_DATAR16	0xE	/* data breakpoint for read 16 bytes */
#define BRK_DATARW16	0xF	/* data breakpoint for read/write 16 bytes */

#define DEFAULT_HW_BP	BRK_DATAW1	/* default hardware breakpoint */

#define BRK_HARDWARE	0x10	/* hardware breakpoint bit */
#define BRK_HARDMASK	0x0f	/* hardware breakpoint mask */

#elif	((CPU == PPC405) || (CPU == PPC405F))

#define DBG_HARDWARE_BP	1

#define BRK_INST	0x0	/* hardware instruction breakpoint */
#define BRK_DATAW1	0x1	/* data breakpoint for write one byte */
#define BRK_DATAR1	0x2	/* data breakpoint for read one byte */
#define BRK_DATARW1	0x3	/* data breakpoint for read/write one byte */
#define BRK_DATAW2	0x4	/* data breakpoint for write 2 bytes */
#define BRK_DATAR2	0x5	/* data breakpoint for read 2 bytes */
#define BRK_DATARW2	0x6	/* data breakpoint for read/write 2 bytes */
#define BRK_DATAW4	0x7	/* data breakpoint for write 4 bytes */
#define BRK_DATAR4	0x8	/* data breakpoint for read 4 bytes */
#define BRK_DATARW4	0x9	/* data breakpoint for read/write 4 bytes */
#define BRK_DATAW32	0xA	/* data breakpoint for write cache line size */
#define BRK_DATAR32	0xB	/* data breakpoint for read 16 bytes */
#define BRK_DATARW32	0xC	/* data breakpoint for read/write 16 bytes */

#define DEFAULT_HW_BP	BRK_DATAW1	/* default hardware breakpoint */

#define BRK_HARDWARE	0x10	/* hardware breakpoint bit */
#define BRK_HARDMASK	0x0f	/* hardware breakpoint mask */

#elif	((CPU == PPC440) || (CPU == PPC85XX) || (CPU == PPC476) || \
         (CPU == PPC465))

#define DBG_HARDWARE_BP	1

#define BRK_INST	0x0	/* hardware instruction breakpoint */
#define BRK_DATARW	0x1	/* data breakpoint for read/write */
#define BRK_DATAR	0x2	/* data breakpoint for read */
#define BRK_DATAW	0x3	/* data breakpoint for write */

/* XXX - 440 has 4 IAC registers (each pair usable as a range), and
 * XXX - 2 DAC registers (usable as a range); also DVC, BRT, ICMP,
 * XXX - IRPT, TRAP, and RET events.  How much of this to support?
 * XXX - ditto to 85XX, which doesn't have IAC3 and IAC4
 */

#define DEFAULT_HW_BP	BRK_DATAW	/* default hardware breakpoint */

#define BRK_HARDWARE	0x10	/* hardware breakpoint bit */
#define BRK_HARDMASK	0x0f	/* hardware breakpoint mask */

#endif	/* 509 555 603 EC603 604 860 : 403 : 405 405F : 440 85XX 476 */
/* End of hardware breakpoint type definitions */

/* No hardware breakpoint support in Hypervisor Guest OS for now */

#ifdef	_WRS_CONFIG_WRHV_GUEST
#undef	DBG_HARDWARE_BP
#define	DBG_HARDWARE_BP	0
#endif	/* _WRS_CONFIG_WRHV_GUEST */

#if	DBG_HARDWARE_BP

#ifndef _ASMLANGUAGE

/*
 * The DBG_REGS structure specifies the values to be
 * loaded into the hardware breakpoint registers.
 */
typedef struct
    {
#if	((CPU == PPC509) || (CPU == PPC555) || (CPU == PPC860))
    UINT32	cmpa;		/* comparator A value register */
    UINT32	cmpb;		/* comparator B value register */
    UINT32 	cmpc;		/* comparator C value register */
    UINT32	cmpd;		/* comparator D value register */
    UINT32	counta;		/* breakpoint counter value register A */
    UINT32	countb;		/* breakpoint counter value register B */
    UINT32	cmpe;		/* comparator E value register */
    UINT32	cmpf;		/* comparator F value register */
    UINT32	cmpg;		/* comparator G value register */
    UINT32	cmph;		/* comparator H value register */
    UINT32	lctrl1;		/* load/store support comparators control reg */
    UINT32	lctrl2;		/* load/store support AND-OR control register */
    UINT32	ictrl;		/* instruction support control register */
    UINT32	bar;		/* breakpoint address register */

#elif	CPU == PPC603 || CPU == PPCEC603 || CPU == PPC604 || CPU == PPC970
# if	CPU != PPC970
    UINT32	iabr;		/* instruction address breakpoint register */
# endif	/* !PPC_970 */
# if	CPU == PPC604 || CPU == PPC970
    UINT32	dabr;		/* data address breakpoint register */
    UINT32	dar;		/* data address register */
# endif	/* 604 || 970 */
#if (defined PPC_83xx  || defined (PPC_g2le))
    UINT32      iabr2;
    UINT32      ibcr;
    UINT32      dabr;
    UINT32      dabr2;
    UINT32      dbcr;
    UINT32	dar;		/* data address register */
#endif /* PPC_83xx |  PPC_g2le */
    UINT32	pc;		/* program counter at the time of HW break */
#elif	(CPU == PPC403)
    UINT32	dbcr;		/* debug control register */
    UINT32	dbsr;		/* debug status register */
    UINT32	dac1;		/* data address compare register 1 */
    UINT32	dac2;		/* data address compare register 2 */
    UINT32	iac1;		/* instruction address compare register 1 */
    UINT32	iac2;		/* instruction address compare register 2 */
    UINT32	msr;		/* machine state register */
#elif   ((CPU == PPC405) || (CPU == PPC405F) || (CPU == PPC440) || \
	 (CPU == PPC85XX) || (CPU == PPC476) || (CPU == PPC465))
    UINT32      dbcr0;          /* debug control register 0 */
    UINT32      dbcr1;          /* debug control register 1 */
# if	((CPU == PPC440) || (CPU == PPC85XX) || (CPU == PPC476) || (CPU == PPC465))
    UINT32      dbcr2;          /* debug control register 2 */
# endif	/* CPU == PPC440, PPC85XX, PPC476, PPC465 */
# if	((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
    UINT32      dbdr;           /* debug data register */
# endif	/* CPU == PPC440, PPC476 */
    UINT32      dbsr;           /* debug status  register */
    UINT32      dac1;           /* data address compare register 1 */
    UINT32      dac2;           /* data address compare register 2 */
    UINT32      iac1;           /* instruction address compare register 1 */
    UINT32      iac2;           /* instruction address compare register 2 */
# if	(CPU != PPC85XX)
    UINT32      iac3;           /* instruction address compare register 3 */
    UINT32      iac4;           /* instruction address compare register 4 */
# endif	 /* CPU != PPC85XX */
    UINT32      msr;            /* machine state register */
#endif	/* 509 555 860 : 603 EC603 604 : 403 : 405 405F 440 85XX 476*/

    } DBG_REGS;

/* Prototypes for hardware breakpoint register access functions */

# if	((CPU == PPC509) || (CPU == PPC555) || (CPU == PPC860))
extern	void	dbgCmpaSet (int value);
extern	void	dbgCmpbSet (int value);
extern	void	dbgCmpcSet (int value);
extern	void	dbgCmpdSet (int value);
extern	void	dbgCmpeSet (int value);
extern	void	dbgCmpfSet (int value);
extern	void	dbgLctrl1Set (int value);
extern	void	dbgLctrl2Set (int value);
extern	void	dbgIctrlSet (int value);
extern	int	dbgCmpaGet (void) ;
extern	int	dbgCmpbGet (void) ;
extern	int	dbgCmpcGet (void) ;
extern	int	dbgCmpdGet (void) ;
extern	int	dbgCmpeGet (void) ;
extern	int	dbgCmpfGet (void) ;
extern	int	dbgLctrl1Get (void) ;
extern	int	dbgLctrl2Get (void) ;
extern	int	dbgIctrlGet (void) ;

# elif	CPU == PPC603 || CPU == PPCEC603 || CPU == PPC604 || CPU == PPC970
#  if	CPU != PPC970
extern	void	wdbDbgIabrSet (int value);
extern	int	wdbDbgIabrGet (void);
#  endif  /* !PPC_970 */
#  if	CPU == PPC604 || CPU == PPC970
extern	void	wdbDbgDabrSet (int value);
extern	int	wdbDbgDabrGet (void);
extern	int	wdbDbgDarGet (void);
#  endif  /* 604 || 970 */
#  if (defined (PPC_83xx) || defined (PPC_g2le))
extern	int	wdbDbgDarGet (void);
extern	void	wdbDbgIabr2Set (int value);
extern	int	wdbDbgIabr2Get (void);
extern	void	wdbDbgIbcrSet (int value);
extern	int	wdbDbgIbcrGet (void);
extern	void	wdbDbgDabrSet (int value);
extern	int	wdbDbgDabrGet (void);
extern	void	wdbDbgDabr2Set (int value);
extern	int	wdbDbgDabr2Get (void);
extern	void	wdbDbgDbcrSet (int value);
extern	int	wdbDbgDbcrGet (void);
#  endif /* PPC_83xx || PPC_g2le */
# elif	(CPU == PPC403)
extern	void	wdbDbgDbcrSet (int value);
extern	int	wdbDbgDbcrGet (void);
extern	void	wdbDbgDbsrSet (int value);
extern	int	wdbDbgDbsrGet (void);
extern	void	wdbDbgDac1Set (int value);
extern	int	wdbDbgDac1Get (void);
extern	void	wdbDbgDac2Set (int value);
extern	int	wdbDbgDac2Get (void);
extern	void	wdbDbgIac1Set (int value);
extern	int	wdbDbgIac1Get (void);
extern	void	wdbDbgIac2Set (int value);
extern	int	wdbDbgIac2Get (void);

# elif   ((CPU == PPC405) || (CPU == PPC405F) || (CPU == PPC440) || \
	  (CPU == PPC85XX) || (CPU == PPC476) || (CPU == PPC465))
extern  void    wdbDbgDbcr0Set (int value);
extern  int     wdbDbgDbcr0Get (void);
extern  void    wdbDbgDbcr1Set (int value);
extern  int     wdbDbgDbcr1Get (void);
#  if	((CPU == PPC440) || (CPU == PPC85XX) || (CPU == PPC476) || (CPU == PPC465))
extern  void    wdbDbgDbcr2Set (int value);
extern  int     wdbDbgDbcr2Get (void);
#  endif  /* CPU == PPC440, PPC85XX, PPC476, PPC465 */
#  if   ((CPU == PPC440) || (CPU == PPC476) || (CPU == PPC465))
extern  void    wdbDbgDbdrSet (int value);
extern  int     wdbDbgDbdrGet (void);
#  endif  /* (CPU == PPC440, PPC476, PPC465) */
extern  void    wdbDbgDbsrSet (int value);
extern  int     wdbDbgDbsrGet (void);
extern  void    wdbDbgDac1Set (int value);
extern  int     wdbDbgDac1Get (void);
extern  void    wdbDbgDac2Set (int value);
extern  int     wdbDbgDac2Get (void);
extern  void    wdbDbgIac1Set (int value);
extern  int     wdbDbgIac1Get (void);
extern  void    wdbDbgIac2Set (int value);
extern  int     wdbDbgIac2Get (void);
# if    (CPU != PPC85XX)
extern  void    wdbDbgIac3Set (int value);
extern  int     wdbDbgIac3Get (void);
extern  void    wdbDbgIac4Set (int value);
extern  int     wdbDbgIac4Get (void);
# endif  /* CPU != PPC85XX */
# endif /* 509 555 860 : 603 EC603 604 : 403 : 405 405F 440 85XX  476*/

#endif 	/* _ASMLANGUAGE */
#endif 	/* DBG_HARDWARE_BP */

#ifdef __cplusplus
}
#endif

#endif /* __INCdbgPpcLibh */
