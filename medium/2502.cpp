class Allocator {
    int n;
    vector<int> memory;
    vector<vector<int>> blocks;

public:
    Allocator(int n): n(n), memory(n + 1, 0), blocks(1001) {}

    int allocate(int size, int mID) {
        for (int i = 0; i < n;) {
            int sz = 0;
            while (i + sz < n && memory[i + sz] == 0) {
                if (++sz == size) {
                    memory[i] = size;
                    blocks[mID].push_back(i);
                    return i;
                }
            }

            if (i + sz == n)
                break;

            i += memory[i + sz] + sz;
        }

        return -1;
    }

    int freeMemory(int mID) {
        int freed = 0;
        for (int pos : blocks[mID]) {
            freed += memory[pos];
            memory[pos] = 0;
        }
        blocks[mID].clear();
        return freed;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
