#include "stack.h"

class Int_Node : public Stack::Node {
public:
	int data;
	Int_Node(int d) : data(d) {}
	virtual ~Int_Node() {}
};

class Double_Node : public Stack::Node {
public:
	double data;
	Double_Node(double d) : data(d) {}
	virtual ~Double_Node() {}
};
