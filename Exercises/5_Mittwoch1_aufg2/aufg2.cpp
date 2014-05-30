#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
using namespace std;

void aufg2_demo(istream&, ostream& out) {
	int data[] = {
			1, 2, 3, 4
	};
	// ..........
	// TO-BE-DONE
	// ..........
}

#define TDD
#ifndef TDD

int main() {
	aufg2_demo(cout);
}

#else

#include <cassert>
#include <sstream>

int main() {
	ostringstream expected_output;
	aufg2_demo(expected_output);
	assert(expected_output.str() == " 1: 1 2 3 4\n"
                                        " 2: 1 2 4 3\n"
                                        " 3: 1 3 2 4\n"
                                        " 4: 1 3 4 2\n"
                                        " 5: 1 4 2 3\n"
                                        " 6: 1 4 3 2\n"
                                        " 7: 2 1 3 4\n"
                                        " 8: 2 1 4 3\n"
                                        " 9: 2 3 1 4\n"
                                        "10: 2 3 4 1\n"
                                        "11: 2 4 1 3\n"
                                        "12: 2 4 3 1\n"
                                        "13: 3 1 2 4\n"
                                        "14: 3 1 4 2\n"
                                        "15: 3 2 1 4\n"
                                        "16: 3 2 4 1\n"
                                        "17: 3 4 1 2\n"
                                        "18: 3 4 2 1\n"
                                        "19: 4 1 2 3\n"
                                        "20: 4 1 3 2\n"
                                        "21: 4 2 1 3\n"
                                        "22: 4 2 3 1\n"
                                        "23: 4 3 1 2\n"
                                        "24: 4 3 2 1\n");
	cout << "** TEST PASSED **" << endl;

}

#endif
