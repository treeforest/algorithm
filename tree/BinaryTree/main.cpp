#include "BinaryTree.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

typedef int ElemType;

typedef int (*Compare)(ElemType v, ElemType w);
int cmp(ElemType v, ElemType w) {
	return v - w;
}

void visit(const ElemType& v) {
	cout << v << " ";
}

int main(){
	BTree<int, Compare> t(cmp);

	int buf[13] = { 9,4,2,1,3,7,6,5,8,11,10,13,12 };
	cout << "Insert: ";
	for (int i = 0; i < 13; i++) {
		cout << buf[i] << " ";
		assert(t.Insert(buf[i]));
	}

	assert(!t.Empty());
	assert(!t.Insert(buf[2]));

	cout << "\n\nPreOrder: ";
	t.PreOrder(visit);
	cout << "\nInOrder: ";
	t.InOrder(visit);
	cout << "\nPostOrder: ";
	t.PostOrder(visit);
	cout << "\nLevelOrder: ";
	t.LevelOrder(visit);

	cout << "\n\nMinimum: " << t.Minimum();
	cout << "\nMaximum: " << t.Maximum();
	cout << "\nSize: " << t.Size();
	cout << "\nDepth: " << t.Depth();

	cout << "\nDelete: 4";
	assert(t.Delete(4));
	assert(!t.Delete(100));

	cout << "\n\nPreOrder: ";
	t.PreOrder(visit);
	cout << "\nInOrder: ";
	t.InOrder(visit);
	cout << "\nPostOrder: ";
	t.PostOrder(visit);
	cout << "\nLevelOrder: ";
	t.LevelOrder(visit);

	return 0;
}