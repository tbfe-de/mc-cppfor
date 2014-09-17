#ifdef NO_FRIEND_RELATIONSHIP
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
class Child {
    class Parent &p;
public:
    Child(Parent &p_);
};

class Parent {
    friend Child::Child(Parent &);
    class Child *c;
    void setChild(Child *c_);
public:
    Parent() : c(nullptr) {}
};

Child::Child(Parent &p_)
    : p(p_) {
    p.setChild(this);
}

void Parent::setChild(Child *c_) {
    c = c_;
}

#endif

int main() {
	Parent first;
	Child second(first);
}
