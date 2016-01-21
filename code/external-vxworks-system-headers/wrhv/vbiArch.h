/* vbiArch.h - vbi architecture specific definitions */

/*
 * Copyright (c) 2008-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,28sep10,rab  add arm support 
01m,29apr10,pad  Moved extern C statement after include statements.
01l,23sep09,d_c  Defect WIND00183017 Fix WIND00183019 - sync with 18-Sep HV
                 DVD
01k,25jun09,to   cleanup for VxWorks 6.8
01j,26may09,md   adapted for VxWorks 6.7
01i,25may09,md   add endian order type defines
01h,17mar09,mpk  Cavium OCTEON MIPS64 port for hypervisor
01g,29jan09,mmi  add vbi/ to the header files path
01f,28jan09,mmi  check PENTIUM4 and PENTIUM, consider error case
01e,06feb09,to   test CPU_FAMILY to include arch specific file
01d,29jan09,rec  merge in from vxWorks6.6.
01c,27jan09,dtr  Build for PENTIUM4.
01b,26jan09,dtr  Check all CPUs.
01a,21jan08,mmi  written.
*/

#ifndef __INCvbiArchh
#define __INCvbiArchh

#include <vxWorks.h>

/* endian types selectable by the arch specific header files */

#define __VBI_LITTLE_ENDIAN 1234  /* least-significant byte first         */
#define __VBI_BIG_ENDIAN    4321  /* most-significant byte first          */
#define __VBI_PDP_ENDIAN    3412  /* LSB first in word, MSW first in long */

/* include the appropriate arch specific header file */

#include <wrhv/vbiTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (CPU == MIPSI64R2)
# include <wrhv/vbiMips64Arch.h>
#elif (CPU_FAMILY == PPC)
# include <wrhv/vbiPpcArch.h>
#elif (CPU_FAMILY == I80X86)
# include <wrhv/vbiX86Arch.h>
#elif (CPU_FAMILY == ARM)
# include <wrhv/vbiArmArch.h>
#else
# error "no arch header file included"
#endif

/* ensure the arch has specified a byte ordering */

#if !defined(__VBI_BYTE_ORDER)
# error Architecture has not defined a byte order!
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvbiArchh */
