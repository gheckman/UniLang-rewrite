/* dsmMipsLib.h - definitions for MIPS IV disassembler */

/* Copyright 1984-2004, 2010 Wind River Systems, Inc. */

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
02h,29apr10,pad  Moved extern C statement after include statements.
02g,02mar04,pes  Add opcode for syscall instruction.
02f,16jul01,ros  add CofE comment
02e,12jul00,dra  add mask for branch instructions
02d,23sep99,myz  added mips16 instruction related macros.
02e,30apr99,dra  added vtype for VR5400 multimedia insn support.
02e,10feb99,kab  added cpumask to INST struct.
02d,10mar97,sub  added MIPS IV Support for VR5000. 
02c,27may95,cd	 switched from MIPSE[BL] to _BYTE_ORDER for ansi compliance
02b,03jan95,cd	 removed enianess dependencies
02a,09oct93,cd   modified for MIPSIII disassembler
01g,22sep92,rrr  added support for c++
01f,12sep92,ajm  changed OPCODE_MASK and OFFSET_MASK due to name space conflict
01e,03jun92,ajm  updated file name referenced to match real name
01d,26may92,rrr  the tree shuffle
01c,04oct91,rrr  passed through the ansification filter
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01b,22jun90,rtp  corrected COPZ mask and number COP0 opcodes.
01a,31may90,rtp  created for MIPS R3000 disassembler.
*/

#ifndef __INCdsmMipsLibh
#define __INCdsmMipsLibh

#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

/* dsmLib status codes */

#define S_dsmLib_UNKNOWN_INSTRUCTION	(M_dsmLib | 1)

/* instruction types */

#ifndef	_ASMLANGUAGE

/*
 *   Structure describing an instruction used to disassemble instruction.
 *   An instruction matches an entry when the instruction ANDed with the
 *   mask matches op.  The instruction operands are decoded using the
 *   operand description string.
 */

typedef struct
    {
    char * 		name;		/* mnemonic */
    unsigned long	op;		/* op-code to match */
    unsigned long	mask;		/* mask used to match with op */
    char *		operands;	/* operand format */
    unsigned long	cpumask;	/* cpu type(s) where inst is valid */
    } INST;

/*
 * Union describing all instruction formats
 */
typedef union
    {
    unsigned int	code;
    struct
   	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	target : 26;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	target : 26;
	unsigned int	op : 6;
#endif
	} jtype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	rs : 5;
	unsigned int	rt : 5;
	int		i : 16;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	int		i : 16;
	unsigned int	rt : 5;
	unsigned int	rs : 5;
	unsigned int	op : 6;
#endif
	} itype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	rs : 5;
	unsigned int	rt : 5;
	unsigned int	u : 16;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	u : 16;
	unsigned int	rt : 5;
	unsigned int	rs : 5;
	unsigned int	op : 6;
#endif
	} utype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	rs : 5;
	unsigned int	rt : 5;
	unsigned int	rd : 5;
	unsigned int	s : 5;
	unsigned int	func : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	func : 6;
	unsigned int	s : 5;
	unsigned int	rd : 5;
	unsigned int	rt : 5;
	unsigned int	rs : 5;
	unsigned int	op : 6;
#endif
	} rtype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	: 1;
	unsigned int	fmt : 4;
	unsigned int	ft : 5;
	unsigned int	fs : 5;
	unsigned int	fd : 5;
	unsigned int	func : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	func : 6;
	unsigned int	fd : 5;
	unsigned int	fs : 5;
	unsigned int	ft : 5;
	unsigned int	fmt : 4;
	unsigned int	: 1;
	unsigned int	op : 6;
#endif
	} ftype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	fr:  5;
	unsigned int	ft : 5;
	unsigned int	fs : 5;
	unsigned int	fd : 5;
	unsigned int    func: 3;
	unsigned int	fmt : 3;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	fmt : 3;
	unsigned int    func: 3;
	unsigned int	fd : 5;
	unsigned int	fs : 5;
	unsigned int	ft : 5;
	unsigned int	fr:  5;
	unsigned int	op : 6;
#endif
	} fmips4type;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	media : 6;
	unsigned int	sel : 4;
	unsigned int	: 1;
	unsigned int	vt : 5;
	unsigned int	vs : 5;
	unsigned int	vd : 5;
	unsigned int	op : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	op : 6;
	unsigned int	vd : 5;
	unsigned int	vs : 5;
	unsigned int	vt : 5;
	unsigned int	: 1;
	unsigned int	sel : 4;
	unsigned int	media : 6;
#endif
	} vtype;


    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	co : 1;
	unsigned int	cofun : 25;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	cofun : 25;
	unsigned int	co : 1;
	unsigned int	op : 6;
#endif
	} ctype;
    struct
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int	op : 6;
	unsigned int	code : 20;
	unsigned int	func : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int	func : 6;
	unsigned int	code : 20;
	unsigned int	op : 6;
#endif
	} ttype;

    struct 
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int       : 11;
	unsigned int    cc : 3;
	unsigned int       : 18;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int       : 18;
	unsigned int    cc : 3;
	unsigned int       : 11;
#endif
	}readCCtype;
    struct 
	{
#if _BYTE_ORDER == _BIG_ENDIAN
	unsigned int       : 21;
	unsigned int    cc : 3;
	unsigned int       : 8;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
	unsigned int       : 8;
	unsigned int    cc : 3;
	unsigned int       : 21;
#endif
	}writeCCtype;
    } mipsInst;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op   : 6;
    unsigned rs   : 5;
    unsigned rt   : 5;
    unsigned immediate : 16;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned immediate : 16;
    unsigned rt   : 5;
    unsigned rs   : 5;
    unsigned op   : 6;
#endif
    } IMMEDIATETYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op   : 6;
    unsigned target : 26;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned target : 26;
    unsigned op   : 6;
#endif
    } JUMPTYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op   : 6;
    unsigned rs   : 5;
    unsigned rt   : 5;
    unsigned rd   : 5;
    unsigned shamt : 5;
    unsigned funct : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned funct : 6;
    unsigned shamt : 5;
    unsigned rd   : 5;
    unsigned rt   : 5;
    unsigned rs   : 5;
    unsigned op   : 6;
#endif
    } REGISTERTYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op  : 6;
    unsigned notOpcode : 26;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned notOpcode : 26;
    unsigned op  : 6;
#endif
    }  UFOTYPEINST;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op : 6;
    unsigned co : 1;
    unsigned cofun : 25;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned cofun : 25;
    unsigned co : 1;
    unsigned op : 6;
#endif
    }  COPZSUBTYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op : 6;
    unsigned z  : 1;
    unsigned fmt : 4;
    unsigned ft : 5;
    unsigned fs : 5;
    unsigned fd : 5;
    unsigned func : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned func : 6;
    unsigned fd : 5;
    unsigned fs : 5;
    unsigned ft : 5;
    unsigned fmt : 4;
    unsigned z  : 1;
    unsigned op : 6;
#endif
    }  FPCPSUBTYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op : 6;
    unsigned rs : 5;
    unsigned rt : 5;
    unsigned offset : 16;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned offset : 16;
    unsigned rt : 5;
    unsigned rs : 5;
    unsigned op : 6;
#endif
    }  BCONDSUBTYPE;

typedef struct
    {
#if _BYTE_ORDER == _BIG_ENDIAN
    unsigned op : 6;
    unsigned brknumber : 10;	 /* this is a MIPS SW convention */
    unsigned code : 10;		 /* available but not used ??    */
    unsigned func : 6;
#endif
#if _BYTE_ORDER == _LITTLE_ENDIAN
    unsigned func : 6;
    unsigned code : 10;		 /* available but not used ??    */
    unsigned brknumber : 10;	 /* this is a MIPS SW convention */
    unsigned op : 6;
#endif
    }  BREAKSUBTYPE;

#endif	/* !_ASMLANGUAGE */

/* instruction and sub-instruction opcode masks */

#define GENERAL_OPCODE_MASK	(077<<26)
#define SPECIAL_OPCODE_MASK 	077		/* and FPCP function mask */
#define BCOND_OPCODE_MASK	(0x1f<<16)
#define COPZ_OPCODE_MASK	(0x1f<<21)
#define COP0_OPCODE_MASK     	0x1f
#define COP1_OPCODE_MASK	(0xf<<22)
#define SHAMT_MASK		(0x1f<<6)
#define RT_POS			16          	/* bit position */
#define RT_MASK			(0x1f<<RT_POS)  /* target register mask */
#define RS_POS			21          	/* bit position */
#define RS_MASK			(0x1f<<RS_POS)  /* source register mask */
#define RD_POS	        	11          	/* bit position */
#define RD_MASK			(0x1f<<RD_POS)  /* destination register mask */
#define BEQ_MASK		(RS_MASK|RT_MASK)
#define REGIMM			(0x4<<24)
#define CC_POS			18
#define CC_MASK			(0x7<<CC_POS)

/* Instruction OP CODE definitions */

#define BEQ_INSTR		0x10000000
#define BNE_INSTR		0x14000000
#define BLEZ_INSTR		0x18000000
#define BGTZ_INSTR		0x1c000000
#define BEQL_INSTR		0x50000000
#define BNEL_INSTR		0x54000000
#define BLEZL_INSTR		0x58000000
#define BGTZL_INSTR		0x5c000000
#define	BC1F_INSTR		0x45000000
#define	BC1T_INSTR		0x45010000
#define	BC1FL_INSTR		0x45020000
#define	BC1TL_INSTR		0x45030000
#define BLTZ_INSTR		0x00000000
#define BGEZ_INSTR		0x00010000
#define BLTZL_INSTR		0x00020000
#define BGEZL_INSTR		0x00030000
#define BLTZAL_INSTR		0x00100000
#define BGEZAL_INSTR		0x00110000
#define BLTZALL_INSTR		0x00120000
#define BGEZALL_INSTR		0x00130000
#define	JR_INSTR		0x00000008
#define	JALR_INSTR		0x00000009
#define	J_INSTR			0x08000000
#define	JAL_INSTR		0x0c000000
#define	BREAK_INSTR		0x0000000d
#define LW_INSTR		0x8c000000
#define SW_INSTR		0xac000000
#define LD_INSTR		0xdc000000
#define SD_INSTR		0xfc000000
#define ADDIU_INSTR		0x24000000
#define SYSCALL_INSTR		0x0000000c

/* Instruction decode definitions */

#define	OPCODE_POS	26
#define BCOND		0x04000000
#define SPECIAL		0x00000000
#define BASE_MASK	0x03e00000  /* base register mask */
#define BASE_POS	21          /* bit position */
#define OFFSET16_MASK	0x0000ffff  /* offset from the base register value */
#define TARGET_MASK	0x03ffffff  /* target of a J or JAL instruction */
#define	TARGET_POS	26	    /* bit position */
#define RA		31          /* return address register number */
#define SP		29          /* stack pointer register number */
#define BCOND_MASK	0x001f0000  /* Branch CONDitional op codes */
#define BCF_MASK	0x03ff0000  /* Branch on coprocessor false */
#define BCT_MASK	0x03ff0000  /* Branch on coprocessor true */
#define SPECIAL_MASK	0x0000003f  /* SPECIAL op codes */
#define	SPECIAL_POS	26
#define BREAK_CODE_MASK	0x00ff0000
#define BREAK_CODE_POS	16
#define	IMMEDIATE_POS	16
#define	CP1_VALUE	0x800000

/* instruction related defines for mips16 */

#define M16_LWSP_INSTR       0x12
#define M16_EXTEND_INSTR     0x1e        /* mips16 extend opcode */
#define M16_B_INSTR          0x2         /* mips16 b opcode */
#define M16_BEQZ_INSTR       0x4
#define M16_BNEZ_INSTR       0x5
#define M16_I8_INSTR         0xc
#define M16_JALNX_INSTR      0x3
#define M16_RR_INSTR         0x1d
#define M16_LB_INSTR         0x10
#define M16_LBU_INSTR        0x14
#define M16_LH_INSTR         0x11
#define M16_LHU_INSTR        0x15
#define M16_LW_INSTR         0x13
#define M16_SB_INSTR         0x18
#define M16_SH_INSTR         0x19
#define M16_SW_INSTR         0x1b
#define M16_ADDIUSP_INSTR    0x0
#define M16_ADDIUPC_INSTR    0x01
#define M16_ADDIU8_INSTR     0x09
#define M16_LWSP_INSTR       0x12
#define M16_LWPC_INSTR       0x16
#define M16_SWSP_INSTR       0x1a

#define M16_I8_SWRASP        0x6200
#define M16_JR_RA_INSTR      0xe820
#define M16_JR_A3_INSTR      0xef00
#define M16_ADJSP_INSTR      0x6300

#define M16_OPCODE_MASK      0xf800      /* instruction opcode mask */
#define M16_OPCODE_SHIFTER   11

#define M16_RX_SHIFTER       0x8
#define M16_RX_MASK          0x700
#define M16_REG_7            0x7
#define M16_I8_MASK          0xff00

#define M16_RI_OFFSET(instr)    (((instr) & 0xff) << 2)

#define M16_RX(instr) \
	(((instr) & M16_RX_MASK) >> M16_RX_SHIFTER)

/* extraction of mips16 jal(x) immediate */

#define M16_JALX_IMM(x) \
	( ((((x) & 0x3e00000) >> 5) | ((x & 0x1f0000) << 5) | (x & 0xffff))<<2) 

/* extraction of mips16 instruction opcode */

#define M16_INSTR_OPCODE(instr) \
	(((instr) & M16_OPCODE_MASK) >> M16_OPCODE_SHIFTER)

/* extraction of extend immediate field */

#define M16_EXTEND_IMM(instr)  ((((instr) & 0x1f) << 11) | ((instr) & 0x7e0))

/* sign extended to 32 bit for a 16 bit value */

#define SIGN_EXTEND_32BIT(value) \
	if (value & 0x8000) \
			value |= 0xffff0000

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmMipsLibh */
