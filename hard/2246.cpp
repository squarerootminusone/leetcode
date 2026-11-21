class Solution {

public:
    int longestPath(vector<int>& parent, string& s) {
        int n = parent.size();
        vector<int> deg(n, 0), down(n, 0), order;
        order.reserve(n);
        for (int i = 1; i < n; i++)
            deg[parent[i]]++;

        // Explore from leaves
        for (int i = 0; i < n; i++)
            if (deg[i] == 0)
                order.push_back(i);

        int best = 0;
        for (int i = 0; i < n; i++) {
            int cur = order[i];
            int par = parent[cur];
            if (par == -1)
                continue;

            // If different, connect the two down paths and update best
            if (s[cur] != s[par]) {
                best = max(best, down[cur] + down[par] + 1);
                down[par] = max(down[par], down[cur] + 1);
            }

            if (--deg[par] == 0)
                order.push_back(par);
        }

        return best + 1;
    }
};
