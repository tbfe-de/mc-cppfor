#ifndef Value_H
#define Value_H

#include <cassert>
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
	virtual ~Value() {}
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
};

#endif
