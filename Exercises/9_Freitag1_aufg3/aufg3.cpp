#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <string>

class FileRes {
private:
	FILE *fp_;
	std::string name_;
	std::string mode_;
public:
	// TO-BE-DONE: add local exception class and throw an
	//			   instance of it for the errors specified
	//			   in the excercise text ...

	std::string name() const { return name_; }

	std::string mode() const { return mode_; }

	void open(const std::string&, const std::string&);

	int close();

	FileRes()
		: fp_(0), name_(), mode_()
	{}

	FileRes(const std::string &nm, const std::string &md = "r")
		: fp_(0), name_(), mode_() {
		open(nm, md);
	}

	~FileRes() {
		static_cast<void>(close());
	}

	operator FILE*() {
		return fp_;
	}

	operator const FILE*() const {
		return fp_;
	}

	operator bool() const {
		return (fp_ != 0);
	}
};

void FileRes::open(const std::string& n, const std::string& m = "r") {
	static_cast<void>(close());
	fp_ = std::fopen(n.c_str(), m.c_str());
	name_ = n;
	mode_ = m;
}

int FileRes::close() {
	if (fp_ == 0) return 0;
	const int r(std::fclose(fp_));
	fp_ = 0;
	mode_.clear();
	name_.clear();
	return r;
}

const std::string TESTFILE("testfile.txt");

void create_file_and_open(IODrive::AssertStream& chk) {
	FileRes fres;
	chk[ fres.operator bool() == false		] << "converts to bool 'false'";
	chk[ fres.name().empty() == true		] << "name is empty";
	chk[ fres.mode().empty() == true		] << "mode is empty";
	chk[ throws_on_typecast(fres) == true	] << "will throw on type-cast to 'FILE*'";
	fres.open(TESTFILE, "w");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("w")	] << "mode is 'w'";
	chk[ fres.operator FILE *() != 0		] << "will type-cast to 'FILE*'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	chk[ fres.close() == 0					] << "close will succeed";
}

void open_file_and_write(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "w");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("w")	] << "mode is 'w'";
	chk[ fres.operator FILE *() != 0		] << "will type-cast to 'FILE*'";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
	const char line[] = "hello, world\n";
	chk[ fputs(line, fres) == 1				] << "write line succeeds";
	chk[ std::feof(fres) == 0				] << "eof-state not set";
	chk[ std::ferror(fres) == 0				] << "error-state not set";
}

void open_file_and_read(IODrive::AssertStream& chk) {
	FileRes fres(TESTFILE, "r");
	chk[ fres.operator bool() == true		] << "converts to bool 'true'";
	chk[ fres.name() == TESTFILE			] << "name is '" << TESTFILE << "'";
	chk[ fres.mode() == std::string("r")	] << "mode is 'r'";
	chk[ fres.operator FILE *() != 0		] << "will type-cast to 'FILE*'";
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
	.test_assertions("via file resource create and open file", create_file_and_open)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("via file resource open and write file", open_file_and_write)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	.test_assertions("via file resource open and read file", open_file_and_read)

	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//
	.summarize();
}
