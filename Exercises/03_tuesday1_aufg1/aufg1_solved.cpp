/*
 ================================================================================
 Print sorted list of words and their position in input
 ================================================================================
*/
#include <iostream>
	using std::cin;
	using std::cout;
	using std::endl;
	using std::istream;
	using std::ostream;
#include <map>
	using std::map;
#include <string>
	using std::string;
#include <utility>
	using std::pair;
#include <vector>
	using std::vector;

void aufg1_demo(istream &in, ostream &out) {
#if 1
	typedef vector<int> POSLIST;
	typedef map<string, POSLIST> WORDLIST;
#else
	using POSLIST = vector<int>;
	using WORDLIST = map<string, POSLIST>;
#endif

	WORDLIST words;
	string w;
	int pos = 0;

	while (in >> w)
		words[w].push_back(++pos);

#if 1
	for (WORDLIST::const_iterator it = words.begin(); it != words.end(); ++it) {
		out << it->first << ':';
		for (POSLIST::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			out << ' ' << *it2;
		out << endl;
	}
#else
	for (const auto &elem : words ) {
		out << elem.first << ':';
		for (auto ps : elem.second )
			out << ' ' << ps;
		out << endl;
	}
#endif
}

#define TDD
#ifndef TDD
int main() {
	aufg1_demo(cin, cout);
}
#else
#include <cassert>
#include <sstream>
using namespace std;

void test_empty() {
	istringstream prepared_input("");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "");
}

void test_one_word() {
	istringstream prepared_input("one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one: 1\n");
}

void test_two_different_words() {
	istringstream prepared_input("one two");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one: 1\n"
	                                "two: 2\n");
}

void test_two_different_words_reversed() {
	istringstream prepared_input("two one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one: 2\n"
	                                "two: 1\n");
}

void test_two_identical_words() {
	istringstream prepared_input("one one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one: 1 2\n");
}

void test_three_words_one_repeated() {
	istringstream prepared_input("one two one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one: 1 3\n"
	                                "two: 2\n");
}

void test_typical_input() {
	istringstream prepared_input("ist das der satz der "
	                             "dreimal der enthaelt "
	                             "oder ist der satz das "
	                             "nicht");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "das: 2 13\n"
	                                "der: 3 5 7 11\n"
	                                "dreimal: 6\n"
	                                "enthaelt: 8\n"
	                                "ist: 1 10\n"
	                                "nicht: 14\n"
	                                "oder: 9\n"
	                                "satz: 4 12\n");
}

int main() {
	test_empty();
	test_one_word();
	test_two_different_words();
	test_two_different_words_reversed();
	test_two_identical_words();
	test_typical_input();
	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
