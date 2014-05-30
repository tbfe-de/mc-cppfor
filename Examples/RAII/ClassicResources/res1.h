#ifndef RES1_H
#define RES1_H

struct res1 {
        // resource state (intended to be opaque)
        // ...
};

res1 *allocateRes1();                   // create initial state (returning) pointer
void deallocateRes1(res1 *);            // cleanup final state (accepting pointer)

void makeUseOfRes1_a(res1 *);           // can have effect on state
void makeUseOfRes1_b(const res1 *);     // will have NO effect on state
void makeUseOfRes1_c(res1 *);           // can have effect on state
// ... maybe many more ...

#endif
