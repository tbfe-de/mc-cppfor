/*
 ================================================================================
 Print all permutations of a simple test sentence
 ================================================================================
*/
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

void aufg3_demo(istream&, ostream &cout) {
	// Automatically calculating the size as value of N below allows to use
	// a different number of initializers without requiring other changes to
	// the program.
	//
	string words[] = { "das", "ist", "mein", "haus" };
	const size_t N = sizeof words / sizeof words[0];

	// ..........
	// TO-BE-DONE
	// ..........

}

int main() {
	aufg3_demo(cin, cout);
}

#if 0
#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		 	.config_quiet_summary(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("permutate: 'das ist mein haus'")
		.expect("  1: das haus ist mein \n"
				"  2: das haus mein ist \n"
				"  3: das ist haus mein \n"
				"  4: das ist mein haus \n"
				"  5: das mein haus ist \n"
				"  6: das mein ist haus \n"
				"  7: haus das ist mein \n"
				"  8: haus das mein ist \n"
				"  9: haus ist das mein \n"
				" 10: haus ist mein das \n"
				" 11: haus mein das ist \n"
				" 12: haus mein ist das \n"
				" 13: ist das haus mein \n"
				" 14: ist das mein haus \n"
				" 15: ist haus das mein \n"
				" 16: ist haus mein das \n"
				" 17: ist mein das haus \n"
				" 18: ist mein haus das \n"
				" 19: mein das haus ist \n"
				" 20: mein das ist haus \n"
				" 21: mein haus das ist \n"
				" 22: mein haus ist das \n"
				" 23: mein ist das haus \n"
				" 24: mein ist haus das \n")
		.run_to_return(aufg3_demo)
		.summarize()
		;

}
#endif
