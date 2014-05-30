/*
 ================================================================================
 Print words "in order" according to the position after each word.
 ================================================================================
*/
#ifndef WORD_POSITIONER_H
#define WORD_POSITIONER_H

#include <iostream>
#include <map>
#include <set>
#include <string>

class WordPositioner {
	typedef std::set<std::string> WORDSET;
	typedef std::map<int, WORDSET::const_iterator> WORDMAP;
	WORDSET seen;
	WORDMAP words;
public:
	void read(std::istream&);
	void write(std::ostream&) const;
};

#endif
