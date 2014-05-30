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
	for (const auto &v : wordlist) {
		out << v.first << ':';
		for (const auto v2 : v.second)
			out << ' ' << v2;
		out << '\n';
	}
}

#include "wordpos.iodrive"
