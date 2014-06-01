/*
 ===============================================================
 RingBuffer as Adaptable Component.
 ===============================================================
*/
#ifndef INCLUDE_RingBuffer_H
#define INCLUDE_RingBuffer_H

#include <cassert>
#include <cstddef>

template<typename T, std::size_t N>
class RingBuffer {
	double data[N+1];
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
	void clear() {
		iget = iput;
	}
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
T RingBuffer<T, N>::peek(std::size_t offset = 0) const {
	assert(offset < size());
	return data[wrap(iget + offset)];
}

#endif
