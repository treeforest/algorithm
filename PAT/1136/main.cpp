#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool huiwen(string s, string t) {
	int len = s.length();
	int i = 0, j = len - 1;
	while (i <= j) {
		if (s[i] != s[j]) {
			return false;
		}
		i++;
		j--;
	}
	return true;
}

string reverse(string s) {
	int len = s.length();
	string t = "";
	for (int i = len - 1; i >= 0; i--) {
		t += s[i];
	}
	return t;
}

string add(string s, string t) {
	stack<char> st;
	int len = s.length();
	int num = 0;
	for (int i = len - 1; i >= 0; i--) {
		int a = s[i] - '0';
		int b = t[i] - '0';
		int sum = a + b + num;
		if (sum >= 10) {
			num = sum / 10;
			st.push(sum - num * 10 + '0');
		}
		else {
			st.push(sum + '0');
			num = 0;
		}
	}
	if (num != 0) {
		st.push(num + '0');
	}
	string s2 = "";
	while (!st.empty()) {
		s2 += st.top();
		st.pop();
	}
	return s2;
}

int main() {
	string s = "";
	cin >> s;
	for (int i = 0; i < 10; i++) {
		string t = reverse(s);
		string out = add(s, t);
		cout << s << " + " << t << " = " << out << endl;
		if (huiwen(out, reverse(out))) {
			cout << out << " is a palindromic number.";
			return 0;
		}
		s = out;
	}
	cout << "Not found in 10 iterations.";
	return 0;
}