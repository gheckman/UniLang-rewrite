/* cavCvmMemCtl.h - CVMMEMCTL register structure */

/*
* Copyright (c) 2008, 2011 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*

modification history
--------------------
01b,20jul11,d_c  Clean up SDK abstraction layer. Make file and function naming
                 consistent
01a,24sep08,pgh  Fix copyright.

DESCRIPTION

This module handles the initialization of the CVMMEMCTL register.

*/

#ifndef _INCcavCvmMemCtlh
#define _INCcavCvmMemCtlh


/* typedefs */

typedef union
{
    uint64_t u64;
    struct
    {
        uint64_t    tlbbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    l1cbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    l1dbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    dcmbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    ptgbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    wbfbist         : 1;    /**< RO 1 = BIST fail, 0 = BIST pass */
        uint64_t    reserved        : 22;   /**< Reserved */
        uint64_t    dismarkwblongto : 1;    /**< R/W If set, marked write-buffer entries time out the same as
                                                as other entries; if clear, marked write-buffer entries use the
                                                maximum timeout. */
        uint64_t    dismrgclrwbto   : 1;    /**< R/W If set, a merged store does not clear the write-buffer entry
                                                timeout state. */
        uint64_t    iobdmascrmsb    : 2;    /**< R/W Two bits that are the MSBs of the resultant CVMSEG LM word
                                                location for an IOBDMA. The other 8 bits come from the SCRADDR
                                                field of the IOBDMA. */
        uint64_t    syncwsmarked    : 1;    /**< R/W If set, SYNCWS and SYNCS only order marked stores; if clear,
                                                SYNCWS and SYNCS only order unmarked stores. SYNCWSMARKED has no
                                                effect when DISSYNCWS is set. */
        uint64_t    dissyncws       : 1;    /**< R/W If set, SYNCWS acts as SYNCW and SYNCS acts as SYNC. */
        uint64_t    diswbfst        : 1;    /**< R/W If set, no stall happens on write buffer full. */
        uint64_t    xkmemenas       : 1;    /**< R/W If set (and SX set), supervisor-level loads/stores can use
                                                XKPHYS addresses with VA<48>==0 */
        uint64_t    xkmemenau       : 1;    /**< R/W If set (and UX set), user-level loads/stores can use XKPHYS
                                                addresses with VA<48>==0 */
        uint64_t    xkioenas        : 1;    /**< R/W If set (and SX set), supervisor-level loads/stores can use
                                                XKPHYS addresses with VA<48>==1 */
        uint64_t    xkioenau        : 1;    /**< R/W If set (and UX set), user-level loads/stores can use XKPHYS
                                                addresses with VA<48>==1 */
        uint64_t    allsyncw        : 1;    /**< R/W If set, all stores act as SYNCW (NOMERGE must be set when
                                                this is set) RW, reset to 0. */
        uint64_t    nomerge         : 1;    /**< R/W If set, no stores merge, and all stores reach the coherent
                                                bus in order. */
        uint64_t    didtto          : 2;    /**< R/W Selects the bit in the counter used for DID time-outs
                                                0 = 231, 1 = 230, 2 = 229, 3 = 214. Actual time-out is between
                                                1× and 2× this interval. For example, with DIDTTO=3, expiration
                                                interval is between 16K and 32K. */
        uint64_t csrckalwys         : 1;    /**< R/W If set, the (mem) CSR clock never turns off. */
        uint64_t mclkalwys          : 1;    /**< R/W If set, mclk never turns off. */
        uint64_t wbfltime           : 3;    /**< R/W Selects the bit in the counter used for write buffer flush
                                                time-outs (WBFLT+11) is the bit position in an internal counter
                                                used to determine expiration. The write buffer expires between
                                                1× and 2× this interval. For example, with WBFLT = 0, a write
                                                buffer expires between 2K and 4K cycles after the write buffer
                                                entry is allocated. */
        uint64_t istrnol2           : 1;    /**< R/W If set, do not put Istream in the L2 cache. */
        uint64_t wbthresh           : 4;    /**< R/W The write buffer threshold. */
        uint64_t reserved2          : 2;    /**< Reserved */
        uint64_t cvmsegenak         : 1;    /**< R/W If set, CVMSEG is available for loads/stores in kernel/debug mode. */
        uint64_t cvmsegenas         : 1;    /**< R/W If set, CVMSEG is available for loads/stores in supervisor mode. */
        uint64_t cvmsegenau         : 1;    /**< R/W If set, CVMSEG is available for loads/stores in user mode. */
        uint64_t lmemsz             : 6;    /**< R/W Size of local memory in cache blocks, 54 (6912 bytes) is max legal value. */
    } s;
    } CAV_CVMMEMCTL_T;


/* functions */

extern void cavCvmMemCtlInit(void);


#endif /* _INCcavCvmMemCtlh */
