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
				throw DuplicateWord();
			int pos;
			while (iss >> pos) {
				if (pos <= 0)
					throw InvalidWordPos();
				if (!allwords.insert(std::make_pair(pos, result.first)).second)
					throw DuplicateWordPos();
				++npos;
			}
		}
		if (npos == 0 || !iss.eof())
			throw BadLineFormat();
	}
}

void WordPositioner::write(ostream& out) const {
	int npos = 0;
	for (auto it = allwords.begin(); it != allwords.end(); ++it) {
		if (++npos < it->first)
			throw MissingWordPos();
		out << *(it->second) << ' ';
	}
	out << endl;
}

void aufg2_demo(istream &in, ostream &out) {
	try {
		std::ostringstream os;
		WordPositioner wp;
		wp.read(in);
		wp.write(os);
		out << os.str();
	}
	catch (const exception &ex) {
		out << "CAUGHT: " << ex.what() << endl;
	}
}

#define TDD
#ifndef TDD

int main() {
	aufg2_demo(cin, cout);
}

#else

#include <cassert>
#include <sstream>
using namespace std;

void test_valid_input() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "eins eins drei fünf "
	                                "drei vier eins vier \n");
}

void test_word_duplicated() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "drei: 4"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() == "CAUGHT: duplicate word\n");
}

void test_position_duplicated() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "fünf: 3"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: duplicate word position\n");
}

void test_position_invalid() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: -1"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: invalid word position\n");
}

void test_position_missing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 5"	"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: missing word position\n");
}

void test_invalid_line_colon_missing() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei; 3"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: bad line format\n");
}

void test_invalid_line_no_word_position() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: "		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: bad line format\n");
}

void test_invalid_line_1st_word_position() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: X"		"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: bad line format\n");
}

void test_invalid_line_2nd_word_position() {
	istringstream prepared_input("eins: 1 2 7"	"\n"
	                             "drei: 3 X"	"\n"
	                             "vier: 6 8"	"\n");
	ostringstream expected_output;
	aufg2_demo(prepared_input, expected_output);
	assert(expected_output.str() ==	"CAUGHT: bad line format\n");
}

int main() {
	test_valid_input();
	test_word_duplicated();
	test_position_duplicated();
	test_position_invalid();
	test_position_missing();
	test_invalid_line_colon_missing();
	test_invalid_line_no_word_position();
	test_invalid_line_1st_word_position();
	test_invalid_line_2nd_word_position();

	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
