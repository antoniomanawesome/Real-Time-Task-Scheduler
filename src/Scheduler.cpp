#include "Scheduler.h"

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
            std::cout << "Tick " << curr_time << ": Running Task " << task.ID << std::endl;

            if(task.period > 0) task.next_run_time += task.period; // if task is periodic, reschedule it
            else tasks.remove(index); // task is run, remove it from array
        }
        else std::cout << "Tick " << curr_time << ": IDLE" << std::endl;

        curr_time++; // increment the time now that the task has been run on the time tick
    }

}

void benchmark(){
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

}