/*! @file IODrive.h
 *
 * Classes, Templates and Inline Member Functions of the IODrive Library
 *
 * See class and member function doxycoms for details.
 *
 */
#ifndef IODRIVE_h
#define IODRIVE_h

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                               optionally avoid global name space
#ifdef DE_TBFE_IODRIVE_IN_ITS_OWN_NAMESPACE
namespace de { namespace tbfe { namespace iodrive {
#endif

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                    C++11 library headers (sorted alphabetically)
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>

/**
 * Main Class of the IODrive Library.
 *
 * The only class defined for this library.
 * Everything else what is required is defined inside.
 * More classes are defined as nested classes here.
 * There is no other technical reason as to avoid name space pollution.
 */
class IODrive {

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                        types in public interface
public:

	/**
	 * Allow some Syntactic Sugar for Writing Assertions
	 */
	class AssertStream;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                       types only used internally
private:

	/**
	 * Packaged Streams for Supplying Input, Catching Output and Comparison to Expectations.
	 */
	class StreamContainer;

	/**
	 * Return Proxy to Allow Detecting some Usage Errors at Compile Time.
	 */
	class TestSpec;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                            special access rights
friend class TestSpec;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                members variables used internally
private:

	/**
	 * Final destination of all generated output.
	 */
	std::ostream& testOutput;


	/**
	 * Instance of packaged streams (when tests are run), otherwise 'nullptr'.
	 */
	StreamContainer* streamContainer;

	/**
	 * Runtime Configuration Option: run code to estimate CPU usage.
	 *
	 * This option is evaluated after successful tests only.
	 * If activated, a loop is entered repeating the test function call.
	 * The loop ends when accumulated CPU time exceeds one (1.0) second.
	 */
	bool estimateCputime;

	/**
	 * Runtime Configuration Option: always show full details.
	 *
	 * Details are usually shown (only) for tests that have failed.
	 * This option adds also details of passed tests to the output.
	 */
	bool detailsUncond;

	/**
	 * Runtime Configuration Option: never show details.
	 *
	 * Details are usually shown for (only) tests that have failed.
	 * This option discards details of failed tests from the output.
	 */
	bool titlesOnly;

	/**
	 * Runtime Configuration Option: do not show titles as tests are executed.
	 *
	 * While a test is run its titles are shown but no end-of-line (std::endl) is added.
	 * When a test ends a passed/FAILED indicator is added together with an end-of-line.
	 * (Besides a 'looking nice' This also gives some idea how testing progresses.)
	 * This option suppresses titles AND ALSO passed/FAILED indicators.
	 * I.e. in a typical setup test results are represented in the summary line only.
	 *
	 * @note
	 * So that a summary line is shown, the 'summarize' member function must be called.
	 * @code
	 * 	   IODrive(std::cout)
	 * 			.test("whatever)
	 * 				...
	 * 				...
	 * 			.test("whatever else")
	 * 				...
	 * 				...
	 * 			.summarize()
	 * 			;
	 * @endcode
	 * Should this call be omitted, there will be no summary and no passed/FAILED indication.
	 */
	bool summaryOnly;

	/**
	 * Runtime Configuration Option: do not show the summary line.
	 *
	 * In a typical setup after all tests are run a line is added summarizing the test results.
	 * This option suppresses the summary, even if there is a call to the 'summarize'.
	 * @see summaryOnly for details
	 *
	 * @note
	 * As typical usage is to make return the 'summarize' member function result from 'main'.
	 * @code
	 * int main() {
	 * 		return
	 * 			IODrive(std::cout)
	 * 					...
	 * 					...
	 * 				.summarize()
	 * 				;
	 * 	}
	 * @endcode
	 * Therefore it may  make sense (sometimes), to activate both, 'summaryOnly' and 'noSummary'.
	 */
	bool noSummary;

	/**
	 * Runtime Configuration Option: replace automated tests with interactive testing.
	 *
	 * While the main usage scenario test automation, interactive use might sometime be desirable.
	 * This option inhibits all tests suppling prepared input/catching output to/from a candidate.
	 * Instead an interactive call of the candidate takes place.
	 *
	 * @note
	 * This works ONLY if (besides automated tests) there is a call to test_cin_cout!
	 * @code
	 * 		IODrive(std::cout)
	 * 			// a first prepared test
	 * 			.test("whatever")
	 * 				...
	 * 			.run_to_return(myTestCandidate)
	 * 			// a second prepared test
	 * 			.test("whatever")
	 * 				...
	 * 			.run_to_return(myTestCandidate)
	 * 			// allow interactive testing
	 * 			.test_cin_cout("please type-in something", myTestCandidate)
	 *
	 * 			// and finally as usual
	 * 			.summarize()
	 * 			;
	 * @endcode
	 * It makes no difference where 'test_cin_cout' member function is called.
	 * The preferred place is usually BEFORE or AFTER all prepared tests.
	 * But the only reason for this is to make the (presumable single) call more stand-out.
	 *
	 * @note
	 * Even more than one call is possible, but NOT RECOMMENDED:
	 * It may lead to difficulties how to correctly supply 'end of input'.
	 */
	bool interactiveMode;


	/**
	 * Runtime Configuration Option: wait for user input after each test.
	 *
	 * Usually in a series of prepared tests one test is run one after the other.
	 * With this option user input is expected after each single test.
	 * In a large series of tests this gives some 'step through' control.
	 *
	 * If only output should not vanish from the screen, a pipelined pager would be as good.
	 * But then, until the screen has filled, new output will continuously be added.
	 * In demonstration runs, one stop after each test executed is often more appropriate.
	 */
	bool pageOutput;

	/**
	 * Runtime Configuration Option: stop after a failed test.
	 *
	 * Usually the series of prepared tests is always run to its end, no matter if some fail.
	 * With this option a series of tests is aborted after the first failed test.
	 */
	bool failedStop;


	/**
	 * Runtime Configuration Option: length of test title lines.
	 *
	 * Typically the presentation of results looks "nicer" with aligned passed/FAILED indicators.
	 * Especially if there are long test titles, it may make sense to increase the default.
	 * (If titles are all very short and screen estate is a scarce you may want to decrease it.)
	 * When set to zero, there will be no alignment, i.e. title lines are 'as short as possible'.
	 *
	 * @note
	 * The length specified here is the minimum for passed tests with NO CPU time estimate.
	 * If a test title is very long, this length may still be exceeded (even for a passed test).
	 * Also additional markers after a FAILED indicator are not taken into account.
	 * Finally, the length lines showing test details will NOT be controlled by this setting.
	 */
	std::string::size_type lineLength;

	/**
	 * Title of test that will be run next.
	 *
	 * The content is valid after a call to any of the following member function:
	 *  - 'test'
	 * It becomes invalid after a call to any of the following member functions:
	 *  - 'run_to_return'
	 *  - 'run_to_throw'
	 * Furthermore it is valid DURING a call to the following member functions:
	 *  - 'test_cin_cout'
	 *  - 'test_assertions'
	 */
	std::string testToRun;

	/**
	 * Number of tests run (so far).
	 */
	int testsRun;

	/**
	 * Number of tests passed (so far).
	 *
	 * @note
	 * If stopping after the first failed test is requested, this can not exceed one!
	 */
	int testsPassed;

	/**
	 * Number of tests skipped (so far).
	 *
	 * @note
	 * After all tests are run, this is the count tests skipped because explicitly omitted.
	 *
	 * @todo
	 * Clarify behavior for tests skipped if 'stop after first failure' is requested.
	 */
	int testsSkipped;

	/**
	 * Indicate current test has delivered the expected output.
	 *
	 * This is a shared variable passed between a limited number of member functions.
	 *
	 * @todo
	 * Consider to pass this in a small 'struct' only between member functions actually using it.
	 */
	bool outputOK;

	/**
	 * Indicate current test has delivered the expected return value.
	 *
	 * This is a shared variable passed between a limited number of member functions.
	 *
	 * @todo
	 * Consider to pass this in a small 'struct' only between member functions actually using it.
	 */
	bool resultOK;

	/**
	 * Number of calls necessary to get an accumulated CPU time of more than one (1.0) second.
	 *
	 * This is a shared variable passed between a limited number of member functions.
	 *
	 * @todo
	 * Consider to make this more local and/or pass it only member functions actually using it.
	 */
	int numberOfCalls;

	/**
	 * Microseconds required by a single call.
	 *
	 * This is a shared variable passed between a limited number of member functions.
	 *
	 * @todo
	 * Consider to make this more local and/or pass it only member functions actually using it.
	 */
	double usecsPerCall;

	/**
	 * Type of testActivation (for better readability only).
	 */
	typedef std::set<std::string> TestActivation;

	/**
	 * Titles of tests to b activated.
	 *
	 * @note
	 * If empty, ALL tests are activated!
	 *
	 * Tests are activated if their title matches any of the strings stored here.
	 * Matching must start at the beginning but not necessarily needs to extend to the end.
	 * Comparison is not case sensitive and underscore an ('_') also represents a space.
	 */
	TestActivation testActivation;

	/**
	 * Indicate whether the current test has been terminated with an exception.
	 *
	 * @note
	 * There two special values with a special meaning:
	 *  - nullptr when the test ran to its end WITHOUT any exception;
	 *  - void* when a test ended with an exception NOT derived from std::exception.
	 *  Therefore (currently) checks for expected non-standard exceptions are not possible.
	 *  This may be seen as s slight design limitation (which could be removed).
	 *  On the other hand it is often recommended to derive exception classes from the standard hierachy.
	 *
	 * @todo
	 * Consider to pass this in a small 'struct' only between member functions actually using it.
	 */
	const std::type_info* terminatingException;

	/**
	 * Hold the what-message if the current test has been terminated with an standard exception.
	 *
	 * @todo
	 * Consider to pass this in a small 'struct' only between member functions actually using it.
	 */
	std::string exceptionWhatString;

	/**
	 * Result collecting stream for details of tests run
	 *
	 * @todo
	 * Consider to pass this in a small 'struct' only between member functions actually using it.
	 */
	std::ostringstream testDetails;

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                                                                members functions used internally
private:

	/**
	 * Compare test names applying some convenience rules.
	 *
	 * @param[in]	testToActivate -- name of test to activate
	 * @param[in]	testTitle -- title of test
	 * @returns		true if testToActivate matches titleOfTest according to rules outline below
	 *
	 * Comparison of strings holding testToActivate and testTitle is done as follows
	 *  - every letter in testTitle is converted to its lower case equivalent
	 *  - any sequence of space and non-letters in testTitle compares equal to a single underscore
	 */
	static
	bool nameCompare(const std::string& testToActivate, const std::string& testTitle);

	/**
	 * Determine if line is complete
	 *
	 * @param[in]	lineToCheck -- line which is to be checked
	 * @returns		true if line ends with a newline character
	 */
	static
	inline
	bool isCompleteLine(const std::string& lineToCheck);

	/**
	 * Check if test is to activate.
	 *
	 * @param[in]	testTitle -- title of test
	 * @returns		true if test is to activate
	 *
	 * So that a test is activated
	 *  - either the set testActivation must be empty
	 *  - or any of its title must compare 'loosely' compare equal to some member of this set.
	 *
	 * @note
	 * Comparison rules are outlined in more detail in the helper function nameCompare.
	 */
	bool lookupActivation(const std::string& testTitle);

	/**
	 * Check if testDetails indicate a failed assertion.
	 *
	 * @return	true if NO assertion failed
	 *
	 * Failed assertions are indicated by a line starting with a minus ('-') sign.
	 *
	 * @note
	 * Consider to replace the current implementation with a regular expression match.
	 */
	bool validateAssertions() const;

	/**
	 * Show exact location where expected and thrown exception differ
	 *
	 * @param[in]	lineMark -- marker to appear in leftmost position of line
	 * @param[in]	expectedWhat -- expected content of what-string
	 * @param[in]	thrownWhat -- content of what string as actually thrown
	 *
	 * @todo
	 * Care for 'pretty printing' of exception class name with name-mangling compilers (like g++).
	 */
	template<class Expected>
	void showExceptionDiff(const std::string& lineMark,
						   const std::string& expectedWhat,
						   const std::string& thrownWhat);

	/**
	 * Print detailed test results.
	 *
	 * @param[in]	lineMark -- marker to appear in leftmost position of first line
	 * @param[in]	lineSequence -- content of one or more lines to be printed
	 *
	 * The lineSequence printed is beautified in the following ways:
	 *  - lineMark followed by a single space is printed in front of the first line;
	 *  - any non-printing character is replaced by its (C-style) escape sequence;
	 *  - after an end-of-line indication (\n) a new (subsequent) line starts;
	 *  - subsequent lines are indented like the first line but no lineMark is shown.
	 */
	void prettyPrintLines(const std::string& lineMark,
						  const std::string& lineSequence);

	/**
	 * Show help page.
	 *
	 * The help page contains a brief summary of command line options.
	 */
	void helpPage();

	/**
	 * Prepare execution of a single test.
	 *
	 * Prints the test name and some dots to alignment (if test titles are not suppressed).
	 * Clears the member testDetails (filled later when the actual test is run).
	 * Completes streamContainer initialisation and cares for initial state changes.
	 * (For tests not activated no stream container exists, hence there will be no initialization.)
	 */
	void prepareTest();

	/**
	 * Completes execution of a single test.
	 *
	 * @param[in]	passedOK -- indicates successful test completion
	 * @param[in]	failMarker -- reason for failure
	 *
	 * After successful completion of a test shows 'passed'.
	 * Otherwise shows 'FAILED' together with supplied failMarkers.
	 * Also cares for showing details and paging through output.
	 */
	void completeTest(const bool passedOK,
					  const std::string& failMarker = std::string());

	/**
	 * Prepare the test set-up so that the supply stream will assume the eof state at this point.
	 *
	 * @return	call object disguised as TestSpec (mainly to detect usage errors at compile time).
	 */
	TestSpec supplyEof();

	/**
	 * Prepare test set-up so that the supply stream will assume the fail state at this point.
	 *
	 * @return	call object disguised as TestSpec (mainly to detect usage errors at compile time).
	 */
	TestSpec supplyFail();

	/**
	 * Prepare test set-up so that a given char sequence is in the supply stream at this point.
	 *
	 * @param[in]	charsSupplied -- char sequence to be supplied as input
	 * @param[in]	endLine --indicate that a full line is to be supplied
	 * @return		call object disguised as TestSpec (mainly to detect usage errors at compile time)
	 *
	 * If endLine is set a new-line character is appended to the supplied output.
	 */
	TestSpec supplyInput(const std::string& charsSupplied, const bool endLine);

	/**
	 * Prepare test set-up so that output is checked against a given char sequence at this point.
	 *
	 * @param[in]	charsExpected -- char sequence expected as output
	 * @param[in]	endLine --indicate that a full line is expected
	 * @return		call object disguised as TestSpec (mainly to detect usage errors at compile time).
	 *
	 * If endLine is set a new-line character is expected at the end of output.
	 */
	TestSpec expectOutput(const std::string& charsExpected, const bool endLine);

	/**
	 * Repeat calls to the candidate under test until a certain amount of CPU-time is accumulated.
	 *
	 * @param[in]	testCandidate -- function to be called (repeatedly)
	 *
	 * @todo
	 * Consider to make fixed accumulation limit of 1.0 sec configurable.
	 */
	void repeatForTimings(std::function<void(std::istream&, std::ostream&)> testCandidate);

	/**
	 * Call a test candidate and check its return value against an expected result.
	 *
	 * @param[in]	expectedResult -- return value expected from the function call
	 * @param[in]	testCandidate -- function to call in this test
	 * @return		true if actual result meets expectation
	 *
	 * The expected result is always handed over via pointer.
	 * There is a separate specialisation for functions returning 'void'.
	 * The type of the first argument would then be 'void *'.
	 * (For a function actually returning 'void *', it would be 'void **' !!)
	 */
	template<typename ResultType>
	bool checkedCall(const ResultType* const expectedResult,
					 std::function<ResultType(std::istream&, std::ostream&)>);

	/**
	 * Wrap calls of a test candidate so that exceptions are caught.
	 *
	 * @param[in]	testCandidate -- function to call in this test
	 */
	template<typename ResultType>
	void runHelper(const ResultType* expectedResult,
			       std::function<ResultType(std::istream&, std::ostream&)> testCandidate);

	template<typename ResultType>
	IODrive& runToReturn(const ResultType*,
			             std::function<ResultType(std::istream&, std::ostream&)>);

	template<typename ExpectedException>
	IODrive& runToException(const std::string&,
			                std::function<void(std::istream&, std::ostream&)>);

	/**
	 * Run test candidate set up and check if all assertions are met.
	 *
	 * @param[in]	testCandidate -- test candidate to be executed
	 * @return		call-object (for easy call-chaining)
	 *
	 * @note
	 * See class AssertStream for more details on assert stream usage.
	 */
	IODrive& testAssertions(std::function<void(AssertStream&)> testCandidate);

public:

	IODrive(std::ostream&);

	IODrive& config_estimate_cputime(const bool v) {
		estimateCputime = v;
		return *this;
	}
	IODrive& config_details_uncond(const bool v) {
		detailsUncond = v;
		return *this;
	}
	IODrive& config_titles_only(const bool v) {
		titlesOnly = v;
		return *this;
	}
	IODrive& config_summary_only(const bool v) {
		summaryOnly = v;
		return *this;
	}
	IODrive& config_quiet_summary(const bool v) {
		noSummary = v;
		return *this;
	}
	IODrive& config_interactive_mode(const bool v) {
		interactiveMode = v;
		return *this;
	}
	IODrive& config_page_output(const bool v) {
		pageOutput = v;
		return *this;
	}
	IODrive& config_failure_stop(const bool v) {
		failedStop = v;
		return *this;
	}
	IODrive& config_line_length(const int v) {
		lineLength = v;
		return *this;
	}
	IODrive& config(int, char**);

	TestSpec test(const std::string& title);

	IODrive& test_assertions(const std::string&, std::function<void(AssertStream&)>);

	IODrive& test_cincout(const std::string&, std::function<void(std::istream&, std::ostream&)>);

	int summarize();

};

class IODrive::TestSpec {

	friend class IODrive;

	IODrive& iodrive;

	explicit TestSpec(IODrive& hull)
		: iodrive(hull)
	{}

public:

	IODrive& test_assertions(std::function<void(AssertStream&)> testFunction) {
		return iodrive.testAssertions(testFunction);
	}

	IODrive::TestSpec supply(const std::string& in) {
		return iodrive.supplyInput(in, false);
	}

	IODrive::TestSpec supply_line(const std::string& in) {
		return iodrive.supplyInput(in, true);
	}

	IODrive::TestSpec supply_fail() {
		return iodrive.supplyFail();
	}

	IODrive::TestSpec supply_eof() {
		return iodrive.supplyEof();
	}

	IODrive::TestSpec expect(const std::string& out) {
		return iodrive.expectOutput(out, false);
	}

	IODrive::TestSpec expect_line(const std::string& out) {
		return iodrive.expectOutput(out, true);
	}

	IODrive& run_to_return(std::function<void(std::istream&, std::ostream&)> testFunction) {
		return iodrive.runToReturn<void>(0, testFunction);
	}

	template<typename ResultType>
	IODrive& run_to_return(const ResultType expectedResult,
			       std::function<ResultType(std::istream&, std::ostream&)> testFunction) {
		return iodrive.runToReturn(&expectedResult, testFunction);
	}


	template<typename ExpectedException>
	IODrive& run_to_throw(const std::string& expectedWhat,
			      std::function<void(std::istream&, std::ostream&)> testFunction) {
		return iodrive.runToException<ExpectedException>(expectedWhat, testFunction);
	}
};

class IODrive::StreamContainer {

	friend class IODrive;

	StreamContainer(IODrive& io)
		: iodrive(io)
		, suppliedContent("")
		, supplyBuffer(*this)
		, supplyStream(&supplyBuffer)
	    , receiveStream(receivedContent.rdbuf())
	    , firstDifference(-1)
		, runTimings(false)
	{}

	class SupplyBuffer : private std::vector<char>, public std::streambuf {

		// friend StreamContainer::StreamContainer(IODrive&);
		friend class StreamContainer;

		size_type endpos;

		StreamContainer& streamContainer;

		SupplyBuffer(StreamContainer& c)
			: streamContainer(c)
		{
			reserve(4000);
			resize(1);
			reset();
		}

		void reset() {
			endpos = 0;
			char* const buffer_base = &operator[](0);
			setg(buffer_base, buffer_base, buffer_base);
		}

		virtual int underflow();

		virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way, std::ios_base::openmode which);

		virtual std::streampos seekpos(std::streampos sp, std::ios_base::openmode which);

	};

	IODrive& iodrive;

	std::stringstream suppliedContent;
	SupplyBuffer supplyBuffer;
	std::istream supplyStream;

	std::stringstream receivedContent;
	std::ostream receiveStream;

	std::stringstream expectedContent;

	int firstDifference;
	bool runTimings;

	typedef std::map<std::streampos, std::streampos> ExpectationChecks;
	ExpectationChecks expectationChecks;
	ExpectationChecks::const_iterator nextExpectationCheck;

	typedef std::map<std::streampos, std::ios_base::iostate> StateChanges;
	StateChanges stateChanges;
	StateChanges::iterator nextStateChange;

	std::string processedInputLine;

	void showProcessedInput();

	void addSupplied(const std::string&, const bool);

	void addExpected(const std::string&, const bool);

	void addStateChange(std::ios_base::iostate state);

	void checkActuallyReceived(std::string::size_type);

	bool checkFinallyReceived();

	void changeStateSupplied(std::ios_base::iostate);

	int supplyNextChar();

	void prepareExpectationChecks();

	void doExpectationChecks();

	void prepareStateChanges();

	void doStateChanges();

	void compareHelper(std::istream&, std::string&, bool& skip);

	void readyToRestart();
};

class IODrive::AssertStream {
	std::ostream& out;
	const std::string pass;
	const std::string fail;
	std::stringstream collect;
	void flush() {
		out << collect.str() << std::endl;
		collect.str(std::string());
	}
	struct Holder {
		friend class AssertStream;
		AssertStream& assertStream;
		Holder(AssertStream& fc)
			: assertStream(fc)
		{}
		~Holder() {
			assertStream.flush();
		}
	public:
		template<typename T>
		Holder& operator<<(const T& rhs) {
			assertStream.collect << rhs;
			return *this;
		}
	};
	friend class Holder;
public:
	AssertStream(std::ostream& o, const std::string& p = "+ ", const std::string& f = "- ")
		: out(o), pass(p), fail(f)
	{}
	Holder operator[](const bool m) {
		collect << (m ? pass : fail);
		return Holder(*this);
	}
};

inline
bool IODrive::isCompleteLine(const std::string& lineToCheck) {
	return !lineToCheck.empty() && (lineToCheck.back() == '\n');
}

template<class Expected>
void IODrive::showExceptionDiff(const std::string& mark, const std::string& what, const std::string& thrownWhat) {
	std::string visualMarker;
	for (std::string::size_type pos = 0; pos < what.size(); ++pos) {
		if (pos < thrownWhat.length()) {
			if (what.at(pos) != thrownWhat.at(pos))
				break;
			visualMarker.append("-");
		}
	}
	visualMarker.append("^");
	testDetails << mark << ' ' << what << " [" << typeid(Expected).name() << "]" << std::endl
		    << "<? " << visualMarker << std::endl;
}

template<typename T>
bool IODrive::checkedCall(const T* const expectedRetval,
			  std::function<T(std::istream&, std::ostream&)> candidate) {
	streamContainer->supplyStream.seekg(0);
	const T actualRetval = candidate(streamContainer->supplyStream, streamContainer->receiveStream);
	numberOfCalls = 1;
	streamContainer->checkFinallyReceived();
	testDetails << "<: " << actualRetval << std::endl;
	if (actualRetval == *expectedRetval) {
		if (streamContainer->checkFinallyReceived()
		 && estimateCputime)
			static_cast<void>(repeatForTimings(candidate));
		return true;
	}
	testDetails << "<~ " << *expectedRetval << std::endl;
	return false;
}

template<>
bool IODrive::checkedCall<void>(const void* const, std::function<void(std::istream&, std::ostream&)>);

template<typename T>
void IODrive::runHelper(const T* result, std::function<T(std::istream&, std::ostream&)> testFunction) {
	prepareTest();
	try {
		resultOK = checkedCall(result, testFunction);
		outputOK = (streamContainer->firstDifference < 0);
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
	delete streamContainer;
	streamContainer = 0;
}

template<typename ExpectedException>
IODrive& IODrive::runToException(const std::string& what, std::function<void(std::istream&, std::ostream&)> testFunction) {
	if (interactiveMode)
		return *this;
	if (streamContainer == 0)
		return *this;
	runHelper<void>(0, testFunction);
	if (!terminatingException) {
		testDetails << "<| " << what << " [" << typeid(ExpectedException).name() << "]" << std::endl;
		if (!summaryOnly)
			completeTest(false, "/n");
	}
	else if (*terminatingException != typeid(ExpectedException)) {
		showExceptionDiff<ExpectedException>("<|", what, exceptionWhatString);
		if (!summaryOnly)
			completeTest(false, "/x");
	}
	else if (exceptionWhatString != what) {
		showExceptionDiff<ExpectedException>("<|", what, exceptionWhatString);
		if (!summaryOnly)
			completeTest(false, "/z");
	}
	else {
		if (!summaryOnly)
			completeTest(true);
		++testsPassed;
	}
	return *this;
}

template<typename ResultType>
IODrive& IODrive::runToReturn(const ResultType* result, std::function<ResultType(std::istream&, std::ostream&)> testFunction) {
	if (interactiveMode)
		return *this;
	if (streamContainer == 0)
		return *this;
	runHelper<ResultType>(result, testFunction);
	if (terminatingException) {
		if (!summaryOnly)
			completeTest(false, "/x");
	}
	else if (!outputOK || !resultOK) {
		if (!summaryOnly) {
			std::string markers;
			if (!outputOK)
				markers.append("/o");
			if (!resultOK)
				markers.append("/r");
			completeTest(false, markers);
		}
	}
	else {
		if (!summaryOnly)
			completeTest(true);
		++testsPassed;
	}
	return *this;
}

#ifdef DE_TBFE_IODRIVE_IN_ITS_OWN_NAMESPACE
}}} // EONS de::tbfe::iodrive
#endif


#endif
