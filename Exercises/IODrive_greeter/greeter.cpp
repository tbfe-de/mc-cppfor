#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

int greeter(istream &in, ostream& out) {
	string line;
	int ngreets = 0;
	if (in.fail()) {
		throw runtime_error("greeter: 'in' fail-state at start");
	}
	if (in.eof()) {
		throw runtime_error("greeter: 'in' eof-state at start");
	}
	while (getline(in, line)) {
		istringstream iss(line);
		string name;
		if (iss >> name) {
			out << "hello " << name;
			++ngreets;
			while (iss >> name) {
				out << " and " << name;
				++ngreets;
			}
		}
		out << endl;
	}
	if (ngreets == 0) {
		out << "... hmm, nobody here?" << endl;
	}
	if (!out.good()) {
		throw runtime_error("greeter: 'out' not good-state at end");
	}
	return ngreets;
}

#include "IODrive.h"

int main(int argc, char* argv[]) {
	return IODrive(cout)
	//	.config_details_uncond(true)
		.config_estimate_cputime(true)
	//	.config_titles_only(true)
	//	.config_summary_only(true)
	//	.config_no_summary(true)
	//	.config_failure_stop(true)
	//	.config_interactive_mode(true)
	//	.config_page_output(true)
	//	.config_line_length(60)
		.config(argc, argv)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("empty input")
	// ---------------------------------------------------------------------------------------
	.expect("... hmm, nobody here?\n")
	.run_to_return(greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("one name")
	// ---------------------------------------------------------------------------------------
	.supply("martin")
	.expect("hello martin\n")
	.run_to_return(greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("one name plus newline")
	// ---------------------------------------------------------------------------------------
	.supply_line("martin")
//	.expect_line("hello Martin")
	.expect_line("hello martin")
	.run_to_return(greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("two names in single line")
	// ---------------------------------------------------------------------------------------
	.supply("eva maria\n")
	.expect("hello eva and maria\n")
//	.run_to_return<int>(3, greeter)
	.run_to_return<int>(2, greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("two names in separate lines")
	// ---------------------------------------------------------------------------------------
	.supply("eva"		"\n"
		"maria"		"\n")
	.expect("hello eva"	"\n"
		"hello maria"	"\n")
	.run_to_return<int>(2, greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("two names in separate lines - alternative")
	// ---------------------------------------------------------------------------------------
	.supply_line("eva")
	.supply_line("maria")
//	.expect_line("hello Eva")
	.expect_line("hello eva")
//	.expect_line("hello Maria")
	.expect_line("hello maria")
	.run_to_return<int>(2, greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("two names in separate lines - correct intermingling")
	// ---------------------------------------------------------------------------------------
	.supply_line("eva")
	.expect_line("hello eva")
	.supply_line("maria")
	.expect_line("hello maria")
	.run_to_return<int>(2, greeter)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("start with bad input")
	// ---------------------------------------------------------------------------------------
	.supply_fail()
//	.run_to_return(greeter)
//  	.run_to_throw<std::logic_error>("greeter: 'in' fail-state at start", greeter)
//  	.run_to_throw<std::runtime_error>("greeter: 'in' fail state at start", greeter)
  	.run_to_throw<std::runtime_error>("greeter: 'in' fail-state at start", greeter)

  	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.test_cincout("direct input", greeter)	// ... just in case
	.summarize();
}
