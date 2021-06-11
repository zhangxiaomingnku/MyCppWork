#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            // j*j <= i 改成 就 j*j < i 错在哪里
            for (int j = 1; j*j <=i; ++j) {
                dp[i] = std::min(dp[i], dp[i-j*j]+1);
            }
        }
        return dp[n];
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    LOG_LINE( s.numSquares(12));
    return 0;
}