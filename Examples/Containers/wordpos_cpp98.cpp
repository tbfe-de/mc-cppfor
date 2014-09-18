#include <iostream>
#include <string>
#include <map>

void wordPos(std::istream& in, std::ostream& out) {
	using std::make_pair;
	using std::multimap;
	using std::string;

	typedef multimap<string, int> WORDLIST;
	WORDLIST wordlist;
	int pos = 0;

	string word;
	while (in >> word)
		wordlist.insert(make_pair(word, ++pos));
	for (WORDLIST::const_iterator it = wordlist.begin(); it != wordlist.end();) {
		out << it->first << ':';
		WORDLIST::size_type cnt = wordlist.count(it->first);
		while (cnt-- != 0)
			out << ' ' << it++->second;
		out << '\n';
	}
}

#include "wordpos.iodrive"
