#include <cstddef>
#include <iostream>
using namespace std;

#include "WindowRes.h"
#include "MenuItemRes.h"

class Choice {
	WindowRes w;
	MenuItemRes mi;
public:
	Choice(bool pop_up, const char *const mtext[], size_t msize)
			: w(pop_up, "... xxx ..."), mi(msize) {
		for (size_t i = 0; i < msize; ++i)
			mi[i].setText(mtext[i]);
		ITrace::allow("== completing creation of Choice()-object");
	}
	void select() {
		ITrace::allow("** executing Choice::select()");
		// ...
		if (w) useWindow(w);
		// ...
	}
private:
	// disable default versions
	Choice(const Choice &);
	Choice &operator=(const Choice &);
};
