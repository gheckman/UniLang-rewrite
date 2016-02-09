/*

  RTA database support library

*/

#include "time.h"

#ifndef PF_EXPORT
#define PF_EXPORT extern
#endif

extern void (*pf_FaultFunc)(char *);

struct EnumRecord;

typedef struct EnumRecord * pf_Enum;
typedef long pf_File;
typedef long pf_Build;
typedef long pf_Run;
typedef long pf_Area;

/* Area types */
#define PFA_FUNCTION	1
#define PFA_BLOCK	2
#define PFA_LINE	3
#define PFA_FILE	4

/* Init and exit ------------------------------------------------------*/

PF_EXPORT void pf_OpenDatabase(char * root);
PF_EXPORT void pf_OpenDatabaseNet(char * host, int port);
PF_EXPORT void pf_OpenDatabaseSocket(int socket);
PF_EXPORT void pf_FlushDatabase(void);
PF_EXPORT void pf_CloseDatabase(void);
PF_EXPORT int  pf_IsDatabaseOpen(void);

/* Enumeration --------------------------------------------------------*/

PF_EXPORT long pf_Next(pf_Enum);
/* returns next object from enumeration */

PF_EXPORT int pf_HasMore(pf_Enum);
/* checks if enumeration has more objects */

PF_EXPORT void pf_Done(pf_Enum);
/* delete enumeration object */


/* Builds -------------------------------------------------------------*/

PF_EXPORT pf_Build pf_NewBuild(pf_File);
/* creates new build record for given executable file */

PF_EXPORT pf_Enum pf_GetBuilds(void);
/* returns builds which are currently in database */

PF_EXPORT char * pf_GetBuildName(pf_Build);
/* returns build name */

PF_EXPORT time_t pf_GetBuildTime(pf_Build);
/* returns build time */

PF_EXPORT pf_File pf_GetExeFile(pf_Build);
/* returns executable file for given build */

PF_EXPORT void pf_DelBuild(pf_Build);
/* deletes all build information from database */

/* Files --------------------------------------------------------------*/

PF_EXPORT pf_Enum pf_GetFiles(void);
/* returns files which are currently in database */

PF_EXPORT pf_Enum pf_GetSources(pf_File);
/* return source files for given file */

PF_EXPORT pf_File pf_NewFile(char * FilePath);
/* stores file information in database */

PF_EXPORT void pf_DelFile(pf_File);
/* deletes file information from database */

PF_EXPORT void pf_RenameFile(pf_File, char *);
/* renames file */

PF_EXPORT void pf_PutFileDependance(pf_File fr, pf_File to);
/* marks file 'fr' as source for file 'to' */

PF_EXPORT time_t pf_GetFileTime(pf_File f);

PF_EXPORT char * pf_GetFilePath(pf_File f);
/* returns file path */

/* Runs ---------------------------------------------------------------*/

PF_EXPORT pf_Enum pf_GetRuns(pf_Build);
/* returns runs available for given build */

PF_EXPORT pf_Run pf_NewRun(pf_Build);
/* create storage for new run information */

PF_EXPORT void pf_DelRun(pf_Run);
/* delete all information about given run from database */

PF_EXPORT long pf_GetRunTime(pf_Run);
/* return total run time */

PF_EXPORT long pf_GetRunTimeUnit(pf_Run);
/* return total run time */

PF_EXPORT void pf_SetRunTime(pf_Run, long, long);
/* store total run time */

PF_EXPORT char * pf_GetRunName(pf_Run);
/* return run name */

PF_EXPORT void pf_SetRunName(pf_Run, char *);
/* store run name */

/* Areas --------------------------------------------------------------*/

/* Area is subset of machine instructions and corresponding source code.
   Area is represented by sequence of PC ranges and source code ranges.
*/

PF_EXPORT pf_Enum pf_GetAreas(pf_Build, int type);
/* returns areas for given build */

PF_EXPORT pf_Enum pf_GetAreasInFile(pf_Build, int type, char * file);
/* returns areas for given build and object file */

PF_EXPORT pf_Enum pf_GetLineAreas(pf_Build b, int type, int file, int line);
/* returns areas for given build and line number */

PF_EXPORT pf_Enum pf_GetPcAreas(pf_Build, int type, unsigned long pc0, unsigned long pc1);
/* returns areas for given build and pc range */

PF_EXPORT pf_Area pf_NewArea(pf_Build, char * name, int type);
/* creates new empty area */

PF_EXPORT void pf_DelArea(pf_Build b, pf_Area area);
/* deletes an area */

PF_EXPORT void pf_GetAreaName(pf_Build, pf_Area, char ** name);
/* returns area name and type */

PF_EXPORT void pf_SetAreaName(pf_Build, pf_Area, char * name);
/*  */

PF_EXPORT void pf_GetAreaMangledName(pf_Build, pf_Area, char ** name);
/* return mangled area name */

PF_EXPORT void pf_SetStkUse(pf_Build b, pf_Area a, unsigned long stk);
/* set function area stack usage, default is 0 */

PF_EXPORT unsigned long pf_GetStkUse(pf_Build b, pf_Area a);
/* returns function area stack usage */

PF_EXPORT void pf_AppPcRange(pf_Build, pf_Area, unsigned long pc0, unsigned long pc1);
/* appends PC range to area */

PF_EXPORT void pf_AppSrcRange(pf_Build, pf_Area, pf_File,
					int line0, int col0,
					int line1, int col1);
/* appends source code range to area */

PF_EXPORT int pf_GetPcRanges(pf_Build b, pf_Area a);
/* returns id of first PC range in given area */

PF_EXPORT int pf_GetNextPcRange(int no, int * pc0, int * pc1);
/* gets co-ordinates of current PC range and returns id of next PC range */

PF_EXPORT int pf_GetSrcRanges(pf_Build, pf_Area);
/* returns id of first source range in geven area */
 
PF_EXPORT int pf_GetNextSrcRange(int no, pf_File *,
					int * line0, int * col0,
					int * line1, int * col1);
/* gets co-ordinates of current source range and returns id of next source range */

PF_EXPORT int pf_GetAreaSize(pf_Build b, pf_Area a);
/* returns area size in bytes */

/* Profiler data ------------------------------------------------------*/

#define pf_NullArea (-1)

PF_EXPORT void pf_SetHitCount(pf_Run, pf_Area, pf_Area, int);
/* set hit count (coverage) for given area and run */

PF_EXPORT void pf_SetAreaTime(pf_Run, pf_Area, pf_Area, int);
/* set time count for given area and run */

PF_EXPORT void pf_SetTotalTime(pf_Run, pf_Area, pf_Area, int);
/* set time count for given area and all functions called from it */

PF_EXPORT int pf_GetHitCount(pf_Run, pf_Area, pf_Area);
/* returns hit count (coverage) for given area and run */

PF_EXPORT int pf_GetAreaTime(pf_Run, pf_Area, pf_Area);
/* returns time count for given area and run */

PF_EXPORT int pf_GetTotalTime(pf_Run, pf_Area, pf_Area);
/* returns time count for given area and all functions called from it */

PF_EXPORT pf_Enum pf_GetChildren(pf_Run r, pf_Area a);
PF_EXPORT pf_Enum pf_GetParents(pf_Run rn, pf_Area a);


/* Low level I/O  -----------------------------------------------------*/

PF_EXPORT void chnl_send_byte(int chnl, int b);
PF_EXPORT void chnl_send_str(int chnl, char * buf);
PF_EXPORT int chnl_recv_bytes(int chnl, char * buf, int len);
PF_EXPORT void pf_send_byte(int n);
PF_EXPORT void pf_send_str(char *s);
PF_EXPORT void pf_send_int(int n);
PF_EXPORT int  pf_recv_int(void);
PF_EXPORT void pf_OutShort(int n);
PF_EXPORT void pf_OutStr(char * str);
PF_EXPORT int  pf_OutEvent(char * cmd, char * arg);
PF_EXPORT void pf_OutFlush(void);
PF_EXPORT int cmd_read_ch(char * ch);
PF_EXPORT int cmd_read_int(int * n);
PF_EXPORT int cmd_read_long(unsigned long * n);
PF_EXPORT int cmd_read_str(char ** str);
PF_EXPORT void cmd_write_ch(int ch);
PF_EXPORT void cmd_write_int(int n);
PF_EXPORT void cmd_write_long(unsigned long n);
PF_EXPORT void cmd_write_str(const char * str);

PF_EXPORT void pf_LogText(char * fmt, ...);

/* Low level File I/O -------------------------------------------------*/

PF_EXPORT void pf_SetLocalIO(int n);
PF_EXPORT int  pf_FileOpen(char * fnm, int m, int s);
PF_EXPORT int  pf_FileClose(int f);
PF_EXPORT int  pf_FileRead(int f, void * buf, unsigned int sz);
PF_EXPORT long pf_FileSeek(int f, long offs, int mode);
