/*
 ===============================================================
 Now, introducing a new data column ...
 ===============================================================
*/
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Maxima {
	// default C'tor allows to allocate arrays (see below)
	//
	Maxima()
		: s(""), d(0.0)
	{}
	string s;
	double d;
};

class Stack {
public:
	class Node {
	private:
		Node *next;
	public:
		// print method adds column with argument (with default)
		//
		virtual void print(ostream& os, const Maxima &, char = '\n') const =0;
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

	virtual void print(ostream& os, const Maxima &m, char sep) const {
		os << data;
		if (data == m.s)
			os << " <---";
		os << sep;
	}
};
class Double_Node : public Stack::Node {
	double data;
public:

	Double_Node(double d, Maxima &m) : data(d) {
		if (m.d < data)
			m.d = data;
	}

	virtual void print(ostream& os, const Maxima &m, char sep) const {
		os << data;
		if (data == m.d)
			os << " <---";
		os << sep;
	}
};

void aufg3_demo(istream &in, ostream &out) {
	const size_t N = 2;
	// IMPORTANT NOTE: Much of the code below is already prepared for
	// handling more than two data columns - BUT NOT ALL OF IT !!!!!!
	// Hence it makes sense to have an early error indication that
	// (hopefully) directs a maintenance programmer to this comment.
	assert(N == 2);

	Stack s[N]; // store input;
	
	string sval[N];
	double dval[N];
	Maxima max[N];	// <--- initialized by default C'tor (see above)
	string line;

	out << "========== Input:" << endl;
	// At first read a whole line ...
	while (getline(in, line)) {
		// ... turn it into a stream ...
		istringstream iss(line);
		// NOTE: Next line will ONLY HANDLE *TWO* COLUMNS CORRECTLY (!!)
		assert(N == 2);
		if (iss >> sval[0] >> sval[1]) {
			// ... from which values are extracted ...
			for (size_t i = 0; i < N; ++i) {
				// ... and being processed (all in the same way)
				//
				if (istringstream(sval[i]) >> dval[i]) {
					s[i].push(new Double_Node(dval[i], max[i]));
				}
				else {
					s[i].push(new String_Node(sval[i], max[i]));
				}
			}
		}
	}

	out << "========== Output:" << endl;
	Stack::Node *np[N];
	// NOTE: Next loop will ONLY HANDLE *TWO* COLUMNS CORRECTLY (!!)
	assert(N == 2);
	while ((np[0] = s[0].pop()) != 0
	    && (np[1] = s[1].pop()) != 0) {
			np[0]->print(out, max[0], '\t');
			delete np[0];
			np[1]->print(out, max[1]);
			delete np[1];
	}

	out << "==========" << endl;
}

/*
 ===============================================================
 ... does not require major changes.
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
		.test("one line with numbers")
		// -------------------------------------------------------------------
		.expect_line("========== Input:")
		.supply_line("1.1  2.2")
		.expect_line("========== Output:")
		.expect_line("1.1 <---"		"\t"	"2.2 <---")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.run_to_return(aufg3_demo)

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
		.expect_line("four"		"\t"	"0.4")
		.expect_line("three"	"\t"	"3 <---")
		.expect_line("two <---"	"\t"	"2")
		.expect_line("one"		"\t"	"1.1")
		.expect_line("==========")
		// -------------------------------------------------------------------
		.run_to_return(aufg3_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		// Sometimes interactive testing might still be desirable ...
		//
		.test_cincout("type numbers to calculate statistic", aufg3_demo)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize() // ... and set return value of main to success / failure.
		;
}
