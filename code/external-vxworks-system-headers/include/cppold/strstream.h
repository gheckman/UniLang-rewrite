/* ----------------------------------------------------------------------
 * stdiostream.h -- Stream I/O thru FILE pointers
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920725	aem	initial
 */

#ifndef __Istrstream
#define __Istrstream

#include <string.h>

#ifndef __Iiostream
#include <iostream.h>
#endif

/* 
 * NOTE: The markers have the following meaning:
 *  (1)	A non-AT&T feature, only avaible in D-C++.
 *  (2)	A undocumented AT&T feature, expected to change, do not use.
 *  (3) A old compability feature, do not use
 */

class strstreambase;

class strstreambuf : public streambuf {
    friend class strstreambase;
  public:
    // Constructors and destructor
    strstreambuf();
    strstreambuf(int i_sz);
    strstreambuf(void* (*a_fnp)(long), void (*f_fnp)(void*));
    strstreambuf(void* (*a_fnp)(long), void (*f_fnp)(void*), int i_sz);
    strstreambuf(char* s, int sz, char* put_start = 0);
    strstreambuf(unsigned char* s, int sz, unsigned char* put_start = 0);
  protected:
    strstreambuf(char* s, int sz, int mode);
				// (1) For ostrstream, strstream
  public:
    ~strstreambuf();

    // Other member functions
    void 	freeze(int n=1);// Disable buffer deletion
    char* 	str();		// Get ptr to buffer
    int		pcount();	// (2) Returns number of chars in buffer

    // Virtuals
    virtual int	doallocate();
    virtual int overflow(int c=EOF);
    virtual int underflow();
    virtual streambuf*
		setbuf(char* s, int len);
    virtual streampos
	seekoff(streamoff offs, ios::seek_dir dir,
		int mode = ios::in | ios::out);
  private:
    void	init(char* s, int sz, char* put_start);
    				// (2) Helper to the constructors
    void*	(*afp)(long);	// (2) Allocator function
    void	(*ffp)(void*);	// (2) Deallocator funtion
    int		ignore_oflow;	// (2) True -> no bounds checks
    int		frozen;		// (2) True iff resource area should be deleted
    int		extend_size;	// (1) Next size to allocate (0 == static mode)
};

class strstreambase : public virtual ios {
  protected:
    strstreambase(char* s, int len, char* put_start);
    strstreambase();
    ~strstreambase();
  protected:
    strstreambase(char* s, int len, int mode);
    				// (1) Used by ostrstream
  public:
    strstreambuf*	rdbuf();
  private:
    strstreambuf	buf;
};

class istrstream : public strstreambase, public istream {
  public:
    istrstream(char* s);
    istrstream(char* s, int sz);
    ~istrstream();
};

class ostrstream : public strstreambase, public ostream {
  public:
    ostrstream();
    ostrstream(char* s, int sz, int mode=ios::out);
    ~ostrstream();
    char* 	str();
    int 	pcount();
};

class strstream : public strstreambase, public iostream {
  public:
    strstream();
    strstream(char* s, int sz, int mode);
    ~strstream();
    char* 	str();
};

#ifndef NO_INLINE
#  include "strstrea.inl"
#endif


#endif /* __Istrstream */
