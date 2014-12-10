/*
 ==============================================================================
 Demonstrate Usefulnes of 2nd Argument to std::inserter Helper Function
 ==============================================================================

 Background information:

 Both, sequential and associative containers have a member function 'insert'
 (or 'insert_after' in case of an 'std::forward_list'), which can takes a value
 to insert and a position. While for sequential containers the latter specifies
 the insertion point exactly, for associative containers it is just taken as a
 hint to optimise determining the position in the (tree) data structure where
 the new element might be placed. (If the hint is wrong, there is no worse
 negative impact as a missed chance for optimisation.) Because the hint is not
 really necessary, the member function 'insert' for associative containers has
 a default for its second argument, so that it need not be specified.

 When members are inserted into an associative containers by means of an
 'std::insert_iterator' and then - for convenience - the 'std::insert' helper is
 used (to avoid having to specifying a redundant type argument), the second
 argument CANNOT be omitted but always has to be specified.

 The example below shows the effect in detail. The new members 10, 20, and 30
 are inserted into an 'std::set' and alternatively an 'std::vector'. In the
 former case the insertion point is effectively ignored (and of course will not
 contribute a useful hint), but in the latter case it actually determines the
 insertion point.

 (Thanks to ..... for a suggestionin the C++-For training 2014-12-09 that
 finally led to creating this example.)
*/

#include <algorithm>
	using std::advance;
	using std::copy;
#include <array>
	using std::array;
#include <iostream>
	using std::cout;
	using std::endl;
#include <iterator>
	using std::istream_iterator;
	using std::ostream_iterator;
	using std::inserter;
#include <sstream>
	using std::istringstream;

#if 0
#include <set>
std::set<int> data = { 1, 2, 3, 4 };
#else
#include <vector>
std::vector<int> data = { 1, 2, 3, 4 };
#endif

int main() {
	auto insert_point = data.begin();
	advance(insert_point, 2);
	istringstream iss("10 20 30");
	copy(istream_iterator<int>(iss), istream_iterator<int>(),
	     inserter(data, insert_point));
	copy(data.begin(), data.end(),
	     ostream_iterator<int>(cout, " "));
	cout << endl;
}
