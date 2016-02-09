/* wtxtypes.h - WTX fundamental type definition */

/*
 * Copyright (c) 1995-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06x,27may10,pad  Moved extern C statement after include statements.
06w,11oct04,fle  Added WTX_HEARTBEAT_PERIOD definition
06v,30sep04,jeg  removed the field added in WTX_TOOL_DESC
06u,16sep04,jeg  updated WTX_TOOL_DESC structure to add lastTargetError field.
		 Added MAX_ERRNO_STR_LEN macro.
06t,03sep04,jeg  added WTX_COPROC_INFO_GET relative macros.
06s,21jul04,x_p  Symbols types are real bitfields
06r,18jun04,x_p  Added addOptions to wtx_process_context_def 
06q,07jun04,x_p  Added segment descriptor
06p,26apr04,x_p  Changed WTX_ACTION_TYPE
06o,14apr04,x_p  Changed REG_SET_TYPE to integer
06n,29mar04,fle  Added REGD_START_FILTER definition
06m,16mar04,x_p  Added cpuVariant / cpuFamilly
06n,26feb04,mil  Added SPE support for PPC85XX.
06m,17nov03,p_b  expanded WTX_TS_INFO
06l,15apr03,sn   Added WTX_DEMANGLER_STYLE_GET_CMD
06k,28aug03,x_p  Changed envBuf in ProcessCreate to envc,envv
06j,25jun03,x_p  Changed status values for better vxWorks compatibility
06i,29apr03,x_p  Changed WTX_SYMBOL_UNDEF to 0x10000000
06h,11apr03,lcs  Add new types required by windsh. Restore symbol types to T2.2
		 values.
06g,19feb03,p_b  fixed INT64 location in WTX_VALUE_T
06f,18feb03,p_b  wtx2 TCL compatibility and merge from T22-latest
06e,17feb03,x_p  Avoid warning if MAX_HOST_NAME already defined
06d,14feb03,c_c  reinstated coprocessor support.
06c,13feb03,elg  Add MAX_HOST_NAME definition.
06b,12feb03,elg  Fix compilation errors.
06a,06feb03,p_b  fixed PD_ID definition
05z,27jan03,p_b  canceled some changes (64 bits)
05y,16dec02,p_b  added WTX_TGTINFO_xxx types
05x,13dec02,p_b  changed TGT_XXX by WTX_TGT_XXX
05w,20nov02,p_b  merging margaux/T3. 64 bits support
05v,25apr02,x_p  Handle exceptions and core
05u,27mar02,x_p  Added WTX_EVENT_AGENT_MODE_TASK, WTX_EVENT_AGENT_MODE_EXTERN
05t,26mar02,x_p  Added WTX_EVENT_CTX_REGS_SET
05s,22mar02,x_p  Added WTX_EVENT_CTX_STEP,CONT,STOP
05r,19mar02,x_p  Changed NO_PARSE to NO_FILE_PARSING
05q,15mar02,x_p  Added env variables for pdCreate, option NO_PARSE
05p,20feb02,x_p  Added WTX_EVENT_CTX_DUMP
05o,12feb02,x_p  Added size in WTX_SYMBOL
05n,06feb02,x_p  Added WTX_SYMBOL_TRAMPOLINE
05m,01feb02,x_p  Added option WTX_BREAK_AT_INIT in WTX_PD_INFO_OPT
05l,22jan02,x_p  Added WTX_PD_INFO_OPT
05k,27nov01,x_p  Added threads list
05j,13nov01,x_p  Added new types for threads
05i,30oct01,x_p  Changed status values
05h,29oct01,x_p  Typo correction
05g,23oct01,x_p  Avoid conflit in status
05f,10oct01,x_p  Added event CTX_ATTACH/CTX_DETACH
05e,11sep01,x_p  Added CONTEXT_RUNNING for BSD
05d,22aug01,x_p  Merge from bsdos.temp
05c,18jun01,x_p  Changed BSD_TARGET/BSD_TARGET to BSD_TARGET
05b,29mar01,x_p  Added READLINK for tgtfs 
                 Added CONTEXT_BSD type
05a,28feb01,x_p  Added umask per tool for tgtfs
04z,26feb01,x_p  Added WTX_TGTFS_OPT_FOLLOW_LINK option + lstat 
04y,20feb01,x_p  Added WTX_SYM_FIND_IN_SHLIB type
04x,05feb01,x_p  Added new types for target filesystem ios
04w,23jan01,x_p  Merge from FCS
04v,22dec00,x_p  Added WTX_MODULES_INFO_SYNCHRO
04u,13dec00,x_p  Added WTX_TGTSVR_ENV_GET/SET types
04t,28nov00,x_p  Added WTX_TARGET_FILE_REMOVE_FORCE flag
04s,28nov00,x_p  Added WTX_TARGET_FILE_COPY_NOMKDIR flag
04r,20nov00,x_p  Added WTX_SHLIB_ADDR_GET for Linux Targets
04q,18sep00,mts  Changed WTX_SYMBOL_UNDEF value from 0 to 0x10000000
04p,12sep00,c_c  Modified wtx_vxworks_info and wtx_rt_info struct.
04o,31aug00,bpn  Added WTX_EVENT_PD_INITIALIZED event.
04n,25aug00,p_b  added missing WTX_LOAD options.
04m,09aug00,bpn  Added pdInitialized field in WTX_TS_INFO structure for the
                 emulators.
04l,07aug00,mts  Added WTX_LOADER_LOAD_MODE_GET_CMD define
04k,28jul00,bpn  Removed WTX_LOAD_STRICT_ORDER_LOAD. Added WTX_UNLOAD_FORCE,
                 WTX_MEM_WRITE_FORCE constants and wtx_load_mode enum type.
04j,19jun00,c_c  Updated doc.
04i,16jun00,c_c  Added referencing module array in WTX_SYMBOL.
04h,30may00,p_b  added VIO_CLOSE_ON_EXIT feature.
04g,04may00,fle  fixed WTX_FLAGS values
04f,30mar00,mts  Renamed CPU_THUMB in CPU_SIM (small instruction mode)
04e,23mar00,mts  Added CPU_THUMB
04d,10mar00,c_c  Added new fields to allow support load and run and C++.
04c,10mar00,elg  Modify WTX_RT_INFO.
04b,25feb00,fle  moved WTXREGD_TGTSVR_ARGS from wtxregd.c to here in
                 WTX_TGTSVR_ARGS for the wtxMsg layer to be able to start a
                 target server
04a,23feb00,bpn  Added linkPath and pdAttachTo  fields in WTX_PD_DESC structure.
                 Added WTX_EVENT_CTX_UPDATE.
03z,23feb00,p_b  Added WTX2.0 out of order load compatibility.
03y,10feb00,fle  added a host field to the WTX_LOG_ACTION
03x,01feb00,bpn  Added WTX_EVENT_TGT_RECOVERED.
03w,01feb00,fle  made pFunc parameter of wtxAsyncNotifyEnable() be a
                 WTX_EVENT_HANDLER rather than a FUNCPTR
03v,20jan00,dbt  Added user service facility.
03u,13jan00,bpn  Added WTX_EVENT_TGT_LOST and WTX_EVENT_TS_POSTMORTEM.
03t,20dec99,wkn  Added WTX_SYMBOL_SECTION
03s,14dec99,p_b  changed wtx_pd_context_desc in wtx_pd_context_def.
                 fixed typos & expanded many comments for DOC clarification.
03r,13dec99,mts  Added new LOAD and SYMBOL enum
03q,25nov99,fle  implemented registry log facility
03p,23nov99,elg  Add float support in WDB_FUNC_CALL.
03o,19nov99,c_c  Added WTX_MEM_CACHE_BYPASS define.
03n,12nov99,kk   update PD options
03m,28oct99,dbt  Added support for trigger eventpoints.
03l,27oct99,fle  added new WTX PD types since new PD types values in pdLib.h
03k,25oct99,c_s  fix dubious enum syntax
03j,21oct99,p_b  removed service management structures.
                 added WTX_SYM_FIND_IN_ALL_PD.
03i,21oct99,fle  added definition of WTX_CONNECTION_TIMEOUT value.
03h,29sep99,fle  added the WTX_TGTSVR_ACTION_TYPE and WTX_REG_LOG_ACTION_TYPE
                 new type for registry
03g,29sep99,c_c  Added SYMBOL_PENDING symbol type.
o3f,25aug99,p_b  added WTX_SYM_FIND_BY_EXACT_VALUE.
03e,19aug99,fle  added nElSymbols to the WTX_SYM_FIND_CRITERIA structure
03d,27jul99,p_b  added WTX_SYMBOL_XXX.
03c,23jul99,fle  changed the PD_ID in WTX_TOOL_DESC into a WTX_TGT_ADDR_T
03b,23jul99,p_b  added comments.
03a,22jul99,fle  made WTX_MOD_FIND_CRITERIA pdId a WTX_TGT_ADDR_T
02z,20jul99,fle  made vmutex include in HOST define
02y,16jul99,fle  moved part of the old wtxp.h in here
02x,09jul99,fle  added WTX_SYMBOL_TYPE enum
		 + moved N_DASM_INST_DEFAULT from wtx.h to here
		 + defined WTX_PROT_VERSION for xdrs
02w,08jul99,p_b  Added WTX_VIO_LINK_CMD, WTX_VIO_UNLINK_CMD, WTX_SOCKET,
                 WTX_TOOL_NUM_GET_CMD, WTX_VIO_LINK_DESC.
02v,07jul99,p_b  added WTX_SYM_UNDF, WTX_MODULE, WTX_MODULE_LIST.
02u,07jul99,fle  renamed WTX_PD_FLAGS into WTX_PD_TYPE
02t,06jul99,c_c  Added wtx_kill_context struct.
02s,30jun99,p_b  Added WTX_MOD_FIND_CRITERIA struct.
02r,29jun99,p_b  Added WTX_SYM_FIND_CRITERIA struct.
02t,05jul99,c_c  Implemented PD context definition.
02s,02jul99,c_c  Changed some WTX_LOAD_COMMAND values.
02r,29jun99,fle  added WTX_PD_DESC and WTX_PD_DESC_Q definitions
		 + added WTX_PD_FLAGS enum
02q,28jun99,fle  added wtxMsgExchangeControl() related types
02p,23jun99,c_c  changed UINT32 to WTX_TGT_ADDR_T for pdId
02o,22jun99,c_c  Added lastError in TOOL_DESC struct.
02n,14jun99,fle  added WTX_VALUE_WITH_PD type to transfer values with a PD ID
02m,07jun99,c_c  Added a PD_ID in the TOOL_DESC structure.
02l,02jun99,c_c  some ptr implementation.
02k,23feb99,c_c  Implemented an API to get the target IP address (SPR #25044).
02j,29jan99,dbt  doc: indicate which elements of WTX_CONTEXT_TYPE are
                 implemented.
02i,12jan99,dbt  indicated that WTX_ACTION_STOP_ALL is not implemented (SPR
                 #22081).
02h,18sep98,pcn  Implement wtxObjModuleInfoAndPathGet.
02g,04sep98,pcn  Added WTX_EVENT_EVTPT_ADDED, WTX_EVENT_EVTPT_DELETED.
02f,18aug98,pcn  Add WTX_SVC_TYPE description.
02e,19jun98,pcn  Added new flags for the asynchronous load.
02d,16jun98,pcn  Changed separator character from "_" to " ".
02c,24apr98,pcn  Changed WTX_ASYNC_HEADER_SIZE.
02b,03apr98,pcn  WTX 2: added WTX_EVENT_TS_KILLED used by the asynchronous
                 notification.
02a,24mar98,dbt  added WTX context status type.
01z,17mar98,pcn  WTX 2: changed WTX_ALL_MODULE_CHECK, MTU. Removed new event
                 types.
01y,12mar98,pcn  WTX 2: added new wtx_event_type.
01x,02mar98,pcn  WTX 2: defined strings for WTX_COMMAND_SEND,
                 WTX_OBJ_MODULE_CHECKSUM, OBJ_MODULE_LOAD_2, WTX_ASYNC_NOTIFY.
                 Changed WTX_EVENT_BREAKPOINT in WTX_EVENT_HW_BP.
01w,29aug97,fle  Adding WTX_MAX_DASM_INST_CNT constant.
01v,31dec96,dgp  doc: more spelling corrections
01u,06dec96,dgp  doc: correct spelling
01t,30sep96,elp  put in share/ (SPR# 6775).
01s,04sep96,dgp  doc: removed WTX_O_RDWR from WTX_OPEN_FLAG since no longer
		 supported per SPR #5959
01r,17jun96,p_m  added flags for WTX_OPEN (SPR# 4941).
01q,26may95,p_m  added WTX_MAX_PATTERN_LEN.
01p,23may95,p_m  changed WTX_CTX... and WTX_REG_SET... values.  Took care
		 of wtx_event_type comments length for manual generation.
01o,19may95,tpr  moved WTX_TGT_ADDR_T and WTX_TGT_ARG_T in host.h.
          + p_m  removed DETECTION related stuff.
01m,17may95,s_w  extended WTX_EVENT_TYPE to have all Target Server generated
                 events. Because WTX_EVENT_TYPE is mapped to WDB_EVENT_TYPE
		 in the Target Server event numbering was made to match
		 for event types 0 through 8.
01l,16may95,p_m  added object kill operations defines.
01k,09may95,p_m  removed WTX_CORE from WTX_DESC and WTX_DESC_Q.
01j,05may95,p_m  changed WTX_STATUS and WTX_REQUEST type to unsigned long.
                 added protocol version number in WTX_CORE.
01i,04may95,s_w  removed include of <rpc/rpc.h> and typedef of WTX_ID. Added
		 WTX_MAX_xxx limit defines that were in wtx.h. Remove HWTX
		 definition that belongs in wtx.h
01h,20apr95,p_m  integrated more WIN32 changes.
01g,08apr95,p_m  added HWTX and _WTX.
01f,04apr95,p_m  added WTX agent mode type.
01e,03apr95,p_m  get rid 0f 0x0 in wtx_action_type.
01d,30mar95,p_m  added new types to completely separate WTX from the
		 agent protocols. removed #include "comtypes.h".
01c,15mar95,p_m  changed #include "vxWorks.h" to #include "host.h".
01b,10jan95,p_m  added basic types.  added #include "comtypes.h" and
		 #include "wtxerr.h".  cleanup.
01a,20jan95,p_m  written.
*/

#ifndef __INCwtxtypesh
#define __INCwtxtypesh

#ifdef HOST
#   include <host.h>
#   include <vmutex.h>
#   ifdef WIN32
#	include <winsock.h>
#   endif /* WIN32 */
#else
#   include <vxWorks.h>
#   include <wdb/wdb.h>
#   define WTX_OK		0
#   define WTX_ERROR		(-1)
#endif /* HOST */

#include <lstLib.h>
#include <sllLib.h>
#include <wtxerr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* limits */

#define WTX_MAX_SYM_CNT		256     /* maximum symbols in list            */
#define WTX_MAX_DASM_INST_CNT   256     /* maximum instructions in list       */
#define WTX_MAX_EVTPT_CNT	256     /* maximum eventpoints in list        */
#define WTX_MAX_MODULE_CNT	1000    /* maximum modules in list            */
#define WTX_MAX_SERVICE_CNT	500     /* valid service numbers: 0 to 500    */
#define WTX_MAX_ARG_CNT		10      /* maximum arguments for func calls   */
#define WTX_MAX_SYM_TBL_CNT	256     /* maximum symbol tables              */
#define WTX_MAX_VIO_DATA	512	/* maximum bytes per VIO transaction  */
					/* this number should be the same     */
					/* as the buffer size used on WDB     */
					/* virtual I/O devices                */
#define WTX_MAX_PATTERN_LEN	512	/* maximum length of pattern for      */
					/* WTX_MEM_SCAN service               */
#define WTX_MAX_FILENAME_LEN	80	/* max length of a filename           */
#define WTX_MAX_OBJ_SEG_CNT	40	/* maximum num of segment in a module */
#define WTX_MAX_SECTION_CNT	40	/* maximum num of section in an       */
					/* object file                        */

#define WTX_MAX_WDB_SVC_CNT	10	/* maximum num of WDB services in an  */
					/* WDB service object module          */

#ifdef	MAXHOSTNAMELEN			/* FIXME - elg: temporary compilation */
#ifndef MAX_HOST_NAME
#define	MAX_HOST_NAME		MAXHOSTNAMELEN
#endif
#else					/* error fix			      */
#ifndef MAX_HOST_NAME
#define	MAX_HOST_NAME		64
#endif
#endif
#define	MAX_ERRNO_STR_LEN	80	/* maximum length of an errno string  */

/* coprocessor data macros */

#define WTX_COPROC_HAS_FPP		1
#define WTX_COPROC_HAS_ALTIVEC		2
#define	WTX_COPROC_HAS_SPE		3
#define	WTX_COPROC_HAS_DSP		4

/* virtual I/O control operations */

#define WTX_CTL_VIO_REDIRECT		1
#define WTX_CTL_VIO_CLOSE_ON_EXIT	2

/* object kill operations */

#define WTX_OBJ_KILL_DESTROY	1	/* terminate                          */
#define WTX_OBJ_KILL_RESTART	2	/* start again                        */

/* load options */

#define WTX_LOAD_FROM_TOOL              0x1  /* tool uploads object to tgtsvr */
#define WTX_LOAD_FROM_TARGET_SERVER     0x2  /* target server uploads the obj */
#define WTX_LOAD_ASYNCHRONOUSLY         0x4  /* load is done asynchronously   */
#define WTX_LOAD_NO_UNLOAD_EXISTING     0x10 /* does not unload a module if   */
                                             /* already loaded                */

/* unload options */

#define WTX_UNLOAD_KEEP_BREAKPOINTS	0x1  /* don't delete breakpoints on   */
					     /*	unload */
#define WTX_UNLOAD_FORCE		0x2  /* unload module even if it is   */
                                             /* used                          */
#define WTX_UNLOAD_COMP_NO_TERM		0x10 /* don't call termination rtn    */
#define WTX_UNLOAD_CPLUS_XTOR_AUTO	0x20 /* automatically call destructor */
#define WTX_UNLOAD_CPLUS_XTOR_MANUAL	0x40 /* manually call destructor      */

#define WTX_UNLOAD_SYNC			0x10000 /* internal use only          */

/* Target File Copy options */
#define WTX_TARGET_FILE_COPY_NOMKDIR	0x1	/* Do not create subdirs on target */
#define WTX_TARGET_FILE_COPY_CHECK	0x2	/* Check for existing file */

/* Target File Remove options */
#define WTX_TARGET_FILE_REMOVE_FORCE	0x1	/* Force deletion even if not in WINDHOME_BASE */

/* strings passed in WTX_COMMAND_SEND */

#define SEPARATOR			" "
#define WDB_LOGGING_ON_CMD		"wdbLoggingOn"
#define WDB_LOGGING_OFF_CMD		"wdbLoggingOff"
#define WTX_LOGGING_ON_CMD		"wtxLoggingOn"
#define WTX_LOGGING_OFF_CMD		"wtxLoggingOff"
#define ALL_LOGGING_OFF_CMD		"allLoggingOff"
#define WTX_ASYNC_NOTIFY_ENABLE_CMD	"wtxAsyncNotifyEnable"
#define WTX_ASYNC_NOTIFY_DISABLE_CMD	"wtxAsyncNotifyDisable"
#define WTX_OBJ_KILL_CMD		"wtxObjKill"
#define WTX_OBJ_KILL_DESTROY_CMD	"wtxObjKillDestroy"
#define WTX_OBJ_KILL_RESTART_CMD	"wtxObjKillRestart"
#define WTX_TS_LOCK_CMD			"wtxTsLock"
#define WTX_TS_LOG_GET_CMD		"wtxTsLogGet"
#define WTX_TS_UNLOCK_CMD		"wtxTsUnlock"
#define WTX_TARGET_RESET_CMD		"wtxTargetReset"
#define WTX_LOADER_LOAD_MODE_GET_CMD	"wtxLoadModeGet"
#define WTX_LOAD_CANCEL_CMD		"wtxObjModuleLoadCancel"
#define WTX_TARGET_IP_ADDRESS_CMD	"wtxTargetIpAddressGet"
#define WTX_TOOL_NUM_GET_CMD		"wtxToolNumGet"
#define WTX_VIO_LINK_CMD		"wtxVioLink"
#define WTX_VIO_UNLINK_CMD		"wtxVioUnlink"
#define WTX_SHLIB_ADDR_GET		"wtxShlibAddrGet"
#define WTX_COPROC_INFO_GET		"wtxCoprocInfoGet"
#define WTX_COPROC_TO_STRING_GET	"wtxCoprocToStringGet"
#define WTX_TGTSVR_ENV_GET		"wtxTgtsvrEnvGet"
#define WTX_TGTSVR_ENV_SET		"wtxTgtsvrEnvSet"
#define WTX_MODULES_INFO_SYNCHRO	"wtxModulesInfoSynchro"
#define WTX_TARGET_TOOLNAME_GET_CMD	"wtxTargetToolNameGet"
#define WTX_DEMANGLER_STYLE_GET_CMD	"wtxDemanglerStyleGet"
#define WTX_LAST_RUNTIME_ERROR_GET	"wtxLastRuntimeErrorGet"

#ifdef WIN32
#define WTX_SOCKET SOCKET
#else
#define WTX_SOCKET int
#endif

#define LOG_WDB     0
#define LOG_WTX     1
#define LOG_ALL     2
#define LOG_OFF     0
#define LOG_ON      1

#define WTX_ALL_MODULE_CHECK    "WTX_ALL_MODULE_CHECK"
#define WTX_ALL_MODULE_ID       1       /* for WTX_OBJ_MODULE_CHECKSUM        */
#define WTX_FILE_SLICE_SIZE     8192    /* for WTX_OBJ_MODULE_LOAD            */

#define WTX_MTU    		1460    /* for WTX_OBJ_MODULE_LOAD            */
#define WTX_ASYNC_HEADER_SIZE   36      /* for WTX_ASYNC_NOTIFY               */

/* load module flags */



#define WTX_LOAD_NO_SYMBOLS  		0x1		/* No symbols added to the target  */
							/* symbol table                    */
#define WTX_LOAD_LOCAL_SYMBOLS 		0x2		/* Only internal symbols added to  */
							/* the target symbol table         */
#define WTX_LOAD_GLOBAL_SYMBOLS 	0x4		/* Only external symbols added to  */
							/* the target symbol table         */
							/* All symbols added to the target */
							/* symbol table                    */
#define	WTX_LOAD_SYMS_AS_ENTRIES	0x8
#define WTX_LOAD_HIDDEN_MODULE     	0x10		/* Don't display module info with  */
							/* moduleShow()                    */
#define WTX_LOAD_FULLY_LINKED      	0x20		/* No relocation required          */
#define WTX_LOAD_NO_DOWNLOAD       	0x40    	/* No relocation required, nothing */
                                        		/* downloaded to the target memory */
#define WTX_LOAD_COMMON_MATCH_NONE  	0x100		/* Only alloc, no search (default) */
#define WTX_LOAD_COMMON_MATCH_USER	0x200		/* Core file excluded from search  */
#define WTX_LOAD_COMMON_MATCH_ALL   	0x400		/* Core file included in search    */
#define WTX_LOAD_COMMON_MATCH_GLOB	0x800
#define WTX_LOAD_BAL_OPTIM		0x1000		/* set i960 branch-and-link optim. */
#define WTX_LOAD_NO_AUTORUN		0x4000
#define WTX_LOAD_COMP_NO_INIT		0x8000
#define WTX_LOAD_FILE_OUTPUT 		0x10000		/* write segments in a file (testing )*/
#define WTX_LOAD_MODULE_REPLACED	0x20000
#define WTX_LOAD_CPLUS_XTOR_AUTO 	0x100000	/* Automatic C++ ctor/dtor strategy */
#define WTX_LOAD_CPLUS_XTOR_MANUAL  	0x200000 	/* Manual off C++ ctor/dtor strategy */
#define WTX_LOAD_MODULE_INFO_ONLY	0x1000000	/* module synchronization */
#define WTX_LOAD_LOADED_BY_TGTSVR	0x2000000	/* module synchronization */

#define WTX_LOAD_ALL_SYMBOLS	(WTX_LOAD_LOCAL_SYMBOLS|WTX_LOAD_GLOBAL_SYMBOLS)
#define WTX_LOAD_CORE_FILE	(WTX_LOAD_FULLY_LINKED|WTX_LOAD_NO_DOWNLOAD)
#define WTX_LOAD_SYMTAB_FILE	(WTX_LOAD_FULLY_LINKED|WTX_LOAD_NO_DOWNLOAD)

/* load progress flags */

#define WTX_LOAD_INIT		0x1	/* initializations are done           */
#define WTX_LOAD_RELOC		0x2	/* relocation phase                   */
#define WTX_LOAD_DOWNLOAD	0x4	/* download to the Target             */
#define WTX_LOAD_DONE		0x8	/* load done                          */
#define WTX_LOAD_ERROR		0x10	/* error during the load              */

/* find critreria flags for wtxSymFind() & wtxSymListGet() */

#define WTX_SYM_FIND_IN_ALL_PD          ((UINT32)-1)
#define WTX_SYM_FIND_BY_NAME		0x2
#define WTX_SYM_FIND_BY_VALUE		0x4
#define WTX_SYM_FIND_BY_EXACT_NAME	0x8
#define WTX_SYM_FIND_BY_EXACT_VALUE     0x10
#define WTX_SYM_FILTER_ON_MODULE_NAME	0x20
#define WTX_SYM_FILTER_ON_MODULE_ID	0x40
#define WTX_SYM_FILTER_ON_TYPE		0x80
#define WTX_SYM_FILTER_ON_REFERENCE	0x100
#define WTX_SYM_FIND_IN_SHLIB		0x200

/* symbol mask for text, data, bss, abs, comm */

#define WTX_SYM_BASE_MASK		0x0000001e

/* find critreria flags for wtxObjModuleList() & wtxObjModuleFind() */

#define WTX_MOD_FIND_IN_ALL_PD          ((UINT32)-1)
#define WTX_MOD_FIND_ALL		0x0
#define WTX_MOD_FIND_BY_NAME		0x2
#define WTX_MOD_FIND_BY_ID		0x4
#define WTX_MOD_FILTER_ON_REF           0x8

/* WTX_OBJ_MODULE_INFO_GET constant */

#define WTX_OBJ_MODULE_PATHNAME_GET	"WTX_OBJ_MODULE_PATHNAME_GET"

/* PD related constants */

#define WTX_PD_ALL		((WTX_TGT_ADDR_T)(-1))	/* specify all PDs    */
#define WTX_PD_CURRENT		((WTX_TGT_ADDR_T)(0))	/* specify current PD */

#define N_DASM_INST_DEFAULT     10      /* default # of disassembled insts    */
#define WTX_PROT_VERSION	4	/* protocol version 4                 */

/* connection defines */

#define WTX_CONNECTION_TIMEOUT  30000   /* rPC connection timeout : 30 secs   */

/* memory operations options */

#define WTX_MEM_CACHE_BYPASS	0x1	/* don't use Tgtsvr cache for reading */
#define WTX_MEM_WRITE_FORCE	0x2	/* force the write protection	      */

/* wtxregd start filter */

#define REGD_START_FILTER	"([^ \t]*tgtsvr(.exe)?[ \t\n$]+)|"\
				"([^ \t]*dfwserver(.exe)?[ \t\n$]+)"

/* wtxregd/tgtsvr heartbeat period */

#define WTX_HEARTBEAT_PERIOD	10

/* typedefs */

typedef unsigned long      WTX_TGT_ADDR_T;   /* target address */
typedef unsigned long      WTX_TGT_ARG_T;    /* target function argument */
typedef unsigned long      WTX_TGT_ID_T;     /* target identifier */
typedef long               WTX_TGT_INT_T;    /* target function integer */

typedef enum cpu_info		/* available cpu information types */
    {
    CPU_INFO_NONE	= 0,	/* no information needed           */
    ARCH_DIR		= 1,	/* target architecture directory   */
    LEADING_CHAR	= 2,	/* symbols prepended character     */
    DEMANGLER		= 3,	/* target symbol demangler name    */
    CPU_NAME		= 4,	/* target CPU name                 */
    CPU_SIM		= 5,	/* target small instruction mode   */
    ARCH_OBJ_DIR	= 6     /* target architecture object dir  */
    } CPU_INFO;

typedef struct cpu_info_type	/* CPU information type        */
    {
    CPU_INFO	param;		/* parameter value             */
    char *	string;		/* parameter associated string */
    char *	section;	/* parameter section           */
    } CPU_INFO_TYPE;

typedef enum wtx_endian_t
    {
    WTX_ENDIAN_BIG	= 0,
    WTX_ENDIAN_LITTLE	= 1,
    WTX_ENDIAN_UNKNOWN	= WTX_ERROR
    } WTX_ENDIAN_T;

typedef enum wtx_symbol_type
    {
    WTX_SYMBOL_GLOBAL    = 0x00000001, /* global (external) (ORed)            */
    WTX_SYMBOL_ABS       = 0x00000002, /* absolute                            */
    WTX_SYMBOL_TEXT      = 0x00000004, /* text                                */
    WTX_SYMBOL_DATA      = 0x00000008, /* data                                */
    WTX_SYMBOL_BSS       = 0x00000010, /* bss                                 */
    WTX_SYMBOL_COMM      = 0x00000020, /* common symbol                       */
    WTX_SYMBOL_LOCAL     = 0x00000040, /* local                               */
    WTX_SYMBOL_THUMB     = 0x00000080, /* thumb function                      */
    WTX_SYMBOL_UNDEF	 = 0x00000100, /* symbol that is not already resolved */
    WTX_SYMBOL_BAL_ENTRY = 0x00000200, /* i80960 BAL entrypoint to func, obs. */
    WTX_SYMBOL_SDA       = 0x00000400, /* symbols related to a PPCSDA section */
    WTX_SYMBOL_SDA2      = 0x00000800, /* symbols related to a PPCSDA2 section*/
    WTX_SYMBOL_MIPS16    = 0x00001000, /* mips16 function - unlikely clash    */ 
    WTX_SYMBOL_LTE	 = 0x00002000, /* linkage table entry 		      */
    WTX_SYMBOL_ENTRY     = 0x00004000, /* entry Point                         */
    WTX_SYMBOL_INIT      = 0x00008000, /* initialization routine              */
    WTX_SYMBOL_TERM      = 0x00010000, /* termination routine                 */
    WTX_SYMBOL_SYSPAGE   = 0x00020000, /* symbols related to the system page  */
    WTX_SYMBOL_WEAK      = 0x00040000, /* weak symbol                         */
    WTX_SYMBOL_SECTION   = 0x00080000, /* section descriptor		      */
    WTX_SYMBOL_TRAMPOLINE= 0x00100000, /* trampoline descriptor		      */
    WTX_SYMBOL_HOST	 = 0x00200000, /* used by host shell for host funcs   */
    WTX_SYMBOL_UPDATE_REL= 0x00400000, /* symbol that has some new reloc info */
    WTX_SYMBOL_UPDATE    = 0x00800000, /* symbol to update (symbol table sync)*/
    WTX_SYMBOL_PENDING	 = 0x01000000, /* pending symbol (Out of Order Load)  */
    WTX_SYMBOL_EXTENTED  = 0x80000000  /* For future use 		      */
    } WTX_SYMBOL_TYPE;

typedef enum wtx_async_load_info_state
    {
    WTX_LOAD_PENDING		= 0,
    WTX_LOAD_INITIALIZED	= 1,
    WTX_LOAD_DOWNLOADING	= 3
    } WTX_ASYNC_LOAD_INFO_STATE;

/* ----------------------- registry related typedefs ------------------------ */

typedef enum wtx_tgtsvr_action_type
    {
    WTX_TGTSVR_START		= 0x01,	/* tell Registry to start a Tgtsvr    */
    WTX_TGTSVR_STOP		= 0x02,	/* tell Registry to stop a Tgtsvr     */
    WTX_TGTSVR_REMOTE_START	= 0x03,	/* internal use for Registry          */
    WTX_TGTSVR_REMOTE_STOP	= 0x04	/* internal use for Registry          */
    } WTX_TGTSVR_ACTION_TYPE;

typedef enum wtx_log_action_type	/* log related actions (OR-able)      */
    {
    WTX_LOG_GET		= 0x01,		/* get part of the log                */
    WTX_LOG_UPDATE	= 0x02,		/* get an update of the log           */
    WTX_LOG_SET		= 0x04		/* set part of the log                */
    } WTX_LOG_ACTION_TYPE;

/* ------------------------- free related typedefs -------------------------- */

typedef struct wtx_free_desc		/* WTXResultFree parameters           */
    {
    void *		pToFree;	/* pointer to free                    */
    FUNCPTR		pFreeRtn;	/* function that should free pointer  */
    void *		pMsgToFree;	/* message pointer containing pToFree */
    FUNCPTR		pMsgFreeRtn;	/* routine to use to free pMsgToFree  */
    } WTX_FREE_DESC;

/* ------------------------- WTX handler definitions ------------------------ */

typedef long		BOOL32;		/* boolean                            */
typedef unsigned long	WTX_STATUS;	/* WTX status value                   */
typedef unsigned long 	WTX_REQUEST;	/* WTX request number                 */

#define WTX_FPP_MASK 		0x0001
#define WTX_ALTIVEC_MASK	0x0002
#define WTX_DSP_MASK		0x0004
#define WTX_SPE_MASK		0x0008

typedef enum wtx_coprocessor_bitshift
    {
    WTX_FPP_BITSHIFT	= 0,
    WTX_ALTIVEC_BITSHIFT= 1,
    WTX_DSP_BITSHIFT	= 2,
    WTX_SPE_BITSHIFT	= 3,
    WTX_LAST_BITSHIFT   = 16
    }	WTX_COPROCESSOR_BITSHIFT;

typedef BOOL32 (*WTX_HANDLER_FUNC) ();
typedef struct _wtx_handler_t * WTX_HANDLER_T;
typedef struct _wtx_handler_t
    {
    WTX_HANDLER_FUNC	pFunc;		/* WTX error handler function pointer */
    void *		pClientData;	/* client data descriptor             */
    WTX_HANDLER_T	prev;		/* previous handler in list           */
    } _WTX_HANDLER_T;

/* ------------------------- wtx handler definition ------------------------- */

typedef struct _wtx * HWTX;		/* WTX Handle                         */

/* ----------------------------- useful typedefs ---------------------------- */

/*
 * WTX_EVENT_TYPE - The class of events that can be generated by the
 * Target Server. User defined event types start at 0x100, event types
 * numbered 22 through 255 are reserved for future use.
 */

typedef enum wtx_event_type
    {
    WTX_EVENT_NONE         = 0,	    /* no event                               */
    WTX_EVENT_CTX_START    = 1,	    /* a target context was created           */
    WTX_EVENT_CTX_EXIT     = 2,	    /* a target context was deleted           */
    WTX_EVENT_TEXT_ACCESS  = 3,	    /* a target text access (breakpoint)      */
    WTX_EVENT_DATA_ACCESS  = 4,	    /* a target data access (watchpoint)      */
    WTX_EVENT_EXCEPTION    = 5,	    /* a target exception occurred            */
    WTX_EVENT_VIO_WRITE    = 6,	    /* a target VIO write occurred            */
    WTX_EVENT_HW_BP        = 7,     /* a target breakpoint: obsolete, use     */
                                    /* WTX_EVENT_TEXT_ACCESS instead          */
    WTX_EVENT_CALL_RETURN  = 8,     /* a target function call returned        */
    WTX_EVENT_USER         = 9,     /* a target agent user defined event      */
    WTX_EVENT_UNKNOWN      = 10,    /* an unknown target event                */
    WTX_EVENT_TGT_RESET    = 11,    /* the Target was reset                   */
    WTX_EVENT_SYM_ADDED    = 12,    /* a symbol added to the symbol table     */
    WTX_EVENT_SYM_REMOVED  = 13,    /* a symbol removed from the symbol table */
    WTX_EVENT_OBJ_LOADED   = 14,    /* an object file was loaded              */
    WTX_EVENT_OBJ_UNLOADED = 15,    /* an object file was unloaded            */
    WTX_EVENT_TOOL_ATTACH  = 16,    /* a tool attached to Target Server       */
    WTX_EVENT_TOOL_DETACH  = 17,    /* a tool detached from Target Server     */
    WTX_EVENT_TOOL_MSG     = 18,    /* a tool to tool message                 */
    WTX_EVENT_TS_KILLED    = 19,    /* the Target Server was reset            */
    WTX_EVENT_EVTPT_ADDED  = 20,    /* a new event point is added 	      */
    WTX_EVENT_EVTPT_DELETED= 21,    /* an event point had been deleted	      */
    WTX_EVENT_TRIGGER	   = 22,    /* a trigger has been hit on the Target   */
    WTX_EVENT_TGT_LOST     = 23,    /* contact with the target is lost        */
    WTX_EVENT_TS_POSTMORTEM= 24,    /* target server in postmortem mode       */
    WTX_EVENT_TGT_RECOVERED= 25,    /* contact with the target is recovered   */
    WTX_EVENT_CTX_UPDATE   = 26,    /* a target context has changed           */
    WTX_EVENT_PD_INITIALIZED	= 27,	/* the pdList is now initialized      */
    WTX_EVENT_CTX_ATTACH   = 28, /* Attach on a process 		      */
    WTX_EVENT_CTX_DETACH   = 29, /* Detach from a process 		      */
    WTX_EVENT_CTX_DUMP	   = 30, /* Catch when a process dumps 		      */
    WTX_EVENT_CTX_STOP	   = 31, /* A context is stopped  	    	      */
    WTX_EVENT_CTX_CONT	   = 32, /* A context is continued  	    	      */
    WTX_EVENT_CTX_STEP	   = 33, /* A context is stepped  	    	      */
    WTX_EVENT_CTX_REGS_SET = 34, /* A context has registers set	    	      */
    WTX_EVENT_AGENT_MODE_TASK = 35, /* User mode has been set		      */
    WTX_EVENT_AGENT_MODE_EXTERN = 36, /* System mode has been set	      */
    WTX_EVENT_TS_RESTART   = 37,    /* Target server will restart 	      */
    WTX_EVENT_OTHER        = 0x100, /* user defined or unrecognized event     */
    WTX_EVENT_INVALID	   = WTX_ERROR   /* invalid/unidentifiable event      */
    } WTX_EVENT_TYPE;

typedef enum wtx_context_type		/* types of context                   */
    {
    WTX_CONTEXT_SYSTEM		= 0,	/* system mode                        */
    WTX_CONTEXT_GROUP		= 1,	/* process group (not implemented)    */
    WTX_CONTEXT_ANY		= 2,	/* any context (not implemented)      */
    WTX_CONTEXT_TASK		= 3,	/* specific task or process           */
    WTX_CONTEXT_ANY_TASK	= 4,	/* any task                           */
    WTX_CONTEXT_ISR		= 5,	/* specific ISR (not implemented)     */
    WTX_CONTEXT_ISR_ANY		= 6,	/* any ISR (not implemented)          */
    WTX_CONTEXT_PD		= 7,  	/* specific Protection Domain         */
    WTX_CONTEXT_PROCESS		= 8	/* BSD process/thread/kernel module   */
    } WTX_CONTEXT_TYPE;

typedef enum wtx_ctx_kill_opt		/* options for context deletion       */
    {
    WTX_PD_DELETE_OPTION_NONE	= 0,	/* no option given                    */
    WTX_PD_NOT_CALL_TERM_RTN	= 1,	/* don't not call termination routine */
    WTX_PD_FORCE_DELETE		= 2	/* force deletion                     */
    }	WTX_CTX_KILL_OPT;

typedef enum wtx_pd_type			/* values for WTX PDs         */
    {
    WTX_PD_APPLICATION		= 0x00000001,	/* application PD             */
    WTX_PD_SHARED_LIB		= 0x00000002,	/* shared library PD          */
    WTX_PD_SHARED_DATA		= 0x00000004,	/* shared data PD             */
    WTX_PD_AUTO_DELETE		= 0x00000010,	/* PD auto terminate          */
    WTX_PD_HEAP_GROWTH		= 0x00000020,	/* PD supports heap growth    */
    WTX_PD_DELETE_SAFE		= 0x00000040,	/* PD is not deletable        */
    WTX_PD_PRIVILEGED		= 0x00000080,	/* PD is privileged           */
    WTX_PD_PRE_MAPPED		= 0x00000100,	/* pre-mapped phys mem in PD  */
    WTX_PD_KERNEL		= 0x00001000,	/* kernel PD                  */
    WTX_PD_SYS_SHARED_LIB	= 0x00002000,	/* system shared lib	      */
    WTX_PD_UNPROTECTED		= 0x00004000,	/* no protected linkage       */
    WTX_PD_PROTECTED		= 0x00008000,	/* protected linkages allowed */
    WTX_PD_ERROR_RESERVED	= 0x80000000	/* reserved for errors        */
    } WTX_PD_TYPE;

typedef WTX_TGT_ID_T WTX_CONTEXT_ID_T;	/* context ID type                    */

/*
 * WTX_ACTION_TYPE - Type of actions to perform when an event occurs.
 * These action types can be bit-wise or-ed together. If the function called
 * in an WTX_ACTION_CALL returns TRUE, then any other actions specified are
 * cancelled. User defined actions use the high order 16 bits of the
 * WTX_ACTION_TYPE.
 *
 * For AExxx products, WTX_ACTION_PD_STOP is replaced by ACTION_ALL_STOP
 */

typedef enum wtx_action_type		/* type of actions                    */
    {
    WTX_ACTION_CALL 	= 1,		/* call a function                    */
    WTX_ACTION_NOTIFY	= 2,		/* post the event to the Host         */
    WTX_ACTION_STOP	= 4,		/* stop the context                   */
    WTX_ACTION_SYS_STOP = 8,		/* stop and goes in system mode       */
    WTX_ACTION_ALL_STOP	= 16		/* stop all threads/tasks             */
    } WTX_ACTION_TYPE;

typedef enum wtx_return_type		/* return value type                  */
    {
    WTX_RETURN_TYPE_INT		= 0,	/* integer return format              */
    WTX_RETURN_TYPE_DOUBLE	= 1,	/* double return format               */
    WTX_RETURN_TYPE_FLOAT	= 2	/* float return format                */
    } WTX_RETURN_TYPE;

typedef enum wtx_svc_type               /* ID for service type & action       */
    {
    WDB_LOGGING_ON		= 0,	/* turn on WDB logging request        */
    WDB_LOGGING_OFF		= 1,	/* turn off WDB logging request       */
    WTX_LOGGING_ON		= 2,	/* turn on WTX logging request        */
    WTX_LOGGING_OFF		= 3,	/* turn off WTX logging request       */
    ALL_LOGGING_OFF		= 4	/* turn off WDB & WTX logging request */
    } WTX_SVC_TYPE;

typedef enum wtx_compat_reg_set_type		/* types of registers                 */
    {
    WTX_REG_SET_IU	= 0,		/* integer unit register set          */
    WTX_REG_SET_FPU	= 1,		/* floating point unit register set   */
    WTX_REG_SET_MMU	= 2,		/* memory management unit register set*/
    WTX_REG_SET_CU	= 3,		/* cache unit register set            */
    WTX_REG_SET_TPU	= 4,		/* time process unit register set     */
    WTX_REG_SET_SYS	= 5,		/* system registers                   */
    WTX_REG_SET_DSP	= 6,		/* DSP registers */
    WTX_REG_SET_AV	= 7,		/* altivec registers */
    WTX_REG_SET_SPE	= 8,		/* SPE registers */
    WTX_REG_SET_LAST	= 9		/* 1 + last used REG_SET number */
    } WTX_COMPAT_REG_SET_TYPE;

typedef UINT32	WTX_REG_SET_TYPE; 

typedef enum wtx_agent_mode_type	/* debug agent running mode           */
    {
    WTX_AGENT_MODE_TASK 	= 1,	/* run in task mode                   */
    WTX_AGENT_MODE_EXTERN	= 2,	/* run in system mode                 */
    WTX_AGENT_MODE_BI		= 3	/* bimodal agent                      */
    } WTX_AGENT_MODE_TYPE;

typedef enum wtx_context_status		/* context status                     */
    {
    /* VxWorks states */

    WTX_CONTEXT_RUNNING        = 0x0,	/* context is running (system mode)   */
    WTX_CONTEXT_SUSPENDED      = 0x1,    /* context is suspended (system mode) */

    /* BSD OS Process status */

    WTX_CONTEXT_SIDL 	       = 0x100,		/* Process being created by fork. */
    WTX_CONTEXT_SRUN	       = 0x200,		/* Currently runnable. */
    WTX_CONTEXT_SSLEEP	       = 0x400,		/* Sleeping on an address. */
    WTX_CONTEXT_SSTOP	       = 0x800,		/* Process debugging or suspension. */
    WTX_CONTEXT_SEXIT	       = 0x1000,	/* Process is exiting/cleaning up */
    WTX_CONTEXT_SZOMB	       = 0x2000,	/* Awaiting collection by parent. */
    WTX_CONTEXT_EXCEPTION      = 0x4000,	/* Exception */
    WTX_CONTEXT_CORE	       = 0x8000,	/* Core dumps */
    WTX_CONTEXT_SSUSPEND       = 0x10000,
    WTX_CONTEXT_SDEBUG	       = 0x20000,
    WTX_CONTEXT_SBREAK         = 0x40000,

   /* BSD/OS Threads status */

    WTX_CONTEXT_PS_DEAD        = 0x80000,
    WTX_CONTEXT_PS_JOIN_WAIT   = 0x100000,
    WTX_CONTEXT_PS_SIG_WAIT    = 0x200000,
    WTX_CONTEXT_PS_WAIT_WAIT   = 0x400000,
    WTX_CONTEXT_PS_SLEEP_WAIT  = 0x800000,
    WTX_CONTEXT_PS_SELECT_WAIT = 0x1000000,
    WTX_CONTEXT_PS_CLOSE_WAIT =  0x2000000,
    WTX_CONTEXT_PS_IO_WAIT    =  0x4000000,
    WTX_CONTEXT_PS_COND_WAIT  =  0x8000000,
    WTX_CONTEXT_PS_MUTEX_WAIT =  0x10000000,
    WTX_CONTEXT_PS_SUSPENDED  =  0x20000000,
    WTX_CONTEXT_PS_RUNNABLE   =  0x40000000,
    WTX_CONTEXT_PS_RUNNING    =  0x80000000


    } WTX_CONTEXT_STATUS;

typedef enum wtx_open_flag		/* flag for WTX_OPEN                  */
    {
    WTX_O_RDONLY 	= 0x1000,	/* open for reading only              */
    WTX_O_WRONLY	= 0x2000,	/* open for writing only              */
    WTX_O_CREAT		= 0x4000	/* open with file create              */
    } WTX_OPEN_FLAG;

typedef enum wtx_pd_info_opt
    {
    WTX_CONTINUE_CHILDREN	= 0x01,	/* Auto resume of children 	      */
    WTX_CONTINUE_THREADS	= 0x02,	/* Auto resume of threads 	      */
    WTX_BREAK_AT_INIT  		= 0x04,	/* Break at _init		      */
    WTX_NO_FILE_PARSING		= 0x08	/* No parsing on host side	      */
    } WTX_PD_INFO_OPT;

typedef struct wtx_core			/* WTX message core                   */
    {
    WTX_TGT_ID_T	objId;			/* identifier                         */
    WTX_ERROR_T	errCode;		/* service error code                 */
    UINT32	protVersion;		/* WTX protocol version               */
    WTX_TGT_ADDR_T	defaultPd;		/* default Protection Domain          */
    UINT32	osErrCode;		/* OS specific error code	      */
    } WTX_CORE;

typedef enum wtx_value_t	/* simple types definitions                   */
    { 
    V_INT8		= 0,	/* 8  bits signed integer                     */
    V_INT16		= 1,	/* 16 bits signed integer                     */
    V_INT32		= 2,	/* 32 bits signed integer                     */
    V_UINT8		= 3,	/* 8  bits unsigned integer                   */
    V_UINT16		= 4,	/* 16 bits unsigned integer                   */
    V_UINT32		= 5,	/* 32 bits unsigned integer                   */
    V_DOUBLE		= 6,	/* double floating point                      */
    V_BOOL32		= 7,	/* 32 bits boolean                            */
    V_PCHAR		= 8,	/* character pointer                          */
    V_PVOID		= 9,	/* void pointer                               */
    V_TGT_ADDR		= 10,	/* target address                             */
    V_TGT_ARG		= 11,	/* target task argument                       */
    V_INT64		= 12,	/* 64 bits signed integer                     */
    V_UINT64		= 13	/* 64 bits unsigned integer                   */
    } WTX_VALUE_T;

typedef struct wtx_value		/* simple type value                  */
    {
    WTX_VALUE_T valueType;		/* value type                         */
    union
	{
	INT8		v_int8;		/* 8  bit signed value                */
	INT16		v_int16;	/* 16 bit signed value                */
	INT32		v_int32;	/* 32 bit signed value                */
	UINT8		v_uint8;	/* 8  bit unsigned value              */
	UINT16		v_uint16;	/* 16 bit unsigned value              */
	UINT32		v_uint32;	/* 32 bit unsigned value              */
	double		v_double;	/* double value                       */
	BOOL32		v_bool32;	/* 32 bit boolean value               */
	char *		v_pchar;	/* string value                       */
	void *		v_pvoid;	/* void pointer value                 */
	WTX_TGT_ADDR_T	v_tgt_addr;	/* target address value               */
	WTX_TGT_ARG_T	v_tgt_arg;	/* target task argument value         */
	INT64		v_int64;	/* 64 bit signed value                */
	UINT64		v_uint64;	/* 64 bit unsigned value              */
	} value_u;
    } WTX_VALUE;

typedef struct wtx_value_with_pd	/* WTX value with PD ID               */
    {
    WTX_TGT_ID_T		pdId;		/* protection domain ID               */
    WTX_VALUE		value;		/* simple parameter value             */
    } WTX_VALUE_WITH_PD;

/* -------------------------- asynchronous typedefs ------------------------- */

typedef struct wtx_event_desc		/* WTX event descriptor               */
    {
    char *		event;		/* event descriptor                   */
    INT32		addlDataLen;	/* additional data length             */
    char *		addlData;	/* additional data (VIO)              */
    } WTX_EVENT_DESC;

typedef void (*WTX_EVENT_HANDLER)
    (
    WTX_EVENT_DESC *,			/* event received by target server    */
    HWTX				/* current WTX session handler        */
    );

typedef struct wtx_async_context
    {
    void *	objId;			/* object address                     */
    WTX_EVENT_HANDLER	wrapperFunc;	/* user routine                       */
    LIST	wtxEventList;		/* global event list                  */
    SEM_ID	wtxEventListMutex;	/* guarding Mutex for event list      */
    SEM_ID	fullListSem;		/* guarding semaphore for event list  */
    SEM_ID	syncSema;		/* synchronization semaphore          */
    SEM_ID	prodMutex;		/* producer Mutex                     */
    SEM_ID	consMutex;		/* consumer Mutex                     */
    WTX_SOCKET	serverSockFd;		/* socket file descriptor             */
    WTX_SOCKET	serverNewSockFd;	/* socket file descriptor             */
    BOOL32	asyncNotifyStarted;	/* asynchronous notification flag     */
    }	WTX_ASYNC_CONTEXT;		/* asynchronous notification context  */

typedef WTX_ASYNC_CONTEXT *	WTX_ASYNC_HANDLE; /* asynch. notif. handle    */

/* -------------------------------- registry -------------------------------- */

typedef struct wtx_tgtsvr_action
    {
    WTX_TGTSVR_ACTION_TYPE	actionType;	/* action type to perform     */
    char *			tgtsvrName;	/* name of Tgtsvr to address  */
    char *			cmdLine;	/* tgtsvr command line        */
    char *			execIP;		/* IP address of exec host    */
    } WTX_TGTSVR_ACTION;

typedef struct wtx_log_action
    {
    char *		host;			/* application's host         */
    char *		svrName;		/* server name to get log     */
    WTX_LOG_ACTION_TYPE	actionType;		/* logging action type        */
    unsigned long int	seek;			/* file position cursor       */
    char *		log;			/* logging file content       */
    } WTX_LOG_ACTION;

typedef struct wtx_wtxregd_info
    {
    char *		name;		/* registry element name / pattern    */
    char *		type;		/* registry element type / pattern    */
    char *		key;		/* registry element key / pattern     */
    char *		host;		/* registry host name / IP address    */
    } WTX_WTXREGD_INFO;

typedef struct wtx_wtxregd_item
    {
    char *		name;		/* exact name of item to retrieve     */
    char *		host;		/* registry host name or IP address   */
    } WTX_WTXREGD_ITEM;

/* ----------------------- server/registry ---------------------------------- */

typedef struct wtx_desc                 /* server descriptor queue            */
    {
    char *              wpwrName;       /* name of wpwr service               */
    char *              wpwrType;       /* type of service                    */
    char *              wpwrKey;        /* unique service key                 */
    struct wtx_desc_q * pNext;          /* next descriptor                    */
    } WTX_DESC;

typedef struct wtx_desc_q               /* server descriptor queue            */
    {
    char *              wpwrName;       /* name of wpwr service               */
    char *              wpwrType;       /* type of service                    */
    char *              wpwrKey;        /* unique service key                 */
    struct wtx_desc_q * pNext;          /* next descriptor                    */
    } WTX_DESC_Q;

typedef struct wtx_svr_desc             /* server descriptor                  */
    {
    char *              wpwrName;       /* name of wpwr service               */
    char *              wpwrType;       /* type of service                    */
    char *              wpwrKey;        /* unique service key                 */
    } WTX_SVR_DESC;

typedef struct wtx_svr_desc_q           /* server descriptor queue            */
    {
    WTX_SVR_DESC            wtxSvrDesc; /* server Descriptor                  */
    struct wtx_svr_desc_q * pNext;      /* next descriptor                    */
    } WTX_SVR_DESC_Q;

typedef struct wtx_vio_file_desc	/* virtual file descriptor            */
    {
    char *	name;			/* file or device name                */
    INT32	fd;			/* file descriptor                    */
    INT32	channel;		/* channel for redirection            */
    INT32	fp;			/* file pointer for streams           */
    INT32	type;			/* file type                          */
    INT32	mode;			/* open mode (O_RDONLY, ...)          */
    INT32	status;			/* opened or closed                   */
    INT64	addlInfo;		/* extra information (eg: process ID) */
    struct wtx_vio_file_desc *	next;	/* ptr to next descriptor for list    */
    } WTX_VIO_FILE_DESC;

typedef struct wtx_vio_link_desc        /* virtual IO link descriptor         */
    {
    NODE node;                          /* node used to link                  */
    UINT32 channel;                     /* target vio channel                 */
    WTX_SOCKET fdIn;                    /* socket file descriptor (input)     */
    WTX_SOCKET fdOut;                   /* socket file descriptor (output)    */
    void * tsNode;                      /* target Server descriptor node      */
    } WTX_VIO_LINK_DESC;

typedef struct wtx_mem_region		/* memory region descriptor           */
    {
    WTX_TGT_ADDR_T	baseAddr;	/* memory region base address         */
    UINT32		size;		/* memory region size                 */
    UINT32		attribute;	/* memory region attributes           */
    } WTX_MEM_REGION;

typedef struct wtx_vxworks_info         /* vxWorks specific information       */
    {
    WTX_TGT_ADDR_T          pdList;     /* pointer on Protection Domain list  */
    } WTX_VXWORKS_INFO;


typedef struct wtx_rt_info              /* target runtime information         */
    {
    char *              rtName;         /* runtime name                       */
    char *              rtVersion;      /* runtime version                    */
    UINT32              cpuType;        /* target processor type              */
    char *		cpuVariant;	/* cpu variant			      */
    UINT32              hasCoprocessor;	/* Coprocessors:  see below           */
    UINT32              hasWriteProtect;/* Text write protect avail.          */
    UINT32              pageSize;       /* size of a page                     */
    UINT32              endian;         /* endianness (LITTLE or BIG)         */
    char *              bspName;        /* board support package name         */
    char *              bspShortName;   /* build tool's BSP_NAME macro value  */
    char *              toolName;       /* tool used to build this target     */
    char *              bootline;       /* boot file name                     */
    WTX_TGT_ADDR_T      memBase;        /* target main memory base address    */
    UINT32              memSize;        /* target main memory size            */
    UINT32              numRegions;     /* number of memory regions           */
    WTX_MEM_REGION *    memRegion;      /* memory region descriptor(s)        */
    WTX_TGT_ADDR_T      hostPoolBase;   /* tgtsvr memory pool base address    */
    UINT32              hostPoolSize;   /* target Server memory pool size     */
    UINT32              numInts;        /* RT specific union length           */
    union
        {
        WTX_VXWORKS_INFO vxWorksInfo;   /* vxWorks specific information       */
        } rtSpecific;
    } WTX_RT_INFO;

/*
 * The hasCoprocessor field is bit-significant, see definitions of
 * WTX_FPP_MASK etc. in wtxtypes.h
 */

typedef struct wtx_agent_info		/* target agent information           */
    {
    char *		agentVersion;	/* WDB agent version                  */
    UINT32		mtu;		/* maximum transfer size (bytes)      */
    UINT32		mode;		/* available agent modes              */
    } WTX_AGENT_INFO;

typedef struct wtx_tgt_info		/* target information                 */
    {
    WTX_AGENT_INFO	agentInfo;	/* information on the agent           */
    WTX_RT_INFO		rtInfo;		/* information on the runtime system  */
    } WTX_TGT_INFO;

typedef struct wtx_tgt_link_desc 	/* link descriptor                    */
    {
    char *		name;		/* target/Host link name              */
    UINT32		type;		/* target/Host link type              */
    UINT32		speed;		/* target/Host link speed             */
    } WTX_TGT_LINK_DESC;

typedef struct wtx_tool_desc		/* tool descriptor                    */
    {
    WTX_TGT_ID_T	id;		/* unique tool identifier             */
    char *		toolName;	/* tool name                          */
    char *		toolArgv;	/* tool argv parameters               */
    char *		toolVersion;	/* tool version                       */
    char *		userName;	/* user name                          */
    WTX_TGT_ADDR_T	clientPd;	/* tool's current PD ID               */
    UINT32		lastError;	/* tool's last error seen             */
    void *		pendingContext;	/* non atomic requests contexts       */
    char *		currentDir;	/* Current directory 		      */
    UINT32		umask;		/* Current umask		      */
    void *		pReserved;	/* reserved                           */
    struct wtx_tool_desc * next;	/* pointer to next tool descriptor    */
    } WTX_TOOL_DESC;

typedef WTX_TOOL_DESC * TOOL_ID;

typedef struct wtx_tgtsvr_args          /* tgtsvr starting args               */
    {
    int		argc;			/* arguments number                   */
    char **	argv;			/* arguments vector                   */
    } WTX_TGTSVR_ARGS;

typedef struct wtx_ts_info		/* target Server information message  */
    {
    WTX_TGT_LINK_DESC	tgtLinkDesc;	/* target link descriptor             */
    WTX_TGT_INFO	tgtInfo;	/* information retrieved from Target  */
    WTX_TOOL_DESC *	pWtxToolDesc;	/* information about attached Tools   */
    char *		version;	/* target Server version              */
    char *		userName;	/* target Server user name            */
    UINT32 		startTime;	/* target Server start time           */
    UINT32		accessTime;	/* target Server access time          */
    char *		lockMsg;	/* lock/authorization message one of: */
	    /* - "authorized" : you are not in the allowed users list         */
	    /* - "locked"     : another user has locked this session          */
	    /* - "available"  : you may connect to this session               */
	    /* - "restricted" : this session is restricted for your own use   */

    BOOL32		pdInitialized;	/* TRUE if the PDs are initialized    */
    WTX_TGTSVR_ARGS	tgtsvrArgs;	/* target Server command line	      */
    void *		pReserved;	/* reserved                           */
    } WTX_TS_INFO;

/* --------------------------- memory operations ---------------------------- */

typedef struct wtx_mem_info	 	/* memory information                 */
    {
    UINT32 	curBytesFree;		/* number of free bytes               */
    UINT32 	curBytesAllocated;	/* current number of allocated bytes  */
    UINT32 	cumBytesAllocated;	/* cumm. number of allocated bytes    */
    UINT32 	curBlocksFree;		/* current number of free blocks      */
    UINT32 	curBlocksAlloc;		/* current number of blocks allocated */
    UINT32 	cumBlocksAlloc;		/* cumm. number of allocated blocks   */
    UINT32 	avgFreeBlockSize;	/* average free blocks size           */
    UINT32 	avgAllocBlockSize;	/* average allocated blocks size      */
    UINT32 	cumAvgAllocBlockSize;	/* cumm. average allocated block size */
    UINT32 	biggestBlockSize;	/* size of biggest block              */
    void * 	pReserved;		/* reserved                           */
    } WTX_MEM_INFO;

typedef struct wtx_mem_xfer		/* memory transfer                    */
    {
    UINT32		numBytes;	/* number of bytes to transfer        */
    WTX_TGT_ADDR_T	destination;	/* destination address                */
    char *		source;		/* source address                     */
    } WTX_MEM_XFER;

/* --------------------------- contexts ------------------------------------- */

typedef struct wtx_context		/* context descriptor                 */
    {
    WTX_CONTEXT_TYPE	contextType;	/* type of context                    */
    WTX_CONTEXT_ID_T	contextId;	/* context ID                         */
    WTX_CONTEXT_ID_T	contextSubId;	/* context Sub ID                     */
    } WTX_CONTEXT;

typedef struct wtx_kill_context		/* context descriptor                 */
    {
    WTX_CONTEXT		wtxContext;	/* type of context                    */
    WTX_CTX_KILL_OPT	killOpt;	/* kill options                       */
    } WTX_KILL_CONTEXT;

typedef struct wtx_task_context_def	/* task creation descriptor           */
    {
    WTX_TGT_ID_T	pdId;		/* context Protection Domain ID       */
    WTX_RETURN_TYPE	returnType;	/* integer or double                  */
    char *		name;		/* task name                          */
    UINT32		priority;	/* priority                           */
    UINT32		options;	/* options                            */
    WTX_TGT_ADDR_T	stackBase;	/* base of stack address              */
    UINT32		stackSize;	/* stack size                         */
    WTX_TGT_ADDR_T	entry;		/* context entry point                */
    WTX_TGT_ID_T	redirIn;	/* redirection in file or NULL        */
    WTX_TGT_ID_T	redirOut;	/* redirection out file or NULL       */
    WTX_TGT_ID_T	redirErr;	/* redirection error file or NULL     */
    UINT32		argc;		/* number of arguments in argv        */
    WTX_TGT_ARG_T *	argv;		/* arguments array                    */
    } WTX_TASK_CONTEXT_DEF;

typedef struct wtx_pd_context_def       /* PD creation descriptor             */
    {
    char *              name;           /* PD name                            */
    UINT32              options;        /* options                            */
    UINT32              heapSize;       /* size of the PD's heap              */
    UINT32              lowPriority;    /* lowest task's priority             */
    UINT32              highPriority;   /* highest task's priority            */
    WTX_TGT_ADDR_T      pagePoolList;   /* page pool list name to use         */
    WTX_TGT_ADDR_T      destroyRtn;     /* rtn. address to call on deletion   */
    char *              linkPath;       /* initial link path for this PD      */
    WTX_TGT_ID_T        redirIn;        /* redirection in file or NULL        */
    WTX_TGT_ID_T        redirOut;       /* redirection out file or NULL       */
    WTX_TGT_ID_T        redirErr;       /* redirection error file or NULL     */
    UINT32              argc;           /* extra argument count (in argv)     */
    WTX_TGT_ARG_T *     argv;           /* extra argument array               */
    } WTX_PD_CONTEXT_DEF;

typedef struct wtx_process_context_def	/* Process descriptor                 */
    {
    char *		name;		/* Process name                       */
    UINT32		options;	/* options                            */
    UINT32		addOptions;	/* Additionnal options                */
    UINT32		heapSize;	/* size of the Process's heap         */
    WTX_TGT_ID_T	redirIn;	/* redirection in file or NULL        */
    WTX_TGT_ID_T	redirOut;	/* redirection out file or NULL       */
    WTX_TGT_ID_T	redirErr;	/* redirection error file or NULL     */
    UINT32		argc;		/* extra argument count (in argv)     */
    char **		argv;		/* extra argument string array        */
    UINT32		uid;		/* uid				      */
    UINT32		gid;		/* gid				      */
    UINT32		priority;	/* priority			      */
    int			envc;		/* Number of environment string	      */
    char **		envv;		/* Environment strings array	      */
    UINT32		stackSize;	/* Stack size			      */
    } WTX_PROCESS_CONTEXT_DEF;

typedef struct wtx_context_desc		/* context creation descriptor        */
    {
    WTX_CONTEXT_TYPE	wtxContextType;	/* type of context                    */
    union wtx_context_def
	{
	WTX_TASK_CONTEXT_DEF	wtxTaskContextDef; /* task context definition */
	WTX_PD_CONTEXT_DEF	wtxPdContextDef;   /* PD context definition   */
	WTX_PROCESS_CONTEXT_DEF	wtxProcessContextDef; /* process ctx def.     */
	} wtxContextDef;
    } WTX_CONTEXT_DESC;

/* --------------------------- symbols -------------------------------------- */

typedef struct wtx_symbol		/* symbol descriptor                  */
    {
    UINT32		status;		/* returned value for find request    */
    WTX_TGT_ID_T	pdId;		/* protection domain ID               */
    char *		name;		/* symbol name                        */
    BOOL32		exactName;	/* fALSE if symbol name prefixed by _ */
    WTX_TGT_ADDR_T	value;		/* symbol value                       */
    UINT32		size;		/* symbol size			      */
    UINT32		type;		/* symbol type                        */
    UINT32		typeMask;	/* symbol type mask for lookup        */
    WTX_TGT_ADDR_T	reference;	/* symbol reference                   */
    char *		moduleName;	/* module name                        */
    UINT32		execMode;	/* entry point execution mode as above*/
#ifdef	HOST
    GROUP_ID		apiGroup;	/* entry point API group              */
#endif
    UINT32		nPendModules;	/* # modules depending on this symbol */
    WTX_TGT_ID_T *	pPendModuleId;	/* depending modules array            */
    void *		pReserved;	/* reserved                           */
    struct wtx_symbol * next;		/* pointer to the next symbol in list */
    } WTX_SYMBOL;

typedef struct wtx_sym_list		/* symbol list                        */
    {
    WTX_SYMBOL *	pSymbol;	/* head of symbol list                */
    } WTX_SYM_LIST;

typedef struct wtx_sym_tbl_info
    {
    WTX_TGT_ID_T	pdId;		/* protection domain ID               */
    UINT32		symNum;		/* number of symbols                  */
    BOOL32		sameNameOk;	/* name clash policy                  */
    } WTX_SYM_TBL_INFO;

typedef struct wtx_sym_find_criteria
    {
    UINT32		options;	/* option flag                        */
    WTX_TGT_ID_T	pdId;		/* PD ID or WTX_SYM_FIND_IN_ALL_PD    */
    char *		findName;	/* symbol name (regular expression)   */
    WTX_TGT_ADDR_T	findValue;	/* symbol value (address)             */
    UINT32		nSymbols;	/* number of symbols to get by value  */
    UINT32		type;		/* type value                         */
    WTX_TGT_ADDR_T	ref;		/* reference value                    */
    WTX_TGT_ID_T	moduleId;	/* module ID value                    */
    char *		moduleName;	/* module name value                  */
    } WTX_SYM_FIND_CRITERIA;

/* --------------------------- module/segment ------------------------------- */

typedef enum wtx_section_type		/* kind of section handled            */
    {
    WTX_SECTION_UNKNOWN = 0,
    WTX_SECTION_RODATA	= 1,		/* read-only data section             */
    WTX_SECTION_TEXT	= 2,		/* text section                       */
    WTX_SECTION_DATA	= 3,		/* data section                       */
    WTX_SECTION_BSS	= 4		/* bSS section                        */
    } WTX_SECTION_TYPE;

typedef struct wtx_section_desc		/* object module section descriptor   */
    {
    WTX_TGT_ID_T	id;		/* section id                         */
    char *		name;		/* section name                       */
    WTX_SECTION_TYPE	type;		/* section type                       */
    UINT32		flags;		/* section flags                      */
    WTX_TGT_ADDR_T	baseAddr;  	/* section base address               */
    WTX_TGT_ADDR_T	partId;		/* dedicated memory partition Id      */
    UINT32		length;		/* section length                     */
    UINT32		checksum;	/* checksum value for section	      */
    } WTX_SECTION_DESC;

typedef enum wtx_seg_type
    {
    WTX_SEGMENT_TEXT =	2,
    WTX_SEGMENT_DATA =  4, 
    WTX_SEGMENT_BSS  =  8
    } WTX_SEG_TYPE;
    
typedef struct wtx_segment_desc
    {
    WTX_SEG_TYPE	type;		/* Segment type 	*/
    WTX_TGT_ADDR_T	addr;		/* Segment location 	*/
    UINT32		length;		/* Segment length 	*/
    UINT32		flags;		/* Segment flags 	*/
    } WTX_SEGMENT_DESC; 

typedef struct wtx_module_file_desc	/* object module file descriptor      */
    {
    char *	   	filename;	/* object file name                   */
    WTX_TGT_ID_T	moduleId;	/* module ID                          */
    INT32	   	loadFlag;	/* behavior control flags             */
    UINT32	   	nSections;	/* number of sections                 */
    WTX_SECTION_DESC * 	section;	/* section description                */
    UINT32		nArgs;		/* # args given for the load and run  */
    WTX_TGT_ADDR_T *	pArgs;		/* args array                         */
    } WTX_MODULE_FILE_DESC;

typedef struct wtx_module_info		/* object module information          */
    {
    WTX_TGT_ID_T	pdId;		/* protection domain ID               */
    WTX_TGT_ID_T	moduleId;	/* module ID                          */
    char *		moduleName;	/* module name (with path)            */
    UINT32		format;		/* object file format                 */
    int			loadFlag;	/* flags used to load module          */
    WTX_TGT_ADDR_T	vxCompRtn;	/* component init/term routine        */
    WTX_TGT_ADDR_T	userInitRtn;	/* user-supplied init routine         */
    UINT32		commTotalSize;	/* memory used by  common symbols     */
    UINT32		nSections;	/* number of sections                 */
    WTX_SECTION_DESC *	section;	/* section description                */
    WTX_SYM_LIST	undefSymList;	/* list of undefined symbols          */
    void *		pReserved;	/* reserved                           */
    UINT32		group;		/* Group			      */
    UINT32		nSegments; 	/* number of segments		      */
    WTX_SEGMENT_DESC *	segment; 	/* segment descriptions		      */
    } WTX_MODULE_INFO;

typedef struct wtx_module
    {
    WTX_TGT_ID_T        pdId;           /* protection domain ID               */
    WTX_TGT_ID_T        moduleId;       /* module ID                          */
    char *              moduleName;     /* module name (with path)            */
    struct wtx_module * next;           /* pointer to the next module in list */
    } WTX_MODULE;

typedef struct wtx_module_list		/* object module list                 */
    {
    WTX_MODULE * 	pModule; 	/* list of object module ID           */
    } WTX_MODULE_LIST;

typedef struct wtx_mod_find_criteria    /* criteria descriptor                */
    {
    UINT32		options;	/* options flag                       */
    WTX_TGT_ID_T	pdId;		/* PD ID or WTX_MOD_FIND_IN_ALL_PD    */
    WTX_TGT_ID_T	moduleId;	/* module ID value                    */
    char *		moduleName;	/* module name value                  */
    WTX_TGT_ADDR_T	ref;		/* reference value                    */
    } WTX_MOD_FIND_CRITERIA;

typedef enum wtx_svr_type               /* type of server to connect to       */
    {
    WTX_SVR_NONE	= 0,		/* no server to connect to            */
    WTX_SVR_SERVER	= 1,		/* server is a Target Server          */
    WTX_SVR_REGISTRY	= 2		/* server is the Registry             */
    } WTX_SVR_TYPE;

typedef enum wtx_ctl_request		/* request for WTX exchange controls  */
    {
    WTX_CTL_NONE	= 0,		/* no request                         */
    WTX_CTL_TIMEOUT_SET	= 1,		/* set exchange timeout value         */
    WTX_CTL_TIMEOUT_GET	= 2,		/* get exchange timeout value         */
    WTX_CTL_ERROR_GET	= 3		/* get exchange error code            */
    } WTX_CTL_REQUEST;

typedef struct wtx_exchange_desc	/* exchange layer descriptor          */
    {
    WTX_SVR_TYPE	svrType;	/* exchange server to address         */
    WTX_CTL_REQUEST	request;	/* request to address to server       */
    union req_val
	{
	UINT32		timeout;	/* value to control is a timeout      */
	WTX_ERROR_T	error;		/* value to control is a WTX error    */
	} reqVal;
    } WTX_EXCHANGE_DESC;

/* --------------------------- load operation ------------------------------- */

typedef enum wtx_load_mode
    {
    WTX_LOADER_NO_LOAD_MODE	= 0,	/* no load mode                      */
    WTX_LOADER_STRICT_MODE	= 1,	/* strict mode                       */
    WTX_LOADER_INCREMENTAL_MODE	= 2,	/* incremental mode		     */
    WTX_LOADER_OUT_OF_ORDER_MODE= 3	/* OOOL mode			     */
    } WTX_LOAD_MODE;

typedef enum wtx_async_load_state
    {
    WTX_LOAD_IN_PROGRESS	= 2,	/* load in progress MUST BE EQUAL TO
    					 * LOAD_PROGRESS enum                 */
    WTX_LOAD_FINISHED		= 4	/* load finished MUST BE EQUAL TO
    					 * LOAD_MODULE_DONE enum              */
    } WTX_ASYNC_LOAD_STATE;

typedef struct wtx_upload_buf
    {
    UINT32		fileSize;	/* file size                          */
    UINT32		numBuffer;	/* current buffer #                   */
    UINT32		bufSize;	/* current buffer size                */
    void *		buffer;		/* the buffer itself                  */
    } WTX_UPLOAD_BUF;

typedef struct wtx_load_progress_info	/* async load progress report infos   */
    {
    UINT32		state;		/* current load state                 */
    UINT32		maxValue;	/* max value for this state           */
    UINT32		currentValue;	/* current value for this state       */
    UINT32		loadErrno;	/* load error number                  */
    } WTX_LOAD_PROGRESS_INFO;

typedef enum wtx_load_command		/* load sub-commands                  */
    {
    LOAD_MODULE		= 0,		/* (async)load (start)                */
    LOAD_UPLOAD		= 1,		/* upload object module               */
    LOAD_PROGRESS	= 2,		/* get asynchronous load status       */
    LOAD_CANCEL		= 3,		/* cancel an asynchronous load        */
    LOAD_MODULE_DONE	= 4		/* synchronous load done              */
    } WTX_LOAD_COMMAND;

typedef struct wtx_load_report_info	/* progress info for async. loads     */
    {
    WTX_ASYNC_LOAD_STATE loadState;	/*
					 * two values :
				 	 *  LOAD_IN_PROGRESS :
				 	 *    - informations available in
				 	 *      WTX_LOAD_PROGRESS_INFO struct.
				 	 *  LOAD_DONE :
				 	 *    - informations available in
				 	 *      WTX_MODULE_FILE_DESC  struct.
				 	 */
    union	state_info
	{
	WTX_MODULE_INFO		moduleInfo;
	WTX_LOAD_PROGRESS_INFO	progressInfo;
	}	stateInfo;
    }	WTX_LOAD_REPORT_INFO;

/* --------------------------- gopher tape ---------------------------------- */

typedef struct wtx_gopher_tape		/* gopher tape                        */
    {
    UINT16	len;			/* length of tape                     */
    char *	data;			/* tape data                          */
    } WTX_GOPHER_TAPE;

/* ---------------------------- disassembler -------------------------------- */

typedef struct wtx_dasm_inst_list       /* instructions list                  */
    {
    char *              pInst;          /* start of instructions list         */
    UINT32              nextInst;       /* next instruction address           */
    UINT32              listSize;       /* list size                          */
    } WTX_DASM_INST_LIST;

/* ---------------------------- Event/Eventpoint ---------------------------- */

typedef struct wtx_action		/* action descriptor                  */
    {
    WTX_ACTION_TYPE	actionType;	/* action type to perform             */
    UINT32		actionArg;	/* action dependent argument          */
    WTX_TGT_ADDR_T	callRtn;	/* function to ACTION_CALL            */
    WTX_TGT_ARG_T	callArg;	/* function argument                  */
    } WTX_ACTION;

typedef struct wtx_event_node           /* WTX event node descriptor          */
    {
    struct wtx_event_desc    event;     /* event descriptor                   */
    struct wtx_event_node *  pNext;     /* pointer to the next event          */
    } WTX_EVENT_NODE;

typedef struct wtx_event		/* target event                       */
    {
    WTX_EVENT_TYPE      eventType;      /* type of event                      */
    UINT32              numArgs;        /* number of arguments                */
    WTX_TGT_ARG_T *     args;           /* list of arguments                  */
    } WTX_EVENT;

typedef struct wtx_evtpt		/* eventpoint descriptor              */
    {
    WTX_EVENT		event;          /* event to detect                    */
    WTX_CONTEXT		context;        /* context descriptor                 */
    WTX_ACTION		action;         /* action to perform                  */
    } WTX_EVTPT;

typedef struct wtx_evtpt_info		/* eventpoint information             */
    {
    WTX_EVTPT		wtxEvtpt;	/* eventpoint descriptor              */
    WTX_TGT_ID_T	toolId;		/* tool identifier	              */
    UINT32		evtptNum;	/* eventpoint identifier              */
    void *		pReserved1;	/* reserved		              */
    void *		pReserved2;	/* reserved		              */
    } WTX_EVTPT_INFO;

typedef struct wtx_evtpt_list		/* eventpoint list message            */
    {
    UINT32              nEvtpt;         /* number of eventpoints in list      */
    WTX_EVTPT_INFO *    pEvtptInfo;     /* eventpoint information list        */
    } WTX_EVTPT_LIST;

/* ---------------------- Protection domain definitions --------------------- */

typedef struct wtx_pd_desc
    {
    WTX_TGT_ID_T		pdId;		/* protection domain ID       */
    char *			pdName;		/* protection domain name     */
    UINT32			pdFlags;	/* protection domain flags    */
    char *			pdLinkPathStr;	/* link path string	      */
    UINT32			pdLinkPathCount;/* number of PD in linkpath   */
    WTX_TGT_ADDR_T *		pdLinkPath;	/* PD ids of the linkpath PDs */
    UINT32			pdAttachToCount;
    WTX_TGT_ADDR_T *		pdAttachTo;
    } WTX_PD_DESC;

typedef struct wtx_pd_desc_q			/* WTX Protection Domain list */
    {
    WTX_PD_DESC			wtxPdDesc;	/* PD descriptor              */
    struct wtx_pd_desc_q *	pNext;		/* next PD in queue           */
    } WTX_PD_DESC_Q;

/* ---------------------- User service definitions ---------------------------*/

typedef struct wtx_usr_svc_add_info	/* extra field for WTX_USR_SVC_ADD */
    {
    WTX_TGT_INT_T	func;		/* routine associated with service */
    WTX_TGT_INT_T	initRtn;	/* init routine for the new service */
    WTX_TGT_INT_T	initRtnArg;	/* argument for init routine */
    } WTX_USR_SVC_ADD_INFO;

typedef struct wtx_usr_svc_rem_info	/* extra field for WTX_USR_SVC_REM */
    {
    WTX_TGT_INT_T	stopRtn;	/* routine to call to stop the */
    					/* command service */
    WTX_TGT_INT_T	stopRtnArg;	/* argument for stop command service */
    } WTX_USR_SVC_REM_INFO;

typedef struct wtx_usr_svc_find_info	/* extra field for WTX_USR_SVC_FIND */
    {
    WTX_TGT_INT_T	func;		/* routine associated with service */
    } WTX_USR_SVC_FIND_INFO;

typedef enum wtx_usr_svc_ctrl_cmd	/* user service sub-commands          */
    {
    WTX_USR_SVC_ADD	= 0,		/* add a user service		      */
    WTX_USR_SVC_REMOVE	= 1,		/* remove a user service	      */
    WTX_USR_SVC_FIND	= 2		/* find a user service		      */
    } WTX_USR_SVC_CTRL_CMD;
   
/* ---------------------- Target Filesystem I/O  ---------------------------*/

typedef enum wtx_tgtfs_inode_ctrl_cmd	/* target filesystem sub-commands     */
    {
    WTX_TGTFS_MKDIR	= 0,		/* mkdir 			      */
    WTX_TGTFS_RMDIR	= 1, 		/* rmdir			      */
    WTX_TGTFS_MV	= 2,		/* rename			      */
    WTX_TGTFS_RM	= 3, 		/* remove file			      */
    WTX_TGTFS_LINK	= 4, 		/* link				      */
    WTX_TGTFS_CP	= 5,		/* local copy			      */
    WTX_TGTFS_MKNOD	= 6,		/* mknod			      */
    WTX_TGTFS_SYMLNK	= 7,		/* symlink 			      */
    WTX_TGTFS_READDIR   = 8,		/* readdir 			      */
    WTX_TGTFS_SETDIR    = 9,		/* Set current directory 	      */
    WTX_TGTFS_GETDIR 	= 10,		/* Get current directory 	      */
    WTX_TGTFS_STAT 	= 11,		/* Stat file		 	      */
    WTX_TGTFS_CHMOD	= 12, 		/* Chmod 			      */
    WTX_TGTFS_CHOWN	= 13,		/* Chown			      */
    WTX_TGTFS_LSTAT	= 14,		/* lstat			      */
    WTX_TGTFS_UMASK	= 15,		/* Umask			      */
    WTX_TGTFS_READLINK  = 16		/* Readlink			      */
    } WTX_TGTFS_INODE_CTRL_CMD;
    
typedef enum wtx_tgtfs_inode_ctrl_opt 	/* target filesystem commands options	*/
    {
    WTX_TGTFS_OPT_READDIR_LONG	= 1,	/* Full informations on readdir */
    WTX_TGTFS_OPT_FOLLOW_LINK	= 2	/* Follow links			*/
    } WTX_TGTFS_INODE_CTRL_OPT;
    
typedef enum wtx_tgtfs_inode_mode_type
    {
    WTX_TGTFS_INODE_MODE_S_IFMT 	= 0170000,
    WTX_TGTFS_INODE_MODE_S_IFSOCK 	= 0140000,
    WTX_TGTFS_INODE_MODE_S_IFLNK	= 0120000,
    WTX_TGTFS_INODE_MODE_S_IFREG	= 0100000,
    WTX_TGTFS_INODE_MODE_S_IFBLK	= 060000,
    WTX_TGTFS_INODE_MODE_S_IFDIR	= 040000,
    WTX_TGTFS_INODE_MODE_S_IFCHR	= 020000,
    WTX_TGTFS_INODE_MODE_S_IFIFO	= 010000,
    WTX_TGTFS_INODE_MODE_S_ISUID	= 04000,
    WTX_TGTFS_INODE_MODE_S_ISGID	= 02000,
    WTX_TGTFS_INODE_MODE_S_ISVTX	= 01000,
    WTX_TGTFS_INODE_MODE_S_IRWXU	= 0700,
    WTX_TGTFS_INODE_MODE_S_IRUSR	= 0400,
    WTX_TGTFS_INODE_MODE_S_IWUSR	= 0200,
    WTX_TGTFS_INODE_MODE_S_IXUSR	= 0100,
    WTX_TGTFS_INODE_MODE_S_IRWXG	= 070,
    WTX_TGTFS_INODE_MODE_S_IRGRP	= 040,
    WTX_TGTFS_INODE_MODE_S_IWGRP	= 020,
    WTX_TGTFS_INODE_MODE_S_IXGRP	= 010,
    WTX_TGTFS_INODE_MODE_S_IRWXO	= 07,
    WTX_TGTFS_INODE_MODE_S_IROTH	= 04,
    WTX_TGTFS_INODE_MODE_S_IWOTH	= 02,
    WTX_TGTFS_INODE_MODE_S_IXOTH	= 01	
    } WTX_TGTFS_INODE_MODE_TYPE;

typedef struct wtx_msg_tgtfs_inode_mkdir_desc	
    {
    char *			pathname;	/* filename to UNIX convention */
    WTX_TGTFS_INODE_MODE_TYPE	mode; 
    } WTX_MSG_TGTFS_INODE_MKDIR_DESC;

typedef struct wtx_msg_tgtfs_inode_chmod_desc	
    {
    char *			pathname; 	/* filename to UNIX convention */
    WTX_TGTFS_INODE_MODE_TYPE	mode; 
    } WTX_MSG_TGTFS_INODE_CHMOD_DESC;

typedef struct wtx_msg_tgtfs_inode_chown_desc	
    {
    char *			pathname; 	/* filename to UNIX convention */
    UINT32			uid;
    UINT32			gid; 
    } WTX_MSG_TGTFS_INODE_CHOWN_DESC;

typedef struct wtx_msg_tgtfs_inode_rmdir_desc
    {
    char *			pathname;	/* filename to UNIX convention */
    } WTX_MSG_TGTFS_INODE_RMDIR_DESC;
    
typedef struct wtx_msg_tgtfs_inode_mv_desc
    {
    char *			oldPath;	
    char *			newPath;
    } WTX_MSG_TGTFS_INODE_MV_DESC; 		

typedef struct wtx_msg_tgtfs_inode_rm_desc
    {
    char *			pathname;	/* filename to UNIX convention */
    } WTX_MSG_TGTFS_INODE_RM_DESC; 

typedef struct wtx_msg_tgtfs_inode_link_desc
    {
    char *			oldPath;	
    char *			newPath; 
    } WTX_MSG_TGTFS_INODE_LINK_DESC;
    
typedef struct wtx_msg_tgtfs_inode_cp_desc
    {
    char *			oldPath;	
    char *			newPath; 
    UINT32			copyOpt;
    } WTX_MSG_TGTFS_INODE_CP_DESC;

typedef struct wtx_msg_tgtfs_inode_mknod_desc
    {
    char *			pathname;
    WTX_TGTFS_INODE_MODE_TYPE	mode;
    UINT32			major;
    UINT32			minor;
    } WTX_MSG_TGTFS_INODE_MKNOD_DESC;

typedef struct wtx_msg_tgtfs_inode_readdir_desc
    {
    char *			pathname; 
    } WTX_MSG_TGTFS_INODE_READDIR_DESC;

typedef struct wtx_msg_tgtfs_inode_setdir_desc
    {
    char *			pathname; 
    } WTX_MSG_TGTFS_INODE_SETDIR_DESC;

typedef struct wtx_msg_tgtfs_inode_stat_res
    {
    UINT32			st_dev[2];
    UINT32			st_inode;
    WTX_TGTFS_INODE_MODE_TYPE 	st_mode;
    UINT32			st_nlink;
    UINT32			st_uid;
    UINT32			st_gid;
    UINT32			st_rdev[2];
    UINT32			st_size;
    UINT32			st_blksize;
    UINT32			st_blocks;
    UINT32			st_atim;
    UINT32			st_mtim;
    UINT32			st_ctim;
    } WTX_TGTFS_INODE_STAT_RES;

typedef struct wtx_msg_tgtfs_inode_readdir_res
    {
    char *			       	   dname;
    struct wtx_msg_tgtfs_inode_stat_res    *pStat;
    struct wtx_msg_tgtfs_inode_readdir_res *next;
    } WTX_TGTFS_INODE_READDIR_RES; 

typedef struct wtx_msg_tgtfs_inode_readdir_list
    {
    WTX_TGTFS_INODE_READDIR_RES *	pDir;	
    UINT32				count;
    } WTX_TGTFS_INODE_READDIR_LIST; 

typedef struct wtx_msg_tgtfs_inode_stat_desc
    {
    char *			pathname; 
    } WTX_MSG_TGTFS_INODE_STAT_DESC;

typedef struct wtx_msg_tgtfs_inode_umask_desc
    {
    WTX_TGTFS_INODE_MODE_TYPE   umask;
    } WTX_MSG_TGTFS_INODE_UMASK_DESC; 
    
typedef struct wtx_msg_tgtfs_inode_readlink_desc
    {
    char *			pathname; 
    } WTX_MSG_TGTFS_INODE_READLINK_DESC;

/* ---------------------- Threads / PD (Added for Bsd/OS) --------------------*/
typedef struct wtx_task_desc
    {
    WTX_TGT_ID_T			taskId;
    WTX_CONTEXT_STATUS		taskStatus;
    } WTX_TASK_DESC;

typedef struct wtx_tasks_info_desc
    {    
    UINT32			nTasks;		/* Number of tasks */
    WTX_TASK_DESC *		pTask;		/* Tasks description */
    } WTX_TASKS_INFO_DESC;


#ifdef __cplusplus
}
#endif

#endif	/* __INCwtxtypesh */
