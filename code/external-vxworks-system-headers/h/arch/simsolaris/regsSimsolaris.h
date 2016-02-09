/* regsSimsolaris.h - simsolaris registers header */

/*
 * Copyright (c) 1995-2007,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable
 * Wind River license agreement.
 */

/*
modification history
--------------------
01q,01apr10,dbt  Removed pc macro to avoid name conflicts (WIND00205750).
01p,05jan07,elp  moved simStatus and simIntPendingLvl to host,
		 added interrupt level macros.
01o,24nov06,dbt  Added WIND_CPU_STATE
01n,26jul05,jmp  added fpReg as defined on other architectures.
01m,29dec03,jeg  added REG_SET_MMU_TRANS_TBL macro. Added additional macros 
		 required for RTP support.
01l,01dec03,jmp  added mmuTransTbl (current MMU translation table) to REG_SET.
01k,24nov03,jeg  added macros to manage supervisor bit
01j,18sep03,jeg  removed SIM_STATUS_INIT macro.
01i,09sep03,jeg  updated REG_SET structure to split intLockKey by a status 
		 bit field.
01h,03apr03,dbt  Removed references to ucontext.
01g,25mar03,dbt  Replaced reg_onstack field in TDB with intLockKey.
		 Removed no longer used signal mask from REG_SET.
		 Enabled use of macro in assembly code.
01f,20mar03,jeg  removed REG_XX definitions
01e,18mar03,dbt  Added interrupt level in REG_SET.
01d,19jun01,jmp  used host NGREG if defined.
01c,30dec97,dbt  added common names for registers
01b,27oct95,ism  cleanup
01a,12jun95,ism  written
*/

#ifndef __INCregsSimsolarish
#define __INCregsSimsolarish

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef struct			/* Solaris VxSim Register Set */
    {
    void *	pc;		/* pc to retore 			     */
    void *	reg_npc;	/* next pc to restore 			     */
    int		reg_psr;	/* psr to restore 			     */
    int		reg_wbcnt;	/* number of outstanding windows (always 0!) */
    int		reg_tbr;	/* not used for sim 			     */
    int		reg_y;		/* y register to restore 		     */
    int		reg_status;	/* status bit field 			     */
    int		unused[4];	/* unused (kept for backward compatibility)  */
    int		reg_global[8];	/* global registers 			     */
    int		reg_out[8];	/* out registers 			     */
    int		reg_local[8];	/* local registers 			     */
    int		reg_in[8];	/* in registers 			     */
    int		mmuTransTbl;	/* current MMU translation table	     */
    int		reserved[111];	/* unused (kept for backward compatibility)  */
   } REG_SET;

typedef struct wind_cpu_state	/* CPU initial state */ 
    {
    REG_SET	regs;		/* initial register set */
    } WIND_CPU_STATE;

/* some common names for registers */

#define reg_pc	pc	/* program counter */
#define reg_sp	reg_out[6]	/* stack pointer 	*/
#define reg_fp	reg_in[6]	/* frame pointer 	*/
#undef spReg
#define spReg	reg_out[6]
#undef fpReg
#define fpReg	reg_in[6]

extern volatile UINT32 *	pSimStatus;
extern volatile UINT32 *	pSimIntPendingLvl;

#define VXSIM_VAR_VALUE_GET(label)		(*##label)
#define VXSIM_VAR_VALUE_SET(label,value)	(*##label = value)

#else /* ASM_LANGUAGE */

#define VXSIM_SIMSTATUS_ADDR_GET(reg)				\
    sethi	%hi( FUNC(pSimStatus) ),reg;			\
    ld		[reg + %lo( FUNC(pSimStatus) )],reg;

#define VXSIM_SIMSTATUS_VALUE_GET(reg)				\
    sethi	%hi(FUNC(pSimStatus)),reg;			\
    ld		[reg + %lo(FUNC(pSimStatus))],reg;		\
    ld          [reg], reg;

#endif	/* _ASMLANGUAGE */

#define REG_SET_PC     		0x00	/* Program Counter 		  */
#define REG_SET_NPC    		0x04	/* Next Program Counter 	  */
#define REG_SET_PSR    		0x08	/* Processor Status Register 	  */
#define REG_SET_WIM    		0x0C	/* Window Invalid Mask 	 	  */
#define REG_SET_TBR    		0x10	/* Trap Base Register 		  */
#define REG_SET_Y      		0x14	/* Y Register 			  */
#define	REG_SET_SIMSTATUS	0x18	/* Status Register 		  */
#define REG_SET_GLOBALS		0x2C	/* Global Registers (%R0  - %R7)  */
#define REG_SET_OUTS		0x4C	/* Out Registers    (%R8  - %R15) */
#define REG_SET_LOCALS		0x6C	/* Local Registers  (%R16 - %R23) */
#define REG_SET_INS		0x8C	/* In Registers     (%R24 - %R31) */
#define REG_SET_MMU_TRANS_TBL	0xAC

#define REG_SET_GLOBAL(n)	(REG_SET_GLOBALS + (4 * (n)))
#define REG_SET_OUT(n)		(REG_SET_OUTS + (4 * (n)))
#define REG_SET_LOCAL(n)	(REG_SET_LOCALS + (4 * (n)))
#define REG_SET_IN(n)		(REG_SET_INS + (4 * (n)))

#define PC_OFFSET	REG_SET_PC	/* referenced by pc() in usrLib */

#define REG_SET_SIZE		620	/* size of REG_SET struct */

/* registers offset into stack frame */

#define SF_REG_LOCALS		0	
#define SF_REG_INS		0x20	

#define SF_REG_LOCAL(n)		(SF_REG_LOCALS + (4 * (n)))
#define SF_REG_IN(n)		(SF_REG_INS + (4 * (n)))

/* status bit fields */

#define SIM_STATUS_INTLOCK	0x0001	/* interrupt locked	*/
#define SIM_STATUS_INTUNLOCK	0x0000	/* interrupt unlocked	*/
#define SIM_STATUS_SUP		0x0002	/* supervisor mode	*/
#define SIM_STATUS_USR		0x0000	/* user mode		*/
#define SIM_STATUS_INTLVL_MASK	0x0f00	/* interrupt level mask */
#define SIM_STATUS_INTLVL_SHIFT	8

/* macros to access interrupt status field */

#define VXSIM_INT_MASK_SET(vxsimStatus) \
    (vxsimStatus |= SIM_STATUS_INTLOCK)

#define VXSIM_INT_MASK_CLEAR(vxsimStatus) \
    (vxsimStatus &= ~(SIM_STATUS_INTLOCK))

#define VXSIM_INT_MASK_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_INTLOCK) == 0) ? FALSE : TRUE)

#define VXSIM_SUP_MODE_SET(vxsimStatus) \
    (vxsimStatus |= SIM_STATUS_SUP)

#define VXSIM_USR_MODE_SET(vxsimStatus) \
    (vxsimStatus &= ~(SIM_STATUS_SUP))
	   
#define VXSIM_SUP_MODE_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_SUP) == 0) ? FALSE : TRUE)

#define VXSIM_INT_LVL_GET(vxsimStatus) \
    (((vxsimStatus & SIM_STATUS_INTLVL_MASK) >> SIM_STATUS_INTLVL_SHIFT))

#define VXSIM_INT_LVL_SET(vxsimStatus,intLvl)			\
    (vxsimStatus = (vxsimStatus & ~SIM_STATUS_INTLVL_MASK) |	\
		   ((intLvl << SIM_STATUS_INTLVL_SHIFT) &	\
		    SIM_STATUS_INTLVL_MASK))

#ifdef __cplusplus
}
#endif

#endif /* __INCregsSimsolarish */
