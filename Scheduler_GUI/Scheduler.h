#ifndef Scheduler_H
#define Scheduler_H

#include "DynamicArray.h"
#include "MinHeap.h"
#include <iostream>
#include <chrono>
#include <vector>

struct TickCounter {
    int tick;
    int taskID;
};

void Array_Scheduler(DynamicArray& tasks, int sim_end, std::vector<TickCounter>& tickHistory_array);
void Heap_Scheduler(std::vector<Task>& tasks, int sim_end, std::vector<TickCounter>& tickHistory_heap);
//void benchmark();
// void optimized_benchmark();
// void Heap_Scheduler_Quiet(MinHeap& pq, int sim_end);
// void Array_Scheduler_Quiet(DynamicArray& tasks, int sim_end);

#endif