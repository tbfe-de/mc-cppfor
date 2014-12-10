// Integer wortweise einlesen

#include <iostream>
#include <sstream>
#include <string>

int main() {

	std::string line;
	int nr = 0;

	while (std::getline(std::cin, line)) {
		std::istringstream one_line(line);
		int x;
		int sum = 0;
		while (one_line >> x) {
			sum += x;
		}
		std::cout << sum << std::endl;
		if (!one_line.eof()) {
			std::cout << "WARNING: not all values processed!\n";
		}
	}
}
