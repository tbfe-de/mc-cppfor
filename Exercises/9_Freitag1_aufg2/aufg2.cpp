#include <cstdio>
#include <string>

class FileRes {
private:
	FILE *fp_;
	std::string name_;
	std::string mode_;
public:
	std::string name() const { return name_; }

	std::string mode() const { return mode_; }

	// ..........
	// TO-BE-DONE
	// ..........

	operator FILE*() {
		return fp_;
	}

	operator const FILE*() const {
		return fp_;
	}

};

#include "IODrive.h"

const std::string TESTFILE("testfile.txt");

void create_closed_file_and_open(IODrive::AssertStream& chk) {
	FileRes fres;
	chk[ fres.operator bool() == false		] << "converts to bool 'false'";
	chk[ fres.name().empty() == true		] << "name is empty";
	chk[ fres.mode().empty() == true		] << "mode is empty";
	chk[ fres.operator FILE *() == 0		] << "type-cast to 'FILE*' is null";
	fres.open(TESTFILE, "w");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("w")	] << "mode is 'w'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ fres.close() == 0					] << "close will succeed";
	chk[ fres.operator bool() == false		] << "converts to bool 'false'";
	chk[ fres.name().empty() == true		] << "name is empty";
	chk[ fres.mode().empty() == true		] << "mode is empty";
	chk[ fres.operator FILE *() == 0		] << "type-cast to 'FILE*' is null";
}

void open_existing_file_and_write(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "w");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("w")	] << "mode is 'w'";
	chk[ fres.operator FILE *() != 0		] << "type-cast to 'FILE*' is valid";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	const char line[] = "hello, world\n";
	chk[ fputs(line, fres) == 1				] << "write line succeeds";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
}

void open_existing_file_and_read(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "r");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ fres.operator FILE *() != 0		] << "type-cast to 'FILE*' is valid";
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
	.test_assertions("create closed file and open", create_closed_file_and_open)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("open existing file and write", open_existing_file_and_write)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("open existing file and read", open_existing_file_and_read)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.summarize();
}
