#include "DynamicArray.h"
#include "Scheduler.h"
#include <iostream>

int main(){
    DynamicArray tasks; // ID, priority, period, next_run_time
    DynamicArray::Task t1(1, 2, 0, 5); // periodic task every 5 ticks

    tasks.push_back(t1);
    tasks.push_back({2, 1, 3, 0}); // one-shot task on the third tick
    tasks.push_back({3, 1, 1, 2}); // periodic every 2 ticks

    Array_Scheduler(tasks, 10);

    std::cin.get();

    return 0;
}