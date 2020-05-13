#include <iostream>
using namespace std;

// primeRK 是用于 Rabin-Karp 算法中的素数
const size_t primeRK = 16777619;

bool Match(char* src, char* dst, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (src[i] != dst[i]) {
			break;
		}
	}
	if (i == len) {
		return true;
	}
	return false;
}

int RabinKarp(char* s, char* sep) {
	size_t sLen = strlen(s);
	size_t sepLen = strlen(sep);
	size_t hashsep, pow, h, sq;
	int j = 0;

	if (sepLen == 0 || sLen < sepLen) {
		return -1;
	}
	
	// 计算 sep 的 hash 值
	hashsep = 0;
	for (int i = 0; i < sepLen; i++) {
		hashsep = hashsep * primeRK + (size_t)(sep[i]);
	}

	pow = 1;
	sq = primeRK;
	for (int i = sepLen; i > 0; i >>= 1) {
		if (i & 1 != 0) { // 如果二进制最低位不是 0
			pow *= sq;
		}
		sq *= sq;
	}
	
	// 计算 s 中长度为 sepLen 的 hash 值
	h = 0;
	for (int i = 0; i < sepLen; i++) {
		h = h * primeRK + (size_t)(s[i]);
	}
	if (h == hashsep && Match(&s[j], sep, sepLen)) {
		return j;
	}
	j++;

	// 滚动 s 的 hash 值并与 sep 的 hash 值进行比较
	for (int i = sepLen; i < sLen; i++) {
		// 加上下一个字符的 hash 值
		h *= primeRK;
		h += (size_t)(s[i]);

		// 去掉第一个字符的 hash 值
		h -= pow * (size_t)(s[i - sepLen]);
		
		// 开始比较
		if (h == hashsep && Match(&s[j], sep, sepLen)) {
			return j;
		}
		j++;
	}

	return -1;
}

int main() {
	char* src = "hfjdhfijdhfiuebghksdgfy";
	char* dst = "dhfiu";
	cout << RabinKarp(src, dst) << endl;

	return 0;
}