#include <cstddef>
#include <string>
#include <iostream>

class RingBuffer {
	enum { MAX_SIZE = 7 };
	std::string data[MAX_SIZE+1];
	std::size_t iput, iget;
public:
	RingBuffer()
		: iput(0)
		, iget(0)
	{}
	std::size_t size() const {
		return (iput >= iget)
			? (iput - iget)
			: (iput + (MAX_SIZE+1) - iget);
	}
	bool empty() const {
		return (iput == iget);
	}
	bool full() const {
		return (((iput+1) % (MAX_SIZE+1)) == iget);
	}
	bool put(const std::string &e) {
		if (full())
			return false;
		data[iput = ((iput+1) % (MAX_SIZE+1))] = e;
		return true;
	}
	bool get(std::string &e) {
		if (empty())
			return false;
		e = data[iget = ((iget+1) % (MAX_SIZE+1))];
		return true;
	}
	bool put(std::istream &is) {
		if (full())
			return false;
		std::string e;
		if (is >> e)
			data[iput = ((iput+1) % (MAX_SIZE+1))] = e;
		return true;
	}
	bool get(std::ostream &os) {
		if (empty())
			return false;
		const std::size_t idx = (iget+1) % (MAX_SIZE+1);
		if (os << data[idx])
			iget = idx;
		return true;
	}
};

#include <cassert>
#include <iostream>

void checksize(const RingBuffer &rb, std::size_t expected_size) {
	assert(rb.size() == expected_size);
	assert(rb.empty() == (expected_size == 0));
	assert(rb.full() == (expected_size == 7));
}

#include <sstream>

int main() {
	using namespace std;
	RingBuffer rb;

	// initial state
	checksize(rb, 0);

	// single put
	istringstream iss("hello");
	assert(rb.put(iss));
	checksize(rb, 1);

	// single get
	ostringstream oss;
	assert(rb.get(oss));
	assert(oss.str() == string("hello"));
	checksize(rb, 0);

	// put until full
	istringstream iss2("x xx xxx xxxx xxxxx xxxxxx xxxxxxx xxxxxxxx");
	int n = 0;
	while (rb.put(iss2)) {
		++n;
		checksize(rb, n);
	}
	assert(n == 7);
	checksize(rb, 7);

	// put when full
	assert(!rb.put(iss2));
	checksize(rb, 7);

	// get until empty
	ostringstream oss2;
	assert(rb.get(oss2));
	checksize(rb, 6);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 5);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 4);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 3);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 2);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 1);
	oss2 << ' ';
	assert(rb.get(oss2));
	checksize(rb, 0);
	assert(oss2.str() == "x xx xxx xxxx xxxxx xxxxxx xxxxxxx");

	// get from empty
	assert(!rb.get(oss2));
	checksize(rb, 0);
	assert(oss2.str() == "x xx xxx xxxx xxxxx xxxxxx xxxxxxx");

	cout << "** ALL TESTS PASSED **" << endl;
}
