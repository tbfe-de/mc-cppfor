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
	for (list<string>::reverse_iterator it = wordlist.rend(); it != wordlist.rbegin();)
		out << *--it << '\n';
}

#include "reversewords.iodrive"

