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
	// Der sehr systematische Code zur Definition der abgeleiteten
	// Klassen für die einzelnen Fehler legt die Verwendung eines
	// Praeprozessor-Makros nahe, um typische "copy&paste"-Fehler
	// zu vermeiden:
	//
#define	DEFINE_ERROR_SUBCLASS(SubClassName)\
	class SubClassName : public Error {\
	public:\
		SubClassName()\
			: Error(#SubClassName) {}\
	};
    //	---------------------------------------
	DEFINE_ERROR_SUBCLASS(InvalidWordPos)
	DEFINE_ERROR_SUBCLASS(BadLineFormat)
	DEFINE_ERROR_SUBCLASS(DuplicateWord)
	DEFINE_ERROR_SUBCLASS(DuplicateWordPos)
	DEFINE_ERROR_SUBCLASS(MissingWordPos)
    //	---------------------------------------
#undef	DEFINE_ERROR_SUBCLASS

	void read(istream& is);

	void write(ostream& os) const;

protected:
	virtual void error_BadLineFormat()			const =0;
	virtual void error_InvalidWordPos()			const =0;
	virtual void error_DuplicateWord()			const =0;
	virtual void error_DuplicateWordPos()			const =0;
	// TO-BE-DONE: chose parameters as necessary
	virtual void error_MissingWordPos(... ???...)	const =0;
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

void WordPositioner::write(ostream& out) const {
	int npos = 0;
	for (auto it = allwords.begin(); it != allwords.end(); ++it) {
		while (it->first > 0
		    && ++npos < it->first) {
			// TO-BE-DONE: hand over more error information
			error_MissingWordPos(... ??? ...);
		}
		out << *(it->second) << ' ';
	}
	out << endl;
}

class Throwing_WordPositioner
	: public WordPositioner {
protected:
	virtual void error_BadLineFormat()	const { throw BadLineFormat(); }
	virtual void error_InvalidWordPos()	const { throw InvalidWordPos(); }
	virtual void error_DuplicateWord()	const { throw DuplicateWord(); }
	virtual void error_DuplicateWordPos()	const { throw DuplicateWordPos(); }
	virtual void error_MissingWordPos(int, ostream&)
						const { throw MissingWordPos(); }
};

class NonThrowing_WordPositioner
	: public WordPositioner {
protected:
	virtual void error_BadLineFormat()	const { /*empty*/ }
	virtual void error_InvalidWordPos()	const { /*empty*/ }
	virtual void error_DuplicateWord()	const { /*empty*/ }
	virtual void error_DuplicateWordPos()	const { /*empty*/ }
	virtual void error_MissingWordPos(int, ostream&)
						const { /*empty*/ }
};

class Replacing_WordPositioner
	: public NonThrowing_WordPositioner {
protected:
	virtual void error_MissingWordPos(int n, ostream& os) const {
		// TO-BE-DONE: generate output "?word-N" if word N is missing
		os << ...
	}
};

template<class SelectedWordPositioner>
void aufg4_demo(std::istream& in, std::ostream& out) {
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

#ifndef TDD

int main() {
	aufg4_demo<NonThrowing_WordPositioner>(std::cin, std::cout);
	// aufg4_demo<Throwing_WordPositioner>(std::cin, std::cout);
	// aufg4_demo<Replacing_WordPositioner>(std::cin, std::cout);
}

#else

#include <cassert>
#include <sstream>

void test_normal_operation_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_normal_operation_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_normal_operation_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_bad_line_format_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei vier eins vier \n");
}

void test_bad_line_format_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: BadLineFormat\n");
}

void test_bad_line_format_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins ?word-3? drei "
	                                "?word-5? vier eins vier \n");
}

void test_invalid_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "zwei eins eins zwei drei vier eins vier \n");
}

void test_invalid_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: InvalidWordPos\n");
}

void test_invalid_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "zwei eins eins zwei drei "
	                                "?word-5? vier eins vier \n");
}

void test_duplicate_word_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei drei vier eins vier \n");
}

void test_duplicate_word_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: DuplicateWord\n");
}

void test_duplicate_word_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei drei vier eins vier \n");
}

void test_duplicate_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei zwei vier eins vier \n");
}

void test_duplicate_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: DuplicateWordPos\n");
}

void test_duplicate_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei zwei vier eins vier \n");
}

void test_missing_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei vier eins vier \n");
}

void test_missing_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: MissingWordPos\n");
}

void test_missing_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg4_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins ?word-3? drei "
	                                "?word-5? vier eins vier \n");
}

int main() {
	test_normal_operation_NonThrowing();
	test_normal_operation_Throwing();
	test_normal_operation_Replacing();

#if 0
	// Tipp: für schnelle Erfolgserlebnisse schalten
	// Sie die Tests erst nach und nach frei, sobald
	// Sie das jeweilige Features implementiert haben
	//
	test_bad_line_format_NonThrowing();
	test_bad_line_format_Throwing();
	test_bad_line_format_Replacing();

	test_invalid_word_position_NonThrowing();
	test_invalid_word_position_Throwing();
	test_invalid_word_position_Replacing();

	test_duplicate_word_NonThrowing();
	test_duplicate_word_Throwing();
	test_duplicate_word_Replacing();

	test_duplicate_word_position_NonThrowing();
	test_duplicate_word_position_Throwing();
	test_duplicate_word_position_Replacing();

	test_missing_word_position_NonThrowing();
	test_missing_word_position_Throwing();
	test_missing_word_position_Replacing();
#endif

	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
