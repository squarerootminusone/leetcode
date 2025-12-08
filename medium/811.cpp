class Solution {
    public:
        vector<string> subdomainVisits(vector<string>& cpdomains) {
            unordered_map<string, int> counts;
            
            for (string &cpdomain: cpdomains) {
                size_t s = cpdomain.find(' ');
                int count = stoi(cpdomain.substr(0, s));
                
                for (int i = (int)cpdomain.size() - 1; i >= (int)s; i--) {
                    if (cpdomain[i] == '.' || cpdomain[i] == ' ')
                        counts[cpdomain.substr(i + 1)] += count;
                }
            }
    
            vector<string> res;
            for (auto [domain, count] : counts)
                res.push_back(to_string(count) + " " + domain);
            return res;
        }
    };