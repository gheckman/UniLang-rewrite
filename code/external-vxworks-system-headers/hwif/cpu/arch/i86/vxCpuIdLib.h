/* vxCpuIdLib.h - Intel Architecture CPUID Header */

/*
 * Copyright (c) 2010-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,17sep13,scm  WIND00374998 - Add bundle for Bay Trail...
01i,07feb13,scm  WIND00387999 support for Haswell micro-arch...
01h,20jun12,yjw  Fix incorrect offset.(WIND00357097)
01g,21may12,c_t  Support detect CPU frequency.(WIND00338455)
01f,13feb12,yjw  Extend pTopParams array to support 32 cores (WIND00293328)
01e,18nov11,jjk  WIND00255693 - Adding support for CedarView
01d,07jul11,scm  WIND00189850, HT/SMT support and logical restructuring
                 of CPU Id tables...
01c,24feb11,rbc  WIND00255497 - Fix CPUID fallback for unknown CPU signatures
01b,18oct10,sem  Update cpuid struct for backward compatibility
01a,26jul10,sem  Created
*/

/*
DESCRIPTION
Intel CPU identification structure definitions and constants.

Support definitions and constants have been added to aid in 
detecting multi-core processor topology on IA platforms.
*/

#ifndef __INCvxCpuIdLibh
#define __INCvxCpuIdLibh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Byte offset in VX_CPUID structure.
 * For backward compatibility, the first 12 offsets must
 * match the CPUID offsets defined in target/h/arch/i86/regsI86.h.
 */

#define VX_CPUID_HIGHVALUE         0    /* offset to highestValue          */
#define VX_CPUID_VENDORID          4    /* offset to vendorId              */
#define VX_CPUID_SIGNATURE         16   /* offset to signature             */
#define VX_CPUID_FEATURES_EBX      20   /* offset to featuresEbx           */
#define VX_CPUID_FEATURES_ECX      24   /* offset to featuresEcx           */
#define VX_CPUID_FEATURES_EDX      28   /* offset to featuresEdx           */
#define VX_CPUID_CACHE_EAX         32   /* offset to cacheEax              */
#define VX_CPUID_CACHE_EBX         36   /* offset to cacheEbx              */
#define VX_CPUID_CACHE_ECX         40   /* offset to cacheEcx              */
#define VX_CPUID_CACHE_EDX         44   /* offset to cacheEdx              */
#define VX_CPUID_SERIALNO          48   /* offset to serialNo64            */
#define VX_CPUID_BRAND_STR         56   /* offset to brandString[0]        */
#define VX_CPUID_HIGHVALUE_EXT     104  /* offset to highestValue Extended */
#define VX_CPUID_EXT_FEATURES_EDX  108  /* offset to featuresEdx Extended  */
#define VX_CPUID_EXT_FEATURES_ECX  112  /* offset to featuresEcx Extended  */
#define VX_CPUID_CACHE_COUNT       116  /* offset to cache count           */
#define VX_CPUID_CACHE_PARAMS      120  /* offset to cache parameters      */
#define VX_CPUID_MONITOR_EAX       216  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_EBX       220  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_ECX       224  /* offset to montor/mwait parameters */
#define VX_CPUID_MONITOR_EDX       228  /* offset to montor/mwait parameters */
#define VX_CPUID_DTSPM_EAX         232  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_EBX         236  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_ECX         240  /* offset to DTSPM parameters */
#define VX_CPUID_DTSPM_EDX         244  /* offset to DTSPM parameters */
#define VX_CPUID_DCA_EAX           248  /* offset to DCA parameters */
#define VX_CPUID_PMON_EAX          252  /* offset to PMON parameters */
#define VX_CPUID_PMON_EBX          256  /* offset to PMON parameters */
#define VX_CPUID_PMON_ECX          260  /* offset to PMON parameters */
#define VX_CPUID_PMON_EDX          264  /* offset to PMON parameters */
#define VX_CPUID_PTOP_COUNT        268  /* offset to PTOP count      */
#define VX_CPUID_PTOP_PARAMS       272  /* offset to PTOP parameters */
#define VX_CPUID_XSAVE_EAX         784  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_EBX         788  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_ECX         792  /* offset to XSAVE parameters */
#define VX_CPUID_XSAVE_EDX         796  /* offset to XSAVE parameters */
#define VX_CPUID_L2CACHE_EAX       800  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_EBX       804  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_ECX       808  /* offset to L2 Cache parameters */
#define VX_CPUID_L2CACHE_EDX       812  /* offset to L2 Cache parameters */
#define VX_CPUID_APM_EAX           816  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_EBX           820  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_ECX           824  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_APM_EDX           828  /* offset to Advanced Power Mgt parameters */
#define VX_CPUID_VPADRS_EAX        832  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_EBX        836  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_ECX        840  /* offset to Virt/Phys Adr Size parameters */
#define VX_CPUID_VPADRS_EDX        844  /* offset to Virt/Phys Adr Size parameters */

/* bit mask in VX_CPUID_VERSION structure */

#define VX_CPUID_BRAND	     0x000000ff
#define VX_CPUID_FLUSH_SIZE	 0x0000ff00
#define VX_CPUID_NPROC	     0x00ff0000
#define VX_CPUID_APIC_ID	 0xff000000

/* bit mask in VX_CPUID_FEATURES structure */

#define VX_CPUID_FPU         0x00000001
#define VX_CPUID_VME         0x00000002
#define VX_CPUID_DEBUG       0x00000004
#define VX_CPUID_PSE         0x00000008
#define VX_CPUID_TSC         0x00000010
#define VX_CPUID_MSR         0x00000020
#define VX_CPUID_PAE         0x00000040
#define VX_CPUID_MCE         0x00000080
#define VX_CPUID_CX8         0x00000100
#define VX_CPUID_APIC        0x00000200
#define VX_CPUID_SEP         0x00000800
#define VX_CPUID_MTTR        0x00001000
#define VX_CPUID_PGE         0x00002000
#define VX_CPUID_MCA         0x00004000
#define VX_CPUID_CMOV        0x00008000
#define VX_CPUID_PAT         0x00010000
#define VX_CPUID_PSE36       0x00020000
#define VX_CPUID_PSNUM       0x00040000
#define VX_CPUID_CLFLUSH     0x00080000
#define VX_CPUID_DTS         0x00200000
#define VX_CPUID_ACPI        0x00400000
#define VX_CPUID_MMX         0x00800000
#define VX_CPUID_FXSR        0x01000000
#define VX_CPUID_SSE         0x02000000
#define VX_CPUID_SSE2        0x04000000
#define VX_CPUID_SS          0x08000000
#define VX_CPUID_HTT         0x10000000
#define VX_CPUID_TM          0x20000000
#define VX_CPUID_PBE         0x80000000

/* bit mask in VX_CPUID_FEATURES_EXT structure */

#define VX_CPUID_SSE3        0x00000001
#define VX_CPUID_PCLMULDQ    0x00000002
#define VX_CPUID_DTES64      0x00000004
#define VX_CPUID_MON         0x00000008
#define VX_CPUID_DS_CPL      0x00000010
#define VX_CPUID_VMX         0x00000020
#define VX_CPUID_SMX         0x00000040
#define VX_CPUID_EST         0x00000080
#define VX_CPUID_TM2         0x00000100
#define VX_CPUID_SSSE3       0x00000200
#define VX_CPUID_CID         0x00000400
#define VX_CPUID_CX16        0x00002000
#define VX_CPUID_XTPR        0x00004000
#define VX_CPUID_PDCM        0x00008000
#define VX_CPUID_DCA         0x00040000
#define VX_CPUID_SSE41       0x00080000
#define VX_CPUID_SSE42       0x00100000
#define VX_CPUID_X2APIC      0x00200000
#define VX_CPUID_MOVBE       0x00400000
#define VX_CPUID_POPCNT      0x00800000
#define VX_CPUID_AES         0x02000000
#define VX_CPUID_XSAVE       0x04000000
#define VX_CPUID_OSXSAVE     0x08000000
#define VX_CPUID_AVX         0x10000000

/* bit mask in VX_CPUID_FEATURES_EXTD structure */

#define VX_CPUID_SCALL_SRET  0x00001000
#define VX_CPUID_EXCDIS      0x00200000
#define VX_CPUID_EM64T       0x20000000

/* bit mask in VX_CPUID_FEATURES_EXTC structure */

#define VX_CPUID_LAHF        0x00000001

/* bit mask in deterministic cache parameters */

#define VX_CPUID_CACHE_TYPE  0x0000001f
#define VX_CPUID_CACHE_LEVEL 0x000000e0

/* bit mask in VX_CPUID_INFO structure */

#define VX_CPUID_STEPID      0x0000000f   /* processor stepping id mask     */
#define VX_CPUID_MODEL       0x000000f0   /* processor model mask           */
#define VX_CPUID_FAMILY      0x00000f00   /* processor family mask          */
#define VX_CPUID_TYPE        0x00003000   /* processor type mask            */
#define VX_CPUID_EXT_MODEL   0x000f0000   /* processor extended model mask  */
#define VX_CPUID_EXT_FAMILY  0x0ff00000   /* processor extended family mask */

/* extended model definitions */

#define VX_CPUID_EXT_MODEL_PENTIUM     0x00000000
#define VX_CPUID_EXT_MODEL_CORE        0x00010000
#define VX_CPUID_EXT_MODEL_SANDYBRIDGE 0x00020000

/* CPU TYPE */

#define VX_CPUID_ORIG        0x00000000    /* type: original OEM   */
#define VX_CPUID_OVERD       0x00001000    /* type: overdrive      */
#define VX_CPUID_DUAL        0x00002000    /* type: dual           */

/* CPUID definitions */

#define VX_CPUID_UNSUPPORTED 0xffffffff   /* family: not supported  */

/* Pentium microarchitecture CPUIDs */

#define VX_CPUID_PENTIUM     0x00000500   /* family: Pentium                */
#define VX_CPUID_PENTIUM4    0x00000000   /* extended family: PENTIUM4      */

/* Core microarchitecture CPUIDs */

#define VX_CPUID_CORE        0x000006e0    /* Core Solo/Duo   */
#define VX_CPUID_CORE2       0x000006f0    /* Core2           */
#define VX_CPUID_CORE2_DUO   0x00010670    /* Core2 Duo       */
#define VX_CPUID_XEON_5400   0x00010670    /* Xeon 52xx/54xx  */
#define VX_CPUID_XEON_7400   0x000106d0    /* Xeon 74xx Core2 */

/* Nehalem microarchitecture CPUIDs */

#define VX_CPUID_XEON_5500   0x000106a0    /* Xeon 55xx        */
#define VX_CPUID_XEON_C5500  0x000106e0    /* Xeon C35xx/C55xx */
#define VX_CPUID_XEON_5600   0x000206c0    /* Xeon 56xx        */
#define VX_CPUID_XEON_7500   0x000206e0    /* Xeon 65xx/75xx   */
#define VX_CPUID_XEON_32NM   0x000206f0    /* Xeon 65xx/75xx 32 NM */
#define VX_CPUID_COREI5_I7M  0x00020650    /* Arrandale i3 or i5/i7 Mobile 6xx/5xx */

/* Atom microarchitecture CPUIDs */

#define VX_CPUID_ATOM        0x000106c0    /* Atom  */
#define VX_CPUID_CEDARVIEW   0x00030660    /* Atom CedarView CPU N2800 */
#define VX_CPUID_SILVERMONT  0x00030672    /* Atom Silvermont CPU */                                

/* Sandy Bridge microarchitecture CPUIDs */

#define VX_CPUID_SANDYBRIDGE 0x000206a0    /* SandyBridge */

/* Haswell microarchitecture CPUIDs */

#define VX_CPUID_HASWELL_CLIENT  0x000306c0    /* Haswell Client */
#define VX_CPUID_HASWELL_SERVER  0x000306f0    /* Haswell Server */
#define VX_CPUID_HASWELL_ULT     0x00040650    /* Haswell ULT    */
#define VX_CPUID_CRYSTAL_WELL    0x00040660    /* Crystal Well   */

/* Dummy entry */

#define VX_CPUID_DUMMY        0    /* Dummy CPUID entry            */

/*
 * CPU FAMILY
 * For backward compatibility, the following definitions for
 * PENTIUM and PENTIUM4 must match those defined in
 * target/h/arch/i86/regsI86.h.
 */

#define VX_X86CPU_UNSUPPORTED   0   /* CPU FAMILY: Not supported    */
#define VX_X86CPU_PENTIUM       2   /* CPU FAMILY: Pentium/P5       */
#define VX_X86CPU_PENTIUM4      5   /* CPU FAMILY: Pentium4/P7      */
#define VX_X86CPU_CORE          6   /* CPU FAMILY: Core/Core2       */
#define VX_X86CPU_ATOM          7   /* CPU FAMILY: Atom             */
#define VX_X86CPU_NEHALEM       8   /* CPU FAMILY: Nehalem          */
#define VX_X86CPU_SANDYBRIDGE   9   /* CPU FAMILY: Sandy Bridge     */
#define VX_X86CPU_HASWELL      10   /* CPU FAMILY: Haswell          */

/* CPU feature override flags */

#define VX_CPUID_FEAT_ENABLE  1    /* CPUID feature enable          */
#define VX_CPUID_FEAT_DISABLE 0    /* CPUID feature disable         */

/*
 * Support definitions and constants to aid in detecting multi-core 
 * processor topology on IA platforms.
 */

#define VX_CPUID_KEY0           0x00000000
#define VX_CPUID_KEY1           0x00000001

#define VX_CPUID_HWMT_BIT       0x10000000      /* bit #28 */

#define VX_CPUID_LOGICAL_BITS   0x00FF0000      /* bits 16 thru 23 */
#define VX_CPUID_LOGICAL_SHIFT  0x00000010      /* shift 16 */

#define VX_CPUID_CORE_BITS      0xFC000000      /* bits 26 thru 31 */
#define VX_CPUID_CORE_SHIFT     0x0000001A      /* shift 26 */

#define VX_CPUID_LEAF_4         0x04

#define VX_CPUID_APIC_ID_BITS   0xFF000000      /* bits 24 thru 31 */
#define VX_CPUID_APIC_ID_SHIFT  0x00000018      /* shift 24 */

#define VX_CPUID_MAX_NUM_CPUS   256             /* max num CPUs */
	
#ifndef _ASMLANGUAGE

/* CPUID override structure */

typedef struct vxcpuidoverride
    {
    uint32_t type;
    uint32_t feat;
    uint32_t state;
    } VX_CPUID_OVERRIDE;

/* CPUID signature table entry structure */

typedef struct vxcpuidentry
    {
    uint32_t signature;
    uint32_t family;
    } VX_CPUID_ENTRY;

/*
 * CPUID standard features
 * For backward compatibility, this structure must match the
 * CPUID structure definition in target/h/arch/i86/regsI86.h.
 */

typedef struct vxcpuidstd      /* CPUID - 80x86 cpuid version/feature */
    {
    int highestValue;	       /* EAX=0: highest integer value */
    int vendorId[3];	       /* EAX=0: vendor identification string */
    int signature;		       /* EAX=1: processor signature */
    int featuresEbx;	       /* EAX=1: feature flags EBX */
    int featuresEcx;	       /* EAX=1: feature flags ECX */
    int featuresEdx;	       /* EAX=1: feature flags EDX */
    int cacheEax;		       /* EAX=2: config parameters EAX */
    int cacheEbx;		       /* EAX=2: config parameters EBX */
    int cacheEcx;		       /* EAX=2: config parameters ECX */
    int cacheEdx;		       /* EAX=2: config parameters EDX */
    int serialNo64[2];	       /* EAX=3: lower 64 of 96 bit serial no */
    int brandString[12];       /* EAX=0x8000000[234]: brand strings */
    } VX_CPUID_STD;

/* CPUID extended features */

typedef struct vxcpuidext      /* CPUID - 80x86 cpuid version/feature */
    {
    int highestExtValue;       /* EAX=0x80000000: highest integer value */
    int featuresExtEdx;        /* EAX=0x80000001: Extended feature flags EDX */
    int featuresExtEcx;        /* EAX=0x80000001: Extended feature flags ECX */
    int cacheCount;            /* Count of cache info blocks */
    int cacheParams[6][4];     /* EAX=0x4: Deterministic cache parameters */
    int monitorParamsEax;      /* EAX=0x5: monitor/mwait parameters EAX */
    int monitorParamsEbx;      /* EAX=0x5: monitor/mwait parameters EBX */
    int monitorParamsEcx;      /* EAX=0x5: monitor/mwait parameters ECX */
    int monitorParamsEdx;      /* EAX=0x5: monitor/mwait parameters EDX */
    int dtspmParamsEax;        /* EAX=0x6: DTSPM parameters EAX */
    int dtspmParamsEbx;        /* EAX=0x6: DTSPM parameters EBX */
    int dtspmParamsEcx;        /* EAX=0x6: DTSPM parameters ECX */
    int dtspmParamsEdx;        /* EAX=0x6: DTSPM parameters EDX */
    int dcaParamsEax;          /* EAX=0x9: DCA parameters EAX */
    int pMonParamsEax;         /* EAX=0xA: PMON parameters EAX */
    int pMonParamsEbx;         /* EAX=0xA: PMON parameters EBX */
    int pMonParamsEcx;         /* EAX=0xA: PMON parameters ECX */
    int pMonParamsEdx;         /* EAX=0xA: PMON parameters EDX */
    int pTopCount;             /* Count of processor topology info blocks */
    int pTopParams[32][4];     /* EAX=0xB: x2APIC/Processor Topology */
    int xsaveParamsEax;        /* EAX=0xD: XSAVE parameters EAX */
    int xsaveParamsEbx;        /* EAX=0xD: XSAVE parameters EBX */
    int xsaveParamsEcx;        /* EAX=0xD: XSAVE parameters ECX */
    int xsaveParamsEdx;        /* EAX=0xD: XSAVE parameters EDX */
    int l2ParamsEax;           /* EAX=0x80000006: Extended L2 Cache EAX */
    int l2ParamsEbx;           /* EAX=0x80000006: Extended L2 Cache EBX */
    int l2ParamsEcx;           /* EAX=0x80000006: Extended L2 Cache ECX */
    int l2ParamsEdx;           /* EAX=0x80000006: Extended L2 Cache EDX */
    int apmParamsEax;          /* EAX=0x80000007: Advanced Power Mgt EAX */
    int apmParamsEbx;          /* EAX=0x80000007: Advanced Power Mgt EBX */
    int apmParamsEcx;          /* EAX=0x80000007: Advanced Power Mgt ECX */
    int apmParamsEdx;          /* EAX=0x80000007: Advanced Power Mgt EDX */
    int vpAdrSizesEax;         /* EAX=0x80000008: Virt/Phys Addr Sizes EAX */
    int vpAdrSizesEbx;         /* EAX=0x80000008: Virt/Phys Addr Sizes EBX */
    int vpAdrSizesEcx;         /* EAX=0x80000008: Virt/Phys Addr Sizes ECX */
    int vpAdrSizesEdx;         /* EAX=0x80000008: Virt/Phys Addr Sizes EDX */
    } VX_CPUID_EXT;


/* CPUID standard and extended features */

typedef struct vxcpuid
    {
    VX_CPUID_STD std; /* Standard CPUID features */
    VX_CPUID_EXT ext; /* Extended CPUID features */
    } VX_CPUID;

/* CPUID fields in the EAX register when EAX=1 */

typedef union
    {
    struct
	{
	uint32_t stepid:4;      /* processor stepping id mask   */
	uint32_t model:4;       /* processor model mask     */
	uint32_t family:4;      /* processor family mask    */
	uint32_t type:2;        /* processor type mask      */
	uint32_t reserved1:2;
	uint32_t modelExt:4;	/* processor extended model mask */
	uint32_t familyExt:8;	/* processor extended family mask */
	uint32_t reserved2:4;
	} field;
    uint32_t value;
    } VX_CPUID_VERSION;

/* CPUID fields in the EBX register when EAX=1 */

typedef union
    {
    struct
	{
	uint32_t brand:8;	    /* Brand index */
	uint32_t flushSize:8;	/* CLFLUSH line size */
	uint32_t nproc:8;	    /* number of local processors */
	uint32_t apicId:8;	    /* local APIC id */
	} field;
    uint32_t value;
    } VX_CPUID_INFO;

/* CPUID: feature bit definitions */

/* CPUID fields in the EDX register when EAX=1 */

typedef union
    {
    struct
	{
	uint32_t fpu:1;		/* FPU on chip			*/
	uint32_t vme:1;		/* virtual 8086 mode enhancement*/
	uint32_t de:1;		/* debugging extensions		*/
	uint32_t pse:1;		/* page size extension		*/
	uint32_t tsc:1;		/* time stamp counter		*/
	uint32_t msr:1;		/* RDMSR and WRMSR support	*/
	uint32_t pae:1;		/* physical address extensions	*/
	uint32_t mce:1;		/* machine check exception	*/
	uint32_t cx8:1;		/* CMPXCHG8 inst		*/
	uint32_t apic:1;	/* APIC on chip			*/
	uint32_t reserved1:1;
	uint32_t sep:1;		/* SEP, Fast System Call	*/
	uint32_t mtrr:1;	/* MTRR				*/
	uint32_t pge:1;		/* PTE global bit		*/
	uint32_t mca:1;		/* machine check arch.		*/
	uint32_t cmov:1;	/* cond. move/cmp. inst		*/
	uint32_t pat:1;		/* page attribute table		*/
	uint32_t pse36:1;	/* 36 bit page size extension	*/
	uint32_t psnum:1;	/* processor serial number	*/
	uint32_t clflush:1;	/* CLFLUSH inst supported	*/
	uint32_t reserved2:1;
	uint32_t dts:1;		/* Debug Store			*/
	uint32_t acpi:1;	/* TM and SCC supported		*/
	uint32_t mmx:1;		/* MMX technology supported	*/
	uint32_t fxsr:1;	/* fast FP save and restore	*/
	uint32_t sse:1;		/* SSE supported		*/
	uint32_t sse2:1;	/* SSE2 supported		*/
	uint32_t ss:1;		/* Self Snoop supported		*/
	uint32_t htt:1;		/* Hyper Threading Technology   */
	uint32_t tm:1;		/* Thermal Monitor supported	*/
	uint32_t reserved3:1;
	uint32_t pbe:1;		/* Pend break enable		*/
	} field;
    uint32_t value;
    } VX_CPUID_EDX_FEATURES;


/* fields in the ECX register when EAX=1 */

typedef union
    {
    struct
	{
	uint32_t sse3:1;	/* SSE3 Extensions */
	uint32_t pclmuldq:1;    /* PCLMULDQ instruction */
	uint32_t dtes64:1;      /* 64-bit debug store */
	uint32_t mon:1;		/* Monitor/wait	*/
	uint32_t ds_cpl:1;	/* CPL qualified Debug Store */
	uint32_t vmx:1;		/* Virtual Machine Technology */
	uint32_t smx:1;		/* Safer mode extensions */
	uint32_t est:1;		/* Enhanced Speedstep Technology */
	uint32_t tm2:1;		/* Thermal Monitor 2 supported */
	uint32_t ssse3:1;	/* SSSE3 Extensions */
	uint32_t cid:1;		/* L1 context ID */
	uint32_t debugmsr:1;    /* IA32_DEBUG_INTERFACE_MSR support */
	uint32_t fma:1;	        /* FMA Extensions Using XMM state */
	uint32_t cx16:1;	/* CMPXCHG16B instruction */
	uint32_t xtpr:1;	/* Update control */
	uint32_t pdcm:1;	/* Perfmon/Debug capability */
	uint32_t reserved3:1;
	uint32_t asid_pcid:1;   /* ASID-PCID support */
	uint32_t dca:1;         /* Direct cache access */
	uint32_t sse41:1;	/* SSE4.1 Extensions */
	uint32_t sse42:1;	/* SSE4.2 Extensions */
	uint32_t x2apic:1;	/* x2APIC feature */
	uint32_t movbe:1;	/* MOVBE instruction */
	uint32_t popcnt:1;	/* POPCNT instruction */
	uint32_t tsc_dline:1;   /* TSC-deadline Timer */
	uint32_t aes:1;		/* AES instruction */
	uint32_t xsave:1;	/* XSAVE/XRSTOR States */
	uint32_t osxsave:1;	/* OS-Enabled Extended State management */
	uint32_t avx:1;	        /* OS-Enabled Extended State management */
	uint32_t f16c:1;        /* Float16 instructions support */
	uint32_t rdrand:1;      /* Read Random Number instructions support */
	uint32_t reserved4:1;
	} field;
    uint32_t value;
    } VX_CPUID_ECX_FEATURES;

/* fields in the EDX register when EAX=0x80000001 */

typedef union
    {
    struct
        {
        uint32_t reserved1:11;  /* 0-10 reserved */
        uint32_t scall_sret:1;  /* Syscall/Sysret available in 64 bit mode */
        uint32_t reserved2:8;   /* 12-19 reserved */
        uint32_t excdis:1;      /* Execute Disable Bit available */
        uint32_t reserved3:5;   /* 21-25 reserved */
        uint32_t gbpss:1;       /* 1 GB Page Size Support */
        uint32_t rdtscp:1;      /* RDTSCP instruction and IA32_TSC_AUX_MSR */
        uint32_t reserved4:1;   /* 28 reserved */
        uint32_t em64t:1;       /* EM64T available */
        uint32_t reserved5:2;   /* 30-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EDX_FEATURES_EXT;

/* fields in the ECX register when EAX=0x80000001 */

typedef union
    {
    struct
        {
        uint32_t lahf:1;       /* LAHF and SAHF instructions */
        uint32_t reserved1:4;  /* 1-4 reserved */
        uint32_t abm:1;        /* Advanced Bit Manipulation instructions */
        uint32_t reserved2:26; /* 6-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_ECX_FEATURES_EXT;


/* Deterministic cache parameter descriptions */

/* fields in the EAX register when EAX=0x4 */

typedef union
    {
    struct
        {
        uint32_t type:5;      /* Cache type */
        uint32_t level:3;     /* Cache level */
        uint32_t self_init:1; /* Self-initializing cache level */
        uint32_t assoc:1;     /* Fully associative cache level */
        uint32_t reserved1:4; /* 10-13 reserved */
        uint32_t threads:12;  /* Max threads sharing cache - add 1 */
        uint32_t apics:6;     /* Num reserved APIC IDs - add 1 */
        } field;
    uint32_t value;
    } VX_CPUID_EAX_CACHE_PARAMS;

/* fields in the EBX register when EAX=0x4 */

typedef union
    {
    struct
        {
        uint32_t line_size:12;  /* System coherency line size - add 1*/
        uint32_t partitions:10; /* Physical line partitions - add 1 */
        uint32_t assoc:10;      /* Ways of Associativity - add 1 */
        } field;
    uint32_t value;
    } VX_CPUID_EBX_CACHE_PARAMS;

/* fields in the ECX register when EAX=0x4 */

typedef struct
    {
    uint32_t sets;              /* Number of Sets - add 1 */
    } VX_CPUID_ECX_CACHE_PARAMS;

/* fields in the EDX register when EAX=0x4 */

typedef union
    {
    struct
        {
        uint32_t wbindv:1;       /* WBINDV/INVD behavior on lower levels */
        uint32_t inclusive:1;    /* Cache is inclusize to lower levels */
        uint32_t complex_addr:1; /* Cache uses complex function to index */
        uint32_t reserved1:29;   /* 3-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EDX_CACHE_PARAMS;

/* MONITOR/MWAIT parameters */

/* fields in the EAX register when EAX=0x5 */

typedef union
    {
    struct
        {
        uint32_t smline:16;     /* Smallest monitor line size in bytes */
        uint32_t reserved1:16;  /* 15-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EAX_MONITOR_PARAMS;

/* fields in the EBX register when EAX=0x5 */

typedef union
    {
    struct
        {
        uint32_t  lgline:16;    /* Largest monitor line size in bytes */
        uint32_t reserved1:16;  /* 15-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EBX_MONITOR_PARAMS;

/* fields in the ECX register when EAX=0x5 */

typedef union
    {
    struct
        {
        uint32_t mwait:1;       /* MONITOR/MWAIT extensions supported */
        uint32_t intr_break:1;  /* Break-events for MWAIT */
        uint32_t reserved1:30;  /* 2-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_ECX_MONITOR_PARAMS;

/* fields in the EDX register when EAX=0x5 */

typedef union
    {
    struct
        {
        uint32_t c0:4;         /* C0 sub-states */
        uint32_t c1:4;         /* C1 sub-states */
        uint32_t c2:4;         /* C2 sub-states */
        uint32_t c3_6:4;       /* C3/6 sub-states */
        uint32_t c4_7:4;       /* C4/7 sub-states */
        uint32_t reserved1:12; /* 20-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EDX_MONITOR_PARAMS;

/* Digital Thermal Sensor and Power Management parameters */

/* fields in the EAX register when EAX=0x6 */

typedef union
    {
    struct
        {
        uint32_t dts:1;           /* Digital thermal sensor capable */
        uint32_t turbo:1;         /* Turbo Boost technology */
        uint32_t invar_apic:1;    /* Invariant Apic Timer */
        uint32_t reserved1:1;     /* 3 reserved */
        uint32_t pln_at_core:1;   /* Power Limit Notification at Core Level */
        uint32_t fgcm:1;          /* Fine Grained Clock Modulation */
        uint32_t thermint_stat:1; /* Package Thermal Interrupt and Status support */
        uint32_t reserved2:25;    /* 7-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EAX_DTSPM_PARAMS;

typedef union
    {
    struct
        {
        uint32_t intr:4;         /* Number of interrupt thresholds */
        uint32_t reserved1:28;   /* 4-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EBX_DTSPM_PARAMS;

typedef union
    {
    struct
        {
        uint32_t hcfc:1;        /* Hardware Coordination Feedback Capability */
        uint32_t acnt2:1;       /* ACNT2 Capability */
        uint32_t reserved1:1;   /* 2 reserved2 reserved */
        uint32_t efps:1;        /* Energy Efficient Policy support */
        uint32_t reserved2:28;  /* 4-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_ECX_DTSPM_PARAMS;

typedef union
    {
    struct
        {
        uint32_t reserved1:32;  /* 0-31 reserved */
        } field;
    uint32_t value;
    } VX_CPUID_EDX_DTSPM_PARAMS;


/* Direct Cache Access (DCA) parameters */

/* fields in the EAX register when EAX=0x9 */

typedef union
    {
    struct
        {
        uint32_t dca_cap:32;         /* PLATFORM_DCA_CAP MSR bits */
       } field;
    uint32_t value;
    } VX_CPUID_EAX_DCA_PARAMS;

/* Performance Monitor Features */

/* fields in the EAX register when EAX=0xA */

typedef union
    {
    struct
        {
        uint32_t ver:8;         /* Architecture PerfMon version */
        uint32_t ncounters:8;   /* Number of counters per logical processor */
        uint32_t nbits:8;       /* Number of bits per programmable counter */
        uint32_t nevts:8;       /* Number of events per logical processor */
       } field;
    uint32_t value;
    } VX_CPUID_EAX_PMON_PARAMS;

/* fields in the EBX register when EAX=0xA, 0 = supported */

typedef union
    {
    struct
        {
        uint32_t core_cycles:1; /* Core Cycles */
        uint32_t instr_ret:1;   /* Instructions retired  */
        uint32_t ref_cycles:1;  /* Reference cycles */
        uint32_t cache_ref:1;   /* Last level cache references  */
        uint32_t cache_miss:1;  /* Last level cache misses */
        uint32_t br_instr:1;    /* Branch instructions retired */
        uint32_t br_mispr:1;    /* Branch mispredicts retired */
        uint32_t reserved:25;   /* 7-31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EBX_PMON_PARAMS;

/* fields in the ECX register when EAX=0xA */

typedef union
    {
    struct
        {
        uint32_t reserved:32;   /* 0:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_ECX_PMON_PARAMS;

/* fields in the EDX register when EAX=0xA */

typedef union
    {
    struct
        {
        uint32_t nfix_cntrs:5;   /* Number of fixed counters */
        uint32_t nbit_cntrs:8;   /* Number of bits in the fixed counters */
        uint32_t reserved:19;    /* 13:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EDX_PMON_PARAMS;

/* x2APIC Features / Core Topology */

/* fields in the EAX register when EAX=0xB */

typedef union
    {
    struct
        {
        uint32_t nbits:5;       /* Number of bits to shift right APIC ID */
        uint32_t reserved1:27;  /* 5:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EAX_PTOP_PARAMS;

/* fields in the EBX register when EAX=0xB */

typedef union
    {
    struct
        {
        uint32_t nproc:16;      /* Number of logical processors at this level */
        uint32_t reserved1:16;  /* 16:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EBX_PTOP_PARAMS;

/* fields in the ECX register when EAX=0xB */

typedef union
    {
    struct
        {
        uint32_t lvl_num:8;      /* Level number */
        uint32_t lvl_type:8;     /* Level type */
        uint32_t reserved1:16;   /* 16:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_ECX_PTOP_PARAMS;

/* fields in the EDX register when EAX=0xB */

typedef union
    {
    struct
        {
        uint32_t xapic_id:32;    /* extended apic ID */
       } field;
    uint32_t value;
    } VX_CPUID_EDX_PTOP_PARAMS;

/* Extended L2 Cache Features */

/* fields in the ECX register when EAX=0x80000006 */

typedef union
    {
    struct
        {
        uint32_t cache_line:8;   /* L2 Cache line size ibn bytes */
        uint32_t reserved1:4;    /* 8:11 reserved */
        uint32_t assoc:4;        /* L2 Cache Associativity */
        uint32_t cache_size:16;  /* L2 Cache size in 1024 byte units */
       } field;
    uint32_t value;
    } VX_CPUID_ECX_L2_PARAMS;

/* Advanced Power Management */

/* fields in the EDX register when EAX=0x80000007 */

typedef union
    {
    struct
        {
        uint32_t reserved1:8;    /* 0:7 reserved */
        uint32_t tsc_inv:1;      /* TSC invariance */
        uint32_t reserved2:23;   /* 9:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EDX_APM_PARAMS;

/* Virtual and Physical Address Sizes */

/* fields in the EAX register when EAX=0x80000008 */

typedef union
    {
    struct
        {
        uint32_t phys:8;        /* Physical address size in bits */
        uint32_t virt:8;        /* Virtual address size  in bits */
        uint32_t reserved1:16;  /* 16:31 reserved */
       } field;
    uint32_t value;
    } VX_CPUID_EAX_VPADRSIZES_PARAMS;

/*
 * This structure represents information that describes the CPU Topology.
 */

typedef struct cpuIdTopology
    {
    unsigned int   maxLP_PC;        /* Maximum Logical Processors per Package */
    unsigned int   maxNC_PP;           /* Maximum Number of Cores per Package */
    unsigned int   maxLP_PP;           /* Maximum Logical Processors per Core */
    
    unsigned int   smtMaskWidth;                             /* SMT Bit Width */
    unsigned int   coreMaskWidth;                           /* Core Bit Width */
    unsigned int   pkgMaskWidth;                         /* Package Bit Width */

    unsigned int   numCores;                               /* Number of Cores */
    unsigned int   numPkgs;                             /* Number of Packages */

    unsigned int   numLP_enabled;     /* Number of Logical Processors Enabled */

    unsigned char  packageIDMask;                          /* Package ID Mask */
    
    unsigned char  tblSMT_ID[VX_CPUID_MAX_NUM_CPUS];               /* SMT Ids */
    unsigned char  tblCore_ID[VX_CPUID_MAX_NUM_CPUS];             /* Core Ids */
    unsigned char  tblPkg_ID[VX_CPUID_MAX_NUM_CPUS];           /* Package Ids */

    unsigned int   tblPhys_Indx[VX_CPUID_MAX_NUM_CPUS];        /* CPUID table */

    cpuset_t       __smtSet[VX_CPUID_MAX_NUM_CPUS];            /* SMT CPU set */
    } CPU_ID_TOPOLOGY;

IMPORT CPU_ID_TOPOLOGY  sysCpuIdTopology, *pSysCpuIdTopology;

/* function declarations */

#if defined (__STDC__) || defined (__cplusplus)

#include <hwif/intCtlr/vxbMpApic.h>

extern void vxCpuIdLibInit(void);
extern int vxCpuIdProbe(VX_CPUID *);
extern STATUS vxCpuIdAdd(VX_CPUID_ENTRY *entry);
extern STATUS vxCpuIdOverride(VX_CPUID *cpuid, VX_CPUID_OVERRIDE *entries, int cnt);
extern void vxCpuIdShow(VX_CPUID *);

extern BOOL vxCpuIdHWMTSupported (void);
extern unsigned int vxCpuIdMaxNumLPPerPkg (void);
extern unsigned int vxCpuIdMaxNumCoresPerPkg (void);
extern unsigned int vxCpuIdBitFieldWidth (unsigned int count_item);
extern unsigned char vxCpuIdInitialApicId (void);

extern unsigned char vxCpuIdBitField (unsigned char fullId,
		                      unsigned char maxSubIdValue,
		                      unsigned char shiftCount);

extern unsigned int vxCpuIdMaxNumLPPerCore (void);

extern void vxCpuIdMapTopology (CPU_ID_TOPOLOGY *pCpuIdTopology, 
		                MP_APIC_DATA *pMpApicData);

extern void vxCpuIdTopology (void);
extern void vxCpuIdShowTopology (CPU_ID_TOPOLOGY *pSysCpuIdTopology);
extern UINT64 vxCpuIdGetFreq (void);
extern UINT64 vxCpuIdCalcFreq (VX_CPUID *vxCpuId);

#else

extern void vxCpuIdLibInit();
extern int vxCpuIdProbe();
extern STATUS vxCpuIdAdd();
extern STATUS vxCpuIdOverride();
extern void vxCpuIdShow();

extern BOOL vxCpuIdHWMTSupported ();
extern unsigned int vxCpuIdMaxNumLPPerPkg ();
extern unsigned int vxCpuIdMaxNumCoresPerPkg ();
extern unsigned int vxCpuIdBitFieldWidth ();
extern unsigned char vxCpuIdInitialApicId ();

extern unsigned char vxCpuIdBitField ();

extern unsigned int vxCpuIdMaxNumLPPerCore ();

extern void vxCpuIdMapTopology ();

extern void vxCpuIdTopology ();
extern void vxCpuIdShowTopology ();
extern UINT64 vxCpuIdGetFreq ();
extern UINT64 vxCpuIdCalcFreq ();

#endif  /* __STDC__ || __cplusplus */

#endif /* !_ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuIdLibh */
