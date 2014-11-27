#ifndef Statistic_H
#define Statistic_H

#include "Average1.h"
#include "Extrema1.h"

class Statistic
	: public Value
	, private AverageMixin
	, private ExtremaMixin {
public:
	virtual void setValue(double v) {
		Value::setValue(v);
		AverageMixin::setValue(v);
		ExtremaMixin::setValue(v);
	}
	using ExtremaMixin::getMinimum;
	using ExtremaMixin::getMaximum;
	using AverageMixin::getAverage;
};

#endif
