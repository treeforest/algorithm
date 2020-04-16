#include "HeapSort.hpp"
#include <time.h> 
#include <iostream>
using namespace std;

typedef int (*compare)(int v, int w);
int cmp(int v, int w) {
	return v - w;
}

int main() {
	srand((unsigned)time(NULL));

	Heap<int, int, compare> hp(cmp, 5);
	ElemType<int, int> e;

	cout << "初始化<k,v>：";
	for (int i = 1; i <= 10; i++) {
		e = { rand() % 20 + 1 , i };
		cout << "<" << e.key << "," << e.val << "> ";
		hp.InsertEqual(e);
	}

	cout << "\n\n大根堆：";
	for (int i = 1; i <= hp.Len(); i++) {
		cout << "<" << hp[i].key << "," << hp[i].val << "> ";
	}
	
	hp.HeapSort();

	cout << "\n\n排序后<k,v>：";
	for (int i = 1; i <= hp.Len(); i++) {
		cout << "<" << hp[i].key << "," << hp[i].val << "> ";
	}

	hp.Delete(e.key);
	cout << "\n\n删除 key = " << e.key;

	cout << "\n\n大根堆：";
	for (int i = 1; i <= hp.Len(); i++) {
		cout << "<" << hp[i].key << "," << hp[i].val << "> ";
	}

	hp.HeapSort();

	cout << "\n\n排序后<k,v>：";
	for (int i = 1; i <= hp.Len(); i++) {
		cout << "<" << hp[i].key << "," << hp[i].val << "> ";
	}

	return 0;
}