/*
 ===============================================================
 The easiest and quickest way to avoid typeid (or dynamic-cast)
 in the main program ...
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
		// (1) add a pure virtual print-Methode here
		//
		virtual void print(ostream&) const =0;

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

// (2) move local variables to global visibility
//
string smax = "";
double dmax = 0.0;

class String_Node : public Stack::Node {
	string data;
public:
	String_Node(std::string d) : data(d) {}
	virtual void print(ostream& os) const {
		// (2b) make local variables accessible
		// only necessary for separate compilaton
		//
		extern string smax;

		// (3) move printing code from main program here
		//
		os << data;
		if (data == smax)
			os << " <---";
		os << endl;
	}
};

class Double_Node : public Stack::Node {
	double data;
public:
	Double_Node(double d) : data(d) {}
	virtual void print(ostream& os) const {
		// (4) -- as before String_Node (2b+3)
		//
		extern double dmax;
		os << data;
		if (data == dmax)
			os << " <---";
		os << endl;
	}
};

void aufg1_demo(istream &in, ostream &out) {
	Stack s; // store input;

	out << "========== Input:" << endl;
	string sval; smax.clear();
	double dval; dmax = 0.0;
	while (in >> sval) {
		istringsstream iss(sval);
		if (iss >> dval) {
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

		// (6) no more need for typeid and dynamic_cast
		//
		np->print(out);
		
		delete np;
	}

	out << "==========" << endl;
}

int main() {
	aufg1_demo(cin, cout);
}

#if 0
/*
 ===============================================================
 ... but it is not so "nice" as it introduces global variables:
 => not modular, including risk of accidental name clashes;
 => no easy access control;
 => might require synchronization in case of multi-threading.
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
		.expect_line("0.56")
		.expect_line("4 <---")
		.expect_line("three")
		.expect_line("two <---")
		.expect_line("1")
		.expect_line("==========")
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

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
		.run_to_return(aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type numbers to calculate statistic", aufg1_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}
#endif
