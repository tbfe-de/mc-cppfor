#ifndef Value_IO_H
#define VALUE_IO_H

#include <iostream>

inline
std::ostream& operator<<(std::ostream& lhs, const Value& rhs) {
	return rhs.print(lhs);
}

#endif
