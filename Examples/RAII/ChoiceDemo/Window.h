#include "ITrace.h"

class Window : public ITrace {
	// ...
	// empty framework, for demo purposes only
	// ...
public:
	Window(const char *) : ITrace("Window") {
		// resource allocation (may fail)
	}
	~Window() {
		// mandatory cleanup after finishing
	}
};

inline
Window *createWindow(const char *t) {
	return new Window(t);
}

inline
void destroyWindow(Window *win) {
	delete win;
}
