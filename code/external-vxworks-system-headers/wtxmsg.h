/* wtxmsg.h - WTX message definition */

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
04t,27may10,pad  Moved extern C statement after include statements.
04s,24sep04,fle  Added WTX_REGISTRY_HEARTBEAT message
04r,25may04,fle  Added wtxMsgRegistryHostSet()
04q,05jan04,x_p  Fix wtxMsgTargetFileCopy
04p,22apr03,p_b  added -cachebypass to wtxMemDisassemble
04o,26mar03,x_p  Removed V3_OFFSET
04n,05feb03,p_b  merging T2.2
04m,28jan03,p_b  canceled some changes (64 bits)
04l,13dec02,p_b  changed TGT_XXX by WTX_TGT_XXX
04k,20nov02,p_b  merging margaux/T3
04j,24jul02,x_p  Removed BSD_TARGET for documentation
04i,22jan02,x_p  Added WTX_MSG_PD_INFO_SET / GET
04h,27nov01,x_p  Added threads
04g,22aug01,x_p  Merge from bsdos.temp
04f,25aug00,p_b  updated a bad comment.
04e,05jun00,mts  Added wtxMsgPdNameGet
04d,26may00,fle  changed pUnusedIn into pWtxMsgParam for wtxMsgRegistryConnect
04c,09mar00,p_b  added load and run handling facility.
04b,29feb00,fle  added message number for WTX_LOG
04a,11feb00,fle  changed WTX_MSG_WTXREGD_LOG action from a pointer to a
                 structure for easier use
03z,01feb00,fle  moved HWTX declaration from here to wtxtypes.h
03y,20jan00,dbt  Added user service facility headers and structures.
03x,05jan00,fle  added wtxMsgInitialize() routine
		 + removed _wtx structure from here for visibility issues
03w,10dec99,bpn  Added wtxMsgKernelPdIdGet() definition.
03v,25nov99,fle  doc : fixed expand of WTX_MSG_WTXREGD_LOG
03u,22oct99,fle  added WTX_REGISTRY_ENTRY_UPDATE message
03t,21oct99,p_b  removed service management structures. Made some clean up.
03s,21oct99,fle  added the registryTimeout field in the HWTX structure (for host
		 side only)
03r,13oct99,c_c  Added WTX2 compatibility.
03q,29sep99,fle  added WTX_MSG_REG_TGTSVR_ACTION and WTX_MSG_REG_LOG_ACTION
                 registry new messages
03p,29sep99,c_c  Added ModuleFind and SymFind.
03o,14sep99,c_c  Added wtxContextCont routine and modified wtxGopherEval.
03n,25aug99,fle  added pdId to HWTX structure
03m,16jul99,fle  removed wtxMsgObjModuleUndefSymAdd and related variables
		 + moved HWTX definition from wtxp.h to here
03l,16jul99,c_c  Modified WTX_MSG_MEM_MOVE_DESC structure.
03k,09jul99,fle  removed references to wtxMsgConsoleKill and
                 wtxMsgConsoleCreate
03j,08jul99,p_b  removed WTX_CONSOLE_XXX.
03i,07jul99,fle  removed wtxSymFind since philb changes
03h,06jul99,c_c  Added wtx_msg_kill_context struct.
03g,05jul99,p_b  Rewritten wtxMsgSymListGet (), wtxMsgSymFind ().
03f,05jul99,c_c  Implemented PD context definition.
03e,02jul99,c_c  Removed WTX_EVENTPOINT_LIST references.
03d,29jun99,fle  added WTX_MSG_DESC_Q message
03c,25jun99,fle  added pdIds in all WTX_MSG_MEM related messages
03b,23jun99,c_c  changed UINT32 to WTX_TGT_ADDR_T for pdId
03a,04jun99,fle  made all the pdIds have the same type
02z,02jun99,fle  added WTX_NULLPROC definition
02y,01jun99,fle  added declarations of new wtxMsgXxx() routines
02x,18aug98,pcn  Moved WTX_SVC_TYPE and renamed WTX_MSG_EVTPT_LIST_GET.
02w,28jul98,lcs  Change TOOL_ID field of WTX_EVTPT_INFO structure to a uint32
02v,20jul98,pcn  Added evtptNum and toolId in the wtxEventpointListGet return
                 list.
02u,19jun98,pcn  Added new fields in WTX_MSG_FILE_LOAD_DESC structure.
02t,26may98,pcn  Changed WTX_MSG_EVTPT_LIST_2 in WTX_MSG_EVTPT_LIST_GET.
02s,08apr98,fle  doc: limit element comment to column 75 for manual generation
                 purpose
02r,07apr98,fle  doc: changed wtx_dasm_desc in wtx_msg_dasm_desc for mangen
02q,24mar98,dbt  added WTX_CONTEXT_STATUS_GET.
02p,03mar98,fle  got rid of WTX_REGISTRY_PING service
02o,02mar98,pcn  WTX 2: added WTX_EVENTPOINT_ADD_2, WTX_EVENTPOINT_LIST_2,
                 WTX_CACHE_TEXT_UPDATE, WTX_MEM_WIDTH_READ,
                 WTX_MEM_WIDTH_WRITE, WTX_OBJ_MODULE_CHECKSUM,
                 WTX_OBJ_MODULE_LOAD_2, WTX_OBJ_MODULE_UNLOAD_2,
                 WTX_UNREGISTER_FOR_EVENT, WTX_EVENT_LIST_GET,
                 WTX_COMMAND_SEND. Removed WTX_UN_REGIS_FOR_EVENT. Added
                 WTX_MSG_MEM_WIDTH_READ_DESC, WTX_MSG_MEM_WIDTH_COPY_DESC,
                 WTX_SVC_TYPE, WTX_MSG_LOG_CTRL, WTX_EVENT_NODE,
                 WTX_MSG_EVENT_LIST, WTX_LD_M_FILE_DESC,
                 WTX_MSG_FILE_LOAD_DESC, WTX_EVENT_2, WTX_EVTPT_2,
                 WTX_MSG_EVTPT_DESC_2, WTX_MSG_EVTPT_LIST_2.
02n,26jan98,fle  added WTX_REGISTRY_PING service number
02m,29aug97,fle  Adding the WTX_MEM_DISASSEMBLE service : creating
		   WTX_MSG_DASM_INST_LIST, WTX_DASM_INST_LIST and
		   WTX_MSG_DASM_DESC structures.
02l,06dec96,dgp  doc: correct spelling
02k,30sep96,elp  put in share/, added WTX_OBJ_MODULE_UNDEF_SYM_ADD (SPR# 6775).
02j,17jun96,p_m	 changed flags type in WTX_MSG_OPEN_DESC (SPR# 4941).
02i,10jun96,elp	 re-installed WTX_MSG_SYM_TBL_INFO type to prevent
		   compatibility problems.
02h,20may96,elp	 added WTX_SYM_TBL_INFO type (SPR# 6502).
02g,25oct95,p_m  added WTX_AGENT_MODE_GET service (SPR# 5231) and
		   WTX_DIRECT_CALL.
02f,17jul95,p_m  cleaned comments for manual generation.
02d,06jun95,p_m  replaced moduleNameOrId in WTX_MSG_SYM_MATCH_DESC by an union.
02c,01jun95,p_m  removed WTX_MSG_CALL_PARAM. added returnType and pReserved
		   and replaced isText by contextType in WTX_MSG_CONTEXT_DESC.
02b,30may95,p_m  completed WTX_MEM_SCAN and WTX_MEM_MOVE implementation.
02a,26may95,p_m  added match field in WTX_MSG_MEM_SCAN_DESC.
01z,23may95,p_m  made missing name changes.
01y,22may95,jcf  name revision.
01x,18may95,p_m  added WTX_VIO_CHAN_GET and WTX_VIO_CHAN_RELEASE.
		   removed DETECTION in enventpoint.
01w,16may95,p_m  added WTX_MSG_KILL_DESC and WTX_TARGET_ATTACH.
01v,10may95,pad  modified WTX_MSG_SYM_LIST and WTX_MSG_SYM_MATCH_DESC to get
		   defined or unknown symbols associated with a module.
01u,09may95,p_m  added wtxregd related messages. added Target Server version
		   in WTX_MSG_TS_INFO.
01t,04may95,s_w  Put in WTX_xxx message numbers previously in private/wtxp.h
01s,02may95,pad  changed WTX_MSG_MODULE_INFO format field from UINT32 to char *
01r,04apr95,p_m  fixed WTX_MSG_CONTEXT_DESC.stackBase comment.
01q,29mar95,p_m  added comments. removed #include "comtypes.h".
		   changed addr type in OBJ_SEGMENT to WTX_TGT_ADDR_T.
01p,28mar95,p_m  took care of comments line length for manual generation.
01o,24mar95,p_m  changed addr type in LD_M_SECTION to WTX_TGT_ADDR_T.
01n,19mar95,c_s  updated gopher structures.
01m,20mar95,f_v  fix few syntax error to work with mgtools
01l,16mar95,p_m  added WTX_MSG_VIO_FILE_LIST.
01k,15mar95,p_m  changed #include "vxWorks.h" to #include "host.h".
01j,10mar95,p_m	 made endian field a UINT32.
01i,03mar95,p_m	 replaced WRAPSTRING by char *.
		   added gopher structure for WTX.
01h,27feb95,p_m	 cleanup up WTX_MSG_MEM_SCAN_DESC.
		   added symTblId to WTX_MSG_SYM_TBL_INFO.
		   simplified WTX_WDB_SERVICE_DESC.
01g,25feb95,jcf	 extended WTX_TS_INFO.  converted spaces to tabs.
01f,20feb95,pad	 added WTX_WTX_SERVICE_DESC type. Modified type
		   WTX_MSG_SERVICE_DESC.
01e,09feb95,p_m	 renamed structures for more coherency.
		   get rid of structures shared with WDB.
		   added comments and cleanup.
01d,08feb95,p_m	 added loadFlag in WTX_MODULE_INFO.
01c,30jan95,p_m	 added additional routines and filenames in SERVICE_DESC.
		   changed rtnObjFile to svcObjFile in SERVICE_DESC.
		   added WTX_MEM_XFER; added WTX_MEM_SET_DESC;
		   added WTX_REG_WRITE;
01b,22jan95,p_m	 added TOOL_DESC field in WTX_TS_INFO.
		   replaced #include "wdb/wdbtypes.h" by #include "wdbtypes.h".
		   replaced rtnName with initRtnName in SERVICE_DESC.
01a,20jan95,p_m	 written.
*/

#ifndef __INCwtxmsgh
#define __INCwtxmsgh

#ifdef HOST
    #include <host.h>
#else
    #include <vxWorks.h>
#endif /* HOST */

#include <wtxtypes.h>		/* basic wtx types    */

#ifdef __cplusplus
    extern "C" {
#endif

/* WTX requests */

/*
 * This offset determines if a call was a pre V3 call or not.
 * If a call goes to the tgtsvr, and its number is less than the offset value,
 * then it will be routed to the backward compat shared lib.
 */


#define	WTX_NULLPROC			(0)
#define	WTX_TOOL_ATTACH			(1)
#define	WTX_TOOL_DETACH			(2)
#define	WTX_TS_INFO_GET			(3)
#define	WTX_TARGET_RESET		(4)
#define	WTX_TS_LOCK			(5)
#define	WTX_TS_UNLOCK			(6)
#define	WTX_TARGET_ATTACH		(7)

#define	WTX_CONTEXT_CREATE		(10)
#define	WTX_CONTEXT_KILL		(11)
#define	WTX_CONTEXT_SUSPEND		(12)
#define	WTX_CONTEXT_CONT		(13)
#define	WTX_CONTEXT_RESUME		(14)
#define	WTX_CONTEXT_STEP		(15)
#define	WTX_CONTEXT_STATUS_GET		(16)
#define	WTX_CONTEXT_STOP		(17)
#define WTX_CONTEXT_ATTACH		(18)
#define WTX_CONTEXT_DETACH		(19)

#define	WTX_EVENTPOINT_ADD		(20)
#define	WTX_EVENTPOINT_DELETE		(21)
#define WTX_EVENTPOINT_LIST_GET		(22)
#define WTX_EVENTPOINT_LIST             (23)

#define	WTX_MEM_CHECKSUM		(30)
#define	WTX_MEM_READ			(31)
#define	WTX_MEM_WRITE			(32)
#define	WTX_MEM_SET			(33)
#define	WTX_MEM_SCAN			(34)
#define	WTX_MEM_MOVE			(35)
#define	WTX_MEM_ALLOC			(36)
#define	WTX_MEM_FREE			(37)
#define	WTX_MEM_INFO_GET		(38)
#define	WTX_MEM_ALIGN			(39)
#define	WTX_MEM_REALLOC			(40)
#define	WTX_MEM_ADD_TO_POOL		(41)
#define WTX_MEM_DISASSEMBLE		(42)
#define WTX_CACHE_TEXT_UPDATE		(43)

#define	WTX_REGS_GET			(50)
#define	WTX_REGS_SET			(51)

#define	WTX_OPEN			(60)
#define	WTX_VIO_READ			(61)
#define	WTX_VIO_WRITE			(62)
#define	WTX_CLOSE			(63)
#define	WTX_VIO_CTL			(64)
#define	WTX_VIO_FILE_LIST		(65)
#define	WTX_VIO_CHAN_GET		(66)
#define	WTX_VIO_CHAN_RELEASE		(67)

#define	WTX_OBJ_MODULE_LOAD		(70)
#define	WTX_OBJ_MODULE_UNLOAD		(71)
#define	WTX_OBJ_MODULE_LIST		(72)
#define	WTX_OBJ_MODULE_INFO_GET		(73)
#define	WTX_OBJ_MODULE_FIND		(74)
#define WTX_OBJ_MODULE_CHECKSUM         (75)

#define	WTX_SYM_TBL_CREATE		(80)
#define	WTX_SYM_TBL_DELETE		(81)
#define	WTX_SYM_TBL_LIST_GET		(82)
#define	WTX_SYM_LIST_GET		(83)
#define	WTX_SYM_TBL_INFO_GET		(84)
#define	WTX_SYM_FIND			(85)
#define	WTX_SYM_ADD			(86)
#define	WTX_SYM_REMOVE			(87)

#define	WTX_EVENT_GET			(100)
#define	WTX_REGISTER_FOR_EVENT		(101)
#define	WTX_UNREGISTER_FOR_EVENT	(102)
#define	WTX_EVENT_ADD			(103)
#define WTX_EVENT_LIST_GET          	(104)

#define	WTX_GOPHER_EVAL			(110)
#define	WTX_FUNC_CALL			(111)
#define	WTX_SERVICE_ADD			(112)
#define	WTX_WTX_SERVICE_LIST		(113)
#define	WTX_WDB_SERVICE_LIST		(114)
#define	WTX_AGENT_MODE_SET		(117)
#define	WTX_AGENT_MODE_GET		(118)
#define	WTX_DIRECT_CALL			(119)

#define	WTX_OBJ_KILL			(120)
#define	WTX_OBJ_RESTART			(121)
#define WTX_COMMAND_SEND		(122)
#define WTX_LOG				(123)

#define WTX_PD_INFO_Q_GET		(130)

#define WTX_TARGET_FILE_COPY		(140)
#define WTX_TARGET_FILE_REMOVE		(141)

#define WTX_TGTFS_INODE_CTRL		(150)

#define WTX_PD_TASKS_LIST		(160)
#define WTX_PD_INFO_SET			(161)
#define WTX_PD_INFO_GET			(162)

#define WTX_REGISTER			(201)
#define WTX_UNREGISTER			(202)
#define WTX_INFO_GET			(203)
#define WTX_INFO_Q_GET			(204)
#define WTX_WTXREGD_TGTSVR_ACTION	(205)
#define WTX_WTXREGD_LOG			(206)
#define WTX_REGISTRY_ENTRY_ADD		(207)
#define WTX_REGISTRY_ENTRY_REMOVE	(208)
#define WTX_REGISTRY_ENTRY_GET		(209)
#define WTX_REGISTRY_ENTRY_LIST_GET	(210)
#define WTX_REGISTRY_ENTRY_UPDATE	(211)
#define WTX_REGISTRY_HEARTBEAT		(212)

#define WTX_USR_SVC_CTRL		(220)
#define WTX_USR_SVC_CALL		(221)

/* typedefs */

typedef struct wtx_msg_result		/* Simple request result              */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_VALUE		val;		/* Result value of call               */
    } WTX_MSG_RESULT;

typedef struct wtx_msg_param		/* Simple request parameter           */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_VALUE		param;		/* Param value of call                */
    } WTX_MSG_PARAM;

typedef struct wtx_msg_param_with_pd	/* simple request parameter with PDID */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_VALUE_WITH_PD	param;		/* parameter with PD ID               */
    } WTX_MSG_PARAM_WITH_PD;

/* -------------------------------- registry -------------------------------- */

typedef struct wtx_msg_wtxregd_pattern	/* wtxregd pattern                    */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    char *		name;		/* Pattern to match wpwrName          */
    char *		type;		/* Pattern to match wpwrType          */
    char *		key;		/* Pattern to match wpwrKey           */
    } WTX_MSG_WTXREGD_PATTERN;

typedef struct wtx_msg_wtxregd_info	/* wtxregd info with host name/IP     */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_WTXREGD_INFO	regdInfo;	/* registry info/match desc           */
    } WTX_MSG_WTXREGD_INFO;

typedef struct wtx_msg_wtxregd_item	/* registry item desc per name        */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_WTXREGD_ITEM	regdItem;	/* exact item short desc (name/IP)    */
    } WTX_MSG_WTXREGD_ITEM;

typedef struct wtx_msg_tgtsvr_action		/* target server action desc  */
    {
    WTX_CORE			wtxCore;	/* WTX message core           */
    WTX_TGTSVR_ACTION *		pAction;	/* action type to perform     */
    } WTX_MSG_TGTSVR_ACTION;

typedef struct wtx_msg_svr_desc         /* Server descriptor message          */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */
    WTX_SVR_DESC        wtxSvrDesc;     /* Server Descriptor                  */
    } WTX_MSG_SVR_DESC;

typedef struct wtx_msg_svr_desc_q       /* Server desc. queue message         */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */
    WTX_SVR_DESC_Q      wtxSvrDescQ;    /* Server Descriptor Queue            */
    } WTX_MSG_SVR_DESC_Q;

typedef struct wtx_msg_wtxregd_log		/* wtxregd log action         */
    {
    WTX_CORE			wtxCore;	/* WTX message core           */
    WTX_LOG_ACTION		action;		/* log action to perform      */
    } WTX_MSG_WTXREGD_LOG;

typedef struct wtx_msg_desc_q
    {
    WTX_CORE                    wtxCore;        /* wtx message core           */
    WTX_DESC_Q *                pDescQ;         /* wtx desc queue             */
    } WTX_MSG_DESC_Q;

/* --------------------------------- server --------------------------------- */

typedef struct wtx_msg_ts_info		/* TS information message             */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TS_INFO		tsInfo;		/* TS info structure                  */
    } WTX_MSG_TS_INFO;

typedef struct wtx_msg_ts_lock		/* Lock message                       */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    UINT32		lockType;	/* Lock type to use                   */
    } WTX_MSG_TS_LOCK;

typedef struct wtx_msg_ts_unlock	/* Unlock message                     */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    BOOL32		force;		/* Force unlock type to use           */
    } WTX_MSG_TS_UNLOCK;

typedef struct wtx_msg_tool_desc 	/* Tool desc. message                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TOOL_DESC	wtxToolDesc;	/* Tool descriptor                    */
    } WTX_MSG_TOOL_DESC;

typedef struct wtx_msg_tool_id		/* Tool identifier message            */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    } WTX_MSG_TOOL_ID;

typedef struct wtx_msg_kill_desc	/* Kill descriptor message            */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    UINT32		request;	/* Object kill flag                   */
    WTX_VALUE		arg;		/* Object kill additional arg         */
    } WTX_MSG_KILL_DESC;

typedef struct wtx_msg_log_ctrl         /* Logging control message            */
    {
    WTX_CORE wtxCore;                   /* WTX message core                   */

    WTX_SVC_TYPE    svcDesc;            /* Service type and action            */
    WTX_VALUE       svcParam;           /* Parameter needed                   */
    int             svcValue;           /* Extra parameter                    */
    } WTX_MSG_LOG_CTRL;

/* --------------------------- symbol operations ---------------------------- */

typedef struct wtx_msg_symbol_desc	/* Symbol message                     */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_SYMBOL		symbol;		/* Symbol                             */
    } WTX_MSG_SYMBOL_DESC;

typedef struct wtx_msg_sym_list		/* Symbol list message                */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Prot. Dom Id                       */

    WTX_SYM_LIST 	symList;	/* Symbol list                        */
    BOOL32		moreToCome;	/* TRUE if symbols are remaining      */
    } WTX_MSG_SYM_LIST;

typedef struct wtx_msg_sym_tbl_info	/* Symbol table information           */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_TGT_ID_T	symTblId;	/* Symbol table identifier            */
    UINT32		symNum;		/* Number of symbols                  */
    BOOL32		sameNameOk;	/* Name clash policy                  */
    } WTX_MSG_SYM_TBL_INFO;

typedef struct wtx_msg_sym_match_desc   /* Symbol lookup descriptor           */
    {
    WTX_CORE			wtxCore;	/* WTX message core           */

    WTX_SYM_FIND_CRITERIA	criteria;	/* criteria struct            */
    BOOL32			giveMeNext;	/* TRUE for a follow-up req   */
    } WTX_MSG_SYM_MATCH_DESC;

/* --------------------------- VIO operations ------------------------------- */

typedef struct wtx_msg_open_desc	/* File opening descriptor            */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    char *		filename;	/* Filename                           */
    WTX_OPEN_FLAG	flags;		/* Unix style open flags              */
    INT32		mode;		/* Unix style mode                    */
    INT32		channel;	/* Channel id for redirection         */
    } WTX_MSG_OPEN_DESC;

typedef struct wtx_msg_vio_ctl_desc	/* VIO control descriptor             */
    {
    WTX_CORE		wtxCore; 	/* WTX message core                   */

    INT32		channel;	/* VIO channel number                 */
    UINT32		request;	/* Control operation                  */
    UINT32		arg;		/* Control argument                   */
    } WTX_MSG_VIO_CTL_DESC;

typedef struct wtx_msg_vio_copy_desc	/* Virtual I/O data                   */
    {
    WTX_CORE		wtxCore; 	/* WTX message core                   */

    UINT32		channel;	/* Virtual I/O channel                */
    UINT32		maxBytes;	/* Maximum bytes to transfer          */
    void *		baseAddr;	/* Base address of data               */
    } WTX_MSG_VIO_COPY_DESC;

typedef struct wtx_msg_vio_file_list	/* VIO files list message             */
    {
    WTX_CORE		wtxCore; 	/* WTX message core                   */

    WTX_VIO_FILE_DESC * pVioFileList;	/* VIO file list                      */
    } WTX_MSG_VIO_FILE_LIST;

/* ------------------------- Target Disk operation ---------------------------*/

typedef struct wtx_msg_target_file_copy_desc
    {
    WTX_CORE	   	wtxCore;	/* WTX message core                   */
    char *		srcPathname;	/* Host source Pathname	 	      */
    char *		dstPathname;	/* Target destination Pathname 	      */
    UINT32		options;	/* load options. Any combination of:
					 *  - WTX_TARGET_FILE_COPY_NOMKDIR
					 *  - WTX_TARGET_FILE_COPY_CHECK
					 */
    } WTX_MSG_TARGET_FILE_COPY_DESC; 
    
typedef struct wtx_msg_target_file_remove_desc
    {
    WTX_CORE	   	wtxCore;	/* WTX message core                   */
    char *		fileName;	/* Target file to erase	 	      */
    UINT32		options;	/* load options. Any combination of:
					 *  - WTX_TARGET_FILE_REMOVE_FORCE
					 */
    } WTX_MSG_TARGET_FILE_REMOVE_DESC;

/* ------------------------- load operation ----------------------------------*/

typedef struct wtx_msg_file_load_desc	/* Object module load desc.           */
    {
    WTX_CORE	   	wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Prot. Dom. Id in which we load     */
    UINT32		loadOpt;	/* load options. Any combination of:
    					 *  - WTX_LOAD_ASYNCHRONOUSLY
					 *  - WTX_LOAD_FROM_TOOL
					 */
    WTX_LOAD_COMMAND	loadCmd;	/* load subcommand                    */
    union wtx_load_subcommand
	{
	WTX_MODULE_FILE_DESC	moduleDesc;	/* module descriptor          */
	WTX_UPLOAD_BUF		loadBuffer;	/* upload buffer              */
	WTX_LOAD_PROGRESS_INFO	progressInfo;	/* async load progress infos  */
	WTX_MODULE_INFO		moduleInfo;	/* module info when loaded    */
	} wtxLoadCmdInfo;
    } WTX_MSG_FILE_LOAD_DESC;

/* ------------------------- module operation --------------------------------*/

typedef struct wtx_msg_module_list	/* Object module list                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* owning Prot. Dom.                  */

    WTX_MODULE_LIST	moduleList;	/* Module list struct                 */
    } WTX_MSG_MODULE_LIST;

typedef struct wtx_msg_module_info	/* Object module information          */
    {
    WTX_CORE	  	wtxCore;	/* WTX message core                   */

    WTX_MODULE_INFO	moduleInfo;	/* object module information          */
    } WTX_MSG_MODULE_INFO;

typedef struct wtx_msg_mod_name_or_id	/* Module name or identifier          */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Prot. Dom. Id in which we look     */

    WTX_TGT_ID_T	moduleId;	/* Module Id                          */
    char *		filename;	/* Module file name                   */
    UINT32		option;		/* option field to carry misc info    */
    } WTX_MSG_MOD_NAME_OR_ID;

typedef struct wtx_msg_mod_match_desc   /* Symbol lookup descriptor           */
    {
    WTX_CORE			wtxCore;	/* WTX message core           */

    WTX_MOD_FIND_CRITERIA	criteria;	/* criteria struct            */
    } WTX_MSG_MOD_MATCH_DESC;

/* -------------------------- event operation --------------------------------*/

typedef struct wtx_msg_event_desc  	/* Event message                      */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_EVENT_DESC	eventDesc;	/* Event descriptor                   */
    } WTX_MSG_EVENT_DESC;

typedef struct wtx_msg_event_reg_desc	/* WTX event register desc.           */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    char *		evtRegExp;	/* Register event reg. expr.          */
    } WTX_MSG_EVENT_REG_DESC;

typedef struct wtx_msg_evtpt_desc	/* Eventpoint message                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_EVTPT		wtxEvtpt;	/* Eventpoint                         */
    } WTX_MSG_EVTPT_DESC;

typedef struct wtx_msg_event_list       /* Message for all events             */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */

    WTX_EVENT_NODE *    pEventList;     /* List of events                     */
    } WTX_MSG_EVENT_LIST;

typedef struct wtx_msg_evtpt_list	/* Eventpoint list message            */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */

    UINT32              nEvtpt;         /* Num. eventpoint in list            */
    WTX_EVTPT_INFO *    pEvtptInfo;     /* Eventpoint info list               */
    } WTX_MSG_EVTPT_LIST;

/* -------------------------- memory operations ------------------------------*/

typedef struct wtx_msg_mem_info	 	/* Memory information                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_MEM_INFO	wtxMemInfo;	/* memory information                 */
    } WTX_MSG_MEM_INFO;

typedef struct wtx_msg_mem_xfer_desc	/* Memory transfer message            */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_MEM_XFER	memXfer;	/* Mem. transfer desc.                */
    } WTX_MSG_MEM_XFER_DESC;

typedef struct wtx_msg_reg_write	/* Register(s) to set                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_REG_SET_TYPE 	regSetType;	/* Type of register set               */
    WTX_CONTEXT	 	context;	/* Associated context                 */
    WTX_MEM_XFER 	memXfer;	/* New value of register(s)           */
    } WTX_MSG_REG_WRITE;

typedef struct wtx_msg_reg_read		/* Register(s) to get                 */
    {
    WTX_CORE	    	wtxCore;	/* WTX message core                   */

    WTX_REG_SET_TYPE   	regSetType;	/* Type of register set               */
    WTX_CONTEXT	    	context;	/* Associated context                 */
    WTX_MEM_REGION  	memRegion;	/* Register block subregion           */
    } WTX_MSG_REG_READ;

typedef struct wtx_msg_mem_block_desc	/* Target memory block                */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Prot. Dom from which we want to    */

    WTX_TGT_ADDR_T	startAddr;	/* Blocks starts from here            */
    UINT32		numBytes;	/* Number of bytes in block           */
    } WTX_MSG_MEM_BLOCK_DESC;

typedef struct wtx_msg_mem_scan_desc	/* Target memory scan desc.           */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Protection Domain ID to look into  */

    BOOL32		match;		/* TRUE for matching pattern          */
    WTX_TGT_ADDR_T	startAddr;	/* Start addr. for scanning           */
    WTX_TGT_ADDR_T	endAddr;	/* End addr. for scanning             */
    UINT32		numBytes;	/* Number of bytes in pattern         */
    void *		pattern;	/* Byte pattern to look for           */
    } WTX_MSG_MEM_SCAN_DESC;

typedef struct wtx_msg_mem_move_desc	/* Target memory move desc.           */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	srcPdId;	/* source Protection Domain           */
    WTX_TGT_ADDR_T	source;		/* Copy from here                     */
    WTX_TGT_ID_T	dstPdId;	/* destination Protection Domain      */
    WTX_TGT_ADDR_T	destination;	/* To there                           */
    UINT32		numBytes;	/* Number of bytes to copy            */
    } WTX_MSG_MEM_MOVE_DESC;

typedef struct wtx_msg_mem_set_desc	/* Memory setting desc.               */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* PD ID to look into                 */

    UINT32		value;		/* Value to set                       */
    UINT8		width;		/* Value width 1, 2, 4 or 8 bytes     */
    WTX_TGT_ADDR_T	startAddr;	/* Set from here                      */
    UINT32		numItems;	/* Number of items to set             */
    } WTX_MSG_MEM_SET_DESC;

typedef struct wtx_msg_mem_copy_desc	/* Target memory copy desc.           */
    {
    WTX_CORE            wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* PD ID to look into                 */

    BOOL32		hostToTgt;	/* it is a host to target mem copy    */
    UINT32              hostAddr;	/* host memory address                */
    WTX_TGT_ADDR_T      tgtAddr;	/* target memory address              */
    UINT32              numBytes;	/* Bytes to copy/bytes copied         */
    UINT8               width;		/* Value width 1, 2, 4 or 8 bytes     */
    UINT32		options;	/* memory operations options          */
    } WTX_MSG_MEM_COPY_DESC;

/* -------------------------- context operations -----------------------------*/

typedef struct wtx_msg_context		/* Context message                    */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_CONTEXT_TYPE	contextType;	/* Type of context                    */
    WTX_CONTEXT_ID_T	contextId;	/* Context ID                         */
    WTX_CONTEXT_ID_T	contextSubId;	/* context Sub ID                     */
    } WTX_MSG_CONTEXT;

typedef struct wtx_msg_kill_context	/* kill context desc.                */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_KILL_CONTEXT 	wtxKillContext;	/* Context to kill                    */
    } WTX_MSG_KILL_CONTEXT;

typedef struct wtx_msg_context_desc		/* Context creation desc.     */
    {
    WTX_CORE		wtxCore;		/* WTX message core           */
    WTX_CONTEXT_DESC	wtxContextDesc;		/* WTX context description    */
    } WTX_MSG_CONTEXT_DESC;

typedef struct wtx_msg_context_step_desc /* Single step desc.                 */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_CONTEXT	 	context;	/* Context to step                    */
    WTX_TGT_ADDR_T	startAddr;	/* Lower bound of step range          */
    WTX_TGT_ADDR_T	endAddr;	/* Upper bound of step range          */
    } WTX_MSG_CONTEXT_STEP_DESC;

/* -------------------------- gopher operations ------------------------------*/

typedef struct wtx_msg_gopher_tape 	/* Gopher tape message                */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_GOPHER_TAPE	tape;		/* Gopher tape                        */
    } WTX_MSG_GOPHER_TAPE;

/* -------------------------- disassembler operations ----------------------- */

typedef struct wtx_msg_dasm_desc        /* Instructions desc. to match        */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */

    WTX_TGT_ID_T        pdId;           /* PD in which we want to work        */
    WTX_TGT_ADDR_T      startAddr;      /* Disassembling start address        */
    WTX_TGT_ADDR_T      endAddr;        /* Disassembling end address          */
    UINT32              nInst;          /* Number of instructions to get      */
    BOOL32              printAddr;      /* Prepends instruction address       */
    BOOL32              printOpcodes;   /* Prepends instruction opcodes       */
    BOOL32              giveMeNext;     /* TRUE for a follow-up req           */
    BOOL32              hexAddr;        /* Turn off "symbolic + offset"       */
    BOOL32		cacheByPass;    /* bypass cache ?		      */
    } WTX_MSG_DASM_DESC; 

typedef struct wtx_msg_dasm_inst_list   /* Instructions list message          */
    {
    WTX_CORE            wtxCore;        /* WTX message core                   */
    WTX_TGT_ID_T        pdId;           /* Protection Domain ID to look into  */

    WTX_DASM_INST_LIST  instList;       /* Symbol list                        */
    BOOL32              moreToCome;     /* TRUE if instructions remain        */
    } WTX_MSG_DASM_INST_LIST;

/* ---------------------- Protection domain operations ---------------------- */

typedef struct wtx_msg_pd_desc_q
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */

    WTX_PD_DESC_Q	wtxPdDescQ;	/* WTX protection domain queue        */
    } WTX_MSG_PD_DESC_Q;

typedef struct wtx_msg_pd_info_set_desc
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Protection Domain ID to set option */
    WTX_PD_INFO_OPT	options;	/* Options 			      */
    } WTX_MSG_PD_INFO_SET_DESC;

typedef struct wtx_msg_pd_info_get_desc
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_ID_T	pdId;		/* Protection Domain ID to set option */
    } WTX_MSG_PD_INFO_GET_DESC;

/* ---------------------- User service operations --------------------------- */

typedef struct wtx_msg_usr_svc_ctrl_info /* user service control information */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGT_INT_T	numInts;	/* depends on opcode */
    WTX_TGT_ID_T	svcId;		/* command Id */
    WTX_USR_SVC_CTRL_CMD opcode;	/* operation to perform */
    union
	{
	WTX_USR_SVC_ADD_INFO add;    /* specific params to add a service */
	WTX_USR_SVC_REM_INFO rem;    /* specific params to remove a service */
	WTX_USR_SVC_FIND_INFO find;  /* specific params to find a service */
	} extra;
    } WTX_MSG_USR_SVC_CTRL_INFO;
  
/* ---------------------- Target filesystem IO --------------------------- */

typedef struct wtx_msg_tgtfs_inode_ctrl_info	/* I-node operations */
    {
    WTX_CORE			wtxCore;	/* WTX message core	*/   
    WTX_TGTFS_INODE_CTRL_CMD	opcode;		/* operation to perform */
    WTX_TGTFS_INODE_CTRL_OPT	options;	/* options */
    union 
        {
	WTX_MSG_TGTFS_INODE_MKDIR_DESC	mkdir;		/* mkdir */
        WTX_MSG_TGTFS_INODE_RMDIR_DESC	rmdir;		/* rmdir */
	WTX_MSG_TGTFS_INODE_MV_DESC	mv;		/* mv */
	WTX_MSG_TGTFS_INODE_RM_DESC	rm;		/* rm */
	WTX_MSG_TGTFS_INODE_LINK_DESC	link;	 	/* link */
	WTX_MSG_TGTFS_INODE_LINK_DESC	symlink;	/* symlink */
	WTX_MSG_TGTFS_INODE_CP_DESC	cp;		/* cp */
	WTX_MSG_TGTFS_INODE_MKNOD_DESC	mknod;		/* mknod */
	WTX_MSG_TGTFS_INODE_READDIR_DESC readdir;	/* readdir */
	WTX_MSG_TGTFS_INODE_SETDIR_DESC  setdir;	/* setdir */
	WTX_MSG_TGTFS_INODE_STAT_DESC	 stats;		/* stat */
	WTX_MSG_TGTFS_INODE_CHMOD_DESC   chmod;		/* chmod */
	WTX_MSG_TGTFS_INODE_CHOWN_DESC   chown;		/* chown */
	WTX_MSG_TGTFS_INODE_UMASK_DESC	 umask;		/* umask */
	WTX_MSG_TGTFS_INODE_READLINK_DESC readlink;	/* readlink */
	} params; 
    } WTX_MSG_TGTFS_INODE_CTRL_INFO; 

typedef struct wtx_msg_tgtfs_inode_ctrl_result		/* Simple request result */
    {
    WTX_CORE		wtxCore;	/* WTX message core                   */
    WTX_TGTFS_INODE_CTRL_CMD	opcode;	/* operation to perform 	      */
    WTX_VALUE		val;		/* Result value of call               */
    union 
       {
       WTX_TGTFS_INODE_READDIR_LIST  	readdir;	/* readdir element list */
       WTX_TGTFS_INODE_STAT_RES *	pStat;		/* stat result */
       } extras; 
    } WTX_MSG_TGTFS_INODE_CTRL_RESULT;

/* ---------------------- Theads (PD/TASKS) --------------------------------- */
typedef struct wtx_msg_tasks_info_desc
    {
    WTX_CORE			wtxCore;	/* WTX message core	*/   
    WTX_TASKS_INFO_DESC 	res;		/* Result */
    } WTX_MSG_TASKS_INFO_DESC;
    
/* ----------------------- End of messages definition ----------------------- */

/* forward declarations */

extern WTX_TGT_ID_T wtxMsgKernelPdIdGet
    (
    HWTX                hWtx            /* wtx API handler    */
    );

extern STATUS wtxMsgAgentModeGet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgAgentModeSet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgCacheTextUpdate
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_BLOCK_DESC *	pWtxMsgMemBlockDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgClose
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgCommandSend
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextStop
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextCont
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextCreate
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_CONTEXT_DESC *	pWtxMsgContextDesc,	/* Input msg. desc.   */
    WTX_MSG_CONTEXT *		pWtxMsgContext		/* Output msg. result */
    );

extern STATUS wtxMsgContextKill
    (
    HWTX			hWtx,		/* WTX API handler    */
    WTX_MSG_KILL_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextResume
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextStatusGet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextStep
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_CONTEXT_STEP_DESC *	pWtxMsgContextStepDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgContextSuspend
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgDirectCall
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_CONTEXT_DESC *	pWtxMsgContextDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgErrDispatch		/* dispatch error for given handle */
    (
    HWTX		hWtx,		/* WTX API handler                 */
    WTX_ERROR_T		errCode,	/* error code pointer              */
    void *		pUnused		/* unused yet                      */
    );

extern STATUS wtxMsgEventpointAdd
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_EVTPT_DESC *	pWtxMsgEvtptDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgEventpointDelete
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgEventpointListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_TOOL_ID *		pWtxMsgToolId,		/* Input msg. desc.   */
    WTX_MSG_EVTPT_LIST *	pWtxMsgEvtptList	/* Output msg. result */
    );

extern STATUS wtxMsgEventAdd
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_EVENT_DESC *	pWtxMsgEventDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgEventGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_TOOL_ID *		pWtxMsgToolId,		/* Input msg. desc.   */
    WTX_MSG_EVENT_DESC *	pWtxMsgEventDesc	/* Output msg. result */
    );

extern STATUS wtxMsgEventListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_PARAM *		pWtxMsgParam,		/* Input msg. desc.   */
    WTX_MSG_EVENT_LIST *	pWtxMsgEventList	/* Output msg. result */
    );

extern STATUS wtxMsgExchangeControl		/* sends a CTL event to exch  */
    (
    HWTX		hWtx,			/* WTX API handle             */
    WTX_EXCHANGE_DESC *	pExchangeDescIn,	/* description of ctl to send */
    WTX_EXCHANGE_DESC *	pExchangeDescOut	/* result of ctl action       */
    );

extern STATUS wtxMsgFreeAdd
    (
    HWTX		hWtx,		/* wtx session handler              */
    void *		pToFree,	/* pointer to be freed              */
    FUNCPTR		pFreeRtn,	/* routine to use to free pToFree   */
    void *		pMsgToFree,	/* message to free if needed        */
    WTX_REQUEST		svcNum		/* service num to free if needed    */
    );

extern STATUS wtxMsgFreeListSearch	/* searches for pointer in free list */
    (
    HWTX		hWtx,		/* wtx session handler               */
    void *		pToFind,	/* pointer to find in list           */
    void *		pUnused		/* unused pointer                    */
    );

extern STATUS wtxMsgFreeListUpdate	/* updates a free node in list     */
    (
    HWTX		hWtx,		/* wtx session handler             */
    WTX_FREE_DESC *	pWtxFreeDesc,	/* description of pointer to free  */
    void *		pUnused		/* unused pointer                  */
    );

extern STATUS wtxMsgFuncCall
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_CONTEXT_DESC *	pWtxMsgContextDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgGopherEval
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_PARAM_WITH_PD *	pWtxMsgParam,		/* Input msg. desc.   */
    WTX_MSG_GOPHER_TAPE *	pWtxMsgGopherTape	/* Output msg. result */
    );

extern STATUS wtxMsgInitialize	/* initialize a WTX handle for a new session  */
    (
    HWTX *	phWtx		/* WTX handle pointer to initialise           */
    );

extern STATUS wtxMsgInfoGet
    (
    HWTX			hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *		pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC *		pWtxMsgSvrDesc	/* Output msg. result */
    );

extern STATUS wtxMsgMemAddToPool
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_BLOCK_DESC *	pWtxMsgMemBlockDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemAlign
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_BLOCK_DESC *	pWtxMsgMemBlockDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemAlloc
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_PARAM_WITH_PD *	pWtxMsgParamWithPD,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemChecksum
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_SET_DESC *	pWtxMsgMemSetDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemDisassemble
    (
    HWTX                        hWtx,                   /* WTX API handler    */
    WTX_MSG_DASM_DESC *         pWtxMsgDasmDesc,        /* Input msg. desc.   */
    WTX_MSG_DASM_INST_LIST *    pWtxMsgDasmInstList     /* Output msg. result */
    );

extern STATUS wtxMsgMemFree
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_PARAM_WITH_PD *	pWtxMsgParamWithPD,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemInfoGet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_MEM_INFO *	pWtxMsgMemInfo	/* Output msg. result */
    );

extern STATUS wtxMsgMemMove
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_MOVE_DESC *	pWtxMsgMemMoveDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemRealloc
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_BLOCK_DESC *	pWtxMsgMemBlockDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemScan
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_SCAN_DESC *	pWtxMsgMemScanDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemSet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MEM_SET_DESC *	pWtxMsgMemSetDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgMemRead
    (
    HWTX			hWtx,			/* WTX API handler  */
    WTX_MSG_MEM_COPY_DESC *	pWtxMsgMemCopyDescIn,	/* Input msg. desc. */
    WTX_MSG_MEM_COPY_DESC *	pWtxMsgMemCopyDescOut	/* Output msg. res. */
    );

extern STATUS wtxMsgMemWrite
    (
    HWTX			hWtx,			/* WTX API handler  */
    WTX_MSG_MEM_COPY_DESC *	pWtxMsgMemCopyDesc,	/* Input msg. desc. */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. res. */
    );

extern STATUS wtxMsgNullProc
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_SVR_TYPE *	pWtxSvrType,	/* Input msg. desc.   */
    void *		pVoidOut	/* Output msg. result */
    );

extern STATUS wtxMsgPdInfoQGet
    (
    HWTX		hWtx,		/* WTX session handler        */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* unused (valid) pointer     */
    WTX_MSG_PD_DESC_Q *	pWtxMsgPdDescQ	/* list of protection domains */
    );

extern STATUS wtxMsgObjKill
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_KILL_DESC *	pWtxMsgKillDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleChecksum
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MOD_MATCH_DESC *	pWtxMsgModMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleInfoGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MOD_MATCH_DESC *	pWtxMsgModMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_MODULE_INFO *	pWtxMsgModuleInfo	/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleFind
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MOD_MATCH_DESC *	pWtxMsgModMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_MODULE_LIST *	pWtxMsgModuleList	/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MOD_MATCH_DESC *	pWtxMsgModMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_MODULE_LIST *	pWtxMsgModuleList	/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleLoad
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_FILE_LOAD_DESC *	pWtxMsgFileLoadDescIn,	/* Input msg. desc.   */
    WTX_MSG_FILE_LOAD_DESC *	pWtxMsgFileLoadDescOut	/* Output msg. result */
    );

extern STATUS wtxMsgObjModuleUnload
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_MOD_NAME_OR_ID *	pWtxMsgModNameOrId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgOpen
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_OPEN_DESC *	pWtxMsgOpenDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgRegisterForEvent
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_EVENT_REG_DESC *	pWtxMsgEventRegDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryConnect	/* setting up registry exchange    */
    (
    HWTX		hWtx,		/* handle to connect to registry   */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input message desc              */
    void *		pUnusedOut	/* output pointer, not used yet    */
    );

extern void wtxMsgRegistryDisconnect	/* closing registry exchange         */
    (
    HWTX		hWtx,		/* handle to disconnect registry     */
    void *		pUnusedIn,	/* input message pointer (not used)  */
    void *		pUnusedOut	/* output message pointer (not used) */
    );

extern STATUS wtxMsgRegsGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_REG_READ *		pWtxMsgRegRead,		/* Input msg. desc.   */
    WTX_MSG_MEM_XFER_DESC *	pWtxMsgMemXferDesc	/* Output msg. result */
    );

extern STATUS wtxMsgRegsSet
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_REG_WRITE *	pWtxMsgRegWrite,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgResultFree
    (
    HWTX			hWtx,		/* WTX API handler            */
    void  *			pToFree,	/* pointer to free from list  */
    void *			pUnused		/* unused value yet           */
    );

extern STATUS wtxMsgSvrDescGet
    (
    HWTX		hWtx,			/* WTX session handler        */
    char *		serverName,		/* target server name to set  */
    char *		hostName,		/* registry host name         */
    WTX_DESC *		pWtxDesc		/* target server full desc    */
    );

extern STATUS wtxMsgSvrSet
    (
    HWTX		hWtx,			/* current wtx session handle */
    WTX_DESC *		pWtxDesc,		/* registry item desc         */
    void *		pUnused			/* unused parameter yet       */
    );

extern STATUS wtxMsgSymAdd
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_SYMBOL_DESC *	pWtxMsgSymbolDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgSymFind
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_SYM_MATCH_DESC *	pWtxMsgSymMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_SYM_LIST *		pWtxMsgSymList		/* Output msg. result */
    );

extern STATUS wtxMsgSymListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_SYM_MATCH_DESC *	pWtxMsgSymMatchDesc,	/* Input msg. desc.   */
    WTX_MSG_SYM_LIST *		pWtxMsgSymList		/* Output msg. result */
    );

extern STATUS wtxMsgSymRemove
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_SYMBOL_DESC *	pWtxMsgSymbolDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgSymTblInfoGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_PARAM *		pWtxMsgParam,		/* Input msg. desc.   */
    WTX_MSG_SYM_TBL_INFO *	pWtxMsgSymTblInfo	/* Output msg. result */
    );

extern STATUS wtxMsgTargetAttach
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgTargetPing
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgTargetReset
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgTerminate
    (
    HWTX		hWtx,		/* WTX API handler    */
    void *		pUnusedIn,	/* unused yet         */
    void *		pUnusedOut	/* unused yet         */
    );

extern STATUS wtxMsgToolAttach
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_TOOL_DESC *	pWtxMsgToolDescIn,	/* Input msg. desc.   */
    WTX_MSG_TOOL_DESC *	pWtxMsgToolDescOut	/* Output msg. result */
    );

extern STATUS wtxMsgToolCleanup
    (
    HWTX		hWtx,			/* WTX API handler     */
    void *		pUnusedIn,		/* input : unused yet  */
    void *		pUnusedOut		/* output : unused yet */
    );

extern STATUS wtxMsgToolDetach
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,		/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgTsInfoGet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_TS_INFO *	pWtxMsgTsInfo	/* Output msg. result */
    );

extern STATUS wtxMsgTsLock
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TS_LOCK *	pWtxMsgTsLock,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgTsUnlock
    (
    HWTX		hWtx,			/* WTX API handler    */
    WTX_MSG_TS_UNLOCK *	pWtxMsgTsUnlock,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgUnregisterForEvent
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_EVENT_REG_DESC *	pWtxMsgEventRegDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgVioChanGet
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_TOOL_ID *	pWtxMsgToolId,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgVioChanRelease
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgVioCtl
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_VIO_CTL_DESC *	pWtxMsgVioCtlDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgVioFileListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_TOOL_ID *		pWtxMsgToolId,		/* Input msg. desc.   */
    WTX_MSG_VIO_FILE_LIST *	pWtxMsgVioFileList	/* Output msg. result */
    );

extern STATUS wtxMsgVioRead
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_VIO_COPY_DESC *	pWtxMsgVioCopyDescIn,	/* Input msg. desc.   */
    WTX_MSG_VIO_COPY_DESC *	pWtxMsgVioCopyDescOut	/* Output msg. result */
    );

extern STATUS wtxMsgVioWrite
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_VIO_COPY_DESC *	pWtxMsgVioCopyDesc,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgContextAttach
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

extern STATUS wtxMsgContextDetach
    (
    HWTX		hWtx,		/* WTX API handler    */
    WTX_MSG_CONTEXT *	pWtxMsgContext,	/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult	/* Output msg. result */
    );

/* ----------------------- registry related routines ------------------------ */

extern STATUS wtxMsgInfoGet
    (
    HWTX			hWtx,		/* WTX API handler    */
    WTX_MSG_PARAM *		pWtxMsgParam,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC *		pWtxMsgSvrDesc	/* Output msg. result */
    );

extern STATUS wtxMsgInfoQGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_PATTERN *	pWtxMsgWtxregdPattern,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC_Q *	pWtxMsgSvrDescQ		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryEntryGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_ITEM *	pWtxMsgWtxregdItem,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC *		pWtxMsgSvrDesc		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryEntryListGet
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_INFO *	pMasWtxregdItem,	/* Input msg. desc.   */
    WTX_MSG_DESC_Q *		pWtxMsgDescQ		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryEntryAdd
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_INFO *	pWtxMsgWtxregInfo,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC *		pWtxMsgSvrDescOut	/* Output msg. result */
    );

extern STATUS wtxMsgRegistryEntryUpdate
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_INFO *	pWtxMsgWtxregInfo,	/* Input msg. desc.   */
    WTX_MSG_SVR_DESC *		pWtxMsgSvrDesc		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryEntryRemove
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_ITEM *	pWtxMsgWtxregdItem,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgRegistryLogAction			/* log action request */
    (
    HWTX			hWtx,			/* session handler    */
    WTX_MSG_WTXREGD_LOG *	pWtxMsgWtxregdLogIn,	/* input parameter    */
    WTX_MSG_WTXREGD_LOG *	pWtxMsgWtxregdLogOut	/* result decription  */
    );

extern STATUS wtxMsgRegister
    (
    HWTX		hWtx,			/* WTX API handler       */
    WTX_MSG_SVR_DESC *	pWtxMsgSvrDescIn,	/* Input msg. desc.      */
    WTX_MSG_SVR_DESC *	pWtxMsgSvrDescOut	/* Output msg. result    */
    );

extern STATUS wtxMsgTgtsvrAction
    (
    HWTX			hWtx,			/* session handler   */
    WTX_MSG_TGTSVR_ACTION *	pWtxMsgTgtsvrAction,	/* input parameter   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* result secription */
    );

extern STATUS wtxMsgUnregister
    (
    HWTX		hWtx,				/* WTX API handler    */
    WTX_MSG_PARAM *	pWtxMsgParam,			/* Input msg. desc.   */
    WTX_MSG_RESULT *	pWtxMsgResult			/* Output msg. result */
    );

extern STATUS wtxMsgRegistryHeartbeat
    (
    HWTX			hWtx,			/* WTX API handler    */
    WTX_MSG_WTXREGD_ITEM *	pWtxMsgWtxregdItem,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

/* ---------------------- WTX message utility routines ---------------------- */

extern BOOL wtxMsgIsAttached
    (
    HWTX	hWtx		/* WTX session handler */
    );


extern STATUS wtxMsgAttachFree
    (
    HWTX	hWtx			/* WTX session handler */
    );

extern STATUS wtxMsgToolDescSet
    (
    HWTX		hWtx,		/* current WTX session handler    */
    WTX_TOOL_DESC *	pToolDesc	/* value to init WTX tool desc to */
    );

extern STATUS wtxMsgToolIdSet
    (
    HWTX	 hWtx,		/* current WTX session handler */
    WTX_TGT_ID_T toolId		/* new tool Id to set          */
    );

extern BOOL32 wtxMsgToolConnected
    (
    HWTX	hWtx	/* current WTX session handler */
    );

extern STATUS wtxMsgAsyncHandleSet
    (
    HWTX		hWtx,		/* current WTX session handler */
    WTX_ASYNC_HANDLE	asyncHAndle	/* new async handler to set to */
    );

extern STATUS wtxMsgToolIdGet
    (
    HWTX		hWtx,		/* current WTX session handler      */
    WTX_MSG_TOOL_ID *	pMsgToolId	/* returned message tool ID pointer */
    );

extern STATUS wtxMsgErrSet
    (
    HWTX		hWtx,		/* current WTX session handler */
    WTX_ERROR_T		errCode		/* error code to set to        */
    );

extern WTX_ERROR_T wtxMsgErrGet
    (
    HWTX		hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgErrHandlerGet
    (
    HWTX		hWtx,		/* current WTX session handler */
    WTX_HANDLER_T *	pErrHandler	/* returned WTX error handler  */
    );

extern STATUS wtxMsgErrHandlerSet
    (
    HWTX		hWtx,		/* current WTX session handler */
    WTX_HANDLER_T *	pErrHandler	/* WTX error handler to set to */
    );

extern char * wtxMsgErrMsgGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern void * wtxMsgClientDataGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgErrMsgSet
    (
    HWTX		hWtx,	/* current WTX session handler */
    const char *	errMsg	/* error message to set to     */
    );


extern STATUS wtxMsgClientDataSet
    (
    HWTX	hWtx,		/* current WTX session handler */
    void **	ppClientData	/* client data to set to       */
    );

extern WTX_TGT_ID_T wtxMsgPdIdGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgPdNameGet
    (
    HWTX	 hWtx,		/* current WTX session handler */
    WTX_TGT_ID_T targetPdId,	/* the PD ID that we want the name of */
    char **	 pdName		/* The string to store the PD name result */
    );

extern STATUS wtxMsgPdIdSet
    (
    HWTX	 hWtx,		/* current WTX session handler */
    WTX_TGT_ID_T pdId		/* PD ID to set to             */
    );

extern WTX_DESC * wtxMsgCurrentSvrDescGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern WTX_TS_INFO * wtxMsgCurrentTsInfoGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern WTX_TOOL_DESC * wtxMsgCurrentToolDescGet
    (
    HWTX		hWtx		/* current WTX session handler */
    );

extern HWTX * wtxMsgSelfGet
    (
    HWTX		hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgVioLinkDescSemTake
    (
    HWTX	hWtx,			/* current WTX session handler */
    int		timeout			/* semTake wait timeout        */
    );

extern STATUS wtxMsgVioLinkDescSemGive
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgVioLinkDescListAdd
    (
    HWTX	hWtx,			/* current WTX session handler */
    NODE *	pNode			/* node to add to list         */
    );

extern WTX_TOOL_DESC * wtxMsgToolDescGet
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern BOOL wtxMsgAsyncNotifyIsStarted
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgAsyncHandleAlloc
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern WTX_ASYNC_HANDLE wtxMsgAsyncHandleGet
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgAsyncNotifyStart
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgAsyncNotifyStop
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgRegistryTimeoutSet
    (
    HWTX	hWtx,			/* current WTX session handler */
    int		timeout			/* timeout value to set to     */
    );

extern int wtxMsgRegistryTimeoutGet
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern WTX_DESC * wtxMsgSelfDescGet
    (
    HWTX	hWtx			/* current WTX session handler */
    );

extern STATUS wtxMsgSelfDescSet
    (
    HWTX	hWtx,			/* current WTX session handler */
    WTX_DESC *	pSelfDesc		/* seld desc to set to         */
    );

extern WTX_TGT_ID_T wtxMsgObjIdGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgUsrSvcCtrl
    (
    HWTX			hWtx,			/* WTX session handle */
    WTX_MSG_USR_SVC_CTRL_INFO *	pUsrSvcCtrlInfo,	/* Input msg. desc.   */
    WTX_MSG_RESULT *		pWtxMsgResult		/* Output msg. result */
    );

extern STATUS wtxMsgUsrSvcCall
    (
    HWTX			hWtx,			/* WTX session handle */
    WTX_MSG_MEM_XFER_DESC *	pWtxMsgMemXferInDesc,	/* Input msg. desc.   */
    WTX_MSG_MEM_XFER_DESC *	pWtxMsgMemXferOutDesc	/* Output msg. result */
    );

STATUS wtxMsgTsLogAction				/* action on tsvr log */
    (
    HWTX			hWtx,			/* session handler    */
    WTX_MSG_WTXREGD_LOG *	pWtxMsgWtxregdLogIn,	/* input parameter    */
    WTX_MSG_WTXREGD_LOG *	pWtxMsgWtxregdLogOut	/* result decription  */
    );

extern STATUS wtxMsgRegistryHostSet
    (
    HWTX		hWtx,		/* wtx session handle                 */
    const char *	host		/* remote registry host name or IP    */
    );

/* ------------------------ WTX target file routines ------------------------ */

extern STATUS wtxMsgTargetFileCopy
    (
    HWTX				hWtx,	/* current session handler */
    WTX_MSG_TARGET_FILE_COPY_DESC *	pWtxMsgTargetFileCopyInDesc,
    WTX_MSG_RESULT *	                pWtxMsgTargetFileCopyOutDesc
    );

extern STATUS wtxMsgTargetFileRemove
    (
    HWTX				hWtx,	/* current session handler */
    WTX_MSG_TARGET_FILE_REMOVE_DESC *	pWtxMsgTargetFileRemoveInDesc,
    WTX_MSG_RESULT *			pUnusedOut /* output ptr, not used yet*/
    );

/* --------------------- WTX target filesystem routines --------------------- */

extern STATUS wtxMsgTgtfsInodeCtrl
    (
    HWTX				hWtx,	/* current session handler */
    WTX_MSG_TGTFS_INODE_CTRL_INFO *	pWtxMsgTgtfsInodeCtrlInfo,
    WTX_MSG_TGTFS_INODE_CTRL_RESULT *	pResult	/* output ptr, not used yet  */
    );

extern UINT32 wtxMsgOsErrCodeGet
    (
    HWTX	hWtx		/* current WTX session handler */
    );

extern STATUS wtxMsgOsErrCodeSet
    (
    HWTX	hWtx,		/* current WTX session handler */
    UINT32	osErrCode	/* error code to set to        */
    );
    
extern UINT32 wtxMsgWtxVersionGet
    (
    HWTX        hWtx            /* current WTX session handler */
    );

extern STATUS wtxMsgWtxVersionSet
    (
    HWTX        hWtx,           /* current WTX session handler */
    UINT32      version         /* version to set */
    );

/* ---------------------- Threads handling ---------------------------------- */

extern STATUS wtxMsgPdTasksListGet
    (
    HWTX			hWtx,		/* current session handler    */
    WTX_MSG_CONTEXT *		pWtxMsgContext,	/* Input msg. desc            */
    WTX_MSG_TASKS_INFO_DESC *	pWtxMsgResult	/* Output msg. result         */
    );

extern STATUS wtxMsgPdInfoSet
    (
    HWTX			hWtx,		/* current session handler    */
    WTX_MSG_PD_INFO_SET_DESC *	pWtxMsgIn,	/* Input msg. desc.           */
    WTX_MSG_RESULT *		pWtxMsgResult	/* Output msg. result         */
    );
    
extern STATUS wtxMsgPdInfoGet
    (
    HWTX			hWtx,		/* current session handler    */
    WTX_MSG_PD_INFO_GET_DESC *	pWtxMsgIn,	/* Input msg.                 */
    WTX_MSG_RESULT *		pWtxMsgResult	/* Output msg. result         */
    );

#ifdef __cplusplus
}
#endif

#endif	/* __INCwtxmsgh */
