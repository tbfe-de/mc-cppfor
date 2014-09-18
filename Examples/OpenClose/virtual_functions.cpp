/*
 * Classical of the 'Template Method Pattern' using virtual
 * methods (= late binding aka runtime polymorphism).
 *
 * Advantage: For a remote sub-system it is sufficient to know
 * the base class; no knowledge is necessary wrt. the concrete
 * object created at runtime.
 *
 * Disadvantage: For extension points NOT USED a JSR/RTS (jump
 * sub-routine / return from sub-routine) is unavoidably left
 * in the executable code (some performance reduction, the more
 * as the more 'flexibility' is designed into the implementation).
*/
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class ContainerProcessor {

        const vector<double> &data;
        virtual void noContent() {}
        virtual void singleElement(double) =0;
        virtual void preProcessing() {}
        virtual void processElement(double, int) =0;
        virtual void postProcessing() {}
protected:
        ContainerProcessor(const vector<double> &d)
                : data(d)
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

class AverageingContainerProcessor : private ContainerProcessor { 
        double sum;
        int count;
        virtual void singleElement(double value) {
                sum = value;
                count = 1;
        }
        virtual void processElement(double value, int n) {
                sum += value;
                ++count;
        }
public:
        AverageingContainerProcessor(const vector<double> &d)
                : ContainerProcessor(d), sum(0.0), count(0)
        {}
        double getAverage() const {
                return sum / count;
        }
        using ContainerProcessor::processContent;
};

class SummingContainerProcessor : private ContainerProcessor { 
        double sum;
        ostream &os;
        virtual void noContent () {
                os << "      (no data)" << endl;
        }
        virtual void preProcessing() {
                sum = 0.0;
        }
        virtual void singleElement(double value) {
                os << "      " << value << endl;
        }
        virtual void processElement(double value, int n) {
                os << setw(4) << (n+1) << ": " << value << endl;
                sum += value;
        }
        virtual void postProcessing() {
                os << "-----" << endl;
                os << "Total " << sum << endl;
        }
public:
        SummingContainerProcessor(const vector<double> &d, ostream &o)
                : ContainerProcessor(d), os(o)
        {}
        using ContainerProcessor::processContent;
};

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
	AverageingContainerProcessor p(td);
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

const vector<double> td_empty;
const vector<double> td_one = {3.3};
const vector<double> td_two = {7.5, 12.5};
const vector<double> td_three = {1.5, 6.5, 7.0};

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
