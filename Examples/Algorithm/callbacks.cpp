/*
 ===============================================================================
 Using Function Pointers, Functors, and Lambdas as Callbacks from Algorithms
 ===============================================================================
 The following demonstrates and compares the use of
    * Classic C Function Pointers,
    * C++ Functors (classes overloading `operator()`), and
    * C++11 Lambdas (with and without capture lists).
 Also the use of the (C++11) `std::function`-template is shown.

*/

#include <algorithm>
#include <forward_list>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

void print_words(const std::string &e) {
    std::cout << ": " << e << "\n";
};

struct PrintWords {
    void operator()(const std::string &e) {
        std::cout << ": " << e << "\n";
    }
};

std::function<void(const std::string &)> pw_lambda =
// or shorter (though not quite the same):
// auto pw_lambda =
    [](const std::string &e) {
        std::cout << ": " << e << "\n";
    };
// Note that suggesting `auto` as alternative  to `std::function` here may lead
// to the (wrong) impression that both are equivalent. In fact they are NOT -
// storing a lambda in an `auto`-typed variable gives it its own, unique type,
// while with `std::function` type erasure will take place, i.e. - at the price
// of a virtual call - the type will be the same for any (compatible) lambda.
// (As all of this is not relevant for the purpose of this example series, it
// is only mentioned but not discussed in depth.)

struct PrintWordsEnumerated {
    void operator()(const std::string &e) {
        std::cout << ++n << ": " << e << "\n";
    }
    PrintWordsEnumerated() : n(0) {}
private:
    int n;
};

struct PrintWordsOnStream {
    void operator()(const std::string &e) {
        std::cout << ++n << ": " << e << "\n";
    }
    PrintWordsOnStream(std::ostream &os_)
        : n(0), os(os_)
    {}
private:
    int n;
    std::ostream &os;
};

// --------------------------------------------------------------- the test data
//
const std::forward_list<std::string> v = {
    "time", "for", "a", "break"
};

// --------------------------------------------------- print words after a colon
//
void test_pw() {
//  std::for_each(v.begin(), v.end(), print_words);
//  std::for_each(v.begin(), v.end(), PrintWords());
    std::for_each(v.begin(), v.end(),
                  [](const std::string &e) {
                      std::cout << ": " << e << "\n";
                  });
    std::for_each(v.begin(), v.end(), pw_lambda);
//  for (const auto e : v) {
//  	std::cout << ": " << e << '\n';
//  }
}

// ------------------------------------------------------ print words enumerated
//
void test_pw_enumerated() {
//  std::for_each(v.begin(), v.end(), PrintWordsEnumerated());
    int n = 0;
    std::for_each(v.begin(), v.end(),
                 [n](const std::string &e) mutable {
                     std::cout << ++n << " :" << e << "\n";
                 });
//  for (const auto e : v) {
//  	std::cout << ++n  << ": " << e << '\n';
//  }
}

// -------------------------------------------- print words enumerated on stream
//
void test_pw_enumerated(std::ostream &output) {
//  std::for_each(v.begin(), v.end(), PrintWordsOnStream(output));
    int n = 0;
    std::for_each(v.begin(), v.end(),
                 [n, &output](const std::string &e) mutable {
                     output << ++n << ": " << e << "\n";
                 });
//  for (const auto e : v) {
//  	output << ++n  << ": " << e << '\n';
//  }
}

// --------------------------------------------- call one or more from the above
//
int main() {
//  test_pw();
//  test_pw_enumerated();
    test_pw_enumerated(std::cout);
}
