#include <iostream>
#include <unordered_map>
#include <list>
#define LOG_LINE(msg) std::cout << msg << std::endl;

class LRUCache {
public:
    LRUCache(int capacity) {capacity_ = capacity;}
    int get(int key) {
        const auto it = m_.find(key);
        if (it == m_.cend()) return -1;
        cache_.splice(cache_.begin(),cache_, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        const auto it = m_.find(key);
        if (it != m_.cend()) {
            it->second->second = value;
            cache_.splice(cache_.begin(),cache_, it->second);
            return;
        }
        if (cache_.size() == capacity_) {
            const auto& node = cache_.back();
            m_.erase(node.first);
            cache_.pop_back();
        }
        cache_.emplace_front(key, value);
        m_[key] = cache_.begin();
    }

private:
    int capacity_;
    std::list<std::pair<int,int>> cache_;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> m_;
};


int main(int argc, char* argv[])
{
    LRUCache* cache = new LRUCache( 2 /* capacity */ );
    cache->put(1, 1);
    cache->put(2, 2);
    LOG_LINE( cache->get(1));       // returns 1
    cache->put(3, 3);    // evicts key 2
    LOG_LINE(cache->get(2));       // returns -1 (not found)
    cache->put(4, 4);    // evicts key 1
    LOG_LINE( cache->get(1) );       // returns -1 (not found)
    LOG_LINE(cache->get(3));       // returns 3
    LOG_LINE(cache->get(4));       // returns 4
    return 0;
}



