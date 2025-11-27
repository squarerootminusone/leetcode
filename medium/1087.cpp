class Solution {
    public:
        void expand_rec(string base, int i, string& s, vector<string>& res) {
            // Go through single options
            for (; i < s.size() && s[i] != '{'; i++)
                base += s[i];
    
            // If the string ended return the current base
            if (i >= s.size())
                res.push_back(base);
    
            else {
                // Determine character options
                vector<char> options;
                i++;
                for (; i < s.size() && s[i - 1] != '}'; i += 2)
                    options.push_back(s[i]);
                sort(options.begin(), options.end());
    
                // Expand for every character option
                for (char option : options)
                    expand_rec(base + option, i, s, res);
            }
        }
    
        vector<string> expand(string s) {
            vector<string> res;
            expand_rec("", 0, s, res);
            return res;
        }
    };