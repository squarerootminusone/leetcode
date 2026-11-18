class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<int> degrees(n, 0);
        for (vector<int>& v: roads) {
            degrees[v[0]]++;
            degrees[v[1]]++;
        }

        long long res = 0;
        sort(degrees.begin(), degrees.end());
        for (int i = 1; i <= n; i++)
            res += (long long)i * degrees[i - 1];

        return res;
    }
};
