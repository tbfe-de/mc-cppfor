#include "IODrive.h"

using namespace std;

void IODrive::helpPage() {
	testOutput
		<< "## IODrive valid options are:       (DEFAULT if not specified)"	<< endl
		<< "##   -?    show this help page      (only for invalid options)"	<< endl
		<< "##   -c    estimate CPU time        (no cpu time estimate)"		<< endl
		<< "##   -f    stop on first FAILURE    (all tests are run)"		<< endl
		<< "##   -i    INTERACTIVE mode         (prepared tests run)"		<< endl
		<< "##   -p    PAGE through output      (do not wait for confirm)"	<< endl
		<< "##   -q    QUIET summary			(show textual summary)"		<< endl
		<< "##   -s    show only SUMMARY        (show also test titles)"	<< endl
		<< "##   -t    show only TITLES         (show also test details)"	<< endl
		<< "##   -u    details UNconditionally  (for failed tests only)"	<< endl
		<< "##   -<N>  title length <N> char-s  (72)"						<< endl
	;
}

bool IODrive::nameCompare(const string& testToActivate, const string& testTitle) {
	string::const_iterator itActivate = testToActivate.begin();
	string::const_iterator itTitle = testTitle.begin();
	while ((itActivate != testToActivate.end())	&& (itTitle != testTitle.end())) {
		if ((*itActivate == *itTitle) || (*itActivate == tolower(*itTitle))) {
			++itTitle;
		}
		else while ((*itActivate == '_') && !isalnum(*itTitle)) {
			if (++itTitle == testTitle.end())
				break;
		}
		++itActivate;
	}
	return (itActivate == testToActivate.end());
}

void IODrive::prepareTest() {
	testDetails.str(std::string());
	if (!summaryOnly) {
		testOutput << "** " << testToRun << ' ';
		for (std::string::size_type i = 12; i + testToRun.length() < lineLength; ++i)
			testOutput << '.';
		testOutput << ':';
		exceptionWhatString.clear();
		resultOK = false;
		outputOK = false;
		testOutput << ' ' << std::flush;
	}
	if (streamContainer != 0) {
		streamContainer->prepareExpectationChecks();
		streamContainer->prepareStateChanges();
		streamContainer->doStateChanges();
	}
}

bool IODrive::lookupActivation(const string& name) {
	if (testActivation.empty())
		return true;
	for (TestActivation::const_iterator it = testActivation.begin(); it != testActivation.end(); ++it) {
		if (nameCompare(*it, name))
			return true;
	}
	return false;
}

IODrive& IODrive::test_cincout(const std::string& name, std::function<void(std::istream&, std::ostream&)> testFunction) {
	if (!interactiveMode)
		return *this;
	testOutput << "## IODrive Interactive Start - " << name << endl;
	try {
		testFunction(std::cin, std::cout);
		testOutput << "## IODrive Interactive End";
		if (cin.eof())
			testOutput << " [eof]";
		else if (cin.fail())
			testOutput << " [fail]";
		testOutput << std::endl;
	}
	catch (std::exception& ex) {
		testOutput << "## IODrive Interactive - "
			   << ex.what() << " [" << typeid(ex).name() << "]" << std::endl;
	}
	catch (...) {
		testOutput << "## IODrive Interactive End [unknown exception]" << std::endl;
	}
	std::cin.clear();
	if (pageOutput) cin.get();
	return *this;
}

int IODrive::summarize() {
	if (interactiveMode)
		return EXIT_SUCCESS;
	const int testsFailed = testsRun - testsPassed;
	if (!noSummary) {
		if (testsFailed == 0 && testsSkipped == 0) {
			testOutput << "== all tests passed" << endl;
		}
		else if (testsFailed == 0 && testsSkipped > 0) {
			testOutput << "=~ " << testsPassed << " tests passed"
			      " / " << testsSkipped << " skipped " << endl;
		}
		else {
			testOutput << "!! " << testsFailed << " of " << testsRun << " tests failed" << endl;
			if (testsSkipped != 0)
				testOutput << " / " << testsSkipped << " skipped" << endl;
		}
	}
	return (testsFailed == 0)
		? EXIT_SUCCESS
		: EXIT_FAILURE;
}

IODrive& IODrive::config(int, char** argv) {
	string badOptions;
	bool showHelp = false;
	while (*++argv) {
		if (*argv[0] != '-')
			testActivation.insert(*argv);
		else {
			char *cp = (*argv);
			while (*++cp) {
				char* endp;
				switch (*cp) {
					case '?':
						showHelp = true;
						break;
					case 'e':
						estimateCputime = true;
						break;
					case 'f':
						failedStop = true;
						break;
					case 'i':
						interactiveMode = true;
						break;
					case 'p':
						pageOutput = true;
						break;
					case 'q':
						noSummary = true;
						break;
					case 's':
						summaryOnly = true;
						break;
					case 't':
						titlesOnly = true;
						break;
					case 'u':
						detailsUncond = true;
						break;
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						lineLength = strtol(cp, &endp, 10);
						cp = endp-1;
						break;
					default:
						showHelp = true;
						badOptions.append(cp, 1);
						break;
				}
			}
		}
	}
	if (showHelp) {
		helpPage();
		if (!badOptions.empty())
			testOutput << "## invalid option(s) specified: " << badOptions << endl;
	}
	return *this;
}

IODrive::IODrive(std::ostream& out)
	: testOutput(out)
	, streamContainer(0)
	// default configuration
	, estimateCputime(false)
	, detailsUncond(false)
	, titlesOnly(false)
	, summaryOnly(false)
	, noSummary(false)
	, interactiveMode(false)
	, pageOutput(false)
	, failedStop(false)
	, lineLength(72)
	// summary counters
	, testsRun(0)
	, testsPassed(0)
	, testsSkipped(0)
{}

IODrive::TestSpec IODrive::test(const std::string& title) {
	assert(streamContainer == 0);
	if (interactiveMode)
		return TestSpec(*this);
	if (!lookupActivation(title)
	 || (failedStop && (testsPassed != testsRun)))
		++testsSkipped;
	else {
		testToRun = title;
		streamContainer = new StreamContainer(*this);
	}
	return TestSpec(*this);
}

IODrive::TestSpec IODrive::supplyEof() {
	if (streamContainer)
		streamContainer->addStateChange(ios_base::eofbit);
	return TestSpec(*this);
}

IODrive::TestSpec IODrive::supplyFail() {
	if (streamContainer)
		streamContainer->addStateChange(ios_base::failbit);
	return TestSpec(*this);
}

IODrive::TestSpec IODrive::supplyInput(const std::string& supplied, const bool eol) {
	if (streamContainer)
		streamContainer->addSupplied(supplied, eol);
	return TestSpec(*this);
}

IODrive::TestSpec IODrive::expectOutput(const std::string& expected, const bool eol) {
	if (streamContainer)
		streamContainer->addExpected(expected, eol);
	return TestSpec(*this);
}

void IODrive::repeatForTimings(std::function<void(std::istream&, std::ostream&)> candidate) {
	int numberOfCalls = 0;
	float totalCpuTime = 0.0f;
	std::clock_t startTime = std::clock();
	do {
		int callsInLoop = 1 + 2*numberOfCalls;
		startTime = std::clock();
		while (callsInLoop-- > 0) {
			streamContainer->readyToRestart();
			streamContainer->prepareStateChanges();
			streamContainer->doStateChanges();
			candidate(streamContainer->supplyStream, streamContainer->receiveStream);
			++numberOfCalls;
		}
		totalCpuTime += std::clock() - startTime;
	} while (totalCpuTime < (1.0 * CLOCKS_PER_SEC));
	usecsPerCall = 1e6 * (totalCpuTime/CLOCKS_PER_SEC) / numberOfCalls;
}

template<>
bool IODrive::checkedCall<void>(const void* const result,
			        std::function<void(std::istream&, std::ostream&)> candidate) {
#if 0
	streamContainer->prepareExpectationChecks();
	streamContainer->prepareStateChanges();
	streamContainer->doStateChanges();
#endif
	streamContainer->supplyStream.seekg(0);
	candidate(streamContainer->supplyStream, streamContainer->receiveStream);
	if (streamContainer->checkFinallyReceived()
	 && estimateCputime)
		repeatForTimings(candidate);
	return true;
}

bool IODrive::validateAssertions() const {
	bool startLine = true;
	const std::string detailsString = testDetails.str();
	for (std::string::const_iterator it = detailsString.begin(); it != detailsString.end(); ++it) {
		if (startLine && *it == '-')
				return false;
		startLine = (*it == '\n');
	}
	return true;
}

IODrive& IODrive::test_assertions(const std::string& title, std::function<void(AssertStream&)> candidate) {
	assert(streamContainer == 0);
	if (interactiveMode)
		return *this;
	testToRun = title;
	prepareTest();
	try {
		AssertStream assertStream(testDetails);
		candidate(assertStream);
		outputOK = validateAssertions();
		terminatingException = 0;
	}
	catch (std::exception& ex) {
		testDetails << "<* " << ex.what() << " [" << typeid(ex).name() << "]" << std::endl;
		terminatingException = &typeid(ex);
		exceptionWhatString = ex.what();
	}
	catch (...) {
		testDetails << "<* [...]" << std::endl;
		terminatingException = &typeid(void);
	}
	++testsRun;
	if (terminatingException) {
		if (!summaryOnly)
			completeTest(false, "/x");
	}
	else if (!outputOK) {
		if (!summaryOnly) {
			std::string result = "/a";
			completeTest(false, result);
		}
	}
	else {
		if (!summaryOnly)
			completeTest(true);
		++testsPassed;
	}
	return *this;
}

void IODrive::StreamContainer::addSupplied(const string& supplied, const bool eol) {
	expectationChecks.insert(make_pair(suppliedContent.tellp(), expectedContent.tellp()));
	suppliedContent << supplied;
	if (eol)
		suppliedContent << endl;
}

void IODrive::StreamContainer::addExpected(const string& expected, const bool eol) {
	expectedContent << expected;
	if (eol)
		expectedContent << endl;
}

void IODrive::StreamContainer::compareHelper(istream& strm, string& part, bool& skip) {
	char ch;
	if (!strm.get(ch))
		return;
	if (!skip) {
		part.append(&ch, 1);
		if ((ch == '\n') && (firstDifference >= 0))
			skip = true;
	}
}

int IODrive::StreamContainer::SupplyBuffer::underflow() {
	streamContainer.doStateChanges();
	if (streamContainer.runTimings) {
		if (endpos+1 < size()) {
			char* const buffer_base = &operator[](0);
			setg(buffer_base, buffer_base+endpos, buffer_base+endpos+1);
			return static_cast<unsigned char>(buffer_base[endpos++]);
		}
		return EOF;
	}
	streamContainer.doExpectationChecks();
	const int c = streamContainer.supplyNextChar();
	if (c != EOF) {
		if (size() == capacity())
			reserve(2*capacity());
		back() = static_cast<char>(c);
		resize(size()+1);
		char* const buffer_base = &operator[](0);
		setg(buffer_base, buffer_base+endpos, buffer_base+endpos+1);
		endpos++;
	}
	return c;
}

std::streampos IODrive::StreamContainer::SupplyBuffer::seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which) {
	switch (way) {
	case std::ios_base::beg:
		return seekpos(off, which);
	case std::ios_base::cur:
		return seekpos((gptr() - eback()) + off, which);
	case std::ios_base::end:
		return seekpos(size() + off, which);
	default:
		return std::streambuf::seekoff(off, way, which);
	}
}

std::streampos IODrive::StreamContainer::SupplyBuffer::seekpos(std::streampos sp, std::ios_base::openmode which) {
	if (which != std::ios_base::in)
		return std::streambuf::seekpos(sp, which);
	if (sp < 0)
		return sp;
	if (sp > static_cast<std::streampos>(endpos))
		sp = static_cast<std::streampos>(endpos);
	char* const buffer_base = &operator[](0);
	setg(buffer_base, buffer_base + sp, buffer_base + endpos);
	return sp;
}

void IODrive::StreamContainer::readyToRestart() {
	// rewind streams - necessary for restarts
	suppliedContent.clear();
	suppliedContent.seekg(0);
	receiveStream.clear();
	receiveStream.seekp(0);
	supplyBuffer.reset();
	supplyStream.clear();
	supplyStream.seekg(0);
    runTimings = true;
}

void IODrive::StreamContainer::changeStateSupplied(ios_base::iostate nstate) {
	if (!processedInputLine.empty())
		showProcessedInput();
	string supplyChange;
	if (nstate & ios_base::eofbit)
		supplyChange.append("EOF ");
	if (nstate & ios_base::failbit)
		supplyChange.append("FAIL ");
	iodrive.prettyPrintLines(".>", supplyChange);
	supplyStream.clear(nstate);
}

bool IODrive::StreamContainer::checkFinallyReceived() {
	const int receivedNotYetChecked = receivedContent.tellp() - receivedContent.tellg();
	const int expectedNotYetChecked = expectedContent.tellp() - expectedContent.tellg();
	const int rangeNotYetChecked = receivedNotYetChecked > expectedNotYetChecked
					? receivedNotYetChecked
					: expectedNotYetChecked;
	checkActuallyReceived(rangeNotYetChecked);
	return (firstDifference < 0);
}

void IODrive::StreamContainer::checkActuallyReceived(string::size_type nchars) {
	if (firstDifference >= 0)
		return;
	string received;
	string expected;
	bool skip_r = false;
	bool skip_e = false;
	string::size_type discard = 0;
	for (string::size_type cpos = 0; cpos < nchars; ++cpos) {
		compareHelper(receivedContent, received, skip_r);
		compareHelper(expectedContent, expected, skip_e);
		if (received == expected) {
			if (isCompleteLine(received)) {
				iodrive.prettyPrintLines("<-", received);
				received.clear();
				expected.clear();
				discard = cpos + 1;
			}
			continue;
		}
		else if (firstDifference < 0) {
			firstDifference = cpos - discard;
		}
		if (firstDifference < 0)
			continue;
		if (isCompleteLine(received)
		 || isCompleteLine(expected))
			break;
	}
	if (firstDifference >= 0) {
		iodrive.prettyPrintLines("<-", received);
		iodrive.prettyPrintLines("<=", expected);
		string visualMarker;
		while (static_cast<int>(visualMarker.length()) < firstDifference)
			visualMarker.append("-");
		visualMarker.append("^");
		iodrive.prettyPrintLines("<?", visualMarker);
	}
}

void IODrive::StreamContainer::prepareStateChanges() {
	nextStateChange = stateChanges.begin();
}

void IODrive::StreamContainer::doStateChanges() {
	while ((nextStateChange != stateChanges.end())
	    && (supplyStream.tellg() >= nextStateChange->first)) {
		changeStateSupplied(nextStateChange->second);
		++nextStateChange;
	}
}

void IODrive::StreamContainer::prepareExpectationChecks() {
	firstDifference = -1;
	nextExpectationCheck = expectationChecks.begin();

}

void IODrive::StreamContainer::doExpectationChecks() {
	while ((nextExpectationCheck != expectationChecks.end())
	    && (supplyStream.tellg() >= nextExpectationCheck->first)) {
		checkActuallyReceived(static_cast<string::size_type>(nextExpectationCheck->second - expectedContent.tellg()));
		++nextExpectationCheck;
	}
}

void IODrive::StreamContainer::showProcessedInput() {
	iodrive.prettyPrintLines("->", processedInputLine);
	processedInputLine.clear();
}

int IODrive::StreamContainer::supplyNextChar() {
	const int c = suppliedContent.get();
	if (c != EOF) {
		const char ch = static_cast<char>(c);
		processedInputLine.append(&ch, 1);
		if (ch == '\n')
			showProcessedInput();
	}
	else {
		if (!processedInputLine.empty())
			showProcessedInput();
	}
	return c;
}

void IODrive::completeTest(const bool passedOK, const string& failMarker) {
	testOutput << (passedOK ? "passed" : ("FAILED" + failMarker));
	if (passedOK && estimateCputime) {
		const auto savedFormatFlags = testOutput.flags();
		const auto savedPrecission = testOutput.precision();
		testOutput.setf(ios::fixed, ios_base::floatfield);
		if (usecsPerCall >= 1e4)
			testOutput.setf(ios::scientific, ios_base::floatfield);
		else if (usecsPerCall >= 100.0)
			testOutput.precision(0);
		else if (usecsPerCall >= 10.0)
			testOutput.precision(1);
		else if (usecsPerCall >= 1.0)
			testOutput.precision(2);
		else if (usecsPerCall >= 0.1)
			testOutput.precision(3);
		else
			testOutput.precision(4);
		testOutput << '/' << usecsPerCall << " usec";
		testOutput.precision(savedPrecission);
		testOutput.flags(savedFormatFlags);
	}
	if (titlesOnly) {
		if (!pageOutput)
			testOutput << std::endl;
		else {
			testOutput.flush();
			std::cin.sync();
			if (std::cin.get() != '\n')
				testOutput << std::endl;
		}
	}
	else {
		testOutput << std::endl;
		if (passedOK ? detailsUncond : !titlesOnly) {
			testOutput << testDetails.str() << std::flush;
			if (pageOutput)
				cin.ignore(1);
		}
	}
}

void IODrive::prettyPrintLines(const string& mark, const string& line) {
	testDetails << mark << ' ';
	bool needsIndent = false;
	for (string::const_iterator cit = line.begin(); cit != line.end(); ++cit) {
		if (needsIndent) {
			testDetails <<  endl << std::setw(mark.length() + 1) << "";
			needsIndent = false;
		}
		if (std::isprint(*cit)) {
			testDetails << *cit;
			continue;
		}
		switch (*cit) {
			case '\\':
				testDetails << "\\\\";
				continue;
			case '\a':
				testDetails << "\\a";
				continue;
			case '\f':
				testDetails << "\\f";
				continue;
			case '\r':
				testDetails << "\\r";
				continue;
			case '\t':
				testDetails << "\\t";
				continue;
			case '\v':
				testDetails << "\\v";
				continue;
			case '\n':
				testDetails << "\\n";
				needsIndent = true; continue;
		}
		const auto savedFlags = testDetails.setf(std::ios::oct, std::ios::basefield);
		testDetails << '\\' << static_cast<int>(*cit);
		testDetails.setf(savedFlags);
	}
	testDetails << endl;
}

void IODrive::StreamContainer::addStateChange(ios_base::iostate nstate) {
	stateChanges[suppliedContent.tellp()] |= nstate;
}

