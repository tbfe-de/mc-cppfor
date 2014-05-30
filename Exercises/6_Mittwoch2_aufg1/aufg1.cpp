/*
 ==============================================================================
 Remove all duplicated strings from input - no matter where they appear
 ==============================================================================
*/
#include <iterator>
#include <set>
#include <string>

void real_unique_copy(
	std::istream_iterator<std::string> beg,	// read string-s from stream
	std::istream_iterator<std::string> end,	// ... until 'end-of-file'
	std::ostream_iterator<std::string> dest	// write result to stream
) {
	// ..........
	// TO-BE-DONE
	// ..........
}

#include <iostream>

void aufg1_demo(std::istream& in, std::ostream& out) {
	real_unique_copy(
		std::istream_iterator<std::string>(in),
		std::istream_iterator<std::string>(),
		std::ostream_iterator<std::string>(out, " ")
	);
}

#ifndef TDD

int main() {
	aufg1_demo(std::cin, std::cout);
}

#else

#include <cassert>
#include <sstream>
using namespace std;

void test_empty_stream() {
	istringstream prepared_input("");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "");
}

void test_one_item() {
	istringstream prepared_input("one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one ");
}

void test_two_items_no_duplicates() {
	istringstream prepared_input("one two");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one two ");
}

void test_two_items_reversed_no_duplicates() {
	istringstream prepared_input("two one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "two one ");
}

void test_many_items_some_duplicates() {
	istringstream prepared_input("one two one two two three one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one two three ");
}

void test_many_items_all_duplicates() {
	istringstream prepared_input("one one one one one one one");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "one ");
}

int main() {
	test_empty_stream();
	test_one_item();
	test_two_items_no_duplicates();
	test_two_items_reversed_no_duplicates();
	test_many_items_some_duplicates();
	test_many_items_all_duplicates();

	std::cout << "** ALL TESTS PASSED **" << std::endl;
}

#endif
