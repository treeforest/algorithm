#include "SkipList.h"
#include <iostream>
using namespace std;

int main() {
	CSkipList L;
	ElementType s[10] = {10, 25, 15, 27, 30, 45, 50, 5, 40, 35};
	for (int i = 0; i < 10; i++) {
		L.Insert(s[i]);
	}

	Position pos = L.Find(5);
	while (pos->elem != ININITY) {
		cout << pos->elem << " ";
		pos = pos->right;
	}

	return 0;
}