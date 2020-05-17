#include "ForestSet.hpp"
#include <iostream>
using namespace std;

FNode<char>* New(char c) {
	FNode<char>* node = new FNode<char>();
	node->val = c;
	return node;
}

int main() {
	FNode<char> *f, *g, *d;
	f = New('f');
	g = New('g');
	d = New('d');
	FSet<char>::MakeSet(f);
	FSet<char>::MakeSet(g);
	FSet<char>::MakeSet(d);
	FSet<char>::Union(f, g);
	FSet<char>::Union(d, g);
	cout << "f->p: " << f->p->val << endl;
	cout << "g->p: " << f->p->val << endl;
	cout << "d->p: " << d->p->val << endl;

	FNode<char> *c, *h, *e, *b;
	c = New('c');
	h = New('h');
	e = New('e');
	b = New('b');
	FSet<char>::MakeSet(c);
	FSet<char>::MakeSet(h);
	FSet<char>::MakeSet(e);
	FSet<char>::MakeSet(b);
	FSet<char>::Union(c, h);
	FSet<char>::Union(h, e);
	FSet<char>::Union(e, b);
	cout << "c->p: " << c->p->val << endl;
	cout << "h->p: " << h->p->val << endl;
	cout << "e->p: " << e->p->val << endl;
	cout << "b->p: " << b->p->val << endl;

	FSet<char>::Union(e, g);
	cout << "g->p: " << g->p->val << endl;
	cout << "h->p: " << h->p->val << endl;

	return 0;
}