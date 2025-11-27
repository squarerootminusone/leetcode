#define max(a, b) (a > b ? a : b)

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<int> degrees(n, 0), prereq(n, 0);
        vector<vector<int>> edges(n, vector<int>());
        for (vector<int>& relation : relations) {
            degrees[relation[1] - 1]++;
            edges[relation[0] - 1].push_back(relation[1] - 1);
        }

        // Queue of nodes with degree 0
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (degrees[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int from = q.front(); q.pop();
            for (int to : edges[from]) {
                prereq[to] = max(prereq[to], prereq[from] + time[from]);
                if (--degrees[to] == 0)
                    q.push(to);
            }
        }

        int longest = 0;
        for (int i = 0; i < n; i++)
            longest = max(longest, prereq[i] + time[i]);
        return longest;
    }
};