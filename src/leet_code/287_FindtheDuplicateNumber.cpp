#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow ==fast) break;
        }
        fast = 0;
        while (fast!=slow) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

int main(int argc, char* argv[])
{
    std::vector<int> input = {1,3,4,2,2};
    Solution s;
    LOG_LINE( s.findDuplicate(input));
    return 0;
}