#include <iostream>
#include <vector>
#include <algorithm>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n) {
        std::vector<int> count(26,0);
        for (char c : tasks) {
            ++count[c - 'A'];
        }
        const int max_count = *std::max_element(count.begin(),count.end());
        size_t ans = (max_count - 1) * (n + 1);
        for (int num : count) {
            if (num == max_count) {
                ++ans;
            }
        }
//        ans += std::count_if(count.begin(), count.end(),
//                        [max_count](int c){ return c == max_count; });
        return std::max(ans, tasks.size());
    }
};


//Input: tasks = ["A","A","A","B","B","B"], n = 2
//Output: 8
//Explanation: A -&gt; B -&gt; idle -&gt; A -&gt; B -&gt; idle -&gt; A -&gt; B.
int main(int argc, char* argv[])
{
    std::vector<char> input = {'A','A','A','B','B','B'};
    Solution s;
    LOG_LINE("can jump: " << s.leastInterval(input, 2));
    return 0;
}