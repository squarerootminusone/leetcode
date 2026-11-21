#include <algorithm>
#include <bit>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Point update, range max. Leaves sit at t[n .. 2n-1], node i has children 2i and 2i+1.
// For another operation swap the three max calls and the identity (sum: 0, min: max()).
template<typename T>
struct SegTree {
    int n;
    vector<T> t;

    // Rounded up to a power of two so print() shows full levels
    SegTree(int sz): n(bit_ceil((unsigned)sz)), t(2 * n, 0) {}

    // Set position pos to val
    void update(int pos, T val) {
        for (t[pos += n] = val; pos > 1; pos /= 2)
            t[pos / 2] = max(t[pos], t[pos ^ 1]);
    }

    // Max over the inclusive range [l, r]
    T query(int l, int r) {
        T res = numeric_limits<T>::lowest(); // identity
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res = max(res, t[l++]);
            if (r & 1) res = max(res, t[--r]);
        }
        return res;
    }

    // One level per line, each node centred above its two children. w = width per leaf (even)
    void print(int w = 4) {
        for (int lvl = 1; lvl <= n; lvl *= 2) {
            int span = w * n / lvl;
            for (int i = lvl; i < lvl * 2; i++)
                cout << setw(span / 2 + 1) << t[i] << setw(span - span / 2 - 1) << "";
            cout << endl;
        }
    }
};
