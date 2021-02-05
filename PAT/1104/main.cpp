#include <iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	double sum = 0.0, tmp;
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		sum += (tmp * i * (n - i + 1));
	}
	printf("%.2f\n", sum);
	return 0;
}