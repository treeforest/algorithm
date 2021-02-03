#include <iostream>
#include <map>
using namespace std;

void Method1() {
	map<int, int> mp;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		mp[num] = 1;
	}
	int m = 0;
	map<int, int>::iterator iter = mp.begin();
	for (iter; iter != mp.end(); iter++) {
		if ((*iter).first < 0) {
			continue;
		}
		if ((*iter).first == (m + 1)) {
			m++;
		}
		else {
			break;
		}
	}
	cout << (m + 1);
}

int main() {
	int n, a, num = 0;
	cin >> n;
	map<int, int> mp;
	for (int i = 0; i < n; i++) {
		cin >> a;
		mp[a] = 1;
	}
	while (++num) {
		if (mp[num] == 0) {
			break;
		}
	}
	cout << num;
	return 0;
}