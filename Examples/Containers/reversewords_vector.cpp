#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

void reverseWords(std::istream& in, std::ostream& out) {
	using std::size_t;
	using std::string;
	using std::vector;

	const size_t MAX = 100;

	vector<string> wordlist;
	size_t filled = 0;
	wordlist.resize(MAX);

	string word;
	while (in >> word && filled < MAX)
		wordlist[filled++] = word;
	for (std::size_t i = filled; i > 0;)
		out << wordlist[--i] << '\n';
}

#include "reversewords.iodrive"
