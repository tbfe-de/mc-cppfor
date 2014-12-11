/*
 ==============================================================================
 Second Implementation of an Aggregate Design with Optional and Multiple Part
 ==============================================================================
 As UML diagram the design implemented here looks as follows:

                       +----------+
           +---------->|  Window  |
           |      0..1 +----------+
          <#>      
     +-----+----+  
     |  Choice  |
     +-----+----+
          <#>
           |      1..* +----------+
           +---------->| MenuItem |
                       +----------+

 This implementation first initialises the two pointers to `nullptr`, then
 allocates heap memory (and executes constructors) and with a local try-catch
 block cares for exceptions eventually thrown during constructor execution.
 Because of these assignments after initialisation the pointers cannot be
 declared with `const`, though - despite the fact any later change is most
 probably a bug - the compiler cannot be coaxed into helping to detect this.

 This class will be compiled with the demo program `choice_demo.cpp` when the
 macro CHOICE_VERSION is set to 2. Besides showing trace output (for objects
 being constructed or destroyed) the program allows to throw exceptions so that
 incomplete cleanup (in practice resulting in a memory leak) could be easily
 demonstrated, though this version should have no such issues.
*/

#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

#include "Window.h"
#include "MenuItem.h"

class Choice {
    Window *w;
    MenuItem *mi;
public:
    Choice(bool pop_up, const char *const mtext[], size_t msize)
        : w(nullptr), mi(nullptr) {
        try {
            if (pop_up)
                w = new Window("... xxx ...");
            mi = new MenuItem[msize];
            for (size_t i = 0; i < msize; ++i)
                mi[i].setText(mtext[i]);
            ITrace::allow("== completing creation of Choice()-object");
        }
        catch (exception &) {
            // delete on nullptr is a no-op
            delete[] mi;
            delete w;
            throw;
        }
    }
    void select() {
        ITrace::allow("** executing Choice::select()");
        // ...
    }
    ~Choice() {
        delete w;
        delete[] mi;
    }
private:
    // disable default versions
    Choice(const Choice &) = delete;
    Choice(Choice &&) = delete;
    Choice &operator=(Choice &&) = delete;
    Choice &operator=(const Choice &) = delete;
};
