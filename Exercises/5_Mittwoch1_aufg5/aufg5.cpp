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
