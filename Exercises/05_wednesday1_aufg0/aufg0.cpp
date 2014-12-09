/**
 * For ease of implementation and printing this file combines in its
 * several sections the content of typically seperate files (as noted
 * at the start of each section).
*/

// -------------------------------------------------------------------
//       Stack class - would normally go into a header of its own.

class Stack {
public:
	class Node; // local class
private:
	Node *top;
public:
	Stack() : top(0) {}
	~Stack();
	void push(Node *);
	Node *pop();
};

class Stack::Node {
private:
	Node *next;
public:
	virtual ~Node() =0;
friend class Stack;
};

// -------------------------------------------------------------------
//      Classes derived from Stack::Node - typically a separate header

#include <string>

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

// -------------------------------------------------------------------
//      Implementation of Stack class - usually a compiled source file

Stack::~Stack() {
	for (Node *np = top; np != 0; np = top) {
		top = np->next;
		delete np;
	}
}

void Stack::push(Node *np) {
	np->next = top;
	top = np;
}

Stack::Node *Stack::pop() {
	Node *np = top;
	if (np != 0)
		top = np->next;
	return np;
}

Stack::Node::~Node() {
	// empty but required!!
}

// -------------------------------------------------------------------
//    Demo application - usually a separately compiled source file too

#include <iostream>
#include <sstream>
#include <typeinfo>
using namespace std;

void stack_demo(istream &in, ostream &out) {
	Stack s; // store input;

	out << "========== Input:" << endl;
	string sval, smax;
	double dval, dmax = 0.0;
	while (in >> sval) {
		if (istringstream(sval) >> dval) {
			s.push(new Double_Node(dval));
			if (dmax < dval)
				dmax = dval;
		}
		else {
			s.push(new String_Node(sval));
			if (smax < sval)
				smax = sval;
		}
	}

	out << "========== Output:" << endl;
	Stack::Node *np;
	while ((np = s.pop()) != 0) {
		if (typeid(*np) == typeid(String_Node)) {
			sval = static_cast< String_Node * >(np)->getString();
			out << sval << (sval == smax ? " <---" : "") << endl;
		}
		if (typeid(*np) == typeid(Double_Node)) {
			dval = static_cast< Double_Node * >(np)->getDouble();
			out << dval << (dval == dmax ? " <---" : "") << endl;
		}
		delete np;
	}

	out << "==========" << endl;
}

#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(cout)
		//	.config_details_uncond(true)
		//	.config_titles_only(true)
		//	.config_summary_only(true)
		//	.config_no_summary(true)
		//	.config_failure_stop(true)
		//	.config_interactive_mode(true)
		//	.config_page_output(true)
		//	.config_line_length(100)
			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Typical test with just some (randomly invented) values.
		//
		.test("realistic example")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 two three 4 .56 seven eight")
		.expect_line("========== Output:")
		.expect_line("eight")
		.expect_line("seven")
		.expect_line("0.56")
		.expect_line("4 <---")
		.expect_line("three")
		.expect_line("two <---")
		.expect_line("1")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Border case with no input supplied.
		//
		.test("empty input")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("")
		.expect_line("========== Output:")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single number.
		//
		.test("one number")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1")
		.expect_line("========== Output:")
		.expect_line("1.1 <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single string.
		//
		.test("one string")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("one")
		.expect_line("========== Output:")
		.expect_line("one <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Number followed by string.
		//
		.test("number and string")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1 two")
		.expect_line("========== Output:")
		.expect_line("two <---")
		.expect_line("1.1 <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Number followed by string.
		//
		.test("string and number")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("one 2.2")
		.expect_line("========== Output:")
		.expect_line("2.2 <---")
		.expect_line("one <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Numbers only.
		//
		.test("some numbers")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 2 3 4 .56 7 .8")
		.expect_line("========== Output:")
		.expect_line("0.8")
		.expect_line("7 <---")
		.expect_line("0.56")
		.expect_line("4")
		.expect_line("3")
		.expect_line("2")
		.expect_line("1")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Strings only.
		//
		.test("some strings")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("one two three four five six seven eight")
		.expect_line("========== Output:")
		.expect_line("eight")
		.expect_line("seven")
		.expect_line("six")
		.expect_line("five")
		.expect_line("four")
		.expect_line("three")
		.expect_line("two <---")
		.expect_line("one")
		.expect_line("==========")
		.run_to_return(stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type some strings and numbers", stack_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}

