#include "MenuItem.h"

class MenuItemRes {
	MenuItem *const mi;
public:
	MenuItemRes(size_t n)
			: mi(new MenuItem[n])
	{}
	MenuItem &operator[](size_t x) {
		return mi[x];
	}
	~MenuItemRes() {
		delete[] mi;
	}
};
