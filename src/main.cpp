#include "DynamicArray.h"
#include "MinHeap.h"
#include "Scheduler.h"
#include <iostream>
#include <vector>
/*int main(){
    //────────────────────────────────────────────────────────────────
    constexpr int SIM_END = 10;   // how long we simulate for

    //─── 1) build & run Array_Scheduler ───────────────────────────
    DynamicArray arrayTasks;
    // now use Task directly, not DynamicArray::Task
    Task t1{1, 2, 0, 5};            // ID=1, pri=2, period=0, next=5
    arrayTasks.push_back(t1);
    arrayTasks.push_back({2, 1, 3, 0});
    arrayTasks.push_back({3, 1, 1, 2});

    //─── 2) copy into a std::vector<Task> before running array scheudler
    std::vector<Task> heapTasks;
    heapTasks.reserve(arrayTasks.get_size());
    for (int i = 0; i < arrayTasks.get_size(); ++i) {
        heapTasks.push_back(arrayTasks[i]);
    }

    std::cout << "=== Array Scheduler ===\n";
    Array_Scheduler(arrayTasks, SIM_END);

    

    std::cout << "\n=== Heap Scheduler ===\n";
    //auto start = std::chrono::high_resolution_clock::now();
    Heap_Scheduler(heapTasks, SIM_END);
    
    
    return 0;
    
   
}*/
int main(){
    benchmark();
    return 0;
}