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
#include <stdexcept>
	using std::exception;
	using std::runtime_error;
#include <string>
	using std::string;

class WordPositioner {
	typedef set<string> WORDSET;
	typedef map<int, WORDSET::const_iterator> WORDMAP;
	WORDSET seen;
	WORDMAP allwords;
public:
	class Error : public std::runtime_error {
	protected:
		Error(const char *text)
			: std::runtime_error(text)
		{}
	};
	class BadLineFormat : public Error {
	public:
		BadLineFormat()
			: Error("bad line format") {}
	};
	class InvalidWordPos : public Error {
	public:
		InvalidWordPos()
			: Error("invalid word position")
		{}
	};
	class DuplicateWord : public Error {
	public:
		DuplicateWord()
			: Error("duplicate word")
		{}
	};
	class DuplicateWordPos : public Error {
	public:
		DuplicateWordPos()
			: Error("duplicate word position")
		{}
	};
	class MissingWordPos : public Error {
	public:
		MissingWordPos()
			: Error("missing word position")
		{}
	};

	void read(istream& is);

	void write(ostream& os) const;

protected:
	virtual void throw_BadLineFormat()		const =0;
	virtual void throw_InvalidWordPos()		const =0;
	virtual void throw_DuplicateWord()		const =0;
	virtual void throw_DuplicateWordPos()		const =0;
	virtual void throw_MissingWordPos()		const =0;
};

void WordPositioner::read(istream& in) {
	string line;
	while (getline(in, line)) {
		istringstream iss(line);
		int npos = 0;
		string w;
		if (getline(iss, w, ':')) {
			const auto result = seen.insert(w);
			if (!result.second)
				throw_DuplicateWord();
			int pos;
			const int snpos = npos;
			while (iss >> pos) {
				if (pos <= 0)
					throw_InvalidWordPos();
				if (!allwords.insert(std::make_pair(pos, result.first)).second)
					throw_DuplicateWordPos();
				++npos;
			}
			if (npos == snpos)
				throw_BadLineFormat();
			if (!iss.eof())
				throw_InvalidWordPos();
		}
	}
}

void WordPositioner::write(ostream& out) const {
	int npos = 0;
	for (auto it = allwords.begin(); it != allwords.end(); ++it) {
		if (++npos < it->first)
			throw_MissingWordPos();
		out << *(it->second) << ' ';
	}
	out << endl;
}

class Throwing_WordPositioner
	: public WordPositioner {
protected:
	/* Der sehr systematische Code dieser Funktionen und vor allem die
	   zweimalige legt die Verwendung des Namens dder Exception-Klasse
	   legt die Verwendung eines Praeprozessor-Makros nahe, also statt:
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	virtual void throw_BadLineFormat()	const { throw BadLineFormat();	  }
	virtual void throw_InvalidWordPos()	const { throw InvalidWordPos();   }
	virtual void throw_DuplicateWord()	const { throw DuplicateWord(); }
	virtual void throw_DuplicateWordPos()	const { throw DuplicateWordPos(); }
	virtual void throw_MissingWordPos()	const { throw MissingWordPos();   }
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	*/
#define	DEFINE_THROWER(ErrorSubClass)\
	virtual void throw_ ## ErrorSubClass() const\
	{\
		 throw ErrorSubClass();\
	}
    //	--------------------------------
	DEFINE_THROWER(BadLineFormat)
	DEFINE_THROWER(InvalidWordPos)
	DEFINE_THROWER(DuplicateWord)
	DEFINE_THROWER(DuplicateWordPos)
	DEFINE_THROWER(MissingWordPos)
    //	--------------------------------
#undef 	DEFINE_THROWER

};

class NonThrowing_WordPositioner
	: public WordPositioner {
protected:
	/* Auch hier laesst sich der systematische Code wieder
	   durch einen Praeprozessor-Makro abkuerzen:
	- - - - - - - - - - - - - - - - - - - - - - - - - - - -
	virtual void throw_BadLineFormat()	const {}
	virtual void throw_InvalidWordPos()	const {}
	virtual void throw_DuplicateWord()	const {}
	virtual void throw_DuplicateWordPos()	const {}
	virtual void throw_MissingWordPos()	const {}
	- - - - - - - - - - - - - - - - - - - - - - - - - - - -
	*/
#define	DEFINE_THROWER(ErrorSubClass)\
	virtual void throw_ ## ErrorSubClass() const {}
    //	--------------------------------
	DEFINE_THROWER(BadLineFormat)
	DEFINE_THROWER(InvalidWordPos)
	DEFINE_THROWER(DuplicateWord)
	DEFINE_THROWER(DuplicateWordPos)
	DEFINE_THROWER(MissingWordPos)
    //	--------------------------------
#undef 	DEFINE_THROWER
};

#include <sstream>
	using std::istringstream;
	using std::ostringstream;

template<class SelectedWordPositioner>
void aufg3_demo(std::istream& in, std::ostream& out) {
	try {
		SelectedWordPositioner wp;
		wp.read(in);
		std::ostringstream os;
		wp.write(os);
		out << os.str();
	}
	catch (const std::exception &ex) {
		out << "CAUGHT: " << ex.what() << std::endl;
	}
}

#define TDD
#ifndef TDD

int main() {
	aufg3_demo<NonThrowing_WordPositioner>(std::cin, std::cout);
	// aufg3_demo<Throwing_WordPositioner>(std::cin, std::cout);
}

#else

#include <cassert>
#include <sstream>

void test_normal_operation_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei fünf "
	                                "drei vier eins vier \n");
}

void test_normal_operation_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei fünf "
	                                "drei vier eins vier \n");
}

void test_bad_line_format_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei fünf drei vier eins vier \n");
}

void test_bad_line_format_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: bad line format\n");
}

void test_invalid_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "zwei eins eins zwei drei vier eins vier \n");
}

void test_invalid_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: invalid word position\n");
}

void test_duplicate_word_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei drei vier eins vier \n");
}

void test_duplicate_word_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: duplicate word\n");
}

void test_duplicate_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 3"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei vier eins vier \n");
}

void test_duplicate_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 3"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: duplicate word position\n");
}

void test_missing_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei vier eins vier \n");
}

void test_missing_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg3_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: missing word position\n");
}

int main() {
	test_normal_operation_NonThrowing();
	test_normal_operation_Throwing();
	test_bad_line_format_NonThrowing();
	test_bad_line_format_Throwing();
	test_invalid_word_position_NonThrowing();
	test_bad_line_format_Throwing();
	test_invalid_word_position_NonThrowing();
	test_invalid_word_position_Throwing();
	test_duplicate_word_NonThrowing();
	test_duplicate_word_Throwing();
	test_duplicate_word_position_NonThrowing();
	test_duplicate_word_position_Throwing();
	test_missing_word_position_NonThrowing();
	test_missing_word_position_Throwing();

	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
