/* ----------------------------------------------------------------------
 * fstream.inl -- File stream I/O inlines
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920722	aem	initial
 */

#ifndef NO_INLINE
#  define IOS_INLINE inline
#else
#  define IOS_INLINE
#endif


/* Return true if filebuf is opened
 * ---------------------------------------------------------------------- */
IOS_INLINE int filebuf::is_open() {
    return opened;
}


/* Return current file descriptior
 * ---------------------------------------------------------------------- */
IOS_INLINE int filebuf::fd() {
    return xfd;
}


/* Default constructor -- just call ios::init()
 * ---------------------------------------------------------------------- */
IOS_INLINE fstreambase::fstreambase() {
    init(&buf);
}


/* Open file named name, with open mode m and protection prot
 * ---------------------------------------------------------------------- */
IOS_INLINE void fstreambase::open(const char* name, int m, int prot) {
    if ( buf.open(name, m, prot) == 0 )
        setstate(ios::failbit);
}


/* Return true if corresponding buffer is open
 * ---------------------------------------------------------------------- */
IOS_INLINE int fstreambase::is_open() {
    return rdbuf()->is_open();
}


/* Attach to filedescriptor fd
 * ---------------------------------------------------------------------- */
IOS_INLINE void fstreambase::attach(int fd) {
    if ( buf.attach(fd) == 0 ) setstate(ios::failbit);
}


/* Open file constructor. Mode and protection are given
 * ---------------------------------------------------------------------- */
IOS_INLINE fstreambase::fstreambase(const char* name, int m, int prot) {
    init(&buf);
    open(name, m, prot);
}


/* Offer buffer to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE void fstreambase::setbuf(char* s, int sz) {
    if ( buf.setbuf(s, sz) == 0 ) setstate(ios::failbit);
}


/* Attach to filedescriptor constructor
 * ---------------------------------------------------------------------- */
IOS_INLINE fstreambase::fstreambase(int fd) {
    init(&buf);
    attach(fd);
}


/* Attach to fildescriptor and offer buffer with length len constructor
 * ---------------------------------------------------------------------- */
IOS_INLINE fstreambase::fstreambase(int fd, char* bp, int len) {
    init(&buf);
    setbuf(bp, len);
    attach(fd);
}


/* Close (normally performed by destructor)
 * ---------------------------------------------------------------------- */
IOS_INLINE void fstreambase::close() {
    if ( buf.close() == 0 ) setstate(ios::failbit);
}


/* Get buffer class instance
 * ---------------------------------------------------------------------- */
IOS_INLINE filebuf* fstreambase::rdbuf() {
    return &buf;
}


/* Create unopened ifstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ifstream::ifstream() : fstreambase() {
}


/* Make opened ifstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ifstream::ifstream(const char* name, int m, int prot)
    : fstreambase(name, m|ios::in, prot) {
}


/* Make attached ifstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ifstream::ifstream(int fd) : fstreambase(fd) {
}


/* Make attached ifstream and offer buffer
 * ---------------------------------------------------------------------- */
IOS_INLINE ifstream::ifstream(int fd, char* s, int len)
    : fstreambase(fd, s, len) {
}


/* Get buffer of stream
 * ---------------------------------------------------------------------- */
IOS_INLINE filebuf* ifstream::rdbuf() {
    return fstreambase::rdbuf();
}


/* Open named file
 * ---------------------------------------------------------------------- */
IOS_INLINE void ifstream::open(const char* name, int m, int prot) {
    fstreambase::open(name, m|ios::in, prot);
}


/* Make unopened ofstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ofstream::ofstream() : fstreambase() {
}


/* Make opened ofstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ofstream::ofstream(const char* name, int m, int prot)
    : fstreambase(name, m|ios::out, prot) {
}


/* Make attached ofstream
 * ---------------------------------------------------------------------- */
IOS_INLINE ofstream::ofstream(int fd) : fstreambase(fd) {
}


/* Make attached ofstream and offer buffer
 * ---------------------------------------------------------------------- */
IOS_INLINE ofstream::ofstream(int fd, char* s, int len)
    : fstreambase(fd, s, len) {
}


/* Get stream buffer
 * ---------------------------------------------------------------------- */
IOS_INLINE filebuf* ofstream::rdbuf() {
    return fstreambase::rdbuf();
}


/* Open named file
 * ---------------------------------------------------------------------- */
IOS_INLINE void ofstream::open(const char* name, int m, int prot) {
    fstreambase::open(name, m|ios::out, prot);
}


/* Make unopened fstream
 * ---------------------------------------------------------------------- */
IOS_INLINE fstream::fstream() : fstreambase() {
}


/* Make opened fstream
 * ---------------------------------------------------------------------- */
IOS_INLINE fstream::fstream(const char* name, int m, int prot)
    : fstreambase(name, m|0, prot) {
}


/* Make attached fstream
 * ---------------------------------------------------------------------- */
IOS_INLINE fstream::fstream(int fd) : fstreambase(fd) {
}


/* Make attached fstream and offer buffer
 * ---------------------------------------------------------------------- */
IOS_INLINE fstream::fstream(int fd, char* s, int len) : fstreambase(fd, s, len) {
}


/* Get stream buffer
 * ---------------------------------------------------------------------- */
IOS_INLINE filebuf* fstream::rdbuf() {
    return fstreambase::rdbuf();
}


/* Open named file
 * ---------------------------------------------------------------------- */
IOS_INLINE void fstream::open(const char* name, int m, int prot) {
    fstreambase::open(name, m, prot);
}
