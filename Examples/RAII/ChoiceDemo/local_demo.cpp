#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "Window.h"
#include "MenuItem.h"

bool bar() {
	ITrace::allow("** executing body of bar()");
	// ...
	return true;
}

void foo(const char *const mtext[], size_t msize) {
	// allocate window object
	Window w("... xxx ...");

	// allocate and configure menus
	vector<MenuItem> mi(msize);
	for (size_t i = 0; i < msize; ++i)
		mi[i].setText(mtext[i]);

	ITrace::allow("** executing body of foo()");
	// ...
	(void) bar();

	// (ressources automatically released)
}

int main() {
	static const char *const MENUBAR[] = { "File", "Edit", "Help" };
	static const size_t MBARSIZE = sizeof MENUBAR / sizeof MENUBAR[0];

	cout << "======= start of main()" << endl;
	try {
		foo(MENUBAR, MBARSIZE);
	}
	catch (runtime_error &fatality) {
		cout << "!! " << fatality.what() << " !!" << endl;
	}
	cout << "======= end of main()" << endl;
}
