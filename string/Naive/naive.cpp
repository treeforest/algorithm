#include <iostream>
using namespace std;

/*
 * 朴素字符串匹配：在主串 S 中取从第 i(初始值为pos) 个字符起、长度和串 T 相等的字串，与串T比较；
 *  若相等则返回 i，否则 i 值增1，直至串 S 中不存在和串 T 相等的字串为止。
 */
int Match(char* src, char* dst, int pos = 0) {
	if (pos < 0) {
		return -1;
	}

	int n, m, l, i, j;
	n = strlen(src);
	m = strlen(dst);
	l = n - m;

	for (i = pos; i <= l; ++i) {
		j = 0;
		while (j < m) {
			if (src[i + j] != dst[j]) {
				break;
			}
			++j;
		}
		if (j == m){
			return i;
		}
	}

	return -1;
}

int main() {
	char* src = "acaabc";
	char* dst = "aab";

	cout << Match(src, dst, 1);

	return 0;
}