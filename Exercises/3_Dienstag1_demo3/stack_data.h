#include "stack.h"

class Int_Node : public Stack::Node {
	int data;
public:
	Int_Node(int d) : data(d) {}
	virtual ~Int_Node() {}
	virtual void print(std::ostream &out) const {
		out << data;
	}
};

class Double_Node : public Stack::Node {
	double data;
public:
	Double_Node(double d) : data(d) {}
	virtual ~Double_Node() {}
	virtual void print(std::ostream &out) const {
		out << data;
	}
};
