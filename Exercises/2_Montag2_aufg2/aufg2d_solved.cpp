/*
 ===============================================================
 Some more effort (compared to all previous variants) ...
 ===============================================================
*/
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// A struct with all maxima ...
//
struct Maxima {
	string s;
	double d;
};

class Stack {
public:
	class Node {
	private:
		Node *next;
	public:
		// ... is handed to the print method ...
		//
		virtual void print(ostream& os, const Maxima &) const =0;
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
public:
	// ... the first 'ctor (will accesses the 's' field) ...
	//
	String_Node(std::string d, Maxima &m) : data(d) {
		if (m.s < data)
			m.s = data;
	}

	// ... the first print method (also accessing the 's' field) ...
	//
	virtual void print(ostream& os, const Maxima &m) const {
		os << data;
		if (data == m.s)
			os << " <---";
		os << endl;
	}
};
class Double_Node : public Stack::Node {
	double data;
public:

	// ... the other c'tor (accessing the 'd' field)
	//
	Double_Node(double d, Maxima &m) : data(d) {
		if (m.d < data)
			m.d = data;
	}

	// ... the other print methode (also accessing the 'd' field)
	//
	virtual void print(ostream& os, const Maxima &m) const {
		os << data;
		if (data == m.d)
			os << " <---";
		os << endl;
	}
};

void aufg2_demo(istream& in, ostream& out) {
	Stack s; // store input;

	out << "========== Input:" << endl;
	string sval;
	double dval;
	// Accordingly the main program defines a struct in its scope ...
	//
	Maxima max = { "", 0.0 };	// ... which it initializes ...
	while (in >> sval) {
		if (istringstream(sval) >> dval) {
			// ... gives to the one c'tor ...
			//
			s.push(new Double_Node(dval, max));
		}
		else {
			// ... or the other one ...
			//
			s.push(new String_Node(sval, max));
		}
	}

	out << "========== Output:" << endl;
	Stack::Node *np;
	while ((np = s.pop()) != 0) {
		// ... and finally to the print method
		//
		np->print(out, max);
		delete np;
	}

	out << "==========" << endl;
}

/*
 ===============================================================
 ... also prepares extending the program to more than one column
 - with still good modularity and access control.

 A main point of criticism could be that the derived classes
 for the specialize data nodes now have a REVERSE dependency to
 their base class Data::Node, because sdding a new node type
 requires
  - to add another element to the struct max,
  - which is the argument type of the Stack::Node (base class)
    print method, leading to a "cyclic dependency".
 It needs to be judiciously decided if this is worth the price.
 (Probably it is if lesser memory consumption is important, and
 it might be not if the "general rules of a 'good' design" are
 the primary guideline.)
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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

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
		.run_to_return(aufg2_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type numbers to calculate statistic", aufg2_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}

