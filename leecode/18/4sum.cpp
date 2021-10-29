#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end(), [](int a, int b) {return a < b; });
        int len = nums.size();
        vector<vector<int>> result;
        if (len < 4) {
            return result;
        }
        int max = 1000000000;
        for (int i = 0; i < len; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                // 去重
                continue;
            }
            for (int j = i + 1; j < len; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    // 去重
                    continue;
                }
                int l = j + 1;
                int r = len - 1;
                while (l < r) {
                    if (nums[i] == max || nums[j] == max || nums[l] == max ||
                        nums[i] + nums[j] > max || nums[j] + nums[l] > max) {
                        // 越界数据
                        break;
                    }
                    int sum = nums[i] + nums[j] + nums[l] + nums[r];
                    if (sum == target) {
                        result.push_back({ nums[i], nums[j], nums[l], nums[r] });
                        while (l < r && nums[l + 1] == nums[l]) l++;
                        while (l < r && nums[r - 1] == nums[r]) r--;
                        l++;
                        r--;
                    }
                    else if (sum > target) {
                        while (l < r && nums[r - 1] == nums[r]) r--;
                        r--;
                    }
                    else {
                        while (l < r && nums[l + 1] == nums[l]) l++;
                        l++;
                    }
                }
            }
        }
        return result;
    }
};