/*
 ===============================================================
 Test RingBuffer as Adaptable Component.
 ===============================================================
*/
#include "RingBuffer.h"
#include <cassert>

/*
 * NOTE: In the following the Standard C Macro "assert" is used as
 * a primitive means for automated testing. For a more serious TDD
 * approach using a Framework like CppTest, Cute, GoogleTest etc.
 * should be strongly considered.
 */

#include <iostream>
int main() {
	RingBuffer<double, 4> rb;

	assert(rb.empty());
	assert(!rb.full());
	assert(rb.size() == 0);

	rb.put(1.1);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 1.1);
	assert(rb.size() == 1);

	rb.clear();
	assert(rb.empty());
	assert(!rb.full());
	assert(rb.size() == 0);

	rb.put(2.2);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 2.2);
	assert(rb.size() == 1);
	double v = 0.0;
	rb.get(v);
	assert(v == 2.2);
	assert(rb.empty());
	assert(!rb.full());
	assert(rb.size() == 0);

	rb.put(3.3);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 3.3);
	assert(rb.size() == 1);

	rb.put(4.4);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 3.3);
	assert(rb.peek(1) == 4.4);
	assert(rb.size() == 2);

	rb.put(5.5);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 3.3);
	assert(rb.peek(1) == 4.4);
	assert(rb.peek(2) == 5.5);
	assert(rb.size() == 3);

	rb.put(6.6);
	assert(!rb.empty());
	assert(rb.full());
	assert(rb.peek(0) == 3.3);
	assert(rb.peek(1) == 4.4);
	assert(rb.peek(2) == 5.5);
	assert(rb.peek(3) == 6.6);
	assert(rb.size() == 4);

	rb.put(7.7);
	assert(!rb.empty());
	assert(rb.full());
	assert(rb.peek(0) == 4.4);
	assert(rb.peek(1) == 5.5);
	assert(rb.peek(2) == 6.6);
	assert(rb.peek(3) == 7.7);
	assert(rb.size() == 4);

	rb.get(v);
	assert(v = 4.4);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 5.5);
	assert(rb.peek(1) == 6.6);
	assert(rb.peek(2) == 7.7);
	assert(rb.size() == 3);

	rb.get(v);
	assert(v = 5.5);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 6.6);
	assert(rb.peek(1) == 7.7);
	assert(rb.size() == 2);

	rb.get(v);
	assert(v = 6.6);
	assert(!rb.empty());
	assert(!rb.full());
	assert(rb.peek(0) == 7.7);
	assert(rb.size() == 1);

	rb.get(v);
	assert(v = 7.7);
	assert(rb.empty());
	assert(!rb.full());
	assert(rb.size() == 0);

	std::cout << "ALL TESTS PASSED" << std::endl;
}
