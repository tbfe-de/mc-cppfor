#ifndef Average_H
#define Average_H

#include <cassert>

#include "Value3.h"

class AverageMixin
	: protected Value::Update {
	double sum;
	int cnt;
	virtual void setNotify(double v) {
		sum += v;
		++cnt;
	}
protected:
	AverageMixin(Value& v)
		: sum(0.0), cnt(0) {
		v.registerUpdate(this);
	}
public:
	bool hasAverage() const {
		return cnt > 0;
	}
	double getAverage() const {
		assert(hasAverage());
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
	virtual std::ostream& print(std::ostream &os) const {
		return os << "ø " << getAverage();
	}
};

#endif
