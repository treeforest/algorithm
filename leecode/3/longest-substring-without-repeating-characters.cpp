#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        set<char> store;
        int l = 0, r = 0, len = s.size();
        size_t count = 0;
        while (r < len) {
            char c = s[r];
            if (store.find(c) != store.end()) {
                count = max(count, store.size());
                while (l < r && s[l] != c) {
                    store.erase(s[l]);
                    l++; // ×óÖ¸ÕëÓÒÒÆ
                }
                l++;
            }
            else {
                store.insert(c);
            }
            r++;
        }
        return max(count, store.size());
    }
};