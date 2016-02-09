/* ----------------------------------------------------------------------
 * iostream.inl -- Stream I/O base inlines
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920610	aem	initial
 */

#ifdef NO_INLINE
#  define IOS_INLINE
#else
#  define IOS_INLINE inline
#endif


/* Make sure a char c cannot equal EOF
 * ---------------------------------------------------------------------- */
IOS_INLINE int zapeof(char c) {
    return (unsigned char)c;
}


/* ======================================================================
 * Implementation of inlined members
 * ======================================================================
 */

/* Inlines of class ios
 * ====================================================================== */


/* Constructor of class ios
 * ---------------------------------------------------------------------- */
IOS_INLINE ios::ios(streambuf* s) {
    init(s);		// All initialization is isolated to ios::init()
}


/* Constructor of class ios -- Does no initialization
 * ---------------------------------------------------------------------- */
IOS_INLINE ios::ios() {
    assign_private = state;
    state = hardfail;
}


/* Return stream formatting flags
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::flags() {
    return x_flags;
}


/* Set formatting flags to f and return old flag settings
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::flags( long f ) {
    long oldf = x_flags;
    x_flags = f;
    osfx_special = f & (unitbuf|stdio);

    return oldf;
}


/* Set bits field of the formatting flags to setbits. Return old setting
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::setf( long setbits, long field ) {
    long oldf = x_flags;
    x_flags = (x_flags & ~field) | (setbits & field);
    osfx_special = x_flags & (unitbuf|stdio);

    return oldf;
}


/* Set the bits setbit of the formatting flags, leave the other unaltered
 * Return old setting
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::setf( long setbits ) {
    long oldf = x_flags;
    x_flags |= setbits;
    osfx_special = x_flags & (unitbuf|stdio);

    return oldf;
}


/* Clear bits clrbits of the formatting flags, leave the other unchanged
 * Return old flag setting
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::unsetf( long clrbits ) {
    long oldf = x_flags;
    x_flags &= ~clrbits;
    osfx_special = x_flags & (unitbuf|stdio);

    return oldf;
}


/* Return the field width setting
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::width() {
    return x_width;
}


/* Set new field width, return old width setting
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::width( int neww ) {
    int oldw = x_width;
    x_width = neww;

    return oldw;
}


/* Set fill char
 * ---------------------------------------------------------------------- */
IOS_INLINE char ios::fill(char newfill) {
    int oldc = x_fill;
    x_fill = newfill;

    return oldc;
}	


/* Get current fill character
 * ---------------------------------------------------------------------- */
IOS_INLINE char ios::fill() {
    return x_fill;
}


/* tie a stream to this ios instance
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream* ios::tie( ostream* s ) {
    ostream* oldtie = x_tie;
    x_tie = s;

    ospecial = (ospecial & ~ios::tied) | (x_tie?ios::tied:0);

    return oldtie;
}


/* Return the stream curretly tied to this ios instance
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream* ios::tie() {
    return x_tie;
}


/* Set precision, return old
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::precision( int n ) {
    int oldn = x_precision;
    x_precision = n;

    return oldn;
}


/* Return current precision
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::precision() {
    return x_precision;
}


/* Return stream state
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::rdstate() {
    return state;
}


/* Convert to void* -- so it can be compared to 0
 * ---------------------------------------------------------------------- */
IOS_INLINE ios::operator void*() {
    return ( state & (errorfield|eofbit)) ? 0 : this;
}	


/* Convert to boolean -- for use in conditionals
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::operator!() {
    return state & errorfield;
} 


/* True if at end of file
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::eof() {
    return state & eofbit;
}


/* True if some error has occured
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::fail() {
    return state & errorfield;
}


/* True if badbit is set
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::bad() {
    return state & badbit;
}


/* True if no error nor eof is set
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::good() {
    return state == goodbit;
}


/* Set stream status to i (hardfail bit is never cleared)
 * ---------------------------------------------------------------------- */
IOS_INLINE void ios::clear(int bits) {
   state = bits | (state & hardfail);
}


/* Return the associated stream
 * ---------------------------------------------------------------------- */
IOS_INLINE streambuf* ios::rdbuf() {
    return bp;
}


/* Return a reference to the i:th user allocated word
 * ---------------------------------------------------------------------- */
IOS_INLINE long& ios::iword(int i) {
    if ( i >= nuser ) chkalloc(i+1);

    return user_bits[i].ival;
}


/* Return a reference to the i:th user allocated word
 * ---------------------------------------------------------------------- */
IOS_INLINE void*& ios::pword(int i) {
    if ( i >= nuser ) chkalloc(i+1);

#ifdef MSDOS
    return (void*&)(user_bits[i].voidval);
#else
    return user_bits[i].voidval;
#endif
}


/* Allocate a new bit in x_flags
 * ---------------------------------------------------------------------- */
IOS_INLINE long ios::bitalloc() {
    long currbit = nextbit;

    nextbit <<= 1;
    return currbit;
}


/* Allocates a new user allocated status word
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::xalloc() {
    return nextidx++;
}


/* Set status bits b (leave others unchanged)
 * ---------------------------------------------------------------------- */
IOS_INLINE void ios::setstate( int b ) {
    state |= b;
}


/* Set skipflag to i (true or flase), return previous value
 * NOTE: Old! Do not use (it will disappear)! 
 * ---------------------------------------------------------------------- */
IOS_INLINE int ios::skip(int i) {
    return setf(i ? skipws : 0, skipws);
}


/* Inlined members of class streambuf
 * ====================================================================== */


/* Return first byte of reserve area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::base() {
    return res_base;
}


/* Return first byte of get area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::pbase() {
    return put_base;
}


/* Return first byte of put area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::pptr() {
    return put_ptr;
}


/* Return first byte after put area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::epptr() {
    return put_end;
}


/* Return first byte of get area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::gptr() {
    return get_ptr;
}


/* Return first byte after get area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::egptr() {
    return get_end;
}


/* Return lower bound for putback
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::eback() {
    return get_base;
}


/* Return first byte after reserve area
 * ---------------------------------------------------------------------- */
IOS_INLINE char* streambuf::ebuf() {
    return res_base+res_len;
}


/* Return size in bytes of reserve area
 * ---------------------------------------------------------------------- */
IOS_INLINE int streambuf::blen() {
    return res_len;
}


/* Set put area: base -- base and beginning, end -- first byte after area
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::setp(char* base, char* end) {
    put_base = put_ptr = base;
    put_end = end;
}


/* Set get area: back -- lower bound, base & end -- same as setp()
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::setg(char* back, char* base, char* end) {
    get_base = back;
    get_ptr = base;
    get_end = end;
}


/* Raw increment of pptr()
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::pbump(int incr) {
    put_ptr += incr;
}


/* Raw increment of gptr()
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::gbump(int incr) {
    get_ptr += incr;
}


/* Return buffering status
 * ---------------------------------------------------------------------- */
IOS_INLINE int streambuf::unbuffered() {
    return unbuffl;
}


/* Set buffering status
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::unbuffered(int f) {
    unbuffl = ( f != 0 );
}


/* Allocate reserve area, if needed. Returns 0 if not needed, 1 upon success
 * and EOF upon allocation failure.
 * ---------------------------------------------------------------------- */
IOS_INLINE int streambuf::allocate() {
    return ( unbuffl || res_base ) ? 0 : doallocate();
}


/* Seek to position in stream relative the beginning
 * ---------------------------------------------------------------------- */
IOS_INLINE streampos streambuf::seekpos(streampos pos, int mode ) {
    return seekoff(streamoff(pos), ios::beg, mode);
}


/* Return number of chars in the input buffer. Return 0 if unbuffered
 * ---------------------------------------------------------------------- */
IOS_INLINE int streambuf::in_avail() {
    return get_end - get_ptr;
}


/* Return number of chars in output buffer. Return 0 if unbuffered
 * ---------------------------------------------------------------------- */
IOS_INLINE int streambuf::out_waiting() {
    return put_ptr - put_base;
}


/* Move get pointer one step if possible
 * ---------------------------------------------------------------------- */
IOS_INLINE void streambuf::stossc() {
    if ( get_ptr++ > get_end ) underflow();
}


/* Set reserve area
 * ---------------------------------------------------------------------- */
IOS_INLINE streambuf* streambuf::setbuf(unsigned char* p, int len) {
    return setbuf( (char*) p, len);
}
IOS_INLINE streambuf* streambuf::setbuf(signed char* p, int len) {
    return setbuf( (char*) p, len);
}


/* Inlines for class istream
 * ====================================================================== */


/* Constructor & destructor -- class ios does the thing...
 * ---------------------------------------------------------------------- */


/* Make istream assosiated with sb
 * ---------------------------------------------------------------------- */
IOS_INLINE istream::istream(streambuf* sb) : ios(sb) {
}


/* Make unititialized istream
 * ---------------------------------------------------------------------- */
IOS_INLINE istream::istream() {
}


/* Return current stream position
 * ---------------------------------------------------------------------- */
IOS_INLINE streampos istream::tellg() {
    return rdbuf()->seekoff(streamoff(0), ios::cur, ios::in);
}


/* Maipulator hook
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::operator>>(istream& (*fnp)(istream&)) {
    return (*fnp)(*this);
}


/* Maipulator hook
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::operator>>(ios& (*fnp)(ios&)) {
    (*fnp)(*this);
    return *this;
}


/* Get string of unsigned/signed chars
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::operator>>(unsigned char* s) {
    return this->operator>>( (char*) s );
}
IOS_INLINE istream& istream::operator>>(signed char* s) {
    return this->operator>>( (char*) s );
}


/* Get an unsigned/signed char
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::operator>>(unsigned char& c) {
    return istream::operator>>((char&)c);
}
IOS_INLINE istream& istream::operator>>(signed char& c) {
    return istream::operator>>((char&)c);
}


/* Suffix function: Does nothing
 * ---------------------------------------------------------------------- */
IOS_INLINE void istream::isfx() {
    // NULL Contents
}


/* Get string
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::get(unsigned char* s, int n, char endc) {
    return get((char*)s, n, endc);
}
IOS_INLINE istream& istream::get(signed char* s, int n, char endc) {
    return get((char*)s, n, endc);
}


/* Get a single character
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::get(unsigned char& c) {
    return istream::get((char&)c);
}
IOS_INLINE istream& istream::get(signed char& c) {
    return istream::get((char&)c);
}


/* Read a byte block
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::read(unsigned char* ptr, int n) {
    return read((char*)ptr,n);
}
IOS_INLINE istream& istream::read(signed char* ptr, int n) {
    return read((char*)ptr,n);
}


/* Get string, delimeter exlusive
 * ---------------------------------------------------------------------- */
IOS_INLINE istream& istream::getline(unsigned char* s, int n, char endc) {
    return getline((char*)s, n, endc);
}
IOS_INLINE istream& istream::getline(signed char* s, int n, char endc) {
    return getline((char*)s, n, endc);
}


/* Return number of chars gotten by last unformatted operation
 * ---------------------------------------------------------------------- */
IOS_INLINE int istream::gcount() {
    return unf_count;
}


/* Sync with external representation
 * ---------------------------------------------------------------------- */
IOS_INLINE int istream::sync() {
    return rdbuf()->sync();
}


/* ======================================================================
 * inlines of class ostream
 * ====================================================================== */


/* Constructor: ostream assosiated w. sb
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream::ostream(streambuf* sb) : ios(sb) {
}


/* Make uninitialized ostream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream::ostream() {
}


/* Manipulator hooks
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(ostream& (*fnp)(ostream&)) {
    return (*fnp)(*this);
}
IOS_INLINE ostream& ostream::operator<<(ios& (*fnp)(ios&)) {
    (*fnp)(*this);
    return *this;
}


/* Output prefix function
 * ---------------------------------------------------------------------- */
IOS_INLINE int ostream::opfx() {
    return ospecial ? do_opfx() : 1;
}


/* Output suffix function
 * ---------------------------------------------------------------------- */
IOS_INLINE void ostream::osfx() {
    if ( osfx_special ) do_osfx();
}


/* Write out buffer to external representation
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::flush() {
    if ( rdbuf()->sync() == EOF ) {
	setstate(badbit);
    }
    return *this;
}


/* Change current position
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::seekp(streampos p) {
    return seekp(streamoff(p), ios::beg);
}


/* Write block to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::write(const unsigned char* s, int n) {
    return this->write( (char*)s, n );
}
IOS_INLINE ostream& ostream::write(const signed char* s, int n) {
    return this->write( (char*)s, n );
}


/* Put single byte on stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::put(unsigned char c) {
    return this->put((char)c);
}
IOS_INLINE ostream& ostream::put(signed char c) {
    return this->put((char)c);
}


/* Write char to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(unsigned char c) {
    this->operator<<( (char)c );
    return *this;
}
IOS_INLINE ostream& ostream::operator<<(signed char c) {
    this->operator<<( (char)c );
    return *this;
}


/* Write string to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(const unsigned char* s) {
    this->operator<<( (char*)s );
    return *this;
}
IOS_INLINE ostream& ostream::operator<<(const signed char* s) {
    this->operator<<( (char*)s );
    return *this;
}


/* Write unsigned integer to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(unsigned int i) {
    return this->operator<<((unsigned long)i);
}


/* Write long integer to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(int i) {
    return this->operator<<((long)i);
}


/* Write short integer to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(short i) {
    return this->operator<<((long)i);
}


/* Write unsigned short integer to stream
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream& ostream::operator<<(unsigned short i) {
    return this->operator<<((unsigned long)i);
}


/* Write float to stream
 * ---------------------------------------------------------------------- */
#if	defined(__EDG__) || !defined(__SINGLE_ONLY)
IOS_INLINE ostream& ostream::operator<<(float f) {
    return this->operator<<((double)f);
}
#endif


/* ======================================================================
 * inlines of class iostream
 * ====================================================================== */


/* Make unititialized iostream
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream::iostream() {
}


/* Make iostream assosiated w. sbp
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream::iostream(streambuf* sbp) {
    init(sbp); 
}


/* ======================================================================
 * inlines of class istream_withassign
 * ====================================================================== */


/* Make unititialized instance
 * ---------------------------------------------------------------------- */
IOS_INLINE istream_withassign::istream_withassign() {
    state = assign_private;	// Undo init done by ios::ios()
}


/* Assosiate stream with streambuf of is
 * ---------------------------------------------------------------------- */
IOS_INLINE istream_withassign& istream_withassign::operator=(istream& is) {
    init(is.rdbuf());
    return *this;
}


/* Assosiate stream w. sbp
 * ---------------------------------------------------------------------- */
IOS_INLINE istream_withassign& istream_withassign::operator=(streambuf* sbp) {
    init(sbp);
    return *this;
}


/* ======================================================================
 * inlines of class ostream_withassign
 * ====================================================================== */


/* Make uninitialized instance
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream_withassign::ostream_withassign() {
    state = assign_private;	// Undo init done bu ios::ios()
}


/* Make instance assosiated w. streambuf of os
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream_withassign& ostream_withassign::operator=(ostream& os) {
    init(os.rdbuf());
    return *this;
}


/* Make instance assosiated w. sbp
 * ---------------------------------------------------------------------- */
IOS_INLINE ostream_withassign& ostream_withassign::operator=(streambuf* sbp) {
    init(sbp);
    return *this;
}


/* ======================================================================
 * inlines of class iostream_withassign
 * ====================================================================== */


/* Make unititialized instance
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream_withassign::iostream_withassign() {
    state = assign_private;	// Undo init done by ios::ios()
}


/* Virtual destructor
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream_withassign::~iostream_withassign() {
}


/* Assosiate instance with streambuf of os
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream_withassign& iostream_withassign::operator=(ios& os) {
    init(os.rdbuf());
    return *this;
}


/* Assosiate instance w. sbp
 * ---------------------------------------------------------------------- */
IOS_INLINE iostream_withassign& iostream_withassign::operator=(streambuf* sbp) {
    init(sbp);
    return *this;
}
