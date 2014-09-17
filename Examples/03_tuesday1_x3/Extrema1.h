#ifndef Extrema_H
#define Extrema_H

#include "Value1.h"

class ExtremaMixin {
	bool first;
	double minimum, maximum;
public:
	ExtremaMixin()
		: first(true)
	{}
	virtual void setValue(double v) {
		if (first) {
			minimum = maximum = v;
			first = false;
		}
		else if (v < minimum)
			minimum = v;
		else if (v > maximum)
			maximum = v;
	}
	double getMinimum() const {
		return minimum;
	}
	double getMaximum() const {
		return maximum;
	}
};

class Extrema
	: public Value
	, private ExtremaMixin {
public:
	virtual void setValue(double v) {
		Value::setValue(v);
		ExtremaMixin::setValue(v);
	}
	using ExtremaMixin::getMinimum;
	using ExtremaMixin::getMaximum;
};

#endif
