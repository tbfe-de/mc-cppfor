/*
 ===============================================================
 Now, introducing a new data column ...
 ===============================================================
*/
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

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
	String_Node(std::string d, Maxima &m) : data(d) {
		if (m.s < data)
			m.s = data;
	}

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

	Double_Node(double d, Maxima &m) : data(d) {
		if (m.d < data)
			m.d = data;
	}

	virtual void print(ostream& os, const Maxima &m) const {
		os << data;
		if (data == m.d)
			os << " <---";
		os << endl;
	}
};

void aufg4_demo(istream& in, ostream& out) {
	Stack s; // store input;

	out << "========== Input:" << endl;
	string sval;
	double dval;
	Maxima max = { "", 0.0 };
	while (in >> sval) {
		if (istringstream(sval) >> dval)
			s.push(new Double_Node(dval, max));
		else
			s.push(new String_Node(sval, max));
	}

	out << "========== Output:" << endl;
	Stack::Node *np;
	while ((np = s.pop()) != 0) {
		np->print(out, max);
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
		.supply_line("1       two")
		.supply_line("three     4")
		.supply_line(".56   seven")
		.supply_line("eight 9.999")
		.expect_line("========== Output:")
		.expect_line("eight"		"\t"	"9.999 <---")
		.expect_line("0.56"		"\t"	"seven")
		.expect_line("three <---"	"\t" 	"4")
		.expect_line("1 <---"		"\t"	"two <---")
		.expect_line("==========")
		.run_to_return(aufg4_demo)

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
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single number.
		//
		.test("one line with numbers")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1  2.2")
		.expect_line("========== Output:")
		.expect_line("1.1 <---"		"\t"	"2.2 <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Single string.
		//
		.test("one line with strings")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("one two")
		.expect_line("========== Output:")
		.expect_line("one <---"		"\t"	"two <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Number followed by string.
		//
		.test("two lines")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1 two")
		.supply_line("three 4")
		.expect_line("========== Output:")
		.expect_line("three <---"	"\t"	"4 <---")
		.expect_line("1.1 <---"		"\t"	"two <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Number followed by string.
		//
		.test("pure string and number column")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("one 1.1")
		.supply_line("two 2e0")
		.supply_line("three 3")
		.supply_line("four .4")

		.expect_line("========== Output:")
		.expect_line("four"	"\t"	"0.4")
		.expect_line("three"	"\t"	"3 <---")
		.expect_line("two <---"	"\t"	"2")
		.expect_line("one"	"\t"	"1.1")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type some strings and numbers in two columns", aufg4_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}
