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
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3,
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3,
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3,
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3,
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3,
};

const size_t N = sizeof data / sizeof data[0];
//    ...    N = sizeof data / sizeof (int);

bool notNullFunction(int v) {
   	return (v != 0);
}

int aufg1_function(istream&, ostream& out) {
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

int aufg1_functor(istream&, ostream& out) {
	return count_if(
			data, data+N,
			NotNullFunctor()
	);
}

int aufg1_lambda(istream&, ostream& out) {
	return count_if(
			data, data+N,
			[](int v) { return (v != 0); }
	);
}

int compareTo;
bool notSomethingFunction(int v) {
   	return (v != compareTo);
}

int aufg1_function2(istream&, ostream& out) {
	::compareTo = 0; // set the GLOBAL variable!
	return count_if(
			data, data+N,
			notSomethingFunction
	);
}

struct NotSomethingFunctor {
	const int something;
	NotSomethingFunctor(int s) : something(s) {}
	bool operator()(int v) const {
		return (v != something);
	}
};

int aufg1_functor2(istream&, ostream& out) {
	int compareTo = 0; // this is LOCAL to the function!
	return count_if(
			data, data+N,
			NotSomethingFunctor(compareTo)
	);
}

int aufg1_lambda2(istream&, ostream& out) {
	int compareTo = 0;  // again LOCAL to the function!
	return count_if(
			data, data+N,
			[compareTo](int v) { return (v != compareTo); }
	              // ^^^^^^^^^--- locals must be explicitely captured
	);
}

int just_return_70(istream&, ostream& out) {
	return 70;
}

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
		.run_to_return<int>(70, aufg1_function)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and functor")
		.run_to_return<int>(70, aufg1_functor)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and lambda (new in C++11)")
		.run_to_return<int>(70, aufg1_lambda)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and function")
		.run_to_return<int>(70, aufg1_function2)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and functor")
		.run_to_return<int>(70, aufg1_functor2)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("elements not zero with count_if and lambda (new in C++11)")
		.run_to_return<int>(70, aufg1_lambda2)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("dummy (to determine overhead of function call)")
		.run_to_return<int>(70, just_return_70)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize()
		;

}
