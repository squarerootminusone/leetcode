#define min(a, b) (a < b ? a : b)

class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double tax = 0.0;
        int prev = 0;
        
        for (vector<int>& bracket : brackets) {
            if (income <= 0)
                break;

            tax += (double)bracket[1] / 100 * min(income, bracket[0] - prev);
            income -= (bracket[0] - prev);
            prev = bracket[0];
        }
        return tax;
    }
};