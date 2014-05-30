#include <cstdio>
#include <string>

class FileRes {
private:
	FILE *fp_;
public:
	FileRes(const std::string &nm, const std::string &md = "r")
		: fp_(fopen(nm.c_str(), md.c_str())) {
	}
	~FileRes() {
		if (fp_) fclose(fp_);
	}
	operator FILE*() {
		return fp_;
	}
	operator const FILE*() const {
		return fp_;
	}
};

#include "IODrive.h"

const std::string TESTFILE("testfile.txt");

const char HELLO_MSG[] = "hello, world\n";

void create_test_file(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "w");
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ fputs(HELLO_MSG, fres) == 1		] << "write line succeeds";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
}

void read_test_file(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE);
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	char line[100];
	const size_t NCHARS = (sizeof line) - 1;
	chk[ fgets(line, NCHARS, fres) == line	] << "reading one line succeeds";
	chk[ strcmp(line, HELLO_MSG) == 0		] << "line read contains 'hello, world\\n'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ getc(fres) == EOF	 				] << "reading one more char returns EOF'";
	chk[ std::feof(fres) == 1				] << "eof-state is set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
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
	.test_assertions("via file resource create test file", create_test_file)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("via file resource read test file", read_test_file)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.summarize();
}
