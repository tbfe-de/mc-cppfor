/*
 ===============================================================
 RingBuffer as Adaptable Component.
 ===============================================================
*/
#include <cassert>
#include <cstddef>

template<typename T, std::size_t N>
class RingBuffer {
	T data[N+1];
protected:
	std::size_t iput;
	std::size_t iget;
	static std::size_t wrap(std::size_t idx) {
		return idx % (N+1);
	}
public:
	RingBuffer()
		: iput(0), iget(0)
	{}
	bool empty() const {
		return (iput == iget);
	}
	bool full() const {
		return (wrap(iput+1) == iget);
	}
	std::size_t size() const {
		return (iput >= iget)
			? iput - iget
			: iput + (N+1) - iget;
	}
	void put(const T &);
	void get(T &);
	T peek(std::size_t) const;
};

template<typename T, std::size_t N>
void RingBuffer<T, N>::put(const T &e) {
	if (full())
		iget = wrap(iget+1);
	assert(!full());
	data[iput] = e;
	iput = wrap(iput+1);
}

template<typename T, std::size_t N>
void RingBuffer<T, N>::get(T &e) {
	assert(!empty());
	e = data[iget];
	iget = wrap(iget+1);
}

template<typename T, std::size_t N>
T RingBuffer<T, N>::peek(std::size_t offset) const {
	assert(size() > offset);
	return data[wrap(iget+offset)];
}

/*
 * NOTE: In the following the Standard C Macro "assert" is used as
 * a primitive means for automated testing. For a more serious TDD
 * approach using a Framework like CppTest, Cute, GoogleTest etc.
 * should be strongly considered.
 */

#include <iostream>
int main() {
	RingBuffer<double, 3> rb;

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

	rb.get(v);
	assert(v == 6.6);
	assert(!rb.full());
	assert(rb.empty());
	assert(rb.size() == 0);

	std::cout << "ALL TESTS PASSED" << std::endl;
}
