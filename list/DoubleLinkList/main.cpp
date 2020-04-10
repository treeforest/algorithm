#include "DoubleLinkList.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

int main() {
	DuLList<int>* lst = new DuLList<int>();

	assert(lst->Empty());

	for (int i = 130; i >= 101; i--) {
		assert(lst->Insert(1, i));
	}

	assert(!lst->Empty());

	int e;

	assert(lst->Get(1, e));
	cout << "第 1 个元素是：" << e << endl;

	assert(lst->Get(20, e));
	cout << "第 20 个元素是：" << e << endl;

	assert(!lst->Get(40, e));

	assert(lst->Modify(3, 200));
	cout << "修改第 3 个元素的值为：200" << endl;
	assert(lst->Get(3, e));
	cout << "第 3 个元素是：" << e << endl;

	assert(lst->Delete(3, e));
	cout << "删除第 3 个元素：" << e << endl;
	assert(lst->Get(3, e));
	cout << "第 3 个元素是：" << e << endl;

	return 0;
}