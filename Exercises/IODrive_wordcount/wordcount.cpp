#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

void wordcount(istream &in, ostream& out) {

	int nchars = 0;
	int nwords = 0;
	int nlines = 0;
	bool inword = false;
	char ch;
	while (in.get(ch)) {
		++nchars;
		if (isspace(ch))
			inword = false;
		else if (!inword) {
			++nwords;
			inword = true;
		}
		if (ch == '\n')
			++nlines;
	}
	out << ' ' << nchars
	    << ' ' << nwords
	    << ' ' << nlines << endl;
}

#include "IODrive.h"

int main(int argc, char* argv[]) {

	IODrive(cout)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("empty input")
	// ---------------------------------------------------------------------------------------
	.expect(" 0 0 0\n")
	.run_to_return(wordcount)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("one word in one line")
	// ---------------------------------------------------------------------------------------
	.supply("hello\n")
	.expect(" 6 1 1\n")
	.run_to_return(wordcount)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("three words in two lines")
	// ---------------------------------------------------------------------------------------
	.supply("one\n"
		"two three\n")
	.expect(" 14 3 2\n")
	.run_to_return(wordcount)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test("two words in three lines")
	// ---------------------------------------------------------------------------------------
	.supply("one\n"
		"\n"
		"three\n")
	.expect(" 11 2 3\n")
	.run_to_return(wordcount)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.summarize();
}
