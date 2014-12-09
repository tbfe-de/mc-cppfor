#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void aufg5_demo(istream &in, ostream &out) {
	// ..........
	// TO-BE-DONE
	// ..........
}

int main() {
	aufg5_demo(cin, cout);
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
		.test("all tests combined")
		// -------------------------------------------------------------------
		.supply_line("hello")
		.expect("  1: hello \n")
		// -------------------------------------------------------------------
		.supply_line("hello world")
		.expect("  1: hello world \n"
		        "  2: world hello \n")
		// -------------------------------------------------------------------
		.supply_line("one two three")
		.expect("  1: one two three \n"
				"  2: three one two \n"
				"  3: three two one \n"
				"  4: two one three \n"
				"  5: two three one \n"
				"  6: one three two \n")
		// -------------------------------------------------------------------
		.supply_line("one one one")
		.expect("  1: one one one \n")
		// -------------------------------------------------------------------
		.supply_line("one two one")
		.expect("  1: one two one \n"
				"  2: two one one \n"
				"  3: one one two \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test_cincout("type lines of words to permutate", aufg5_demo)
		.summarize()
		;

}
#endif
