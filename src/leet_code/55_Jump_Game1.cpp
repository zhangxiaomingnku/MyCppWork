#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    bool canJump(const std::vector<int>& nums) {
        int far= nums[0];
        for (int i = 0; i < nums.size(); ++i) {
            if (i > far) break;
            if (far < i + nums[i]) {
                far = i + nums[i];
            }
        }
        return far >= nums.size() - 1;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {2,3,1,1,4};
    Solution s;
    LOG_LINE("can jump: " << s.canJump(input));
    return 0;
}