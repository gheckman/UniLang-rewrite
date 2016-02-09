/* ----------------------------------------------------------------------
 * fstream.h -- File stream I/O
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920722	aem	initial
 */

#ifndef __Ifstream
#define __Ifstream

#ifndef __Iiostream
#include <iostream.h>
#endif

/* NOTE: The markers have the following meaning:
 *  (1)	A non-AT&T feature, only avaible in D-C++.
 *  (2)	A undocumented AT&T feature, expected to change, do not use.
 *  (3) A old compability feature, do not use
 */

class filebuf : public streambuf {
  public:
    // Open protection choosen by default
    static const int openprot;

    // Constructors and destructor
    filebuf();			// Open a closed stream
    filebuf(int fd);		// Open and attach
    filebuf(int fd, char* s, int sz);
    				// Open, attach and offer buffer
    ~filebuf();			// Flush and close (if opened)

    // Explicit open, attach and close
    filebuf*	open(const char* name, int m, int prot=openprot);
    				// Open file
    filebuf*	attach(int fd);	// Attach to file descriptor
    filebuf*	close();	// Flush and close (if opened)

    // Status value inspektors
    int 	is_open();	// True if attached or open
    int		fd();		// Return current file descriptor

    // Virtuals used by streambuf
    virtual int	overflow(int=EOF);
    				// Consume buffer
    virtual int underflow();	// Get caracters to buffer
    virtual int sync();		// Sync with external representation
    virtual streampos		// Seek relative to dir
		seekoff(streamoff off, ios::seek_dir dir, int omode);
    virtual streambuf*		// Offer buffer to stream
	setbuf(char* s, int sz);
  protected:
    int 	xfd;		// (2) File descriptor assosiated
    int 	mode;		// (2) Open mode, if opened by filebuf::open()
    char	opened;		// (2) True if this buffer is opened
    streampos	last_seek;	// (2) Position of the last seek
    char*	in_start;	// (2) Unused
    char	lahead[2];	// (2) Unused
    int 	nputback;	// (1) Number of chars of putback supported
};

class fstreambase : virtual public ios {
  public:
    // Constructors and destructors
    fstreambase();
    fstreambase(const char* name, int mode, int prot = filebuf::openprot);
    fstreambase(int fd);
    fstreambase(int fd, char* s, int sz);
    ~fstreambase();

    // Opening, attaching and closing
    void	open(const char* name, int mode, int prot =
		     filebuf::openprot);
    void	attach(int fd);
    void 	close();
    void 	setbuf(char* s, int sz);

    // Internal state inspektors
    filebuf*	rdbuf(); 	// Return pointer to buffer
    int		is_open();

  private:
    filebuf	buf;		// Buffer to use
};

class ifstream : public fstreambase, public istream {
  public:
    ifstream();
    ifstream(const char* name, int mode=ios::in, int prot =
	     filebuf::openprot);
    ifstream(int fd);
    ifstream(int fd, char* s, int sz);
    ~ifstream();
    filebuf* 	rdbuf();
    void	open(const char* name, int mode=ios::in, int prot =
		     filebuf::openprot);
};

class ofstream : public fstreambase, public ostream {
  public:
    ofstream();
    ofstream(const char* name, int mode=ios::out, int prot =
	     filebuf::openprot);
    ofstream(int fd);
    ofstream(int fd, char* s, int sz);
    ~ofstream();
    filebuf* 	rdbuf();
    void	open(const char* name, int mode=ios::out, int prot =
		     filebuf::openprot);
};

class fstream : public fstreambase, public iostream {
  public:
    fstream();			// Make a closed fstream
    fstream(const char* name, int mode, int prot = filebuf::openprot);
    				// Open file name
    fstream(int fd);		// Attached to open fd
    fstream(int fd, char* s, int sz);
    ~fstream();
				// Attach & offer buffer
    filebuf* 	rdbuf();	// Return filebuf associated w. stream
    void	open(const char* name, int mode, int prot =
		     filebuf::openprot);
};

/* Include inlines
 * ---------------------------------------------------------------------- */
#ifndef NO_INLINE
#  include "fstream.inl"
#endif


#endif /* __Ifstream */
