class Stack {
public:
	class Node; // local class
private:
	Node *top;
public:
	Stack() : top(0) {}
	~Stack();
	void push(Node *);
	Node *pop();
};

class Stack::Node {
private:
	Node *next;
public:
	virtual ~Node() =0;
friend class Stack;
};
