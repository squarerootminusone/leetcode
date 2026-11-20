#define ll long long
const ll NEG = LLONG_MIN / 4;

class Solution {
public:
    ll maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<ll>> sums(n + 2, vector<ll>(n + 1, 0));

        // Vertical prefix sum table
        for (int x = 0; x < n; x++) {
            for (int y = 1; y <= n; y++)
                sums[x + 1][y] = sums[x + 1][y - 1] + grid[y - 1][x];
        }

        // i is the current end of the interval [a, c]
        vector<vector<ll>> DP_old(n + 1, vector<ll>(n + 1, 0));
        vector<vector<ll>> DP_new(n + 1, vector<ll>(n + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int b = 0; b <= n; b++) {
                // precompute best DP over a (low up to b)
                ll max_all = NEG, max_low = NEG;
                for (int a = 0; a <= b; a++)
                    max_all = max(max_all, DP_old[a][b]);
                max_low = max_all;
                for (int a = b + 1; a <= n; a++)
                    max_all = max(max_all, DP_old[a][b]);

                // iter over c
                // b > c - col c gains from b
                for (int c = 0; c < b; c++)
                    DP_new[b][c] = max_all + sums[i + 1][b] - sums[i + 1][c];

                // b <= c - col b gains from a what hasn't been covered by a
                ll max_mid = NEG;
                for (int c = b; c <= n; c++) {
                    ll best = max_all;                                       // a >= c
                    best    = max(best, max_low + sums[i][c] - sums[i][b]);  // a <= b
                    best    = max(best, max_mid + sums[i][c]);               // b < a < c
                    DP_new[b][c] = best;

                    // a = c joins the middle group for the next c
                    if (c > b)
                        max_mid = max(max_mid, DP_old[c][b] - sums[i][c]);
                }
            }

            swap(DP_old, DP_new);
        }

        ll mx = 0;
        for (int i = 0; i <= n; i++)
            mx = max(DP_old[i][0], mx);

        return mx;
    }
};
