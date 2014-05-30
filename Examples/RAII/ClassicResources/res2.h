#ifndef RES2_H
#define RES2_H

struct res2 {
	// resource state (intended to be opaque)
	// ...
};

res2 *allocateRes2();
void deallocateRes2(res2 *);

void makeUseOfRes2_a(res2 *);
void makeUseOfRes2_b(res2 *);
// ... maybe many more ...

#endif
