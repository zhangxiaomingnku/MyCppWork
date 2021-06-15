#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    bool canPartition(std::vector<int>& nums) {
        int sum = 0;
        for(int i : nums) {
            sum += i;
        }
        if (sum%2 == 1) return false;
        std::vector<int> dp (sum+1, 0);
        dp[0] = 1;
        for (int num : nums) {
//            注意这里一定要从大到小，才能保证本次循环不会重复修改上一个值
            for (int i=sum;i>=0;--i) {
                if(dp[i]) {
                    dp[i+num] = 1;
                }
                if (dp[sum/2]) return true;
            }
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,5, 11, 5};
    Solution s;
    LOG_LINE( s.canPartition(input))
//    LOG_LINE( s.canPartition(std::vector<int> {1,2,3,5}))
    return 0;
}