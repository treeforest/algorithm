#include "SelectSort.hpp"
#include <time.h> 
#include <iostream>
using namespace std;

#define MAXSIZE 10

int cmp(int v, int w) {
	return v - w;
}

int main() {
	srand((unsigned)time(NULL));
	ElemType<int, int> elem[MAXSIZE];
	int n;

	cout << "³õÊ¼»¯<k,v>£º";
	for (int i = 0; i < MAXSIZE; i++) {
		n = rand() % 20 + 1;
		elem[i] = { n , i };
		cout << "<" << n << "," << i << "> ";
	}

	SelectSort(elem, MAXSIZE, cmp);

	cout << "\n\nÅÅÐòºó<k,v>£º";
	for (int i = 0; i < MAXSIZE; i++) {
		cout << "<" << elem[i].key << "," << elem[i].val << "> ";
	}

	return 0;
}