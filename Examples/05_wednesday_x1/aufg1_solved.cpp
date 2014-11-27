/*
 ===============================================================
 Demonstrate the fact that constructors of virtual base classes
 are called from the most derived class, while any constructor
 call from the intermediate levels is ignored.

 (For the ease of printing and compilation, all is combined in a
 single file; realistically each class and interface would go in
 a file of its own, as marked by the separators below.)
 ===============================================================
*/
class Value {
private:
	double val;
public:
	//Value() {} // <--- original example will not compile if removed
	Value(double v)
		: val(v)
	{}
	virtual void setValue(double v) {
		val = v;
	}
	virtual double getValue() {
		return val;
	}
};

class Average : virtual public Value {
private:
	double sum;
	int cnt;
public:
	Average(double v)
		: Value(v) // <-- ignored when c'tor called from derived class
		, sum(v)
		, cnt(1)
	{}
	double getAverage() {
		return sum/cnt;
	}
	void setValue(double v) {
		Value::setValue(v);
		sum += v;
		++cnt;
	}
};

class Extrema : virtual public Value {
private:
	double min;
	double max;
	bool first;
public:
	Extrema(double v)
		: Value(v) // <-- ignored when c'tor called from derived class
		, min(v)
		, max(v)
		, first(false)
	{}
	double getMinimum() const {
		return min;
	}
	double getMaximum() const {
		return max;
	}
	void setValue(double v) {
		Value::setValue(v);
		if (first) {
			min = max = v;
			first = false;
		}
		else if (min > v)
			min = v;
		else if (max < v)
			max = v;
	}
};

class Statistic :
	public Average,
	public Extrema {
public:
	Statistic(double d)
		: Value(d) // <--- virtual base c'tor must be called from most derived class
			   //      (if no c'tor is called explicitely the default c'tor is
			   //      used implicitely, or compile error if it does not exist)
		, Average(d)
		, Extrema(d)
	{}
	virtual void setValue(double d) {
		Average::setValue(d);
		Extrema::setValue(d);
	}
};

#include <iostream>
using std::cout;

int main() {
	Value v(1.1);
	cout << "v: " << v.getValue() << "\n";

	Average a(2.2);
	cout << "a: " << a.getValue() << "  (" << a.getAverage() << ")\n";

	Extrema e(3.3);
	cout << "e: " << e.getValue()
	     << "  (" << e.getMinimum() << " .. " << e.getMaximum() << ")\n";

	Statistic s(4.4);
	cout << "s: " << s.getValue()
	     << "  (" << s.getAverage()
	     << " / " << s.getMinimum() << " .. " << s.getMaximum() << ")\n";
}
