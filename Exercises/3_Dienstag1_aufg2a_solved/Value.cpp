/*
 ===============================================================
 Implementing a Value class using the adaptable RingBuffer
 ===============================================================
*/
#include "Value.h"

Value::Value()
	: history(new HistoricValues())
{}

Value::~Value() {
	delete history;
}

Value::Value(const Value& init)
	: history (new HistoricValues(*init.history))
{}

Value& Value::operator=(const Value& rhs) {
	HistoricValues *const tmp = new HistoricValues(*rhs.history);
	delete history;
	history = tmp;
}

void Value::setValue(double v) {
	if (history->full()) {
		double dummy;
		history->get(dummy);
	}
	history->put(v);
}
