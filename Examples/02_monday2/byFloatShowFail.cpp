/*
 ===============================================================================
 Read Single Lines from Standard Input, then Read 'float'-s from the Lines
 ===============================================================================

 This program should help to understand under which circumstances the state-bits
 (indicating end-of-file or some problem) are set and what the remaining content
 is (which can be retrieved after clearing the state to be 'good' again).
*/

#include <iostream>
	using std::cin;
	using std::cout;
#include <sstream>
#include <string>

int main() {

	std::string line;
	int lnr = 0;
	while (std::getline(cin, line)) {
		std::istringstream iss(line);
		float x;
		cout << "from stringstream holding line " << ++lnr << ":\n";
		while (iss >> x) {
			cout << "= read " << x << '\n';
		}
		if (iss.eof()) {
			cout << "+ found 'eofbit' set\n";
		}
		if (iss.bad()) {
			cout << "+ found 'badbit' set\n";
		}
		if (iss.fail()) {
			cout << "+ found 'failbit' set\n"
                             << "- remaining content |";
			iss.clear();
#if 1
			// manually copy char by char what remains
			char ch; while (iss.get(ch)) cout.put(ch); cout << "|\n";
#else
			cout << iss.rdbuf() << "|\n";
#endif
		}
	}
}
