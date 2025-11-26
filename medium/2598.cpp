class Solution {
    public:
        int findSmallestInteger(vector<int>& nums, int value) {
            vector<int> mods(value);
    
            for (int num : nums) {
                int mod = num % value;
                mods[mod + (mod < 0 ? value : 0)]++;
            }
    
            int min = 1e9, min_pos = -1;
            for (int i = 0; i < value; i++) {
                if (mods[i] < min) {
                    min_pos = i;
                    min = mods[i];
                }
            }
    
            return value * min + min_pos;
        }
    };