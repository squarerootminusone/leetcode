class Solution {
    public:
        void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int xs, int ys) {
            static vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    
            // Initial conditions
            queue<pair<int, int>> q;
            q.push({xs, ys});
            visited[xs][ys] = true;
    
            // Run BFS
            while (!q.empty()) {
                pair<int, int> from = q.front();
                q.pop();
                
                // Propagate in every direction
                for (auto &dir : dirs) {
                    int x = from.first + dir.first;
                    int y = from.second + dir.second;
    
                    if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && !visited[x][y]) {
                        if (grid[x][y] == '1')
                            q.push({x, y});                    
                        visited[x][y] = true;
                    }
                }
            }
        }
    
        int numIslands(vector<vector<char>>& grid) {
            vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    
            int count = 0;
            for (int x = 0; x < grid.size(); x++) {
                for (int y = 0; y < grid[0].size(); y++) {
                    if (!visited[x][y] && grid[x][y] == '1') {
                        bfs(grid, visited, x, y);
                        count++;
                    }
                }
            }
    
            return count;
        }
    };