/*
 ===============================================================================
 Read Integers from Standard Input until End-Of-File
 ===============================================================================
 All integers read are summed up and the total is printed at the end.

 The problem with testing for the 'eof'-bit is that any bad input will not turn
 on this but the 'fail'-bit. Upon this, the program goes into an endless loop
 because all attempts to read more input are silently ignored.
*/

#include <iostream>
#include <fstream>

int main() {

	int sum = 0;
	int value;

	while (!(std::cin >> value).eof()) {
		sum += value;
	}
	std::cout << sum << std::endl;
}
