/* ----------------------------------------------------------------------
 * stdiostream.inl -- Stream I/O thru FILE pointers
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

INLINE FILE* stdiobuf::stdiofile() {
    return fp;
}


INLINE streambuf* stdiobuf::setbuf(char*,int) {
    return NULL;
}
