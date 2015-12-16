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

public:
    // constructur to connect to a stream
    istream_it_demo(std::istream &strr)
        : strp(&strr)
    {}
    // constructur to serve as end-point detecion
    istream_it_demo()
        : strp(nullptr)
    {}
    // actually read something from he stream
    std::string operator*() {
        std::string s;
        (*strp) >> s;
        return s;
    }
    // increment needs to be provided but may do nothing
    istream_it_demo &operator++() {
        return *this;
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
     return lhs.strp != nullptr && lhs.strp->good()
         || rhs.strp != nullptr && rhs.strp->good();
}

// we need to provide this too, as clients might test iterator euality
// with operator!= or with operator ==
bool operator==(const istream_it_demo& lhs, const istream_it_demo& rhs) {
    return !(lhs == rhs)
}

int main() {
    std::vector<std::string> data;
    std::copy(istream_it_demo(std::cin),
             istream_it_demo(),
             std::back_inserter(data)
    );
    for (auto e : data)
        std::cout << e << '\n';
}
