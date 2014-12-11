#ifndef ITrace_h
#define ITrace_h

#include <iostream>
#include <string>
#include <map>

class ITrace {
	static std::map<std::string, int> typesid;
	static std::string mbrace(int);
	std::string type;
	int sid;
public:
	ITrace(const std::string &);
	ITrace(const ITrace &);
	ITrace &operator=(const ITrace &);
	~ITrace();
	operator std::string() const;
	static void allow(const std::string&, const std::string & = "operation aborted");
};

inline std::string operator+(const char *lhs, const ITrace &rhs) {
	return std::string(lhs) + std::string(rhs);
}

inline std::string operator+(const std::string &lhs, const ITrace &rhs) {
	return lhs + std::string(rhs);
}

#endif
