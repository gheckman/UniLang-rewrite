/* ----------------------------------------------------------------------
 * iostream.h -- Stream I/O base header
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920610	aem	initial
 */

#ifndef __Iiostream
#define __Iiostream

/* NOTE: The markers have the following meaning:
 *  (1)	A non-AT&T feature, only avaible in D-C++.
 *  (2)	A undocumented AT&T feature, expected to change, do not use.
 *  (3) A old compability feature, do not use
 */

#ifndef EOF
#define EOF 		(-1)
#endif

#ifndef NULL
#define NULL		0
#endif


extern int zapeof(char);

/* Typedefs used for seeking
 * ---------------------------------------------------------------------- */
typedef long streampos;			// Position in a stream
typedef long streamoff;			// Offset in a stream

class streambuf;
class ostream;
class Iostream_init;

/* Class ios -- stream state container
 * ---------------------------------------------------------------------- */
class ios {
    friend Iostream_init;		// Needs access to delbuf
  public:
    // Local types and constants

    // Stream error state constants (state)
    enum io_state {
	goodbit		= 0x00,		// Everything's ok
	eofbit		= 0x01,		// End of file has been reached
	failbit		= 0x02,		// Set upon I/O failure
	badbit		= 0x04,		// Set upon invalid usage
	hardfail	= 0x80		// Unrecoverable error (cannot be
					// altered by user)
    };

    // Stream mode constants
    enum open_mode {
	in		= 0x1,		// Readable stream
	out		= 0x2,		// Writable stream
	ate		= 0x4,		// Seek to eof upon open
	app		= 0x8,		// Append only to stream
	trunc		= 0x10,		// Delete contents if already existing
	nocreate	= 0x20,		// Do not create file when opening it
	noreplace	= 0x40,		// Do not earase old file
	binary		= 0x80		// Ignored
    };

    // Stream seek direction constants
    enum seek_dir {
	beg		= 0,		// Seek from beginning
	cur		= 1,		// Seek from current position
	end		= 2		// Seek from end
    };

    // Stream formatting state constants (x_flags)
    enum {
	skipws		= 0x1,		// Skip whilespace
	left 		= 0x2,		// Adjustment:	left
	right		= 0x4,		//		right
	internal 	= 0x8,		// Pad inbetween to field width
	dec		= 0x10,		// Decimal mode
	oct		= 0x20,		// Octal mode
	hex		= 0x40,		// Hexadecimal mode
	showbase	= 0x80,		// Prepend base prefix
	showpoint	= 0x100,	// Show decimal point
	uppercase	= 0x200,	// Use uppercase hex chars
	showpos		= 0x400,	// Add unary plus to positive numebrs
	scientific 	= 0x800,	// Use scientific notation with floats
	fixed		= 0x1000,	// Use fixed notation w. floats
	unitbuf		= 0x2000,	// Flush after each write operation
	stdio		= 0x4000	// Flush files stdout & stderr on write
    };

    // Some constants collections
    static const long basefield;	// is: oct | dec | bin
    static const long adjustfield;	// is: left | right | internal
    static const long floatfield;	// is: scientific | fixed
    static const long errorfield;	// is: failbit | badbit | hardfail (1)

    // Constructors, initialization and destructor
    		ios(streambuf* sb);	// Create ios associated with sb
    virtual 	~ios();			// Destroy ios
  private:
    		ios(ios&);		// Error trap -- Never defined
    void 	operator=(ios&);	// Error trap -- Never defined
  protected:
    void 	init(streambuf*);	// Does real constructor work
    		ios();			// No initialization
  public:
    static void sync_with_stdio();	// Flush stdin, stdout, stderr

    // State fetchers and changers
  public:
    streambuf*	rdbuf();		// Return associated streambuf

    // Functionality to read/change format flags
    long 	flags();		// Return current format flag settings
    long 	flags(long bits);	// Set format flags, return old flags
    long 	setf(long bits, long mask);
					// Turn on setbits in field
    long 	setf(long bits);	// Turn on format flags bits
    long 	unsetf(long bits);	// Turn off format flags bits

    int		skip(int flag);		// (3) OLD! Do not use!
					//     Use setf() instead.
    // Read/set precision
    int 	precision(int prec);	// Set float precision to prec
    int 	precision();		// Get float precision

    // Read/set width
    int 	width();		// Get field width
    int 	width(int w);		// Set field width to w
    
    // Read/set fill char
    char 	fill(char c);		// Set fill (padding) char to c
    char 	fill();			// Get fill char

    // Read/set tied output stream
    ostream* 	tie(ostream* os);	// Tie a ostream to this stream
    ostream* 	tie();			// Get the tied ostream

    // Read/alter/set stream state
    int 	rdstate();		// Get stream state
    void 	setstate(int bits);	// Set the state bits
    void 	clear(int bits = 0);	// Set error state to bits

    		operator void*();	// NULL if failbit | badbit | hardbit
    int 	operator!();		// true if failbit | badbit | hardbit

    int 	eof();			// true if at end of file
    int 	fail();			// true if failbit | badbit | hardbit
    int 	bad();			// true if badbit
    int 	good();			// true if no eof or failure

    // Read/set user defined format flags
    long& 	iword(int i);		// Return the i:th user def word
    void*& 	pword(int i);		// Same as iword(int) but typecast

    // Allocation of more bits and user status words
    static long bitalloc();		// Allocate a new bit set word
    static int	xalloc();		// Return a previously unused index

  private:
    // Implementation of user status bits & words
    union ios_user_bits {		// A user status word should be big
	long	ival;			// enough to hold an long or void*
	void*	voidval;
    };
    static long nextbit;		// Next bit free bit map (not position)
    static long nextidx;		// Next free bitmap word index
    
    long	nuser;			// Number of allocated bitmap words
    union ios_user_bits* user_bits;	// Allocated bitmap
    void 	chkalloc(int i);	// Make sure i bitmap words are alloc.

  protected:
    // Flags for the *special members (2)
    enum {
	    skipping=01000,		// (2) ios::skipws is true
	    tied=02000			// (2) This stream is tied
    };
    streambuf* 	bp;			// (2) The associated streambuf
    int 	state;			// (2) State bits (io_state)
    long	ispecial;		// (2) Used by istream::ipfx(int)
    long	ospecial;		// (2) Used by ostream::opfx()
    long	isfx_special;		// (2) ??? Probably unused
    long	osfx_special;		// (2) Used by ostream::osfx()
    int 	delbuf;			// (2) Delete bp in destructor

    ostream* 	x_tie;			// (2) Tied stream
    long 	x_flags;		// (2) Formatting flags (skipws etc)
    short 	x_precision;		// (2) Float precision
    char 	x_fill;			// (2) Fill character
    short 	x_width;		// (2) Field width

    static void	(*stdioflush)();	// (2) Function that flushes stdio

    int		assign_private;		// (2) ???
};


/* Abstract base class for buffers
 * ---------------------------------------------------------------------- */
class streambuf {
    // Constructors and destructor (only to be used by derived classes)
  public:
		streambuf();		// Make a empty sequence streambuf
		streambuf(char* p, int len);
					// Make a empty streambuf with buffer p
		streambuf(char* p, int len,int count);
					// (3) Old version. Do not use!
    virtual	~streambuf();
  private:
		streambuf(streambuf&); 	// Error trap -- Calls abort
    void	operator=(streambuf&);	// Error trap -- Calls abort

    // Public interface
  public:
    virtual int	overflow(int c = EOF);	// Overflow handler
    virtual int	underflow();		// Fill buffer
    virtual int	pbackfail(int c);	// Try to putback more
    virtual int	sync();			// Write out buffers to source/sink
    virtual streampos
		seekoff(streamoff offs, ios::seek_dir dir,
 			int mode = ios::in | ios::out);
					// Seek with direction info
    virtual streampos
		seekpos(streampos pos, int mode = ios::in | ios::out) ;
					// Seek relative to the beginning

    int		in_avail();		// Number of bytes avaible in buffer
    int		out_waiting();		// Number of bytes to be written
    int		sgetc();		// Peek at current character
					// WARNING: Does not get the character
    int		snextc();		// Gets the next character
    int		sbumpc();		// Gets the current character
    void	stossc();		// Moves get pointer 1 step if possible
    int		sputbackc(char c);	// Unget char c
    int		sputc(int c);		// Put char at current position
    int		sputn(const char* s,int n);
					// Puts n chars from s
    int		sgetn(char* s,int n);	// Gets n chars to s
    virtual streambuf*			// Set reserve area to p
		setbuf(char* p, int len);
    streambuf*	setbuf(unsigned char* p, int len);
    streambuf*	setbuf(signed char* p, int len);

    streambuf*	setbuf(char* p, int len, int count);
					// (3) Old version. Do not use!

  protected:
    char*	base();			// Return first byte of reserve area
    char*	ebuf();			// Return first byte after reserve area
    int		blen();			// Size of reserve area

    char*	pbase();		// Return first byte of put area base
    char*	pptr();			// Return first byte of put area
    char*	epptr();		// Return first byte after put area

    char*	eback();		// Return lower bound for putback
    char*	gptr();			// Return first byte of get area
    char*	egptr();		// Return first byte after get area

    int		unbuffered();		// Return buffering status
    void	unbuffered(int f);	// Set buffering status

    void	setb(char* base, char* end, int f = 0 );
					// Set base(), blen() and alloc
    void	setp(char* base, char* end);
					// Set put area: pbase(),pptr(),epptr()
    void	setg(char* back, char* base, char* end);
					// Set get area: gback(),gptr(),egptr()

    int		allocate();		// Allocate reserve area, if needed
    virtual int doallocate();		// Allocate reserve area

    void	pbump(int incr);	// Raw increment of x_pptr
    void	gbump(int incr);	// Raw increment of x_gptr

    // Get/put block of bytes
    virtual int xsgetn(char* s, int n);
    virtual int xsputn(const char* s, int n);	

    // Helper functions
    void	dbp(int fd=1);		// Debug printout
  private:
    int		snextc_uf();		// Helper of snextc()

    // Member variables	
  private:
    short	delfl;			// Delete buffer flag (true==delete)
    short	unbuffl;		// Buffering flag (true==no buffering)
    char*	res_base;		// First byte of reserve area
    char*	put_base;		// First byte of put area base
    char*	put_ptr;		// First byte of put area
    char*	put_end;		// First byte after put area
    char*	get_ptr;		// First byte of get area
    char*	get_end;		// First byte after get area
    char*	get_base;		// Lower bound for putback
    int		res_len;		// Size in bytes of reserve area
};

class istream : virtual public ios {
    // Constructors & destructor
  public:
		istream(streambuf* sb);	// Associate streambuf with istream
		istream(streambuf*, int sk, ostream* t=0);
					// OLD! Do not use!
		istream(int size ,char*,int sk=1);
					// OLD! Do not use!
		istream(int fd,int sk=1, ostream* t=0);
					// OLD! Do not use!
  protected:
		istream();		// Error hook -- Never defined
  public:
    virtual	~istream();

  public:
    // Prefix & suffix handling
    int		ipfx(int need=0);	// Input prefix: flush if nessesary
    void	isfx();			// Input suffix: Unused

    // Seeks
    istream&	seekg(streampos pos);	// Seek to position pos
    istream&	seekg(streamoff off, ios::seek_dir dir);
					// Seek to position off from dir
    streampos	tellg();		// Get current position

    // Mainipulator hooks
    istream&	operator>>(istream& (*fnp)(istream&));
    istream&	operator>>(ios& (*fnp)(ios&));

    // Get string
    istream&	operator>>(char* s);
    istream&	operator>>(unsigned char* s);
    istream&	operator>>(signed char* s);

    // Get single character
    istream&	operator>>(char& c);
    istream&	operator>>(unsigned char& c);
    istream&	operator>>(signed char&);

    // Get various integers and floats
    istream&	operator>>(short& s);
    istream&	operator>>(int& i);
    istream&	operator>>(long& l);
    istream&	operator>>(unsigned short& s);
    istream&	operator>>(unsigned int& i);
    istream&	operator>>(unsigned long& l);
    istream&	operator>>(float& f);
#if	defined(__EDG__) || !defined(__SINGLE_ONLY)
    istream&	operator>>(double& d);
#endif

    // Copy characters from stream
    istream&	operator>>(streambuf* sbp);

    // Get array of bytes
    istream&	get(char* s, int n, char endc='\n');
    istream&	get(unsigned char* s,int n, char endc='\n');
    istream&	get(signed char* s,int n, char endc='\n');

    // Get array (and leave endc ungotten)
    istream&	getline(char* s, int n, char endc='\n');
    istream&	getline(unsigned char* s, int n, char endc='\n');
    istream&	getline(signed char* s, int n, char endc='\n');

    istream&	get(streambuf& sb, char endc ='\n');
					// Store chars in sb
    // Get a single char
    istream&	get(char& c);
    istream&	get(unsigned char& c);
    istream&	get(signed char& c);
    int		get();			// Get a single char or EOF
    int		peek();			// Peek at next char (could be EOF)
    istream&	ignore(int n=1,int endc=EOF);
					// Throw away n chars
    istream&	read(char* s,int n);	// Read n characters
    istream&	read(unsigned char* s,int n);
    istream&	read(signed char* s,int n);
					// Read n characters

    int		gcount();		// Return # of chars read by last
					// unformatted read
    istream&	putback(char c);	// Unget char c
    int		sync();			// Write out data

  protected:  
    int		do_ipfx(int n);		// (2) Helper to ipfx()
  private:
    int		unf_count;		// # of bytes gotten by last
					// unformatted operation
    void	xget(char* c);		// ??? Not implemented
};


class ostream : virtual public ios {
  public:
    virtual	~ostream();
                ostream(streambuf*);
  public:
    int		opfx();			// Output preamble
    void	osfx();			// Output postamble
    ostream&	flush();		// Write out data
    ostream&	seekp(streampos p);	// Change current position
    ostream&	seekp(streamoff o, ios::seek_dir d);
    					// Change current pos. relative to d
    streampos	tellp();		// Current position in stream

    // Write c to stream
    ostream&	put(char c);
    ostream&	put(unsigned char c);
    ostream&	put(signed char c);
    ostream&	complicated_put(char c);// ???

    // Write c to stream
    ostream&	operator<<(char c);
    ostream&	operator<<(unsigned char c);
    ostream&	operator<<(signed char c);

    ostream& 	ls_complicated(char);	// ???
    ostream& 	ls_complicated(unsigned char);
    					// ???
    // Write string to stream
    ostream&	operator<<(const char*);
    ostream&	operator<<(const unsigned char*);
    ostream&	operator<<(const signed char*);

    // Write integers according to current base
    ostream&	operator<<(short);
    ostream&	operator<<(int);	
    ostream&	operator<<(long);
    ostream&	operator<<(unsigned short);
    ostream&	operator<<(unsigned int);
    ostream&	operator<<(unsigned long);
    ostream&	operator<<(bool b) { return operator<<((int)b); }

    // Write real according to curr format
#if	defined(__EDG__) || !defined(__SINGLE_ONLY)
    ostream&	operator<<(double);	
#endif
    ostream&	operator<<(float);

    ostream&	operator<<(void*);	// Write out pointer address
    ostream&	operator<<(streambuf*);	// Write all chars from stream

    // Manipulator hooks
    ostream&	operator<<( ostream& (*f)(ostream&) );
    ostream&	operator<<( ios& (*f)(ios&) );

    // Write byte block to stream
    ostream&	write(const char* s,int n);
    ostream&	write(const unsigned char* s,int n);
    ostream&	write(const signed char* s,int n);
    					
  protected:
    int		do_opfx();		// ???
    void	do_osfx();		// ???
    		ostream();		// Constructor
  public: /*** Obsolete constructor, carried over from stream package ***/
		ostream(int fd); 	// OLD! Do not use!
					// Use class fstream instead.
};


/* The input and output streams combined
 * ---------------------------------------------------------------------- */
class iostream : public istream, public ostream {
  public:
    virtual	~iostream();		// Destructor
    iostream(streambuf*);		// Construct from streambuf
  protected:
    iostream();				// For use by derived classes
};


/* Assignable version of the input stream
 * ---------------------------------------------------------------------- */
class istream_withassign : public istream {
  public:
    virtual	~istream_withassign();
		istream_withassign();
    istream_withassign&
		operator=(istream&);
    istream_withassign&
		operator=(streambuf*);
};


/* Assignable version of the output stream
 * ---------------------------------------------------------------------- */
class ostream_withassign : public ostream {
  public:
    virtual	~ostream_withassign();
		ostream_withassign();
    ostream_withassign&
		operator=(ostream&);
    ostream_withassign&
		operator=(streambuf*);
};


/* Assignable version of the input & output stream
 * ---------------------------------------------------------------------- */
class iostream_withassign : public iostream {
public:
    virtual	~iostream_withassign();
		iostream_withassign();
    iostream_withassign&
		operator=(ios&);	// Copy constructor???
    iostream_withassign&
		operator=(streambuf*);	// Normal constructor
};


/* Predefined streams
 * ---------------------------------------------------------------------- */
extern istream_withassign cin;		// Standard input
extern ostream_withassign cout;		// Standard output
extern ostream_withassign cerr;		// Standard error (unbuffered)
extern ostream_withassign clog;		// Log stream (buffered cerr)


/* Predefined manipulators
 * ---------------------------------------------------------------------- */
ios&		oct(ios&);		// Integer base: octal
ios&		dec(ios&);		// Integer base: decimal
ios&		hex(ios&);		// Integer base: hexadecimal
ostream&	endl(ostream& i);	// Insert newline and flush
ostream&	ends(ostream& i);	// End string: Insert null byte
ostream&	flush(ostream&);	// Flush stream
istream&	ws(istream&);		// Get whitespace chars


/* Class used to initialize the iostream package
 * ---------------------------------------------------------------------- */
class Iostream_init {
  public:			// 2DO: Make this private
    enum stdstatenum {
	unknown = 0,		// Not initialized state
	fds = 1,		// File descriptors are used
	FILEs = 2		// FILE structures are used
    };
    static stdstatenum
		stdstatus;	// Current stdio mode
    static int	initcount;	// Counter so init is done only once
    friend	ios;		// So ios::sync_with_stdio() can access us
  public:
		Iostream_init();
		~Iostream_init();
};

/* Include inlined members
 * ---------------------------------------------------------------------- */
#ifndef NO_INLINE
#  include "iostream.inl"
#endif

#ifndef __DONT_INIT_IOSTREAMS

/* Make sure iostream package is initialized
 * ---------------------------------------------------------------------- */
static Iostream_init iostream_init;
#endif

//
//	Brutal fix by Dalle
//

extern "C" char *ecvt(double, int, int*, int*);
extern "C" char* fcvt(double, int, int*, int*);

#endif /* __Iiostream */
