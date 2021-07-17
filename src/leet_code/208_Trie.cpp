#include <iostream>
#include <vector>
#define LOG_LINE(msg) std::cout << msg << std::endl;
using namespace std;

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root_ = unique_ptr<TrieNode>(new TrieNode());
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root_.get();
        for (const char c : word) {
            if (!p->children[c - 'a']) {
                p->children[c - 'a'] = new TrieNode();
            }
            p = p->children[c - 'a'];
        }
        p->is_word = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto p = find(word);
        return p && p->is_word;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

private:
    struct TrieNode {
        TrieNode(): is_word(false),children(26, nullptr) {};
        ~TrieNode() {
            for (TrieNode* tn_ptr : children) {
                if (tn_ptr) {
                    delete tn_ptr;
                }
            }
        }

        bool is_word;
        vector<TrieNode*> children;
    };

    const TrieNode* find(const string& prefix) const {
        const TrieNode* p = root_.get();
        for (const char c : prefix) {
            p = p->children[c - 'a'];
            if (p == nullptr) break;
        }
        return p;
    }

    unique_ptr<TrieNode> root_;
};