//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	string s;
	int n;
	cin >> s;
	cin >> n;
	for (int i = 0; i < n; i++) {	
		string t = "";
		t += s[0];
		int num = 1;
		for (unsigned int j = 1; j < s.length(); j++) {
			if (s[j - 1] == s[j]) {
				num++;
			}
			else {
				stringstream out;
				out << num;
				t += out.str();
				t += s[j];
				num = 1;
			}
		}
		stringstream out;
		out << num;
		t += out.str();
		s = t;
	}
	cout << s << endl;
	return 0;
}