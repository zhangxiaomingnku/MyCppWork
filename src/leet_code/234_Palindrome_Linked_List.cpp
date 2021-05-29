#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define LOG_LINE(msg) std::cout << msg << std::endl;

 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        if(fast) slow = slow->next;
        slow = reverse(slow);
        while (slow) {
            if (slow->val != head->val) return false;
            slow = slow->next;
            head = head->next;
        }
        return true;
    }

private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        while (head) {
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};


int main(int argc, char* argv[])
{
    LOG_LINE("hello world");
    return 0;
}




