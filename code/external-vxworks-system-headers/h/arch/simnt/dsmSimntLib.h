/* dsmI86Lib.h - i80x86 disassembler header */

/*
 * Copyright (c) 1992-1994, 1998, 2001-2004, 2007, 2010-2012
 *                Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01r,04dec12,scm  WIND00390647 - Incorrect disassembly for floating point op
                 codes...
01q,15dec11,scm  correct/clean up disassembler, fixed :WIND00253537,
                 WIND00268334, WIND00273589, WIND00281892, WIND00306787,
                 WIND00312688.
01p,19jan11,ggm  Added support for AVX and AES instructions and fixed the REX
                 prefix in the dissambler.
01o,18oct10,ggm  Fixed some SSE and SSE2 instructions. Added SSE3, SSE4.1 and
                 SSE4.2 instructions for both 32 and 64 bits. Now dissasembler
                 supports all the SSE instruction for both 32 and 64 bits.
01n,29apr10,pad  Moved extern C statement after include statements.
01m,15nov07,rlp  Modified the type of the instrOp field (CQ:WIND00111070).
01l,02mar07,jmp  added instrOp field to FORMAT_X structure in order to hide
		 persistent software breakpoints in disassembler.
01k,16mar04,md   Add output functions to dmsData() and dsmInst()
01j,01mar03,pai  Made the FORMAT_X & FORMAT_Y opcode data pointers point to
                 constant data.  Updated Copyright.
01i,16sep02,pai  Updated support for SSE2 & Pentium 4 instructions.
01h,30aug01,hdn  added SIMD, sysenter/exit support.
01g,06may98,fle  added P5 and P6 instructions and facilities
01f,14nov94,hdn  changed D->DISR, W->WFUL, S->SEXT, P->POP, A->AX, I->IMM.
	   +kdl  minor cleanup.
01e,29may94,hdn  removed I80486 conditional.
01d,31aug93,hdn  changed a type of pD, from char to UCHAR.
		 changed a type of 1st parameter, from char to UCHAR.
01c,07jun93,hdn  added support for c++
01b,26mar93,hdn  added new instructions for 486.
01a,23jun92,hdn  written. 
*/

#ifndef __INCdsmI86Libh
#define __INCdsmI86Libh

/* includes */

#include "vwModNum.h"
#include <stdio.h>

#ifdef BENCHTEST
#include "testBench.h"
#endif /* BENCHTEST */

#ifdef __cplusplus
extern "C" {
#endif

/* dsmLib status codes */

#define S_dsmLib_UNKNOWN_INSTRUCTION	(M_dsmLib | 1)

#define DSM_BUFSIZE16	(16)
#define DSM_BUFSIZE32	(32)
#define DSM_BUFSIZE48	(48)

#define PREFIX_2_COUNT     6

#define PREFIX_ADDR        0x67         /* Address size override prefix */         

#define PREFIX_REX         0x40
#define PREFIX_REX_MASK    0xF0

#define REXW_MASK	   0x08         /* rexW -64bit op size */
#define REXR_MASK          0x04         /* rexR -ext reg field */
#define REXX_MASK	   0x02         /* rexX -ext index field */
#define REXB_MASK	   0x01         /* rexB -ext base field */

#define VEX_PREFIX_3       0xc4         /* 3 bytes VEX prefix */
#define VEX_PREFIX_2       0xc5         /* 2 bytes VEX prefix */

#define VEX_VVVV_SHIFT     3
#define VEX_VVVV_MASK      0x78         /* vexVVVV -register specifier */
#define VEXL_MASK          0x04         /* vexL    -vector length */
#define VEXR_MASK          0x80         /* vexR    -ext reg field */
#define VEXX_MASK          0x40         /* vexX    -ext index field */
#define VEXB_MASK          0x20         /* vexB    -ext base field */
#define VEXW_MASK          0x80         /* vexW    -64bit op size */     
#define VEXPP_MASK         0x03         /* vexPP   -ext pp mask */     

/* instruction table opcode entry format */

typedef struct				/* INST */
    {
    const char * pOpc;			/* Instruction Name */
    UINT	 type;			/* instruction type */
    UINT	 flag;			/* instruction flag */
    UINT	 flag2;			/* instruction flag2 */
    UCHAR	 op0;			/* opcode 0         */
    UCHAR	 op1;			/* opcode 1         */
    UCHAR	 op2;			/* opcode 2         */
    UCHAR	 op3;			/* opcode 3         */
    UCHAR	 mask0;			/* mask 0           */
    UCHAR	 mask1;			/* mask 1           */
    UCHAR	 mask2;			/* mask 2           */
    UCHAR	 mask3;			/* mask 3           */
    } INST;

/* FORMAT_X - repository for data collection on opcode entry */

typedef struct				/* FORMAT_X */
    {
    const INST *  pI;			/* pointer to an INST descriptor */
    const char *  pD;			/* opcode data pointer */
    const char *  pOpc;			/* instruction name pointer */    
    UCHAR         prefix2;              /* Group 2 prefix value  */
    UCHAR         prefixAsize;          /* Group 4 prefix exists  0,1 */
    UINT	  instrOp;		/* instruction opcode */
    char	  obuf [DSM_BUFSIZE32];	/* instruction name buffer */
    _Vx_usr_arg_t addr;                 /* address to be used for print */
    char	  addr_size;		/* address size        0,1,2 */
    char	  data_size;		/* data size           0,1,2 */
    char	  lenP;			/* length of prefixes  */
    char	  lenO;			/* opcode length       1,2 */
    char	  lenD;			/* displacement length 0,1,2,4 */
    char	  lenI;			/* immediate length    0,1,2,4 */
    char	  modrm;		/* MODRM               0,1 */
    char	  sib;			/* SIB                 0,1 */
    UINT	  imm;		        /* IMM value               */
    char	  w;			/* W -data is byte or full-sized  0,1 */
    char	  d;			/* D -direction of data operation 0,1 */
    char	  s;			/* S -sign ext of immediate field 0,1 */
    char	  reg;			/* MODRM byte, reg bits 3,4,5, 8 bits */
    char	  mod;			/* MODRM byte, mod bits 6,7 */
    char	  rm;			/* MODRM byte, rm bits  0,1,2 */
    char	  ss;                   /* SIB byte, scale bits 6,7 */
    char	  index;                /* SIB byte, index bits 3.4.5 */
    char	  base;                 /* SIB byte, base bits  0,1,2 */
    char	  mf;
    char	  st;
    char	  fd;
    char          rex_prefix;           /*  the REX prefix is used    0,1 */
    char          rex_value;            /*  the REX prefix value */
    char          vex_vvvv_value;       /* VEX.vvvv value */
    char          vex_r_inv;            /* VEX.R inverted value     0,1 */ 
    char          vex_x_inv;            /* VEX.X inverted value     0,1 */ 
    char          vex_b_inv;            /* VEX.B inverted value     0,1 */
    char          vex_w;                /* VEX.W value     0,1 */
    char          vex_l;                /* VEX.L value     0,1 */
    char          vex_pp;               /* VEX.PP value    0-3 */
    } FORMAT_X;

/* FORMAT_Y - format data collected on opcode entry */

typedef struct				/* FORMAT_Y */
    {
    const char *  pD;			/* opcode data pointer */
    const char *  pOpc;			/* instruction name pointer */
    char *	  pOpr0;		/* output string 0 */
    char *	  pOpr1;		/* output string 1 */
    char *	  pOpr2;		/* output string 2 */
    char *	  pOpr3;		/* output string 3 */
    int		  len;			/* instruction length */
    _Vx_usr_arg_t addr;			/* address operand */
    char	  obuf [DSM_BUFSIZE16];	/* opcode buffer */
    char	  rbuf [DSM_BUFSIZE16];	/* register buffer */
    char	  mbuf [DSM_BUFSIZE32];	/* memory buffer */
    char	  temp [DSM_BUFSIZE32];	/* temporary buffer */
    char	  ibuf [DSM_BUFSIZE48];	/* immediate buffer, also used to hold RIP */
    char	  dbuf [DSM_BUFSIZE16];	/* displacement buffer */
    char	  vbuf [DSM_BUFSIZE16];	/* buffer for reg def'd in  VEX.vvvv */
    } FORMAT_Y;

/* bit definitions of flag */

/*
 * -/digiti, the reg field contains a digit between 0 and 7 that
 * provides an extension to the instruction's opcode
 */

#define DSM_SLSH_0    (0x00)
#define DSM_SLSH_1    (0x08)
#define DSM_SLSH_2    (0x10)
#define DSM_SLSH_3    (0x18)
#define DSM_SLSH_4    (0x20)
#define DSM_SLSH_5    (0x28)
#define DSM_SLSH_6    (0x30)
#define DSM_SLSH_7    (0x38)

/*
 *  7  6 5          3 2   0       
 * +-----------------------+        
 * | Mod |  Reg/Op   | R/M |   ModR/M 
 * +-----------------------+          
 */

#define MODRM_MOD     (0xc0)
#define MODRM_REG     (0x38)
#define MODRM_RM      (0x07)

#define DSM_REG       (0x03)
#define DSM_MOD       (0x06)

/*  
 *  7     6 5     3 2     0    
 * +-----------------------+ 
 * | Scale | Index | Base  |    SIB 
 * +-----------------------+
 */

#define SIB_SS        (0xc0)
#define SIB_INDEX     (0x38)
#define SIB_BASE      (0x07)

#define DSM_INDEX     (0x03)
#define DSM_SS        (0x06)

#define DSM_EXT       (0x08)

/*
 * MSB of flag byte is not included in switch statement used
 * to format the output.
 */

/* MODRM must be defined if REG, MMXREG, XMMREG are defined */

#define SF	(0x10000000)

#define OP1	(0x20000000)      /* 1 byte opcode format */
#define OP2	(0x40000000)      /* 2 byte opcode format */
#define OP3	(0x80000000)      /* 3 byte opcode format */

#define DSM_1B  (0x00000001)	  /* 1 byte(s) of data represents opcode */
#define DSM_2B  (0x00000002)	  /* 2 byte(s) of data represents opcode */
#define DSM_3B  (0x00000004)	  /* 3 byte(s) of data represents opcode */
#define DSM_4B  (0x00000008)	  /* 4 byte(s) of data represents opcode */
#define DSM_5B  (0x00000010)	  /* 5 byte(s) of data represents opcode */
#define DSM_6B  (0x00000020)	  /* 6 byte(s) of data represents opcode */

#define DSM_MXB (0x0000001f)	  /* range of byte(s) to represent opcode */
                                  /* (currently 1 thru 5)                 */

#define WFUL    (0x01000000)      /* operand size bit */
#define SEXT    (0x02000000)      /* sign extend flag */
#define DISR    (0x04000000)      /* data direction info encoded in opcode */
#define TTT     (0x08000000)      /* hack to look for rotate instructions */

#define TTTN    (0x00100000)      /* opcode least significant byte 
				   * bits 0-4 = condition test field */
#define MF      (0x00200000)      /* opcode bits 1-2 are = register size info */
#define POP     (0x00400000)      /* cat a "P" to end of instruction name */

#define IMM     (0x00000001)
#define I8      (0x00000002)      /* imm8 byte exists */

#define DIS     (0x00000004)      /* displacement info */
#define D8      (0x00000008)      /* displacement info */
#define D16     (0x00000010)      /* displacement info */

#define AX      (0x00000020)      /* store into AX register */
#define CL      (0x00000040)      /* cat "CL" to end of operands */

#define REG     (0x00000080)      /* modrm bits 3-5 = register specifier */
#define SREG2   (0x00000100)      /* modrm bits 3-4 = 2 bit segment register */
#define SREG3   (0x00000200)      /* modrm bits 3-5 = 3 bit segment register */
#define MODRM   (0x00000400)      /* modrm byte exists */
#define EEE     (0x00000800)      /* modrm bits 3-5 = control/debug register */
#define REGRM   (0x00001000)      /* modrm bits 0-2 = register specifier */

#define PORT    (0x00002000)      /* use a port as an operand */

#define OFFSEL  (0x00004000)      /* jump or call offset */

#define D16L8   (0x00008000)      /* displacement info */

#define FD      (0x00010000)      /* stack element is destination */
#define ST      (0x00020000)      /* stack element is operand */

#define MMXRM   (0x00040000)      /* modrm bits 0-2 = MMX register */
#define MMXREG  (0x00080000)      /* modrm bits 3-5 = MMX register */

#define GG      (0x00800000)      /* least sign opcode byte 
				   * bits 0-1 = MMX granularity    */

/* bit definitions of flag2 */

#define XMMRM   (0x00000001)      /* modrm bits 0-2 = XMM register */
#define XMMREG  (0x00000002)      /* modrm bits 3-5 = XMM register */

#define DIR0    (0x00000004)      /* location of instruction dir */
#define DIR1    (0x00000008)      /* location of instruction dir */

#define GG_F    (0x00000010)      /* granularity of floating instructions */
#define GG_2    (0x00000020)      /* granularity of SSE 4.1 instructions  */
#define GG_4_1  (0x00000040)      /* granularity of SSE 4.1 instructions  */

#define REX     (0x80000000)      /* REX prefix is used   */

#define AVX     (0x40000000)      /* AVX instruction   */

#define VVVV    (0x20000000)      /* VVVV field of AVX instruction is used  */

#define DIR_R   (0x08000000)      /* reverse the direction  */

#define ESC     (0xd8)            /* for co-processor instructions */

/* instruction types */

#define		itAaa 			 1
#define		itAad       		 2
#define		itAam       		 3
#define		itAas       		 4
#define		itAddItoA   		 5
#define		itAddItoRM  		 6
#define		itAddRMtoRM		 7
#define		itAndItoA   		 8
#define		itAndItoRM  		 9
#define		itAndRMtoRM		10
#define		itArpl     		11
#define		itAsize   		12
#define		itBound   		13
#define		itBsf       		14
#define		itBsr       		15
#define		itBtI        		16
#define		itBtR        		17
#define		itBtcI      		18
#define		itBtcR      		19
#define		itBtrI      		20
#define		itBtrR      		21
#define		itBtsI      		22
#define		itBtsR      		23
#define		itCall     		24
#define		itCallRM   		25
#define		itCallSeg  		26
#define		itCallSegRM		27
#define		itCbw       		28
#define		itCjmp   		29
#define		itClc       		30
#define		itCld       		31
#define		itCli       		32
#define		itClts     		33
#define		itCmc       		34
#define		itCmpIwiA   		35
#define		itCmpIwiRM  		36
#define		itCmpRMwiRM		37
#define		itCmps     		38
#define		itCs         		39
#define		itCset     		40
#define		itCwd       		41
#define		itDaa       		42
#define		itDas       		43
#define		itDecR      		44
#define		itDecRM     		45
#define		itDiv       		46
#define		itDs         		47
#define		itEnter   		48
#define		itEs         		49
#define		itFs         		50
#define		itGs         		51
#define		itHlt       		52
#define		itIdiv     		53
#define		itImulAwiRM		54
#define		itImulRMwiI		55
#define		itImulRwiRM		56
#define		itInF        		57
#define		itInV        		58
#define		itIncR      		59
#define		itIncRM     		60
#define		itIns       		61
#define		itInt       		62
#define		itInt3      		63
#define		itInto     		64
#define		itIret     		65
#define		itJcxz     		66
#define		itJmpD      		67
#define		itJmpRM     		68
#define		itJmpS      		69
#define		itJmpSeg    		70
#define		itJmpSegRM  		71
#define		itLahf     		72
#define		itLar       		73
#define		itLds       		74
#define		itLea       		75
#define		itLeave   		76
#define		itLes       		77
#define		itLfs       		78
#define		itLgdt     		79
#define		itLgs       		80
#define		itLidt     		81
#define		itLldt     		82
#define		itLmsw     		83
#define		itLock     		84
#define		itLods     		85
#define		itLoop     		86
#define		itLoopnz		87
#define		itLoopz   		88
#define		itLsl       		89
#define		itLss       		90
#define		itLtr       		91
#define		itMovAMtoMA 		92
#define		itMovC      		93
#define		itMovD      		94
#define		itMovItoR   		95
#define		itMovItoRM  		96
#define		itMovRMtoMR  		97
#define		itMovRMtoS  		98
#define		itMovRtoRM  		99
#define		itMovStoRM  		100
#define		itMovT      		101
#define		itMovs     		102
#define		itMovsx   		103
#define		itMovzx   		104
#define		itMulAwiRM  		105
#define		itNeg       		106
#define		itNop       		107
#define		itNopMb     		108
#define		itNot       		109
#define		itOrItoA    		110
#define		itOrItoRM   		111
#define		itOrRMtoRM  		113
#define		itOsize   		115
#define		itOutF      		116
#define		itOutV      		117
#define		itOuts     		118
#define		itPopR      		119
#define		itPopRM     		120
#define		itPopS      		121
#define		itPopa     		122
#define		itPopf     		123
#define		itPushI    		124
#define		itPushR    		125
#define		itPushRM   		126
#define		itPushS    		127
#define		itPusha   		128
#define		itPushf   		129
#define		itRNcmps		130
#define		itRNscas		131
#define		itRcmps   		132
#define		itRet       		133
#define		itRetI      		134
#define		itRetSeg    		135
#define		itRetSegI   		136
#define		itRins      		137
#define		itRlods    		138
#define		itRmovs    		139
#define		itRolRMby1		140
#define		itRolRMbyCL		141
#define		itRolRMbyI		142
#define		itRouts    		143
#define		itRscas   		144
#define		itRstos    		145
#define		itSahf     		146
#define		itSbbIfrA   		147
#define		itSbbIfrRM  		148
#define		itSbbRMfrRM		149
#define		itScas     		150
#define		itSgdt     		151
#define		itShldRMbyCL		152
#define		itShldRMbyI		153
#define		itShrdRMbyCL		154
#define		itShrdRMbyI		155
#define		itSmsw     		156
#define		itSs         		157
#define		itStc       		158
#define		itStd       		159
#define		itSti       		160
#define		itStos     		161
#define		itStr      		162
#define		itSubIfrA   		164
#define		itSubIfrRM  		165
#define		itSubRMfrRM		166
#define		itTestIanA 		167
#define		itTestIanRM		168
#define		itTestRManR		169
#define		itWait     		170
#define		itXchgA    		171
#define		itXchgRM   		172
#define		itXlat     		173

/* instructions for 387 */

#define		itF2xm1			174
#define		itFabs			175
#define		itFaddIRM		176
#define		itFaddST		177
#define		itFchs			178
#define		itFclex			179
#define		itFcomIRM		180
#define		itFcomST		181
#define		itFcompIRM		182
#define		itFcompST		183
#define		itFcompp		184
#define		itFcos			185
#define		itFdecstp		186
#define		itFdivIRM		187
#define		itFdivST		188
#define		itFfree			189
#define		itFincstp		190
#define		itFinit			191
#define		itFld1			192
#define		itFldBCDM		193
#define		itFldERM		194
#define		itFldIRM		195
#define		itFldL2E		196
#define		itFldL2T		197
#define		itFldLG2		198
#define		itFldLIM		199
#define		itFldLN2		200
#define		itFldPI			201
#define		itFldST			202
#define		itFldZ			203
#define		itFldcw			204
#define		itFldenv		205
#define		itFmulIRM		206
#define		itFmulST		207
#define		itFnop			208
#define		itFpatan		209
#define		itFprem			210
#define		itFprem1		211
#define		itFptan			212
#define		itFrndint		213
#define		itFrstor		214
#define		itFsave			215
#define		itFscale		216
#define		itFsin			217
#define		itFsincos		218
#define		itFsqrt			219
#define		itFstIRM		220
#define		itFstST			221
#define		itFstcw			222
#define		itFstenv		223
#define		itFstpBCDM		224
#define		itFstpERM		225
#define		itFstpIRM		226
#define		itFstpLIM		227
#define		itFstpST		228
#define		itFstsw			229
#define		itFstswA		230
#define		itFsubIRM		231
#define		itFsubST		232
#define		itFtst			233
#define		itFucom			234
#define		itFucomp		235
#define		itFucompp		236
#define		itFxam			237
#define		itFxch			238
#define		itFxtract		239
#define		itFyl2x			240
#define		itFyl2xp1		241
#define		itFcmovb		242
#define		itFcmove		243
#define		itFcmovbe		244
#define		itFcmovu		245
#define		itFcmovnb		246
#define		itFcmovne		247
#define		itFcmovnbe		248
#define		itFcmovnu		249
#define		itFcomi			250
#define		itFucomi		251
#define		itFcomip		252
#define		itFucomip		253

/* addendum */

#define		itSidt			300
#define		itSldt			301
#define		itVerr			302
#define		itVerw			303
#define		itXorItoRM		304
#define		itAdcItoRM		305
#define		itXorItoA		306
#define		itAdcItoA		307
#define		itXorRMtoRM		308
#define		itAdcRMtoRM		309
#define		itRep			310
#define		itRepNe			311

/* 80486 instructions */

#define		itBswap			400
#define		itCmpxchg		401
#define		itXadd			402
#define		itInvd			403
#define		itWbinvd		404
#define		itInvlpg		405

/* P5 instructions */

#define		itCmpxchg8b		500
#define		itCpuid			501
#define		itRdtsc			502
#define		itRdmsr			503
#define		itWrmsr			504
#define		itRsm			505

/* P6 instructions */

#define		itCmovcc		600
#define		itRdpmc			601
#define		itUd2			602
#define         itSysenter              603
#define         itSysexit               604

/* MMX/SSE2 instructions */

#define		itEmms			700
#define		itMovd			701
#define		itMovq			702
#define		itPackssdw		703
#define		itPacksswb		704
#define		itPackuswb		705
#define		itPadd			706
#define		itPaddq			707
#define		itPadds			708
#define		itPaddus		709
#define		itPand			710
#define		itPandn			711
#define		itPcmpeq		712
#define		itPcmpgt		713
#define		itPmadd			714
#define		itPmulh			715
#define		itPmull			716
#define		itPor			717
#define		itPsll			718
#define		itPsra			719
#define		itPsrl			720
#define		itPsub			721
#define		itPsubs			722
#define		itPsubus		723
#define		itPunpckh		724
#define		itPunpckl		725
#define		itPxor			726

/* SSE/SSE2 instructions */

#define         itAddpd                 800
#define         itAddps                 801
#define         itAddsd                 802
#define         itAddss                 803
#define         itAndnpd                804
#define         itAndnps                805
#define         itAndpd                 806
#define         itAndps                 807
#define         itCmppd                 821
#define         itCmpps                 822
#define         itCmpsd                 823
#define         itCmpss                 824
#define         itComisd                826
#define         itComiss                827
#define         itCvtdq2pd              828
#define         itCvtdq2ps              829
#define         itCvtpd2dq              830
#define         itCvtpd2ps              831
#define         itCvtpi2pd              832
#define         itCvtpi2ps              833
#define         itCvtps2dq              834
#define         itCvtps2pd              835
#define         itCvtps2pi              836
#define         itCvtsd2si              837
#define         itCvtsd2ss              838
#define         itCvtsi2sd              839
#define         itCvtsi2ss              840
#define         itCvtss2sd              841
#define         itCvtss2si              842
#define         itCvttpd2dq             843
#define         itCvttpd2pi             844
#define         itCvttps2dq             845
#define         itCvttps2pi             846
#define         itCvttsd2si             847
#define         itCvttss2si             848
#define         itDivpd                 849
#define         itDivps                 850
#define         itDivsd                 851
#define         itDivss                 852
#define         itFxrstor               853
#define         itFxsave                854
#define         itLdmxcsr               855
#define         itMaskmovdqu            856
#define         itMaskmovq              857
#define         itMaxpd                 858
#define         itMaxps                 859
#define         itMaxsd                 860
#define         itMaxss                 861
#define         itMinpd                 862
#define         itMinps                 863
#define         itMinsd                 864
#define         itMinss                 865
#define         itMovapd                866
#define         itMovaps                867
#define         itMovdq2q               868
#define         itMovdqa                869
#define         itMovdqu                870
#define         itMovhlps               871
#define         itMovhpd                872
#define         itMovhps                873
#define         itMovlhps               874
#define         itMovlpd                875
#define         itMovlps                876
#define         itMovmskpd              877
#define         itMovmskps              878
#define         itMovntdq               879
#define         itMovntpd               880
#define         itMovntps               881
#define         itMovntq                882
#define         itMovq2dq               883
#define         itMovsd                 884
#define         itMovss                 885
#define         itMovshdup              886
#define         itMovsldup              887
#define         itMovupd                888
#define         itMovups                889
#define         itMulpd                 890
#define         itMulps                 891
#define         itMulsd                 892
#define         itMulss                 893
#define         itOrpd                  894
#define         itOrps                  895
#define         itPavgb                 896
#define         itPavgw                 897
#define         itPextrw                898
#define         itPinsrw                899
#define         itPmaxsw                900
#define         itPmaxub                901
#define         itPminsw                902
#define         itPminub                903
#define         itPmovmskb              904
#define         itPmulhuw               905
#define         itPmuludq               906
#define         itPrefetchnta           907
#define         itPrefetcht0            908
#define         itPrefetcht1            909
#define         itPrefetcht2            910
#define         itPsadbw                911
#define         itPshufd                912
#define         itPshufhw               913
#define         itPshuflw               914
#define         itPshufw                915
#define         itPslldq                916
#define         itPsrldq                917
#define         itPunpckhqdq            918
#define         itPunpcklqdq            919
#define         itRcpps                 920
#define         itRcpss                 921
#define         itRsqrtps               922
#define         itRsqrtss               923
#define         itSfence                924
#define         itShufps                925
#define         itShufpd                996
#define         itSqrtpd                927
#define         itSqrtps                928
#define         itSqrtsd                929
#define         itSqrtss                930
#define         itStmxcsr               931
#define         itSubpd                 932
#define         itSubps                 933
#define         itSubsd                 934
#define         itSubss                 935
#define         itUcomisd               936
#define         itUcomiss               937
#define         itUnpckhpd              938
#define         itUnpckhps              939
#define         itUnpcklpd              940
#define         itUnpcklps              941
#define         itXorpd                 942
#define         itXorps                 943

/* SSE3 instructions */

#define         itAddSubPD              1100
#define         itAddSubPS              1101
#define		itHaddpd                1102
#define		itHaddps                1103
#define		itHsubpd                1104
#define		itHsubps                1105
#define		itLddqu                 1110
#define		itMovddup               1111
#define		itPabs                  1112
#define		itPhadd                 1113
#define		itPhaddsw               1114
#define         itPalignr               1115
#define		itPhsub                 1116
#define		itPhsubsw               1117
#define		itPmaddubsw             1118
#define		itPmulhrsw              1119
#define		itPshufb                1120
#define		itPsign                 1121

/* SSE4 instructions */

#define         itBlend                 2101
#define         itBlendv                2102
#define         itDp                    2103
#define         itExtractps             2104
#define         itInsertps              2105
#define         itMovntdqa              2106
#define         itMpsadbw               2107
#define         itPackusdw              2108
#define         itPblendvb              2109
#define         itPblendW               2110
#define         itPcmpeqq               2111
#define         itPcmpestri             2112
#define         itPcmpestrm             2113
#define         itPcmpgtq               2114
#define         itPcmpistri             2115
#define         itPcmpistrm             2116
#define         itPextr                 2117
#define         itPhminposuw            2118
#define         itPinsr                 2119
#define         itPmaxsb                2120
#define         itPmaxsd                2121
#define         itPmaxud                2122
#define         itPmaxuw                2123
#define         itPminsb                2124
#define         itPminsd                2125
#define         itPminud                2126
#define         itPminuw                2127
#define         itPmovsx                2128
#define         itPmovzx                2129
#define         itPmulld                2130
#define         itPmuldq                2131
#define         itPtest                 2132
#define         itRound                 2133

/* 64 bits SSE to SSE 4 instructions */

#define		itCrc32R  		4000
#define         itCvtsd2siR             4001            
#define         itCvtsi2sdR             4002
#define         itCvtsi2ssR             4003
#define         itCvtss2siR             4004
#define         itCvttsd2siR            4005
#define         itCvttss2siR            4006
#define         itP05                   4007
#define		itPopcntR		4008

/* Pentium 4 instructions */

#define		itClflush		1000
#define		itCrc32  		1001
#define		itLfence		1002
#define		itMfence		1003
#define		itMovnti		1004
#define		itPause			1005
#define		itPopcnt		1006
#define		itRdtscp		1007
#define		itSwapgs		1008
#define		itSyscall		1009
#define		itSysret		1010
#define		itXrstor		1011
#define		itXsave 		1012
#define		itXgetbv		1013
#define		itXsetbv		1014

/* Encription instructions */

#define         itPclmulqdq             3108

  /* AES instructions */

#define         itAesdec                3400
#define         itAesdeclast            3401
#define         itAesenc                3402
#define         itAesenclast            3403
#define         itAesimc                3404
#define         itAeskeygenassist       3405
#define         itvAesdec               3450
#define         itvAesdeclast           3451
#define         itvAesenc               3452
#define         itvAesenclast           3453
#define         itvAesimc               3454
#define         itvAeskeygenassist      3455

/* AVX  instructions */

#define         itvAdd                  5000
#define         itvAddsub               5001
#define         itvAnd                  5002
#define         itvAndn                 5003
#define         itvBlend                5004
#define         itvBlendv               5005
#define         itvBroadcastf128        5006
#define         itvBroadcast            5007
#define         itvDiv                  5008
#define         itvDpp                  5009
#define         itvCmp_1                5010
#define         itvCmp_2                5011
#define         itvComisd               5012
#define         itvComiss               5013
#define         itvCvtdq2pd             5014
#define         itvCvtdq2ps             5015
#define         itvCvtsd2si             5016
#define         itvCvtsd2ss             5017
#define         itvCvtsi2_1             5018
#define         itvCvtsi2_2             5019
#define         itvCvtss2sd             5020
#define         itvCvtss2si             5021
#define         itvCvtpd2dq             5022
#define         itvCvtpd2ps             5023
#define         itvCvtps2dq             5024
#define         itvCvtps2pd             5025
#define         itvCvttsd2si            5026
#define         itvCvttss2si            5027
#define         itvCvttpd2dq            5028
#define         itvCvttps2dq            5029
#define         itvExtractf128          5030
#define         itvExtractps            5031
#define         itvHadd                 5032
#define         itvHsub                 5033
#define         itvInsertf128           5034
#define         itvInsertps             5035
#define         itvLddqu                5036
#define         itvLdmxcsr              5037
#define         itvLdStMxcsr            5038
#define         itvMaskmov              5039
#define         itvMaskmovdqu           5040
#define         itvMax                  5041
#define         itvMin                  5042
#define         itvMov_1                5043
#define         itvMov_2                5044
#define         itvMova_1               5045
#define         itvMova_2               5046
#define         itvMovd                 5047
#define         itvMovddup              5048
#define         itvMovdqa               5049
#define         itvMovdqu               5050
#define         itvMovq                 5051
#define         itvMovhlps              5052
#define         itvMov_0x12             5053
#define         itvMov_0x16             5054
#define         itvMovh_1               5055
#define         itvMovh_2               5056
#define         itvMovl_1               5057
#define         itvMovl_2               5058
#define         itvMovlhps              5059
#define         itvMovmsk               5060
#define         itvMovnt                5061
#define         itvMovntdq              5062
#define         itvMovntdqa             5063
#define         itvMovshdup             5064
#define         itvMovsldup             5065
#define         itvMovu_1               5066
#define         itvMovu_2               5067
#define         itvMul                  5075
#define         itvMpsadbw              5076
#define         itvOr                   5077
#define         itvPabs                 5078
#define         itvPadd                 5079
#define         itvPaddq                5080
#define         itvPadds                5081
#define         itvPaddus               5082
#define         itvPalignr              5083
#define         itvPackssdw             5084
#define         itvPacksswb             5085
#define         itvPackusdw             5086
#define         itvPackuswb             5087
#define         itvPand                 5088
#define         itvPandn                5089
#define         itvPavgb                5090
#define         itvPavgw                5091
#define         itvPblendvb             5092
#define         itvPblendw              5093
#define         itvPcmulqdq             5094
#define         itvPerm2f128            5095
#define         itvPermil1              5096
#define         itvPermil2              5097
#define         itvPextr                5098
#define         itvPextrw               5099
#define         itvPhadd                5100
#define         itvPhaddsw              5101
#define         itvPhminposuw           5102
#define         itvPhsub                5103
#define         itvPhsubsw              5104
#define         itvPinsrb               5105
#define         itvPinsrd               5106
#define         itvPinsrq               5107
#define         itvPinsrw               5108
#define         itvPmaddwd              5109
#define         itvPmaddubsw            5110
#define         itvPmaxsb               5111
#define         itvPmaxsd               5112
#define         itvPmaxsw               5113
#define         itvPmaxub               5114
#define         itvPmaxuw               5115
#define         itvPmaxud               5116
#define         itvPminsb               5117
#define         itvPminsd               5118
#define         itvPminsw               5119
#define         itvPminub               5130
#define         itvPminud               5131
#define         itvPminuw               5132
#define         itvPcmpeq               5133
#define         itvPcmpeqq              5134
#define         itvPcmpestri            5135
#define         itvPcmpestrm            5136
#define         itvPcmpgt               5137
#define         itvPcmpgtq              5138
#define         itvPcmpistri            5139           
#define         itvPcmpistrm            5140
#define         itvPmovmskb             5150
#define         itvPmovsx               5151
#define         itvPmovzx               5152
#define         itvPmuldq               5153
#define         itvPmulhrsw             5154
#define         itvPmulhw               5155
#define         itvPmulhuw              5156
#define         itvPmullw               5157
#define         itvPmulld               5158
#define         itvPmuludq              5159
#define         itvPor                  5160
#define         itvPsadbw               5161
#define         itvPShufb               5162
#define         itvPShufd               5163
#define         itvPShufhw              5164
#define         itvPShuflw              5165
#define         itvPsign                5166
#define         itvPsll_1               5167
#define         itvPsll_2               5168
#define         itvPsll_Psrl_Psra       5169
#define         itvPslldq               5170
#define         itvPsra_1               5171
#define         itvPsra_2               5172
#define         itvPsrl_1               5173
#define         itvPsrl_2               5174
#define         itvPsrldq               5175
#define         itvPsub                 5176
#define         itvPsubs                5177
#define         itvPsubus               5178
#define         itvPtest                5179
#define         itvPunpckh              5180
#define         itvPunpckhqdq           5181
#define         itvPunpckl              5182
#define         itvPunpcklqdq           5190
#define         itvPxor                 5191
#define         itvRcpps                5192
#define         itvRcpss                5193
#define         itvRsqrtss              5194
#define         itvRsqrtps              5195
#define         itvRound                5196
#define         itvShuf                 5197
#define         itvStmxcsr              5198
#define         itvSqrt                 5200
#define         itvSub                  5201
#define         itvTest                 5202
#define         itvUcomisd              5203
#define         itvUcomiss              5204
#define         itvUnpckh               5205
#define         itvUnpckl               5206
#define         itvXor                  5207
#define         itvZeroall              5208
#define         itvZeroupper            5209

typedef void (*NPRTADDRESS_OUTPUT_FUNCPTR)
	(_Vx_usr_arg_t, OPRINTF_OUTPUT_FUNCPTR, _Vx_usr_arg_t);

/* function declarations */

#if defined (__STDC__) || defined (__cplusplus)

IMPORT int dsmData (UCHAR * pD, 
		    _Vx_usr_arg_t address, 
		    OPRINTF_OUTPUT_FUNCPTR oFn, 
		    _Vx_usr_arg_t oArg);

IMPORT int dsmInst (UCHAR * pD, 
		    _Vx_usr_arg_t address, 
		    NPRTADDRESS_OUTPUT_FUNCPTR prtAddress, 
		    OPRINTF_OUTPUT_FUNCPTR oFn, 
		    _Vx_usr_arg_t oArg);

IMPORT int dsmNbytes (UCHAR * pD);

#else

IMPORT int dsmData ();
IMPORT int dsmInst ();
IMPORT int dsmNbytes ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmI86Libh */
