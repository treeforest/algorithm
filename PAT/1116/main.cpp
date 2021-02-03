#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <set>
using namespace std;
bool is_prime(int n) {
	if (n <= 1) {
		return false;
	}
	int sq = sqrt((double)n);
	for (int i = 2; i <= sq; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}
int main() {
	int n, k;
	string id;
	cin >> n;
	map<string, string> mp;
	set<string> s;
	for (int i = 0; i < n; i++) {
		cin >> id;
		mp[id] = i + 1;
		if (i == 0) {
			mp[id] = "Mystery Award";
		}
		else if (is_prime(i + 1)) {
			mp[id] = "Minion";
		}
		else {
			mp[id] = "Chocolate";
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> id;
		if (mp[id] == "") {
			cout << id << ": Are you kidding?\n";
		}
		else {
			if (s.find(id) == s.end()) {
				cout << id << ": " << mp[id] << endl;
				s.insert(id);
			}
			else {
				cout << id << ": " << "Checked\n";
			}
		}
	}
	return 0;
}