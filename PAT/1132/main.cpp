#include <iostream>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	int buf[21];
	for (int i = 0; i < n; i++) {
		cin >> buf[i];
	}
	for (int i = 0; i < n; i++) {
		string s = to_string(buf[i]);
		int len = s.length();
		int a = stoi(s.substr(0, len / 2));
		int b = stoi(s.substr(len / 2, len / 2));
		int c = a * b;
		if (c != 0 && buf[i] % c == 0) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
}