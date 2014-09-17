/*
 ===============================================================
 Testing the Class Value
 ===============================================================
*/
#include "Value.h"

#include <cassert>
#include <cstddef>
#include <iostream>

int main() {
	Value data(0.0);

	assert(data.size() == 1);
	assert(data.max_size() == 6);
	assert(data.getHistoricValue(0) == 0.0);

	data.setValue(1.1);
	assert(data.size() == 2);
	assert(data.getValue() == 1.1);
	assert(data.getHistoricValue(0) == 1.1);
	assert(data.getHistoricValue(1) == 0.0);

	data.setValue(2.2);
	assert(data.size() == 3);
	assert(data.getValue() == 2.2);
	assert(data.getHistoricValue(0) == 2.2);
	assert(data.getHistoricValue(1) == 1.1);
	assert(data.getHistoricValue(2) == 0.0);

	data.setValue(3.3);
	assert(data.size() == 4);
	assert(data.getValue() == 3.3);
	assert(data.getHistoricValue(0) == 3.3);
	assert(data.getHistoricValue(1) == 2.2);
	assert(data.getHistoricValue(2) == 1.1);
	assert(data.getHistoricValue(3) == 0.0);

	data.setValue(4.4);
	assert(data.size() == 5);
	assert(data.getValue() == 4.4);
	assert(data.getHistoricValue(0) == 4.4);
	assert(data.getHistoricValue(1) == 3.3);
	assert(data.getHistoricValue(2) == 2.2);
	assert(data.getHistoricValue(3) == 1.1);
	assert(data.getHistoricValue(4) == 0.0);

	data.setValue(5.5);
	assert(data.size() == 6);
	assert(data.getValue() == 5.5);
	assert(data.getHistoricValue(0) == 5.5);
	assert(data.getHistoricValue(1) == 4.4);
	assert(data.getHistoricValue(2) == 3.3);
	assert(data.getHistoricValue(3) == 2.2);
	assert(data.getHistoricValue(4) == 1.1);
	assert(data.getHistoricValue(5) == 0.0);

	data.setValue(6.6);
	assert(data.size() == 6);
	assert(data.getValue() == 6.6);
	assert(data.getHistoricValue(0) == 6.6);
	assert(data.getHistoricValue(1) == 5.5);
	assert(data.getHistoricValue(2) == 4.4);
	assert(data.getHistoricValue(3) == 3.3);
	assert(data.getHistoricValue(4) == 2.2);
	assert(data.getHistoricValue(5) == 1.1);

	data.setValue(7.7);
	assert(data.size() == 6);
	assert(data.getValue() == 7.7);
	assert(data.getHistoricValue(0) == 7.7);
	assert(data.getHistoricValue(1) == 6.6);
	assert(data.getHistoricValue(2) == 5.5);
	assert(data.getHistoricValue(3) == 4.4);
	assert(data.getHistoricValue(4) == 3.3);
	assert(data.getHistoricValue(5) == 2.2);

	data.clearHistory();
	assert(data.size() == 1);
	assert(data.getValue() == 7.7);
	assert(data.getHistoricValue(0) == 7.7);

	std::cout << "ALL TESTS PASSED" << std::endl;
}
