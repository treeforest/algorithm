#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        int l = 0;
        int r = 1;
        while (r < nums.size()) {
            if (nums[r] != nums[l]) {
                l++;
                nums[l] = nums[r];
                r++;
            }
            else {
                r++;
            }
        }
        return l + 1;
    }
};