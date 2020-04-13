#include "SeqSearch.hpp"
#include <iostream>
#include <assert.h>
using namespace std;

bool equal(int v, int w) {
	if (v == w) return true;
	return false;
}

int main() {
	SSTable<int, int> sst(5);
	int i;
	
	for (i = 1; i <= sst.Len(); i++) {
		sst[i] = { i + 10, i + 100 };
	}

	assert(0 == sst.search_seq(4, equal));

	i = sst.search_seq(13, equal);
	cout << "key = 13, value = " << sst[i].val << endl;

	for (i = 1; i <= sst.Len(); i++) {
		cout << "key = " << sst[i].key << " ,value = " << sst[i].val << endl;
	}

	return 0;
}