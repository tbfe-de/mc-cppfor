/*
 ================================================================================
 Print all permutations of a simple test sentence
 ================================================================================
*/
#include <algorithm>
	using std::copy;
	using std::next_permutation;
	using std::sort;
#include <cstddef>
	using std::size_t;
#include <cstring>
	using std::strcmp;
#include <iomanip>
	using std::setw;
#include <iostream>
	using std::cin;
	using std::cout;
	using std::endl;
	using std::istream;
	using std::ostream;
#include <iterator>
	using std::ostream_iterator;
#include <string>
	using std::string;

void aufg3_demo(ostream &out) {
	// Automatically calculating the size as value of N below allows to use
	// a different number of initializers without requiring other changes to
	// the program.
	//
	string words[] = { "das", "ist", "mein", "haus" };
	const size_t N = sizeof words / sizeof words[0];

	// Only if the data is sorted, the loop controlled by the return value
	// of std::next_permutation will show ALL 24 values.
	//
	sort(&words[0], &words[N]);

	int line = 0;
	do {
		out << setw(2) << ++line << ": ";
		copy(&words[0], &words[N], ostream_iterator<string>(out, " "));
		out << endl;
	} while (next_permutation(&words[0], &words[N]));
}

bool classicStringCompare(const char *lhs, const char *rhs) {
	return (strcmp(lhs, rhs) < 0);
}

void aufg3x_demo(ostream &out) {
	// Now assume the container of words is not an array of string (class) objects but
	// character pointers, then we need a TWO calls to 'strcmp' for comparisions ...
	//
	const char *words[] = { "das", "ist", "mein", "haus" };
	const size_t N = sizeof words / sizeof words[0];

	// ... first here ---------vvvvvvvvvvvvvvvvvvvv ...
	sort(&words[0], &words[N] /*, classicStringCompare*/);

	int line = 0;
	do {
		out << setw(2) << ++line << ": ";
		copy(&words[0], &words[N], ostream_iterator<string>(out, " "));
		out << endl;
		// ... second here ---------------------vvvvvvvvvvvvvvvvvvvv
	} while (next_permutation(&words[0], &words[N], classicStringCompare));
}

//#define TDD
#ifndef TDD

int main() {
	aufg3x_demo(cout);
}

#else

#include <cassert>
#include <sstream>

int main() {
	using namespace std;
	ostringstream expected_output;
	aufg3_demo(expected_output);
	assert(expected_output.str() == " 1: das haus ist mein \n"
                                        " 2: das haus mein ist \n"
                                        " 3: das ist haus mein \n"
                                        " 4: das ist mein haus \n"
                                        " 5: das mein haus ist \n"
                                        " 6: das mein ist haus \n"
                                        " 7: haus das ist mein \n"
                                        " 8: haus das mein ist \n"
                                        " 9: haus ist das mein \n"
                                        "10: haus ist mein das \n"
                                        "11: haus mein das ist \n"
                                        "12: haus mein ist das \n"
                                        "13: ist das haus mein \n"
                                        "14: ist das mein haus \n"
                                        "15: ist haus das mein \n"
                                        "16: ist haus mein das \n"
                                        "17: ist mein das haus \n"
                                        "18: ist mein haus das \n"
                                        "19: mein das haus ist \n"
                                        "20: mein das ist haus \n"
                                        "21: mein haus das ist \n"
                                        "22: mein haus ist das \n"
                                        "23: mein ist das haus \n"
                                        "24: mein ist haus das \n");

	cout << "** TEST PASSED **" << endl;
}
#endif
