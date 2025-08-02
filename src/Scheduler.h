#include "DynamicArray.h"
#include <iostream>
#include <chrono>
#include <vector>
void Array_Scheduler(DynamicArray& tasks, int sim_end);
void Heap_Scheduler(std::vector<Task>& tasks, int sim_end);
void benchmark();