#include "BinarySearch.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

int compare(int v, int w) {
	return v - w;
}

int main() {
	SSTable<int, int> sst;
	int len, i;

	cout << "insert: ";
	len = sst.Len();
	for (i = 0; i < len; ++i) {
		cout << i + 10 << " ";
		sst[i] = { i + 10, i + 50 };
	}

	cout << "\nsearch_binary(20): ";
	i = sst.search_binary(20, compare);
	cout << "Ë÷Òý i = " << i << " <" << sst[i].key << "," << sst[i].val << ">" << endl;

	for (i = 0; i < len; ++i) {
		cout << "<" << sst[i].key << "," << sst[i].val << "> ";
	}

	return 0;
}