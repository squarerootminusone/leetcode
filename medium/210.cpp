class Solution {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<vector<int>> adj(numCourses);
            vector<int> degree(numCourses);
    
            for (vector<int> &prereq : prerequisites) {
                adj[prereq[1]].push_back(prereq[0]);
                degree[prereq[0]]++;
            }
        
            queue<int> q;
            for (int i = 0; i < numCourses; i++)
                if (degree[i] == 0)
                    q.push(i);
    
            vector<int> res;
            while (!q.empty()) {
                int from = q.front();
                q.pop();
                res.push_back(from);
    
                for (int to : adj[from]) {
                    degree[to]--;
                    if (degree[to] == 0)
                        q.push(to);
                }
            }
    
            if (res.size() == numCourses)
                return res;
    
            return vector<int>();
        }
    };s