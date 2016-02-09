/* ----------------------------------------------------------------------
 * stdiostream.h -- Stream I/O thru FILE pointers
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920725	aem	initial
 */

#ifdef NO_INLINE
#  define INLINE
#else
#  define INLINE inline
#endif


/* INLINES */

INLINE strstreambuf::strstreambuf(char* s, int sz, char* put_start) {
    init(s, sz, put_start);
}

INLINE strstreambuf::strstreambuf(unsigned char* s, int sz,
				  unsigned char* put_start) {
    init((char*)s, sz, (char*)put_start);
}

INLINE strstreambuf::strstreambuf(char* s, int sz, int mode) {
    char* put_start = s;
    if ( mode & (ios::ate|ios::app) ) {
	put_start += strlen(s);
    }
    init(s, sz, put_start);
}

INLINE void strstreambuf::freeze(int n) {
    frozen = n;
}

INLINE char* strstreambuf::str() {
    frozen = 1;
    return base();
}

INLINE int strstreambuf::pcount() {
    return pptr() - base();
}

INLINE strstreambase::strstreambase(char* s, int len, char* put_start)
    : buf(s, len, put_start) {
    ios::init(&buf);
}

INLINE strstreambase::strstreambase() {
    ios::init(&buf);
}

INLINE strstreambase::strstreambase(char* s, int len, int mode)
    : buf(s, len, mode) {
    ios::init(&buf);
}

INLINE strstreambase::~strstreambase() { }

INLINE strstreambuf* strstreambase::rdbuf() {
    return &buf;
}

INLINE istrstream::istrstream(char* s) : strstreambase(s, 0, (char*)0) { }

INLINE istrstream::istrstream(char* s, int sz)
    : strstreambase(s, sz, (char*)0) { }

INLINE istrstream::~istrstream() { }

INLINE ostrstream::ostrstream() { }

INLINE ostrstream::ostrstream(char* s, int sz, int mode)
    : strstreambase(s, sz, mode) { }

INLINE ostrstream::~ostrstream() { }
    
INLINE char* ostrstream::str() {
    return strstreambase::rdbuf()->str();
}

INLINE int ostrstream::pcount() {
    return strstreambase::rdbuf()->pcount();
}

INLINE strstream::strstream() : strstreambase() { }

INLINE strstream::strstream(char* s, int sz, int mode)
    : strstreambase(s, sz, mode) {}

INLINE strstream::~strstream() {}

INLINE char* strstream::str() {
    return strstreambase::rdbuf()->str();
}
