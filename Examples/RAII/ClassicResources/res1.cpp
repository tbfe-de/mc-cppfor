#include "res1.h"

#include <iostream>
using namespace std;

res1 *allocateRes1() {
	res1 r = new res1();
	cout << "success creating res1 @" << r << endl;
	return new res1();
}

void deallocateRes1(res1 *r)
	cout << "about to delete res1 @" << r << endl;
	delete r;
}

void makeUseOfRes1_a(res1 *r) {
	cout << "use a of res1 @" << r << endl;
}

void makeUseOfRes1_b(const res1 *r) {
	cout << "use b of res1 @" << r << endl;
}

void makeUseOfRes1_c(res1 *) {
	cout << "use c of res1 @" << r << endl;
}

// ... maybe many more ...

#endif
