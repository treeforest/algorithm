#include "HeapSort.hpp"
#include <time.h> 
#include <iostream>
using namespace std;

#define MAXSISE 12

typedef int (*compare)(int v, int w);
int cmp(int v, int w) {
	return v - w;
}

int main() {
	srand((unsigned)time(NULL));
	ElemType<int, int> e;
	int len = 0;

	ElemType<int, int> A[MAXSISE + 1];
	cout << "初始化<k,v>：";
	for (int i = 1; i <= MAXSISE - 1; i++) {
		e = { rand() % 20 + 1 , i };
		A[i] = e;
		len++;
		cout << "<" << e.key << "," << e.val << "> ";
	}

	Heap<int, int, compare> h(cmp);

	h.BuildMaxHeap(A, len);
	cout << "\n\n大根堆：";
	for (int i = 1; i <= len; i++) {
		cout << "<" << A[i].key << "," << A[i].val << "> ";
	}

	h.InsertEqual(A, len, MAXSISE, e);
	cout << "\n\n插入元素：<" << e.key << ", " << e.val << ">";
	cout << "\n大根堆：";
	for (int i = 1; i <= len; i++) {
		cout << "<" << A[i].key << "," << A[i].val << "> ";
	}

	h.Delete(A, len, e.key);
	cout << "\n\n删除元素：key = " << e.key;
	cout << "\n大根堆：";
	for (int i = 1; i <= len; i++) {
		cout << "<" << A[i].key << "," << A[i].val << "> ";
	}

	h.HeapSort(A, len);
	cout << "\n\n排序后<k,v>：";
	for (int i = 1; i <= len; i++) {
		cout << "<" << A[i].key << "," << A[i].val << "> ";
	}

	return 0;
}