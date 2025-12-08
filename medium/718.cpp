#define max(a, b) (a > b ? a : b)

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<int> prev(nums2.size() + 1);
        int best = 0;
        for (int i = 0; i < nums1.size(); i++) {
            vector<int> cur(nums2.size() + 1);
            for (int j = 0; j < nums2.size(); j++) {
                if (nums1[i] == nums2[j]) {
                    cur[j + 1] = 1 + prev[j];
                    best = max(best, cur[j + 1]);
                }
            }

            prev = cur;
        }

        return best;
    }
};