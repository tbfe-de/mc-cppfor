/*
 ================================================================================
 Print words "in order" according to the position after each word.
 ================================================================================
*/
#include <iostream>
	using std::cin;
	using std::cout;
	using std::cerr;
	using std::endl;
	using std::istream;
	using std::ostream;
#include <map>
	using std::map;
	using std::make_pair;
#include <set>
	using std::set;
#include <sstream>
	using std::istringstream;
	using std::ostringstream;
#include <stdexcept>
	using std::exception;
	using std::runtime_error;
#include <string>
	using std::string;

template<class Policy>
class WordPositioner : private Policy {
	// TO-BE-DONE: add using directives for methods
	//			   implemented in Policy class ...

	typedef set<string> WORDSET;
	typedef map<int, WORDSET::const_iterator> WORDMAP;
	WORDSET seen;
	WORDMAP allwords;
public:
	void read(istream&);
	void write(ostream&) const;
};

class Error : public std::runtime_error {
protected:
	Error(const char *text)
		: std::runtime_error(text)
	{}
};

template<class Policy>
void WordPositioner<Policy>::read(istream& in) {
	string line;
	while (getline(in, line)) {
		istringstream iss(line);
		int npos = 0;
		string w;
		if (getline(iss, w, ':')) {
			const auto result = seen.insert(w);
			if (!result.second)
				error_DuplicateWord();
			int pos;
			const int snpos = npos;
			while (iss >> pos) {
				if (pos <= 0)
					error_InvalidWordPos();
				if (!allwords.insert(std::make_pair(pos, result.first)).second)
					error_DuplicateWordPos();
				++npos;
			}
			if (npos == snpos)
				error_BadLineFormat();
			if (!iss.eof())
				error_InvalidWordPos();
		}
	}
}

template<class Policy>
void WordPositioner<Policy>::write(ostream& out) const {
	int npos = 0;
	for (auto it = allwords.begin(); it != allwords.end(); ++it) {
		while (it->first > 0
			&& ++npos < it->first) {
			error_MissingWordPos(npos, out);
		}
		out << *(it->second) << ' ';
	}
	out << endl;
}

class NonThrowing {
protected:
	// TO-BE-DONE: add methods with implementation to do nothing
	//				for the "non-throwing"-case ...

};
typedef WordPositioner<NonThrowing> NonThrowing_WordPositioner;

class Throwing {
public:
	class BadLineFormat : public Error {
		public: BadLineFormat()	: Error("BadLineFormat") {}
	};
	// TO-BE-DONE: add more classes like the one above to be
	//			   thrown in case of various problems ...

protected:
	// TO-BE-DONE: add method implementations that actually
	//			   throw in case of problems
};
typedef WordPositioner<Throwing> Throwing_WordPositioner;

class Replacing
	: protected NonThrowing {
protected:
	// TO-BE-DONE: override just those methods that differ
	//			   from the "throwing" case ...
};

typedef WordPositioner<Replacing> Replacing_WordPositioner;

template<class Selected_WordPositioner>
void aufg5_demo(istream &in, ostream &out) {
	Selected_WordPositioner wp;
	try {
		wp.read(in);
		std::ostringstream os;
		wp.write(os);
		out << os.str();
	}
	catch (Error &err) {
		out << "CAUGHT: " << err.what() << endl;
	}
}

#include "IODrive.h"

int main(int argc, char* argv[]) {

	return IODrive(std::cout)
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
		//
		.test("normal operation - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins zwei drei zwei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("normal operation- Throwing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins zwei drei zwei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("normal operation - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins zwei drei zwei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("bad line format - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"xxx abc 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		// -------------------------------------------------------------------
		.expect("eins eins drei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("bad line format - Throwing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"xxx abc 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("CAUGHT: BadLineFormat\n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("bad line format - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"xxx abc 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins ?wort-3? drei ?wort-5? vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("invalid word position - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3-5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("zwei eins eins zwei drei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("invalid word position - Throwing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3-5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("CAUGHT: InvalidWordPos\n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("invalid word position - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3-5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("zwei eins eins zwei drei ?wort-5? vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
      	.test("duplicate word - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"drei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 3 6 8"		"\n")
		.expect("eins eins drei drei drei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("duplicate word - Throwing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"drei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("CAUGHT: DuplicateWord\n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("duplicate word - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"drei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins drei drei drei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
      	.test("duplicate word position - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 3 6 8"		"\n")
		.expect("eins eins zwei drei zwei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("duplicate word position - Throwing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3"		"\n"
				"drei: 4"		"\n"
				"vier: 3 6 8"		"\n")
		.expect("CAUGHT: DuplicateWordPos\n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("duplicate word position - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"zwei: 3 5"		"\n"
				"drei: 4"		"\n"
				"vier: 3 6 8"		"\n")
		.expect("eins eins zwei drei zwei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)



		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test("missing word position - NonThrowing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins drei vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<NonThrowing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
      	.test("missing word position - Throwing")
		// -------------------------------------------------------------------
      	.supply("eins: 1 2 7"	"\n"
				"drei: 3 5"		"\n"
				"vier: 6 8"		"\n")
		.expect("CAUGHT: MissingWordPos\n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Throwing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
      	.test("missing word position - Replacing")
		// -------------------------------------------------------------------
		.supply("eins: 1 2 7"	"\n"
				"drei: 4"		"\n"
				"vier: 6 8"		"\n")
		.expect("eins eins ?wort-3? drei ?wort-5? vier eins vier \n")
		// -------------------------------------------------------------------
		.run_to_return(aufg5_demo<Replacing_WordPositioner>)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		//
		.test_cincout("type words to position", aufg5_demo<Replacing_WordPositioner>)
		.summarize()
		;
}
