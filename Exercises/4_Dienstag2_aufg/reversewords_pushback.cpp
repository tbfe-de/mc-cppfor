#include <iostream>
#include <string>
#include <vector>

void reverseWords(std::istream& in, std::ostream& out) {
	using std::string;
	using std::vector;

	vector<string> wordlist;

	string word;
	while (in >> word)
		wordlist.push_back(word);
	for (vector<string>::size_type i = wordlist.size(); i > 0;)
		out << wordlist.at(--i) << '\n';
}

#include "reversewords.iodrive"
