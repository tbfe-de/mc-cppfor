#include <cstdlib>

#include "ITrace.h"

typedef struct {
	ITrace *itp;
	// ...
	// empty framework, for demo purposes only
	// ...
} WINDOW;

WINDOW *createWindow(const char *t) {
	WINDOW *wp = new WINDOW;
	wp->itp = new ITrace("WINDOW");
	// ... initialize WINDOW ressource
	// ...
	return wp;
}

void destroyWindow(WINDOW *wp) {
	// ... release WINDOW ressource
	// ...
	delete wp->itp;
	delete wp;
}

void useWindow(WINDOW *wp) {
	ITrace::allow("** using " + std::string(*(wp->itp)));
	// ...
}

