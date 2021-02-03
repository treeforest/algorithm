#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
	int m, n, s;
	cin >> m >> n >> s;
	map<string, int> mp;
	string input;
	string result = "";
	for (int i = 1; i <= m; i++) {
		cin >> input;
		if (i == s) {
			if (mp[input] == 0) {
				mp[input] = 1;
				s += n;
				result += input + "\n";
			}
			else {
				s++;
			}
		}
	}
	if (result == "") {
		result = "Keep going...\n";
	}
	cout << result;
	return 0;
}