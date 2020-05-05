#include "fibheap.hpp"
#include <time.h> 
#include <iostream>
using namespace std;

#define MAX_SIZE 1000
#define MIN_KEY (~(1 << (sizeof(int) * 8 - 1)) + 1)

typedef FibHeapNode<int> FIBNODE;

typedef int(*Compare)(int, int);
int compare(int k1, int k2) {
	if (k1 == MIN_KEY) {
		return -1;
	}
	else if (k2 == MIN_KEY) {
		return 1;
	}
	return k1 - k2;
}

int main() {
	srand((unsigned)time(NULL));

	FibHeap<int, Compare> fib(compare, MIN_KEY);
	
	int keys[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++) {
		keys[i] = rand() % MAX_SIZE + 1;
		// cout << keys[i] << " ";
		FIBNODE* x = new FIBNODE();
		x->key = keys[i];
		fib.Insert(x);
	}
	//cout << endl;

	FIBNODE* y = NULL, *z = NULL;
	y = fib.ExtractMin();
	while (y != NULL){
		cout << y->key << " ";
		z = y;
		y = fib.ExtractMin();
		if (y && (z->key > y->key)){
			cout << "Error" << endl;
		}
	}

	cout << "It's OK." << endl;
	return 0;
}