#include "PriorityQueue.hpp"
#include <cassert>
#include <ctime>
#include <iostream>
using namespace std;

typedef int (*compare)(int v, int w);
int cmp(int v, int w) {
	return v - w;
}

int main() 
{
	PQueue<int, int, compare> q(cmp, 5);
	assert(q.empty());
	assert(q.size() == 0);
	
	ElemType<int, int> e;
	srand((unsigned)time(NULL));
	for (int i = 0; i < 30; i++) {
		e.key = rand() % 100 + 1;
		e.val = i;
		q.push(e);
		cout << i << " key=" << e.key << endl;
	}

	q.increase_key(10, 99);

	cout << "\nPriority queue size = " << q.size();
	cout << "\nPop All: ";
	while (!q.empty()) {
		e = q.front();
		cout << e.key << " ";
		q.pop();
	}

	return 0;
}