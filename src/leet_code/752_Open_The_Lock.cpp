#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#define LOG_LINE(msg) std::cout << msg << std::endl;


class Solution {
public:
    int openLock(const std::vector<std::string>& deadends, std::string target) {
        const std::string start = "0000";
        std::unordered_set<std::string> dead(deadends.begin(), deadends.end());
        if (dead.count(start)) return -1;
        if (start == target) return 0;

        std::queue<std::string> q;
        std::unordered_set<std::string> visited{start};
        int steps = 0;
        q.push(start);
        while (!q.empty()) {
            ++steps;
            int size = q.size();
            //            这里注意不可也写成 i<q.size()
            for (int i = 0; i < size; ++i) {
                const std::string cur = q.front();
                q.pop();
                for (int k = 0; k < 4; ++k) {
                    for(int n = -1; n <=1; n +=2) {
                        std::string next = cur;
                        next[k] = (next[k] - '0' + n + 10)%10 + '0';
                        if(next == target) {
                            return steps;
                        }
                        if(dead.count(next) || visited.count(next)) {
                            continue;
                        }
                        q.push(next);
                        visited.insert(next);
                    }
                }

            }
        }
        return -1;
    }
};


//Input: deadends = ["8888"], target = "0009"
//Output: 1
//Explanation:
//We can turn the last wheel in reverse to move from "0000" -> "0009".

int main(int argc, char* argv[])
{
    std::vector<std::string> input = {"8888"};
    std::string target = "0009";
    Solution s;
    LOG_LINE("open steps: " << s.openLock(input, target));
    return 0;
}