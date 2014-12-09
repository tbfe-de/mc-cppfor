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
	using std::getline;
	using std::istream;
	using std::ostream;
#include <iterator>
	using std::back_inserter;
	using std::istream_iterator;
	using std::ostream_iterator;
#include <sstream>
	using std::istringstream;
#include <string>
	using std::string;
#include <vector>
	using std::vector;

void aufg5_demo(istream &in, ostream &out) {
	string zeile;

	// read full line(s) in outer loop ...
	//
	while (getline(in, zeile)) {
		// ... turn (single) line into another stream ...
		istringstream iss(zeile);

		vector<string> words; // (created by default-C'tor => initially empty)

		// ... fill vector of words from this stream (i.e. the line read) ...
		copy(
			istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(words)
		);

		// ... remembers start configuration ...
		const vector<string> wstart(words);

		// ... and finally shows all permutations of words (sequentially numbered).
		int line = 0;
		do {
			out << setw(3) << ++line << ": ";
			copy(words.begin(), words.end(), ostream_iterator<string>(out, " "));
			out << endl;
			next_permutation(words.begin(), words.end());
		} while (words != wstart);
	}
}

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
		.test("one single world")
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
