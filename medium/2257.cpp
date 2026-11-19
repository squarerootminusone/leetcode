class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<bool>> mp(m, vector<bool>(n, false));

        // horizontal
        sort(guards.begin(), guards.end(), [](const vector<int>& lhs, const vector<int>& rhs) { 
            if (lhs[0] == rhs[0])
                return lhs[1] < rhs[1];
            return lhs[0] < rhs[0];
        });
        sort(walls.begin(), walls.end(), [](const vector<int>& lhs, const vector<int>& rhs) { 
            if (lhs[0] == rhs[0])
                return lhs[1] < rhs[1];
            return lhs[0] < rhs[0];
        });

        int it_g = -1;
        int it_w = -1;
        for (int y = 0; y < m; y++) {
            bool on = (it_g + 1 < (int)guards.size() && guards[it_g + 1][0] == y && (it_w + 1 == (int)walls.size() || walls[it_w + 1][0] != y || walls[it_w + 1][1] > guards[it_g + 1][1]));
            for (int x = 0; x < n; x++) {
                if (it_g + 1 < (int)guards.size() && guards[it_g + 1][0] == y && guards[it_g + 1][1] == x) {
                    it_g++;
                    on = true;
                    mp[y][x] = true;
                } else if (it_w + 1 < (int)walls.size() && walls[it_w + 1][0] == y && walls[it_w + 1][1] == x) {
                    it_w++;
                    on = !(it_g + 1 == (int)guards.size() || guards[it_g + 1][0] != y || !(it_w + 1 == (int)walls.size() || walls[it_w + 1][0] != y || walls[it_w + 1][1] > guards[it_g + 1][1]));
                    mp[y][x] = true;
                } else if (on) {
                    mp[y][x] = true;
                }
            }
        }
        
        // vertical
        sort(guards.begin(), guards.end(), [](const vector<int>& lhs, const vector<int>& rhs) { 
            if (lhs[1] == rhs[1])
                return lhs[0] < rhs[0];
            return lhs[1] < rhs[1];
        });
        sort(walls.begin(), walls.end(), [](const vector<int>& lhs, const vector<int>& rhs) { 
            if (lhs[1] == rhs[1])
                return lhs[0] < rhs[0];
            return lhs[1] < rhs[1];
        });

        it_g = -1;
        it_w = -1;
        for (int x = 0; x < n; x++) {
            bool on = (it_g + 1 < (int)guards.size() && guards[it_g + 1][1] == x && (it_w + 1 == (int)walls.size() || walls[it_w + 1][1] != x || walls[it_w + 1][0] > guards[it_g + 1][0]));
            for (int y = 0; y < m; y++) {
                if (it_g + 1 < (int)guards.size() && guards[it_g + 1][0] == y && guards[it_g + 1][1] == x) {
                    it_g++;
                    on = true;
                    mp[y][x] = true;
                } else if (it_w + 1 < (int)walls.size() && walls[it_w + 1][0] == y && walls[it_w + 1][1] == x) {
                    it_w++;
                    on = !(it_g + 1 == (int)guards.size() || guards[it_g + 1][1] != x || !(it_w + 1 == (int)walls.size() || walls[it_w + 1][1] != x || walls[it_w + 1][0] > guards[it_g + 1][0]));
                    mp[y][x] = true;
                } else if (on) {
                    mp[y][x] = true;
                }
            }
        }

        // count
        int cnt = 0;
        for (int y = 0; y < m; y++)
            for (int x = 0; x < n; x++)
                cnt += (int)mp[y][x];

        return m * n - cnt;
    }
};
