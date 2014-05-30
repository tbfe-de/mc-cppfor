#include <cassert>
#include <cstddef>

class RingBuffer {
	double data[11];
protected:
	std::size_t iput;
	std::size_t iget;
	static std::size_t wrap(std::size_t idx) {
		return idx % 11;
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
	void put(const double &);
	void get(double &);
	double peek(std::size_t) const;
};

void RingBuffer::put(const double &e) {
	if (full())
		iget = wrap(iget+1);
	assert(!full());
	data[iput] = e;
	iput = wrap(iput+1);
}

void RingBuffer::get(double &e) {
	assert(!empty());
	e = data[iget];
	iget = wrap(iget+1);
}

double RingBuffer::peek(std::size_t offset = 0) const {
	assert(!empty());
	assert(offset >= 0);
	assert(offset < 10);
	return data[wrap(iget+offset)];
}

#include <iostream>

void test_initial_state() {
	RingBuffer rb;

	assert(rb.empty() == true);
	assert(rb.full() == false);
}

void test_single_put_and_get() {
	RingBuffer rb;

	rb.put(3.14);
	assert(rb.empty() == false);
	assert(rb.full() == false);
	assert(rb.peek() == 3.14);
	assert(rb.peek(0) == 3.14);

	double v;
	rb.get(v);
	assert(v == 3.14);
	assert(rb.empty() == true);
	assert(rb.full() == false);
}

void test_several_put_and_get() {
	RingBuffer rb;
	double v = 1.0;

	rb.put(v /= 2);
	rb.put(v /= 2);
	rb.put(v /= 2);
	assert(rb.empty() == false);
	assert(rb.full() == false);
	assert(rb.peek(0) == 1.0/2);
	assert(rb.peek(1) == 1.0/4);
	assert(rb.peek(2) == 1.0/8);

	rb.get(v);
	assert(v == 1.0/2);
	assert(rb.empty() == false);
	assert(rb.full() == false);
	assert(rb.peek(0) == 1.0/4);
	assert(rb.peek(1) == 1.0/8);
	rb.get(v);
	assert(v == 1.0/4);
	assert(rb.empty() == false);
	assert(rb.full() == false);
	assert(rb.peek(0) == 1.0/8);
	rb.get(v);
	assert(v == 1.0/8);
	assert(rb.empty() == true);
	assert(rb.full() == false);
}

void test_put_until_full() {
	RingBuffer rb;

	int count = 0;
	while (!rb.full()) {
		rb.put(count / 2.0);
		++count;
	}
	assert(count == 10);
	assert(rb.full() == true);
	assert(rb.empty() == false);

	assert(rb.peek(0) == 0/2.0);
	assert(rb.peek(1) == 1/2.0);
	assert(rb.peek(2) == 2/2.0);
	// ...
	assert(rb.peek(8) == 8/2.0);
	assert(rb.peek(9) == 9/2.0);
}

void test_put_to_overspill() {
	RingBuffer rb;

	int count = 0;
	while (!rb.full()) {
		rb.put(count / 2.0);
		++count;
	}

	rb.put(1.1);
	assert(rb.full() == true);
	assert(rb.empty() == false);
	assert(rb.peek(0) == 1/2.0);
	assert(rb.peek(1) == 2/2.0);
	// ...
	assert(rb.peek(8) == 9/2.0);
	assert(rb.peek(9) == 1.1);

	rb.put(2.2);
	assert(rb.full() == true);
	assert(rb.empty() == false);
	assert(rb.peek(0) == 2/2.0);
	// ...
	assert(rb.peek(8) == 1.1);
	assert(rb.peek(9) == 2.2);
}

void test_get_from_half_full_until_empty() {
	RingBuffer rb;

	for (int i = 0; i < 5; ++i) {
		rb.put(i / 2.0);
	}
	assert(rb.empty() == false);
	assert(rb.full() == false);

	const std::size_t N = 5;
	double v[N] = {0.0}; // will initialize all
	std::size_t idx = 0;
	while (!rb.empty()) {
		assert(idx < N);
		rb.get(v[idx++]);
	}
	assert(v[0] == 0 / 2.0);
	assert(v[1] == 1 / 2.0);
	assert(v[2] == 2 / 2.0);
	assert(v[3] == 3 / 2.0);
	assert(v[4] == 4 / 2.0);
}

void test_get_from_exactly_full_until_empty() {
	RingBuffer rb;

	for (int i = 0; i < 10; ++i) {
		assert(rb.full() == false);
		rb.put(i / 2.0);
	}
	assert(rb.full() == true);

	const std::size_t N = 10;
	double v[N] = {0.0};
	std::size_t idx = 0;
	while (!rb.empty()) {
		assert(idx < N);
		rb.get(v[idx++]);
	}
	assert(v[0] == 0 / 2.0);
	assert(v[1] == 1 / 2.0);
	assert(v[2] == 2 / 2.0);
	// ...
	assert(v[8] == 8 / 2.0);
	assert(v[9] == 9 / 2.0);
}

void test_get_from_overspilled_full_until_empty() {
	RingBuffer rb;

	for (int i = 0; i < 15; ++i) {
		assert(i < 10 || rb.full() == true);
		rb.put(i / 2.0);
	}

	const std::size_t N = 10;
	double v[N] = {0.0};
	std::size_t idx = 0;
	while (!rb.empty()) {
		assert(idx < N);
		rb.get(v[idx++]);
	}
	assert(v[0] == 5 / 2.0);
	assert(v[1] == 6 / 2.0);
	assert(v[2] == 7 / 2.0);
	// ...
	assert(v[8] == 13 / 2.0);
	assert(v[9] == 14 / 2.0);
}

int main() {
	test_initial_state();
	test_single_put_and_get();
	test_several_put_and_get();
	test_put_until_full();
	test_put_to_overspill();
	test_get_from_half_full_until_empty();
	test_get_from_exactly_full_until_empty();
	test_get_from_overspilled_full_until_empty();
	
	std::cout << "** ALL TESTS PASSED **" << std::endl;
}

