/* uefiVxWorksTypes.h - Define types for EFI/UEFI in Vxworks terms */

/*
 * Copyright (c) 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,15Oct07,d_z  derived from IA32/efibind.h from the Intel EFI Sample implementation 1.10.14.62
*/

#ifndef UEFIVXWORKSTYPES_H_INC
#define UEFIVXWORKSTYPES_H_INC


/*
 * Basic EFI types of various widths
 */

typedef uint64_t     UINT64;
typedef int64_t      INT64;

typedef uint16_t     UINT16;
typedef int16_t      INT16;
typedef uint8_t      UINT8;

#if defined(TOOL_FAMILY) && (TOOL_FAMILY != GNU)
typedef int8_t       INT8;
#endif

#undef VOID
#define VOID         void

typedef int32_t      INTN;
typedef uint32_t     UINTN;

/* EFI/UEFI Status handling macros */
#define EFIERR(a)           (0x80000000 | a)
#define EFI_ERROR_MASK      0x80000000
#define EFIERR_OEM(a)       (0xc0000000 | a)      

#define EFI_BAD_POINTER         0xFBFBFBFB  /* same as BAD_POINTER in EFI */
#define EFI_MAX_ADDRESS         0xFFFFFFFF  /* same as MAX_ADDRESS in EFI */


/*
 * Pointers must be aligned to these address to function
 */

#define MIN_ALIGNMENT_SIZE  4

#define ALIGN_VARIABLE(Value ,Adjustment) \
            (UINTN)Adjustment = 0; \
            if((UINTN)Value % MIN_ALIGNMENT_SIZE) \
                (UINTN)Adjustment = MIN_ALIGNMENT_SIZE - ((UINTN)Value % MIN_ALIGNMENT_SIZE); \
            Value = (UINTN)Value + (UINTN)Adjustment

/*
 * Define macros to build data structure signatures from characters.
 */

#define EFI_SIGNATURE_16(A,B)             ((A) | (B<<8))
#define EFI_SIGNATURE_32(A,B,C,D)         (EFI_SIGNATURE_16(A,B)     | (EFI_SIGNATURE_16(C,D)     << 16))
#define EFI_SIGNATURE_64(A,B,C,D,E,F,G,H) (EFI_SIGNATURE_32(A,B,C,D) | ((UINT64)(EFI_SIGNATURE_32(E,F,G,H)) << 32))

/*
 * EFIAPI - prototype calling convention for EFI function pointers
 * BOOTSERVICE - prototype for implementation of a boot service interface
 * RUNTIMESERVICE - prototype for implementation of a runtime service interface
 * RUNTIMEFUNCTION - prototype for implementation of a runtime function that is not a service
 * RUNTIME_CODE - pragma macro for declaring runtime code    
 */

#ifndef EFIAPI                   /* Forces EFI calling conventions reguardless of compiler options */
    #if _MSC_EXTENSIONS
        #define EFIAPI __cdecl   /* Force C calling convention for Microsoft C compiler */
    #else
        #define EFIAPI           /* Substitute expresion to force C calling convention */
    #endif
#endif

#define BOOTSERVICE
#define RUNTIMESERVICE
#define RUNTIMEFUNCTION

#define RUNTIME_CODE(a)         alloc_text("rtcode", a)
#define BEGIN_RUNTIME_DATA()    data_seg("rtdata")
#define END_RUNTIME_DATA()      data_seg()

#define VOLATILE    volatile

#define MEMORY_FENCE()    

#ifdef EFI_NO_INTERFACE_DECL
  #define EFI_FORWARD_DECLARATION(x)
  #define EFI_INTERFACE_DECL(x)
#else
  #define EFI_FORWARD_DECLARATION(x) typedef struct _##x x
  #define EFI_INTERFACE_DECL(x) typedef struct x
#endif

/*
 * Some compilers don't support the forward reference construct:
 *  typedef struct XXXXX
 *
 * The following macro provide a workaround for such cases.
 */
#ifdef NO_INTERFACE_DECL
#define INTERFACE_DECL(x)
#else
#define INTERFACE_DECL(x) typedef struct x
#endif


/*
 * Type definitions inserted to make the EFI files work.
 * these are not the correct definitions for these types, but the types
 * are not used in VxWorks.
 */
typedef void *EFI_DEVICE_PATH;

/* bootservices routines, N/A for us */

typedef void *SIMPLE_INPUT_INTERFACE;
typedef void *SIMPLE_TEXT_OUTPUT_INTERFACE;

#include "efierr.h" /* status definitions for UEFI/EFI */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* ifndef UEFIVXWORKSTYPES_H_INC */
