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
			out << setw(2) << ++line << ": ";
			copy(words.begin(), words.end(), ostream_iterator<string>(out, " "));
			out << endl;
			next_permutation(words.begin(), words.end());
		} while (words != wstart);
		out << "---\n";
	}
}

#define TDD
#ifndef TDD

int main() {
	aufg5_demo(cin, cout);
}

#else
#include <cassert>
#include <sstream>
using namespace std;

int main() {

	istringstream prepared_input("hello\n"
	                             "hello world\n"
	                             "one two three\n"
	                             "one one one\n"
	                             "one two one\n");
	ostringstream expected_output;
	aufg5_demo(prepared_input, expected_output);
	assert(expected_output.str() == " 1: hello \n"
	                                "---\n"
	                                " 1: hello world \n"
	                                " 2: world hello \n"
	                                "---\n"
	                                " 1: one two three \n"
	                                " 2: three one two \n"
                                        " 3: three two one \n"
                                        " 4: two one three \n"
                                        " 5: two three one \n"
                                        " 6: one three two \n"
	                                "---\n"
	                                " 1: one one one \n"
	                                "---\n"
	                                " 1: one two one \n"
			                " 2: two one one \n"
			                " 3: one one two \n"
	                                "---\n");

	cout << "** TEST PASSED **" << endl;
}

#endif
