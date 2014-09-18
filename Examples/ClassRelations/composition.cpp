/*
 ===============================================================================
 Creating Composition in Various Forms
 ===============================================================================
 This example shows various forms to create composition, which are commented in
 more detail in the following code_sections that are meant to be conditionally
 compiled, depending on one of the following macros:
 * PART_AS_MEMBER (part is contained as member in composite)
 * PART_AS_PRIVATE_BASE (part is a private base class of composite)
 * PART_VIA_RAW_POINTER (part held and refered to by raw pointer)
 * PART_VIA_UNIQUE_PTR (part held and refered to by unique_ptr)
 *
 * NOTE: All implementations of assignment operators below assume that there
 * will no exceptions been thrown inside their body, or otherwise they will not
 * be able to fulfill anything above the basic guarantee.
*/

// The Motor is the same in all cases and hence defined only once.
//
class Motor {
    // will usually be created
    // as part of a car and
    // also scrapped with it
public:
    void start() {
        // …
    }
};

#if defined(PART_AS_MEMBER)

// This is technique should be usually prefered because coupling between the
// composite (`Car`) and its part (`Motor`) has the lowest degree of coupling.
//
class Car {
    Motor engine;

public:
    Car()
        : engine()
    {}

    void start() {
        // …
        engine.start();
        // …
    }
};

#elif defined (PART_AS_PRIVATE_BASE)

// There is slihgtly more coupling

class Car : private Motor {
public:
    Car()
        : Motor()
    {}

    void start() {
        // …
        Motor::start();
        // …
    }
    // or, if to start a car requires nothing else but to start the
    // engine must be done, the following using statement is sufficient:
//  using Motor::start;
};

#elif defined (PART_VIA_RAW_POINTER)

// If - for any reason - the `Motor` builtin to a `Car` needs to be allocated
// on the heap, a lot of code must be written sytematically simply to care for
// correct memory management.
//
// In the following it is assumed a `Car` - as a C++ object - shall be copyable
// and movable. If these operations are not required, the code can be slightly
// simpliefied (as indicated by the comments).
//
class Car {
    Motor *engine;

public:
    Car()
        : engine(new Motor())
    {}

    ~Car() {
        delete engine;
    }

    Car(const Car &other)
        : engine(new Motor(*other.engine))
    {}
    Car &operator=(const Car &other) {
        if (this != &other) {
	    delete engine;
	    engine = new Motor(*other.engine);
        }
        return *this;
    }
    // or if copy construction/assigmnent
    // should not be supported:
    // Car(const Car&)             =delete;
    // Car &operator=(const Car &) =delete;

    Car(Car &&other)
        : engine(other.engine)
    {
        other.engine = nullptr;
    }
    Car &operator=(Car &&rhs) {
        if (this != &rhs) {
	    delete engine;
	    engine = rhs.engine;
	    rhs.engine = nullptr;
        }
        return *this;
    }
    // or if move construction/assigmnent
    // should not be supported:
    // Car(Car&&)             =delete;
    // Car &operator=(Car &&) =delete;

    void start() {
        // …
        engine->start();
        // …
    }
};

#elif defined (PART_VIA_UNIQUE_PTR)

// Using an `std::unique_ptr` to refer to a `Motor` (assumed to exist with its
// lifetime connected to the lifetime of some `Car`) allows for briefer code,
// especially if only the move-construction and -assignment must be supported,
// but not copy-construction and -assignment.

#include <memory>

class Car {
    std::unique_ptr<Motor> engine;

public:
    Car()
        : engine(new Motor())
    {}

    // If no copy-construction and and -assigment must be supported, these
    // operations should be disabled:
//  Car(const Car &)            = delete;
//  Car& operator=(const Car &) = delete;
    // To implement the above, the object referenced by the `Motor` must be
    // cloned, what is still a bit easier with an `std::unique_ptr` as with
    // a raw pointer, because the former automatically takes care for any
    // object it already references:
    // must be cloned (what
    // an std::unique_ptr member (other as for raw pointers) they can just be
    // enabled:
    Car(const Car &other)
        : engine(new Motor(*other.engine))
    {}
    Car& operator=(const Car &rhs) {
        if (this != &rhs) {
            engine.reset(new Motor(*rhs.engine));
        }
        return *this;
    }

    // As the default move-construction and -assignment do the right thing for
    // an std::unique_ptr member (other as for raw pointers) they can just be
    // enabled:
//  Car(Car &&)            = default;
//  Car& operator=(Car &&) = default;
    // If (and only if) there is additional work to do, an implementation could
    // just move the `Motor` explicitely:
    Car(Car &&other)
        : engine(std::move(other.engine))
    {
        // …
        // do any extra work necessary
        // …
    }
    Car& operator=(Car &&rhs) {
        if (this != &rhs) {
            // …
            engine = std::move(rhs.engine);
            // …
        }
    }

    void start() {
        // …
        engine->start();
        // …
    }
};

#else
#error "No variant selected"
#endif

Car foo() {
	return Car();
}

int main() {
	Car someCar;
	Car secondCar(someCar);
        Car thirdCar(foo());
        someCar = thirdCar;
        secondCar = foo();
}
