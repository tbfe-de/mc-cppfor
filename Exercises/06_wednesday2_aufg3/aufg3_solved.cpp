/*
 ===============================================================
 Introducing a new node type ("Int_Node") ...
 ===============================================================
*/
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Stack {
public:
	class Node {
	private:
		Node *next;
	public:
		virtual void print(ostream& os) const =0;
		virtual ~Node() {};
	friend class Stack;
	};
	Stack() : top(0) {}
	void push(Node *);
	Node *pop();
private:
	Node *top;
};

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

class String_Node : public Stack::Node {
	string data;
	string &smax;
public:
	String_Node(std::string d, std::string &m)
		: data(d), smax(m) {
		if (smax < data)
			smax = data;
	}

	virtual void print(ostream& os) const {
		os << data;
		if (data == smax)
			os << " <---";
		os << endl;
	}
};

class Double_Node : public Stack::Node {
	double data;
	double &dmax;
public:

	Double_Node(double d, double &m)
		: data(d), dmax(m) {
		if (dmax < data)
			dmax = data;
	}

	virtual void print(ostream& os) const {
		os << data;
		if (data == dmax)
			os << " <---";
		os << endl;
	}
};

// (1) class Double_Node copied, name changed to Int_Node
//
class Int_Node : public Stack::Node {
	// (2) ... some more small changes here ...
	int data;	// double -> int
	int &imax;	// double -> int, dmax -> imax
public:

	// (3) ... here ...
	Int_Node(int d, int &m)		// double -> int
		: data(d), imax(m) {	// dmax -> imax
		if (imax < data)
			imax = data;
	}

	virtual void print(ostream& os) const {
		os << data;
		// (4) ... and here ...
		if (data == imax)	// dmax -> imax
			os << " <---";
		os << endl;
	}
};

void aufg3_demo(istream &in, ostream &out) {
	Stack s; // store input;

	out << "========== Input:" << endl;
	string sval, smax = "";
	double dval, dmax = 0.0;
	// (5) ... and finally local variables for new type
	//
	int ival, imax = 0;
	while (in >> sval) {
		if (istringstream(sval) >> dval) {
			ival = static_cast<int>(dval);
			if (static_cast<double>(ival) == dval)
				s.push(new Int_Node(ival, imax));
			else
				s.push(new Double_Node(dval, dmax));
		}
		else {
			s.push(new String_Node(sval, smax));
		}
	}

	out << "========== Output:" << endl;
	Stack::Node *np;
	while ((np = s.pop()) != 0) {
		np->print(out);
		delete np;
	}

	out << "==========" << endl;
}

/*
 ===============================================================
 ... requires a certain amount of "copy&paste"-programming.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 Observation: if all maximum variables in the specialized data
 node classes (smax, dmax, imax) were simply named max, besides
 the name (Double_Node -> Int_Node, as name of the class and
 the constructor), only TYPES had to be changed. Therefore a
 further improvement (with lesser manual changes) were possible
 with the use of the C++ template feature.
 ===============================================================
*/
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
		.expect_line("0.56 <---")
		.expect_line("4 <---")
		.expect_line("three")
		.expect_line("two <---")
		.expect_line("1")
		.expect_line("==========")
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Numbers only.
		//
		.test("some numbers")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1 2 3 4 .56 7 .8")
		.expect_line("========== Output:")
		.expect_line("0.8 <---")
		.expect_line("7 <---")
		.expect_line("0.56")
		.expect_line("4")
		.expect_line("3")
		.expect_line("2")
		.expect_line("1")
		.expect_line("==========")
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type numbers to calculate statistic", aufg3_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}
