#include <iostream>
#include <set>
using namespace std;
int main() {
	int n;
	cin >> n;
	set<int> s;
	for (int i = 0; i < n; i++) {
		int num, sum = 0;
		cin >> num;
		while (num != 0) {
			sum += num % 10;
			num /= 10;
		}
		s.insert(sum);
	}
	set<int>::iterator iter;
	int size = s.size();
	cout << size << endl;
	for (iter = s.begin(); iter != s.end(); iter++) {
		cout << *iter;
		if (size > 1) {
			cout << " ";
		}
		size--;
	}
	return 0;
}