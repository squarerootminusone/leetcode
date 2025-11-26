class Solution {
    public:
        void dfs(string a, vector<string> &itinerary, unordered_map<string, multiset<string, greater<string>>> &graph) {
            while (!graph[a].empty()) 
                dfs(graph[a].extract(--graph[a].end()).value(), itinerary, graph);
            itinerary.push_back(a);
        }
    
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            unordered_map<string, multiset<string, greater<string>>> graph = {};
            vector<string> itinerary = vector<string>();
            for (vector<string> &ticket : tickets)
                graph[ticket[0]].insert(ticket[1]);
    
            dfs("JFK", itinerary, graph);
            reverse(itinerary.begin(), itinerary.end());
            return itinerary;
        }
    };