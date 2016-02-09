/* svDataCollectorLibP.h - System Viewer data collector header file */

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
01e,27jul11,wzc  PPM for SV (WIND00214625)
01d,26aug08,tcr  add Scopetools event class
01c,19aug08,tcr  update heading
01b,16may08,tcr  add SV_ prefix to class idents
01a,25apr08,tcr  created
*/

#ifndef __svDataCollectorLibPh
#define __svDataCollectorLibPh

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    SV_DATA_COLLECTOR_CTX = 1,
    SV_DATA_COLLECTOR_TSS = 2,
    SV_DATA_COLLECTOR_AIL = 3,
    SV_DATA_COLLECTOR_SIGNAL = 4,
    SV_DATA_COLLECTOR_EVENT = 5,
    SV_DATA_COLLECTOR_EDR = 6,
    SV_DATA_COLLECTOR_SAL = 7,
    SV_DATA_COLLECTOR_ST = 8,
    SV_DATA_COLLECTOR_PWR = 9
} SV_LOGGING_LEVEL_T;

STATUS svDataCollectorLibInit (void);
STATUS svDataCollectorsAdd (SV_LOGGING_LEVEL_T level);
STATUS svDataCollectorsRemove (SV_LOGGING_LEVEL_T level);
STATUS svDataCollectorsRemoveAll (void);


#ifdef __cplusplus
}
#endif


#endif /* __svDataCollectorLibPh */

