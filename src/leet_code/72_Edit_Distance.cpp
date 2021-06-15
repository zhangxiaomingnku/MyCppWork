#include <iostream>
#include <vector>
#include <string>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int minDistance(std::string word1, std::string word2) {
        int l1 = word1.length();
        int l2 = word2.length();
        std::vector<std::vector<int>> dp(l1 + 1, std::vector<int>(l2 + 1, 0));
        for (int i=0;i<=l1;++i) {
            dp[i][0] = i;
        }
        for (int j=0;j<=l2;++j) {
            dp[0][j] = j;
        }
        for (int i=1;i<=l1;++i) {
            for (int j=1;j<=l2;++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = std::min(dp[i-1][j-1], std::min(dp[i-1][j] +1, dp[i][j-1]+1));
                } else {
                    dp[i][j] = std::min(dp[i-1][j-1]+1, std::min(dp[i-1][j] +1, dp[i][j-1]+1));
                }
            }
        }
        return dp[l1][l2];
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    LOG_LINE( s.minDistance("syr", "sjj"));
    return 0;
}