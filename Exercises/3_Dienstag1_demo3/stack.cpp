#include "stack.h"

Stack::~Stack() {
	for (Node *np = top; np != 0; np = top) {
		top = np->next;
		delete np;
	}
}

void Stack::push(Node *np) {
	np->next = top;
	top = np;
}

Stack::Node *Stack::pop() {
	Node *np = top;
	if (np != 0)
		top = np->next;
	return np;
}

Stack::Node::~Node() {
	// empty but required!!
}
