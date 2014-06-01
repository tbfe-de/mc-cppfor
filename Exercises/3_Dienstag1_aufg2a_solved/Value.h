/*
 ===============================================================
 Implementing a Value Class Using the Adaptable RingBuffer
 ===============================================================
*/
#ifndef INCLUDE_Value_H
#define INCLUDE_Value_H

#include "RingBuffer.h"

class Value {
	typedef RingBuffer<double, 6> HistoricValues;
	HistoricValues *history;
public:
	Value();
	~Value();
	Value(const Value&);
	Value& operator=(const Value&);
	void setValue(double);
	double getValue() const;
	double getHistoricValue(int = 0) const;
	std::size_t size() const;
	void clear();
};

inline
double Value::getValue() const {
	return history->peek();
}

inline
double Value::getHistoricValue(int n) const {
	return history->peek(n);
}

inline
std::size_t Value::size() const {
	return history->size();
}

inline
void Value::clear() {
	return history->clear();
}

#endif
