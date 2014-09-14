/*
 ===============================================================
 Calulate Sum of Values (Taken as Input from Keyboard)
 ===============================================================
*/

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

double sum = 0.0;

bool prompt_get(std::string &userinput) {
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << setw(6) << sum << ":  ";
	return getline(cin, userinput);
}

int main() {
	string line;
	while (prompt_get(line)) {
		istringstream iss(line);
		double v;
		if (line == ".")
			break;
		else if (line == "*")
			sum = 0.0;
		else if (iss >> v)
			sum += v;
		else {
			if (line != "?")
				cout << "bad input: " << line << "<\n";
			cout << "type a double value\n"
			     << "or '*' to clear sum\n"
			     << "or '.' to exit\n\n";
		}
	}
}
