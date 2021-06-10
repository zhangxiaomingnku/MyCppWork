#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    std::vector<int> getZerosOnes(const std::string& str) {
        std::vector<int> zerosOnes(2);
        for (int i= 0; i < str.length(); i++) {
            zerosOnes[str[i] - '0'] ++;
        }
        return zerosOnes;
    }

    int findMaxForm(std::vector<std::string>& strs, int m, int n) {
        int len = strs.size();
        std::vector<std::vector<std::vector<int>>> dp(len + 1, std::vector<std::vector<int>>(m +1 ,std::vector<int>(n+1)));
        for (int i = 1; i <= len; i++) {
            std::vector<int> zerosOnes = getZerosOnes(strs[i - 1]);
            int zeros = zerosOnes[0];
            int ones = zerosOnes[1];
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    if (j >= zeros && k >= ones) {
                        dp[i][j][k] = std::max(dp[i][j][k], (dp[i - 1][j - zeros][k - ones] + 1));
                    }
                }
            }
        }
        return dp[len][m][n];
    }
};
//TODO 状态压缩





//Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
//Output: 4
int main(int argc, char* argv[])
{
    std::vector<std::string> input = {"10","0001","111001","1","0"};
    Solution s;
    LOG_LINE( s.findMaxForm(input, 5, 3));
    return 0;
}