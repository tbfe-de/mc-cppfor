#include <iostream>
#include <string>
#include <map>

void wordCount(std::istream& in, std::ostream& out) {
	using std::map;
	using std::string;

	map<string, int> wordlist;
	string word;

	while (in >> word)
		++wordlist[word];
	for (const auto &w : wordlist)
		out << w.first << ':' << w.second << '\n';
}

#include "wordcount.iodrive"
