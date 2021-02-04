#include <iostream>
#include <map>
#include <set>
using namespace std;
int main() {
	int k;
	string input = "";
	cin >> k >> input;
	map<char, int> status; // -1, 0, 1
	string src = "";
	int len = input.length();
	for (int i = 0; i < len; ) {
		char c = input[i];
		if (status[c] == 1) {
			i++;
		}
		else {
			int j;
			for (j = i + 1; j < i + k && j < len; j++) {
				if (c != input[j]) {
					status[c] = 1;
					break;
				}
			}
			if (j == len) {
				status[c] = 1;
			}
			if (j == i + k) {
				status[c] = -1;
			}
			i = j;
		}
	}
	set<char> s;
	for (int i = 0; i < len; ) {
		char c = input[i];
		if (status[c] == 1) {
			src += c;
			i++;
			continue;
		} 
		if (s.find(c) == s.end()) {
			cout << c;
			s.insert(c);
		}
		src += c;
		i += k;
	}
	cout << endl;
	cout << src << endl;
	return 0;
}