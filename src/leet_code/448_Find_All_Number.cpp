#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        for (int i=0;i<nums.size();++i) {
            nums[abs(nums[i])-1] = -abs(nums[abs(nums[i])-1]);
        }
        std::vector<int> res;
        for (int i=0;i<nums.size();++i) {
            if (nums[i] > 0) {
                res.push_back(i+1);
            }
        }
        return res;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,2,2};
    Solution s;
    std::vector<int> res = s.findDisappearedNumbers(input);
    for (auto i:res) {
        LOG_LINE(i);
    }
    return 0;
}