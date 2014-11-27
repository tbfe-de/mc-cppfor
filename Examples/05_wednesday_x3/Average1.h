#ifndef Average_H
#define Average_H

#include "Value1.h"

class AverageMixin {
	double sum;
	int cnt;
public:
	AverageMixin()
		: sum(0.0), cnt(0)
	{}
	virtual void setValue(double v) {
		sum += v;
		++cnt;
	}
	double getAverage() const {
		return sum/cnt;
	}
};

class Average
	: public Value
	, private AverageMixin {
public:
	Average() : Value(), AverageMixin() {}
	virtual ~Average() {}
	virtual void setValue(double v) {
		Value::setValue(v);
		AverageMixin::setValue(v);
	}
	using AverageMixin::getAverage;
};

#endif
