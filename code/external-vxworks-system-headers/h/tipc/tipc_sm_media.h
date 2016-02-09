/* tipc_sm_media.h - TIPC Shared Memory bearer external definitions */

/* Copyright (c) 2005-2006, 2010, Wind River Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */ 

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,01dec06,mze  name change during port of TIPC1.7.1 
01c,14apr05,bwa  updated following code review.
01b,14apr05,als  added licensing info; removed unneeded prototypes
01a,15fev05,bwa  written.
*/

#ifndef __INCsm_mediah
#define __INCsm_mediah

#include <smLib.h>
#include <smPktLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* types */

typedef struct _smTipcMediaInt  /* interrupt type and arguments */
    {                           /* ---------------------------- */
    int  type;                  /* 0x00: interrupt type         */
    int  arg1;                  /* 0x04: interupts argument #1  */
    int  arg2;                  /* 0x08: interupts argument #2  */
    int  arg3;                  /* 0x0c: interupts argument #3  */
    } SM_TIPC_MEDIA_INT;        /* 0x10: TOTAL SIZE             */

/* prototypes */

extern void   smTipcMediaPktHdrSetup    (const SM_ANCHOR * pAnchor);
extern STATUS smTipcMediaHeartbeatSetup (const int timeout);
extern STATUS smTipcMediaDriverSetup    (      SM_ANCHOR * pAnchor,
                                         const SM_TIPC_MEDIA_INT * pSmInt,
                                         const int cpu,
                                         const unsigned int qlen,
                                         const int numbuf,
                                         const int instance);
                                         
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCsm_mediah */

