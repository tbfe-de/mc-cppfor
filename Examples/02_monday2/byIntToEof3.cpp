/*
 ===============================================================================
 Read Integers from Standard Input until End-Of-File
 ===============================================================================
 All integers read are summed up and the total is printed at the end.

 To avoid the problem that any bad input turns a loop reading from a stream into
 an endless loop, it is usually preferable to test for the'good'-state - what in
 effect means that none of 'failbit', 'eofbit', or 'badbit' is set.
*/

#include <iostream>

int main() {

	int x;
	int sum = 0;

	while (std::cin >> x) {
		sum += x;
	}
	std::cout << sum << std::endl;
}
