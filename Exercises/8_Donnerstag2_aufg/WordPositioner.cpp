/*
 ================================================================================
 Print words "in order" according to the position after each word.
 ================================================================================
*/
#include "WordPositioner.h"

#include <sstream>

void WordPositioner::read(std::istream& in) {
	std::string line;
	while (std::getline(in, line)) {
		std::istringstream iss(line);
		std::string w;
		if (std::getline(iss, w, ':')) {
			auto wp(seen.insert(w).first);
			int pos;
			while (iss >> pos)
				words.insert(std::make_pair(pos, wp));
		}
	}
}

void WordPositioner::write(std::ostream& out) const {
	for (auto it = words.begin(); it != words.end();  ++it)
		out << *(it->second) << ' ';
	out << std::endl;
}
