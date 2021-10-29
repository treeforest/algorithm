#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    // 下一个更大的整数序列
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        int i, j;
        for (i = len - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                break;
            }
        }
        if (i >= 0) {
            for (j = len - 1; j > i; j--) {
                if (nums[j] > nums[i]) {
                    break;
                }
            }
            swap(nums[i], nums[j]);
        }
        int l = i + 1;
        int r = len - 1;
        while (l < r) {
            swap(nums[l], nums[r]);
            l++;
            r--;
        }
    }
};
