/*
 * This is a "quick and may be a little bit dirty" implementation of an
 * istream_iterator for std::string-s. It works (at least) with algorithms
 * std::copy and std::unique_copy (test for the latter see below).
 *
 * All the requirements for an "InputIterator" as specified in by C++11
 * (see http://en.cppreference.com/w/cpp/concept/InputIterator for details)
 * as also outlined in the comments below.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class istream_it_demo :
    // provide the necessary base class to describe that ...
    public std::iterator<std::input_iterator_tag, std::string> {
    // (a) ... the category   ^^^^^^^^^^^^^^ and
    // (b) the dereferenced type (value_type)           ^^^^^^        

    std::istream *strp;  // stream from which the iterator reads
    std::string temp;    // and value last read susccessfully

private:
    // Do the actual input - read a string from the stream
    void read_next() {
        /*
         * As long as strp is different from nullptr the stream is in
         * a usable state, i.e. not consumed up to its end or in a fail
         * state (the latter cannot happen when strings are read, but
         * if this class were extended to a template reading other types
         * the ossibility would occur).
        */
        if (strp) {
            if (!(*strp >> temp))
                strp = nullptr;
	}
    }

public:
    // constructur to connect to a stream
    istream_it_demo(std::istream &strr)
        : strp(&strr)
    {
        /*
         * As accoding to the InputIterator requirements two consecutive
         * applications of operator* must return the same item, actual
         * reading cannot happen there - at least not in the simple-most
         * implemetation. So we read the first item in the constructor.
        */
        read_next(); // actually first (see ong comment above)
    }
    // constructur to serve as end-point detecion
    istream_it_demo()
        : strp(nullptr)
    {}
    // actually read something from the stream
    istream_it_demo &operator++() {
        read_next();
        return *this;
    }
    // return the value last read
    const std::string &operator*() {
        return temp;
    }
    // implementation see below
    friend bool operator!=(const istream_it_demo&, const istream_it_demo&);
};

// if any of the operands has not been created by the default constructor
// it still needs to refer to usable stream (in the good state) - just
// think about how input iterators are used, e.g. in copy:
// copy(beg, end, to) {
//     while (beg != end)
//         *to++ = *beg++;
// }
bool operator!=(const istream_it_demo& lhs, const istream_it_demo& rhs) {
     return lhs.strp != rhs.strp;
}

// we need to provide this too as clients might test iterator equality
// with operator!= or with operator ==
bool operator==(const istream_it_demo& lhs, const istream_it_demo& rhs) {
    return !(lhs != rhs);
}

int main() {
    std::vector<std::string> data;
#if 0
    std::unique_copy(std::istream_iterator<std::string>(std::cin),
                     std::istream_iterator<std::string>(),
                     std::back_inserter(data)
#else
    std::unique_copy(istream_it_demo(std::cin),
                     istream_it_demo(),
                     std::back_inserter(data)
    );
#endif
    for (auto e : data)
        std::cout << e << '\n';
}
