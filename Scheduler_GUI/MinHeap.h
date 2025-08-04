#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include "DynamicArray.h"
#include "Task.h"
class MinHeap {
    public:
        MinHeap();
        bool empty() const;
        int size() const;
        void push(const Task& t);
        Task& top();
        void pop();
        void build(const std::vector<Task>& init) {
            heap = init;
            for(int i = int(heap.size())/2 - 1; i >= 0; --i)
                heapify_down(i);
        }
    private:
        std::vector<Task> heap;
        void heapify_up(int idx);
        void heapify_down(int idx);
        bool compare(int a, int b) const;  
};

#endif
