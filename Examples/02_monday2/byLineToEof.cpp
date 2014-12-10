/*
 ===============================================================================
 Read Whole Lines from 'std::cin'
 ===============================================================================
 Lines are read one by one from 'std::cin' and directly shown on 'std::cout'
 with a line number added before the content.
*/

#include <iostream>
#include <string>

int main() {

	std::string line;
	int nr = 0;

	while (std::getline(std::cin, line)) {
		std::cout << ++nr << '\t' << line << '\n';		
	}
}
