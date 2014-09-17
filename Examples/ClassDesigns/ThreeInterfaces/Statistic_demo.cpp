/*
 ===============================================================
 Demo-Program for Class Statistic
 ===============================================================
*/
#include "Statistic.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string showHistory(IValue &r) {
	ostringstream os;
	int i = r.historySize();
	while (--i > 0)
		os << ": " <<  r.getHistoricValue(i) << '\n';
	os << "= " << r.getValue();
	return os.str();
}

string showAverage(IAverage &r) {
	ostringstream os;
	os << "ø " << r.getAverage();
	return os.str();
};

string showExtrema(IExtrema &r) {
	ostringstream os;
	os << r.getMinimum() << " … " << r.getMaximum();
	return os.str();
};

Statistic data(0.0);

bool prompt_get(string &ln) {
	if (cin) {
		cout << showHistory(data)
			  << " [ " << showAverage(data)
			  << " / " << showExtrema(data) << " ] "
			  << flush;
		cin >> ln;
	}
	return cin.good();
}
	
int main() {
	string line;
	while (prompt_get(line)) {
		if (line == ".")
			data.clearHistory();
		else
			data.setValue(stod(line));
	}
}
