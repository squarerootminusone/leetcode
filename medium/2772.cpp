class Solution {
public:
    bool checkArray(vector<int>& nums, int k) {
        // Lookback table
        vector<int> arr(nums.size(), 0);

        int cnt = 0;
        for (int it = 0; it < nums.size(); it++) {
            // If past k-th element, substract how much was added k steps ago
            if (it >= k)
                cnt -= arr[it - k];

            // If the next element cannot absorb the count, it's impossible 
            if (nums[it] < cnt)
                return false;

            // If adding, save to the lookback array
            if (nums[it] > cnt) {
                arr[it] = nums[it] - cnt;
                cnt = nums[it];
            }
        }

        // Make sure nothing was added in the last k-1 steps
        for (int it = nums.size() - k + 1; it < nums.size(); it++)
            if (arr[it] > 0)
                return false;

        return true;    
    }
};
