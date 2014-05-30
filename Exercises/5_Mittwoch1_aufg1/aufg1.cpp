/*
 ==============================================================================
 Count number of elements in int-array that do NOT have the value 0
 ==============================================================================
*/

#include <algorithm>
	using std::count_if;
#include <iostream>
	using std::cout;
	using std::endl;
	using std::istream;
	using std::ostream;

const int data[] = {
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3
};
const size_t N = sizeof data / sizeof data[0];

bool notNullFunction(int v) {
   	return (v != 0);
}

int aufg1_function() {
	return count_if(
			data, data+N,
			notNullFunction
	);
}

struct NotNullFunctor {
	// ...
	// TO-BE-DONE
	// ...
};

int aufg1_functor() {
	return count_if(
			data, data+N,
			// ... TO-BE-DONE ...
	);
}

int main() {
	cout << "with function:" << aufg1_function() << endl;
//	cout << "with functor:" << aufg1_functor() << endl;
}

