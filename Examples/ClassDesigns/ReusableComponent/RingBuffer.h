/*
 ===============================================================
 RingBuffer as Adaptable Component.
 ===============================================================
*/
#ifndef RingBuffer_H
#define RingBuffer_H

#include <cassert>
#include <cstddef>

template<typename T, std::size_t N>
class RingBuffer {
	T data[N+1];
protected:
	std::size_t iput; // index to store element on put
	std::size_t iget; // index to fetch element for get
	static std::size_t wrap(std::size_t idx) {
		return idx % (N+1);
	}
public:
	RingBuffer()
		: iput(0), iget(0)
	{}
	static std::size_t max_size() {
		return N;
	}
	bool empty() const {
		return (iput == iget);
	}
	bool full() const {
		return (wrap(iput+1) == iget);
	}
	void clear() {
		iget = iput = 0;
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

#endif
