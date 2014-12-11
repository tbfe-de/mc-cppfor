/*
 ==============================================================================
 Fourth Implementation of an Aggregate Design with Optional and Multiple Part
 ==============================================================================
 As UML diagram the design implemented here looks as follows:

                       +------------+           +----------+
           +---------->| WindowRes  |<#>------->|  Window  |
           |           +------------+      0..1 +----------+
     +----<#>---+  
     |  Choice  |
     +----<#>---+
           |           +-------------+     1..* +----------+
           +---------->| MenuItemRes |<#>------>| MenuItem |
                       +-------------+          +----------+

 This implementation introduces RAII with two resource wrapper classes, named
 `WindowRes` and `MenuItemRes`.

 The first one does not use the minimal possible implementation because it
 already incorporates the "optionality" of the `Window` (recognizable by the
 multiplicity which moved away from the connection with `Choice`).

 Also the second one is a bit special as the ressource wrapped is a container
 and therefore it makes sense to hide access to the ressource identifier in the
 indexing operation (i.e. `operator[]`, not - as with `Window` before - with a
 type-conversion (`operator Window*()`)

 

 This class will be compiled with the demo program `choice_demo.cpp` when the
 macro CHOICE_VERSION is set to 4. Besides showing trace output (for objects
 being constructed or destroyed) the program allows to throw exceptions so that
 incomplete cleanup (in practice resulting in a memory leak) could be easily
 demonstrated, though this version should have no such issues.
*/

#include <cstddef>
#include <iostream>
using namespace std;

#include "WindowRes.h"
#include "MenuItemRes.h"

class Choice {
	WindowRes w;
	MenuItemRes mi;
public:
	Choice(bool pop_up, const char *const mtext[], size_t msize)
			: w(pop_up, "... xxx ..."), mi(msize) {
		for (size_t i = 0; i < msize; ++i)
			mi[i].setText(mtext[i]);
		ITrace::allow("== completing creation of Choice()-object");
	}
	void select() {
		ITrace::allow("** executing Choice::select()");
		// ...
		if (w) useWindow(w);
		// ...
	}
private:
	// disable default versions
	Choice(const Choice &);
	Choice &operator=(const Choice &);
};
