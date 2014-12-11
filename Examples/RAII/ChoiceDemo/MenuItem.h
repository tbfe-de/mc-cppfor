#include "ITrace.h"

class MenuItem : public ITrace {
	// ...
	// empty framework, for demo purposes only
	// ...
public:
	MenuItem() : ITrace("MenuItem") {
		// resource allocation (may fail)
		// ...
	}
	~MenuItem() {
		// mandatory cleanup after finishing
		// ...
	}
	void setText(const std::string &t) {
		allow(" + setText(\"" + t + "\") for " + *(ITrace *)this);
		// ...
	}
};
