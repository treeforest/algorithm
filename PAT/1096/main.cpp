#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int n;
	cin >> n;
	int maxn = sqrt(n), len = 0, first = 0;
	for (int i = 2; i <= maxn; i++) {
		int j;
		int tmp = 1;
		for (j = i; j <= maxn; j++) {
			tmp *= j;
			if (n % tmp != 0) {
				break;
			}
		}
		if (j - i > len) {
			len = j - i;
			first = i;
		}
	}
	if (first == 0) {
		cout << 1 << endl << n;
	}
	else {
		cout << len << endl;
		for (int i = 0; i < len; i++) {
			cout << first + i;
			if (i + 1 != len) {
				cout << "*";
			}
		}
	}
	return 0;
}