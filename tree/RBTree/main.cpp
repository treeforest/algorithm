#include "RBTree.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

typedef int (*Compare)(int v, int w);
int cmp(int v, int w) {
	return v - w;
}

void visit(const int& key, const int& val) {
	cout << key << " ";
}

void print(RBTree<int, int, Compare>* t) {
	cout << "\nDepth: " << t->Depth();

	cout << "\nCount: " << t->Count();

	cout << "\nMinimum: " << t->Minimum();

	cout << "\nMaximum: " << t->Maximum();

	cout << "\nLevelOrder: ";
	t->LevelOrder(visit);

	cout << "\nPreOrder: ";
	t->PreOrder(visit);

	cout << "\nInOrder: ";
	t->InOrder(visit);

	cout << "\nPostOrder: ";
	t->PostOrder(visit);

	cout << endl;
}

int main() 
{
	RBTree<int, int, Compare>* t = new RBTree<int, int, Compare>(cmp);

	assert(t->Empty());

	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		cout << "\nInsertUnique: <" << a[i] << "," << i << ">";
		t->InsertUnique(a[i], i);
		print(t);
	}

	assert(!t->Search(100));

	assert(t->Search(11));
	cout << "Search(11): " << *(t->Search(11)) << endl;

	cout << "Modify key = 11, val = 1000" << endl;
	t->Modify(11, 1000);
	
	cout << "search key = 11: val = " << *(t->Search(11)) << endl;

	assert(!t->Delete(123));

	cout << "\n\ndelete key = 11";
	assert(t->Delete(11));
	print(t);

	cout << "\n\ndelete key = 7";
	assert(t->Delete(7));
	print(t);

	cout << "\n\ndelete key = 3";
	assert(t->Delete(3));
	print(t);

	return 0;
}