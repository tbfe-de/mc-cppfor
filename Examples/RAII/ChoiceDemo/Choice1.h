/*
 ==============================================================================
 First Implementation of an Aggregate Design with Optional and Multiple Part
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

 The implementation as shown has the deficit that it does no proper cleanup if
 exceptions occur during execution of the constructor. (They would have to be
 handled in a local try catch block, what is demonstrated in the next version.)

 This class will be compiled with the demo program `choice_demo.cpp` when the
 macro CHOICE_VERSION is set to 1. Besides showing trace output (for objects
 being constructed or destroyed) the program allows to throw exceptions so that
 incomplete cleanup (in practice resulting in a memory leak) can be easily
 demonstrated.

 Some things to try:
   * Stepping through all trace output shows ressources are released in the
     reverse order of allocation, followed by a regular program termination.
   * Throwing an exception outside the constructor will also release all
     ressources but makes the program terminate with an error message.
   * Throwing an exception during the construction of the `Choice` class will
     NOT release all resources before the program terminates with an error
     message.

 Note: If the program actually terminates, most hosted environments anyway will
 clean up memory afterwards, so it does not matter that much whether or not all
 allocated memory is explicitely released. But in case the program continues
 there will some memory be lost and if this happens a number of times - i.e. in
 a long-running application a restart might become necessary.
*/

#include <cstddef>

#include "ITrace.h"
#include "Window.h"
#include "MenuItem.h"

class Choice {
    Window *w;
    MenuItem *mi;
public:
    Choice(bool pop_up, const char *const mtext[], std::size_t msize)
            : w(0), mi(new MenuItem[msize]) {
        if (pop_up)
            w = new Window("... xxx ...");
        for (std::size_t i = 0; i < msize; ++i)
            mi[i].setText(mtext[i]);
        ITrace::allow("== completing creation of Choice()-object");
    }
    void select() {
        ITrace::allow("** executing Choice::select()");
        // ...
    }
    ~Choice() {
        // NOTE: destructor is NOT called when an
        // exception terminates the constructor
        delete[] mi;
        delete w;
    }
private:
    // disable default versions
    Choice(const Choice &) = delete;
    Choice &operator=(const Choice &) = delete;
    Choice(Choice &&) = delete;
    Choice &operator=(Choice &&) = delete;
};
