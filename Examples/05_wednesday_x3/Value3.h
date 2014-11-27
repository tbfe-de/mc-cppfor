#ifndef Value_H
#define Value_H

#include <cassert>
#include <iostream>
#include <set>

class Value {
public:
	struct Update {
		virtual void setNotify(double) =0;
	};
private:
	double val;
	typedef std::set<Update*> UpdateListeners;
	UpdateListeners ul;
public:
	void registerUpdate(Update *const up) {
		assert(up);
		ul.insert(up);
	}
	void setValue(double v) {
		val = v;
		for (UpdateListeners::iterator ulit = ul.begin(); ulit != ul.end(); ++ulit)
			(*ulit)->setNotify(v); // or: (**ulit).setNotify(v);
	}
	double getValue() const {
		return val;
	}
	virtual std::ostream& print(std::ostream& os) const {
		return os << "= " << val;
	}
};


#endif
