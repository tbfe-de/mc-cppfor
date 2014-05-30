
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
	assert(size() > offset);
	const std::size_t idx = (iput >= (offset+1))
				? iput - (offset+1)
				: iput + 11 - (offset+1);
	return data[wrap(idx)];
}

int main() {
	// object under test
	RingBuffer rb;

	// test initial state
	//
	assert(r.empty() == true);
	// ...
	// TO-BE-DONE: add more tests
	
	// (... many more tests ...)
}

