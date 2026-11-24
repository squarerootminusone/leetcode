class Solution {
    struct TrieNode {
        array<unique_ptr<TrieNode>, 26> next{};
        int16_t eow = -1, cnt = 0;
    };

    struct Position {
        int y, x;

        inline bool valid(vector<vector<char>>& board) {
            return y >= 0 && x >= 0 && y < board.size() && x < board.front().size();
        }
    };

    unique_ptr<TrieNode> root = make_unique<TrieNode>();

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Construct the trie
        for (int i = 0; i < words.size(); i++) {
            TrieNode* node = root.get();
            for (char c : words[i]) {
                if (node->next[c - 'a'] == nullptr)
                    node->next[c - 'a'] = make_unique<TrieNode>();
                node = node->next[c - 'a'].get();
                node->cnt++;
            }
            node->eow = i;
        }

        // Traverse for every grid tile
        vector<string> res;
        vector<vector<bool>> visited(board.size(), vector<bool>(board.front().size(), false));
        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board.front().size(); x++) {
                TrieNode* start = root->next[board[y][x] - 'a'].get();
                if (start && start->cnt > 0) {
                    auto dfs = [&](auto&& self, TrieNode* node, Position cur) -> int {
                        int got = 0;
                        static constexpr array<Position, 4> dirs = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};

                        // Check that the trie matches
                        if (node->eow >= 0) {
                            res.push_back(words[node->eow]);
                            node->eow = -1;
                            got++;
                        }

                        for (auto& dir: dirs) {
                            Position next{cur.y + dir.y, cur.x + dir.x};
                            if (!next.valid(board) || visited[next.y][next.x])
                                continue;

                            TrieNode* child = node->next[board[next.y][next.x] - 'a'].get();
                            if (child && child->cnt > 0) {
                                visited[next.y][next.x] = true;
                                got += self(self, child, next);
                                visited[next.y][next.x] = false;
                            }
                        }

                        node->cnt -= got;
                        return got;
                    };

                    visited[y][x] = true;
                    dfs(dfs, start, {y, x});
                    visited[y][x] = false;
                }
            }
        }

        return res;
    }
};
