/* fpSoft.h - constants for MIPS R3010 software floating point emulation */

/*
 * Copyright (c) 1991-1993, 1995, 2000-2001, 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * This file has been developed or significantly modified by the
 * MIPS Center of Excellence Dedicated Engineering Staff.
 * This notice is as per the MIPS Center of Excellence Master Partner
 * Agreement, do not remove this notice without checking first with
 * WR/Platforms MIPS Center of Excellence engineering management.
 */

/*
modification history
--------------------
01m,29nov06,pes  Correct namespace collisions with dsmMipsLib.h.
01l,20mar06,rlg  SPR 117241 - new defines for COP1x emulation.
01k,16jul01,ros  add CofE comment
01j,28feb00,dra  updated explicit conversion opcodes for .L format.
01i,27may95,cd	 switched from MIPSE[BL] to _BYTE_ORDER for ansi compliance
01h,03apr95,ism  added 'int' to the 'signed' and 'unsigned' bit field types
01g,01sep93,yao  added constant definitions for fpu load/store instruction.
01f,22sep92,rrr  added support for c++
01e,12sep92,ajm  changed OPCODE_MASK for name clash
01d,03jun92,ajm  updated file name referenced to match real name
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01a,22jul91,ajm   wrs-ized from MIPS code
*/

/* |-----------------------------------------------------------|
 * | Copyright (c) 1990 MIPS Computer Systems, Inc.            |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 52.227-7013.   |
 * |         MIPS Computer Systems, Inc.                       |
 * |         928 Arques Avenue                                 |
 * |         Sunnyvale, CA 94086                               |
 * |-----------------------------------------------------------|
 */

#ifndef __INCfpSofth
#define __INCfpSofth

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The _MASK's are used to get a the specified field after it has been
 * shifted by _SHIFT and then bit patterns (like _COPN) can be used to test
 * the field.
 */
/* constants for the OPCODE field for some general instructions */
#define	OPCODE_SHIFT	26
#define	OPCODE_GMASK	0x3f
#define	OPCODE_SPECIAL	0x00
#define	OPCODE_BCOND	0x01
#define	OPCODE_REGIMM	0x01
#define	OPCODE_J	0x02
#define	OPCODE_JAL	0x03
#define	OPCODE_BEQ	0x04
#define	OPCODE_C1	0x11
/*
* spr 117241 - addition of missing emulation opcodes 
* and other definitions to facilitate the emulation of those opcodes
* COP1X = 0x13  bits 31-26  madd,nmadd,msub,nmsub instructions
* Subcode = bits 5-3 
* FMT = bits 2-0
*/
#define	OPCODE_C1X	0x13		/* bits 31-26 */
#define C1XSBCD_SHIFT   0x3		/* shift value to get sub code */
#define C1XSBCD_MASK    0x7		/* mask value to get sub code */
#define SBCODE_MADD     0x4		/* sub code for MADD */
#define SBCODE_NMADD    0x6		/* sub code for NMADD */
#define SBCODE_MSUB     0x5		/* sub code for NMADD */
#define SBCODE_NMSUB    0x7		/* sub code for NMADD */
#define SBCODE_FMT_MASK 0x7		/* format mask value */
#define SBCODE_FMT_S    0		/* 32 bit precision */
#define SBCODE_FMT_D    1		/* 64 bit precision */
#define SBCODE_FMT_PS   0x6             /* paired single mode */

#define C1XREG_FD_SFT   0x6		/* shift value for fd reg */
#define C1XREG_FS_SFT   0xb		/* shift value for fs reg */
#define C1XREG_FT_SFT   0x10		/* shift value for ft reg */
#define C1XREG_FR_SFT   0x15		/* shift value for fr reg */
#define C1XREG_MASK     0x1f		/* mask value registers */


/* constants for the emulating jump or jump and link instructions */
#define	TARGET_MASK	0x03ffffff
#define	PC_JMP_MASK	0xf0000000

/* constants for the FUNC field for some general instructions */
#define	FUNC_MASK	0x3f
#define	FUNC_JR		0x08
#define	FUNC_JALR	0x09

/*
 * constants for the OPCODE field for detecting all general branch
 * (beq,bne,blez,bgtz) instructions and all coprocessor instructions.
 */
#define	BRANCH_MASK	0x3c
#define	OPCODE_BRANCHES	0x04
#define OPCODE_BRANCH_LIKELIES	0x14
#define	COPN_MASK	0x3c
#define	OPCODE_COPN	0x10

/*
 * constants for the RegisterImmediate instructions
 */
#define REGIMM_SHIFT	0x16
#define REGIMM_BRANCH_MASK	0x1c
#define REGIMM_BCOND		0x00		/* bltz, bgez, bltzl, bgezl */
#define REGIMM_BAL		0x10		/* bltzal, bgezal, etc.	    */

/* constants for load/store COPN instructions */
#define	OP_LSWCOPNMASK	0x33
#define	OP_LSWCOPN	0x31
#define OP_LSBITMASK	0x8			/* store vs load */
#define OP_LSDBITMASK	0x4			/* doubleword vs singleword */
#define OP_LBIT		0x0

/* constants for branch on COPN condition instructions */
#define	COPN_BCSHIFT	24
#define	COPN_BCMASK	0x3
#define	COPN_BC		0x1
#define	BC_TFBITSHIFT	16
#define	BC_TFBITMASK	0x1
#define BC_FBIT		0x0

/* constants for move to/from COPN instructions */
#define	COPN_MTFSHIFT	25
#define	COPN_MTFMASK	0x1
#define	COPN_MTF	0x0
#define	COPN_MTFBITSHIFT	23
#define	COPN_MTFBITMASK	0x1
#define COPN_MFBIT	0x0

/* constants for move control registers to/from CP1 instructions */
#define M_CONBITSHIFT	22
#define	M_CONBITMASK	0x1

#define FPR_REV		0
#define FPR_EIR		30
#define FPR_CSR		31
#define	SOFTFP_REVWORD	0x0

/*
 * These constants refer to the fields of coprocessor instructions not
 * cpu instructions (ie the RS and RD fields are different).
 */
#define BASE_SHIFT	21
#define FPE_BASE_MASK	0x1f
#define RT_SHIFT	16
#define	FPE_RT_MASK	0x1f
#define	RT_FPRMASK	0x1e
#define RS_SHIFT	11
#define	FPE_RS_MASK	0x1f
#define	RS_FPRMASK	0x1e
#define RD_SHIFT	6
#define	FPE_RD_MASK	0x1f
#define	RD_FPRMASK	0x1e

#define IMMED_SHIFT	16

#define C1_FMT_SHIFT	21
#define	C1_FMT_MASK	0xf
#define C1_FMT_SINGLE	0
#define C1_FMT_DOUBLE	1
#define C1_FMT_EXTENDED	2
#define C1_FMT_QUAD	3
#define C1_FMT_WORD	4
#define C1_FMT_MAX	5

#define C1_FUNC_MASK	0x3f
#define C1_FUNC_DIV	3
#define C1_FUNC_NEG	7
#define C1_FUNC_ROUNDL	8
#define C1_FUNC_FLOORL	0x0b
#define C1_FUNC_ROUNDW	0x0c
#define C1_FUNC_FLOORW	0x0f
#define C1_FUNC_CVTS	0x20
#define C1_FUNC_CVTD	0x21
#define C1_FUNC_CVTW	0x24
#define C1_FUNC_CVTL	0x25
#define C1_FUNC_1stCMP	0x30

#define COND_UN_MASK	0x1
#define COND_EQ_MASK	0x2
#define COND_LT_MASK	0x4
#define COND_IN_MASK	0x8

/* 
 * These constants refer to the fields of coprocessor store/load instructions.
 */

#define	FPU_TYPE_SHIFT	16		/* shift instruction 16 bits to right */
#define	FPU_I_INST_MASK	0x03c0    	/* I-type instruction mask */
#define	FPU_TYPE_MASK	0x0200    	/* I-type instruction mask */
#define	FPU_INST_MFC	0x0000    	/* mfc1 instructio */
#define	FPU_INST_MTC	0x0080    	/* mtc1 instructio */
#define	FPU_INST_CFC	0x0040    	/* cfc1 instructio */
#define	FPU_INST_CTC	0x00c0    	/* ctc1 instructio */
#define FPU_I_RT_MASK	0x001f		/* rt bits */
#define FPU_I_RS_MASK	0xf800		/* rs bits */
#define FPU_STLD1_MASK	0xfc00		/* swc1/lwc1 code mask 16 bit right 
					 * shifted */
#define	FPU_SW_INSTR	0xe400		/* swc1 instruction */
#define	FPU_LW_INSTR	0xc400		/* lwc1 instruction */
#define	OFFSET_MASK	0xffff		/* offset mask for I-type instruction */
#define	SLW_BASE_MASK	0x03e0		/* base maske for I-type instruction */

/*
 * These constants refer to fields in the floating-point status and control
 * register.
 */
#define	CSR_CBITSHIFT	23
#define	CSR_CBITMASK	0x1
#define	CSR_CBITSET	0x00800000
#define	CSR_CBITCLEAR	0xff7fffff

#define	CSR_EXCEPT	0x0003f000
#define	UNIMP_EXC	0x00020000
#define	INVALID_EXC	0x00010040
#define	DIVIDE0_EXC	0x00008020
#define	OVERFLOW_EXC	0x00004010
#define	UNDERFLOW_EXC	0x00002008
#define	INEXACT_EXC	0x00001004

#define CSR_ENABLE		0x00000f80
#define	INVALID_ENABLE		0x00000800
#define	DIVIDE0_ENABLE		0x00000400
#define	OVERFLOW_ENABLE		0x00000200
#define	UNDERFLOW_ENABLE	0x00000100
#define	INEXACT_ENABLE		0x00000080

#define	CSR_RM_MASK	0x3
#define	CSR_RM_RN	0
#define	CSR_RM_RZ	1
#define	CSR_RM_RPI	2
#define	CSR_RM_RMI	3

/*
 * These constants refer to floating-point values for all formats
 */
#define	SIGNBIT		0x80000000

#define	GUARDBIT	0x80000000
#define	STKBIT		0x20000000

/*
 * These constants refer to word values
 */
#define	WORD_MIN	0x80000000
#define	WORD_MAX	0x7fffffff
#define	WEXP_MIN	-1
#define	WEXP_MAX	30
#define	WQUIETNAN_LEAST	0x7fffffff

/*
 * These constants refer to 64-bit long values
 */
#define	LONG_MIN_HIGH	0x80000000
#define	LONG_MIN_LOW	0x00000000
#define	LONG_MAX_HIGH	0x7fffffff
#define	LONG_MAX_LOW	0xffffffff
#define	LEXP_MIN	-1
#define	LEXP_MAX	62
#define	LQUIETNAN_LEAST_HIGH	0x7fffffff
#define	LQUIETNAN_LEAST_LOW	0xffffffff

/*
 * These constants refer to single format floating-point values
 */
#define	SEXP_SHIFT	23
#define	SEXP_MASK	0xff
#define	SEXP_NAN	0xff
#define	SEXP_INF	0xff
#define	SEXP_BIAS	127
#define	SEXP_MAX	127
#define	SEXP_MIN	-126
#define	SEXP_OU_ADJ	192
#define	SIMP_1BIT	0x00800000
#define	SFRAC_LEAD0S	8
#define	SFRAC_BITS	23
#define	SFRAC_MASK	0x007fffff
#define	SFRAC_LEAST_MAX	0x007fffff

#define	SSNANBIT_MASK	0x00400000
#define	SQUIETNAN_LEAST	0x7fbfffff

/*
 * These constants refer to double format floating-point values
 */
#define	DEXP_SHIFT	20
#define	DEXP_MASK	0x7ff
#define	DEXP_NAN	0x7ff
#define	DEXP_INF	0x7ff
#define	DEXP_BIAS	1023
#define	DEXP_MAX	1023
#define	DEXP_MIN	-1022
#define	DEXP_OU_ADJ	1536
#define	DIMP_1BIT	0x00100000
#define	DFRAC_LEAD0S	11
#define	DFRAC_BITS	52
#define	DFRAC_MASK	0x000fffff
#define	DFRAC_LESS_MAX	0x000fffff
#define	DFRAC_LEAST_MAX	0xffffffff

#define	DSNANBIT_MASK	0x00080000
#define	DQUIETNAN_LESS	0x7ff7ffff
#define	DQUIETNAN_LEAST	0xffffffff

#ifndef _ASMLANGUAGE
/*
 * Structure and constant definisions for floating-point instructions.
 */
union fpu_instr {
	unsigned long instr;

	struct {
#if _BYTE_ORDER==_BIG_ENDIAN
		unsigned int op : 6;
		unsigned int base : 5;
		unsigned int rt : 5;
		signed int immed : 16;
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */
#if _BYTE_ORDER==_LITTLE_ENDIAN
		signed int immed : 16;
		unsigned int rt : 5;
		unsigned int base : 5;
		unsigned int op : 6;
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */
	} itype;

	struct {
#if _BYTE_ORDER==_BIG_ENDIAN
		unsigned int op : 6;
		unsigned int sub : 5;
		unsigned int rt : 5;
		unsigned int rs : 5;
		unsigned int : 11;
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */
#if _BYTE_ORDER==_LITTLE_ENDIAN
		unsigned int : 11;
		unsigned int rs : 5;
		unsigned int rt : 5;
		unsigned int sub : 5;
		unsigned int op : 6;
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */
	} mtype;

	struct {
#if _BYTE_ORDER==_BIG_ENDIAN
		unsigned int op : 6;
		unsigned int one : 1;
		unsigned int fmt : 4;
		unsigned int rt : 5;
		unsigned int rs : 5;
		unsigned int rd : 5;
		unsigned int func : 6;
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */
#if _BYTE_ORDER==_LITTLE_ENDIAN
		unsigned int func : 6;
		unsigned int rd : 5;
		unsigned int rs : 5;
		unsigned int rt : 5;
		unsigned int fmt : 4;
		unsigned int one : 1;
		unsigned int op : 6;
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */
	} rtype;
};
#endif	/* _ASMLANGUAGE */

#define FMT_SINGLE	0
#define FMT_DOUBLE	1
#define FMT_EXTENDED	2
#define FMT_QUAD	3
#define FMT_WORD	4
#define FMT_MAX		4

#define FUNC_ADD	0
#define FUNC_SUB	1
#define FUNC_MUL	2
#define FUNC_DIV	3

#define	FUNC_SQRT	4
#define	FUNC_ABS	5
#define	FUNC_MOV	6
#define FUNC_NEG	7

#define FUNC_CVTS	0x20
#define FUNC_CVTD	0x21
#define FUNC_CVTE	0x22
#define FUNC_CVTQ	0x23
#define FUNC_CVTW	0x24

/*
 * The func field of floating-point compare opcodes are FUNC_FC with
 * some combination of conditions (COND_*).
 */

#define FUNC_FC		0x30
#define COND_UN_MASK	0x1
#define COND_EQ_MASK	0x2
#define COND_LT_MASK	0x4
#define COND_IN_MASK	0x8

/*
 * The _MASK's are used to get a the specified field after it has been
 * shifted by _SHIFT and then bit patterns above can be used to test
 * the field.  These are useful in assembly code.
 */

#define	FPU_BASE_SHIFT	21
#define	FPU_BASE_MASK	0x1f
#define	FPU_FMT_SHIFT	21
#define	FPU_FMT_MASK	0xf
#define	FPU_RT_SHIFT	16
#define	FPU_RT_MASK	0x1f
#define	FPU_RT_FPRMASK	0x1e
#define	FPU_RS_SHIFT	11
#define	FPU_RS_MASK	0x1f
#define	FPU_RS_FPRMASK	0x1e
#define	FPU_RD_SHIFT	6
#define	FPU_RD_MASK	0x1f
#define	FPU_RD_FPRMASK	0x1e

#ifndef _ASMLANGUAGE

/*
 * Structure and constant definisions for the floating-point control
 * implementation and revision register (fpc_irr).
 */
union fpc_irr {
	unsigned long fi_word;
	struct {
#if _BYTE_ORDER==_BIG_ENDIAN
		unsigned int reserved : 16;
		unsigned int implementation : 8;
		unsigned int revision : 8;
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */
#if _BYTE_ORDER==_LITTLE_ENDIAN
		unsigned int revision : 8;
		unsigned int implementation : 8;
		unsigned int reserved : 16;
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */
	} fi_struct;
};
#endif	/* _ASMLANGUAGE */

/*
 * Constants for the implementation fieid of the fpc_irr structure for the
 * known implementations.
 */
#define IMPLEMENTATION_NONE	0	/* software */
#define IMPLEMENTATION_R2360	1	/* board */
#define IMPLEMENTATION_R2010	2	/* chip */

/*
 * The constant IRR_IMP_MASK is to get at the implementation fieid of the
 * implementation and revision register.  The other constants (IRR_IMP_*)
 * are constants for the known implementations.
 */
#define IRR_IMP_MASK		0x0000ff00

#define IRR_IMP_NONE		0x00000000
#define IRR_IMP_R2360		0x00000100
#define IRR_IMP_R2010		0x00000200
#define IRR_IMP_R3010		0x00000300
#define IRR_IMP_R6010		0x00000400

/*
 * Structure and constant definisions for the floating-point control
 * control and status register (fpc_csr).
 */
#ifndef _ASMLANGUAGE
union fpc_csr {
	unsigned long fc_word;
	struct {
#if _BYTE_ORDER==_BIG_ENDIAN
		unsigned int reserved0 : 8;
		unsigned int condition : 1;
		unsigned int reserved1 : 5;

		unsigned int ex_unimplemented : 1;
		unsigned int ex_invalid : 1;
		unsigned int ex_divide0 : 1;
		unsigned int ex_overflow : 1;
		unsigned int ex_underflow : 1;
		unsigned int ex_inexact : 1;

		unsigned int en_invalid : 1;
		unsigned int en_divide0 : 1;
		unsigned int en_overflow : 1;
		unsigned int en_underflow : 1;
		unsigned int en_inexact : 1;

		unsigned int se_invalid : 1;
		unsigned int se_divide0 : 1;
		unsigned int se_overflow : 1;
		unsigned int se_underflow : 1;
		unsigned int se_inexact : 1;

		unsigned int rounding_mode : 2;
#endif	/* _BYTE_ORDER==_BIG_ENDIAN */
#if _BYTE_ORDER==_LITTLE_ENDIAN
		unsigned int rounding_mode : 2;

		unsigned int se_inexact : 1;
		unsigned int se_underflow : 1;
		unsigned int se_overflow : 1;
		unsigned int se_divide0 : 1;
		unsigned int se_invalid : 1;

		unsigned int en_inexact : 1;
		unsigned int en_underflow : 1;
		unsigned int en_overflow : 1;
		unsigned int en_divide0 : 1;
		unsigned int en_invalid : 1;

		unsigned int ex_inexact : 1;
		unsigned int ex_underflow : 1;
		unsigned int ex_overflow : 1;
		unsigned int ex_divide0 : 1;
		unsigned int ex_invalid : 1;
		unsigned int ex_unimplemented : 1;

		unsigned int reserved1 : 5;
		unsigned int condition : 1;
		unsigned int reserved0 : 8;
#endif	/* _BYTE_ORDER==_LITTLE_ENDIAN */
	} fc_struct;
};
#endif	/* _ASMLANGUAGE */

/*
 * Constants for the rounding_mode field of the fpc_csr
 */
#define ROUND_TO_NEAREST	0
#define ROUND_TO_ZERO		1
#define ROUND_TO_PLUS_INFINITY	2
#define ROUND_TO_MINUS_INFINITY	3

/* Masks to get at the unimplemented exception */
#define	FPCSR_UNIMP		0x00020000
#define	FPCSR_EXCEPTIONS	0x0003f000	/* all exceptions */
#define	FPCSR_ENABLES		0x00000f80	/* all enables */

/*
 * fpc_parity bits
 */
#define FPPARITY_FRF	0x00800000	/* force reg file parity error */
#define FPPARITY_IRF	0x00020000	/* inhibit reg file parity error */
#define FPPARITY_IIB	0x00010000	/* inhibit icache bus parity error */
#define FPPARITY_RF	0x00000002	/* reg file parity error */
#define FPPARITY_IB	0x00000001	/* icache bus parity error */

#ifdef __cplusplus
}
#endif

#endif /* __INCfpSofth */
