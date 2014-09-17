#ifndef Extrema_H
#define Extrema_H

#include "Value2.h"

class ExtremaMixin : public Value::Update {
	bool first;
	double minimum, maximum;
	virtual void setNotify(double v) {
		if (first) {
			minimum = maximum = v;
			first = false;
		}
		else if (v < minimum)
			minimum = v;
		else if (v > maximum)
			maximum = v;
	}
public:
	ExtremaMixin(Value& v)
		: first(true)
	{
		v.registerUpdate(this);
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
	, public ExtremaMixin {
public:
	Extrema()
		: ExtremaMixin(static_cast<Value&>(*this))
	{}
};

#endif
