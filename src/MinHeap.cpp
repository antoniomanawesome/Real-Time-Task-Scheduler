#include "MinHeap.h"
#include <algorithm>
#include "Task.h"
MinHeap::MinHeap() { }

bool MinHeap::empty() const {
    return heap.empty();

}

int MinHeap::size() const{
    return heap.size();

}

void MinHeap::push(const Task& t){
    heap.push_back(t);
    heapify_up(heap.size() - 1);
}

Task& MinHeap::top() {
    return heap.front();
}

void MinHeap::pop() {
    std::swap(heap.front(), heap.back());
    heap.pop_back();
    if (!heap.empty()) heapify_down(0);
}
bool MinHeap::compare(int a, int b) const {
    const auto &A = heap[a], &B = heap[b];

    // 1) run‐time ordering
    if (A.next_run_time != B.next_run_time)
        return A.next_run_time < B.next_run_time;

    // 2) priority ordering
    if (A.priority != B.priority)
        return A.priority < B.priority;

    // 3) tie‐break by ID so it’s 100% deterministic
    return A.ID < B.ID;
}

void MinHeap::heapify_up(int idx) {
    while(idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare(idx, parent)) {
            std::swap(heap[idx], heap[parent]);
            idx = parent;
        } else break;
    }
}

void MinHeap::heapify_down(int idx) {
    int n = heap.size();
    while(true){
        int left  = 2*idx + 1;
        int right = 2*idx + 2;
        int smallest = idx;

        if(left < n && compare(left, smallest))
            smallest = left;
        if(right < n && compare(right, smallest))
            smallest = right;

        if(smallest != idx){
            std::swap(heap[idx], heap[smallest]);
            idx = smallest;
        }
        else break;
    }
}