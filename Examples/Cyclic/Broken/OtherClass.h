// file: OtherClass.h

#ifndef OtherClass_H
#define OtherClass_H

#include "SomeClass.h"

class OtherClass {
public:
	// ...

	// this is why we need to include
	// the header file of SomeClass:
	//
	SomeClass &someLink;
};

// ...

#endif
