/*
 ==============================================================================
 Count number of elements in int-array that do NOT have the value 0
 ==============================================================================
*/

#include <algorithm>
#include <functional>

const int data[] = {
		3, 12, 19, -4,  0,  8,  0,  0, 20, -1,
		99,  0,  2,  2,  8,  0,  7,  6,  0,  3
};
const size_t N = sizeof data / sizeof data[0];

bool notNullFunction(int v) {
   	return (v != 0);
}

int aufg1_function() {
	return std::count_if(
			data, data+N,
			notNullFunction
	);
}

struct NotNullFunctor {
	bool operator()(int v) const {
		return (v != 0);
	}
};

int aufg1_functor() {
	return std::count_if(
			data, data+N,
			NotNullFunctor()
	);
}

int aufg1_functional() {
	return count_if(
			data, data+N,
			std::bind2nd(std::not_equal_to<int>(), 0)
	);
}

int aufg1_lambda() {
	return std::count_if(data, data+N, [](int v) { return (v != 0); });

}

#include <cassert>
#include <iostream>

int main() {
	using namespace std;
	cout << "with function: " << aufg1_function() << endl;
	cout << "with functor: " << aufg1_functor() << endl;
	cout << "with functional: " << aufg1_functional() << endl;
	cout << "with lambda: " << aufg1_lambda() << endl;
}
