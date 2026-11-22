class Solution {
    vector<int> bestSubseq(vector<int>& seq, int len) {
        vector<int> s;
        s.reserve(len);
        for (int i = 0; i < seq.size(); i++) {
            // If the top number is larger and there is enough space, then pop
            while (!s.empty() && seq[i] > s.back() && seq.size() - i + s.size() > len)
                s.pop_back();
            // If there is space left, add the number
            if (s.size() < len)
                s.push_back(seq[i]);
        }
        return s;
    }

public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> best_res(k, -1), res(k);
        for (int a = max(0, k - (int)nums2.size()); a <= min(k, (int)nums1.size()); a++) {
            int b = k - a;

            // Calculate subsegments
            vector<int> best1 = bestSubseq(nums1, a);
            vector<int> best2 = bestSubseq(nums2, b);

            // Combine
            int l = 0, r = 0;
            for (int i = 0; i < k; i++)
                res[i] = lexicographical_compare(best2.begin() + r, best2.end(), best1.begin() + l, best1.end())
           ? best1[l++] : best2[r++];

            if (lexicographical_compare(best_res.begin(), best_res.end(), res.begin(), res.end()))
                best_res = res;
        }

        return best_res;
    }
};
