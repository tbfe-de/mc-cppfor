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

void aufg4_demo(istream& in, ostream &out) {
	vector<string> words;
	// ..........
	// TO-BE-DONE
	// ..........
}

int main() {
	aufg4_demo(cin, cout);
}

#if 0
#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		// 	.config_quiet_summary(true)
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
#endif
