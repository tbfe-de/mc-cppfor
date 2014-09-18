/*
 * Modern implementation of the 'Template Method Pattern'
 * using C++-Templates.
 *
 * Advantage/Disadvantage: certain knowledge about concrete
 * spread-out over the clients but zero overhead for unused
 * extension points (= improved performance at the price of
 * stronger compile-time coupling).
*/
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

template<class ProcessingDetails>
class ContainerProcessor : public ProcessingDetails {
	const vector<double> &data;
	using ProcessingDetails::noContent;
	using ProcessingDetails::singleElement;
	using ProcessingDetails::preProcessing;
	using ProcessingDetails::processElement;
	using ProcessingDetails::postProcessing;
public:
	ContainerProcessor(const vector<double> &d)
		: ProcessingDetails(), data(d)
	{}
	template<class T1>
	ContainerProcessor(const vector<double> &d, T1 &arg1)
		: ProcessingDetails(arg1), data(d)
	{}
	template<class T1, class T2>
	ContainerProcessor(const vector<double> &d, T1 &arg1, T2& arg2)
		: ProcessingDetails(arg1, arg2), data(d)
	{}
	template<class T1, class T2, class T3>
	ContainerProcessor(const vector<double> &d, T1 &arg1, T2& arg2, T3& arg3)
		: ProcessingDetails(arg1, arg2, arg3), data(d)
	{}
	void processContent() {
   		// this is the 'closed' part (or the 'Template Method'
    	// using the terminology of the related design pattern)
		if (data.empty())
			noContent();
		else if (data.size() == 1)
			singleElement(data[0]);
		else {
			preProcessing();
			for (vector<double>::size_type i = 0; i < data.size(); ++i)
				processElement(data[i], i);
			postProcessing();
		}
	}
};

class ContainerDefaultProcessing { 
protected:
	inline void noContent() {}
	inline void preProcessing() {}
	inline void postProcessing() {}
};

class AverageingDetails : protected ContainerDefaultProcessing {
	double sum;
	int count;
protected:
	void singleElement(double value) {
		sum = value;
		count = 1;
	}
	void processElement(double value, int n) {
		sum += value;
		++count;
	}
	AverageingDetails() : sum(0.0), count(0) {}
public:
	double getAverage() const {
		return sum / count;
	}
};

class SummingDetails : protected  ContainerDefaultProcessing  {
	double sum;
	ostream &os;
protected:
	SummingDetails(ostream &o)
		: sum(0.0), os(o)
	{}
	void noContent () {
		os << "      (no data)" << endl;
	}
	void singleElement(double value) {
		os << "      " << value << endl;
	}
	void processElement(double value, int n) {
		os << setw(4) << (n+1) << ": " << value << endl;
		sum += value;
	}
	void postProcessing() {
		os << "-----" << endl;
		os << "Total " << sum << endl;
	}
};

typedef ContainerProcessor<SummingDetails> SummingProcessor;
typedef ContainerProcessor<AverageingDetails> AverageingProcessor;

#define PERFORMANCE_TEST
#ifdef PERFORMANCE_TEST
#ifndef REPETITIONS
#define REPETITIONS 5*1000*1000
#endif

int main() {
	vector<double> td;
	double value = 100.0;
	while (td.size() < 1000) {
		td.push_back(value /= 2.0);
	}
	
	cout << "Average = " << flush;
	AverageingProcessor p(td);
	for (int i = 0; i < REPETITIONS; ++i) {
		p.processContent();
	}
	cout << p.getAverage() << endl;
}

#else

/*
 * AUTOMATED TESTS following below (use 'as is' or feel free to extend).
 * Note: interactive testing mode currently NOT supported - use specific
 * main program if required.
 */
#include "IODrive.h"

const vector<double> td_empty({});
const vector<double> td_one({3.3});
const vector<double> td_two({7.5, 12.5});
const vector<double> td_three({1.5, 6.5, 7.0});

int main(int argc, char* argv[]) {

    	return IODrive(cout)
    			.config_estimate_cputime(true)
    		//	.config_details_uncond(true)
    		//	.config_titles_only(true)
    		//	.config_summary_only(true)
    		//	.config_no_summary(true)
    		//	.config_failure_stop(true)
    		//	.config_interactive_mode(true)
    		//	.config_page_output(true)
    		//	.config_line_length(100)
    			.config(argc, argv)

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("calculating average - one data element")
		.run_to_return<double>(3.3,
				[](istream&, ostream&) {
						// ========================================
						AverageingContainerProcessor p(td_one);
						p.processContent();
						return p.getAverage();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("calculating average - two data elements")
		.run_to_return<double>(10.0,
				[](istream&, ostream&) {
						// ========================================
						AverageingContainerProcessor p(td_two);
						p.processContent();
						return p.getAverage();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("calculating average - three data elements")
		.run_to_return<double>(5.0,
				[](istream&, ostream&) {
						// ========================================
						AverageingContainerProcessor p(td_three);
						p.processContent();
						return p.getAverage();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("summing up - no data")
		// -------------------------------------------------------------------
		.expect("      (no data)\n")
		// -------------------------------------------------------------------
		.run_to_return(
				[](istream&, ostream& out) {
						// ========================================
						SummingContainerProcessor p(td_empty, out);
						p.processContent();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("summing up - one data element")
		// -------------------------------------------------------------------
		.expect("      3.3\n")
		// -------------------------------------------------------------------
		.run_to_return(
				[](istream&, ostream& out) {
						// ========================================
						SummingContainerProcessor p(td_one, out);
						p.processContent();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("summing up - two data elements")
		// -------------------------------------------------------------------
		.expect("   1: 7.5"  "\n"
				"   2: 12.5" "\n"
				"-----"      "\n"
				"Total 20"   "\n")
		// -------------------------------------------------------------------
		.run_to_return(
				[](istream&, ostream& out) {
						// ========================================
						SummingContainerProcessor p(td_two, out);
						p.processContent();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.test("summing up - three data elements")
		// -------------------------------------------------------------------
		.expect("   1: 1.5" "\n"
				"   2: 6.5" "\n"
				"   3: 7" 	"\n"
				"-----"     "\n"
				"Total 15"  "\n")
		// -------------------------------------------------------------------
		.run_to_return(
				[](istream&, ostream& out) {
						// ========================================
						SummingContainerProcessor p(td_three, out);
						p.processContent();
						// ========================================
				})

		// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
		.summarize()
		;
}

#endif
