/*
 ===============================================================
 Class Value using RingBuffer as Adaptable Component.
 ===============================================================
*/
#ifndef Value_H
#define Value_H

#include <cassert>

#include "../ReusableComponent/RingBuffer.h"

class Value : private RingBuffer<double, 6> {
              typedef RingBuffer<double, 6> HelperContainer;
public:
#if 1
	using HelperContainer::max_size;
	using HelperContainer::size;
#else
	static int max_size() const {
		return static_cast<int>(HelperContainer::max_size());
	}
	int size const() {
		return static_cast<int>(HelperContainer::size());
	}
#endif
	Value(double v) {
		setValue(v);
	}
	virtual void setValue(double v) {
		HelperContainer::put(v);
	}
	double getValue() const {
		return getHistoricValue(0);
	}
	double getHistoricValue(int n) const {
		assert(n >= 0);
		assert(n <= 5);
		return HelperContainer::peek(size() - 1 - n);
	}
	void clearHistory() {
		while (size() > 1) {
			double dummy;
			HelperContainer::get(dummy);
		}
	}
};

#endif
