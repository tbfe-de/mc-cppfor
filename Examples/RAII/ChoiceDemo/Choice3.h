/*
 ==============================================================================
 Third Implementation of an Aggregate Design with Optional and Multiple Part
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

 This implementation uses `const`-qualified pointers, what makes sense as after
 initialisation the pointers will not be changed any more. Therefore the MI-list
 (short for member initialisation list) needs to be used and to protect against
 exceptions thrown from the constructors of `Window` or `MenuItem` the MI-list
 (together with the construtcor code block) is wrapped into a try-catch block.
 (The option to wrap the whole initializer list had been introduced with C++98,
 before the below code were rejected as syntax error.)

 Though the approach looks valid at a cursory glance, it is flawed and the
 program is in UB-land (UB = undefined behaviour) if an exception is thrown
 while executing member initializers, as the pointers are not yet set if an
 execption occurs, and arbitrary "pointer"-values are given to `delete` that
 are neither received from a call to `new` nor `nullptr`.

 While `delete`-ing the ressource allocated is clearly wrong (because, if it
 were executed this were either successful and hence the local catch were never
 entered or it failed and the catch block were entered but the `mi`-pointer
 uninitialized), WHEN entring the catch-block it could not be safely decided
 whether the `w`-pointer refers to a valid resource or is uninitialized.s

 Using nested try-blocks, like

      MyClass *const p1 = new MyClass( … );
      try {
          OtherClass *const p2 = OtherClass( … );
          try {
              …
              … // use p1 and p2
              …
          }
          catch ( … ) {
              delete p2;
              throw;
          }
      catch ( … ) {
          delete p1;
          throw;
      }

 which usually solves this kind of problem can not be used in MI-lists.
 (Starting a try block in the middle of an MI-list is no valid syntax.)

 This class will be compiled with the demo program `choice_demo.cpp` when the
 macro CHOICE_VERSION is set to 3. Besides showing trace output (for objects
 being constructed or destroyed) the program allows to throw exceptions in many
 situations, what can be used to verify the following claim:
   * Besides the one mentioned abor, there should be no other problems with
     respect to memory managment!
   * As consequences of the problem technically are UB, no prediction can be
     made what actually will happen ... it may even APPEAR as if all is well,
     and also debug- and release-versions may expose different behavior.
*/

#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

#include "Window.h"
#include "MenuItem.h"

class Choice {
    Window *const w;
    MenuItem *const mi;
public:
    Choice(bool pop_up, const char *const mtext[], size_t msize)
        try : w(pop_up ? new Window("... xxx ...") : 0)
            , mi(new MenuItem[msize]) {
        for (size_t i = 0; i < msize; ++i)
            mi[i].setText(mtext[i]);
        ITrace::allow("== completing creation of Choice()-object");
    }
    catch (...) {
        delete[] mi;
	delete w;
        throw;
    }
    void select() {
        ITrace::allow("** executing Choice::select()");
        // ...
    }
    ~Choice() {
        delete[] mi;
        delete w;
    }
private:
    // disable default versions
    Choice(const Choice &) = delete;
    Choice(Choice &&) = delete;
    Choice &operator=(Choice &&) = delete;
    Choice &operator=(const Choice &) = delete;
};
