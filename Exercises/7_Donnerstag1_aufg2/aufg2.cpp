/*
 * Modern implementation of the 'Template Method Pattern'
 * using C++-Templates.
 *
 * Advantage/Disadvantage: certain knowledge about concrete
 * spread-out over the clients but zero overhead for unused
 * extension points (= improved performance at the price of
 * stronger compile-time coupling).
*/
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
		: data(d)
	{}
	template<typename T2>
	ContainerProcessor(const vector<double> &d, T2 &arg2)
		: ProcessingDetails(arg2), data(d)
	{}
	template<typename T2, typename T3>
	ContainerProcessor(const vector<double> &d, T2 &arg2, T3& arg3)
		: ProcessingDetails(arg2, arg3), data(d)
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
			for (int i = 0; i < data.size(); ++i)
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

class Averageing : protected ContainerDefaultProcessing { 
	double sum;
	int count;
protected:
	void singleElement(double value) {
		// TO-DO
	}
	void processElement(double value, int n) {
		// TO-DO
	}
	Averageing() : sum(0.0), count(0) {}
public:
	double getAverage() const {
		// TO-DO
	}
};

class Summing : protected  ContainerDefaultProcessing  { 
	double sum;
	ostream &os;
protected:
	Summing(ostream &o)
		// TO-DO
	{}
	void noContent () {
		// TO-DO 
	}
	void singleElement(double value) {
		// TO-DO 
	}
	void processElement(double value, int n) {
		// TO-DO 
	}
	void postProcessing() {
		// TO-DO 
	}
};

typedef ContainerProcessor<Summing> SummingContainerProcessor;
typedef ContainerProcessor<Averageing> AverageingContainerProcessor;

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
