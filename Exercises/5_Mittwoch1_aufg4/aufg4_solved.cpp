/*
 ================================================================================
 Print all permutations of words in a sentence read from standard input
 ================================================================================
*/
#include <algorithm>
	using std::copy;
	using std::next_permutation;
	using std::sort;
#include <cstddef>
	using std::size_t;
#include <iomanip>
	using std::setw;
#include <iostream>
	using std::cin;
	using std::cout;
	using std::endl;
	using std::istream;
	using std::ostream;
#include <iterator>
	// using std::back_inserter;
	// Note that std::back_inserter gets used below but as an ARGUMENT to
	// std::copy. Therefore search includes the namespace std anyway and an
	// explicit using statement is not necessary (but also will not hurt).
	using std::istream_iterator;
	using std::ostream_iterator;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

void aufg4_demo(istream& in, ostream &out) {
	vector<string> words;
	int line = 0;
	copy(
		istream_iterator<string>(in),
		istream_iterator<string>(),
		back_inserter(words)
	     // ^^^^^^^^^^^^^^^^^^^^------ a shorthand for:
	     // back_insert_iterator<vector<string>>(words)
	     // (Using the back_inserter is more convenient as the class which it
	     // returns, because the type would have to be supplied redundantly.)
	);

	// As an alternative to sorting the words supplied as input the sequence could
	// be stored in a temporary and the loop executed until the starting state is
	// reached again:
	//
	const vector<string> wstart(words);
	do {
		out << setw(2) << ++line << ": ";
		copy(words.begin(), words.end(), ostream_iterator<string>(out, " "));
		out << endl;
		next_permutation(words.begin(), words.end());
	} while (words != wstart);
}

#define TDD
#ifndef TDD

int main() {
	aufg4_demo(cin, cout);
}

#else

#include <cassert>
#include <sstream>
using namespace std;

void test_one_word() {
	istringstream prepared_input("hello");
	ostringstream expected_output;
	aufg4_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: hello \n");
}

void test_two_words() {
	istringstream prepared_input("hello world");
	ostringstream expected_output;
	aufg4_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: hello world \n"
	                                " 2: world hello \n");
}

void test_three_words_all_different() {
	istringstream prepared_input("one two three");
	ostringstream expected_output;
	aufg4_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: one two three \n"
	                                " 2: three one two \n"
                                        " 3: three two one \n"
                                        " 4: two one three \n"
                                        " 5: two three one \n"
                                        " 6: one three two \n");
}

void test_three_words_all_same() {
	istringstream prepared_input("one one one");
	ostringstream expected_output;
	aufg4_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: one one one \n");
}

void test_three_words_two_same() {
	istringstream prepared_input("one two one");
	ostringstream expected_output;
	aufg4_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: one two one \n"
			                " 2: two one one \n"
			                " 3: one one two \n");
}

int main() {
	test_one_word();
	test_two_words();
	test_three_words_all_different();
	test_three_words_all_same();
	test_three_words_two_same();

	cout << "** ALL TESTS PASSED" << endl;
}
#endif
