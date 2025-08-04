#include "Scheduler.h"
#include "MinHeap.h"
#include "Task.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()
#include <random>

void Array_Scheduler(DynamicArray& tasks, int sim_end){
    int curr_time = 0, index = 0;
    while(curr_time < sim_end){

        // reset the index
        index = -1;

        // find task to run
        for(int i = 0; i < tasks.get_size(); i++){
            auto &task = tasks[i]; // storing current task
            if(task.next_run_time <= curr_time){ 
                if(index == -1 || (task.priority < tasks[index].priority)) index = i; //if the index's priority is higher than current loop priority override index
            }
        }

        // execute the task
        if(index != -1){
            auto &task = tasks[index];
            /*std::cout << "Tick " << curr_time << ": Running Task " << task.ID << std::endl;*/
            

            if(task.period > 0) task.next_run_time += task.period; // if task is periodic, reschedule it
            else tasks.remove(index); // task is run, remove it from array
        }
       // else std::cout << "Tick " << curr_time << ": IDLE" << std::endl;

        curr_time++; // increment the time now that the task has been run on the time tick
    }

}

/*void benchmark(){
    const int NUM_TASKS = 10000;
    const int SIM_END = 5000;

    DynamicArray arrayTasks;

    // ID, priority, period, next_run_time

    //ARRAY VERSION
    for(int i = 0; i < NUM_TASKS; i++){
        arrayTasks.push_back({i, rand() % 5, rand() % SIM_END, rand() % 10});
    }

    auto start = std::chrono::high_resolution_clock::now();
    Array_Scheduler(arrayTasks, SIM_END);
    auto end = std::chrono::high_resolution_clock::now();
    auto Array_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Array Scheduler Time: " << Array_duration << " ms" << std::endl;

    //HEAP VERSION

}*/

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



void Heap_Scheduler(std::vector<Task>& tasks, int sim_end) {
    MinHeap pq;
    for (auto &t : tasks) {
        pq.push(t);
    }
    /*std::cout << "-- HEAP ORDER BEFORE SIM --\n";
    {
        MinHeap copy = pq;  
        while (!copy.empty()) {
            auto t = copy.top();
            copy.pop();
            std::cout << "  ID=" << t.ID
                      << " next=" << t.next_run_time
                      << " pri="  << t.priority << "\n";
        }
    }
    std::cout << "--------------------------\n";*/
    // ─── Smoke‐test: print heap order before simulation ─────────────
    

    for (int curr_time = 0; curr_time < sim_end; ++curr_time) {
        // ─── Debug: show what the heap thinks is next ───────────────────
        /*if (!pq.empty()) {
            const auto &peek = pq.top();
            std::cout << "[DBG] Tick " << curr_time
                      << "  HeapTop -> ID="   << peek.ID
                      << " next="           << peek.next_run_time
                      << " pri="            << peek.priority
                      << "\n";
        }
*/
     

        // ─── Run one ready task, or idle ────────────────────────────────
        if (!pq.empty() && pq.top().next_run_time <= curr_time) {
            Task task = pq.top();
            pq.pop();
            /*std::cout << "Tick " << curr_time
                      << ": Running Task " << task.ID << "\n";*/
            if (task.period > 0) {
                task.next_run_time += task.period;
                pq.push(task);
            }
        } 
        /*
        else {
            std::cout << "Tick " << curr_time
                      << ": IDLE\n";
        }
        */
    }
}

