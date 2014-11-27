#ifndef Statistic_H
#define Statistic_H

#include "Value3.h"
#include "Average3.h"
#include "Extrema3.h"

class Statistic
	: public Value
	, public AverageMixin
	, public ExtremaMixin {
public:
	Statistic()
		: AverageMixin(static_cast<Value&>(*this))
		, ExtremaMixin(static_cast<Value&>(*this))
	{}
	virtual std::ostream& print(std::ostream& os) const {
		return os << "ø " << getAverage() << "; "
			  << getMinimum() << " … " << getMaximum(); 
	}
};

#endif
