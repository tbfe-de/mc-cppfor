/*
 ===============================================================
 Calulate Sum of Values (Taken as Input from Keyboard)
 ===============================================================
*/

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
#include <boost/regex.hpp>
using namespace boost::regex;

double sum = 0.0;

bool prompt_get(std::string &userinput) {
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << setw(6) << sum << ":  ";
	if (!getline(cin, userinput).good())
		return false;
	userinput = regex_replace(userinput, "^[ \t](.*)", "\\1");
	userinput = regex_replace(userinput, "(.*?)[ \t]$", "\\1");
	return true;
}

int main() {
	string line;
	while (prompt_get(line)) {
		istringstream iss(line + " ");
		double v;
		if (line == ".")
			break;
		else if (line == "*")
			sum = 0.0;
		else if ((iss >> v >> ws).eof()) {
			if (static_cast<long long>(100*v) != 100*v)
				cout << "some decimal digits truncated\n";
			sum += v;
		}
		else {
			if (line != "?")
				cout << "bad input: " << line << "<\n";
			cout << "type a double value\n"
			     << "or '*' to clear sum\n"
			     << "or '.' to exit\n\n";
		}
	}
}
