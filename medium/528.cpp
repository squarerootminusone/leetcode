class Solution {
    vector<int> pref;
    random_device rd;  // a seed source for the random number engine
    mt19937 gen; // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib;

public:
    Solution(vector<int>& w): pref(w.size()), gen(rd()) {
        pref[0] = w[0];
        for (int i = 1; i < w.size(); i++)
            pref[i] = pref[i - 1] + w[i];

        distrib = uniform_int_distribution<>(1, pref.back());
    }

    int pickIndex() {
        int idx = lower_bound(pref.begin(), pref.end(), distrib(gen)) - pref.begin();
        return idx;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
