#if MIXIN_VERSION == 1
#include "Value1.h"
#include "Average1.h"
#include "Extrema1.h"
#include "Statistic1.h"
#include "Mixin-IO.h"
#elif MIXIN_VERSION == 2
#include "Value2.h"
#include "Average2.h"
#include "Extrema2.h"
#include "Statistic2.h"
#include "Mixin-IO.h"
#elif MIXIN_VERSION == 3
#include "Value3.h"
#include "Average3.h"
#include "Extrema3.h"
#include "Statistic3.h"
#include "Mixin-IO3.h"
#else
#error "MIXIN_VERSION must be defined as '1', '2', or '3'"
#endif

int main()  {
	Value v;
	Average a;
	Extrema e;
	Statistic s;
	using namespace std;
	double val;
	while (cin >> val) {
		v.setValue(val);
		a.setValue(val);
		e.setValue(val);
		s.setValue(val);
		cout << "v: " << v << '\n'
		     << "a: " << a << '\n'
		     << "e: " << e << '\n'
		     << "s: " << s << '\n'
		     << "--" << endl;

	}
}
