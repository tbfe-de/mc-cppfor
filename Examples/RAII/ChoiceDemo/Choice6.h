#include <cstddef>
#include <iostream>
#include <memory>

#include "Window.h"
#include "MenuItem.h"

class Choice {
	std::unique_ptr<Window> w;
	std::unique_ptr<MenuItem[]> mi;
public:
	Choice(bool pop_up, const char * const mtext[], size_t msize)
		: w(pop_up ? new Window("... xxx ...") : nullptr)
		, mi(new MenuItem[msize])
	{
		for (size_t i = 0; i < msize; ++i)
			mi[i].setText(mtext[i]);
		ITrace::allow("== completing creation of Choice()-object");
	}
	void select() {
		ITrace::allow("** executing Choice::select()");
		// ...
	}
private:
	// disable default versions
	Choice(const Choice &)            = delete;
	Choice &operator=(const Choice &) = delete;
};
