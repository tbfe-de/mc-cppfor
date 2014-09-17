/*
 ===============================================================
 Class Extrema Derived From Average
 ===============================================================
 As the problem specification didn't state whether the statistic
 extrem values should be calculated from the "historic" values
 only or from all values ever seen, the implementation below
 again allows for both options, again selected by the macro
 STATISTIC_OF_HISTORY_ONLY.
*/
#ifndef Extrema_H
#define Extrema_H

#include <cassert>

#include "Average.h"

class Extrema : public Average {
	double min, max;
public:
	Extrema(double v) : Average(v), min(v), max(v) {}
	double getMinimum() const {
		return min;
	}
	double getMaximum() const {
		return max;
	}
#ifdef STATISTIC_OF_HISTORY_ONLY
	void setValue(double v) {
		Average::setValue(v);
		min = max = getValue();
		for (auto i = 1; i < size(); ++i) {
			const auto t = getHistoricValue(i);
			if (t < min) min = t;
			if (t > max) max = t;
		}
	}
	void clearHistory() {
		min = max = getValue();
		Average::clearHistory();
	}
#else
	void setValue(double v) {
		if (v < min) min = v;
		if (v > max) max = v;
		Average::setValue(v);
	}
#endif
};

#endif
