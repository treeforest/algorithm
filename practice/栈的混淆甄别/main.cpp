#include <stack>
#include <string>
#include <iostream>
using namespace std;

bool stackWashing(stack<int> src, stack<int> dst) {
	stack<int> x, y;
	while (dst.size() != 0) {
		x.push(dst.top());
		dst.pop();
	}

	while (src.size()) {
		y.push(src.top());
		src.pop();
		if (x.top() == y.top()) {
			x.pop();
			y.pop();
			while (!y.empty() && x.top() == y.top()) {
				x.pop();
				y.pop();
			}
		}
	}

	return x.empty();
}

int main() {
	stack<int> src;
	stack<int> dst;
	src.push(4);
	src.push(3);
	src.push(2);
	src.push(1);

	dst.push(2);
	dst.push(1);
	dst.push(4);
	dst.push(3);

	cout << stackWashing(src, dst) << endl;
	return 0;
}