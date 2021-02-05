#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
string base[] = {
	"tret", "jan", "feb", "mar", "apr", "may", "jun",
	"jly", "aug", "sep", "oct", "nov", "dec",
};
string high[] = {
	"", "tam", "hel", "maa", "huh", "tou", "kes", "hei", 
	"elo", "syy", "lok", "mer", "jou",
};
string mars(int n) {
	string s = "";
	if (n / 13 != 0) {
		s = high[n / 13];
		n = n - 13 * (n / 13);
		if (n != 0) {
			s = s + " " + base[n];
		}
	}
	else {
		s = base[n];
	}
	return s;
}
int earth(string s) {
	int num = 0;
	if (s.length() == 7) {
		string tmp = s.substr(0, 3);
		s = s.substr(4, 3);
		for (int i = 1; i < 13; i++) {
			if (high[i] == tmp) {
				num += i * 13;
				break;
			}
		}
	}
	for (int i = 0; i < 13; i++) {
		if (base[i] == s) {
			num += i;
			return num;
		}
	}
	for (int i = 1; i < 13; i++) {
		if (high[i] == s) {
			return i * 13;
		}
	}
	return -1;
}
int main() {
	int n = 0;
	cin >> n;
	cin.get();
	for (int i = 0; i < n; i++) {
		char num[8] = { 0 };
		int tmp = -1;
		cin.getline(num, 8);
		sscanf(num, "%d", &tmp);
		if (tmp != -1) {
			cout << mars(tmp) << endl;
		}
		else {
			cout << earth(num) << endl;
		}
	}
	return 0;
}