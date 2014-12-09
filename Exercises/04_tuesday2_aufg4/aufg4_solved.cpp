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
		out << setw(3) << ++line << ": ";
		copy(words.begin(), words.end(), ostream_iterator<string>(out, " "));
		out << endl;
		next_permutation(words.begin(), words.end());
	} while (words != wstart);
}

#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		// 	.config_no_summary(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("one word")
		// -------------------------------------------------------------------
		.supply("hello")
		.expect("  1: hello \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("two words")
		// -------------------------------------------------------------------
		.supply("hello world")
		.expect("  1: hello world \n")
		.expect("  2: world hello \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("three words (all different")
		// -------------------------------------------------------------------
		.supply("one two three")
		.expect("  1: one two three \n"
				"  2: three one two \n"
				"  3: three two one \n"
				"  4: two one three \n"
				"  5: two three one \n"
				"  6: one three two \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("three words (all same)")
		// -------------------------------------------------------------------
		.supply("one one one")
		.expect("  1: one one one \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("three words (two same)")
		// -------------------------------------------------------------------
		.supply("one two one")
		.expect("  1: one two one \n"
			"  2: two one one \n"
			"  3: one one two \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test_cincout("type words to permutate", aufg4_demo)
		.summarize()
		;

}
