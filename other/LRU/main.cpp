#include "lrucache.h"
#include <iostream>
using namespace std;

int main() {
	LRUCache cache(2);

	cache.Put(1, 1);
	cache.Put(2, 2);
	cout << cache.Get(1) << endl;

	cache.Put(3, 3); // 该操作会使得密钥 2 作废
	cout << cache.Get(2) << endl;

	cache.Put(4, 4); // 该操作会使得密钥 1 作废
	cout << cache.Get(1) << endl;
	
	cout << cache.Get(3) << endl;
	cout << cache.Get(4) << endl;

	return 0;
}