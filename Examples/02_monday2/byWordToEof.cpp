/*
 ===============================================================================
 Read Words from 'std::cin'
 ===============================================================================

 Words are read one by one from 'std::cin' and directly shown on 'std::cout',
 each one in a line by its own and with a number and a colon added before.

 Note: differently from the example which read 'int'-s here is no danger the
 stream could switch to 'fail'-state; therefore testing for the 'eof'-bit is
 sufficient and OK, but as well all the test could be omitted and the reading
 loop written in the usual style as 'while (cin >> w) ...'.
*/

// Strings wortweise einlesen

#include <iostream>
#include <string>

int main() {

	std::string w;
	int n = 1;

	while (!(std::cin >> w).eof()) {
		std::cout << n++ << ": " << w << '\n';
	}
}
