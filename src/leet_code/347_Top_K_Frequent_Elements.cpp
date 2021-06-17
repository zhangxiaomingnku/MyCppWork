#include <iostream>
#include <vector>
#include <unordered_map>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> count;
        int max_frequent = 1;
        for (int num : nums) {
            ++count[num];
            max_frequent = std::max(max_frequent, count[num]);
        }
        std::unordered_map<int, std::vector<int>> reverse_count;
        for (const auto& kv : count) {
            reverse_count[kv.second].push_back(kv.first);
        }
        std::vector<int> res;
        for (int i=max_frequent;i>=0;--i) {
            auto it = reverse_count.find(i);
            if(it == reverse_count.end()) continue;
            res.insert(res.end(), it->second.begin(), it->second.end());
            if (res.size() == k) return res;
        }
        return res;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,2,2,3,4,3,3,5};
    Solution s;
    for (auto num : s.topKFrequent(input, 2)) {
        LOG_LINE(num);
    }
    return 0;
}