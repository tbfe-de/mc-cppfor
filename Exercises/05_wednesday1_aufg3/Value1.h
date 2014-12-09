#ifndef Value_H
#define Value_H

class Value {
	double val;
public:
	virtual void setValue(double v) {
		val = v;
	}
	double getValue() const {
		return val;
	}
};

#endif
