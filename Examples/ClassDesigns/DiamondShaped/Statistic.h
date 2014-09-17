/*
 ===============================================================
 Class Statistic Derived From Average and Extrema
 ===============================================================
*/
#ifndef Statistic_H
#define Statistic_H

#include "Average.h"
#include "Extrema.h"

class Statistic : public Average, public Extrema {
public:
	Statistic(double v) : Value(v), Average(v), Extrema(v) {}
	void setValue(double v) {
		Average::setValue(v, false);
		Extrema::setValue(v, true);
	}
};

#endif
