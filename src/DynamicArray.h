//The goal is to replicate the std::vector container
//A regular array that can grow or shrink at runtime

#include <task.h>

class DynamicArray{
    private:
        Task* data; //pointer to array in the heap
        int size; //# elements stored
        int capacity; //total allocated space
    public:
        DynamicArray(int initCapacity = 8); // Constructor
        void push_back(Task* task);
        void insert(Task* task, int index);
        void remove(int index);
        void sort();
};