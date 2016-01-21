/* mnd_adapt.h - MIPC network device OS adaptation layer API */

/********************************************************************
The following file is dual licensed and is available under either 
the GPL version 2 or a Wind River commercial license.

*********************************************************************
Copyright (c) 2009-2011 Wind River Systems, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*********************************************************************
Copyright (c) 2009-2011 Wind River Systems, Inc.

The right to copy, distribute, modify, or otherwise make use
of this software may be licensed pursuant to the terms
of an applicable Wind River license agreement.

*********************************************************************/

/*
modification history
--------------------
01d,07jan11,jlk  Update license header
01c,26aug10,jlk  Make sure #ifdef __cplusplus starts after #includes
01b,24jun10,h_w  Upgrade to MND 2.1
01a,03jul09,spw  Written.
*/

#ifndef __INC_mnd_adapt_h
#define __INC_mnd_adapt_h

#ifdef _WRS_KERNEL
#include <vxWorks.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_KERNEL
typedef TASK_ID	MULTIOS_PROC_ID;
#else
typedef int		MULTIOS_PROC_ID;
#endif

/* OS adaptation routines that MND calls */

int mnd_proc_create(const char *name, int (*entry)(void *data), void *arg,
                    MULTIOS_PROC_ID *ppid);

int mnd_proc_delete(MULTIOS_PROC_ID pid);


#ifdef __cplusplus
}
#endif

#endif /* __INC_mnd_adapt_h */
