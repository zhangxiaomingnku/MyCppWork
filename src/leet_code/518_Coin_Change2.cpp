#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int change( int amount, std::vector<int>& coins) {
        std::vector<long long> dp(amount + 1);
        dp[0] = 1;
        for(int coin : coins) {
            for(int i=0;i<=amount; ++i) {
                if(i>=coin) {
                    dp[i] = dp[i] + dp[i-coin];
                }
            }
        }
        return dp[amount];
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,2,5};
    Solution s;
    LOG_LINE( s.change(5, input));
    return 0;
}