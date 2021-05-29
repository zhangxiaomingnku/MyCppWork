#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class Solution {
public:
    bool isPalindrome(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode* tmp = root->right;
        root->right = invertTree(root->left);
        root->left = invertTree(tmp);
        return root;
    }
};

int main(int argc, char* argv[])
{
    LOG_LINE("Hello world");
    return 0;
}

