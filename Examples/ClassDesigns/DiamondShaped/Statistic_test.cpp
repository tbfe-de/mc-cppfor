/*
 ===============================================================
 Testing Class Statistic (Derived from Average and Extrema)
 ===============================================================
*/
#include "Statistic.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

struct Near {
	const double d;
	Near(double d_) : d(d_) {}
};
bool operator==(double lhs, const Near &rhs) {
	if (lhs == 0.0 && rhs.d == 0.0) return true;
	const auto rdelta = std::fabs(lhs-rhs.d) / std::fabs(lhs+rhs.d);
	return (rdelta < 1e-9);
}

int main() {
	Statistic data(0.0);

	assert(data.size() == 1);
	assert(data.max_size() == 6);
	assert(data.getHistoricValue(0) == 0.0);
	assert(data.getAverage() == 0.0);
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 0.0);

	data.setValue(1.1);
	assert(data.size() == 2);
	assert(data.getValue() == 1.1);
	assert(data.getHistoricValue(0) == 1.1);
	assert(data.getHistoricValue(1) == 0.0);
	assert(data.getAverage() == Near(1.1/2));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 1.1);

	data.setValue(2.2);
	assert(data.size() == 3);
	assert(data.getValue() == 2.2);
	assert(data.getHistoricValue(0) == 2.2);
	assert(data.getHistoricValue(1) == 1.1);
	assert(data.getHistoricValue(2) == 0.0);
	assert(data.getAverage() == Near(3.3/3));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 2.2);

	data.setValue(3.3);
	assert(data.size() == 4);
	assert(data.getValue() == 3.3);
	assert(data.getHistoricValue(0) == 3.3);
	assert(data.getHistoricValue(1) == 2.2);
	assert(data.getHistoricValue(2) == 1.1);
	assert(data.getHistoricValue(3) == 0.0);
	assert(data.getAverage() == Near(6.6/4));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 3.3);

	data.setValue(4.4);
	assert(data.size() == 5);
	assert(data.getValue() == 4.4);
	assert(data.getHistoricValue(0) == 4.4);
	assert(data.getHistoricValue(1) == 3.3);
	assert(data.getHistoricValue(2) == 2.2);
	assert(data.getHistoricValue(3) == 1.1);
	assert(data.getHistoricValue(4) == 0.0);
	assert(data.getAverage() == Near(11.0/5));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 4.4);

	data.setValue(5.5);
	assert(data.size() == 6);
	assert(data.getValue() == 5.5);
	assert(data.getHistoricValue(0) == 5.5);
	assert(data.getHistoricValue(1) == 4.4);
	assert(data.getHistoricValue(2) == 3.3);
	assert(data.getHistoricValue(3) == 2.2);
	assert(data.getHistoricValue(4) == 1.1);
	assert(data.getHistoricValue(5) == 0.0);
	assert(data.getAverage() == Near(16.5/6));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 5.5);

	data.setValue(6.6);
	assert(data.size() == 6);
	assert(data.getValue() == 6.6);
	assert(data.getHistoricValue(0) == 6.6);
	assert(data.getHistoricValue(1) == 5.5);
	assert(data.getHistoricValue(2) == 4.4);
	assert(data.getHistoricValue(3) == 3.3);
	assert(data.getHistoricValue(4) == 2.2);
	assert(data.getHistoricValue(5) == 1.1);
#ifdef	STATISTIC_OF_HISTORY_ONLY
	assert(data.getAverage() == Near(23.1/6));
	assert(data.getMinimum() == 1.1);
	assert(data.getMaximum() == 6.6);
#else
	assert(data.getAverage() == Near(23.1/7));
	assert(data.getMinimum() == 0.0);
	assert(data.getMaximum() == 6.6);
#endif

	data.setValue(-.7);
	assert(data.size() == 6);
	assert(data.getValue() == -.7);
	assert(data.getHistoricValue(0) == -.7);
	assert(data.getHistoricValue(1) == 6.6);
	assert(data.getHistoricValue(2) == 5.5);
	assert(data.getHistoricValue(3) == 4.4);
	assert(data.getHistoricValue(4) == 3.3);
	assert(data.getHistoricValue(5) == 2.2);
#ifdef	STATISTIC_OF_HISTORY_ONLY
	assert(data.getAverage() == Near(21.3/6));
	assert(data.getMinimum() == -.7);
	assert(data.getMaximum() == 6.6);
#else
	assert(data.getAverage() == Near(22.4/8));
	assert(data.getMinimum() == -.7);
	assert(data.getMaximum() == 6.6);
#endif

	data.clearHistory();
	assert(data.size() == 1);
	assert(data.getValue() == -.7);
	assert(data.getHistoricValue(0) == -.7);
#ifdef	STATISTIC_OF_HISTORY_ONLY
	assert(data.getAverage() == Near(-.7/1));
	assert(data.getMinimum() == -.7);
	assert(data.getMaximum() == -.7);
#else
	assert(data.getAverage() == Near(22.4/8));
	assert(data.getMinimum() == -.7);
	assert(data.getMaximum() == 6.6);
#endif

	std::cout << "ALL TESTS PASSED" << std::endl;
}
