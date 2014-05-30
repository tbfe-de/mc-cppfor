#include <cstddef>
#include <iostream>
#include <string>

void reverseWords(std::istream& cin, std::ostream& cout) {
	using std::size_t;
	using std::string;

	const size_t MAX = 100;
	string wordlist[MAX];
	size_t filled = 0;

	string word;
	while (cin >> word && filled < MAX)
		wordlist[filled++] = word;
	for (std::size_t i = filled; i > 0;)
		cout << wordlist[--i] << '\n';
}

#include "reversewords.iodrive"
