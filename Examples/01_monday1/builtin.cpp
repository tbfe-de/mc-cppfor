#include <iostream>

void f(char) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void f(signed char) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void f(unsigned char) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

typedef signed char mytype;
//void f(mytype) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

int main() {
     char a;
     signed char b;
     unsigned char c;
     mytype d;
     f(a);
     f(b);
     f(c);
     f(d);
}
