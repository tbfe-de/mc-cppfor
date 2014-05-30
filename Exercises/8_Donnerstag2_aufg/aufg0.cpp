#include "WordPositioner.h"

using namespace std;

void aufg0_demo(istream &in, ostream &out) {
	WordPositioner wp;
	wp.read(in);
	wp.write(out);
}

int main() {
	aufg0_demo(cin, cout);
}
