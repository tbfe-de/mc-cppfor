/*
 * Classical implementation of the 'Template Method Pattern'
 * using virtual methods (= runtime polymorphism aka. late
 * binding).
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
                // TO-DO:
        		// add implementation for processing a container
        		// with just one value when calculating the average
        		// of all values (is called just once from the
        		// 'Template Method')
        }
        virtual void processElement(double value, int n) {
                // TO-DO:
        		// add implementation for processing a single value
        		// when processing a container with more than one
        		// values (is called in a loop from the 'Template
        		// Method')
        }
public:
        AverageingContainerProcessor(const vector<double> &d)
                // TO-DO:
        		// add implementation for the constructor (care
        		// for base class initialization)
        {}
        double getAverage() const {
                // TO-DO:
        		// return calculated average
        }
        using ContainerProcessor::processContent;
};

class SummingContainerProcessor : private ContainerProcessor { 
        double sum;
        ostream &os;
        virtual void noContent () {
                // TO-DO: ...
        }
        virtual void preProcessing() {
                // TO-DO: ...
        }
        virtual void singleElement(double value) {
                // TO-DO: ...
        }
        virtual void processElement(double value, int n) {
                // TO-DO: ...
        }
        virtual void postProcessing() {
                // TO-DO: ...
        }
public:
        SummingContainerProcessor(const vector<double> &d, ostream &o)
                : ContainerProcessor(d), os(o)
        {}
        using ContainerProcessor::processContent;
};

/*
 * AUTOMATED TESTS following below (use 'as is' or feel free to extend).
 * Note: interactive testing mode currently NOT supported - use specific
 * main program if required.
 */

#include <cassert>
#include <sstream>

const vector<double> td_empty;
const vector<double> td_one = {3.3};
const vector<double> td_two = {7.5, 12.5};
const vector<double> td_three = {1.5, 6.5, 7.0};

void test_calculating_average_one_data_element() {
	AverageingContainerProcessor p(td_one);
	p.processContent();
	assert(p.getAverage() == 3.3);
}

void test_calculating_average_two_data_elements() {
	AverageingContainerProcessor p(td_two);
	p.processContent();
	assert(p.getAverage() == 10.0);
}

void test_calculating_average_three_data_elements() {
	AverageingContainerProcessor p(td_three);
	p.processContent();
	assert(p.getAverage() == 5.0);
}

void test_summing_up_no_data() {
	ostringstream expected_output;
	SummingContainerProcessor p(td_empty, expected_output);
	p.processContent();
	assert(expected_output.str() == "      (no data)\n");
}

void test_summing_up_one_data_element() {
	ostringstream expected_output;
	SummingContainerProcessor p(td_one, expected_output);
	p.processContent();
	assert(expected_output.str() == "      3.3\n");
}

void test_summing_up_two_data_elements() {
	ostringstream expected_output;
	SummingContainerProcessor p(td_two, expected_output);
	p.processContent();
	assert(expected_output.str() == "   1: 7.5"  "\n"
                                        "   2: 12.5" "\n"
                                        "-----"      "\n"
                                        "Total 20"   "\n");
}

void test_summing_up_three_data_elements() {
	ostringstream expected_output;
	SummingContainerProcessor p(td_three, expected_output);
	p.processContent();
	assert(expected_output.str() == "   1: 1.5" "\n"
	                                "   2: 6.5" "\n"
	                                "   3: 7"   "\n"
	                                "-----"     "\n"
	                                "Total 15"  "\n");
}

int main() {
	test_calculating_average_one_data_element();
	test_calculating_average_two_data_elements();
	test_calculating_average_three_data_elements();
	test_summing_up_no_data();
	test_summing_up_one_data_element();
	test_summing_up_two_data_elements();
	test_summing_up_three_data_elements();

	cout << "** ALL TESTS PASSED **" << endl;
}

#endif
