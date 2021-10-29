class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result(2, -1);
        if (nums.size() == 0) {
            return result;
        }
        int low = 0;
        int high = nums.size() - 1;
        int mid;
        while (low <= high) {
            mid = (low + high) / 2;
            if (nums[mid] == target) {
                for (int i = mid; i >= 0; i--) {
                    if (nums[i] != target) {
                        break;
                    }
                    result[0] = i;
                }
                for (int i = mid; i < nums.size(); i++) {
                    if (nums[i] != target) {
                        break;
                    }
                    result[1] = i;
                }
                break;
            }
            else if (nums[mid] > target) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return result;
    }
};