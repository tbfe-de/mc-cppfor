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
	// ...

	// single put
	// ...

	// single get
	// ...

	// put until full
	// ...

	// put when full

	// get until empty
	// ...

	// get from empty
	// ...

	cout << "** ALL TESTS PASSED **" << endl;
}
