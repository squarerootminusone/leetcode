#define max(a, b) (a > b ? a : b)

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int> &lhs, vector<int> &rhs) {
            return lhs[0] < rhs[0];
        });

        vector<vector<int>> res;
        res.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            if (res.back()[1] >= intervals[i][0])
                res[res.size() - 1][1] = max(intervals[i][1], res.back()[1]);
            else
                res.push_back(intervals[i]);
        }

        return res;
    }
};