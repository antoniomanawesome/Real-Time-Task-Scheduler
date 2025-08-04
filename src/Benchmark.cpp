#include "Benchmark.h"

void benchmark(){
    const int NUM_TASKS = 10000;
    const int SIM_END   = 5000;

    // ─── 1) Generate one master list of random tasks ───────────────────
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    DynamicArray arrayTasks;
    std::vector<Task> heapTasks;
    heapTasks.reserve(NUM_TASKS);

    for(int i = 0; i < NUM_TASKS; ++i){
        Task t{
            i,                     // ID
            std::rand() % 5,       // priority in [0..4]
            std::rand() % SIM_END, // period in [0..SIM_END-1]
            std::rand() % 10       // next_run_time in [0..9]
        };
        arrayTasks.push_back(t);
        heapTasks.push_back(t);
    }

    // ─── 2) Time the Array Scheduler ──────────────────────────────────
    auto startA = std::chrono::high_resolution_clock::now();
    Array_Scheduler(arrayTasks, SIM_END);
    auto endA   = std::chrono::high_resolution_clock::now();
    auto array_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endA - startA).count();
    std::cout << "Array Scheduler Time: " << array_ms << " ms\n\n";

    // ─── 3) Time the Heap Scheduler ───────────────────────────────────
    auto startH = std::chrono::high_resolution_clock::now();
    Heap_Scheduler(heapTasks, SIM_END);
    auto endH   = std::chrono::high_resolution_clock::now();
    auto heap_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endH - startH).count();
    std::cout << "Heap Scheduler Time : " << heap_ms << " ms\n";
}