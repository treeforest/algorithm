#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

#define MAXSIZE 1080
#define STEP 10

int length(char* str, int size) {
	int n = 0;
	for (n; n < size; n += STEP) {
		if (str[n] == '\0') {
			break;
		}
	}
	while (str[n] == '\0' || str[n] == '\r' || str[n] == '\n') {
		n--;
	}
	return n + 1;
}

void caculate(char* res, int& resBegin, int& resEnd, char* tmp, int tmpLen) {
	int i = resEnd;// res 的末尾索引
	int j = tmpLen - 1;
	int flag = 0;
	int num = 0;
	int sub = 2 * '0';
	int k; // 新的末尾索引
	int newBegin = resBegin;
	int resLen = resEnd - resBegin + 1;
	resLen = resLen > tmpLen ? resLen : tmpLen;

	if (resBegin == 0) {
		newBegin = 1;
	}
	resEnd = resLen;
	k = resEnd;

	for (i, j; i >= resBegin && j >= 0; --i, --j) {
		num = res[i] + tmp[j] - sub + flag;
		if (num > 9) {
			num = num - 10;
			flag = 1;
		}
		else {
			flag = 0;
		}
		res[k--] = num + '0';
	}

	while (i >= resBegin && flag) {
		num = res[i--] - '0' + flag;
		if (num > 9) {
			num = num - 10;
			flag = 1;
		}
		else {
			flag = 0;
		}
		res[k--] = num + '0';
	}
	while (i >= resBegin) res[k--] = res[i--];

	while (j >= 0 && flag) {
		num = tmp[j--] - '0' + flag;
		if (num > 9) {
			num = num - 10;
			flag = 1;
		}
		else {
			flag = 0;
		}
		res[k--] = num + '0';
	}
	while (j >= 0) res[k--] = tmp[j--];

	if (flag) {
		res[k--] = flag + '0';
		if (k == -1) {
			newBegin = 0;
		}
	}

	resBegin = newBegin;
	res[resEnd + 1] = '\0';
}

int main() {
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时 

	ifstream inFile;
	inFile.open("file.txt", ios::binary);
	if (inFile.bad()) {
		abort();
	}

	char res[MAXSIZE] = { 0 };// 存结果
	char tmp[MAXSIZE] = { 0 };// 存临时数据
	if (inFile.eof()) {
		return 0;
	}
	memset(res, '\0', MAXSIZE);
	inFile.getline(res, MAXSIZE);

	int resBegin, resEnd, tmplen;
	resBegin = 0;
	resEnd = length(res, MAXSIZE) - 1;
	tmplen = MAXSIZE;

	while (!inFile.eof()) {
		memset(tmp, '\0', tmplen);
		inFile.getline(tmp, MAXSIZE);
		tmplen = length(tmp, MAXSIZE);
		caculate(res, resBegin, resEnd, tmp, tmplen);
		//cout << &res[resBegin] << endl;
	}

	cout << &res[resBegin] << endl;
	inFile.close();

	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "程序执行时间：" << time * 1000 << "ms" << endl;
	system("pause");

	return 0;
}