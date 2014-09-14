/*
 ===============================================================
 Test Value Class Interactively
 ===============================================================
*/
#include "Value.h"

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

Value tval;

bool prompt_get(std::string &userinput) {
	cout << '[';
	if (tval.size() > 0) {
		cout << tval.getHistoricValue();
		for (int i = 1; i < tval.size(); ++i)
			cout << ' ' << tval.getHistoricValue(i);
	}
	cout << ']' << ' ' << ' ';
	return getline(cin, userinput);
}

int main() {
	string line;
	while (prompt_get(line)) {
		istringstream iss(line);
		double v;
		if (line == ".")
			break;
		else if (line == "-")
			tval.clear();
		else if (iss >> v)
			tval.setValue(v);
		else 
			cout << "type a double value\n"
			     << "or '-' to clear history\n"
			     << "or '.' to exit\n\n";
	}

}
	
