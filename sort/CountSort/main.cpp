#include <iostream>
using namespace std;

/*
 * 计数排序
 *
 * 参数
 *  A：待排序的数组
 *  B：存放排序输出的数组
 *  len：数组 A 的长度（也即 B 的长度）
 *  k：要求 A 中的每一个数组都是 0~k 的数
 */
void CountSort(int A[], int B[], int len, int k) {
	int i, j;
	int* C = new int[k + 1]();
	
	// make C[i] contains the number of elements equal to i.
	for (i = 0; i < len; i++) {
		C[A[i]] = C[A[i]] + 1;
	}

	// make C[i] contains the number of elements less than or equal to i.
	for (i = 1; i <= k; i++) {
		C[i] = C[i] + C[i - 1];
	}

	for (j = len - 1; j >= 0; j--) {
		B[C[A[j]]] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}
}

int main() {

	int A[] = { 2,5,3,0,2,3,0,3 };
	int B[8] = {};
	CountSort(A, B, sizeof(A) / sizeof(int), 5);

	return 0;
}