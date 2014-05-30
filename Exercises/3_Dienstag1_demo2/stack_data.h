#include <string>

#include "stack.h"

class String_Node : public Stack::Node {
	std::string data;
public:
	String_Node(std::string d) : data(d) {}
	virtual ~String_Node() {}
	std::string getString() const { return data; }
};

class Double_Node : public Stack::Node {
	double data;
public:
	Double_Node(double d) : data(d) {}
	virtual ~Double_Node() {}
	double getDouble() const { return data; }
};
