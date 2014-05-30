#include <cstddef>
#include <string>

class RingBuffer {
	std::string data[8];
	std::size_t iput, iget;
public:
	RingBuffer()
		: iput(0)
		, iget(0)
	{}
	bool empty() {
		return (iput == iget);
	}
	bool full() {
		return (((iput+1) % 8) == iget);
	}
	bool put(std::string e) {
		if (full())
			return false;
		data[iput = ((iput+1) % 8)] = e;
		return true;
	}
	bool get(std::string &e) {
		if (empty())
			return false;
		e = data[iget = ((iget+1) % 8)];
		return true;
	}
};

#include <cassert>
#include <iostream>

int main() {
	using namespace std;
	RingBuffer rb;

	// initial state
	assert(rb.empty());
	assert(!rb.full());

	// single put
	assert(rb.put(string("hello, world")));
	assert(!rb.empty());
	assert(!rb.full());

	// single get
	string s;
	assert(rb.get(s));
	assert(s == string("hello, world"));
	assert(rb.empty());
	assert(!rb.full());

	// put until full
	s = "x";
	int n = 0;
	while (rb.put(s)) {
		++n;
		s += "x";
	}
	assert(n == 7);
	assert(!rb.empty());
	assert(rb.full());

	// put when full
	assert(!rb.put("xxxxxxxx"));
	assert(!rb.empty());
	assert(rb.full());

	// get until empty
	assert(rb.get(s) && s == "x");
	assert(!rb.full());
	assert(rb.get(s) && s == "xx");
	assert(rb.get(s) && s == "xxx");
	assert(rb.get(s) && s == "xxxx");
	assert(rb.get(s) && s == "xxxxx");
	assert(rb.get(s) && s == "xxxxxx");
	assert(rb.get(s) && s == "xxxxxxx");
	assert(rb.empty());

	// get from empty
	assert(!rb.get(s));
	assert(!rb.full());
	assert(rb.empty());

	cout << "** ALL TESTS PASSED **" << endl;
}
