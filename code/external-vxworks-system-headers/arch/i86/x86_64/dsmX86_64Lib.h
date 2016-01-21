/* dsmX86_64Lib.h - x86_64 disassembler header */

/*
 * Copyright (c) 2009, 2010 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01f,16sep10,mcm  Get OPRINTF_OUTPUT_FUNCPTR prototype from stdio.h
01e,29apr10,pad  Moved extern C statement after include statements.
01d,02sep09,scm  clean up new compiler warnings...
01c,30jun09,scm  resolve FUNCPTR...
01b,05may09,scm  make 64bit compliant...
01a,10feb09,jb   Created from 32-bit version 01m
*/

#ifndef __INCdsmX86_64Libh
#define __INCdsmX86_64Libh

/* includes */

#include <vwModNum.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* dsmLib status codes */

#define S_dsmLib_UNKNOWN_INSTRUCTION	(M_dsmLib | 1)

#define DSM_BUFSIZE16	(16)
#define DSM_BUFSIZE32	(32)
#define DSM_BUFSIZE64	(64)

/* instruction table opcode entry format */

typedef struct				/* INST */
    {
    char        *pOpc;			/* Instruction Name */
    UINT	 type;			/* instruction type */
    UINT	 flag;			/* instruction flag */
    UINT	 flag2;			/* instruction flag2 */
    UINT	 flag3;			/* instruction flag2 */
    UCHAR	 op0;			/* opcode 0         */
    UCHAR	 op1;			/* opcode 1         */
    UCHAR	 op2;			/* opcode 2         */
    UCHAR	 op3;			/* opcode 3         */
    UCHAR	 op4;			/* opcode 4         */
    UCHAR	 op5;			/* opcode 5         */
    UCHAR	 mask0;			/* mask 0           */
    UCHAR	 mask1;			/* mask 1           */
    UCHAR	 mask2;			/* mask 2           */
    UCHAR	 mask3;			/* mask 3           */
    UCHAR	 mask4;			/* mask 4           */
    UCHAR	 mask5;			/* mask 5           */
    } INST;

/* FORMAT_X - repository for data collection on opcode entry */

typedef struct				/* FORMAT_X */
    {
    INST	*pI;			/* pointer to an INST descriptor */
    char	*pD;			/* opcode data pointer */
    char	*pOpc;			/* instruction name pointer */
    char	*pRx;			/* REX prefix name pointer */
    BOOL	 prefixRex;             /* prefix REX, 0x40 - 0x4f */
    UINT  	 instrOp;		/* instruction opcode */
    UINT  	 rexOp;			/* REX prefix opcode */
    size_t	 pOpcLen;		/* len of instruction + prefix string */
    char	 obuf [DSM_BUFSIZE32];	/* instruction name buffer */
    char	 rxbuf [DSM_BUFSIZE16];	/* REX prefix name buffer */
    int 	 a64;			/* address size        0,1,2 */
    int 	 d64;			/* data size           0,1,2 */
    int 	 lenO;			/* opcode length       1,2,3 */
    int 	 lenD;			/* displacement length 0,1,2,4 */
    int 	 lenI;			/* immediate length    0,1,2,4 */
    int 	 modrm;			/* MODRM byte present  0,1 */
    int 	 sib;			/* SIB byte present    0,1 */
    int  	 w;	                /* W -data is byte or full-sized  0,1 */
    int 	 d;	                /* D -direction of data operation 0,1 */
    int 	 s;	                /* S -sign ext of immediate field 0,1 */
    int 	 mod;			/* MODRM byte, mod bits 6,7 */
    int 	 reg;			/* MODRM byte, reg bits 3,4,5, 8 bits */
    int 	 rm;			/* MODRM byte, rm bits  0,1,2 */
    int 	 ss;                    /* SIB byte, scale bits 6,7 */
    int 	 index;                 /* SIB byte, index bits 3.4.5 */
    int 	 base;                  /* SIB byte, base bits  0,1,2 */
    int 	 mf;
    int 	 st;
    int 	 fd;
    int          rexW;			/* rexW -64bit op size:   0,1 */
    int          rexR;			/* rexR -ext reg field:   0,1 */
    int          rexX;			/* rexX -ext index field: 0,1 */
    int          rexB;			/* rexB -ext base field:  0,1 */
    } FORMAT_X;

/* FORMAT_Y - format data collected on opcode entry */

typedef struct				/* FORMAT_Y */
    {
    char	 *pD;			/* opcode data pointer */
    char	 *pOpc;			/* instruction name pointer */
    char	 *pOpr0;		/* output string 0 */
    char	 *pOpr1;		/* output string 1 */
    char	 *pOpr2;		/* output string 2 */
    int		  len;			/* instruction length */
    _Vx_usr_arg_t addr;			/* address operand */
    char	  obuf [DSM_BUFSIZE32];	/* opcode buffer */
    char	  rbuf [DSM_BUFSIZE16];	/* register buffer */
    char	  mbuf [DSM_BUFSIZE32];	/* memory buffer */
    char	  temp [DSM_BUFSIZE32];	/* temporary buffer */
    char	  ibuf [DSM_BUFSIZE16];	/* immediate buffer */
    char	  dbuf [DSM_BUFSIZE16];	/* displacement buffer */
    } FORMAT_Y;

/* bit definitions */

/* -/digiti, the reg field contains a digit betweeb 0 and 7 that
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

#define SIB_SS      (0xc0)
#define SIB_INDEX   (0x38)
#define SIB_BASE    (0x07)

#define DSM_INDEX   (0x03)
#define DSM_SS      (0x06)

/* REX prefix bits: "0100_WRXB", 0x40 thru 0x4F */

/* NOTE: REX prefixes that promote legacy instructions to 64-bit behavior
 * are not listed explicitly in the opcode column.
 */

#define REX     (0x40)

#define REXB	(0x01)
#define REXX	(0x02)
#define REXR	(0x04)
#define REXW	(0x08)

#define DSM_EXT (0x08)

/* MSB of flag byte is not included in switch statement used
 * to format the output.
 */

/* MODRM must be defined if REG, MMXREG, XMMREG are defined */

#define SF	(0x10000000)

#define OP1	(0x20000000)	 /* 1 byte opcode format */
#define OP2	(0x40000000)	 /* 2 byte opcode format */
#define OP3	(0x80000000)	 /* 3 byte opcode format */

#define DSM_1B  (0x00000001)	 /* 1 byte(s) of data represents opcode */
#define DSM_2B  (0x00000002)	 /* 2 byte(s) of data represents opcode */
#define DSM_3B  (0x00000004)	 /* 3 byte(s) of data represents opcode */
#define DSM_4B  (0x00000008)	 /* 4 byte(s) of data represents opcode */
#define DSM_5B  (0x00000010)	 /* 5 byte(s) of data represents opcode */
#define DSM_6B  (0x00000020)	 /* 6 byte(s) of data represents opcode */

#define DSM_MXB (0x0000001f)	 /* range of byte(s) used to represent opcode */
                                 /* (currently 1 thru 5)                      */

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

#define INS64   (0x00004000)      /* 64 bit instruction */

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

#define ESC     (0xd8)            /* for co-processor instructions */

/* instruction types */

#define		itAddItoA   		 1
#define		itAddItoRM  		 2
#define		itAddRMtoRM		 3
#define		itAndItoA   		 4
#define		itAndItoRM  		 5
#define		itAndRMtoRM		 6
#define		itAsize   		 7
#define		itBound   		 8
#define		itBsf       		 9
#define		itBsr       		10
#define		itBtI        		11
#define		itBtR        		12
#define		itBtcI      		13
#define		itBtcR      		14
#define		itBtrI      		15
#define		itBtrR      		16
#define		itBtsI      		17
#define		itBtsR      		18
#define		itCall     		19
#define		itCallRM   		20
#define		itCallSegRM		21
#define		itCbw       		22
#define		itCjmp   		23
#define		itClc       		24
#define		itCld       		25
#define		itCli       		26
#define		itClts     		27
#define		itCmc       		28
#define		itCmpIwiA   		29
#define		itCmpIwiRM  		30
#define		itCmpRMwiRM		31
#define		itCmps     		32
#define		itCs         		33
#define		itCset     		34
#define		itCwd       		35
#define		itDecRM     		36
#define		itDiv       		37
#define		itDs         		38
#define		itEnter   		39
#define		itEs         		40
#define		itFs         		41
#define		itGs         		42
#define		itHlt       		43
#define		itIdiv     		44
#define		itImulAwiRM		45
#define		itImulRMwiI		46
#define		itImulRwiRM		47
#define		itInF        		48
#define		itInV        		49
#define		itIncRM     		50
#define		itIns       		51
#define		itInt       		52
#define		itInt3      		53
#define		itIret     		54
#define		itJcxz     		55
#define		itJmpD      		56
#define		itJmpRM     		57
#define		itJmpS      		58
#define		itJmpSegRM  		59
#define		itLar       		60
#define		itLea       		61
#define		itLeave   		62
#define		itLfs       		63
#define		itLgdt     		64
#define		itLgs       		65
#define		itLidt     		66
#define		itLldt     		67
#define		itLmsw     		68
#define		itLock     		69
#define		itLods     		70
#define		itLoop     		71
#define		itLoopnz		72
#define		itLoopz   		73
#define		itLsl       		74
#define		itLss       		75
#define		itLtr       		76
#define		itMovAMtoMA 		77
#define		itMovC      		78
#define		itMovD      		79
#define		itMovItoR   		80
#define		itMovItoRM  		81
#define		itMovRMtoMR  		82
#define		itMovRMtoS  		83
#define		itMovRtoRM  		84
#define		itMovStoRM  		85 
#define		itMovT      		86 
#define		itMovs     		87 
#define		itMovsx   		88 
#define		itMovsxd   		89 
#define		itMovzx   		90 
#define		itMulAwiRM  		91 
#define		itNeg       		92 
#define		itNop       		93 
#define		itNot       		94 
#define		itOrItoA    		95 
#define		itOrItoRM   		96 
#define		itOrRMtoRM  		97 
#define		itOsize   		98 
#define		itOutF      		99 
#define		itOutV      		100
#define		itOuts     		101
#define		itPopS      		102
#define		itPopR      		103
#define		itPopRM     		104
#define		itPopf     		105
#define		itPushS    		106
#define		itPushI    		107
#define		itPushR    		108
#define		itPushRM   		109
#define		itPushf   		110
#define		itRNcmps		111
#define		itRNscas		112
#define		itRcmps   		113
#define		itRet       		114
#define		itRetI      		115
#define		itRetSeg    		116
#define		itRetSegI   		117
#define		itRins      		118
#define		itRlods    		119
#define		itRmovs    		120
#define		itRolRMby1		121
#define		itRolRMbyCL		122
#define		itRolRMbyI		123
#define		itRouts    		124
#define		itRscas   		125
#define		itRstos    		126
#define		itSbbIfrA   		127
#define		itSbbIfrRM  		128
#define		itSbbRMfrRM		129
#define		itScas     		130
#define		itSgdt     		131
#define		itShldRMbyCL		132
#define		itShldRMbyI		133 
#define		itShrdRMbyCL		134
#define		itShrdRMbyI		135
#define		itSmsw     		136
#define		itSs         		137
#define		itStc       		138
#define		itStd       		139
#define		itSti       		140
#define		itStos     		141
#define		itStr      		142
#define		itSubIfrA   		143
#define		itSubIfrRM  		144
#define		itSubRMfrRM		145
#define		itTestIanA 		146
#define		itTestIanRM		147
#define		itTestRManR		148
#define		itWait     		149
#define		itXchgA    		150
#define		itXchgRM   		151
#define		itXlat     		152

/* instructions for 387 */

#define		itF2xm1			200
#define		itFabs			201
#define		itFaddIRM		202
#define		itFaddST		203
#define		itFchs			204
#define		itFclex			205
#define		itFcomIRM		206
#define		itFcomST		207
#define		itFcompIRM		208
#define		itFcompST		209
#define		itFcompp		210
#define		itFcos			211
#define		itFdecstp		212
#define		itFdivIRM		213
#define		itFdivST		214
#define		itFfree			215
#define		itFincstp		216
#define		itFinit			217
#define		itFld1			218
#define		itFldBCDM		219
#define		itFldERM		220
#define		itFldIRM		221
#define		itFldL2E		222
#define		itFldL2T		223
#define		itFldLG2		224
#define		itFldLIM		225
#define		itFldLN2		226
#define		itFldPI			227
#define		itFldST			228
#define		itFldZ			229
#define		itFldcw			230
#define		itFldenv		231
#define		itFmulIRM		232
#define		itFmulST		233
#define		itFnop			234
#define		itFpatan		235
#define		itFprem			236
#define		itFprem1		237
#define		itFptan			238
#define		itFrndint		239
#define		itFrstor		240
#define		itFsave			241
#define		itFscale		242
#define		itFsin			243
#define		itFsincos		244
#define		itFsqrt			245
#define		itFstIRM		246
#define		itFstST			247
#define		itFstcw			248
#define		itFstenv		249
#define		itFstpBCDM		250
#define		itFstpERM		251
#define		itFstpIRM		252
#define		itFstpLIM		253
#define		itFstpST		254
#define		itFstsw			255
#define		itFstswA		256
#define		itFsubIRM		257
#define		itFsubST		258
#define		itFtst			259
#define		itFucom			260
#define		itFucomp		261
#define		itFucompp		262
#define		itFxam			263
#define		itFxch			264
#define		itFxtract		265
#define		itFyl2x			266
#define		itFyl2xp1		267
#define		itFcmovb		268
#define		itFcmove		269
#define		itFcmovbe		270
#define		itFcmovu		271
#define		itFcmovnb		272
#define		itFcmovne		273
#define		itFcmovnbe		274
#define		itFcmovnu		275
#define		itFcomi			276

/* addendum */

#define		itAdcItoRM		300
#define		itAdcItoA		301
#define		itAdcRMtoRM		302
#define		itRep			303
#define		itRepNe			304
#define		itSidt			305
#define		itSldt			306
#define		itVerr			307
#define		itVerw			308
#define		itXorItoRM		309
#define		itXorItoA		310
#define		itXorRMtoRM		311

/* 80486 instructions */

#define		itBswap			400
#define		itCmpxchg		401
#define		itInvd			402
#define		itInvlpg		403
#define		itWbinvd		404
#define		itXadd			405

/* P5 instructions */

#define		itCmpxchg8b		500
#define		itCpuid			501
#define		itRdtsc			502
#define		itRdmsr			503
#define		itWrmsr			504

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
#define		itPadds			707
#define		itPaddus		708
#define		itPand			709
#define		itPandn			710
#define		itPcmpeq		711
#define		itPcmpgt		712
#define		itPcmpgtq               713
#define		itPhadd			714
#define		itPhminposuw            715
#define		itPhsub			716
#define		itPmadd			717
#define		itPmaddubsw		718
#define         itPmovsx                719 
#define         itPmovzx                720 
#define         itPmuldq                721 
#define         itPmulld                722 
#define         itPmulhrsw              723 
#define		itPmulh			724
#define		itPmull			725
#define		itPor			726
#define		itPround                727
#define		itPsign			728
#define		itPsll			729
#define		itPsra			730
#define		itPsrl			731
#define		itPsub			732
#define		itPsubs			733
#define		itPsubus		734
#define		itPsubq 		735
#define		itPunpckh		736
#define		itPunpckl		737
#define		itPxor			738

/* SSE/SSE2 instructions */

#define         itAddpd                 800
#define         itAddps                 801
#define         itAddsd                 802
#define         itAddss                 803
#define         itAndnpd                804
#define         itAndnps                805
#define         itAndpd                 806
#define         itAndps                 807
#define         itCmppd                 808
#define         itCmpps                 809
#define         itCmpsd                 810
#define         itCmpss                 811
#define         itComiss                812
#define         itCvtdq2pd              813
#define         itCvtdq2ps              814
#define         itCvtpd2dq              815
#define         itCvtpd2ps              816
#define         itCvtpi2pd              817
#define         itCvtpi2ps              818
#define         itCvtps2dq              819
#define         itCvtps2pd              820
#define         itCvtps2pi              821
#define         itCvtsd2si              822
#define         itCvtsd2ss              823
#define         itCvtsi2sd              824
#define         itCvtsi2ss              825
#define         itCvtss2sd              826
#define         itCvtss2si              827
#define         itCvttpd2dq             828
#define         itCvttpd2pi             829
#define         itCvttps2dq             830
#define         itCvttps2pi             831
#define         itCvttsd2si             832
#define         itCvttss2si             833
#define         itDivpd                 834
#define         itDivps                 835
#define         itDivsd                 836
#define         itDivss                 837
#define         itFxrstor               838
#define         itFxsave                839
#define         itLdmxcsr               840
#define         itMaskmovdqu            841
#define         itMaskmovq              842
#define         itMaxpd                 843
#define         itMaxps                 844
#define         itMaxsd                 845
#define         itMaxss                 846
#define         itMinpd                 847
#define         itMinps                 848
#define         itMinsd                 849
#define         itMinss                 850
#define         itMovapd                851
#define         itMovaps                852
#define         itMovdq2q               853
#define         itMovdqa                854
#define         itMovdqu                855
#define         itMovhlps               856
#define         itMovhpd                857
#define         itMovhps                858
#define         itMovlhps               859
#define         itMovlpd                860
#define         itMovlps                861
#define         itMovmskpd              862
#define         itMovmskps              863
#define         itMovntdq               864
#define         itMovntpd               865
#define         itMovntps               866
#define         itMovntq                867
#define         itMovq2dq               868
#define         itMovsd                 869
#define         itMovss                 870
#define         itMovupd                871
#define         itMovups                872
#define         itMulpd                 873
#define         itMulps                 874
#define         itMulsd                 875
#define         itMulss                 876
#define         itOrpd                  877
#define         itOrps                  878
#define         itPavgb                 879
#define         itPavgw                 880
#define         itPextrw                881
#define         itPextrd                882 
#define         itPinsrw                883
#define         itPmaxsw                884
#define         itPmaxub                885
#define         itPminsw                886
#define         itPminub                887
#define         itPmovmskb              888
#define         itPmulhuw               889
#define         itPmuludq               890
#define         itPrefetchnta           891
#define         itPrefetcht0            892
#define         itPrefetcht1            893
#define         itPrefetcht2            894
#define         itPsadbw                895
#define         itPshufd                896
#define         itPshufhw               897
#define         itPshuflw               898 
#define         itPshufw                899
#define         itPshufb                900
#define         itPslldq                901
#define         itPsrldq                902
#define         itPtest                 903
#define         itPunpckhqdq            904
#define         itPunpcklqdq            905
#define         itRcpps                 906
#define         itRcpss                 907
#define         itRsqrtps               908
#define         itRsqrtss               909
#define         itSfence                910
#define         itShufps                911
#define         itShufpd                912
#define         itSqrtpd                913
#define         itSqrtps                914
#define         itSqrtsd                915
#define         itSqrtss                916
#define         itStmxcsr               917
#define         itSubpd                 918
#define         itSubps                 919
#define         itSubsd                 920
#define         itSubss                 921
#define         itUcomisd               922
#define         itUcomiss               923
#define         itUnpckhpd              924
#define         itUnpckhps              925
#define         itUnpcklpd              926
#define         itUnpcklps              927
#define         itXorpd                 928
#define         itXorps                 929

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

/* REX Prefixes */

#define		itRex      		1100
#define		itRex_B     		1101
#define		itRex_X     		1102
#define		itRex_XB    		1103
#define		itRex_R     		1104
#define		itRex_RB    		1105
#define		itRex_RX    		1106
#define		itRex_RXB   		1107
#define		itRex_W      		1108
#define		itRex_WB     		1109
#define		itRex_WX     		1110
#define		itRex_WXB    		1111
#define		itRex_WR     		1112
#define		itRex_WRB    		1113
#define		itRex_WRX    		1114
#define		itRex_WRXB   		1115

typedef void (*NPRTADDRESS_OUTPUT_FUNCPTR)(_Vx_usr_arg_t, OPRINTF_OUTPUT_FUNCPTR, _Vx_usr_arg_t);

/* function declarations */

#if defined (__STDC__) || defined (__cplusplus)

IMPORT  int  dsmData (UCHAR * pD, _Vx_usr_arg_t address, OPRINTF_OUTPUT_FUNCPTR oFn, _Vx_usr_arg_t oArg);
IMPORT  int  dsmInst (UCHAR * pD, _Vx_usr_arg_t address, NPRTADDRESS_OUTPUT_FUNCPTR prtAddress, 
		      OPRINTF_OUTPUT_FUNCPTR, _Vx_usr_arg_t);
IMPORT  int  dsmNbytes (UCHAR *);

#else

IMPORT  int  dsmData ();
IMPORT  int  dsmInst ();
IMPORT  int  dsmNbytes ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCdsmX86_64Libh */
