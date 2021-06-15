#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    bool stoneGame(std::vector<int>& piles) {
        int len = piles.size();
        std::vector<std::vector<int>> dp(len, std::vector<int>(len, 0));
        for (int i=0;i<len;++i) {
            dp[i][i] = std::abs(piles[i]);
        }
        for (int r = 2; r <= len; ++r) {
            for (int i=0;i < len +1 - r;++i) {
                int j = i + r -1;
                dp[i][j] = std::max(piles[j] - dp[i][j-1], piles[i] - dp[i+1][j]);
            }
        }
        return dp[0][len-1] > 0;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {5,3,4,5};
    Solution s;
    LOG_LINE( s.stoneGame(input));
    return 0;
}