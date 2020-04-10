#include "StaticLinkList.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

int main() {
	SLList<int>* lst = new SLList<int>();

	assert(lst->Empty());

	for (int i = MAXSIZE; i >= 1; i--) {
		cout << i << " ";
		assert(lst->Insert(1, i));
	}
	cout << endl;

	assert(lst->Insert(1, 133) == false);

	int e;

	assert(lst->Get(1, e));
	cout << "第 1 个元素是：" << e << endl;

	assert(lst->Get(20, e));
	cout << "第 20 个元素是：" << e << endl;

	assert(lst->Get(40, e) == false);

	assert(lst->Modify(3, 200));
	cout << "修改第 3 个元素的值为：200" << endl;
	assert(lst->Get(3, e));
	cout << "第 3 个元素是：" << e << endl;

	assert(lst->Delete(3, e));
	cout << "删除第 3 个元素：" << e << endl;

	assert(lst->Insert(3, 133));
	cout << "插入第 3 个元素：133" << endl;

	assert(lst->Get(3, e));
	cout << "第 3 个元素是：" << e << endl;

	return 0;
}