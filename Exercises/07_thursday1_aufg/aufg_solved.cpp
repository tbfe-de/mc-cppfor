#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#if 0
void real_unique_copy(
	std::istream_iterator<std::string> in,
	std::istream_iterator<std::string> end,
	std::ostream_iterator<std::string> out
) {
     std::set<std::string> seen;
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
}

template<typename T>
void real_unique_copy(
	std::istream_iterator<T> in,
	std::istream_iterator<T> end,
	std::ostream_iterator<T> out
) {
     std::set<T> seen;
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
}

template<typename T1, typename T2>
void real_unique_copy(
	T1 in,
	T1 end,
	T2 out
) {
#if 0
     using ElementType = typename T1::value_type;
     std::set<ElementType> seen;
#else
     std::set<typename T1::value_type> seen;
#endif
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
}

template<typename T1, typename T2>
T2 real_unique_copy(
	T1 in,
	T1 end,
	T2 out
) {
     using ElementType = typename T1::value_type;
     std::set<ElementType> seen;
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
     return out;
}

template<typename ElementType, typename T2>
T2 real_unique_copy(
	ElementType* in,
	ElementType* end,
	T2 out
) {
     std::set<ElementType> seen;
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
     return out;
}

#endif

template<typename T>
struct my_iterator_traits {
//  typedef typename T::value_type value_type;
    using value_type = typename T::value_type;
};

template<typename T>
struct my_iterator_traits<T*> {
//  typedef T value_type;
    using value_type = T;
};

template<typename T1, typename T2>
T2 real_unique_copy(
	T1 in,
	T1 end,
	T2 out
) {
//   using ElementType = typename std::iterator_traits<T1>::value_type;
     using ElementType = typename my_iterator_traits<T1>::value_type;
     std::set<ElementType> seen;
     while (in != end) {
         auto result = seen.insert(*in++);
         if (result.second)
             *out++ = *result.first;
     }
     return out;
}

int main() {
    using namespace std;
    {
    istringstream prepared_input("eins zwei eins drei eins zwei drei");
    ostringstream actual_output;
    real_unique_copy(istream_iterator<string>(prepared_input),
                     istream_iterator<string>(),
                     ostream_iterator<string>(actual_output, " "));
    assert(actual_output.str() == "eins zwei drei ");
    }
//  ------------------------------------------------------------------
    {
    istringstream prepared_input("1 2 3 2 3 02 2 1");
    ostringstream actual_output;
    real_unique_copy(istream_iterator<string>(prepared_input),
                     istream_iterator<string>(),
                     ostream_iterator<string>(actual_output, " "));
    assert(actual_output.str() == "1 2 3 02 ");
    }
//  ------------------------------------------------------------------
    {
    istringstream prepared_input("1 2 3 2 3 02 2 1");
    ostringstream actual_output;
    real_unique_copy(istream_iterator<int>(prepared_input),
                     istream_iterator<int>(),
                     ostream_iterator<int>(actual_output, " "));
    assert(actual_output.str() == "1 2 3 ");
    }

//  ------------------------------------------------------------------
    {
    vector<int> data({1, 2, 3, 2, 3, 02, 2, 1});
    ostringstream actual_output;
    real_unique_copy(data.begin(), data.end(),
                     ostream_iterator<int>(actual_output, " "));
    assert(actual_output.str() == "1 2 3 ");
    }

//  ------------------------------------------------------------------
    {
    vector<int> data({1, 2, 3, 2, 3, 02, 2, 1});
    list<int> result;
    ostringstream actual_output;
    real_unique_copy(data.begin(), data.end(),
                     back_inserter(result));
    auto t = result.begin();
    assert(*t++ == 1);
    assert(*t++ == 2);
    assert(*t++ == 3);
    assert(t == result.end());
    }

//  ------------------------------------------------------------------
    {
    vector<double> data({1, 2, 3, 2.2, 3, 1});
    list<int> result;
    ostringstream actual_output;
    real_unique_copy(data.begin(), data.end(),
                     back_inserter(result));
    auto t = result.begin();
    assert(*t++ == 1);
    assert(*t++ == 2);
    assert(*t++ == 3);
    assert(*t++ == 2);
    assert(t == result.end());
    }

//  ------------------------------------------------------------------
    {
    vector<double> data({1, 2, 3, 2.2, 3, 1});
    double result[10];
    auto filled = real_unique_copy(data.begin(), data.end(), &result[0]);

    assert((filled - &result[0]) == 4);
    assert(result[0] == 1.0);
    assert(result[1] == 2.0);
    assert(result[2] == 3.0);
    assert(result[3] == 2.2);
    }

//  ------------------------------------------------------------------
    {
    std::array<double, 8> data = {1, 2, 3, 2.2, 3, 1};
    std::array<double, 10> result;
    auto filled = real_unique_copy(data.begin(), data.end(), &result[0]);

    assert((filled - &result[0]) == 5);
    assert(result[0] == 1.0);
    assert(result[1] == 2.0);
    assert(result[2] == 3.0);
    assert(result[3] == 2.2);
    assert(result[4] == 0.0);
    }

//  ------------------------------------------------------------------
    {
    double data[] = {1, 2, 3, 2.2, 3, 1};
    double result[10];
    ostringstream actual_output;
    auto filled = real_unique_copy(&data[0], &data[4], &result[0]);

    assert((filled - &result[0]) == 4);
    assert(result[0] == 1.0);
    assert(result[1] == 2.0);
    assert(result[2] == 3.0);
    assert(result[3] == 2.2);
    }

    cout << "ALL TESTS PASSED\n";
}
