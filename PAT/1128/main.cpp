#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
queue<string> que;

int main() {
	int k = 0, n = 0;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> n;
		vector<int> v(n);
		bool ok = true;
		for (int j = 0; j < n; j++) {
			cin >> v[j];
			if (!ok) {
				continue;
			}
			for (int t = 0; t < j; t++) {
				if (v[j] == v[t] || abs(v[j] - v[t]) == abs(j - t)) {
					ok = false;
					break;
				}
			}
		}
		que.push(ok ? "YES" : "NO");
	}
	
	while (!que.empty()) {
		cout << que.front() << endl;
		que.pop();
	}

	return 0;
}