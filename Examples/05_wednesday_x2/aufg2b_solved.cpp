/*
 ===============================================================
 Class Value using RingBuffer as Adaptable Component.
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
T RingBuffer<T, N>::peek(std::size_t offset = 0) const {
	assert(size() > offset);
	const std::size_t idx = (iput >= (offset+1))
				? iput - (offset+1)
				: iput + (N+1) - (offset+1);
	return data[wrap(idx)];
}

class Value {
	RingBuffer<double, 6> historicValues;
public:
	void setValue(double v) {
		historicValues.put(v);
	}
	double getValue() const {
		return getHistoricValue(0);
	}
	double getHistoricValue(int n) const {
		assert(n >= 0);
		assert(n <= 5);
		return historicValues.peek(n);
	}
	void clearHistory() {
		while (historicValues.size() > 1) {
			double dummy;
			historicValues.get(dummy);
		}
	}
	std::size_t size() const {
		return historicValues.size();
	}
};

#include <iostream>
int main() {
	Value data;

	assert(data.size() == 0);

	data.setValue(1.1);
	assert(data.size() == 1);
	assert(data.getValue() == 1.1);
	assert(data.getHistoricValue(0) == 1.1);

	data.setValue(2.2);
	assert(data.size() == 2);
	assert(data.getValue() == 2.2);
	assert(data.getHistoricValue(0) == 2.2);
	assert(data.getHistoricValue(1) == 1.1);

	data.setValue(3.3);
	assert(data.size() == 3);
	assert(data.getValue() == 3.3);
	assert(data.getHistoricValue(0) == 3.3);
	assert(data.getHistoricValue(1) == 2.2);
	assert(data.getHistoricValue(2) == 1.1);

	data.setValue(4.4);
	assert(data.size() == 4);
	assert(data.getValue() == 4.4);
	assert(data.getHistoricValue(0) == 4.4);
	assert(data.getHistoricValue(1) == 3.3);
	assert(data.getHistoricValue(2) == 2.2);
	assert(data.getHistoricValue(3) == 1.1);

	data.setValue(5.5);
	assert(data.size() == 5);
	assert(data.getValue() == 5.5);
	assert(data.getHistoricValue(0) == 5.5);
	assert(data.getHistoricValue(1) == 4.4);
	assert(data.getHistoricValue(2) == 3.3);
	assert(data.getHistoricValue(3) == 2.2);
	assert(data.getHistoricValue(4) == 1.1);

	data.setValue(6.6);
	assert(data.size() == 6);
	assert(data.getValue() == 6.6);
	assert(data.getHistoricValue(0) == 6.6);
	assert(data.getHistoricValue(1) == 5.5);
	assert(data.getHistoricValue(2) == 4.4);
	assert(data.getHistoricValue(3) == 3.3);
	assert(data.getHistoricValue(4) == 2.2);
	assert(data.getHistoricValue(5) == 1.1);

	data.setValue(7.7);
	assert(data.size() == 6);
	assert(data.getValue() == 7.7);
	assert(data.getHistoricValue(0) == 7.7);
	assert(data.getHistoricValue(1) == 6.6);
	assert(data.getHistoricValue(2) == 5.5);
	assert(data.getHistoricValue(3) == 4.4);
	assert(data.getHistoricValue(4) == 3.3);
	assert(data.getHistoricValue(5) == 2.2);

	data.clearHistory();
	assert(data.size() == 1);
	assert(data.getValue() == 7.7);
	assert(data.getHistoricValue(0) == 7.7);

	std::cout << "ALL TESTS PASSED" << std::endl;
}
