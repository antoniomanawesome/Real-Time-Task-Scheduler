#include "DynamicArray.h"
#include "MinHeap.h"
#include <iostream>
#include <chrono>
#include <vector>
void Array_Scheduler(DynamicArray& tasks, int sim_end);
void Heap_Scheduler(std::vector<Task>& tasks, int sim_end);
void benchmark();
void optimized_benchmark();
void Heap_Scheduler_Quiet(MinHeap& pq, int sim_end);
void Array_Scheduler_Quiet(DynamicArray& tasks, int sim_end);