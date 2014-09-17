/*
 ===============================================================
 Class Extrema Derived From Value
 ===============================================================
*/
#ifndef Extrema_H
#define Extrema_H

#include <cassert>

#include "Value.h"

class Extrema : virtual public Value {
	double min, max;
public:
	Extrema(double v) : Value(v), min(v), max(v) {}
	double getMinimum() const {
		return min;
	}
	double getMaximum() const {
		return max;
	}
	void setValue(double v, bool update_value = true) {
		if (v < min) min = v;
		if (v > max) max = v;
		if (update_value)
			Value::setValue(v);
	}
};

#endif
