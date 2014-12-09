/*
 ================================================================================
 Print sorted list of words and their position in input
 ================================================================================
*/

#include <iostream>
#include <map>
#include <vector>
// ... may be more
// ... #includes ?

void aufg1_demo(istream &in, ostream &out) {
	typedef std::vector<int> POSLIST;
	typedef std::map<string, POSLIST> WORDLIST;

	// ..........
	// TO-BE-DONE
	// ..........

	while (in >> w) {
		// ... TO-BE-DONE ...
	}

	for (WORDLIST::const_iterator it(words.begin()); it != words.end(); ++it) {
		// ..........
		// TO-BE-DONE
		// ..........
	}
}

int main() {
	aufg1_demo(cin, cout)
}

#if 0
#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		//	.config_no_summary(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("realistic example")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("ist das der satz der dreimal der enthaelt "
				     "oder ist der satz das nicht")
		.expect_line("========== Output:")
		.expect_line("das: 2 13")
		.expect_line("der: 3 5 7 11")
		.expect_line("dreimal: 6")
		.expect_line("enthaelt: 8")
		.expect_line("ist: 1 10")
		.expect_line("nicht: 14")
		.expect_line("oder: 9")
		.expect_line("satz: 4 12")
		.expect_line("==========")
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("empty input")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("")
		.expect_line("========== Output:")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("single word")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("hello")
		.expect_line("========== Output:")
		.expect_line("hello: 1")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("same word repeated")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("hello hello hello hello")
		.expect_line("========== Output:")
		.expect_line("hello: 1 2 3 4")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("words repeated mixed")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("hello world hello world hello world hello world")
		.expect_line("========== Output:")
		.expect_line("hello: 1 3 5 7")
		.expect_line("world: 2 4 6 8")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("words repeated unmixed")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("hello hello hello hello world world world world")
		.expect_line("========== Output:")
		.expect_line("hello: 1 2 3 4")
		.expect_line("world: 5 6 7 8")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type words to list positions", aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}
#endif
