#ifndef Extrema_H
#define Extrema_H

#include "Value3.h"

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
protected:
	ExtremaMixin(Value& v)
		: first(true)
	{
		v.registerUpdate(this);
	}
public:
	bool hasExtrema() const {
		return !first;
	}
	double getMinimum() const {
		assert(hasExtrema());
		return minimum;
	}
	double getMaximum() const {
		assert(hasExtrema());
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
	virtual std::ostream& print(std::ostream& os) const {
		return os << getMinimum() << " … " << getMaximum();
	}
};

#endif
