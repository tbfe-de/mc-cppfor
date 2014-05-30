#include <cstddef>
#include <iostream>
#include <string>
#include <list>

void reverseWords(std::istream& in, std::ostream& out) {
	using std::string;
	using std::list;

	list<string> wordlist;
	string word;

	while (in >> word)
		wordlist.push_front(word);
	for (const string w : wordlist)
		out << w << '\n';
}

#include "reversewords.iodrive"
