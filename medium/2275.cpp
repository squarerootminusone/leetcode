class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        int cnt[32] = {0};
        for (int& candidate: candidates)
            for (int i = 0; i < 32; i++)
                cnt[i] += (candidate & (1 << i)) > 0 ? 1: 0;

        return *max_element(cnt, cnt + 32);
    }
};
