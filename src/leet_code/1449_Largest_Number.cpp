#include <iostream>
#include <vector>
#include <string>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    std::string largestNumber(std::vector<int>& cost, int target) {
        std::vector<std::pair<int, int>> dp(target + 1, {-1, -1});
        dp[0] = {0,0};
        for (int i=0; i<=target; ++i) {
            for (int j=1; j<=9; ++j) {
                const int sub_targrt = i - cost[j-1];
                if (sub_targrt < 0 || dp[sub_targrt].second == -1
                || dp[sub_targrt].second + 1 < dp[i].second) {
                    continue;
                }
                dp[i] = std::pair<int, int> {j, dp[sub_targrt].second +1};
            }
        }
//        LOG_LINE(dp[target].first << ":" << dp[target].second);
        if (dp[target].second == -1) return "0";
        std::string ans;
        while (target) {
            ans += dp[target].first + '0';
            target -= cost[dp[target].first - 1];
        }
        return ans;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {4,3,2,5,6,7,2,5,5};
    Solution s;
    LOG_LINE( s.largestNumber(input, 9));
    return 0;
}