#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> ans;
        std::vector<int> cur;
        std::sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, cur, ans);
        return ans;
    }

    void dfs(std::vector<int>& candidates, int target, int s, std::vector<int>& cur, std::vector<std::vector<int>>& ans) {
        if (target == 0) {
            ans.emplace_back(cur);
            return;
        }
        for (int i = s; i < candidates.size(); ++i) {
            if (target < candidates[i]) {
                break;
            } else {
                cur.push_back(candidates[i]);
                dfs(candidates, target - candidates[i], i, cur, ans);
                cur.pop_back();
            }
        }
    }
};

//Input: candidates = [2,3,6,7], target = 7
//Output: [[2,2,3],[7]]
//Explanation:
//2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
//7 is a candidate, and 7 = 7.
//These are the only two combinations.

int main(int argc, char* argv[])
{
    std::vector<int> candidates = {2,3,6,7};
    int target = 7;
    Solution solution;
    std::vector<std::vector<int>> ans = solution.combinationSum(candidates, target);
    for (auto& res : ans) {
        std::string str;
        for (auto e : res) {
            str = str.append(std::to_string(e)).append(" ");
        }
        LOG_LINE(str);
    }
    return 0;
}




