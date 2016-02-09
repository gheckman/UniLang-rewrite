/* ----------------------------------------------------------------------
 * iomanip.h -- Stream I/O manipulators
 *
 * Copyright: Diab Data AB, Sweden, 1992, 1993, All Rights Reserved
 * ----------------------------------------------------------------------
 * History:	920721	aem	initial
 */

#ifndef __Iiomanip
#define __Iiomanip

#include <iostream.h>


#define SMANIP(TYPE)	smanip_ ## TYPE
#define SAPP(TYPE)	sapply_ ## TYPE
#define IMANIP(TYPE)	imanip_ ## TYPE
#define OMANIP(TYPE)	omanip_ ## TYPE
#define IOMANIP(TYPE)	iomanip_ ## TYPE
#define IAPP(TYPE)	iapply_ ## TYPE
#define OAPP(TYPE)	oapply_ ## TYPE
#define IOAPP(TYPE)	ioapply_ ## TYPE

#define IOMANIPdeclare(TYPE)						\
class SMANIP(TYPE) {							\
  public:								\
    SMANIP(TYPE)(ios&(*fnp)(ios&, TYPE), TYPE val);			\
    friend istream& operator>>(istream& is, SMANIP(TYPE)& m);		\
    friend ostream& operator<<(ostream& os, SMANIP(TYPE)& m);		\
  private:								\
    ios& (*x_fnp)(ios&,TYPE);						\
    TYPE x_val;								\
};									\
class SAPP(TYPE) {							\
  public:								\
    SAPP(TYPE)(ios&(*fnp)(ios&,TYPE)); 					\
    SMANIP(TYPE) operator()(TYPE val);					\
  private:								\
    ios& (*x_fnp)(ios&,TYPE);						\
};									\
class IMANIP(TYPE) {							\
  public:								\
    IMANIP(TYPE)(istream& (*fnp)(istream&,TYPE), TYPE val);		\
    friend istream& operator>>(istream& is, IMANIP(TYPE)& m);		\
  private:								\
    istream& (*x_fnp)(istream&,TYPE);					\
    TYPE x_val;								\
};									\
class IAPP(TYPE) {							\
  public:								\
    IAPP(TYPE)(istream&(*fnp)(istream&,TYPE));				\
    IMANIP(TYPE) operator()(TYPE val);					\
  private:								\
    istream& (*x_fnp)(istream&,TYPE);					\
};									\
class OMANIP(TYPE) {							\
  public:								\
    OMANIP(TYPE)(ostream& (*fnp)(ostream&,TYPE), TYPE val);		\
    friend ostream& operator<<(ostream& is, OMANIP(TYPE)& m);		\
  private:								\
    ostream& (*x_fnp)(ostream&,TYPE);					\
    TYPE x_val;								\
};									\
class OAPP(TYPE) {							\
  public:								\
    OAPP(TYPE)(ostream&(*fnp)(ostream&,TYPE));				\
    OMANIP(TYPE) operator()(TYPE val);					\
  private:								\
    ostream& (*x_fnp)(ostream&,TYPE);					\
};									\
class IOMANIP(TYPE) {							\
  public:								\
    IOMANIP(TYPE)(iostream& (*fnp)(iostream&,TYPE), TYPE val);		\
    friend istream& operator<<(iostream& is, IOMANIP(TYPE)& m);		\
    friend ostream& operator>>(iostream& is, IOMANIP(TYPE)& m);		\
  private:								\
    iostream& (*x_fnp)(iostream&, TYPE);				\
    TYPE x_val;								\
};									\
inline SMANIP(TYPE)::SMANIP(TYPE)(ios&(*fnp)(ios&, TYPE), TYPE val) {	\
    x_fnp = fnp;							\
    x_val = val;							\
}									\
inline istream& operator>>(istream& is, SMANIP(TYPE)& m) {		\
    (*m.x_fnp)(is, m.x_val);						\
    return is;								\
}									\
inline ostream& operator<<(ostream& os, SMANIP(TYPE)& m) {		\
    (*m.x_fnp)(os, m.x_val);						\
    return os;								\
}									\
inline SAPP(TYPE)::SAPP(TYPE)(ios&(*fnp)(ios&,TYPE)) {			\
    x_fnp = fnp;							\
}									\
inline SMANIP(TYPE) SAPP(TYPE)::operator()(TYPE val) {			\
    return SMANIP(TYPE)(x_fnp, val);					\
}									\
inline IMANIP(TYPE)::IMANIP(TYPE)(istream& (*fnp)(istream&,TYPE),	\
	TYPE val) {							\
    x_fnp = fnp;							\
    x_val = val;							\
}									\
inline istream& operator>>(istream& is, IMANIP(TYPE)& m) {		\
    (*m.x_fnp)(is, m.x_val);						\
    return is;								\
}									\
inline IAPP(TYPE)::IAPP(TYPE)(istream&(*fnp)(istream&, TYPE)) {		\
    x_fnp = fnp;							\
}									\
inline IMANIP(TYPE) IAPP(TYPE)::operator()(TYPE val) {			\
    return IMANIP(TYPE)(x_fnp, val);					\
}									\
inline OMANIP(TYPE)::OMANIP(TYPE)(ostream& (*fnp)(ostream&,TYPE),	\
	TYPE val) {							\
    x_fnp = fnp;							\
    x_val = val;							\
}									\
inline ostream& operator<<(ostream& is, OMANIP(TYPE)& m) {		\
    (*m.x_fnp)(is, m.x_val);						\
    return is;								\
}									\
inline OAPP(TYPE)::OAPP(TYPE)(ostream&(*fnp)(ostream&, TYPE)) {		\
    x_fnp = fnp;							\
}									\
inline OMANIP(TYPE) OAPP(TYPE)::operator()(TYPE val) {			\
    return OMANIP(TYPE)(x_fnp, val);					\
}									\
inline IOMANIP(TYPE)::IOMANIP(TYPE)(iostream& (*fnp)(iostream&,TYPE),	\
	TYPE val) {							\
    x_fnp = fnp;							\
    x_val = val;							\
}									\
inline istream& operator<<(iostream& is, IOMANIP(TYPE)& m) {		\
    (*m.x_fnp)(is, m.x_val);						\
    return is;								\
}									\
inline ostream& operator>>(iostream& is, IOMANIP(TYPE)& m) {		\
    (*m.x_fnp)(is, m.x_val);						\
    return is;								\
}									\
class IOAPP(TYPE) {							\
  public:								\
    IOAPP(TYPE)(iostream&(*fnp)(iostream&,TYPE)) {			\
	x_fnp = fnp;							\
    }									\
    IOMANIP(TYPE) operator()(TYPE val) {				\
	return IOMANIP(TYPE)(x_fnp, val);				\
    }									\
  private:								\
    iostream& (*x_fnp)(iostream&,TYPE);					\
}

IOMANIPdeclare(int);
IOMANIPdeclare(long);

SMANIP(long)	resetiosflags(long f);
SMANIP(int)	setfill(int i);
SMANIP(long)	setiosflags(long f);
SMANIP(int)	setprecision(int i);
SMANIP(int)	setw(int i);
SMANIP(int)	setbase(int i);

#endif /* __Iiomanip */
