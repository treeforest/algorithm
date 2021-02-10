#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	string a, b; 
	cin >> a >> b;
	map<char, int> mp1, mp2;
	for (int i = 0; i < a.length(); i++) {
		mp1[a[i]]++;
	}
	for (int i = 0; i < b.length(); i++) {
		mp2[b[i]]++;
	}
	int miss = 0;
	map<char, int>::iterator it;
	for (it = mp2.begin(); it != mp2.end(); it++) {
		int sub = it->second - mp1[it->first];
		if (sub > 0) {
			miss += sub;
		}
	}
	if (miss != 0) {
		cout << "No " << miss << endl;
	}
	else {
		cout << "Yes " << a.length() - b.length() << endl;
	}
	return 0;
}