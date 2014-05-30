#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void uniqueWords(std::istream& in, std::ostream& out) {
	using std::for_each;
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
	for_each(wordlist.begin(), end,
		[&out](const string& w) {
		out << w << '\n';
	});
}

#include "uniquewords.iodrive"
