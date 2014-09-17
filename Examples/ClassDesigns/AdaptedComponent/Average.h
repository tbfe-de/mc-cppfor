/*
 ===============================================================
 Class Average Derived From Value
 ===============================================================
 As the problem specification didn't state whether the statistic
 average should be calculated from the "historic" values only or
 from all values ever seen, the implementation below allows for
 both options, selected by the macro STATISTIC_OF_HISTORY_ONLY.
*/
#ifndef Average_H
#define Average_H

#include <cassert>

#include "Value.h"

class Average : public Value {
	double sum;
	int cnt;
public:
	Average(double v) : Value(v), sum(v), cnt(1) {}
	double getAverage() const {
		return sum / cnt;
	}
#ifdef STATISTIC_OF_HISTORY_ONLY
	void setValue(double v) {
		sum += v;
		if (size() < max_size())
			++cnt;
		else
			sum -= getHistoricValue(size()-1);
		Value::setValue(v);
	}
	void clearHistory() {
		sum = getValue();
		cnt = 1;
		Value::clearHistory();
	}
#else
	void setValue(double v) {
		sum += v;
		++cnt;
		Value::setValue(v);
	}
#endif
};

#endif
