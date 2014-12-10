/*
 ===============================================================================
 Read Integers from Standard Input until End-Of-File
 ===============================================================================

 This program shows how white space-skipping (as part of reading some builtin
 type or 'std::string' with 'operator>>') is switched of and might then be done
 manually.
*/

#include <iostream>
#include <string>

int my_skipws() {
	int n = 0;
	while (std::cin.peek() == ' '
	    || std::cin.peek() == '\t'
	    || std::cin.peek() == '\n') {
		std::cin.ignore(1);
		++n;
	}
	return n;
}

int main() {

	std::string x;

	std::cin.unsetf(std::ios::skipws);
	while (std::cin >> x) {
		std::cout << x << " followed by " << my_skipws() << " ws-char\n";
	}
}
