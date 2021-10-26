#include <iostream>
using namespace std;

// 方法一 递归
//int fib(int N) {
//    if (N == 1 || N == 2) {
//        return 1;
//    }
//    return fib(N - 1) + fib(N - 2);
//}

// 方法二 备忘录方式
//int helper(int* memo, int n) {
//    if (n == 0 || n == 1) {
//        return n;
//    }
//    if (memo[n] != 0) {
//        return memo[n];
//    }
//    memo[n] = helper(memo, n - 1) + helper(memo, n - 2);
//    return memo[n];
//}
//int fib(int N) {
//    int* memo = new int[N + 1]();
//    return helper(memo, N);
//}


// 方法三 dp数组迭代
int fib(int N) {
    if (N == 0) {
        return 0;
    }
    int* dp = new int[N + 1]();
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= N; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[N];
}

int main() {
    cout << fib(30) << endl;
}