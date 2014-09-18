#include <iostream>
#include <string>
#include <set>

void uniqueWords(std::istream& in, std::ostream& out) {
	using std::string;
	using std::set;

	set<string> wordlist;
	string word;

	while (in >> word)
		wordlist.insert(word);
	for (const string w : wordlist)
		out << w << '\n';
}

#include "uniquewords.iodrive"
