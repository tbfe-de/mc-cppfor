/*
 ===============================================================================
 Creating Aggregation
 ===============================================================================
 This example shows how to create aggregation.
*/

#include <algorithm>
#include <cassert>
#include <iostream>

// The lifetime of a `Motor`  motor used as engine in some aggregate (car,
// boat, airplane ...) will gnerally not depend on the aggregate's life-time.
//
class Motor {
    // …
public:
    void start() {
        // …
    }
    operator std::string() const {
    }
    friend
    std::ostream &operator<<(std::ostream &, const Motor *);
};

class Car {
    Motor *e;
public:
    Car(Motor *e_ = nullptr)
        : e(e_)
    {}
    void setEngine(Motor *e_) {
        assert(e && !e_
           || !e && e_);
        e = e_;
    }
    bool swapEngine(Motor *&e_) {
	std::swap(e, e_);
	return (e != nullptr);
    }
    void start() {
        // …
        e->start();
        // …
    }
    friend
    std::ostream &operator<<(std::ostream &, const Car &);
};

class TestBench {
    Motor *testedEngine;
public:
    TestBench()
         : testedEngine(nullptr)
    {}
    operator Motor *&() {
        return testedEngine;
    }
    friend
    std::ostream &operator<<(std::ostream &, const TestBench &);
};

#include <iostream>
using namespace std;

ostream &operator<<(ostream &lhs, const Motor *rhs) {
    return (rhs == nullptr)
            ? (lhs << "no motor")
	    : (lhs << "motor (s/n " << static_cast<const void*>(rhs) << ")");
}

ostream &operator<<(ostream &lhs, const Car &rhs) {
    return lhs << "car (s/n " << &rhs << ") " << rhs.e;
}

ostream &operator<<(ostream &lhs, const TestBench &rhs) {
    return lhs << "::: on test bench " << rhs.testedEngine;
}

int main() {
                                    cout << "--- building some engines"       << '\n';
    static Motor firstMotor;        cout << "    first " << &firstMotor       << '\n';
    static Motor otherMotor;        cout << "    other " << &otherMotor       << '\n';
    static Motor spareMotor;        cout << "    spare " << &spareMotor       << '\n';
    static Motor testMotor;         cout << "    test " << &testMotor         << '\n';
                                    cout << "--- building some cars"          << '\n';
    Car soldCar(&firstMotor);       cout << "    sold " << soldCar            << '\n';
    Car otherCar(&otherMotor);      cout << "    other " << otherCar          << '\n';
    Car forCrashTest;               cout << "    crash test " << forCrashTest << '\n';
                                    cout << "--- building the testbench"      << '\n';
    TestBench bench;                cout << bench                             << '\n';
                                    cout << "--- testing a motor"             << '\n';
    otherCar.swapEngine(bench);     cout << bench << " <= other " << otherCar << '\n';
    otherCar.swapEngine(bench);     cout << bench << " => other " << otherCar << '\n';
                                    cout << "--- replacing a motor"           << '\n';
    soldCar.setEngine(nullptr);     cout << "    sold " << soldCar            << '\n';
    soldCar.setEngine(&spareMotor); cout << "    sold " << soldCar            << '\n';
                                    cout << "==="                             << endl;
}
