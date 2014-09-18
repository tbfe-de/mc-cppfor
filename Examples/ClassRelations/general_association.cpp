/*
 ===============================================================================
 Creating a Permanent Association with Unrestricted Navigability
 ===============================================================================
 This example shows how to create a PERMANENT association between a `Parent` and
 a `Child` class. Only one of both can refer to the other with a reference, the
 other one needs to use a pointer (or both may use pointers), because in case of
 two references there would be the "chicken and egg" problem, i.e. to initialize
 each reference it would be necessary that the referenced object already exists.

 Aside of the main topic of this this example also tackles the pro's and con's
 of public member functions vs. friend relationships, if two classes must work
 together with each other much more closely as with the rest of the world. The
 two aproaches implemented here depend on the macro `NO_FRIEND_RELATIONSHIPS`.
 (It is detailed in the conditionally compiled sections below.)
*/

#ifdef NO_FRIEND_RELATIONSHIP
// If no friend relationship is used `Parent::setChild` must be made public,
// so that the CHILD can create the connection of itself with the parent.
// OTH this is not much better (or worse) as publicly exposing the pointer
// connecting the parent with the child, because it can now be set by EVERY
// OTHER UNKNOWN CLIENT that (somehow) has gained access to a `Parent` object.

class Parent {
    class Child *c;
public:
    Parent() : c(nullptr) {}
    void setChild(Child *c_) {
        c = c_;
    }
};

class Child {
    class Parent &p;
public:
    Child(Parent &p_)
        : p(p_) {
        p.setChild(this);
    }
};

#else
// The alternative approach nicely demonstrates how friend relationships will
// actually improve but not weaken access protection: Now ONLY the constructor
// of `Child` is allowed to access the `Parent` bypassing the public interface.
// (In fact, using a setter for the `Child *c;` pointer is more to follow the
// conventional style not to access data members directly.
//
// A minor aspect that might be of interest is that to limit friendship to the
// constructor `Child::Child(Parent &)`, the order of declarations needs to put
// class `Child` first. Otherwise `Parent` could only declare unspecific class
// friendship to `Child`, i.e. ALL member functions of `Child` could access any
// member of `Parent`. Therefore a forward declaration of `Parent` must be made
// before the definition of class `Child`.
//
// But the there can only be a declaration of `Child::Child(Parent &)`, as the
// implementation needs the full definition of class `Parent`, not just as an
// incomplete type. This finally leads to the intermingling below, by
//
// * first defining class `Child` (as necessary for the `friend` declaration
//   in `Parent`) but WITHOUT implementing its inline member functions;
// * then defining class `Parent` (which now needs no forward declaration of
//   of `Child` anymore),
// * followed by the implementation of inline member functions (in any order,
//   as all declarations have already been made).

class Parent;
class Child {
    Parent &p;
public:
    Child(Parent &p_);
};

class Parent {
    friend Child::Child(Parent &);
    Child *c;
    void setChild(Child *c_);
public:
    Parent() : c(nullptr) {}
};

Child::Child(Parent &p_)
    : p(p_) {
    p.setChild(this);
    // or: p.c = this;
}

void Parent::setChild(Child *c_) {
    c = c_;
}

#endif

int main() {
	Parent first;
	Child second(first);
}
