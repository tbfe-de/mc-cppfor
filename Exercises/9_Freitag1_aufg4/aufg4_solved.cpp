#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <string>

class FileRes {
private:
	FILE *fp_;
	std::string name_;
	std::string mode_;
	int errno_;
public:
	class NotOpen
		: public std::runtime_error {
	public:
		NotOpen()
		    : std::runtime_error("FileRes::NotOpen")
		{}
	};

	std::string name() const { return name_; }

	std::string mode() const { return mode_; }

	int error() const { return errno_; }

	void open() { open(name_, mode_); }

	void open(const std::string&, const std::string&);

	int close();

	int remove();

	FileRes()
		: fp_(0), name_(), mode_()
	{}

	FileRes(const std::string &nm, const std::string &md)
		: fp_(0), name_(), mode_() {
		open(nm, md);
	}

	~FileRes() {
		static_cast<void>(close());
	}

	operator FILE*() {
		if (fp_ == 0) throw NotOpen();
		return fp_;
	}

	operator const FILE*() const {
		if (fp_ == 0) throw NotOpen();
		return fp_;
	}

	operator bool() {
		return (fp_ != 0);
	}

	operator bool() const {
		return (fp_ != 0);
	}
};

void FileRes::open(const std::string& nm, const std::string& md) {
	static_cast<void>(close());
	name_ = nm;
	mode_ = md;
	if (nm.empty() || md.empty()) throw NotOpen();
	fp_ = std::fopen(nm.c_str(), md.c_str());
	if (fp_ == 0) {
		errno_ = errno;
		throw NotOpen();
	}
}

int FileRes::close() {
	if (fp_ == 0) return 0;
	const int r(std::fclose(fp_));
	errno_ = errno;
	fp_ = 0;
	return r;
}

int FileRes::remove() {
	static_cast<void>(close());
	if (name_.empty()) return -1;
	return std::remove(name_.c_str());
}

#include "IODrive.h"

bool throws_on_typecast(const FileRes &f) {
	try {
		f.operator const FILE*();
	}
	catch (FileRes::NotOpen &) { return true; }
	catch (...) {}
	return false;
}

const std::string TESTFILE("testfile.txt");
const std::string BAD_FILE("this-file-should-not-exist");

void open_non_existing_file(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "r");
	chk[false] << "did not throw as expected";
}

void create_open_for_write(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "w");
	chk[ fres.operator bool() == true		] << "converts to bool value 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("w")	] << "mode is 'w'";
	chk[ fres.operator FILE *() != 0		] << "will type-cast to 'FILE*'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ fputs("hello, world\n", fres) >= 0	] << "line of output written";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
}


void create_default_not_open(IODrive::AssertStream& chk) {
	FileRes fres;
	chk[ fres.operator bool() == false		] << "converts to bool value 'false'";
	chk[ fres.name().empty() == true		] << "name is empty";
	chk[ fres.mode().empty() == true		] << "mode is empty";
	chk[ throws_on_typecast(fres) == true	] << "will throw on type-cast to 'FILE*'";
	chk[ fres.open(TESTFILE, "r"), true		] << "will open for read";
	chk[ fres.operator bool() == true		] << "converts to bool value 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ throws_on_typecast(fres) == false	] << "will type-cast to 'FILE*'";
	chk[ fres.close() == 0					] << "will close with result '0'";
	chk[ fres.operator bool() == false		] << "converts to bool value 'false'";
	chk[ fres.name() == TESTFILE			] << "name is '" << fres.name() << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is '" << fres.mode() << "'";
	chk[ throws_on_typecast(fres) == true	] << "will not throw on type cast";
}

void create_open_for_read(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "r");
	chk[ fres.operator bool() == true		] << "converts to bool value 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ throws_on_typecast(fres) == false	] << "will type-cast to 'FILE*'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	char line[100];
	const size_t NCHARS = (sizeof line) - 1;
	chk[ fgets(line, NCHARS, fres) == line	] << "reading one line succeeds";
	chk[ strcmp(line, "hello, world\n") == 0] << "line read contains 'hello, world\\n'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ getc(fres) == EOF	 				] << "reading one more char returns EOF'";
	chk[ std::feof(fres) == 1				] << "eof-state is set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ throws_on_typecast(fres) == false	] << "will type-cast to 'FILE*'";
	chk[ fres.remove() == 0					] << "removing file succeeds";
	chk[ fres.operator bool() == false		] << "converts to bool value 'false'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ throws_on_typecast(fres) == true	] << "will throw on type-cast to 'FILE*'";
}

int main(int argc, char* argv[]) {
	return IODrive(std::cout)
	//	.config_details_uncond(true)
	//	.config_titles_only(true)
	//	.config_summary_only(true)
	//	.config_no_summary(true)
	//	.config_failure_stop(true)
	//	.config_interactive_mode(true)
	//	.config_page_output(true)
	//	.config_line_length(60)
		.config(argc, argv)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("file resource constructed open for write", create_open_for_write)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("file resource constructed per default", create_default_not_open)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("file resource constructed open for read", create_open_for_read)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.summarize();
}
