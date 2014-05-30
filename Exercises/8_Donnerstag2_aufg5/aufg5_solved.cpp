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
	using Policy::error_BadLineFormat;
	using Policy::error_InvalidWordPos;
	using Policy::error_DuplicateWord;
	using Policy::error_DuplicateWordPos;
	using Policy::error_MissingWordPos;

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
	void error_BadLineFormat()			const { /*empty*/ }
	void error_InvalidWordPos()			const { /*empty*/ }
	void error_DuplicateWord()			const { /*empty*/ }
	void error_DuplicateWordPos()			const { /*empty*/ }
	void error_MissingWordPos(int, ostream&)	const { /*empty*/ }
};
typedef WordPositioner<NonThrowing> NonThrowing_WordPositioner;

class Throwing {
public:
#	define	DEFINE_ERROR_SUBCLASS(SubClassName)\
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
#	undef	DEFINE_ERROR_SUBCLASS

protected:
	void error_BadLineFormat() const {
		throw Throwing::BadLineFormat();
	}
	void error_InvalidWordPos() const {
		throw Throwing::InvalidWordPos();
	}
	void error_DuplicateWord() const {
		throw Throwing::DuplicateWord();
	}
	void error_DuplicateWordPos() const {
		throw Throwing::DuplicateWordPos();
	}
	void error_MissingWordPos(int, ostream&) const {
		throw Throwing::MissingWordPos();
	}
};
typedef WordPositioner<Throwing> Throwing_WordPositioner;

class Replacing
	: protected NonThrowing {
protected:
	void error_MissingWordPos(int n, ostream& os) const {
		os << "?word-" << n << "? ";
	}
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

#define TDD
#ifndef TDD

int main() {
	aufg5_demo<NonThrowing_WordPositioner>(std::cin, std::cout);
	// aufg5_demo<Throwing_WordPositioner>(std::cin, std::cout);
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
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_normal_operation_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_normal_operation_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei "
	                                "zwei vier eins vier \n");
}

void test_bad_line_format_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei vier eins vier \n");
}

void test_bad_line_format_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: BadLineFormat\n");
}

void test_bad_line_format_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "xxx abc 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins ?word-3? drei "
	                                "?word-5? vier eins vier \n");
}

void test_invalid_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "zwei eins eins zwei drei vier eins vier \n");
}

void test_invalid_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: InvalidWordPos\n");
}

void test_invalid_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3-5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "zwei eins eins zwei drei "
	                                "?word-5? vier eins vier \n");
}

void test_duplicate_word_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei drei vier eins vier \n");
}

void test_duplicate_word_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: DuplicateWord\n");
}

void test_duplicate_word_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei drei drei vier eins vier \n");
}

void test_duplicate_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei zwei vier eins vier \n");
}

void test_duplicate_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: DuplicateWordPos\n");
}

void test_duplicate_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "zwei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 3 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins zwei drei zwei vier eins vier \n");
}

void test_missing_word_position_NonThrowing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<NonThrowing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei vier eins vier \n");
}

void test_missing_word_position_Throwing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Throwing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: MissingWordPos\n");
}

void test_missing_word_position_Replacing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg5_demo<Replacing_WordPositioner>(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins ?word-3? drei "
	                                "?word-5? vier eins vier \n");
}

int main() {
	test_normal_operation_NonThrowing();
	test_normal_operation_Throwing();
	test_normal_operation_Replacing();

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

	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
