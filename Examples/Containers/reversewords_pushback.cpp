#include <iostream>
#include <string>
#include <vector>

void reverseWords(std::istream& in, std::ostream& out) {
	using std::string;
	using std::vector;

	vector<string> wordlist;

	string word;
	out << "initially reserved: " << wordlist.capacity() << std::endl;
	while (in >> word) {
		if (wordlist.capacity() == wordlist.size()) {
			wordlist.reserve(wordlist.size() + 5);
		}
		wordlist.push_back(word);
		out << "size now: " << wordlist.size() << std::endl;
		out << "reserved: " << wordlist.capacity() << std::endl;
	}
	out << "size now: " << wordlist.size() << std::endl;
	wordlist.reserve(wordlist.size());
	out << "reserved: " << wordlist.capacity() << std::endl;
	wordlist.shrink_to_fit();
	out << "reserved: " << wordlist.capacity() << std::endl;
	for (vector<string>::size_type i = wordlist.size(); i > 0;)
		out << wordlist.at(--i) << '\n';
}

int main() {
	reverseWords(std::cin, std::cout);
}

//#include "reversewords.iodrive"
