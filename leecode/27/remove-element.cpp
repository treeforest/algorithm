class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        int i = -1;
        int j = 0;
        int len = nums.size();
        while (j < len) {
            if (nums[j] == val) {
                j++;
            }
            else {
                i++;
                nums[i] = nums[j];
                j++;
            }
        }
        return i + 1;
    }
};