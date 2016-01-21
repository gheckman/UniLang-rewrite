/* fppMipsLib.h - R3010 floating-point coprocessor support library header */

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
01q,07dec03,pes  Cleanup Compiler warnings.
01p,31may02,tpw  Fix typo in offset of f29. SPR 78188.
01o,16jul01,ros  add CofE comment
01n,05jun01,mem  Add FPEXTRA
01m,05jun01,tlc  Add IMPORT declaration for fppArchUnitInit();
01l,05oct99,dra  Added 32 FP reg mode support.
01k,25nov96,kkk  added prototypes for math routines.
01j,22sep92,rrr  added support for c++
01i,04jul92,jcf  added variable declarations; changed fp*RegIndex to fp*RegName
01h,03jun92,ajm  updated file name referenced to match real name
01g,26may92,rrr  the tree shuffle
01f,23feb92,yao  added FPREG_SET.  renamed FP_NUM_REGS to FP_NUM_DREGS.
01e,04oct91,rrr  passed through the ansification filter
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01d,01aug91,ajm  added definitions for assembler language
01c,04may90,dcb  added MIPS R3000 support
01b,18mar88,gae  boosted FP_STATE_FRAME_SIZE by 32 for MC68882.
01a,12aug87,gae  written.
*/

#ifndef __INCfppMipsLibh
#define __INCfppMipsLibh

#ifdef __cplusplus
extern "C" {
#endif

/* extra space for expansion: e.g., vr5400 ACC */
#define FP_EXTRA	8

/* maximum size of floating-point coprocessor state frame */
#define FP_STATE_FRAME_SIZE	\
    ((FP_NUM_REGS * _WRS_FP_REGISTER_SIZE) + ((FP_EXTRA + 1) * 4))

/* 32 bit FP support */
#if (_WRS_FP_REGISTER_SIZE == 4)

/* number of fp registers on coprocessor */

#define	FP_NUM_DREGS	16

/* 64 bit FP support */
#elif (_WRS_FP_REGISTER_SIZE == 8)

/* number of fp registers on coprocessor */

#define	FP_NUM_DREGS	32

#else	/* _WRS_FP_REGISTER_SIZE */
#error "invalid _WRS_FP_REGISTER_SIZE value"
#endif	/* _WRS_FP_REGISTER_SIZE */

#ifndef	_ASMLANGUAGE

typedef struct fpContext	/* FP_CONTEXT */
    {
    double fpx[FP_NUM_DREGS];	/* fp registers */
    int fpcsr;			/* control/statu */
    int pad;			/* padding */
    int fpxtra[FP_EXTRA];	/* ACC, etc */
    } FP_CONTEXT;

#define FPREG_SET FP_CONTEXT

#endif	/* _ASMLANGUAGE */

/* variable declarations */


#ifndef	_ASMLANGUAGE

extern REG_INDEX fpRegName[];		/* f-point data register table */
extern REG_INDEX fpCtlRegName[];	/* f-point control register table */
extern WIND_TCB *pFppTaskIdPrevious;	/* task id for deferred exceptions */
extern FUNCPTR	 fppCreateHookRtn;	/* arch dependent create hook routine */
extern FUNCPTR	 fppDisplayHookRtn;	/* arch dependent display routine */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

IMPORT void	fppArchInit (void);
IMPORT void	fppArchTaskCreateInit (FP_CONTEXT *pFpContext);
IMPORT void 	fppInitialize(void);
IMPORT void 	fppArgsToRegs (double *dblPtr);
IMPORT ULONG	fppClearFloat(void);
IMPORT void     fppArchUnitInit(void);

#else	/* __STDC__ */

IMPORT void	fppArchInit ();
IMPORT void	fppArchTaskCreateInit ();
IMPORT void 	fppInitialize();
IMPORT void 	fppArgsToRegs ();
IMPORT ULONG	fppClearFloat();
IMPORT void     fppArchUnitInit();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

/* FP_CONTEXT structure offsets */
#if (_WRS_FP_REGISTER_SIZE==4)

#define	FPX		0x0	/* OFFSET(FP_CONTEXT, fpx[0])		*/
#define	FP0		0x0	/* OFFSET(fpx[0])			*/
#define	FP1		0x4	/* OFFSET(fpx[1])			*/
#define	FP2		0x8	/* OFFSET(fpx[2])			*/
#define	FP3		0xc	/* OFFSET(fpx[3])			*/
#define	FP4		0x10	/* OFFSET(fpx[4])			*/
#define	FP5		0x14	/* OFFSET(fpx[5])			*/
#define	FP6		0x18	/* OFFSET(fpx[6])			*/
#define	FP7		0x1c	/* OFFSET(fpx[7])			*/
#define	FP8		0x20	/* OFFSET(fpx[8])			*/
#define	FP9		0x24	/* OFFSET(fpx[9])			*/
#define	FP10		0x28	/* OFFSET(fpx[10])			*/
#define	FP11		0x2c	/* OFFSET(fpx[11])			*/
#define	FP12		0x30	/* OFFSET(fpx[12])			*/
#define	FP13		0x34	/* OFFSET(fpx[13])			*/
#define	FP14		0x38	/* OFFSET(fpx[14])			*/
#define	FP15		0x3c	/* OFFSET(fpx[15])			*/
#define	FP16		0x40	/* OFFSET(fpx[16])			*/
#define	FP17		0x44	/* OFFSET(fpx[17])			*/
#define	FP18		0x48	/* OFFSET(fpx[18])			*/
#define	FP19		0x4c	/* OFFSET(fpx[19])			*/
#define	FP20		0x50	/* OFFSET(fpx[20])			*/
#define	FP21		0x54	/* OFFSET(fpx[21])			*/
#define	FP22		0x58	/* OFFSET(fpx[22])			*/
#define	FP23		0x5c	/* OFFSET(fpx[23])			*/
#define	FP24		0x60	/* OFFSET(fpx[24])			*/
#define	FP25		0x64	/* OFFSET(fpx[25])			*/
#define	FP26		0x68	/* OFFSET(fpx[26])			*/
#define	FP27		0x6c	/* OFFSET(fpx[27])			*/
#define	FP28		0x70	/* OFFSET(fpx[28])			*/
#define	FP29		0x74	/* OFFSET(fpx[29])			*/
#define	FP30		0x78	/* OFFSET(fpx[30])			*/
#define	FP31		0x7c	/* OFFSET(fpx[31])			*/
#define	FPCSR		0x80	/* OFFSET(FP_CONTEXT, fpcsr)		*/
#define	FPEXTRA		0x88	/* OFFSET(FP_CONTEXT, fpxtra)		*/

#elif ( _WRS_FP_REGISTER_SIZE==8)

#define	FPX		0x0	/* OFFSET(FP_CONTEXT, fpx[0])		*/
#define	FP0		0x0	/* OFFSET(fpx[0])			*/
#define	FP1		0x8	/* OFFSET(fpx[1])			*/
#define	FP2		0x10	/* OFFSET(fpx[2])			*/
#define	FP3		0x18	/* OFFSET(fpx[3])			*/
#define	FP4		0x20	/* OFFSET(fpx[4])			*/
#define	FP5		0x28	/* OFFSET(fpx[5])			*/
#define	FP6		0x30	/* OFFSET(fpx[6])			*/
#define	FP7		0x38	/* OFFSET(fpx[7])			*/
#define	FP8		0x40	/* OFFSET(fpx[8])			*/
#define	FP9		0x48	/* OFFSET(fpx[9])			*/
#define	FP10		0x50	/* OFFSET(fpx[10])			*/
#define	FP11		0x58	/* OFFSET(fpx[11])			*/
#define	FP12		0x60	/* OFFSET(fpx[12])			*/
#define	FP13		0x68	/* OFFSET(fpx[13])			*/
#define	FP14		0x70	/* OFFSET(fpx[14])			*/
#define	FP15		0x78	/* OFFSET(fpx[15])			*/
#define	FP16		0x80	/* OFFSET(fpx[16])			*/
#define	FP17		0x88	/* OFFSET(fpx[17])			*/
#define	FP18		0x90	/* OFFSET(fpx[18])			*/
#define	FP19		0x98	/* OFFSET(fpx[19])			*/
#define	FP20		0xa0	/* OFFSET(fpx[20])			*/
#define	FP21		0xa8	/* OFFSET(fpx[21])			*/
#define	FP22		0xb0	/* OFFSET(fpx[22])			*/
#define	FP23		0xb8	/* OFFSET(fpx[23])			*/
#define	FP24		0xc0	/* OFFSET(fpx[24])			*/
#define	FP25		0xc8	/* OFFSET(fpx[25])			*/
#define	FP26		0xd0	/* OFFSET(fpx[26])			*/
#define	FP27		0xd8	/* OFFSET(fpx[27])			*/
#define	FP28		0xe0	/* OFFSET(fpx[28])			*/
#define	FP29		0xe8	/* OFFSET(fpx[29])			*/
#define	FP30		0xf0	/* OFFSET(fpx[30])			*/
#define	FP31		0xf8	/* OFFSET(fpx[31])			*/
#define	FPCSR		0x100	/* OFFSET(FP_CONTEXT, fpcsr)		*/
#define	FPEXTRA		0x108	/* OFFSET(FP_CONTEXT, fpxtra)		*/

#else	/* _WRS_FP_REGISTER_SIZE */
#error "invalid _WRS_FP_REGISTER_SIZE value"
#endif	/* _WRS_FP_REGISTER_SIZE */

#ifdef __cplusplus
}
#endif

#endif /* __INCfppMipsLibh */
