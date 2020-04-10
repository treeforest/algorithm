#include "LinkStack.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

int main() {
	LStack<int> s;

	assert(s.empty());

	cout << "stack push element: ";
	for (int i = 1; i < 10; i++) {
		cout << i << " ";
		s.push(i);
	}
	cout << endl;

	assert(!s.empty());

	cout << "stack size: " << s.size() << endl;

	cout << "stack pop element: ";
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}

	return 0;
}
