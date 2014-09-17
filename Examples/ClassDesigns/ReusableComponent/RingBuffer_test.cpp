/*
 ===============================================================
 Testing the RingBuffer Adaptable Component.
 ===============================================================
*/
#include "RingBuffer.h"

#include <iostream>

/*
 * NOTE: In the following the Standard C Macro "assert" is used as
 * a primitive means for automated testing. For a more serious TDD
 * approach using a Framework like CppTest, Cute, GoogleTest etc.
 * should be strongly considered.
 */

#include <iostream>
int main() {
	RingBuffer<double, 3> rb;
	assert(rb.max_size() == 3);

	assert(rb.empty());
	assert(!rb.full());
	assert(rb.size() == 0);

	rb.put(3.3);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.size() == 1);

	// access stored values without removal
	assert(rb.peek(0) == 3.3);

	rb.put(4.4);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.size() == 2);

	// access stored values without removal
	assert(rb.peek(1) == 4.4);
	assert(rb.peek(0) == 3.3);

	rb.put(5.5);
	assert(!rb.empty());
	assert(rb.full());
	assert(rb.size() == 3);

	// access stored values without removal
	assert(rb.peek(2) == 5.5);
	assert(rb.peek(1) == 4.4);
	assert(rb.peek(0) == 3.3);

	rb.put(6.6); // overwrite oldest !!
	assert(!rb.empty());
	assert(rb.full());
	assert(rb.size() == 3);

	// access stored values without removal
	assert(rb.peek(2) == 6.6);
	assert(rb.peek(1) == 5.5);
	assert(rb.peek(0) == 4.4);

	double v;
	rb.get(v);
	assert(v == 4.4);
	assert(!rb.full());
	assert(!rb.empty());
	assert(rb.size() == 2);
	
	rb.get(v);
	assert(v == 5.5);
	assert(!rb.full());
	assert(!rb.empty());
	assert(rb.size() == 1);

	rb.clear();
	assert(!rb.full());
	assert(rb.empty());
	assert(rb.size() == 0);

	// other size and type
	RingBuffer<int, 5> rb2;
	assert(rb2.max_size() == 5);

	assert(rb2.empty());
	assert(!rb2.full());
	assert(rb2.size() == 0);
	rb2.put(1);
	rb2.put(2);
	rb2.put(3);
	rb2.put(4);
	rb2.put(5);
	assert(rb2.full());
	assert(rb2.size() == 5);
	assert(rb2.peek(0) == 1);
	assert(rb2.peek(1) == 2);
	assert(rb2.peek(2) == 3);
	assert(rb2.peek(3) == 4);
	assert(rb2.peek(4) == 5);

	rb2.clear();
	assert(!rb2.full());
	assert(rb2.empty());
	assert(rb2.size() == 0);

	std::cout << "ALL TESTS PASSED" << std::endl;
}
