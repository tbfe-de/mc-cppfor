#include <iostream>
using namespace std;

#include "stack_data.h"

int main() {
	Stack ivs; // store positive int-values here
	Stack dvs; // store negative double-values here
	Stack::Node *np;

	cout << "========== Input:" << endl;
	double dval;
	while (cin >> dval) {
		int ival = static_cast<int>(dval);
		if (dval == static_cast<double>(ival))
			np = new Int_Node(ival);
		else
			np = new Double_Node(dval);
		if (ival > 0)
			ivs.push(np);
		if (dval < 0.0)
			dvs.push(np);
	}

	cout << "========== Output:" << endl;
	try {
		while ((np = ivs.pop()) != 0) {
			cout << static_cast<Int_Node &>(*np).data << ' ';
			delete np;
		}
		cout << endl;
		while ((np = dvs.pop()) != 0) {
			cout << static_cast<Double_Node &>(*np).data << ' ';
			delete np;
		}
		cout << endl;
	}
	catch (...)  {
		cout << " - oops! " << endl;
	}

	cout << "==========" << endl;
}
