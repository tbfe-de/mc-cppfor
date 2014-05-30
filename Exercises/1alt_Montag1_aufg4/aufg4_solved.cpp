#include <cstddef>
#include <string>

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
};

#include <cassert>
#include <iostream>

void checksize(const RingBuffer &rb, std::size_t expected_size) {
	assert(rb.size() == expected_size);
	assert(rb.empty() == (expected_size == 0));
	assert(rb.full() == (expected_size == 7));
}

int main() {
	using namespace std;
	RingBuffer rb;

	// initial state
	checksize(rb, 0);

	// single put
	assert(rb.put(string("hello, world")));
	checksize(rb, 1);

	// single get
	string s;
	assert(rb.get(s));
	assert(s == string("hello, world"));
	checksize(rb, 0);

	// put until full
	s = "x";
	int n = 0;
	while (rb.put(s)) {
		++n;
		checksize(rb, n);
		s += "x";
	}
	assert(n == 7);
	checksize(rb, 7);

	// put when full
	assert(!rb.put("xxxxxxxx"));
	checksize(rb, 7);

	// get until empty
	assert(rb.get(s) && s == "x");
	checksize(rb, 6);
	assert(rb.get(s) && s == "xx");
	checksize(rb, 5);
	assert(rb.get(s) && s == "xxx");
	checksize(rb, 4);
	assert(rb.get(s) && s == "xxxx");
	checksize(rb, 3);
	assert(rb.get(s) && s == "xxxxx");
	checksize(rb, 2);
	assert(rb.get(s) && s == "xxxxxx");
	checksize(rb, 1);
	assert(rb.get(s) && s == "xxxxxxx");
	checksize(rb, 0);

	// get from empty
	assert(!rb.get(s));
	checksize(rb, 0);

	cout << "** ALL TESTS PASSED **" << endl;
}
