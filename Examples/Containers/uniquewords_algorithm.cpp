#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void uniqueWords(std::istream& in, std::ostream& out) {
	using std::sort;
	using std::string;
	using std::unique;
	using std::vector;

	vector<string> wordlist;

	string word;
	while (in >> word)
		wordlist.push_back(word);
	sort(wordlist.begin(), wordlist.end());
	const auto end = unique(wordlist.begin(), wordlist.end());
     //	wordlist.resize(end - wordlist.begin());
	for (auto it = wordlist.begin(); it != end; ++it)
		out << *it << '\n';
}

#include "uniquewords.iodrive"
