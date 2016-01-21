/* Aligned for MIPS64LE - MIPS64 Little-Endian */


/* THIS FILE IS AUTO_GENERATED. PLEASE DO NOT EDIT. */

#ifndef _ASMLANGUAGE

#include <vxWorks.h>
#include <taskLib.h>
#include <rtpLib.h>
#include <sdLib.h>
#include <shlLib.h>
#include <signal.h>
#include <socket.h>
#include <time.h>
#include <setjmp.h>
#include <ioLib.h>
#include <private/semSysCall.h>
#include <private/objLibP.h>
#include <private/rtpLibP.h>
#include <private/mqPxSysCall.h>
#include <private/pxObjSysCall.h>
#include <private/semPxSysCall.h>
#include <private/taskSysCall.h>
#include <private/timerSysCall.h>
#include <private/eventSysCall.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <base/b_trace_attr_t.h>
#include <base/b_trace_id_t.h>
#include <base/b_trace_event_id_t.h>
#include <base/b_pthread_t.h>

struct _exitScArgs 
	{
	int status;
	};

struct _creatScArgs 
	{
	const char * name;
	UINT32 flagPad;
	mode_t flag;
	};

struct _openScArgs 
	{
	const char * name;
	UINT32 flagsPad;
	int flags;
	UINT32 modePad;
	int mode;
	};

struct _closeScArgs 
	{
	int fd;
	};

struct _readScArgs 
	{
	int fd;
	UINT32 bufferPad;
	void * buffer;
	UINT32 maxbytesPad;
	size_t maxbytes;
	};

struct _writeScArgs 
	{
	int fd;
	UINT32 bufferPad;
	const void * buffer;
	UINT32 nbytesPad;
	size_t nbytes;
	};

struct _ioctlScArgs 
	{
	int fd;
	UINT32 functionPad;
	int function;
	UINT32 argPad;
	_Vx_ioctl_arg_t arg;
	};

struct dupScArgs 
	{
	int fd;
	};

struct dup2ScArgs 
	{
	int fd;
	UINT32 fd2Pad;
	int fd2;
	};

struct pipeScArgs 
	{
	int filedes[2];
	};

struct removeScArgs 
	{
	const char * name;
	};

struct selectScArgs 
	{
	int width;
	UINT32 readFdsPad;
	fd_set * readFds;
	UINT32 writeFdsPad;
	fd_set * writeFds;
	UINT32 excFdsPad;
	fd_set * excFds;
	UINT32 timeoutPad;
	struct timeval * timeout;
	};

struct socketScArgs 
	{
	int domain;
	UINT32 typePad;
	int type;
	UINT32 protocolPad;
	int protocol;
	};

struct bindScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr * name;
	UINT32 namelenPad;
	int namelen;
	};

struct listenScArgs 
	{
	int s;
	UINT32 backlogPad;
	int backlog;
	};

struct acceptScArgs 
	{
	int s;
	UINT32 addrPad;
	struct sockaddr * addr;
	UINT32 addrlenPad;
	int *addrlen;
	};

struct connectScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr * name;
	UINT32 namelenPad;
	int namelen;
	};

struct sendtoScArgs 
	{
	int s;
	UINT32 bufPad;
	caddr_t buf;
	UINT32 bufLenPad;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	UINT32 toPad;
	struct sockaddr * to;
	UINT32 tolenPad;
	int tolen;
	};

struct sendScArgs 
	{
	int s;
	UINT32 bufPad;
	const char * buf;
	UINT32 bufLenPad;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	};

struct sendmsgScArgs 
	{
	int s;
	UINT32 mpPad;
	struct msghdr * mp;
	UINT32 flagsPad;
	int flags;
	};

struct recvfromScArgs 
	{
	int s;
	UINT32 bufPad;
	char * buf;
	UINT32 bufLenPad;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	UINT32 fromPad;
	struct sockaddr *from;
	UINT32 pFromLenPad;
	int * pFromLen;
	};

struct recvScArgs 
	{
	int s;
	UINT32 bufPad;
	char * buf;
	UINT32 bufLenPad;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	};

struct recvmsgScArgs 
	{
	int s;
	UINT32 mpPad;
	struct msghdr * mp;
	UINT32 flagsPad;
	int flags;
	};

struct setsockoptScArgs 
	{
	int s;
	UINT32 levelPad;
	int level;
	UINT32 optnamePad;
	int optname;
	UINT32 optvalPad;
	char * optval;
	UINT32 optlenPad;
	int optlen;
	};

struct getsockoptScArgs 
	{
	int s;
	UINT32 levelPad;
	int level;
	UINT32 optnamePad;
	int optname;
	UINT32 optvalPad;
	char * optval;
	UINT32 optlenPad;
	int * optlen;
	};

struct getsocknameScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr *name;
	UINT32 namelenPad;
	int * namelen;
	};

struct getpeernameScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr *name;
	UINT32 namelenPad;
	int *namelen;
	};

struct shutdownScArgs 
	{
	int s;
	UINT32 howPad;
	int how;
	};

struct mmapScArgs 
	{
	void * addr;
	UINT32 lenPad;
	size_t len;
	UINT32 protPad;
	int prot;
	UINT32 flagsPad;
	int flags;
	UINT32 fildesPad;
	int fildes;
	UINT32 offPad;
	off64_t off;
	};

struct munmapScArgs 
	{
	void * addr;
	UINT32 lenPad;
	size_t len;
	};

struct mprotectScArgs 
	{
	void * addr;
	UINT32 lenPad;
	size_t len;
	UINT32 protPad;
	int prot;
	};

struct killScArgs 
	{
	OBJ_HANDLE rtpId;
	UINT32 signoPad;
	int signo;
	};

struct sigpendingScArgs 
	{
	sigset_t * pSet;
	};

struct sigprocmaskScArgs 
	{
	int how;
	UINT32 pSetPad;
	const sigset_t * pSet;
	UINT32 pOsetPad;
	sigset_t * pOset;
	};

struct _sigqueueScArgs 
	{
	OBJ_HANDLE rtpId;
	UINT32 signoPad;
	int signo;
	UINT32 pValuePad;
	const union sigval * pValue;
	UINT32 sigCodePad;
	int sigCode;
	};

struct _sigsuspendScArgs 
	{
	const sigset_t * pSet;
	};

struct _sigtimedwaitScArgs 
	{
	const sigset_t * pSet;
	UINT32 pInfoPad;
	struct siginfo * pInfo;
	UINT32 pTimePad;
	const struct timespec * pTime;
	};

struct _sigactionScArgs 
	{
	int signo;
	UINT32 pActPad;
	const struct sigaction * pAct;
	UINT32 pOactPad;
	struct sigaction * pOact;
	UINT32 retAddrPad;
	void * retAddr;
	};

struct chdirScArgs 
	{
	const char * name;
	};

struct _getcwdScArgs 
	{
	char * buffer;
	UINT32 lengthPad;
	int length;
	};

struct _waitpidScArgs 
	{
	OBJ_HANDLE childRtpId;
	UINT32 pStatusPad;
	int * pStatus;
	UINT32 optionsPad;
	int options;
	};

struct sysctlScArgs 
	{
	int * pName;
	UINT32 nameLenPad;
	u_int nameLen;
	UINT32 pOldPad;
	void * pOld;
	UINT32 pOldLenPad;
	size_t * pOldLen;
	UINT32 pNewPad;
	void * pNew;
	UINT32 newLenPad;
	size_t newLen;
	};

struct _schedPxInfoGetScArgs 
	{
	BOOL * pTimeSlicingOn;
	UINT32 pTimeSlicePeriodPad;
	ULONG * pTimeSlicePeriod;
	};

struct sigaltstackScArgs 
	{
	stack_t * ss;
	UINT32 ossPad;
	stack_t * oss;
	};

struct unlinkScArgs 
	{
	const char * name;
	};

struct linkScArgs 
	{
	const char * name;
	UINT32 newnamePad;
	const char * newname;
	};

struct _fsyncScArgs 
	{
	int fd;
	};

struct _fdatasyncScArgs 
	{
	int fd;
	};

struct renameScArgs 
	{
	const char * oldname;
	UINT32 newnamePad;
	const char * newname;
	};

struct fpathconfScArgs 
	{
	int fd;
	UINT32 namePad;
	int name;
	};

struct pathconfScArgs 
	{
	const char * path;
	UINT32 namePad;
	int name;
	};

struct accessScArgs 
	{
	const char * path;
	UINT32 amodePad;
	int amode;
	};

struct chmodScArgs 
	{
	const char * path;
	UINT32 modePad;
	mode_t mode;
	};

struct pxTraceCreationScArgs 
	{
	int cmd;
	UINT32 pidPad;
	pid_t pid;
	UINT32 attrPad;
	trace_attr_t * attr;
	UINT32 fdPad;
	int fd;
	UINT32 tridPad;
	trace_id_t * trid;
	};

struct pxTraceCtlScArgs 
	{
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	UINT32 filterPad;
	struct trace_event_set_t * filter;
	UINT32 howPad;
	int how;
	UINT32 thread_idPad;
	pthread_t thread_id;
	UINT32 pcPad;
	void * pc;
	UINT32 ptr_outPad;
	void * ptr_out;
	};

struct pxTraceEventScArgs 
	{
	int cmd;
	UINT32 id_inPad;
	int id_in;
	UINT32 dataPad;
	char * data;
	UINT32 data_lenPad;
	size_t data_len;
	UINT32 thread_idPad;
	pthread_t thread_id;
	UINT32 pcPad;
	void * pc;
	UINT32 id_outPad;
	trace_event_id_t * id_out;
	};

struct pxTraceEventNameQueryScArgs 
	{
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	UINT32 id_in1Pad;
	int id_in1;
	UINT32 id_in2Pad;
	int id_in2;
	UINT32 namePad;
	char * name;
	UINT32 id_outPad;
	trace_event_id_t * id_out;
	UINT32 unavailablePad;
	int * unavailable;
	};

struct pxTraceLogScArgs 
	{
	int cmd;
	UINT32 trid_inPad;
	trace_id_t trid_in;
	UINT32 fdPad;
	int fd;
	UINT32 trid_outPad;
	trace_id_t *trid_out;
	};

struct pxTraceEventGetScArgs 
	{
	int cmd;
	UINT32 tridPad;
	trace_id_t trid;
	UINT32 num_bytesPad;
	size_t num_bytes;
	UINT32 timeoutPad;
	struct timespec * timeout;
	UINT32 eventPad;
	struct posix_trace_event_info * event;
	UINT32 dataPad;
	void * data;
	UINT32 data_lenPad;
	size_t * data_len;
	UINT32 unavailablePad;
	int * unavailable;
	};

struct eventReceiveScArgs 
	{
	UINT32 events;
	UINT32 optionsPad;
	UINT32 options;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	UINT32 pEvtsReceivedPad;
	UINT32 * pEvtsReceived;
	};

struct eventSendScArgs 
	{
	int taskId;
	UINT32 eventsPad;
	UINT32 events;
	};

struct eventCtlScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 commandPad;
	VX_EVT_CTL_CMD command;
	UINT32 pArgPad;
	void * pArg;
	UINT32 pArgSizePad;
	size_t * pArgSize;
	};

struct msgQSendScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 bufferPad;
	char * buffer;
	UINT32 nBytesPad;
	size_t nBytes;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	UINT32 priorityPad;
	int priority;
	};

struct msgQReceiveScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 bufferPad;
	char * buffer;
	UINT32 maxNBytesPad;
	size_t maxNBytes;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _msgQOpenScArgs 
	{
	const char * name;
	UINT32 maxMsgsPad;
	size_t maxMsgs;
	UINT32 maxMsgLengthPad;
	size_t maxMsgLength;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	UINT32 contextPad;
	void * context;
	};

struct objDeleteScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct objInfoGetScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pInfoPad;
	void * pInfo;
	UINT32 pInfoSizePad;
	size_t * pInfoSize;
	UINT32 levelPad;
	int level;
	};

struct _semTakeScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semGiveScArgs 
	{
	OBJ_HANDLE handle;
	};

struct _semOpenScArgs 
	{
	const char * name;
	UINT32 typePad;
	SEM_TYPE type;
	UINT32 initStatePad;
	int initState;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	UINT32 contextPad;
	void * context;
	};

struct semCtlScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 commandPad;
	VX_SEM_CTL_CMD command;
	UINT32 pArgPad;
	void * pArg;
	UINT32 pArgSizePad;
	size_t * pArgSize;
	};

struct _taskOpenScArgs 
	{
	struct vx_task_open_sc_args * pArgs;
	};

struct taskCtlScArgs 
	{
	int tid;
	UINT32 commandPad;
	VX_TASK_CTL_CMD command;
	UINT32 pArgPad;
	void * pArg;
	UINT32 pArgSizePad;
	size_t * pArgSize;
	};

struct taskDelayScArgs 
	{
	_Vx_ticks_t ticks;
	};

struct rtpSpawnScArgs 
	{
	const char * rtpFileName;
	UINT32 argvPad;
	const char ** argv;
	UINT32 envpPad;
	const char ** envp;
	UINT32 priorityPad;
	int priority;
	UINT32 uStackSizePad;
	size_t uStackSize;
	UINT32 optionsPad;
	int options;
	UINT32 taskOptionsPad;
	int taskOptions;
	};

struct rtpInfoGetScArgs 
	{
	OBJ_HANDLE rtpId;
	UINT32 rtpStructPad;
	RTP_DESC * rtpStruct;
	};

struct taskKillScArgs 
	{
	OBJ_HANDLE taskHandle;
	UINT32 signoPad;
	int signo;
	};

struct _taskSigqueueScArgs 
	{
	OBJ_HANDLE taskHandle;
	UINT32 signoPad;
	int signo;
	UINT32 pValuePad;
	const union sigval * pValue;
	UINT32 sigCodePad;
	int sigCode;
	};

struct _timer_openScArgs 
	{
	const char * name;
	UINT32 modePad;
	int mode;
	UINT32 clockIdPad;
	clockid_t clockId;
	UINT32 evpPad;
	struct sigevent * evp;
	UINT32 contextPad;
	void * context;
	};

struct timerCtlScArgs 
	{
	TIMER_CTL_CMD cmdCode;
	UINT32 timerHandlePad;
	OBJ_HANDLE timerHandle;
	UINT32 pArgsPad;
	void * pArgs;
	UINT32 pArgSizePad;
	size_t pArgSize;
	};

struct pxOpenScArgs 
	{
	PX_OBJ_TYPE type;
	UINT32 namePad;
	const char * name;
	UINT32 objOpenModePad;
	int objOpenMode;
	UINT32 attrPad;
	void * attr;
	};

struct pxCloseScArgs 
	{
	OBJ_HANDLE handle;
	};

struct pxUnlinkScArgs 
	{
	PX_OBJ_TYPE type;
	UINT32 namePad;
	const char * name;
	};

struct pxCtlScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 cmdCodePad;
	PX_CTL_CMD_CODE cmdCode;
	UINT32 pArgsPad;
	void * pArgs;
	UINT32 pArgSizePad;
	size_t * pArgSize;
	};

struct pxMqReceiveScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pMsgPad;
	char * pMsg;
	UINT32 msgLenPad;
	size_t msgLen;
	UINT32 pMsgPrioPad;
	unsigned int * pMsgPrio;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	UINT32 time_outPad;
	const struct timespec * time_out;
	};

struct pxMqSendScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pMsgPad;
	const char * pMsg;
	UINT32 msgLenPad;
	size_t msgLen;
	UINT32 msgPrioPad;
	unsigned int msgPrio;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	UINT32 time_outPad;
	const struct timespec * time_out;
	};

struct pxSemWaitScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 waitOptionPad;
	PX_WAIT_OPTION waitOption;
	UINT32 time_outPad;
	const struct timespec * time_out;
	};

struct pxSemPostScArgs 
	{
	OBJ_HANDLE handle;
	};

struct pipeDevCreateScArgs 
	{
	const char * name;
	UINT32 nMessagesPad;
	size_t nMessages;
	UINT32 nBytesPad;
	size_t nBytes;
	};

struct pipeDevDeleteScArgs 
	{
	const char * name;
	UINT32 forcePad;
	BOOL force;
	};

struct _sdCreateScArgs 
	{
	char * name;
	UINT32 optionsPad;
	int options;
	UINT32 sizePad;
	size_t size;
	UINT32 physAddressPad;
	off64_t physAddress;
	MMU_ATTR attr;
	UINT32 pVirtAddressPad;
	void ** pVirtAddress;
	};

struct _sdOpenScArgs 
	{
	char * name;
	UINT32 optionsPad;
	int options;
	UINT32 modePad;
	int mode;
	UINT32 sizePad;
	size_t size;
	UINT32 physAddressPad;
	off64_t physAddress;
	MMU_ATTR attr;
	UINT32 pVirtAddressPad;
	void ** pVirtAddress;
	};

struct sdDeleteScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct sdMapScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 attrPad;
	MMU_ATTR attr;
	UINT32 optionsPad;
	int options;
	};

struct sdUnmapScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 optionsPad;
	int options;
	};

struct sdProtectScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 attrPad;
	MMU_ATTR attr;
	};

struct _edrErrorInjectScArgs 
	{
	int kind;
	UINT32 fileNamePad;
	const char *fileName;
	UINT32 lineNumberPad;
	int lineNumber;
	UINT32 regsetPad;
	REG_SET *regset;
	UINT32 addrPad;
	void *addr;
	UINT32 msgPad;
	const char *msg;
	};

struct wvEventScArgs 
	{
	int eventId;
	UINT32 pDataPad;
	const char * pData;
	UINT32 dataSizePad;
	unsigned int dataSize;
	};

struct rtpVarAddScArgs 
	{
	void ** pVar;
	UINT32 valuePad;
	void * value;
	};

struct sdInfoGetScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pSdStructPad;
	SD_DESC * pSdStruct;
	};

struct _shlOpenScArgs 
	{
	const char * name;
	UINT32 optionsPad;
	int options;
	};

struct _shlUnlockScArgs 
	{
	SHL_ID shlId;
	};

struct _shlCloseScArgs 
	{
	SHL_ID shlId;
	};

struct _shlGetScArgs 
	{
	SHL_ID shlId;
	UINT32 pInfoPad;
	SHLINFO *pInfo;
	};

struct _shlPutScArgs 
	{
	SHL_ID shlId;
	UINT32 pInfoPad;
	const SHLINFO *pInfo;
	};

struct objUnlinkScArgs 
	{
	const char * name;
	UINT32 classTypePad;
	enum windObjClassType classType;
	};

struct getprlimitScArgs 
	{
	int idtype;
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 resourcePad;
	int resource;
	UINT32 rlpPad;
	struct rlimit *rlp;
	};

struct setprlimitScArgs 
	{
	int idtype;
	UINT32 handlePad;
	OBJ_HANDLE handle;
	UINT32 resourcePad;
	int resource;
	UINT32 rlpPad;
	struct rlimit *rlp;
	};

struct _mctlScArgs 
	{
	void * addr;
	UINT32 lenPad;
	size_t len;
	UINT32 functionPad;
	int function;
	UINT32 argPad;
	void * arg;
	};

struct _taskOpenWithGuardScArgs 
	{
	struct vx_task_open_guard_sc_args * pArgs;
	};

struct clockCtlScArgs 
	{
	clockid_t clock_id;
	UINT32 cmdCodePad;
	CLOCK_CTL_CMD cmdCode;
	UINT32 pArgStructPad;
	void * pArgStruct;
	UINT32 pArgSizePad;
	size_t * pArgSize;
	};

struct _semRTakeScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semWTakeScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct _semExchangeScArgs 
	{
	OBJ_HANDLE giveHandle;
	UINT32 takeHandlePad;
	OBJ_HANDLE takeHandle;
	UINT32 timeoutPad;
	_Vx_ticks_t timeout;
	};

struct wvRtpEventScArgs 
	{
	int eventId;
	UINT32 pDataPad;
	const char * pData;
	UINT32 dataSizePad;
	unsigned int dataSize;
	};

#endif	/* _ASMLANGUAGE */
