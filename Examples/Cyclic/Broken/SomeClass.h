// file: SomeClass.h

#ifndef SomeClass_H
#define SomeClass_H

#include "OtherClass.h"

class SomeClass {
	// ...

	// this is why we need to include
	// the header file of OtherClass:
	//
	OtherClass *otherLink;
};

// ...

#endif
