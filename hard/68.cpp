class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int lhs = 0;
        int len = words[0].size();

        while (lhs < words.size()) {
            // Get words
            int rhs = lhs;
            while (rhs + 1 < words.size() && len + words[rhs + 1].size() + (rhs - lhs + 1) <= maxWidth) {
                rhs++;
                len += words[rhs].size();
            }

            // Add string
            string s;
            int splits = rhs - lhs;

            // Left-adjusted
            if (splits == 0 || rhs + 1 >= words.size()) {
                for (int i = lhs; i < rhs; i++)
                    s += words[i] + " ";
                s += words[rhs];
                s += string(maxWidth - s.size(), ' ');
            }
            // Evenly spaced
            else {
                int empty = maxWidth - len;
                int stride = empty / splits;

                for (int i = lhs; i < rhs; i++)
                    s += words[i] + string(stride + (int)(stride * splits + (i - lhs + 1) <= empty), ' ');
                s += words[rhs];
            }
            res.push_back(s);

            // Next
            lhs = rhs + 1;
            len = rhs + 1 < words.size() ? words[rhs + 1].size() : 0;
        }

        return res;
    }
};
