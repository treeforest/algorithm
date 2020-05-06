#include <ctime>
#include <iostream>
using namespace std;

struct Bucket {
	double val;
	Bucket* next;
};

void BucketSort(double A[], int len) {
	int i, j;
	Bucket** B = NULL;
	Bucket* b = NULL;
	Bucket* p = NULL;
	Bucket* q = NULL;

	B = new Bucket*[len]();
	for (i = 0; i < len; i++) {
		B[i] = NULL;
	}

	for (i = 0; i < len; i++) {
		b = new Bucket();
		b->val = A[i];
		b->next = NULL;
		j = (int)(A[i] * len);

		p = B[j];
		if (!p){
			B[j] = b;
			continue;
		}

		if (b->val < p->val) {
			b->next = p;
			B[j] = b;
			continue;
		}

		while (p && b->val > p->val) {
			q = p;
			p = p->next;
		}
		q->next = b;
		b->next = p;
	}

	for (i = 0, j = 0; i < len && j < len; i++) {
		p = B[i];
		while (p){
			A[j++] = p->val;
			q = p->next;
			delete p;
			p = q;
		}
	}

	delete[] B;
}

int main() {
	srand((unsigned)time(NULL));
	const int buf_size = 10;
	double buf[buf_size] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

	BucketSort(buf, buf_size);

	for (int i = 0; i < buf_size; i++){
		cout << buf[i] << " ";
	}

	return 0;
}