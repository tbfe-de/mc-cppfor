// file: OtherClass.h

#ifndef OtherClass_H
#define OtherClass_H
#include "SomeClass.h"

class OtherClass {
public:
	// ...

	// no full class definition required so
	// far as only a pointer is defined (same
	// would be true if it were a reference)
	//
	class SomeClass *someLink;
};

// We might need to include the full definition of
// OtherClass (and can do it safely at this point),
// in case any member function implementation of
// SomeClass needs to use any (accessible) member
// of OtherClass in this header.
//
#include "OtherClass.h"

// ...

#endif
