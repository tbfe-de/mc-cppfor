/*
 ===============================================================
 Class Statistic Derived From Average and Extrema
 ===============================================================
*/
#ifndef Statistic_H
#define Statistic_H

#include <cassert>

#include "RingBuffer.h"
#include "IValue.h"
#include "IAverage.h"
#include "IExtrema.h"

class Statistic : public IValue, public IAverage, public IExtrema {
	RingBuffer<double, 6> values;
	double avg, min, max;
public:
	Statistic(double v) : avg(v), min(v), max(v) {
		values.put(v);
	}
	virtual void setValue(double v) {
		values.put(v);
		avg = min = max = getValue();
		for (int i = 1; i < values.size(); ++i) {
			const auto tmp = values.peek(values.size()-i-1);
			avg += tmp;
			if (tmp < min) min = tmp;
			if (tmp > max) max = tmp;
		}
		avg /= values.size();
	}
	virtual double getValue() const {
		return getHistoricValue(0);
	}
	virtual double getHistoricValue(int n) const {
		assert(n >= 0);
		assert(n <= 5);
		return values.peek(values.size() - 1 - n);
	}
	virtual int maxHistory() const {
		return static_cast<int>(values.max_size());
	}
	virtual int historySize() const {
		return static_cast<int>(values.size());
	}
	virtual void clearHistory() {
		while (values.size() > 1) {
			double dummy;
			values.get(dummy);
		}
		avg = min = max = getValue();
	}
	virtual double getAverage() const {
		return avg;
	}
	virtual double getMinimum() const {
		return min;
	}
	virtual double getMaximum() const {
		return max;
	}
};

#endif
