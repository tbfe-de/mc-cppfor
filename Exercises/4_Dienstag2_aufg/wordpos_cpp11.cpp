#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <map>

void wordPos(std::istream& in, std::ostream& out) {
	using std::for_each;
	using std::get;
	using std::make_pair;
	using std::multimap;
	using std::pair;
	using std::string;
	using std::tuple;

	multimap<string, int> wordlist;
	int pos = 0;
	string word;

	while (in >> word)
		wordlist.insert(make_pair(word, ++pos));
	bool initial = true;
	for_each(wordlist.begin(), wordlist.end(),
		[&](const pair<string, int>& elem) {
			if (initial)
				out << (word = elem.first) << ':', initial = false;
			else if (word != elem.first)
				out << '\n' << (word = elem.first) << ':';
			out << ' ' << elem.second;
	});
	if (!initial)
		out << '\n';
}

#include "wordpos.iodrive"
