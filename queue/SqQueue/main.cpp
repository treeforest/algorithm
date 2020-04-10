#include "SqQueue.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

int main()
{
	SqQueue<int> Q;

	assert(Q.empty());

	cout << "queue push: ";
	for (int i = 0; i < 40; i++) {
		cout << i << " ";
		Q.push(i);
	}
	cout << endl;

	cout << "queue pop: " << Q.front() << endl;;
	Q.pop();

	cout << "queue push 100" << endl;
	Q.push(100);

	cout << "queue size: " << Q.size() << endl;
	cout << "queue front: " << Q.front() << endl;
	cout << "queue back: " << Q.back() << endl;
	cout << "queue pop: ";
	for (int i = 0; i < 40; i++) {
		cout << Q.front() << " ";
		Q.pop();
	}

	return 0;
}