/*
 ================================================================================
 Print all permutations of words in a sentence read from standard input
 ================================================================================
*/
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

void aufg4_demo(istream &in, ostream &out) {
	vector<string> words;
	// ..........
	// TO-BE-DONE
	// ..........
}

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
