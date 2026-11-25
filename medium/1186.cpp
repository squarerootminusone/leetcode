class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<array<int, 2>> dp(n + 1);

        int best = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][1] = max(0, max(dp[i - 1][0], dp[i - 1][1] + arr[i - 1]));
            dp[i][0] = max(0, dp[i - 1][0] + arr[i - 1]);
            best = max(best, max(dp[i][0], dp[i][1]));
        }

        return best == 0 ? ranges::max(arr) : best;
    }
};
