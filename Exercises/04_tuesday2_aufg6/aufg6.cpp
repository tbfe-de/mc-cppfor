/*
 ==============================================================================
 Count number of elements in int-array that do NOT have the value 0
 ==============================================================================
*/

#include <algorithm>
	using std::count_if;
#include <iostream>
	using std::cin;
	using std::cout;
	using std::endl;
	using std::flush;
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

int aufg6_function(istream&, ostream& out) {
	return count_if(
			data, data+N,
			notNullFunction
	);
}

struct NotNullFunctor {
	bool operator()(int v) const {
        	return (v != 0);
	}
};

int aufg6_functor(istream&, ostream& out) {
	return count_if(
			data, data+N,
			NotNullFunctor()
	);
}

#ifdef __GXX_EXPERIMENTAL_CXX0X__

int aufg6_lambda(istream&, ostream& out) {
	return // ... TO-BE-DONE
}

int aufg6_range_for(istream&, ostream& out) {
	return // ... TO-BE-DONE
}

#endif

int aufg6_index_loop(istream&, ostream& out) {
	return // ... TO-BE-DONE
}

int aufg6_pointer_loop(istream&, ostream& out) {
	return // ... TO-BE-DONE
}

#include <cassert>
int main() {
	unsigned long r;
	// -------------------------------------------------------------
	r = 50uL*1000uL*1000uL;
	cout << r << " repetitions of version with function ..." << flush;
	assert(aufg6_function(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_function(cin, cout));
	cout << " done." << endl;
	// -------------------------------------------------------------
	r = 3000uL*1000uL*1000uL;
	cout << r << " repetitions of version with functor ..." << flush;
	assert(aufg6_functor(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_functor(cin, cout));
	cout << " done." << endl;
	// -------------------------------------------------------------
#ifdef __GXX_EXPERIMENTAL_CXX0X__
	r = 3000uL*1000uL*1000uL;
	cout << r << " repetitions of version with lambda ..." << flush;
	assert(aufg6_lambda(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_lambda(cin, cout));
	cout << " done." << endl;
	// -------------------------------------------------------------
	r = 3000uL*1000uL*1000uL;
	cout << r << " repetitions of version with range for ..." << flush;
	assert(aufg6_range_for(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_range_for(cin, cout));
	cout << " done." << endl;
#endif	// -------------------------------------------------------------
	r = 3000uL*1000uL*1000uL;
	cout << r << " repetitions of version with index loop ..." << flush;
	assert(aufg6_index_loop(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_index_loop(cin, cout));
	cout << " done." << endl;
	// -------------------------------------------------------------
	r = 3000uL*1000uL*1000uL;
	cout << r << " repetitions of version with pointer loop ..." << flush;
	assert(aufg6_pointer_loop(cin, cout) == 14);
	while (r-- > 0) static_cast<void>(aufg6_pointer_loop(cin, cout));
	cout << " done." << endl;
	// -------------------------------------------------------------
}

#if 0
#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		//	.config_no_summary(true)
			.config_estimate_cputime(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and function")
		.run_to_return<int>(14, aufg6_function)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and functor")
		.run_to_return<int>(14, aufg6_functor)

#ifdef __GXX_EXPERIMENTAL_CXX0X__
		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and lambda (new in C++11)")
		.run_to_return<int>(14, aufg6_lambda)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with range-based for loop (new in C++11)")
		.run_to_return<int>(14, aufg6_range_for)
#endif

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with classic index loop")
		.run_to_return<int>(14, aufg6_index_loop)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with classic pointer loop")
		.run_to_return<int>(14, aufg6_pointer_loop)

		.summarize()
		;

}
#endif
