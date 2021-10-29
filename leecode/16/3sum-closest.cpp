#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end(), [](int a, int b) {return a < b; });
        int res = 10000;
        for (int i = 0; i < nums.size(); i++) {
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (abs(sum - target) < abs(res - target)) {
                    if (sum == target) {
                        // 相等 <=> 最接近，直接返回
                        return sum;
                    }
                    res = sum;
                }
                if (sum < target) {
                    while (l < r && nums[l] == nums[l + 1]) l++;
                    l++;
                }
                else {
                    while (l < r && nums[r] == nums[r - 1]) r--;
                    r--;
                }
            }
        }
        return res;
    }
};