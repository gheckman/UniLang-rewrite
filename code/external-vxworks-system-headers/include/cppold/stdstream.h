/* ----------------------------------------------------------------------
 * stdiostream.h -- Stream I/O thru FILE pointers
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920725	aem	initial
 */

#ifndef __Istdiostream
#define __Istdiostream

#ifndef __Iiostream
#include <iostream.h>
#endif

#ifndef __Istdio
#include <stdio.h>
#endif

/* NOTE: The markers have the following meaning:
 *  (1)	A non-AT&T feature, only avaible in D-C++.
 *  (2)	A undocumented AT&T feature, expected to change, do not use.
 *  (3) A old compability feature, do not use
 */
    
class stdiobuf : public streambuf {
  public:
    // Constructor and destructor
    stdiobuf(FILE* xfp);
    virtual ~stdiobuf();
    // I/O operations
    virtual int underflow();
    virtual int overflow(int c = EOF);
    virtual int sync();
    virtual streampos seekoff(streamoff offs, ios::seek_dir dir,
			      int mode  = ios::in | ios::out);
    virtual int pbackfail(int c);
    // Status value related members
    FILE*	stdiofile();
    streambuf*	setbuf(char*,int);
  private:
    FILE*	fp;
    int 	last_op;
    char	buf[2];
};

class stdiostream : public iostream {
  public:
    stdiostream(FILE* fp);
    ~stdiostream();
  private:
    stdiobuf	buf;
};

#ifndef NO_INLINE
#  include "stdiostr.inl"
#endif


#endif /* __Istdiostream */
