#include <iostream>
#include <map>
#include <string>
#include <vector>

void wordPos(std::istream& in, std::ostream& out) {
	using std::map;
	using std::string;
	using std::vector;

	typedef vector<int> POSLIST;
	typedef map<string, POSLIST> WORDLIST;
	WORDLIST wordlist;
	int pos = 0;

	string word;
	while (in >> word)
		wordlist[word].push_back(++pos);
	for (WORDLIST::const_iterator it = wordlist.begin();
				      it != wordlist.end(); ++it) {
		out << it->first << ':';
		for (POSLIST::const_iterator it2 = it->second.begin();
					     it2 != it->second.end(); ++it2)
			out << ' ' << *it2;
		out << '\n';
	}
}

#include "wordpos.iodrive"
