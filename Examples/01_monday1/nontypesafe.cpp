#include <iostream>
#include <vector>
class Base {
public:
    int x;
    Base(int x_) : x(x_) {}
};

class Derived : public Base {
    float z = 20;
public:
	using Base::Base;
};

int main() {
    std::vector<Derived> arr = { 10, 1, 17, 19 };
#if 0
    auto p = arr.begin();
#else
    Base* p = arr.data();
#endif
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << i << ": " << (p++)->x << '\n';
    }
}
