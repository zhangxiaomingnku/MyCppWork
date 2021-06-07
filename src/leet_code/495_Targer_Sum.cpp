#include <iostream>
#include <vector>
#include <numeric>
#define LOG_LINE(msg) std::cout << msg << std::endl;

/**
     * 494
     * 输入: nums: [1, 1, 1, 1, 1], S: 3
     * 输出: 5
     * 解释:
     * -1+1+1+1+1 = 3
     * +1-1+1+1+1 = 3
     * +1+1-1+1+1 = 3
     * +1+1+1-1+1 = 3
     * +1+1+1+1-1 = 3
     *
     * sum(P) 前面符号为+的集合；sum(N) 前面符号为减号的集合
     * 所以题目可以转化为
     * sum(P) - sum(N) = target
     * => sum(nums) + sum(P) - sum(N) = target + sum(nums)
     * => 2 * sum(P) = target + sum(nums)
     * => sum(P) = (target + sum(nums)) / 2
     * 因此题目转化为01背包，也就是能组合成容量为sum(P)的方式有多少种
     */

class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum < target) return 0;
        const int n = nums.size();
        const int offset = sum;
        std::vector<std::vector<int>> ways(n + 1, std::vector<int>(offset + sum + 1, 0));
        ways[0][sum] = 1;
        for (int i =0; i < n; ++i) {
            for (int j = nums[i]; j < 2*sum - nums[i] +1; ++j ) {
                if (ways[i][j]) {
                    ways[i+1][j + nums[i]] = ways[i][j] + ways[i+1][j + nums[i]];
                    ways[i+1][j - nums[i]] = ways[i][j] + ways[i+1][j - nums[i]];
                }
            }
        }
        return ways.back()[target + offset];
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,1,1,1,1};
    Solution s;
    LOG_LINE("target sum: " << s.findTargetSumWays(input, 3));
    return 0;
}