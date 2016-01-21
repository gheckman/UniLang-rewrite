/* Aligned for x86-64 - x86-64 padding */


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
	mode_t flag;
	};

struct _openScArgs 
	{
	const char * name;
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
	size_t maxbytes;
	};

struct _writeScArgs 
	{
	int fd;
	UINT32 bufferPad;
	const void * buffer;
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
	fd_set * writeFds;
	fd_set * excFds;
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
	int *addrlen;
	};

struct connectScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr * name;
	int namelen;
	};

struct sendtoScArgs 
	{
	int s;
	UINT32 bufPad;
	caddr_t buf;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	UINT32 toPad;
	struct sockaddr * to;
	int tolen;
	};

struct sendScArgs 
	{
	int s;
	UINT32 bufPad;
	const char * buf;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	};

struct sendmsgScArgs 
	{
	int s;
	UINT32 mpPad;
	struct msghdr * mp;
	int flags;
	};

struct recvfromScArgs 
	{
	int s;
	UINT32 bufPad;
	char * buf;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	UINT32 fromPad;
	struct sockaddr *from;
	int * pFromLen;
	};

struct recvScArgs 
	{
	int s;
	UINT32 bufPad;
	char * buf;
	int bufLen;
	UINT32 flagsPad;
	int flags;
	};

struct recvmsgScArgs 
	{
	int s;
	UINT32 mpPad;
	struct msghdr * mp;
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
	int * optlen;
	};

struct getsocknameScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr *name;
	int * namelen;
	};

struct getpeernameScArgs 
	{
	int s;
	UINT32 namePad;
	struct sockaddr *name;
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
	size_t len;
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
	size_t len;
	};

struct mprotectScArgs 
	{
	void * addr;
	size_t len;
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
	sigset_t * pOset;
	};

struct _sigqueueScArgs 
	{
	OBJ_HANDLE rtpId;
	UINT32 signoPad;
	int signo;
	UINT32 pValuePad;
	const union sigval * pValue;
	int sigCode;
	};

struct _sigsuspendScArgs 
	{
	const sigset_t * pSet;
	};

struct _sigtimedwaitScArgs 
	{
	const sigset_t * pSet;
	struct siginfo * pInfo;
	const struct timespec * pTime;
	};

struct _sigactionScArgs 
	{
	int signo;
	UINT32 pActPad;
	const struct sigaction * pAct;
	struct sigaction * pOact;
	void * retAddr;
	};

struct chdirScArgs 
	{
	const char * name;
	};

struct _getcwdScArgs 
	{
	char * buffer;
	int length;
	};

struct _waitpidScArgs 
	{
	OBJ_HANDLE childRtpId;
	UINT32 pStatusPad;
	int * pStatus;
	int options;
	};

struct sysctlScArgs 
	{
	int * pName;
	u_int nameLen;
	UINT32 pOldPad;
	void * pOld;
	size_t * pOldLen;
	void * pNew;
	size_t newLen;
	};

struct _schedPxInfoGetScArgs 
	{
	BOOL * pTimeSlicingOn;
	ULONG * pTimeSlicePeriod;
	};

struct sigaltstackScArgs 
	{
	stack_t * ss;
	stack_t * oss;
	};

struct unlinkScArgs 
	{
	const char * name;
	};

struct linkScArgs 
	{
	const char * name;
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
	int name;
	};

struct accessScArgs 
	{
	const char * path;
	int amode;
	};

struct chmodScArgs 
	{
	const char * path;
	mode_t mode;
	};

struct pxTraceCreationScArgs 
	{
	int cmd;
	UINT32 pidPad;
	pid_t pid;
	trace_attr_t * attr;
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
	int how;
	UINT32 thread_idPad;
	pthread_t thread_id;
	void * pc;
	void * ptr_out;
	};

struct pxTraceEventScArgs 
	{
	int cmd;
	UINT32 id_inPad;
	int id_in;
	UINT32 dataPad;
	char * data;
	size_t data_len;
	pthread_t thread_id;
	void * pc;
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
	trace_event_id_t * id_out;
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
	struct timespec * timeout;
	struct posix_trace_event_info * event;
	void * data;
	size_t * data_len;
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
	size_t * pArgSize;
	};

struct msgQSendScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 bufferPad;
	char * buffer;
	size_t nBytes;
	_Vx_ticks_t timeout;
	UINT32 priorityPad;
	int priority;
	};

struct msgQReceiveScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 bufferPad;
	char * buffer;
	size_t maxNBytes;
	_Vx_ticks_t timeout;
	};

struct _msgQOpenScArgs 
	{
	const char * name;
	size_t maxMsgs;
	size_t maxMsgLength;
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
	size_t * pInfoSize;
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
	size_t * pArgSize;
	};

struct taskDelayScArgs 
	{
	_Vx_ticks_t ticks;
	};

struct rtpSpawnScArgs 
	{
	const char * rtpFileName;
	const char ** argv;
	const char ** envp;
	int priority;
	UINT32 uStackSizePad;
	size_t uStackSize;
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
	int sigCode;
	};

struct _timer_openScArgs 
	{
	const char * name;
	int mode;
	UINT32 clockIdPad;
	clockid_t clockId;
	struct sigevent * evp;
	void * context;
	};

struct timerCtlScArgs 
	{
	TIMER_CTL_CMD cmdCode;
	UINT32 timerHandlePad;
	OBJ_HANDLE timerHandle;
	UINT32 pArgsPad;
	void * pArgs;
	size_t pArgSize;
	};

struct pxOpenScArgs 
	{
	PX_OBJ_TYPE type;
	UINT32 namePad;
	const char * name;
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
	size_t * pArgSize;
	};

struct pxMqReceiveScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pMsgPad;
	char * pMsg;
	size_t msgLen;
	unsigned int * pMsgPrio;
	PX_WAIT_OPTION waitOption;
	UINT32 time_outPad;
	const struct timespec * time_out;
	};

struct pxMqSendScArgs 
	{
	OBJ_HANDLE handle;
	UINT32 pMsgPad;
	const char * pMsg;
	size_t msgLen;
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
	size_t nMessages;
	size_t nBytes;
	};

struct pipeDevDeleteScArgs 
	{
	const char * name;
	BOOL force;
	};

struct _sdCreateScArgs 
	{
	char * name;
	int options;
	UINT32 sizePad;
	size_t size;
	off64_t physAddress;
	MMU_ATTR attr;
	UINT32 pVirtAddressPad;
	void ** pVirtAddress;
	};

struct _sdOpenScArgs 
	{
	char * name;
	int options;
	UINT32 modePad;
	int mode;
	UINT32 sizePad;
	size_t size;
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
	int lineNumber;
	UINT32 regsetPad;
	REG_SET *regset;
	void *addr;
	const char *msg;
	};

struct wvEventScArgs 
	{
	int eventId;
	UINT32 pDataPad;
	const char * pData;
	unsigned int dataSize;
	};

struct rtpVarAddScArgs 
	{
	void ** pVar;
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
	size_t len;
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
	CLOCK_CTL_CMD cmdCode;
	UINT32 pArgStructPad;
	void * pArgStruct;
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
	unsigned int dataSize;
	};

#endif	/* _ASMLANGUAGE */
