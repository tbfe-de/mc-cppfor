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
	for (map<string, int>::const_iterator it = wordlist.begin(); it != wordlist.end(); ++it)
		out << it->first << ':' << it->second << '\n';
}

#include "wordcount.iodrive"
