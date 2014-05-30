#include <iostream>
using namespace std;

#include "stack_data.h"

void stack_demo(istream &in, ostream &out) {
	Stack ivs; // store int-values here
	Stack dvs; // store double-values here

	out << "========== Input:" << endl;
	double dval;
	while (in >> dval) {
		int ival = static_cast<int>(dval);
		if (dval == static_cast<double>(ival))
			ivs.push(new Int_Node(ival));
		else
			dvs.push(new Double_Node(dval));
	}

	out << "========== Output:" << endl;
	Stack::Node *np;
	while ((np = ivs.pop()) != 0) {
		np->print(out);
		out << ' ';
		delete np;
	}
	out << endl;
	while ((np = dvs.pop()) != 0) {
		np->print(out);
		out << ' ';
		delete np;
	}
	out << endl;

	out << "==========" << endl;
}


#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(std::cout)
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
		// Typical test with just some (randomly invented) values.
		//
		.test("realistic example")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 2.2 3.1 4 .56 7 8")
		.expect_line("========== Output:")
		.expect_line("8 7 4 1 ")
		.expect_line("0.56 3.1 2.2 ")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Border case with no input supplied.
		//
		.test("empty input")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("")
		.expect_line("========== Output:")
		.expect_line("")
		.expect_line("")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single number.
		//
		.test("one integer")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1")
		.expect_line("========== Output:")
		.expect_line("1 ")
		.expect_line("")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single string.
		//
		.test("one double")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("2.2")
		.expect_line("========== Output:")
		.expect_line("")
		.expect_line("2.2 ")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Double followed by integer.
		//
		.test("integer and string")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1 2")
		.expect_line("========== Output:")
		.expect_line("2 ")
		.expect_line("1.1 ")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Integer followed by double.
		//
		.test("string and number")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 2.2")
		.expect_line("========== Output:")
		.expect_line("1 ")
		.expect_line("2.2 ")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Integers only.
		//
		.test("some integers")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 2 3 4")
		.expect_line("========== Output:")
		.expect_line("4 3 2 1 ")
		.expect_line("")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Strings only.
		//
		.test("some doubles")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line(".1 .2 .3 .4")
		.expect_line("========== Output:")
		.expect_line("")
		.expect_line("0.4 0.3 0.2 0.1 ")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type int-s and double-s", stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}

