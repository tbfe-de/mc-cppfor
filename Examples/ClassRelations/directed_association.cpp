/*
 ===============================================================================
 Creating a Permanent Association with Restricted Navigability
 ===============================================================================
 This example shows how to create a PERMANENT association between a `Parent` and
 a `Child` class. Because of restricted navigability. (In the code shown below
 the child knows its parent but not vice versa, though the choice of names is
 of course arbitrary.) 
 Because there is only one direction (and assuming it is always possible to
 create the `Parent` object before the `Child` object is created), there is no
 problem with representing the directed association with a reference.
*/

class Parent {
public:
    Parent() {}
};

class Child {
    class Parent &p;
public:
    Child(Parent &p_)
        : p(p_) {
    }
};

int main() {
	Parent first;
	Child second(first);
}
