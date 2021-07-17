#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() <= 0) return -1;
        int max = nums[0];
        std::vector<int> dp(nums.size());
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = dp[i - 1] < 0 ? (nums[i]) : (dp[i - 1] + nums[i]);
            if (dp[i] > max) {
                max = dp[i];
            }
        }
        return max;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {-2,1,-3,4,-1,2,1,-5,4};
    Solution s;
    LOG_LINE( s.maxSubArray(input));
    return 0;
}