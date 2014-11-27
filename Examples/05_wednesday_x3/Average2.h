#ifndef Average_H
#define Average_H

#include "Value2.h"

class AverageMixin
	: protected Value::Update {
	double sum;
	int cnt;
	virtual void setNotify(double v) {
		sum += v;
		++cnt;
	}
	AverageMixin(const AverageMixin& v);
public:
	AverageMixin(Value& v)
		: sum(0.0), cnt(0) {
		v.registerUpdate(this);
	}
	double getAverage() const {
		return sum/cnt;
	}
};

class Average
	: public Value
	, public AverageMixin {
public:
	Average()
		: AverageMixin(static_cast<Value&>(*this))
	{}
};

#endif
