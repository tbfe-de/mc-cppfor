/*
 ==============================================================================
 Count number of elements in int-array that do NOT have the value 0
 ==============================================================================
*/

#include <algorithm>
	using std::count_if;
#include <iostream>
	using std::cout;
	using std::istream;
	using std::ostream;

const int data[] = {
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3
};
const size_t N = sizeof data / sizeof data[0];

bool notNullFunction(int v) {
   	return (v != 0);
}

int aufg1_function(istream&, ostream&) {
	return count_if(
			data, data+N,
			notNullFunction
	);
}

struct NotNullFunctor {
	// ...
	// TO-BE-DONE
	// ...
};

int aufg1_functor(istream&, ostream&) {
	return count_if(
			data, data+N,
			// ... TO-BE-DONE ...
	);
}

int main() {
	cout << "with function:" << aufg1_function(cin, cout) << endl;
	cout << "with functor:" << aufg1_functor(cin, cout) << endl;
}

#if 0
#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		//	.config_no_summary(true)
		//	.config_estimate_cputime(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and function")
		.run_to_return<int>(14, aufg1_function)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and functor")
		.run_to_return<int>(14, aufg1_functor)

		.summarize()
		;

}
#endif
