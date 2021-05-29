#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define LOG_LINE(msg) std::cout << msg << std::endl;
//input:  11000
//        11000
//        00100
//        00011
//output: 3

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        if(grid.empty()) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                ans += grid[x][y] - '0';
                dfs(grid, x, y, m, n);
            }
        }
        return ans;
    }
private:
    void dfs(std::vector<std::vector<char>>& grid, int x, int y, int m, int n) {
        if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == '0')
            return;
        grid[x][y] = '0';
        dfs(grid, x - 1, y, m, n);
        dfs(grid, x + 1, y, m, n);
        dfs(grid, x, y - 1, m, n);
        dfs(grid, x, y + 1, m, n);
    }
};

int main(int argc, char* argv[])
{
    std::vector<std::vector<char>> grid = {{'1','1','0','0','0'},{'1','1','0','0','0'}};
    Solution solution;
    int ans = solution.numIslands(grid);
    LOG_LINE(ans);
    return 0;
}

