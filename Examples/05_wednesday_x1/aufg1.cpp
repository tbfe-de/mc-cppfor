/*
 ===============================================================
 An Example for Diamond-Shaped Inheritance.
 ===============================================================
*/
class Value {
private:
	double val;
public:
	Value() {}
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
		: Value(v)
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
		: Value(v)
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
		: Average(d)
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
