#include "window.h"

class WindowRes {
	WINDOW *const res;
public:
	WindowRes(bool create, const char *t)
		: res(create ? createWindow(t) : nullptr)
	{}
	~WindowRes() {
		if (res)
			destroyWindow(res);
	}
	operator WINDOW *() {
		return res;
	}
	operator bool() const {
		return res != 0;
	}
};
