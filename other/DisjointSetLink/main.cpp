#include "LinkSet.hpp"
#include <iostream>
using namespace std;

typedef bool(*Compare)(char v1, char v2);
bool compare(char v1, char v2) {
	return v1 == v2;
}

int main() {
	typedef LinkSet<char, Compare> LS;
	LS x(compare);
	LS y(compare);

	char S1[] = { 'f', 'g', 'd' };
	char S2[] = { 'c', 'h', 'e', 'b' };

	cout << "x: ";
	for (int i = 0; i < sizeof(S1) / sizeof(char); i++) {
		cout << S1[i] << " ";
		x.MakeSet(S1[i]);
	}
	cout << endl;
	
	cout << "y: ";
	for (int i = 0; i < sizeof(S2) / sizeof(char); i++) {
		cout << S2[i] << " ";
		y.MakeSet(S2[i]);
	}
	cout << endl;

	LS::Union(&x, &y);

	cout << "x: ";
	LSNode<char>* p = x.FindSet();
	while (p) {
		cout << p->val << " ";
		p = p->next;
	}

	return 0;
}