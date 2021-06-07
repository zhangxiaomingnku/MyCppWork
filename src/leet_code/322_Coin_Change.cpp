#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        std::vector<long long> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for(int coin : coins) {
            for(int i=0;i<=amount; ++i) {
                if(i>=coin) {
                    dp[i] = std::min(dp[i], dp[i-coin]+1);
                }
            }
        }
        return dp[amount] == INT_MAX ? -1 :dp[amount];
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,2,5};
    Solution s;
    LOG_LINE( s.coinChange(input, 11));
    return 0;
}