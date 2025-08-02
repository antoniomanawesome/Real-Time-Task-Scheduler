// The goal is to replicate the std::vector container
// A regular array that can grow or shrink at runtime

// Made by Antonio Marrero-Acosta

#include <iostream>
#include "Task.h"

#ifndef DynamicArray_H
#define DynamicArray_H

class DynamicArray{
        
    public:
    /*
    struct Task{
            int ID;             // Task ID
            int priority;       // Task priority
            int period;         // Period of task (0 is aperiodic, >0 is periodic)
            int next_run_time;  // When the task is scheduled to run next

            Task() : ID(0), priority(0), period(0), next_run_time(0) {}     // Default task constructor
            Task(int ID, int priority, int period, int run_time): ID(ID),   // Parameterized task constructor
            priority(priority), period(period), next_run_time(run_time)  {}
        };*/
       

        DynamicArray();                                     // initialize array with a default capacity
        ~DynamicArray();                                    // deallocating heap memory
        void push_back(const Task& task);                   // Add new item to the end of the array
        void remove(int index);
        int get_size() const;                               // Gets the size of the array
        int get_capacity() const;                           // Gets the capacity of the array
        Task& operator[](int index);                        // Have the ability to iterate through the array

    private:

        Task* data;     // Pointer to array in the heap
        int size;       // Number of elements stored
        int capacity;   // Total allocated space
        void resize();  // If size is at capacity, increase the size of the array
};

#endif