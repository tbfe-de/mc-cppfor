/*
 ================================================================================
 Print words "in order" from output of previous exercise
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
	using std::make_pair;
#include <sstream>
	using std::istringstream;
#include <string>
	using std::string;

void aufg2_demo(istream &in, ostream &out) {
	typedef map<int, string> WORDMAP;
	WORDMAP words;

	string line;
	while (getline(in, line)) {
		istringstream iss(line);
		string w;
		if (getline(iss, w, ':')) {
			int pos;
			while (iss >> pos)
				words.insert(make_pair(pos, w));
				// is slightly more efficient as:
				// words[pos] = w;
		}
	}
#if 0
	for (auto it = words.begin(); it != words.end(); ++it)
		out << it->second << ' ';
#else
	for (auto &e : words)
		out << e.second << ' ';
		// out << (&e)->second << ' ';
#endif
	out << endl;
}

// #define TDD
#ifndef TDD
int main() {
	aufg2_demo(cin, cout);
}
#else

#include <cassert>
#include <sstream>
using namespace std;

void test_empty() {
	istringstream prepared_input("");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "\n");
}

void test_one_word() {
	istringstream prepared_input("one: 1");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one \n");
}

void test_two_different_words() {
	istringstream prepared_input("one: 1\n"
	                             "two: 2\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one two \n");
}

void test_two_different_words_reversed() {
	istringstream prepared_input("one: 2\n"
	                             "two: 1\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "two one \n");
}

void test_two_identical_words() {
	istringstream prepared_input("one: 1 2\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one one \n");
}

void test_three_words_one_repeated() {
	istringstream prepared_input("one: 1 3\n"
	                             "two: 2\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one two one \n");
}

void test_typical_input() {
	istringstream prepared_input("das: 2 13\n"
	                             "der: 3 5 7 11\n"
	                             "dreimal: 6\n"
	                             "enthaelt: 8\n"
	                             "ist: 1 10\n"
	                             "nicht: 14\n"
	                             "oder: 9\n"
	                             "satz: 4 12\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "ist das der satz der "
	                                "dreimal der enthaelt "
	                                "oder ist der satz das "
	                                "nicht \n");
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
