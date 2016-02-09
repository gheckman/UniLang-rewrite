/* yfuns.h functions header */
#ifndef _YFUNS
#define _YFUNS
#include <stddef.h>
#if !defined(__RTP__) && defined(__DCC__)
#include "fnames.h"
#endif
_C_STD_BEGIN

 #if _USE_EXISTING_SYSTEM_NAMES

  #if defined(__BORLANDC__)
   #define _Environ	_environ

  #else /* defined(__BORLANDC__) */
   #define _Environ	environ
  #endif /* defined(__BORLANDC__) */

 #if _HAS_C9X

 #else /* _IS_C9X */
 #define _Exit	_exit
 #endif /* _IS_C9X */

#if !defined(__RTP__) && defined(__DCC__)
  #define _Close	CLOSE
  #define _Lseek	LSEEK
  #define _Read		READ
  #define _Write	WRITE
#else
  #define _Close	close
  #define _Lseek	lseek
  #define _Read		read
  #define _Write	write
#endif
 #endif /* _USE_EXISTING_SYSTEM_NAMES */

		/* process control */
#define _Envp	(*_Environ)

		/* stdio functions */
#define _Fclose(str)	_Close(_FD_NO(str))
#define _Fread(str, buf, cnt)	_Read(_FD_NO(str), buf, cnt)
#define _Fwrite(str, buf, cnt)	_Write(_FD_NO(str), buf, cnt)

		/* interface declarations */
_EXTERN_C
#if	defined(_NO_WINDRIVER_MODIFICATIONS)
extern const char **_Environ;
#elif	defined(__RTP__)
extern const char **_Environ;
#else	/* standalone diab */
extern char **_Environ;
#endif

_NO_RETURN(_Exit(int));

 #if defined(__APPLE__)
int _Close(int);
_Longlong _Lseek(int, _Longlong, int);
int _Read(int, void *, size_t);
int _Write(int, const void *, size_t);

 #else /* defined(__APPLE__) */
  #if defined(__RTP__)
long long _Lseek(int, _Longlong, int);
  #elif defined(__DCC__)
int _Lseek(int, int, int);
  #else
long _Lseek(int, long, int);
  #endif /* __RTP__  */
int _Close(int);
  #if !defined(__RTP__) && defined(__DCC__)
int _Read(int, void *, unsigned int);
int _Write(int, const void *, unsigned int);
  #else
int _Read(int, unsigned char *, int);
int _Write(int, const unsigned char *, int);
  #endif
 #endif /* defined(__APPLE__) */

_END_EXTERN_C
_C_STD_END
#endif /* _YFUNS */

/*
 * Copyright (c) 1992-2006 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.01:1278 */
