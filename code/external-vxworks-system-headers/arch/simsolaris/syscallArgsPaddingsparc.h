/* System call padding for sparc - align 64-bit elements */


/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

#ifndef _ASMLANGUAGE

#include <syscall.h>

typedef struct syscall_args_padding_tbl {
	int	scNum;
	int	paddingEnum;
} SYSCALL_ARGS_PADDING_TBL;

SYSCALL_ARGS_PADDING_TBL syscallArgsPaddingTbl[] = {
	{ SYSCALL_NUMBER (SCG_STANDARD, 28), 0x20 },
	{ SYSCALL_NUMBER (SCG_VXWORKS, 31), 0x8 },
};

#endif	/* _ASMLANGUAGE */
