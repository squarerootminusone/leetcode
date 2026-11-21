template<typename T>
struct SegTree {
    int n;
    vector<T> t;

    SegTree(int sz): n(bit_ceil((unsigned)sz)), t(2 * n, 0) {}

    void update(int pos, T val) {
        for (t[pos += n] = val; pos > 1; pos /= 2) 
            t[pos / 2] = max(t[pos], t[pos ^ 1]);
    }
    
    T query(int l, int r) {
        T res = numeric_limits<T>::lowest(); // identity
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }

    void print(int w = 4) {
        for (int lvl = 1; lvl <= n; lvl *= 2) {
            int span = w * n / lvl;
            for (int i = lvl; i < lvl * 2; i++) 
                cout << setw(span / 2 + 1) << t[i] << setw(span - span / 2 - 1) << "";
            cout << endl;
        }
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        int n = min((int)5e4, 3 * (int)queries.size()) + 2;
        SegTree<int> tree(n);

        // Keep track of obstacles
        set<int> obstacles;
        obstacles.insert(0);
        obstacles.insert(n - 1);

        vector<bool> res;
        for (vector<int>& query: queries) {
            switch(query[0]) {
                case 1: {
                    int pos = query[1];

                    // Find the two neighbouring obstacles and update the set
                    int lhs = *prev(obstacles.lower_bound(pos));
                    int rhs = *obstacles.upper_bound(pos);
                    obstacles.insert(pos);

                    // Update the tree
                    tree.update(pos, pos - lhs);
                    tree.update(rhs, rhs - pos);
                    break;
                }
                case 2: {
                    int x = query[1], sz = query[2];
                    // Consider [last_obstacle, x]
                    int lhs = *prev(obstacles.lower_bound(x));
                    res.push_back(tree.query(0, x) >= sz || x - lhs >= sz);
                    break;
                }
            }
        }

        return res;
    }
};
