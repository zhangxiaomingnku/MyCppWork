#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
public:
    int peek() const {
        return data_[0];
    }

    int size() const {
        return data_.size();
    }

    int pop() {
        swap(data_[0], data_[data_.size() - 1]);
        int min = data_.back();
        data_.pop_back();
//        从上向下整理
        heapifyDown(0);
        return min;
    }

    void push(int key){
        data_.push_back(key);
//        从下向上整理
        heapifyUp(data_.size() - 1);
    }

private:
    vector<int> data_;
    void heapifyUp(int index) {
        if (index == 0) return;;
        int parent = (index - 1)/2;
        if (data_[index] < data_[parent]) {
            swap(data_[parent], data_[index]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2*index + 1;
        int right = 2*index + 2;
        if (left >= data_.size()) return;;
        int min_val = (right < data_.size()) && data_[right] < data_[left] ? right : left;
        if (data_[index] <= data_[min_val]) return;;
        swap(data_[min_val], data_[index]);
        heapifyDown(min_val);
    }
};


int main() {
    vector<int> data{5,1,3,5,3,4,3,7};
    MinHeap heap;
    for (int x : data)
        heap.push(x);
    vector<int> output;
    while (heap.size())
        output.push_back(heap.pop());
    for (int num : output) {
        std::cout<< num << " ";
    }
    assert(output == vector<int>({1,3,3,3,4,5,5,7}));
}