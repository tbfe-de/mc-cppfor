#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

#if VERSION == 1
#include "Choice1.h"
#elif VERSION == 2
#include "Choice2.h"
#elif VERSION == 3
#include "Choice3.h"
#elif VERSION == 3
#include "Choice3.h"
#elif VERSION == 4
#include "Choice4.h"
#elif VERSION == 5
#include "Choice5.h"
#elif VERSION == 6
#include "Choice6.h"
#else
#error "no such version"
#endif

int main() {
	static const char *const MENUBAR[] = { "File", "Edit", "Help" };
	static const size_t MBARSIZE = sizeof MENUBAR / sizeof MENUBAR[0];

	cout << "======= start of main()" << endl;
	try {
		Choice p(true, MENUBAR, MBARSIZE);
		p.select();
	}
	catch (runtime_error &fatality) {
		cout << "!! " << fatality.what() << " !!" << endl;
	}
	cout << "======= end of main()" << endl;
}
