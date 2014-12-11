#include "ITrace.h"

#include <stdexcept>
#include <string>

std::map<std::string, int> ITrace::typesid;

std::string ITrace::mbrace(int s) {
	std::string result("<>");
	do 
		result.insert(1, 1, (char)(s%10 + '0'));
	while (s /= 10);
	return result;
}

ITrace::ITrace(const std::string &t)
		: type(t), sid(++typesid[t]) {
	allow(" - creating " + *this);
}

ITrace::ITrace(const ITrace &init)
		: type(init.type), sid(++typesid[init.type]) {
	allow(" - copyctor " + *this + " from " + mbrace(init.sid));
}

ITrace &ITrace::operator=(const ITrace &rhs) {
	allow(" - copy op= " + *this + " from " + mbrace(rhs.sid));
	return *this;
}

ITrace::~ITrace() {
	allow(" - deleting " + *this);
}

ITrace::operator std::string() const {
	return type + mbrace(sid);
}

void ITrace::allow(const std::string &txt, const std::string &failure) {
	std::cout << txt << " ..." << std::flush;
	std::string answer;
	if (std::getline(std::cin, answer) && !answer.empty())
		throw std::runtime_error(failure);
}
