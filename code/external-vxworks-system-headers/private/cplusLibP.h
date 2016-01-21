/* private/cplusLibP.h - VxWorks C++ support */

/* 
 * Copyright (c) 1992-1993, 1998, 2001, 2003-2005, 2009-2010, 2013 
 * Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02m,04nov13,mcm  Fix for static analysis issue 
02l,08apr10,jpb  Replaced funcBindP.h with logLib.h.
02k,14oct09,fan  updated for LP64 data model
02j,06may09,jpb  Updated _func_logMsg() arguments for LP64 support.
02i,05sep05,v_r  Moved loader-specific includes to
                 share/include/private/cplusLoadP.h and shared C++ strategy
                 and Xtors routines definitions in
                 share/include/private/cplusXtorsP.h
02h,18sep04,jn   Move toward shared code on host and target
02g,01sep04,bpn  Added cplusMangledSymGet() prototype.
02f,18aug04,bpn  Added new definitions.
02e,04mar04,bpn  Added cplusUserAsk() prototype.
02d,09apr03,sn   define CPLUS_DEMANGLER_MODE(S) in terms of DEMANGLER_MODE
02c,30oct01,sn   fixed syntax error
02b,24jul01,r_s  changed code to be ANSI compatible so that it compiles with
                 diab. made asm macro changes for diab
02a,10apr98,sn   added decls for cplusDemanglerInit & cplusDemangleFunc
01j,31oct93,srh  added cplusNewHdlMutex
01i,25apr93,srh  added non-ANSI declaration for cplusUnloadFixup...
01h,25apr93,srh  added declaration for cplusUnloadFixup.
01g,25apr93,srh  fixed a typo which was introduced during 01f
01f,24apr93,srh  removed extraneous comma from CPLUS_XTOR_STRATEGIES to
		 please certain compilers.
01e,23apr93,srh  added declarations for cplusLibMinInit
01d,31jan93,srh  renamed from cplusLib.h, coalesced other cplusLib hdrs
01c,22sep92,rrr  added support for c++
01b,03aug92,ajm  corrected non __STDC__ define of cplusDemangle
01a,30jul92,srh  written
*/

#ifndef __INCcplusLibPh
#define __INCcplusLibPh

#include <vxWorks.h>
#include <hashLib.h>
#include <limits.h>
#include <lstLib.h>
#include <moduleLib.h>
#include <semLib.h>
#include <symbol.h>
#include <symLib.h>
#include <logLib.h>		/* _func_logMsg */
#include <sysSymTbl.h>
#include <demanglerTypes.h>
#include <private/cplusXtorsP.h>

/* type declarations */

typedef enum
    {
    OFF		= DMGL_MODE_OFF,
    TERSE	= DMGL_MODE_TERSE,
    COMPLETE	= DMGL_MODE_COMPLETE
    } CPLUS_DEMANGLER_MODES;

typedef char * (*CPLUS_DEM_FUNC_PTR) (char *, char *, size_t);
typedef char * (*CPLUS_DEM_FUNC2_PTR) (const char *, DEMANGLER_STYLE,
				       DEMANGLER_MODE);
typedef DEMANGLER_RESULT (*CPLUS_DEM_BUFF_FUNC_PTR) (char *, char *,
						     size_t *,
						     DEMANGLER_MODE, char **);

/* C++-only declarations */

#ifdef __cplusplus

/* type declarations */

class RBString_T
    {
public:
    		  RBString_T ();	     // create an empty s
    		  RBString_T (RBString_T &); // create a copy of another
					     // RBString_T
    		  RBString_T (const char *); // create an RBString_T from
  					     // a C string
    void	  clear ();		     // reinitialize this RBString_T
    char	* extractCString (char *, size_t); // extract C string

    RBString_T	& operator =  (RBString_T &);
  
    BOOL 	  operator == (RBString_T &) const;
    BOOL 	  operator != (RBString_T &) const;

    size_t	  length () const	  // return number of characters,
		    { return nChars; }	  // not counting NUL.

    RBString_T	& append (RBString_T &);  // append RBString_T contents
    RBString_T	& append (const char *,	  // append C string contents
			  size_t len = INT_MAX);
    RBString_T  & append (char);	  // append character

    RBString_T	& prepend (RBString_T &); // prepend RBString_T contents
    RBString_T	& prepend (const char *,  // prepend C string contents
			   size_t len = INT_MAX);
    RBString_T	& prepend (char);	  // prepend character

protected:
    char	  appendChar (char);      // append a character
    char	  prependChar (char);	  // prepend a character
  
protected:
    char	  data [ MAX_SYS_SYM_LEN ]; // data
    char	* head;			    // pointer to first character
					    // in string
    char	* tail;			    // pointer to delimiting
					    // NUL character
    size_t		  nChars;		    // number of characters currently
					    // in string, not counting NUL

private:
    friend class RBStringIterator_T;
    };

class RBStringIterator_T
    {
public:
    		RBStringIterator_T (const RBString_T &); // initialize a
  							 // new iterator
    char	nextChar ();				 // fetch next char.

protected:
    const RBString_T	* theRBString;
    const char 		* nc;
    };

struct ArrayDesc_T
    {
    // functions
    ArrayDesc_T (void *pObject, size_t nElems);

    // data
    HASH_NODE	  hashNode;
    void 	* pObject;
    size_t		  nElems;
    };

class ArrayStore_T
    {
 public:
    	   	  ArrayStore_T ();
		 ~ArrayStore_T ();
    void 	  insert (void * pObject, size_t nElems);
    ssize_t  	  fetch  (void *pObject);
 private:
    HASH_ID	  hashId;
    SEM_ID	  mutexSem;
    };

class Demangle_T
    {
 public:
    Demangle_T (const char *);

    char	* extractDemangled (char * buf, size_t length = MAX_SYS_SYM_LEN);
    BOOL	  isDemangled ();
  
 private:
    BOOL	  scanArg (RBString_T * shadow = 0, RBString_T * retType = 0);
    BOOL	  scanArgs (RBString_T * shadow = 0, RBString_T * retType = 0);
    BOOL	  scanCastOperator ();
    BOOL	  scanClassName (RBString_T * shadow = 0);
    BOOL	  scanCtorDtor ();
    BOOL	  scanFunctionName ();
    BOOL	  scanNName (RBString_T * shadow = 0);
    BOOL	  scanSimpleFunctionName ();
    BOOL	  scanSpecialFunctionName ();
    BOOL          scanSimpleOperator ();
    BOOL	  demangle (const char *mangledName);

    Demangle_T ()					{}
    Demangle_T (const Demangle_T &)			{}
    void	  operator = (const Demangle_T &)	{}

    const char	* theMangledName;
    const char	* currentPosition;
    RBString_T	  workingString;
    BOOL	  demanglingSucceeded;

    enum DeclMod_T
	{
	dm_unsigned	= 0x0001,
	dm_const	= 0x0002,
	dm_volatile	= 0x0004,
	dm_signed	= 0x0008,
	dm_pointer	= 0x0010,
	dm_reference	= 0x0020,
	dm_array	= 0x0040,
	dm_function	= 0x0080,
	dm_ptrToMember  = 0x0100
	};

    class Declaration_T
        {
    public:
	Declaration_T ();
	Declaration_T (const Declaration_T &);
	Declaration_T	& operator =  (const Declaration_T &);
	Declaration_T	& operator += (const DeclMod_T);
        Declaration_T	& operator -= (const DeclMod_T);
			  
	BOOL		  is (const DeclMod_T) const;
			  
    private:
	long		  contents;
	};
    };

/* inline definitions */

#ifdef __cplusplus
extern "C" {
#endif

// cplusLogMsg

#ifdef __cplusplus
}
#endif

inline void cplusLogMsg (char *fmt, int arg1, int arg2, int arg3,
			 int arg4, int arg5, int arg6)
    {
    if (_func_logMsg != 0)
	{
	(* _func_logMsg) (fmt, (_Vx_usr_arg_t) arg1, (_Vx_usr_arg_t) arg2, 
                          (_Vx_usr_arg_t) arg3, (_Vx_usr_arg_t) arg4, 
                          (_Vx_usr_arg_t) arg5, (_Vx_usr_arg_t) arg6);
	}
    }

// ArrayDesc_T :: ArrayDesc_T
//
inline ArrayDesc_T :: ArrayDesc_T (void *pObject, size_t nElems)
    {
    this->pObject = pObject;
    this->nElems = nElems;
    this->hashNode.next = NULL;
    }

#endif				/* __cplusplus (C++-only declarations) */

/* data declarations */

extern CPLUS_XTOR_STRATEGIES cplusXtorStrategy;
extern SEM_ID                cplusNewHdlMutex;

/* function declarations, C linkage */

#ifdef __cplusplus
extern "C" {
#endif

extern CPLUS_DEM_FUNC_PTR	cplusDemangleFunc;
extern CPLUS_DEM_FUNC2_PTR	cplusDemangle2Func;
extern CPLUS_DEM_BUFF_FUNC_PTR	cplusDemangleToBufferFunc;

extern DEMANGLER_STYLE		cplusDemanglerStyle;
extern CPLUS_DEMANGLER_MODES	cplusDemanglerMode;

extern void	cplusArraysInit (void);
extern void	cplusDemanglerInit (void);
extern int	cplusUserAsk (LIST * pSymList);
extern UINT	cplusMatchMangledListGet (SYMTAB_ID symTab, const char * string,
					  LIST * pSymList);
extern BOOL	cplusMatchMangled (SYMTAB_ID symTab, char *string,
				   SYM_TYPE *pType, void** pValue);
extern STATUS	cplusMangledSymGet (SYMTAB_ID symTab, char * string,
				    SYM_TYPE * pType, void** pValue,
				    BOOL * pSymbolList);
extern char *	cplusDemangle (char *source, char *dest, size_t n);
extern char *	cplusDemangle2 (const char * mangledSymbol,
				DEMANGLER_STYLE style,
				DEMANGLER_MODE mode);
extern DEMANGLER_RESULT	cplusDemangleToBuffer (char * source,
					       char * buffer,
					       size_t * pBufferSize,
					       DEMANGLER_MODE mode,
					       char ** pResult);
extern BOOL	cplusMangledSymCheck (const char * symbol);
extern STATUS	cplusLibInit (void);
extern STATUS	cplusLibMinInit (void);

extern void     cplusDemanglerStyleInit (void);

extern void	cplusCtorsLink (void);
extern void	cplusDtorsLink (void);
extern void	cplusCallNewHandler(void);
extern BOOL	cplusNewHandlerExists(void);
extern void	cplusTerminate(void);
extern char	* _cplusDemangle
	(
	char *  source,     /* mangled name */
	char *  dest,       /* buffer for demangled copy */
	size_t          n           /* maximum length of copy */
	);

#ifdef __cplusplus
}
#endif

#endif /* __INCcplusLibPh */
