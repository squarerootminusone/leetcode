class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        // Build adjecency list
        vector<vector<int>> g(n);
        for (vector<int>& e : edges) {
            g[e[0] - 1].push_back(e[1] - 1);
            g[e[1] - 1].push_back(e[0] - 1);
        }

        // Get nodes with odd degree
        vector<int> odd;
        for (int i = 0; i < n; i++) 
            if (((int)g[i].size()) & 1)
                odd.push_back(i);
            
        if (odd.size() > 4)
            return false;

        auto can_add = [&](int a, int b) {
            return find(g[odd[a]].begin(), g[odd[a]].end(), odd[b]) == g[odd[a]].end(); 
        };

        // Case 0
        if (odd.size() == 0)
            return true;
        
        // Case 2
        if (odd.size() == 2) {
            if (can_add(0, 1))
                return true;

            // Check if there exists a node that neither of the odd nodes connect to
            vector<bool> blocked(n, false);
            for (int to : g[odd[0]]) blocked[to] = true;
            for (int to : g[odd[1]]) blocked[to] = true;
            return find(blocked.begin(), blocked.end(), false) != blocked.end();
        }

        // Case 4
        return (can_add(0, 1) && can_add(2, 3)) ||
               (can_add(0, 2) && can_add(1, 3)) || 
               (can_add(0, 3) && can_add(1, 2));
    }
};
