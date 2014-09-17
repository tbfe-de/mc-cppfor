/*
 ===============================================================
 Class Average Derived From Value
 ===============================================================
*/
#ifndef Average_H
#define Average_H

#include <cassert>

#include "Value.h"

class Average : virtual public Value {
	double sum;
	int cnt;
public:
	Average(double v) : Value(v), sum(v), cnt(1) {}
	double getAverage() const {
		return sum / cnt;
	}
	void setValue(double v, bool update_value = true) {
		sum += v;
		++cnt;
		if (update_value)
			Value::setValue(v);
	}
};

#endif
