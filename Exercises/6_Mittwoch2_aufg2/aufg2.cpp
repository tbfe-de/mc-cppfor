/*
 ==============================================================================
 Remove all duplicated strings from input - no matter where they appear
 ==============================================================================
*/
#include <iterator>
#include <set>
#include <string>

// ... TO-BE-DONE ...
void real_unique_copy(
	// ..........
	// TO-BE-DONE
	// ..........
) {
	std::set<ElemType> known;
	while (beg != end) {
		const ElemType elem = *beg++;	// fulfill "contract" for input iterator
		if (known.insert(elem).second) {
			*dest++ = elem;		// fulfill "contract" for output iterator
		}
	}
}

void aufg1_demo(std::istream& in, std::ostream& out) {
	real_unique_copy(
		std::istream_iterator<std::string>(in),
		std::istream_iterator<std::string>(),
		std::ostream_iterator<std::string>(out, " ")
	);
}

void aufg2_demo(std::istream& in, std::ostream& out) {
	real_unique_copy(
		std::istream_iterator<int>(in),
		std::istream_iterator<int>(),
		std::ostream_iterator<int>(out, " ")
	);
}

#ifndef TDD

int main() {
	aufg1_demo(std::cin, std::cout);
}

#else

#include <cassert>
#include <iostream>
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

void test_some_integers() {
	istringstream prepared_input("1 2 01 02 002 1 3");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "1 2 3 ");
}

void test_some_integers_as_strings() {
	istringstream prepared_input("1 2 01 02 002 1 3");
	ostringstream expected_output;
	aufg1_demo(prepared_input, expected_output);
	assert(expected_output.str() == "1 2 01 02 002 3 ");
}

int main() {
	test_empty_stream();
	test_one_item();
	test_two_items_no_duplicates();
	test_two_items_reversed_no_duplicates();
	test_many_items_some_duplicates();
	test_many_items_all_duplicates();
	test_some_integers();
	test_some_integers_as_strings();

	std::cout << "** ALL TESTS PASSED **" << std::endl;
}

#endif

