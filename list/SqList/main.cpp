#include "SqList.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

typedef int ElemType;
bool Compare(ElemType e1, ElemType e2) {
	if (e1 == e2) {
		return true;
	}
	return false;
}

int main() {
	SqList<ElemType>* sq = SqList<ElemType>::CreateList();
	assert(sq);

	assert(sq->Empty());
	cout << "len:" << sq->Length() << endl;
	cout << "cap:" << sq->Capacity() << endl;

	for (int i = 1; i <= 33; i++) {
		assert(sq->Insert(sq->Length(), i));
	}

	cout << "插入元素后：" << endl;
	cout << "len:" << sq->Length() << endl;
	cout << "cap:" << sq->Capacity() << endl;

	ElemType e;
	assert(sq->Get(1, e));
	assert(false == sq->Get(34, e));
	assert(sq->Get(31, e));

	cout << "元素 10 的位置索引 = " << sq->Locate(10, Compare) << endl;

	assert(false == sq->Prior(0, e, Compare));
	assert(sq->Prior(6, e, Compare));
	cout << "元素 6 前面的元素为: " << e << endl;

	assert(false == sq->Next(33, e, Compare));
	assert(sq->Next(6, e, Compare));
	cout << "元素 6 后面的元素为：" << e << endl;

	cout << "删除元素：";
	for (int i = 0; i < 5; i++) {
		assert(sq->Delete(0, e));
		cout << e << " ";
	}
	
	assert(sq->Free());
	delete sq;

	return 0;
}