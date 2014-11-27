#ifndef Statistic_H
#define Statistic_H

#include "Value2.h"
#include "Average2.h"
#include "Extrema2.h"

class Statistic
	: public Value
	, public AverageMixin
	, public ExtremaMixin {
public:
	Statistic()
		: AverageMixin(static_cast<Value&>(*this))
		, ExtremaMixin(static_cast<Value&>(*this))
	{}
};

#endif
