/* uncomp_fsm.h - AF_LOCAL/COMP protocol: Finite state machine */

/* Copyright 2003 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,30sep03,bwa  written.
*/

#ifndef __INCuncomp_fsmh
#define __INCuncomp_fsmh

#ifdef __cplusplus
extern "C" {
#endif

/* COMP state machine state definitions */

#define UNCOMPS_NSTATES    6   /* number of defined states */

/*        STATE          VALUE    [  WHO?  ] HOW & WHEN                      */
/* ------------------------------------------------------------------------- */
#define UNCOMPS_CLOSED     0   /* [  both  ] before connect()/after close()  */
#define UNCOMPS_REQUEST    1   /* [ client ] connect() issued before accept()*/
#define UNCOMPS_LISTENING  2   /* [ server ] listen() issued                 */
#define UNCOMPS_EXCHANGING 3   /* [  both  ] connect() accepted by accept()  */
#define UNCOMPS_DONE_SEND  4   /* [  both  ] shutdown (write) issued by self */
#define UNCOMPS_DONE_RECV  5   /* [  both  ] shutdown (write) issued by peer */

#ifdef __cplusplus
}
#endif

#endif /* __INCuncomp_fsmh */

